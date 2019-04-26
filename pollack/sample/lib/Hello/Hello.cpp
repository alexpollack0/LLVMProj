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
#include "llvm/ADT/StringRef.h"
using namespace llvm;


#define DEBUG 1


namespace {

	std::vector<Function *> getClones(Function* currFunc);
	bool entireClone(llvm::Module &M, Function *F);

	struct Hello :  public ModulePass
	{

		/** Constructor. */
		static char ID;
		Hello() : ModulePass(ID) {
		}

		GlobalVariable* gvar_int32_g;
		Function*       func_pop_direct_branch;
		std::vector<llvm::StringRef> funcNames;
		std::vector<Function *> clonedFuncs;

		// Returns a vector holding cloned versions of a function in question
		std::vector<Function *> getClones(Function* currFunc){

			std::vector<Function *> toReturn;
			for(std::vector<Function*>::iterator iter = clonedFuncs.begin() ; iter != clonedFuncs.end(); ++iter){
				Function* currCheckFunc = *iter;
				if((currCheckFunc->getName()).find(currFunc->getName(), 0) != llvm::StringRef::npos){
					errs() << "Pushing " << currCheckFunc->getName() << ", Original function: "<< currFunc->getName() << "\n";
					toReturn.push_back(currCheckFunc);
				}
			}

			return toReturn;
		}

		Function* buildClone(Function* toClone, bool prevCloned){

			llvm::ValueToValueMapTy VMap;
			llvm::ClonedCodeInfo *CodeInfo = (ClonedCodeInfo *)malloc(sizeof(ClonedCodeInfo));

			CodeInfo->ContainsCalls = false;
			CodeInfo->ContainsDynamicAllocas = false;
			Function *clonedFunc = llvm::CloneFunction(toClone, VMap, CodeInfo);

			Twine f_name = clonedFunc->getName();

			clonedFunc->setName("_cloned_" + f_name);

			#if DEBUG //Make sure cloned functions are identical
			errs() << "Printing Original Function:\n";
			for(Function::iterator o = toClone->begin(), oe = toClone->end(); o != oe; ++o){
				BasicBlock* OB = o;
				for(BasicBlock::iterator oI = OB->begin(), oIE = OB->end(); oI != oIE; ++oI){
					Instruction *origInstr = oI;
					errs() << *origInstr << "\n";
				}
			}
			#endif

			if(!prevCloned){
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

							}else{
								errs() << "Returning void\n";
							}

							// Insert a call to the pop_direct_branch function right before the return call
							// and after the new Store Instruction
							CallInst* pop_call = CallInst::Create(func_pop_direct_branch, "", clonInstr);
						}
					}
				}
			}

			return clonedFunc;

		}

		bool entireClone(llvm::Module &M, Function *F){

			errs() << "In entireClone - " << F->getName() << "\n";

			for(Function::iterator b = F->begin(), be = F->end(); b != be; ++b){

				BasicBlock* BB = b;

				for(BasicBlock::iterator i = BB->begin(), ie = BB->end(); i != ie; ++i){

					Instruction* IN = i;
					errs() << "Instruction: " << *IN << "\n";

					if(isa<CallInst>(*IN)){

						CallInst *CI = cast<CallInst>(IN);
						Function* callingFunc = CI->getCalledFunction();
						errs() << "Call Instruction: " << *CI << "\n";

						if(callingFunc && callingFunc->getName().front() == 'p'
						&& (std::find(funcNames.begin(), funcNames.end(), callingFunc->getName()) != funcNames.end())
						&& callingFunc->getName() != "pop_direct_branch"){

							errs() << "Ready to clone " << callingFunc->getName() << "\n";

							std::vector<Function*> prevClonedFuncs = getClones(callingFunc);

							Function *newClonedFunc;
							// First time this function is being cloned
							if(prevClonedFuncs.empty()){

								#if DEBUG
									errs() << "First time cloning " << callingFunc->getName() << "\n";
								#endif
								newClonedFunc = buildClone(callingFunc, false);

							}
							// Function has previously been cloned
							else{

								#if DEBUG
								errs() << "Re-cloning " << callingFunc->getName() << "\n";
								#endif
								newClonedFunc = buildClone(prevClonedFuncs.at(0), true);

							}

							#if DEBUG
							errs() << "Printing Cloned and Modified Function: " << newClonedFunc->getName() << "\n";
							for(Function::iterator o = newClonedFunc->begin(), oe = newClonedFunc->end(); o != oe; ++o){
								BasicBlock* OB = o;
								for(BasicBlock::iterator oI = OB->begin(), oIE = OB->end(); oI != oIE; ++oI){
									Instruction *origInstr = oI;
									errs() << *origInstr << "\n";
								}
							}
							#endif


							Instruction *nextInstr = ++i;

							LoadInst* load_from_g = new LoadInst(gvar_int32_g, "", nextInstr);
							CI->replaceAllUsesWith(load_from_g);

							// Set the calling instruction to call the cloned function insted of the original function
							CI->setCalledFunction(newClonedFunc);
							M.getFunctionList().push_front(newClonedFunc);

							

							

							// 

							// if(isa<StoreInst>(nextInstr)){
							// 	#if DEBUG
							// 	errs() << "Previous Instruction: " << *IN << "\n";
							// 	errs() << "Next Instruction: " << *nextInstr << "\n";
							// 	#endif

							// 	LoadInst* load_from_g = new LoadInst(gvar_int32_g, "", nextInstr);
							// 	StoreInst *strG = new StoreInst(load_from_g, nextInstr->getOperand(1), false, nextInstr);


							// 	// Remove nextInstr
							// 	//++i;
							// 	//nextInstr->dropAllReferences();
							// 	//nextInstr->eraseFromParent();

							// }
							// else{
							// 	--i;
							// }
							// // CallInst *cloned_call = CallInst::Create( clonedFunc, CI->getArgOperand(0), "", CI);
							// // CI->dropAllReferences();
							// // CI->eraseFromParent();

							#if DEBUG
							errs() << "Done with function call: " << callingFunc->getName() << "\n";
							#endif

							clonedFuncs.push_back(newClonedFunc);
						}
					}
				}
			}
			return true;
		}

		virtual bool doInitialization(Module &M){

			for(Module::iterator iterF = M.begin(), iterE = M.end(); iterF != iterE; ++iterF){
				Function *currFunc = iterF;
				if(!currFunc->isDeclaration()){
					funcNames.push_back(currFunc->getName());
				}
			}

			gvar_int32_g = new GlobalVariable(M, IntegerType::get(M.getContext(),32), false, GlobalValue::ExternalLinkage, 0,"g");
			gvar_int32_g->setAlignment(4);

			ConstantInt* const_int32_0 = ConstantInt::get(M.getContext(), APInt(32, StringRef("0"), 10));
			gvar_int32_g->setInitializer(const_int32_0);

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

				std::vector<Function*> clonedCurr = getClones(F);

				if(clonedCurr.empty()){
					entireClone(M, F);
				}
				else{
					for(std::vector<Function*>::iterator iter = clonedCurr.begin() ; iter != clonedCurr.end(); ++iter){
						Function* currCheckFunc = *iter;
						entireClone(M, currCheckFunc);
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
