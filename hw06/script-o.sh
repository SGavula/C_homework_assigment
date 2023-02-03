clang ./main.c -o main;

# Test01 Optional
./main -prp-optional < data/opt/pub01-o.in > my-pub01-o.out 2> my-pub01-o.err;
diff data/opt/pub01-o.out my-pub01-o.out; 
diff data/opt/pub01-o.err my-pub01-o.err;

# Test02 Optional
./main -prp-optional < data/opt/pub02-o.in > my-pub02-o.out 2> my-pub02-o.err;
diff data/opt/pub02-o.out my-pub02-o.out; 
diff data/opt/pub02-o.err my-pub02-o.err;

# Test03 Optional
./main -prp-optional < data/opt/pub03-o.in > my-pub03-o.out 2> my-pub03-o.err;
diff data/opt/pub03-o.out my-pub03-o.out; 
diff data/opt/pub03-o.err my-pub03-o.err;

# Test04 Optional
./main -prp-optional < data/opt/pub04-o.in > my-pub04-o.out 2> my-pub04-o.err;
diff data/opt/pub04-o.out my-pub04-o.out; 
diff data/opt/pub04-o.err my-pub04-o.err;

# Test05 Optional
./main -prp-optional < data/opt/pub05-o.in > my-pub05-o.out 2> my-pub05-o.err;
diff data/opt/pub05-o.out my-pub05-o.out; 
diff data/opt/pub05-o.err my-pub05-o.err;

# Test06 Optional
./main -prp-optional < data/opt/pub06-o.in > my-pub06-o.out 2> my-pub06-o.err;
diff data/opt/pub06-o.out my-pub06-o.out; 
diff data/opt/pub06-o.err my-pub06-o.err;

# Test07 Optional
./main -prp-optional < data/opt/pub07-o.in > my-pub07-o.out 2> my-pub07-o.err;
diff data/opt/pub07-o.out my-pub07-o.out; 
diff data/opt/pub07-o.err my-pub07-o.err;

# Test08 Optional
./main -prp-optional < data/opt/pub08-o.in > my-pub08-o.out 2> my-pub08-o.err;
diff data/opt/pub08-o.out my-pub08-o.out; 
diff data/opt/pub08-o.err my-pub08-o.err;

# Test09 Optional
./main -prp-optional < data/opt/pub09-o.in > my-pub09-o.out 2> my-pub09-o.err;
diff data/opt/pub09-o.out my-pub09-o.out; 
diff data/opt/pub09-o.err my-pub09-o.err;