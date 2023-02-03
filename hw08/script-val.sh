clang ./main.c -g -o main;
valgrind ./main < data/man/pub01-m.in
valgrind ./main < data/man/pub02-m.in
valgrind ./main < data/man/pub03-m.in
valgrind ./main < data/man/pub04-m.in