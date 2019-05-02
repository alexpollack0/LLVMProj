Alex Pollack, Carl Brando
Group Number: 8

Alex Pollack - Contributions:
1. Initial creation of global variable
2. Search for all user-defined functions, determine which functions start with “p”
3. Cloning of functions including
3a. Addition of a store instruction at the end of the function to save the return value to a global variable
3b. Ensuring that the proper cloned version of functions is always called
4. Creation of several test cases

Carl Brando - Contributions:
1. Add pop_direct_branch call to cloned functions
2. Loading the value from the global variable
2a. Making sure that the load from the global variabe made it to all the instruction that use it
3. Created a test script
4. Creation of several test cases

Testing:
1. MultCallTest.c and use_after_call.c
- Ensure that cloned functions properly call cloned functions
- Ensure proper return values: return var + pfunc(var)
2. multi_site.c
- Ensure if a function that has been cloned is twice called in another function, the calling function
calls the cloned version both times
3. mult_pow.c
- Ensure proper return values: return pfunc(var) + var
4. NotSavingRet.c
- Ensure proper execution when not saving a value returned

How to run:
In the directory 'test_code', run the bash script: ./test_helper.sh
The execution of the script generates both optimized ("_cloned") and non-optimized ("_original") version of the bytecode, assembly, ir, and executable.
Proper functionality can be tested by running the original and cloned versions of the executable and ensuring identical output.
Examining the ir can also be helpful in ensuring that cloned functions are consistently called and the global variable is used in the proper manner.

Short summary:
For this project we created an LLVM ModulePass. This pass overrides the doInitilazation and runOnModule functions.
The do doInitilazation fucntion will first collect all the user defined functions in the module and store them in a
vector. Next it will create a global variable for us to use to store the return value of our cloned functions. Finally, it will
extract the pop_direct_branch function from the module to be used later.

The runOnModule function is where most of the work of our pass is done. It begins be iterating through all the functions in the module.
For each function it will call the getClones function which will return a vector containing all the cloned versions of the current function.
If a clone already exists for this function we pass the cloned function to entireClone otherwise we pass the original function. This is so
that we will make sure to process the cloned version of a function if it has already been cloned instead of the original one.

The function entireClone will iterate through all the instructions of a given function and find calls to user defined functions that begin with 'p'.
For each of these functions it will check if they have been already cloned. If it has it will reuse the clone. Otherwise it will build a new clone by calling buildClone.
The buildClone function will call LLVM's CloneFunction and append '_cloned_' to beginning the function name of the new clone. Next, it will find all the return
instructions and insert a store to the global variable g of the value that was being returned. It will also insert a call to the function pop_direct_branch right before
the return instruction.

After cloning or using the already cloned version of a function entireClone will insert a load from the global variable g right after the function call. Next,
entireClone will check to see if there are instructions that use the functions return value. If so it will make sure that all their operands are
loaded after the function call and replace the operand from the call with the load from the global. Finally, buildClone will change the calling instruction to call
the cloned function instead of the original function. 
