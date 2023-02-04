clang ./grep.c -o grep;

#Test 01
valgrind ./grep dvd < ./data/opt/pub01-A.in;

#Test 02
valgrind ./grep --color=always el ./data/opt/pub05-C.in;