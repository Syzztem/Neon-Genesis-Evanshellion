#!/bin/zsh

test_dir="tests"
test_files=("test_tokenizer.sh" "test_wildcard.sh")
libft_path="libft"
libft_files=`echo $libft_path/*.c $libft_path/*.h`
minishell_files=`echo src/*.c includes/*.h`

while getopts n:f: flag
do
	case $flag in
		n)
			norme_mode=${OPTARG};;
		f)
			test_files=("${OPTARG}");;
	esac
done
case $norme_mode in
	full)
		echo checking norme...
		norminette $minishell_files $libft_files | grep -B 1 Error
		;;
	none)
		;;
	*)
		echo checking norme...
		norme_error_count=`norminette $minishell_files $libft_files | grep Error | wc -l | sed "s/ //g"`
		if [ $norme_error_count -gt 0 ]; then
			echo You have $norme_error_count norme errors, run with \'-n full\' for more details
		fi
esac
set -e
echo compiling libft...
(cd $libft_path && make)
for file in $test_files; do
	echo run $file
	(cd $test_dir && ./$file)
done
