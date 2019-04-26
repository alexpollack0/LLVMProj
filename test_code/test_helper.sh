#!/bin/bash
setenv PATH /afs/glue/class/old/enee/759c/llvm/llvm-3.4-install/opt/bin/:$PATH

# Clean the files
rm -f *.bc
rm -f *.s
rm -f *.x

for d in $PWD/*.c; do
    # Create the bytecode files for the test files
    clang -c -emit-llvm $d -o "${d%.*}.bc"

    # Create the original asm files for the test files
    llc "${d%.*}.bc" -o "${d%.*}_original.s"

    # Create the original executable for the test files
    gcc "${d%.*}_original.s" -o "${d%.*}_original.x"

    # Pass the bytecode files through our pass
    opt -load ../pollack/opt/lib/libHello.so -hello "${d%.*}.bc" -o "${d%.*}_cloned.bc"
    
    #  Create the asm files for the bytecode files that went through our pass
    llc "${d%.*}_cloned.bc" -o "${d%.*}_cloned.s"

    # Create the executables that have been run through our pass
    gcc "${d%.*}_cloned.s" -o "${d%.*}_cloned.x"

    # Create the IR files for the originals
    llvm-dis "${d%.*}.bc" -o "${d%.*}_original.ir"

    # Create th IR files for the ones that went through our pass
    llvm-dis "${d%.*}_cloned.bc" -o "${d%.*}_cloned.ir"
done





