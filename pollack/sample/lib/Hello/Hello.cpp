#define DEBUG_TYPE "hello"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/Casting.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/ADT/ValueMap.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/IR/SymbolTableListTraits.h"
#include <vector>
using namespace llvm;


#define DEBUG 1


namespace {
struct Hello :  public FunctionPass
{

        /** Constructor. */
	static char ID;
	Hello() : FunctionPass(ID) {
	}
	
	GlobalVariable* gvar_int32_g;
        Function*       func_pop_direct_branch;
	std::vector<llvm::StringRef> funcNames;

	virtual bool doInitialization(Module &M){

		
		gvar_int32_g = new GlobalVariable(M,
			IntegerType::get(M.getContext(),32),
			false,
			GlobalValue::ExternalLinkage, /*TODO: Check that linkage is correct */
			0,
			"g");
		gvar_int32_g->setAlignment(4);

		for(Module::iterator iterF = M.begin(), iterE = M.end(); iterF != iterE; ++iterF){
			Function *currFunc = iterF;
			if(!currFunc->isDeclaration()){
				funcNames.push_back(currFunc->getName());
			}
		}

		func_pop_direct_branch = M.getFunction("pop_direct_branch");
	       
		if (!func_pop_direct_branch) {

	          errs() << "Could not find function \"pop_direct_branch\"" << "\n";
	  
	          #if 0
		  func_pop_direct_branch = Function::Create(
							    /*Type=*/FuncTy_6,
							    /*Linkage=*/GlobalValue::ExternalLinkage,
							    /*Name=*/"pop_direct_branch", M); 
		  func_pop_direct_branch->setCallingConv(CallingConv::C);
		  #endif
		}
		AttributeSet func_pop_direct_branch_PAL;
		{
		  SmallVector<AttributeSet, 4> Attrs;
		  AttributeSet PAS;
		  {
		    AttrBuilder B;
		    B.addAttribute(Attribute::NoUnwind);
		    B.addAttribute(Attribute::UWTable);
		    PAS = AttributeSet::get(M.getContext(), ~0U, B);
		  }
  
		  Attrs.push_back(PAS);
		  func_pop_direct_branch_PAL = AttributeSet::get(M.getContext(), Attrs);
  
		}
		func_pop_direct_branch->setAttributes(func_pop_direct_branch_PAL);

		
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
					if(callingFunc && callingFunc->getName().front() == 'p' && (std::find(funcNames.begin(), funcNames.end(), callingFunc->getName()) != funcNames.end())){
						errs() << "Cloning " << callingFunc->getName() << "\n";
						llvm::ValueToValueMapTy VMap;
						llvm::ClonedCodeInfo *CodeInfo = (ClonedCodeInfo *)malloc(sizeof(ClonedCodeInfo));
						// TODO: Determine if correct assignment to CodeInfo
						CodeInfo->ContainsCalls = false;
						CodeInfo->ContainsDynamicAllocas = false;
						Function *clonedFunc = llvm::CloneFunction(callingFunc, VMap, CodeInfo);

						// For testing purposes - Make sure cloned functions are identical
						#if DEBUG
						errs() << "Printing Original Function:\n";
						for(Function::iterator o = callingFunc->begin(), oe = callingFunc->end(); o != oe; ++o){
							BasicBlock* OB = o;
							for(BasicBlock::iterator oI = OB->begin(), oIE = OB->end(); oI != oIE; ++oI){
								Instruction *origInstr = oI;
								errs() << *origInstr << "\n";
							} 
						}
						#endif
											
						//errs() << "Printing cloned function:\n";
						for(Function::iterator c = clonedFunc->begin(), ce = clonedFunc->end(); c != ce; ++c){
							BasicBlock *CB = c;
							for(BasicBlock::iterator cI = CB->begin(), cIE = CB->end(); cI != cIE; ++cI){
								Instruction *clonInstr = cI;
								//errs() << *clonInstr << "\n";
								if(isa<ReturnInst>(clonInstr)){									
									Value* retVal = cast<ReturnInst>(clonInstr)->getReturnValue();
									if(retVal){
										errs() << "Returning " << *retVal << "\n";
										// Store return value in g
										StoreInst *str     = new StoreInst(retVal, gvar_int32_g, clonInstr);										
										
										#if DEBUG
										for(BasicBlock::iterator strI = CB->begin(), strIE = CB->end(); strI != strIE; ++strI){
											Instruction *clonInstrStr = strI;
											errs() << *clonInstrStr << "\n";
										}
										#endif
										// TODO: Do we need to remove cloneInstr from function?
									}
									else{
										errs() << "Returning void\n";
										// Don't need to store to g
									}

									// Insert a call to the pop_direct_branch function right before the return call
									// and after the new Store Instruction
									CallInst* pop_call = CallInst::Create(func_pop_direct_branch, "", clonInstr);
								}
							}
						}

						#if DEBUG
						errs() << "Printing Cloned and Modified Function:\n";
						for(Function::iterator o = clonedFunc->begin(), oe = clonedFunc->end(); o != oe; ++o){
							BasicBlock* OB = o;
							for(BasicBlock::iterator oI = OB->begin(), oIE = OB->end(); oI != oIE; ++oI){
								Instruction *origInstr = oI;
								errs() << *origInstr << "\n";
							} 
						}
						#endif

					errs() << "Done with function call: " << callingFunc->getName() << "\n";
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



