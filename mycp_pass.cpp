#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Constant.h"
#include "llvm/Analysis/ConstantFolding.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include <vector>
#include "llvm/Transforms/Scalar.h"
using namespace llvm;

namespace {
	struct const_prop : public FunctionPass {
		static char ID;
		const_prop() : FunctionPass(ID) {}

		virtual bool runOnFunction(Function &F) {
			std::vector < Instruction* > list_of_instrs;
			//put all instructions in the above vector
			for (inst_iterator inst = inst_begin(F), e = inst_end(F); inst != e; inst++){
				list_of_instrs.push_back(&*inst);
			}
			//check whether our vec is non empty
			while (!list_of_instrs.empty()){
				//take first instruction to process, delete it from vec
				Instruction *inst = list_of_instrs.front();
				

				//check if above instruction has atleast one use
				//instruction class is derived from Value
				if (!inst->use_empty()){
					if (Constant *constant = ConstantFoldInstruction(inst,
						F.getParent()->getDataLayout(),
						&getAnalysis<TargetLibraryInfoWrapperPass>().getTLI()
						)){

						//check instruction k uses, in mein we can substitute
						for (User *user: inst->users()){
							list_of_instrs.push_back(cast<Instruction>(user));
						}
						//function of value superclass
						inst->replaceAllUsesWith(constant); //if se jo aye ga
						list_of_instrs.erase(list_of_instrs.begin());
						inst->eraseFromParent();
					}
				}
				return true; //we changed the function
			}
		}
	};
}

char const_prop::ID = 0;
static RegisterPass<const_prop> X("cp", "my cp pass", false, true);
// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
// static void registerSkeletonPass(const PassManagerBuilder &,
// 												 legacy::PassManagerBase &PM) {
// 	PM.add(new const_prop());
// }
// static RegisterStandardPasses
// 	RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
// 								 registerSkeletonPass);
