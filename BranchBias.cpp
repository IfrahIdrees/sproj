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

namespace
{
struct BranchBias : ModulePass
{
    static char ID;
    Function* toCall;
    Function* toPrint;
    BranchBias() : ModulePass(ID) {}
    virtual bool runOnModule(Module &M)
    {
        std::vector<Type *> a;
        std::vector<Type *> b;
        FunctionType *pntype = FunctionType::get(Type::getVoidTy(M.getContext()), b, false);
        PointerType *p1 = PointerType::get(IntegerType::get(M.getContext(), 8), 0);
        a.push_back(p1);
        a.push_back(IntegerType::get(M.getContext(), 1));
        FunctionType *fntype = FunctionType::get(Type::getVoidTy(M.getContext()), a, false);
        // M.getOrInsertFunction()
        toCall = (Function *)(M.getOrInsertFunction("check", fntype));
        // toCall = cast<Function>(funcToCall);
        // Function::arg_iterator arguments = toCall->arg_begin();
        toPrint = (Function *)(M.getOrInsertFunction("print", pntype));

        for (auto &F : M)
        {
            for (auto &BB : F)
            {
                // auto* b = &BB;
                // IRBuilder<> builder(b);
                for (BasicBlock::iterator iter = BB.begin(), end = BB.end(); iter != end; iter++)
                {
                    Instruction *I = &*iter;
                    IRBuilder<> builder(I);

                    // errs() << I->getOpcodeName() << "\n";
                    if (isa<BranchInst>(I)){
                        // errs() << "here\n";
                        // BranchInst* shit = cast<BranchInst>(I);
                        // BasicBlock* sh = shit->getSuccessor(0);
                        BranchInst* II = cast<BranchInst>(I);
                        if (II->isConditional()){
                            unsigned int asdf = I->getNumOperands();
                            if (asdf > 1){
                                std::vector<Value *> args;
                                Value *str = builder.CreateGlobalStringPtr(I->getParent()->getParent()->getName(), "");
                                args.push_back(str);
                                args.push_back(I->getOperand(0));
                                // errs() << *(I->getOperand(0)) << "\n";
                                ArrayRef<Value *> ar(args);
                                builder.CreateCall(toCall, ar);
                            }
                        }
                    }
                    if (std::string(I->getParent()->getParent()->getName()) == "main" && std::string(I->getOpcodeName()) == "ret")
                    {
                        std::vector<Value *> x;
                        ArrayRef<Value *> ag(x);
                        builder.CreateCall(toPrint, ag);
                    }
                }
            }
        }
        return true;
    }
};
}
char BranchBias::ID = 0;

static void registerBranchBias(const PassManagerBuilder &,
                                 legacy::PassManagerBase &PM)
{
    PM.add(new BranchBias());
}
static RegisterStandardPasses
    RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                   registerBranchBias);
static RegisterPass<BranchBias> X("branchbias", "lul kappa", true, true);
