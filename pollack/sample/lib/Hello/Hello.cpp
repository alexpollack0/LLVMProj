//===- Hello.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements two versions of the LLVM "Hello World" pass described
// in docs/WritingAnLLVMPass.html
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "hello"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/Casting.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/ADT/ValueMap.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/Cloning.h"

using namespace llvm;



namespace {
struct Hello :  public FunctionPass
{

        /** Constructor. */
	static char ID;                           
	Hello() : FunctionPass(ID) {
	}

	virtual bool doInitialization(Module &M){

		
		GlobalVariable* gvar_int32_g = new GlobalVariable(M,
			IntegerType::get(M.getContext(),32),
			false,
			GlobalValue::ExternalLinkage, /*TODO: Check that linkage is correct */
			0,
			"g");
		gvar_int32_g->setAlignment(4);
		
		return true;
	}

        /**
         * @brief Runs this pass on the given function.
         * @param [in,out] func The function to analyze
         * @return true if the function was modified; false otherwise
        */
        virtual bool runOnFunction(llvm::Function &F){
		errs() << "Function Name: ";
		errs().write_escaped(F.getName())<< "\n";
		errs() << "Getting instructions: \n";
		for(Function::iterator b = F.begin(), be = F.end(); b != be; ++b){
			BasicBlock* BB = b;
			for(BasicBlock::iterator i = BB->begin(), ie = BB->end(); i != ie; ++i){
				Instruction* IN = i;
				if(isa<CallInst>(*IN)){
					//errs() << *IN << "\n";
					CallInst *CI = cast<CallInst>(IN);
					Function* callingFunc = CI->getCalledFunction();
					if(callingFunc->getName().front() == 'p' && callingFunc->getName() != "printf"){
						errs() << "Cloning " << callingFunc->getName() << "\n";
						llvm::ValueToValueMapTy VMap;
						llvm::ClonedCodeInfo *CodeInfo = (ClonedCodeInfo *)malloc(sizeof(ClonedCodeInfo));
						// TODO: Determine if correct assignment to CodeInfo
						CodeInfo->ContainsCalls = false;
						CodeInfo->ContainsDynamicAllocas = false;
						Function *clonedFunc = llvm::CloneFunction(callingFunc, VMap, CodeInfo);

						// For testing purposes - Make sure cloned functions are identical
						/*
						for(Function::iterator o = callingFunc->begin(), oe = callingFunc->end(); o != oe; ++o){
							BasicBlock* OB = o;
							for(BasicBlock::iterator oI = OB->begin(), oIE = OB->end(); oI != oIE; ++oI){
								Instruction *origInstr = oI;
								errs() << *origInstr << "\n";
							} 
						}
						errs() << "Printing cloned function:\n";
						for(Function::iterator c = clonedFunc->begin(), ce = clonedFunc->end(); c != ce; ++c){
							BasicBlock *CB = c;
							for(BasicBlock::iterator cI = CB->begin(), cIE = CB->end(); cI != cIE; ++cI){
								Instruction *clonInstr = cI;
								errs() << *clonInstr << "\n";
							}
						}
						*/
					}
				}
			}
		}
		return false;
	}
	};
}

char Hello::ID = 0;
static RegisterPass<Hello> X("hello", "Clone Test Pass", false, false);



