clang ./main.c -g -o main;
valgrind ./main < data/man/pub01-m.in
valgrind ./main < data/man/pub02-m.in
valgrind ./main < data/man/pub03-m.in
valgrind ./main < data/man/pub04-m.in
valgrind ./main < data/man/pub05-m.in
valgrind ./main < data/man/pub06-m.in
valgrind ./main < data/man/pub07-m.in
valgrind ./main < data/man/pub08-m.in

valgrind ./main -prp-optional < data/opt/pub01-o.in
valgrind ./main -prp-optional < data/opt/pub02-o.in
valgrind ./main -prp-optional < data/opt/pub03-o.in
