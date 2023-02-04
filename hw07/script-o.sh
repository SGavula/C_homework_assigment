clang ./grep.c -o grep;

#Test 01
./grep dvd < ./data/opt/pub01-A.in > my-pub01-A.out 2> my-pub01-A.err;
diff data/opt/pub01-A.out my-pub01-A.out; 
diff data/opt/pub01-A.err my-pub01-A.err;

#Test 02
./grep --color=always el ./data/opt/pub05-C.in > my-pub05-C.out 2> my-pub05-C.err;
diff data/opt/pub05-C.out my-pub05-C.out; 
diff data/opt/pub05-C.err my-pub05-C.err;