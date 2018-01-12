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
#include "llvm/IR/DataLayout.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <set>
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Dominators.h"
#include <map>
using namespace llvm;


namespace {
	struct SkeletonPass : public FunctionPass {
		static char ID;
		int checkpoint = 0;
		const int inst_cp = 20;
		const int threshold = 7;
		std::string functionName = "process_thread_webserver_process";
		// std::string functionName = "process_thread_calc_process";
		// std::string functionName = "collect_view_construct_message";
		std::vector< Instruction* > saved_stores;
		std::vector< Instruction*> checkpoint_instructions;
    // std::string functionName = ""
		struct states{
			std::vector<Instruction*> save;
			std::vector< std::vector<Instruction*> > compute;
      // std::vector<Instruaction*> intermediary;
		};
		std::map<Instruction*, states> checkpoint_list;
		void getAnalysisUsage(AnalysisUsage &AU) const override
		{
			AU.addRequired<LoopInfoWrapperPass>();
			AU.setPreservesAll();
		}
		SkeletonPass() : FunctionPass(ID) {}

  // void iterate//
		std::vector<BasicBlock *> makeSlice(std::vector<BasicBlock *> vec, int start, int end)
		{
      // std::vector<BasicBlock*> toReturn(end-start+1);
      // for (start; start < end; start++){
			return std::vector<BasicBlock *>(vec.begin() + start, vec.begin() + end + 1);
      // }
		}
		bool inVector(std::vector<Instruction*> vec, Instruction* instr) {
			// errs() << "Comgin";
      // if (std::find(vec.begin(), vec.end(), instr) != vec.end()){
      //   errs() << "heeeeeeeellllllllloooooo\n";
      //   return 1;
      // }
			for (int i=0; i<vec.size(); i++){
				// errs () << "inVector" << "\n";
				// errs() << vec[i] << "          " << instr << "\n";
				if (vec[i]->isIdenticalTo(instr)){
					// errs() << "yeah\n";
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
				// errs() << "inVector called from getRealNumUses\n";
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
			if (F.getName() != functionName)
				return false;
			int uses = 0;

			std::vector<Instruction *> allLoopInstructions;
			std::vector<BasicBlock*> loop;
			std::map<BasicBlock*, std::vector<Instruction*> > loopInfo;
			// errs() << F.getName() << "\n";
      // Module *m = F.getParent();
			std::vector<BasicBlock *> bblist;
			for (auto &BB : F)
			{
				auto *bb = &BB;
				bblist.push_back(bb);
			}
			int end, start;
			int loopStart;
      // errs() << bblist.size() ;
			for (end = 0; end < bblist.size(); end++)
			{
				TerminatorInst *tI = bblist[end]->getTerminator();
				if (BranchInst *bi = dyn_cast<BranchInst>(tI))
				{
					for (start = 0; start < end; start++)
					{
						for (int i = 0; i < bi->getNumSuccessors(); i++)
						{
							BasicBlock *successor = bi->getSuccessor(i);
							if (successor == bblist[start])
							{
								// errs() << "comparison successful\n";
								loopStart = shit;
								// errs() << end << " " << start << "\n";
								loop = makeSlice(bblist, start, end);
								break;
							}
						}
					}
				}
			}

			for (int i = 0; i < loop.size(); i++) {
				BasicBlock* bb = loop[i];
				std::vector<Instruction*> instructions;
				// BasicBlock& BB = bb;
				for (BasicBlock::iterator I = bb->begin(); I!=bb->end(); ++I) {
					// *I;
					Instruction* ins = &*I;

					// *ins;
					instructions.push_back(ins);
					errs() << "S: " << *ins << "\n";
				}


				loopInfo[bb] = instructions;

			}


      //  Function* thisFunc = &F;
      // llvm::DominatorTree* DT = new llvm::DominatorTree();
      //  DT->recalculate(*thisFunc);
      //  //generate the LoopInfoBase for the current function
      //  llvm::LoopInfoBase<llvm::BasicBlock, llvm::Loop>* KLoop = new llvm::LoopInfoBase<llvm::BasicBlock, llvm::Loop>();
      //  KLoop->releaseMemory();
      //  KLoop->Analyze(DT->getBase());

      //  errs() << "The number of block in this function are " << KLoop->getLoopDepth() << "\n";
      // std::vector<Instruction *> allLoopInstructions;
      // //take each instruction in a loop and insert into above vector. it will be later used to filter uses which aren't inside a loop.
      // // DO NOT CHANGE THE CODE BELOW
			
      //DO NOT CHANNGE THE CODE ABOVE
      // for (auto& F: M){
      // for (auto& BB: F){

      // errs() << BB.getInstList().size() << "\n";
      // for (auto& Inst: BB){
			std::vector< std::vector<Instruction*> > compute;
          		std::vector<Instruction*> save, remaining_inst;// inter; // 3 sets
          		for (inst_iterator Inst = inst_begin(F); Inst != inst_end(F); ++Inst){
          			Instruction* I = &*Inst;
        // errs() << checkpoint << "shit: " << I << "\n";;

          // std::set<Value*> live_variable; 
          			if (std::string(F.getName()) == functionName && 
          				checkpoint % inst_cp == 0){

          				compute.clear();
          				save.clear();
             //at checkpoint
          			// 	errs()<<"Checkpoint Instruction is"<< *I <<"\n";	
          			// errs() << "++++++++++++++++++++++++++++++save size before add: " << save.size() << "compute size before add: " << compute.size() << "\n";

            //get all save instructions one by one and perform use-def analysis
            	// errs()<<saved_stores.size()<<"\n";
          			if (I->getOpcodeName() == std::string("store")){
            		// errs() << "before populating save store \n";
          			// errs()<<*&*I<<"\n";
          				saved_stores.push_back(&*I);
          			}
          			else{
          				save.push_back(&*I);
          			}
          			for (int st = 0; st < saved_stores.size(); st++){

          				Instruction* save_instr = saved_stores[st];
          		// BasicBlock::iterator it1(next_to_save_instr);
          		// it1--;
          		// Instruction* save_instr = &*it1;
          				uses = getNumUses(save_instr);
          				inst_iterator use_iter = Inst;
          				use_iter--;
          				uses = getRealNumUses(uses, getUses(save_instr), checkpoint_list[checkpoint_instructions[checkpoint_instructions.size()-1]].save, checkpoint_list[checkpoint_instructions[checkpoint_instructions.size()-1]].compute);
          				// errs() << "Store instruction to be checked"<< *save_instr << "------"<< uses <<"\n";
          				if (uses > threshold){
          					save.push_back(save_instr);
          				}
          				else{
          					std::vector<Instruction*> temporary_uses = getUses(save_instr);
          					temporary_uses.push_back(save_instr);
          					// errs()<<"compute set"<<"\n";
          					// for (auto &i :temporary_uses){
          					// 	errs()<<*i<<"\n";
          					// }
          					// temporary_uses.push_back(save_instr);
          			// std::vector<Instruction*> usesnotinloop ;

                //compute set has all the formulas, for each store statement in the format (an example below)
                //       alloca
                //       store
                //       add
                //       store (the actual store instruction is part of the set)
          					compute.push_back(temporary_uses);
                // compute.insert(compute.end(), std::make_move_iterator(temporary_uses.begin()), std::make_move_iterator(temporary_uses.end()));
          				}
          			}
          			saved_stores.clear();
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
          			// if (std::string("store") != std::string(I->getOpcodeName())){
             //  // std::vector<Instruction*> inter;
             //  // fix if no stores
          			// 	for (int a=0; a<compute.size(); a++){
          			// 	errs () << "Invector called when instruction not store\n";
          			// 		if (inVector(compute[a], &*I)){
          			// 			errs() << "Instruction is being used as a Use, can not transfer to Save set\n";
          			// 		}
             //  // else{
             
             //  // }

          			// 	}
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
          			// }
            //fix states constructor
            // states* current_checkpoint = new states(save, compute, iter);
          			// errs() <<"writing to map\n";
          			// errs() << remaining_inst.size() << "\n";
          			// for (int c=0; c<compute.size();c++){
          			// 	// errs() << "compute set #" << c+1 << ":\n";
          			// 	for (int d=0;d<compute[c].size();d++){
          			// 		errs() << *compute[c][d] << "\n";
          			// 	}
          			// }
          			if(compute.size() != 0){
	          			for (int x=0; x<remaining_inst.size();x++){
		          			for (int a = 0; a < compute.size(); a++)
					          	{
		          				// errs() << "!invector called when instruction not store, and to be saved in save set\n";
					          		if (!inVector(compute[a], remaining_inst[x]))
					          		{
					          			// errs() << "Not being used, so simply sent to save set\n";
					          			save.push_back(remaining_inst[x]);
					          			break;
					          		}
					          		// else{
					          		// 	errs() << "Being used. cant send to save\n";
					          		// }
					          	}
	          			}
          			}
          			else{

	          			for (int x=0; x<remaining_inst.size();x++){
					        save.push_back(remaining_inst[x]);

	          			}

          			}
          			remaining_inst.clear();
          			states current_checkpoint;
          			current_checkpoint.save = save;
          			current_checkpoint.compute = compute;
          // current_checkpoint.intermediary = inter;
            //dictionary key to value mapping
          			Instruction* temp = &*I;
          			checkpoint_instructions.push_back(temp);
          			checkpoint_list[temp] = current_checkpoint;
          			// errs() << "******************************save size after add: " << save.size() << "         compute size after add: " << compute.size() << "\n";
          			// errs() << "Printing mapppppp\n";
          			// for (std::map<Instruction*, states>::iterator it = checkpoint_list.begin(); it != checkpoint_list.end(); ++it){
          			// 	// errs() << *(it->first) << "<- checkpoint instruction\n";
          			// 	// errs() << it->second.save.size() << "    "<<it->second.compute.size() << "\n";
          			// }
          			// save.clear();
          			// compute.clear();
          // inter.clear();
          			// errs() << "done with checkpointing\n";
          			uses = 0; 
          		}
          		// else if (std::string(F.getName()) == functionName && checkpoint % inst_cp == 1){
          		// 	saved_stores.clear();
          		// }
          		else if (std::string(F.getName()) == functionName){
          			if (I->getOpcodeName() == std::string("store")){
          		// BasicBlock::iterator it(I);
          		// ++it;
          		// errs()<<"before populating save store"<<"\n";
          		// errs()<<"outside if"<<*it<<"\n";
          		// if (it != I->getParent()->end()){
          			// errs()<<*&*I<<"\n";
          				saved_stores.push_back(&*I);
          			}
          			else{
          				// errs() << "COmpute ka size: " <<  compute.size() << "\n";
          				// errs() << "Remaining Instruction " << *I << "\n";
          				if (I->getOpcodeName() == std::string("ret")){
          					// errs() << "hmmmmmmmmmmm\n";
          					break;
          				}
          				remaining_inst.push_back(&*I);
         				
          			}
          	// }
          		}
          // else{
          // 	for (int a = 0; a < compute.size(); a++)
          // 	{
          // 		if (!inVector(compute[a], &*I))
          // 		{
          // 			errs() << "Not being used, so simply sent to save set\n";
          // 			save.push_back(&*I);
          // 		}
          // 	}
          // }
          // else if (F.getName() != "process_thread_processes_process"){
          //  errs() << F.getName() << "\n";
          //  // errs() << "lul kappa no process_thread_processes_process found\n";
          // }
          // for (int a = 0; a < compute.size(); a++)
          // {
          //   if (!inVector(compute[a], &*I))
          //   {
          //     errs() << "Not being used, so simply sent to save set\n";
          //     save.push_back(&*I);
          //   }
          // }
          		checkpoint++;
          	}
        // checkpoint = 1;
        // }
      // }
          	// errs() << "out of for loop\n";
          	std::map<Instruction*,states>::reverse_iterator map_iterator, second_map_iterator;


    //iterator over the map
          	for (map_iterator = checkpoint_list.rbegin(); map_iterator != checkpoint_list.rend(); map_iterator++) {
          		states temp = map_iterator->second;
          	// errs() << "lul kappa\n";
        // errs() << "FIRST" << "\n";
          		for (int i = 0; i < map_iterator->second.compute.size(); i++) {
          // errs() << "SECOND" << "\n";

          			for (int j = 0; j < map_iterator->second.compute[i].size(); j++) {
            // errs() << "THIRD" << "\n";
          				bool dependency = false;
          				for (second_map_iterator = map_iterator, second_map_iterator++; second_map_iterator != checkpoint_list.rend();second_map_iterator++) {
              // errs() << "FOURTH" << "\n";
          					// errs() << second_map_iterator->second.save.size() << "\n"; size zero
              // errs () << i << "     " << j << "\n";
              				// errs() << *map_iterator->second.compute[i][j] << "\n";
          					if (inVector(second_map_iterator->second.save, map_iterator->second.compute[i][j])) {
          						dependency = true;
                
          						break;
          					}
          				// errs() << "out of FOURTH\n";
          				}

          // transfer compute set to save set

          				if (dependency) {
          					map_iterator->second.save.insert(map_iterator->second.save.end(), map_iterator->second.compute[i].rbegin(), map_iterator->second.compute[i].rbegin()+1);
          					map_iterator->second.compute.erase(map_iterator->second.compute.begin() + j);
          					// if(i != 0){
								i--;
								break;
          					// }
          					// continue;
          				}


          // clear the save set for the 
          // map_iterator->second.compute.clear();
          			}
          		}
          	}

          	// errs() << "yup\n";
      // for ()
      // printing for debug purposesl
          	std::map<Instruction*,states>::iterator map_iterator2;
          	std::vector<Instruction*> startingInstructions;
          	std::vector<Instruction*> endingInstructions;
          	int basicBlockIndex, instructionIndex;
          	int endingBasicBlockIndex, endingInstructionIndex;


          	basicBlockIndex = -1;
          	endingBasicBlockIndex = -1;
          	bool flag = false;
          	for (map_iterator2 = checkpoint_list.begin(); map_iterator2 != checkpoint_list.end(); map_iterator2++) {
          		Instruction* checkpoint_instruction = (map_iterator2->first);

      	// if (flag) break;
          		for (int i = 0; i < loop.size(); i++) {
      			// if (flag)
      				// break;
          			std::vector<Instruction*> instructions = loopInfo[loop[i]];
          			for (int j = 0; j < instructions.size() ; j++) {
      			// errs() << "loop 1 k ander\n";
              // if (checkpoint_instruction->isIdenticalTo(instructions[j])) {
              	// errs() << *checkpoint_instruction ;//<< "  --   " <<*(instructions[j]) << "\n";
          				if (checkpoint_instruction==instructions[j]) {
      			// errs() << "loop 1 k if k ander\n";
      			// errs() << *checkpoint_instruction << "\n";
          					if (basicBlockIndex == -1 || i < basicBlockIndex) {

                	// errs() << "STARTING INSTRUCTION " << *checkpoint_instruction << "\n";
          						basicBlockIndex = i;
          						instructionIndex = j;

                // } else if (i < basicBlockIndex) {
                	// basicBlockIndex = i;
                	// instructionIndex = j	
          					}
                // flag = true;
                // break; 
          				}
          			}
          		}
          	}
     // flag = false;

          	std::map<Instruction*,states>::reverse_iterator map_iterator3;  
     // errs() << basicBlockIndex << "asdjkksajl " << instructionIndex << "\n";
          	for (map_iterator3 = checkpoint_list.rbegin(); map_iterator3 != checkpoint_list.rend(); map_iterator3++) {
      	// errs() << "ooper wala loop theek hai\n";
          		Instruction* checkpoint_instruction = map_iterator3->first;
      	//bool flag = false;
      	// if (flag) break;
          		for (int i = loop.size()-1 ; i >= 0; i--) {
      		// if (flag)
      			// break;
          			std::vector<Instruction*> instructions = loopInfo[loop[i]];
          			for (int j = instructions.size()-1; j >= 0; j--) {
          				if (checkpoint_instruction==instructions[j]) {
          					if (endingBasicBlockIndex == -1 || i > endingBasicBlockIndex) {
            		// errs() << "ENDING INSTURCTION: " << *checkpoint_instruction << "\n";
            	// errs() << "loop 2 k if k ander\n";
            	// errs() << *checkpoint_instruction << "\n";
          						endingBasicBlockIndex = i;
          						endingInstructionIndex = j;
          					}
              // flag=true;
              // break; 
          				}
          			}
          		}
          	}

     // errs() << endingBasicBlockIndex << "asdjkksajl--" << endingInstructionIndex << "\n";
      // errs () <<basicBlockIndex << " " << instructionIndex << " " << endingBasicBlockIndex << " " <<endingInstructionIndex << "\n";
          	std::vector<Instruction*> instructions;

          	// errs() << "THE BASIC BLOCK IS: " << "\n";
          	// loop[basicBlockIndex]->print(errs());
          	// errs() << "---^---";

          	if (basicBlockIndex != -1 || endingBasicBlockIndex != -1) {

          		
	          	for (int bb = 0; bb < basicBlockIndex; bb++) {
	          		instructions = loopInfo[loop[bb]];
	          		for (int j = 0; j < instructions.size(); j++) {
	          			startingInstructions.push_back(instructions[j]);
	          		}
	          	}

	          	instructions = loopInfo[loop[basicBlockIndex]];

	          	// errs() << "aslkdnaklsdnasndlkaknsdlkanksdlasd\n";
	          	for (int i = 0; i < instructionIndex; i++ ) {
	          		// errs()<<*instructions[i]<<"\n";
	          		startingInstructions.push_back(instructions[i]);
	          	}
	          	instructions = loopInfo[loop[endingBasicBlockIndex]];

	          	for (int i = endingInstructionIndex+1; i < instructions.size(); i++) {
	          		// errs()<<*instructions[i]<<"\n";
	          		endingInstructions.push_back(instructions[i]);
	          	}
	          	for (int bb = endingInstructionIndex+1; bb < loop.size(); bb++) {
	          		instructions = loopInfo[loop[bb]];
	          		for (int j = 0; j < instructions.size(); j++) {
	          			endingInstructions.push_back(instructions[j]);
	          		}
	          	}

	          	errs() << "printing sets" << "\n";
	          	errs() << "--------------------------------" << "\n";
	          	// std::reverse(endingInstructions.begin(), endingInstructions.end());
	          	errs() << "EXTRA SET LOOP INSIDE" << endingInstructions.size()<<"       "<<startingInstructions.size()<<"\n";
	          	for (int i = 0; i < endingInstructions.size(); i++) {
	          		errs() << *endingInstructions[i] << "\n";
	          	}

	          	for (int i = 0 ; i < startingInstructions.size(); i++) {
	          		errs() << *startingInstructions[i] << "\n";
	          	}
	          	// errs() << "------------------\n"; 

          	}
          	DataLayout* DL = new DataLayout(F.getParent());
          	for (map_iterator2 = checkpoint_list.begin(); map_iterator2 != checkpoint_list.end(); map_iterator2++) {
          		errs() << "-- Checkpoint instruction --" << "\n";
          		int save_size = 0; int total = 0;
          		// errs() << *(map_iterator2->first) << "\n";
          		errs() << "Save set: \n";
          		for (int i = 0; i < map_iterator2->second.save.size(); i++) {
          			Instruction* printInst = &*(map_iterator2->second.save[i]);
		      			errs() << *printInst << "\n";
          // errs() << *(map_iterator2->second.save[i]) << "\n";
          			if (!(*printInst->getType()).isVoidTy()){
          				save_size += DL->getTypeAllocSize(printInst->getType());
          				total += DL->getTypeAllocSize(printInst->getType());
          			}
          			else{
          				if (printInst->getOperand(0)->getType()->isSized()){
          					// errs() << "here\n";
          					// errs() << save_size << "before\n";
          					save_size += DL->getTypeAllocSize(printInst->getOperand(0)->getType());
          					// errs() << save_size << "after\n";
          					total += DL->getTypeAllocSize(printInst->getOperand(0)->getType());
          				}
          			}
          		}
        // errs() << "Intermediary set: \n";
        // for (int i = 0; i < map_iterator2->second.intermediary.size(); i++) {
        //   errs() << *(map_iterator2->second.intermediary[i]) << "\n";
        // }
          		errs() << "Compute set: \n";

          		for (int i =0; i< map_iterator2->second.compute.size(); i++) {
          			for (int j = 0; j < map_iterator2->second.compute[i].size(); j++) {
          				Instruction* pI = &*(map_iterator2->second.compute[i][j]);
          				errs() << *pI << "\n";
          					// errs() << "lulzzzzzzzzzzzzzzzzzzzzzzzz " <<*pI->getType() << "\n";
          				if (!(*pI->getType()).isVoidTy())
          				{
          					total += DL->getTypeAllocSize(pI->getType());
          				}
          				else{
          					if (pI->getOperand(0)->getType()->isSized()){
          						
	          					total += DL->getTypeAllocSize(pI->getOperand(0)->getType());
          					}
          				}
          			}
          		}
          		errs () << "Save set memory: "<< save_size << " Total memory: "<<  total << "\n"; 
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
