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

# Test05 Mandatory
./main < data/man/pub05-m.in > my-pub05.out 2> my-pub05.err;
diff data/man/pub05-m.out my-pub05.out; 
diff data/man/pub05-m.err my-pub05.err;

# Test06 Mandatory
./main < data/man/pub06-m.in > my-pub06.out 2> my-pub06.err;
diff data/man/pub06-m.out my-pub06.out; 
diff data/man/pub06-m.err my-pub06.err;

# Test07 Mandatory
./main < data/man/pub07-m.in > my-pub07.out 2> my-pub07.err;
diff data/man/pub07-m.out my-pub07.out; 
diff data/man/pub07-m.err my-pub07.err;

# Test08 Mandatory
./main < data/man/pub08-m.in > my-pub08.out 2> my-pub08.err;
diff data/man/pub08-m.out my-pub08.out; 
diff data/man/pub08-m.err my-pub08.err;

# Test09 Mandatory
./main < data/man/pub09-m.in > my-pub09.out 2> my-pub09.err;
diff data/man/pub09-m.out my-pub09.out; 
diff data/man/pub09-m.err my-pub09.err;
