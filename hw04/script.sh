clang ./main.c -o main;

# Test01 Mandatory
./main < data/pub01.in > my-pub01.out 2> my-pub01.err;
diff data/pub01.out my-pub01.out; 
diff data/pub01.err my-pub01.err;

# Test02 Mandatory
./main < data/pub02.in > my-pub02.out 2> my-pub02.err;
diff data/pub02.out my-pub02.out;
diff data/pub02.err my-pub02.err;

# Test03 Mandatory
./main < data/pub03.in > my-pub03.out 2> my-pub03.err;
diff data/pub03.out my-pub03.out; 
diff data/pub03.err my-pub03.err;

# Test04 Mandatory
./main < data/pub04.in > my-pub04.out 2> my-pub04.err;
diff data/pub04.out my-pub04.out; 
diff data/pub04.err my-pub04.err;

# Test05 Mandatory
./main < data/pub05.in > my-pub05.out 2> my-pub05.err;
diff data/pub05.out my-pub05.out; 
diff data/pub05.err my-pub05.err;

# Test06 Mandatory
./main < data/pub06b.in > my-pub06.out 2> my-pub06.err;
diff data/pub06b.out my-pub06.out; 
diff data/pub06b.err my-pub06.err;
