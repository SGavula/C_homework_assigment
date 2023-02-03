clang ./main.c -g -o main;

valgrind ./main -prp-optional < data/opt/pub01-o.in
valgrind ./main -prp-optional < data/opt/pub02-o.in
valgrind ./main -prp-optional < data/opt/pub03-o.in
valgrind ./main -prp-optional < data/opt/pub04-o.in
valgrind ./main -prp-optional < data/opt/pub05-o.in
valgrind ./main -prp-optional < data/opt/pub06-o.in
valgrind ./main -prp-optional < data/opt/pub07-o.in
valgrind ./main -prp-optional < data/opt/pub08-o.in
valgrind ./main -prp-optional < data/opt/pub09-o.in
