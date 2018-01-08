#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/User.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <set>
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Analysis/LoopInfo.h"
#include <map>
using namespace llvm;


namespace {
  struct SkeletonPass : public FunctionPass {
    static char ID;
    int checkpoint = 1;
    const int inst_cp = 4;
    const int threshold = 3;
    std::vector< Instruction* > saved_stores;
    std::vector< Instruction*> checkpoint_instructions;
    struct states{
      std::vector<Instruction*> save;
      std::vector< std::vector<Instruction*> > compute;
      // std::vector<Instruction*> intermediary;
    };
    std::map<Instruction*, states> checkpoint_list;
    void getAnalysisUsage(AnalysisUsage &AU) const override
    {
      AU.addRequired<LoopInfoWrapperPass>();
      AU.setPreservesAll();
    }
    SkeletonPass() : FunctionPass(ID) {}

  // void iterate//

    bool inVector(std::vector<Instruction*> vec, Instruction* instr) {
      errs() << "Comgin";
      // if (std::find(vec.begin(), vec.end(), instr) != vec.end()){
      //   errs() << "heeeeeeeellllllllloooooo\n";
      //   return 1;
      // }
      for (int i=0; i<vec.size(); i++){
        
        if (vec[i]->isIdenticalTo(instr)){
          errs() << "yeah\n";
          return 1;
        }
      }
      // for (int i = 0; i< vec.size(); i++) {
      //   Value* first,*second;
      //   if (vec[i]->getNumOperands() > 0){
      //     first = vec[i]->getOperand(0);
      //     second = vec[i]->getOperand(1);
      //   for (int j = 0; j < instr->getNumOperands(); j++) {
      //     Value* operand = (instr->getOperand(j));
      //     // errs() << *operand << "\n";
      //     // for (int j = 0 ; j < vec.size(); j++) {
      //     //   if (vec[j].getOperand)
      //     // }
      //     if (operand == first || operand == second) {
      //       return 1;
      //     }
      //   }
      //   }
      //   // errs() << *first << " ; " << second << "\n";

      // }
      

      return 0;
    }

