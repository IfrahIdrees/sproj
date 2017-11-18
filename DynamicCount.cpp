#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Constant.h"
#include "llvm/Analysis/ConstantFolding.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include <vector>
#include <map>
#include "llvm/Transforms/Scalar.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"

using namespace llvm;

namespace {
    struct DynamicCount: ModulePass {
        static char ID;
        Function* toCall;
        Function* toPrint;
        // IRBuilder<> builder(entry);
        DynamicCount() : ModulePass(ID) {}
        virtual bool runOnModule(Module &M){
            // Constant *funcToCall = M.getOrInsertFunction("count", Type::getVoidTy(M.getContext()), NULL);
            std::vector<Type*> a;
            PointerType* p1 = PointerType::get(IntegerType::get(M.getContext(), 8), 0);
            a.push_back(p1);
            FunctionType* fntype = FunctionType::get(Type::getVoidTy(M.getContext()),a, false);
            // M.getOrInsertFunction()
            toCall = (Function*) (M.getOrInsertFunction("count", fntype));
                // toCall = cast<Function>(funcToCall);
            // Function::arg_iterator arguments = toCall->arg_begin();
            std::vector<Type*> b;
            FunctionType* pntype = FunctionType::get(Type::getVoidTy(M.getContext()),b, false);
            toPrint = (Function*) (M.getOrInsertFunction("print", pntype));

            for (auto& F: M){
                for (auto& BB: F){
                    // auto* b = &BB;
                    // IRBuilder<> builder(b);
                    for (BasicBlock::iterator iter = BB.begin(), end = BB.end()
                            ; iter != end; ++iter){
                                Instruction *I = &*iter;
                                IRBuilder<> builder(I);
                                std::vector<Value*> args;
                                Value* str  = builder.CreateGlobalStringPtr(I->getOpcodeName(), "");
                                args.push_back(str);
                                ArrayRef<Value*> ar (args);
                                
                            if (std::string(I->getOpcodeName()) == "phi")
                                builder.SetInsertPoint(I->getNextNode());
                            builder.CreateCall(toCall, ar);
                            if (std::string(I->getParent()->getParent()->getName()) == "main" && std::string(I->getOpcodeName()) == "ret"){
                                std::vector<Value*> x;
                                ArrayRef<Value*> ag(x);
                                builder.CreateCall(toPrint, ag);
                            }
                        // }
                    }
                }
            }
            return true;
        }
    };
}
char DynamicCount::ID = 0;

static void registerDynamicCount(const PassManagerBuilder &,
    legacy::PassManagerBase &PM) {
PM.add(new DynamicCount());
}
static RegisterStandardPasses
RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
registerDynamicCount);
static RegisterPass<DynamicCount> X("dynamic", "DynamicCount", true, true);

///////////////////////////////////////////////////////////////////
