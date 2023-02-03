clang ./main.c -o main;

# Test01 Mandatory
./main < data/man/pub01-m.in > my-pub01.out 2> my-pub01.err;
diff data/man/pub01-m.out my-pub01.out; 
diff data/man/pub01-m.err my-pub01.err;

# Test02 Mandatory
./main < data/man/pub02-m.in > my-pub02.out 2> my-pub02.err;
diff data/man/pub02-m.out my-pub02.out; 
diff data/man/pub02-m.err my-pub02.err;

# Test03 Mandatory
./main < data/man/pub03-m.in > my-pub03.out 2> my-pub03.err;
diff data/man/pub03-m.out my-pub03.out; 
diff data/man/pub03-m.err my-pub03.err;

# Test04 Mandatory
./main < data/man/pub04-m.in > my-pub04.out 2> my-pub04.err;
diff data/man/pub04-m.out my-pub04.out; 
diff data/man/pub04-m.err my-pub04.err;