    // void deleteAt(vector<Instruction*)
    int getNumUses(Instruction* I){
      int num_uses = 0;
      for (Use& U: I->operands()){
        Value* V = U.get();
        if (Instruction* use = dyn_cast<Instruction>(V)){
          num_uses++;
          num_uses += getNumUses(use);
        }
      }
      return num_uses;
    }
    int getRealNumUses(int num_uses, std::vector<Instruction*> uses, std::vector<Instruction*> save, std::vector< std::vector<Instruction*> > compute){
      int u = num_uses;
      for (int i=0; i<uses.size(); i++){
        if (inVector(save, uses[i]))
          u--;
        for (int j=0; j<compute.size(); j++){
          if (inVector(compute[j], uses[i]))
            u--;
        }
      }
      return u;
    }
    std::vector<Instruction*> getUses(Instruction* I) {
      std::vector<Instruction*> uses ;
      for (Use &U : I->operands()) {
        Value *v = U.get();
        if (Instruction *use = dyn_cast<Instruction>(v)) {
          uses.push_back(use);
          std::vector<Instruction*> lul_kappa = getUses(use);
          uses.insert(
            uses.end(),
            std::make_move_iterator(lul_kappa.begin()),
            std::make_move_iterator(lul_kappa.end())
            );
        }
      }
      return uses;
    }
    virtual bool runOnFunction(Function &F) {
      if (F.getName() != std::string("main"))
        return false;
      int uses = 0;
      std::vector<Instruction *> allLoopInstructions;
      //take each instruction in a loop and insert into above vector. it will be later used to filter uses which aren't inside a loop.
      // DO NOT CHANGE THE CODE BELOW
      if (!F.isDeclaration())
      {
        LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
        LoopInfo::iterator lit = getAnalysis<LoopInfoWrapperPass>().getLoopInfo().begin();
        LoopInfo::iterator let = getAnalysis<LoopInfoWrapperPass>().getLoopInfo().end();
        for (; lit != let; ++lit)
        {
          Loop *L = *lit;
          auto allBlocks = L->getBlocks();
          for (int s = 0; s < allBlocks.size(); s++)
          {
            BasicBlock *BB = allBlocks[s];
            for (BasicBlock::iterator bi = BB->begin(); bi != BB->end(); ++bi)
            {
              Instruction *loopInst = &*bi;
              allLoopInstructions.push_back(&*loopInst);
            }
          }
        }
      }
      //DO NOT CHANNGE THE CODE ABOVE
      // for (auto& F: M){
      // for (auto& BB: F){

      // errs() << BB.getInstList().size() << "\n";
      // for (auto& Inst: BB){
      for (inst_iterator Inst = inst_begin(F); Inst != inst_end(F); ++Inst){
        Instruction* I = &*Inst;
        // errs() << checkpoint << "shit: " << I << "\n";;

          std::vector< std::vector<Instruction*> > compute;
          std::vector<Instruction*> save;// inter; // 3 sets
          // std::set<Value*> live_variable; 
        if (std::string(F.getName()) == std::string("main") && 
          checkpoint % inst_cp == 0){
             //at checkpoint

            //get all save instructions one by one and perform use-def analysis
          for (int st = 0; st < saved_stores.size(); st++){

            Instruction* next_to_save_instr = saved_stores[st];
            BasicBlock::iterator it1(next_to_save_instr);
            it1--;
            Instruction* save_instr = &*it1;
            uses = getNumUses(save_instr);
            inst_iterator use_iter = Inst;
            use_iter--;
            uses = getRealNumUses(uses, getUses(save_instr), checkpoint_list[&*use_iter].save, checkpoint_list[&*use_iter].compute);
            if (uses > threshold){
              save.push_back(save_instr);
            }
            else{
              std::vector<Instruction*> temporary_uses = getUses(save_instr);
              temporary_uses.push_back(save_instr);
              std::vector<Instruction*> usesnotinloop ;
              for (int u=0; u<temporary_uses.size();u++){
                if (!inVector(allLoopInstructions, temporary_uses[u])){
                  usesnotinloop.push_back(temporary_uses[u]);
                }
                else{
                  save.push_back(temporary_uses[u]);
                }
              }
                //compute set has all the formulas, for each store statement in the format (an example below)
                //       alloca
                //       store
                //       add
                //       store (the actual store instruction is part of the set)
              compute.push_back(usesnotinloop);
                // compute.insert(compute.end(), std::make_move_iterator(temporary_uses.begin()), std::make_move_iterator(temporary_uses.end()));
            }
          }
            //back track
            // if store is not on checkpoint, then we go back to last store, and save instruction from then on to the chekcpoint
            // in an intermediary set
            // will decide what to do with them later
            // ONE SOLUTION: perform use def on these
            // we have the dictionary like
            // checkpoint_inst -> struct {save, compute , intermediary}
            // we iterate over intermediary, do use def, and filter instructions. Then we add them to save or compute set of
            // the same struct accordingly
          //save all instruction which arent used to make a store instruction
          if (std::string("store") != std::string(I->getOpcodeName())){
              // std::vector<Instruction*> inter;
              // fix if no stores
            for (int a=0; a<compute.size(); a++){
              if (inVector(compute[a], &*I)){
                errs() << "Instruction is being used as a Use, can not transfer to Save set\n";
              }
              // else{
              //   errs() << "FUCKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKlol\n";
              // }
            
            }
          //   //pseuday iss se neechay inter wali handling hain
          //     //MASLA HERE 
          //   if (saved_stores.size() > 0){
          //     BasicBlock::iterator next_to_store(saved_stores[saved_stores.size()-1]);
          //     BasicBlock::iterator curr_inst(I);
          //       //go till current instruction
          //     for (; curr_inst != next_to_store; --curr_inst){
          //       // errs() << "lul\n";
          //       // errs() << &*curr_inst << "     " << &*next_to_store << "\n";
          //       inter.push_back(&*curr_inst);
          //     }
          //     std::reverse(inter.begin(), inter.end());
          //   }
          //   else{
          //       // errs() << "hehehehhehe\n";
          //       // errs() << checkpoint << "\n";
          //       // errs() << checkpoint_instructions.size() << "\n";
          //     if (checkpoint_instructions.size() > 0){
          //         // errs() << checkpoint_instructions.size()-1 << "\n";
          //       BasicBlock::iterator bi(checkpoint_instructions[checkpoint_instructions.size()-1]);
          //         // errs() << "getting here\n";
          //       BasicBlock::iterator bf(I);
          //       for (BasicBlock::iterator iter = bi; iter != bf; iter++){
          //           // errs() << &*iter<< "\n";
          //         inter.push_back(&*iter);
          //           // errs() << "here?\n";
          //       }
          //     }
          //     else{
          //         // errs() << "here\n";
          //       errs() << checkpoint <<"\n";
          //         //If at pos5, need four decrements to goto pos1
          //       int iffi_counter = inst_cp-1;
          //       BasicBlock::iterator fin(I);
          //       for (BasicBlock::iterator iter = fin; iffi_counter>0; iter--){
          //           // errs() << "yes\n";
          //         errs() << iffi_counter << "\n";
          //         errs() << *iter << "\n";
          //         inter.push_back(&*iter);
          //         iffi_counter--;
          //       }
          //       std::reverse(inter.begin(), inter.end());
          //     }


          //   }
          //   //yahan se ooper inter handling
          }
            //fix states constructor
            // states* current_checkpoint = new states(save, compute, iter);
          errs() <<"writing to map\n";
          states current_checkpoint;
          current_checkpoint.save = save;
          current_checkpoint.compute = compute;
          // current_checkpoint.intermediary = inter;
            //dictionary key to value mapping
          checkpoint_instructions.push_back(&*I);
          checkpoint_list[&*I] = current_checkpoint;
          save.clear();
          compute.clear();
          // inter.clear();
          errs() << "done with checkpointing\n";
          uses = 0; 
        }
        else if (std::string(F.getName()) == std::string("main") && checkpoint % inst_cp == 1){
          saved_stores.clear();
        }
        else if (std::string(F.getName()) == std::string("main") && checkpoint % inst_cp != 0){
          if (I->getOpcodeName() == std::string("store")){
            BasicBlock::iterator it(I);
            ++it;
            if (it != I->getParent()->end()){
              saved_stores.push_back(&*it);
            }
          }
        }
        else{
          for (int a = 0; a < compute.size(); a++)
          {
           if (!inVector(compute[a], &*I))
            {
              errs() << "Not being used, so simply sent to save set\n";
              save.push_back(&*I);
            }
          }
        }
          // else if (F.getName() != "main"){
          //  errs() << F.getName() << "\n";
          //  // errs() << "lul kappa no main found\n";
          // }

        checkpoint++;
      }
        // checkpoint = 1;
        // }
      // }

      std::map<Instruction*,states>::reverse_iterator map_iterator, second_map_iterator;

    //iterator over the map
      for (map_iterator = checkpoint_list.rbegin(); map_iterator != checkpoint_list.rend(); map_iterator++) {
        states temp = map_iterator->second;
        // errs() << "FIRST" << "\n";
        for (int i = 0; i < map_iterator->second.compute.size(); i++) {
          // errs() << "SECOND" << "\n";

          for (int j = 0; j < map_iterator->second.compute[i].size(); j++) {
            // errs() << "THIRD" << "\n";
            bool dependency = false;
            for (second_map_iterator = map_iterator, second_map_iterator++; second_map_iterator != checkpoint_list.rend(); second_map_iterator++) {
              // errs() << "FOURTH" << "\n";
              errs() << second_map_iterator->second.save.size() << "\n";
              if (inVector(second_map_iterator->second.save, map_iterator->second.compute[i][j])) {
                dependency = true;
                // errs() << "HAI DEPENDANCY" << "\n";
                break;
              }
            }

          // transfer compute set to save set

            if (dependency) {
              map_iterator->second.save.insert(map_iterator->second.save.end(), map_iterator->second.compute[i].rbegin(), map_iterator->second.compute[i].rbegin()+1);
              map_iterator->second.compute.erase(map_iterator->second.compute.begin() + j);
              i--;
              continue;
            }


          // clear the save set for the 
          // map_iterator->second.compute.clear();
          }
        }
      }


      // printing for debug purposes
      std::map<Instruction*,states>::iterator map_iterator2;
      for (map_iterator2 = checkpoint_list.begin(); map_iterator2 != checkpoint_list.end(); map_iterator2++) {
        errs() << "-- Checkpoint instruction --" << "\n";
        errs() << *(map_iterator2->first) << "\n";
        errs() << "Save set: \n";
        for (int i = 0; i < map_iterator2->second.save.size(); i++) {
          errs() << *(map_iterator2->second.save[i]) << "\n";

        }
        // errs() << "Intermediary set: \n";
        // for (int i = 0; i < map_iterator2->second.intermediary.size(); i++) {
        //   errs() << *(map_iterator2->second.intermediary[i]) << "\n";
        // }
        errs() << "Computer set: \n";

        for (int i =0; i< map_iterator2->second.compute.size(); i++) {
          for (int j = 0; j < map_iterator2->second.compute[i].size(); j++) {
            errs() << *(map_iterator2->second.compute[i][j]) << "\n";
          }
        }
      }
      return false;
    }
  };
}

char SkeletonPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerSkeletonPass(const PassManagerBuilder &,
 legacy::PassManagerBase &PM) {
  PM.add(new SkeletonPass());
}
static RegisterStandardPasses
RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
 registerSkeletonPass);

static RegisterPass<SkeletonPass> X("course","shit");

// #include "llvm/Pass.h"
// #include "llvm/IR/Function.h"
// #include "llvm/Support/raw_ostream.h"
// #include "llvm/IR/LegacyPassManager.h"
// #include "llvm/Transforms/IPO/PassManagerBuilder.h"
// #include "llvm/IR/InstIterator.h"
// using namespace llvm;

// namespace {
//   struct SkeletonPass : public FunctionPass {
//     static char ID;
//     SkeletonPass() : FunctionPass(ID) {}

//     // void iterate//

//     void printUses(Instruction* I) {
//       for (Use &U : I->operands()) {
//         Value *v = U.get();
//         if (Instruction *use = dyn_cast<Instruction>(v)) {
//           errs() << *use << "\n";
//           printUses(use);
//         }

//       }
//     }

//     virtual bool runOnFunction(Function &F) {

//       for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I) {
//         // errs() << I->getOpcodeName();

//         std::string name(I->getOpcodeName());
//         if (name == "store") {

//         errs() << *I << "\n";
//         printUses(&*I);
//           // errs() << "ALKsjdklas";
//           // for (Use &U : I->operands()) {
//           //   Value *v = U.get();

//             // if (Instruction *use = dyn_cast<Instruction>(v)) {
//               // errs() << *use << "\n";

//             // }

//           // }

//           errs() << "\n\n";

//         }
//         // errs() << *I;
//       }
//   // errs() << *I << "\n"
//       // errs() << "I saw a function called " << F.getName() << "!\n";
//       return false;
//     }
//   };
// }

// char SkeletonPass::ID = 0;

// // Automatically enable the pass.
// // http://adriansampson.net/blog/clangpass.html
// static void registerSkeletonPass(const PassManagerBuilder &,
//                          legacy::PassManagerBase &PM) {
//   PM.add(new SkeletonPass());
// }
// static RegisterStandardPasses
//   RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
//                  registerSkeletonPass);

// static RegisterPass<SkeletonPass> X("course","shit");
