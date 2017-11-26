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
using namespace llvm;

namespace {
  struct SkeletonPass : public FunctionPass {
    static char ID;
  int checkpoint = 1;
  const int inst_cp = 5;
  const int threshold = 3;
    SkeletonPass() : FunctionPass(ID) {}

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
    virtual bool runOnFunction(Function &F) {
		int uses = 0;
      for (auto& BB: F){
        for (auto& Inst: BB){
		  auto* I = &Inst;
		  std::set<Value*> live_variable;	
          if (F.getName() == "main" && 
              checkpoint % inst_cp == 0 &&  
              std::string(I->getOpcodeName()) == "store"){
			  uses = getNumUses(&*I);
              errs() << "Uses for: " << *I << "\n";
			  errs() << "Number of uses: " << uses << "\n";
			  if (uses > threshold){
				  //save
					errs() << "have to save these\n";
					std::vector<Instruction*> allUses = getUses(&*I);
					for (auto i = allUses.end()-1; i != allUses.begin()-1; --i){
						errs() << **i << "\n";
						// errs() << *((*i)->getOperand(0)) << "<--------------\n";
					}
				}
			  else{
				  //make formula for recompute
					errs() << "have to compute  these\n";
					errs() << *I->getOperand(0) << "\n";
			  }
			  uses = 0; 
          }
          checkpoint++;
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