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
#include <map>
#include "llvm/Transforms/Scalar.h"
using namespace llvm;

namespace {
  struct StaticCount : public ModulePass {
	static char ID;
	StaticCount() : ModulePass(ID) {}
    std::map < const char* , int> instmapper ;
    int total = 0;
	virtual bool runOnModule(Module &M) {
		for (auto& F: M){
            for (auto& BB: F){
            	for (auto& I: BB){
	            	auto* Inst = &I;
            		// errs() << Inst->getOpcodeName() << "\n";
            		const char* opcode = Inst->getOpcodeName();
	            	int value = instmapper[opcode] ;
                    instmapper[opcode] = value + 1;
                    total += 1;
	            }
            }
        }
	return false;
	}
    // virtual bool doFinalization(Module &M){
    //     for (auto iter = instmapper.begin(); iter != instmapper.end(); iter++){
    //             errs() << iter->first << " " << iter->second << "\n";
    //             total += iter->second;
    //         }
    //         errs() << "Total: " << total << "\n";
    //     return false;
    // }
    virtual void print(llvm::raw_ostream &OS, const Module *M) const{
        for (auto iter = instmapper.begin(); iter != instmapper.end(); iter++){
            OS << iter->first << " " << iter->second << "\n";
        }
        OS << "Total: " << total << "\n";
    }
  };
}

char StaticCount::ID = 0;

static void registerStaticCount(const PassManagerBuilder &,
						 legacy::PassManagerBase &PM) {
  PM.add(new StaticCount());
}
static RegisterStandardPasses
  RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                 registerStaticCount);
static RegisterPass<StaticCount> X("static", "staticcount", false, true);


