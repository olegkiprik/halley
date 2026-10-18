(GLOBIGNORE="extra.c:launcher.c:undef.c:undef_generator.c" ; cat *.c | ./undef_generator undef_black_list.txt > undef.c)
