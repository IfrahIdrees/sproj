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
#include <iostream>
#include <vector>
#include <iterator>
#include <set>
#include <map>
using namespace llvm;


namespace {
  struct SkeletonPass : public ModulePass {
  static char ID;
  int checkpoint = 1;
  const int inst_cp = 5;
  const int threshold = 3;
  std::vector< Instruction* > saved_stores;

  class states{
	std::vector<Instruction*> save;
	std::vector<Instruction*> compute;
	std::vector<Instruction*> intermediary;
	states(std::vector<Instruction *> a, std::vector<Instruction *> b, std::vector<Instruction *> c){
		//copy input vectors to class vectors
		//change the following line of code, it doesnt work. iterator equal kar k copy krna parna
		save = a; compute = b; intermediary = c;
	}
  };
   std::map<Instruction*,states> checkpoint_list; 
	SkeletonPass() : ModulePass(ID) {}
   
	// void iterate//
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
	virtual bool runOnModule(Module &M) {
		int uses = 0;
		for (auto& F: M){
		    for (auto& BB: F){
		    	for (auto& Inst: BB){
					auto* I = &Inst;
							
		 		  // std::set<Value*> live_variable; 
			  		if (F.getName() == "main" && 
			 		checkpoint % inst_cp == 0){
						 //at checkpoint
						 //reverse the instructions
						std::vector<Instruction*> save, compute, inter;
						for (int st = 0; st < saved_stores.size(); st++){
							Instruction* next_to_save_instr = saved_stores[st];
							BasicBlock::iterator it1(next_to_save_instr);
							it1--;
							Instruction* save_instr = &*it1;
							uses = getNumUses(save_instr);
							if (uses > threshold){
								save.push_back(save_instr);
							}
							else{
								std::vector<Instruction*> temporary_uses = getUses(save_instr);
								temporary_uses.push_back(save_instr);
								compute.insert(compute.end(), std::make_move_iterator(temporary_uses.begin()), std::make_move_iterator(temporary_uses.end()));
							}
						}
						//back track
						if (std::string("store") != I->getOpcodeName()){
							// std::vector<Instruction*> inter;
							BasicBlock::iterator it2(saved_stores[saved_stores.size()-1]);
							//go till current instruction
							for (inst_iterator iter = it2; iter != Inst; iter++){
								inter.push_back(&*iter);
							}
						}
						//fix states constructor
						states current_checkpoint(save, compute, inter);


						// if(I->getOpcodeName() == std::string("store")){
						// 	uses = getNumUses(&*I);
						// 	errs() << "Uses for: " << *I << "\n";
						// 	errs() << "Number of uses: " << uses << "\n";
						// 	if (uses > threshold)
						// 	{
						// 		//save
						// 		errs() << "have to save these\n";
						// 		std::vector<Instruction *> allUses = getUses(&*I);
						// 		Value *val = dyn_cast<Value>(I->getOperand(0));
						// 		errs() << *val << "\n";
						// 	}
						// 	else
						// 	{
						// 		//make formula for recompute
						// 		std::vector<Instruction *> computeUses = getUses(&*I);
						// 		computeUses.push_back(&*I);
						// 		errs() << "have to compute  these\n";
						// 		errs() << *I << "\n";
						// 		errs() << "The uses are: \n";
						// 		for (int a = 0; a < computeUses.size(); a++)
						// 		{
						// 			errs() << *computeUses[a] << "\n";
						// 		}
						// 	}
						// }
						// else{
						// 	//go back to the last store and save instructions till checkpoint
						// }   
		    			
					uses = 0; 
				}
				else if (F.getName() == "main" && checkpoint % inst_cp == 1){
					saved_stores.clear();
				}
				else if (F.getName() == "main" && checkpoint % inst_cp != 0){
					if (I->getOpcodeName() == std::string("store")){
						BasicBlock::iterator it(I);
						++it;
						if (it != I->getParent()->end()){
							saved_stores.push_back(&*it);
						}
					}
				}

					checkpoint++;
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