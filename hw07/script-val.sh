clang ./grep.c -g -o grep;
valgrind ./grep < ./grep MemFr ./data/man/pub01-m.in;
valgrind ./grep < ./grep NeexistujiciText ./data/man/pub02-m.in;
valgrind ./grep < ./grep li ./data/man/pub03-m.in;
valgrind ./grep < ./grep xy ./data/man/pub04-m.in;