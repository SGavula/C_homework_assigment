clang ./main.c -o main;

# Test01 Mandatory
valgrind ./main < data/pub01.in;
# Test02 Mandatory
valgrind ./main < data/pub02.in;
# Test03 Mandatory
valgrind ./main < data/pub03.in;
# Test04 Mandatory
valgrind ./main < data/pub04.in;
# Test05 Mandatory
valgrind ./main < data/pub05.in;
# Test06 Mandatory
valgrind ./main < data/pub06b.in;
