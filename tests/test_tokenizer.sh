#!/bin/zsh
libft_path="../libft"
tests=("The quick brown fox jumps over the lazy dog" \
	"'test' 'xx'" \
	"te'st'" \
	"'te*st'" \
	"te*st" \
	" cat file | grep test" \
	"test\ lol zobzob" \
	"test\\lol zobzob" \
	"'single quotes'" \
	"'single q' test pt'dr'" \
	"ls *" \
	"\"test\""
	"\$TERM is your terminal emulator" \
	"\"\$TERM is your terminal emulator\"" \
	"\"quo\"'ted'\ text" \
	"'*************'"
	"\"test\"\$TERM" \
	"\"test")
source_folder="../src"
include_folder="../includes"

set -e
echo testing tokenizer:
echo
echo
clang -Wall -Werror -Wextra -g $source_folder/tokenizer.c $source_folder/ft_getenv.c $source_folder/tokenizer_utils.c $source_folder/methods.c src/main_tokenizer.c $source_folder/wildcard.c -I$include_folder -I$libft_path -L$libft_path -lft
for elem in $tests; do
	echo testing $elem ':'
	./a.out $elem
done
rm a.out
