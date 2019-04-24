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
#include "llvm/IR/Constants.h"
#include "llvm/PassAnalysisSupport.h"

#include <vector>
using namespace llvm;


#define DEBUG 1


namespace {
	struct Hello :  public ModulePass
	{

		/** Constructor. */
		static char ID;
		Hello() : ModulePass(ID) {
		}

		GlobalVariable* gvar_int32_g;
		Function*       func_pop_direct_branch;
		std::vector<llvm::StringRef> funcNames;

		virtual bool doInitialization(Module &M){

			gvar_int32_g = new GlobalVariable(M, IntegerType::get(M.getContext(),32), false, GlobalValue::ExternalLinkage, 0,"g");
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
				}
				#endif
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
			}

			return true;	
		}

		/**
		* @brief Runs this pass on the given module.
		* @param [in,out] M The module to analyze
		* @return true if the module was modified; false otherwise
		*/
		virtual bool runOnModule(llvm::Module &M){
			// Iterate through all functions in the module
			for(Module::iterator iterF = M.begin(), iterE = M.end(); iterF != iterE; ++iterF){

				Function *F = iterF;

				#if DEBUG // Print out contents of function before modification
				errs() << "-------------------Parsing function: " << F->getName() << "---------------------\n";
				errs() << "Contents before modification:\n";
				for(Function::iterator b = F->begin(), be = F->end(); b != be; ++b){
					BasicBlock* BB = b;
					for(BasicBlock::iterator i = BB->begin(), ie = BB->end(); i != ie; ++i){
						Instruction* IN = i;
						errs() << *IN << "\n";
					}
				}
				#endif


				for(Function::iterator b = F->begin(), be = F->end(); b != be; ++b){
					BasicBlock* BB = b;
					for(BasicBlock::iterator i = BB->begin(), ie = BB->end(); i != ie; ++i){
						Instruction* IN = i;
						if(isa<CallInst>(*IN)){

							CallInst *CI = cast<CallInst>(IN);
							Function* callingFunc = CI->getCalledFunction();							

							if(callingFunc && callingFunc->getName().front() == 'p' && (std::find(funcNames.begin(), funcNames.end(), callingFunc->getName()) != funcNames.end())){

								#if DEBUG // Print name of function to be cloned and the module
									errs() << "Cloning " << callingFunc->getName() << "\n";
									errs() << "Function's original Mod: " << (callingFunc->getParent())->getModuleIdentifier() << "\n";
									//errs() << "Func's subProgram: " << callingFunc->getSubprogram() << "\n";
								#endif

								llvm::ValueToValueMapTy VMap;
								llvm::ClonedCodeInfo *CodeInfo = (ClonedCodeInfo *)malloc(sizeof(ClonedCodeInfo));

								// TODO: Determine if correct assignment to CodeInfo
								CodeInfo->ContainsCalls = false;
								CodeInfo->ContainsDynamicAllocas = false;
								Function *clonedFunc = llvm::CloneFunction(callingFunc, VMap, CodeInfo);							

								//errs() << "cloned function's Mod: " << (clonedFunc->getParent()) << "\n";

								Twine f_name = clonedFunc->getName();

								//errs() << f_name << "\n";

								clonedFunc->setName("__cloned__" + f_name);

								#if DEBUG //Make sure cloned functions are identical
									errs() << "Printing Original Function:\n";
									for(Function::iterator o = callingFunc->begin(), oe = callingFunc->end(); o != oe; ++o){
										BasicBlock* OB = o;
										for(BasicBlock::iterator oI = OB->begin(), oIE = OB->end(); oI != oIE; ++oI){
											Instruction *origInstr = oI;
											errs() << *origInstr << "\n";
										}
									}
								#endif

								for(Function::iterator c = clonedFunc->begin(), ce = clonedFunc->end(); c != ce; ++c){
									BasicBlock *CB = c;
									for(BasicBlock::iterator cI = CB->begin(), cIE = CB->end(); cI != cIE; ++cI){
										Instruction *clonInstr = cI;

										if(isa<ReturnInst>(clonInstr)){

											Value* retVal = cast<ReturnInst>(clonInstr)->getReturnValue();

											if(retVal){

												#if DEBUG
													errs() << "Returning " << *retVal << "\n";
												#endif

												// Store return value in g
												StoreInst *str = new StoreInst(retVal, gvar_int32_g, clonInstr);

												#if DEBUG
													for(BasicBlock::iterator strI = CB->begin(), strIE = CB->end(); strI != strIE; ++strI){
														Instruction *clonInstrStr = strI;
														errs() << *clonInstrStr << "\n";
													}
												#endif

												Instruction *nextInstr = ++i;

												#if DEBUG
													errs() << "Previous Instruction: " << *IN << "\n";
													errs() << "Next Instruction: " << *nextInstr << "\n";
												#endif

												LoadInst* load_from_g = new LoadInst(gvar_int32_g, "", nextInstr);
												StoreInst *strG = new StoreInst(load_from_g, nextInstr->getOperand(1), false, nextInstr);

												#if DEBUG
													errs() << "Printing new str instruction: " << *strG << "\n";
												#endif

												// Remove nextInstr
												++i;
												nextInstr->dropAllReferences();
												nextInstr->eraseFromParent();

												#if DEBUG // Useful for testing that instructions have been added/deleted properly
													errs() << "Printing earlier function call: \n";
													for(BasicBlock::iterator cIEdit = BB->begin(), cIEditE = BB->end(); cIEdit != cIEditE; ++cIEdit){
														Instruction *instrU = cIEdit;
														errs() << *instrU << "\n";
													}
												#endif

											}else{
													errs() << "Returning void\n";
													// Don't need to store to g
											}

											// Insert a call to the pop_direct_branch function right before the return call
											// and after the new Store Instruction
											CallInst* pop_call = CallInst::Create(func_pop_direct_branch, "", clonInstr);											
										}
									}
								}

								#if 1
								errs() << "Printing Cloned and Modified Function:\n";
								for(Function::iterator o = clonedFunc->begin(), oe = clonedFunc->end(); o != oe; ++o){
									BasicBlock* OB = o;
									for(BasicBlock::iterator oI = OB->begin(), oIE = OB->end(); oI != oIE; ++oI){
										Instruction *origInstr = oI;
										errs() << *origInstr << "\n";
									}
								}
								
								#endif

								// Set the calling instruciton to call the cloned function insted of the original function
								CI->setCalledFunction(clonedFunc);
								M.getFunctionList().push_front(clonedFunc);
								// CallInst *cloned_call = CallInst::Create( clonedFunc, CI->getArgOperand(0), "", CI);
								// CI->dropAllReferences();
								// CI->eraseFromParent();					

								#if DEBUG
									errs() << "Done with function call: " << callingFunc->getName() << "\n";
								#endif
							}
						}
					}
				}

				#if DEBUG // Print out contents of function after modification
				errs() << "~~~~~~~~~~~~~~~~~~Parsing function: " << F->getName() << "~~~~~~~~~~~~~~~~~~~~\n";
				errs() << "Contents after modification:\n";
				for(Function::iterator b = F->begin(), be = F->end(); b != be; ++b){
					BasicBlock* BB = b;
					for(BasicBlock::iterator i = BB->begin(), ie = BB->end(); i != ie; ++i){
						Instruction* IN = i;
						errs() << *IN << "\n";
					}
				}
				#endif


			}

			return true;
		}
	};

// 	struct FPass :  public FunctionPass
// 	{

// 		/** Constructor. */
// 		static char ID;
// 		FPass() : FunctionPass(ID) {
// 		}

// 		virtual bool doInitialization(Module &M){
// 			AnalysisUsage* au = new AnalysisUsage();
// 			au->addRequired<Hello>();

// 			return true;
// 		}

// 		virtual bool runOnFunction(llvm::Function &F){
// 			errs() << "Running function pass!!!\n";

// 			return true;
// 		}
// 	};

}

char Hello::ID = 0;
static RegisterPass<Hello> X("hello", "Clone Test Pass", false, false);
//char FPass::ID = 1;
//static RegisterPass<FPass> Y("fpass", "Clone function pass", false, false);
