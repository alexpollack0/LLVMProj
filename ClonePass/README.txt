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
3. Created a test script

Testing:
1. MultCallTest.c
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
