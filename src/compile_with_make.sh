rm -f *.o amd64/*.o halley deps.mk undef_generator
clang -march=native -O3 -s -DNDEBUG -o undef_generator undef_generator.c
(GLOBIGNORE="extra.c:launcher.c:undef.c:undef_generator.c" ; cat *.c | ./undef_generator undef_black_list.txt > undef.c)
make halley -j
