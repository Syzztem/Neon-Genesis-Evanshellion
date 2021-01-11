#!/bin/zsh
libft_path="../libft"
tests=("*" "a*" "*b" "a*e" "a*c*e" "*e" "*ab" "xx/*" "*/*" "xx/t*t" "*x/test/*l")
include_folder="../includes"

set -e
echo testing wildcard:
echo
echo
clang -Wall -Werror -Wextra ../src/wildcard.c src/main_wildcard.c -I$include_folder -L$libft_path -I$libft_path -lft
for elem in $tests; do
	echo testing $elem :
	echo
	./a.out $elem
done
rm a.out
