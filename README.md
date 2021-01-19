# Neon-Genesis-Evanshellion
A cruel anshell thesis

## Test framework

`run_all_tests.sh`
runs all the tests and checks the norme

### Options

`-n [none/full]` none will not check the norme, full will display all informations about errors

`-f <file>` runs the specified test file

compile termcaps getter
`clang -g get_term_line.c termcaps.c cursor.c termcaps_utils.c ../tests/src/main_termcaps.c -L../libft -lft -I../includes -I../libft -lncursesclang -g get_term_line.c termcaps.c cursor.c termcaps_utils.c ../tests/src/main_termcaps.c -L../libft -lft -I../includes -I../libft -lncurses`
