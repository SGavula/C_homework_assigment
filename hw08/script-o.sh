clang ./main.c -o main;

# Test01 Mandatory
./main < data/opt/pub01-o.in > my-pub01-o.out 2> my-pub01-o.err;
diff data/opt/pub01-o.out my-pub01-o.out;
diff data/opt/pub01-o.err my-pub01-o.err;