clang ./main.c -g -o main;
valgrind ./main < data/opt/pub01-o.in
valgrind ./main < data/opt/pub02-o.in