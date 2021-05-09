#!/bin/bash

abspath() {
  # $1 : relative filename
  if [ -d "${1%/*}" ]; then
    echo "$(cd ${1%/*}; pwd)/${1##*/}"
  fi
}
cmp_shell()
{
	FUNC_RET=0;
	MY_OUTFILE=/tmp/my_outfile;
	TST_OUTFILE=/tmp/tst_outfile;
	
	echo "$@" | exec -a "$SHELL_TEST_NAME" $MY_SHELL > $MY_OUTFILE  2> /dev/null;
	MY_RET=$?;
	echo "$@" | exec -a "$SHELL_TEST_NAME" $TST_SHELL > $TST_OUTFILE 2> /dev/null;
	TST_RET=$?;
	
	if [ "$(uname)" = "Linux" ];then
		DIFF_COLOR='--color=always'
	fi

	if [ "$MY_RET" != "$TST_RET" ];then
		echo "[ERROR]: Return values differs.";
		printf "CMD: %s\n" "$@"
		printf "\t%s\n" "$MY_RET <- $MY_SHELL $@";
		printf "\t%s\n" "$TST_RET <- $TST_SHELL $@";
		FUNC_RET=1;
	fi

	if ! diff "$MY_OUTFILE" "$TST_OUTFILE" > /dev/null;then				   			
		echo "[ERROR]: Output differs.";
		printf "CMD: %s\n" "$@"
		printf "%s                                                          | %s\n" "($MY_SHELL)" "($TST_SHELL)"
		FUNC_RET=1;
		diff -y "$MY_OUTFILE" "$TST_OUTFILE" $DIFF_COLOR
	elif [ "$VERBOSE" = on ];then
		printf '\n$> %s :\n\n%s\n\n$> %s :\n\n%s\n\n----------\n'  "$MY_SHELL"  "$(cat $MY_OUTFILE)" "$TST_SHELL" "$(cat $TST_OUTFILE)"
	fi
	#rm "$MY_OUTFILE" "$TST_OUTFILE";
	if [ $FUNC_RET != 0 ];then
		RET_VALUE=$FUNC_RET
	fi
	return $FUNC_RET;
}

interactive()
{
	while IFS= read -e -p '> ' line; do
		cmp_shell $line;
	done
}

unit_multiline()
{
	cmp_shell '
/bin/echo 1
/bin/echo 2
/bin/echo 3
/bin/echo 4
/bin/echo 5
/bin/echo 6
/bin/echo 7
/bin/echo 8
/bin/echo 9
/bin/echo 10'
	cmp_shell '
/bin/echo "1
2
3
4
5
6
7
8
9
10"'
	cmp_shell "
/bin/echo '1
2
3
4
5
6
7
8
9
10'"

	cmp_shell "
/bin/echo '1
2
3
4
5
6
7
8
9
10' | grep 3"

	cmp_shell "
/bin/echo '1
2
bonjour
4
5
6
bonuit
8
9
10' | grep bon"

}

unit_no_arg()
{
	cmp_shell 'ls'
	cmp_shell 'pwd'
	cmp_shell '/bin/echo'
	cmp_shell 'uname'
	cmp_shell 'arch'
	cmp_shell "$EXE_FOLDER/no_arg.sh"

}

unit_arg()
{
	cmp_shell /bin/echo Hello World
	cmp_shell ls ..
	cmp_shell uname -a
}

unit_parsing()
{
	cmp_shell 'export A=p;export B=w;$A$B"d"'
	cmp_shell "/bin/echo '\'"
	cmp_shell '/bin/echo \\'
	cmp_shell '/bin/echo au feeling'
	cmp_shell '/bin/echo "au feeling"'
	cmp_shell '/bin/echo \$PATH'
	cmp_shell '/bin/echo a;/bin/echo b;/bin/echo c;/bin/echo d;/bin/echo e;/bin/echo f;/bin/echo g;/bin/echo h;/bin/echo i;/bin/echo j;/bin/echo k;/bin/echo l;/bin/echo m;/bin/echo n;/bin/echo o;/bin/echo p;/bin/echo q;/bin/echo r;/bin/echo s;/bin/echo t;/bin/echo u;/bin/echo v;/bin/echo w;/bin/echo x;/bin/echo y;/bin/echo z;/bin/echo A;/bin/echo B;/bin/echo C;/bin/echo D;/bin/echo E;/bin/echo F'
	cmp_shell '/bin/echo 0;/bin/echo 1;/bin/echo 2;/bin/echo 3;/bin/echo 4;/bin/echo 5;/bin/echo 6;/bin/echo 7;/bin/echo 8;/bin/echo 9;/bin/echo 10;/bin/echo 11;/bin/echo 12;/bin/echo 13;/bin/echo 14;/bin/echo 15;/bin/echo 16;/bin/echo 17;/bin/echo 18;/bin/echo 19;/bin/echo 20'
}

unit_pipes_env()
{
	cmp_shell 'printf "caca\nprout" | grep prout'
	cmp_shell 'printf "caca\nprout" | grep caca'
	cmp_shell 'printf "bonjour\nsalut\nbonuit" | grep bon'
	cmp_shell 'printf "bonjour\nsalut\nbonuit" | grep bon | grep nuit'
	cmp_shell 'printf "bonjour\nsalut" | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut '
	cmp_shell 'export H=hello;/bin/echo hello | grep hello | grep $H '
	cmp_shell 'export H=hello;/bin/echo hello | grep hello | grep $H | grep hello | grep $H | grep hello | grep $H | grep hello | grep $H | grep hello | grep $H | grep hello | grep $H | grep hello | grep $H | grep hello | grep $H | grep hello | grep $H'
	cmp_shell '/bin/echo \| | grep \|'
	cmp_shell '/bin/echo \|\|\|\|\| | grep \|'
}

unit_pipes()
{
	cmp_shell 'printf "caca\nprout" | grep prout'
	cmp_shell 'printf "caca\nprout" | grep caca'
	cmp_shell 'printf "bonjour\nsalut\nbonuit" | grep bon'
	cmp_shell 'printf "bonjour\nsalut\nbonuit" | grep bon | grep nuit'
	cmp_shell 'printf "bonjour\nsalut" | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut '
	cmp_shell '/bin/echo \| | grep \|'
	cmp_shell '/bin/echo \|\|\|\|\| | grep \|'
	cmp_shell '/bin/echo hello|grep -o he'
	cmp_shell '/bin/echo hello|grep -o he|grep -o e'
	cmp_shell 'printf "bonjour\nsalut"|grep salut|grep salut|grep salut|grep salut|grep salut|grep salut|grep salut|grep salut|grep salut| grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut | grep salut '
}

unit_echo()
{
	cmp_shell 'echo'
	cmp_shell 'echo hello'
	cmp_shell 'echo'
	cmp_shell 'echo -n hello'
	cmp_shell 'echo -n hello world'
	cmp_shell 'echo -n'
	cmp_shell 'echo -n -n'
	cmp_shell 'echo -n n -n'
	cmp_shell 'echo -n -m'
	cmp_shell 'echo -nv'
	cmp_shell 'echo --help'
	cmp_shell 'echo "hello world"'
	cmp_shell 'echo "hello    " "       world" hi hey'
}

unit_pwd()
{
	cmp_shell "pwd"
	cmp_shell "pwd .."
	#undefined #cmp_shell 'mkdir /tmp/my_dir;cd /tmp/my_dir ;mkdir 1;mkdir 1/2; mkdir 1/2/3;cd 1/2/3;pwd; rm -rf ../../../1;pwd;echo $?'
}

unit_exit()
{
	cmp_shell "exit"
	cmp_shell "exit 53"
	cmp_shell '/bin/echo "exit 53;" | ls ; /bin/echo $?'
}

unit_env_vars()
{
	cmp_shell 'echo $PATH'
	cmp_shell 'echo $SHELL'
	#cmp_shell 'echo $0'
	cmp_shell '/bin/pwd ; echo $?'
	cmp_shell 'ee ; echo $?'
	#undefined#cmp_shell '/bin/echo $$'
}

unit_env()
{
	cmp_shell 'env eee'
	cmp_shell 'env abc abc'
}

unit_builtins_no_arg()
{
	cmp_shell 'echo'
	cmp_shell "cd"
	cmp_shell 'pwd'
	cmp_shell 'unset'
	cmp_shell 'exit'
}

unit_quotes()
{
	cmp_shell '/bin/echo "'hi'"'
	cmp_shell "/bin/echo '"hi"'"
	cmp_shell "/bin/echo '"'"'"'"'"'"''"'"'"'"'"'"'"
	cmp_shell "/bin/echo ''''''''''''''''"
	cmp_shell "/bin/echo "''''''''''''''''" "
	cmp_shell "/bin/echo \"''''''''''''''''\""
	cmp_shell "/bin/echo \'hello world\'"
	cmp_shell '/bin/echo "" "" "" "" " "'
	cmp_shell '/bin/echo "\\"'
	cmp_shell '/bin/echo "    \\"'
	cmp_shell '/bin/echo """""" "" "" "" "" """" ""'
	cmp_shell '/bin/echo a"b"c" "d"    "e'
}

unit_argv_zero()
{
	cmp_shell '/bin/echo $0'
}

unit_semicolons()
{
	#cmp_shell ';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;'
	#cmp_shell '; ; ; ; ; ;'
	cmp_shell '/bin/echo a; /bin/echo b; /bin/echo c'
	cmp_shell '/bin/echo "a;echo b;pwd" '
	cmp_shell '/bin/echo hello\;echo world'
	cmp_shell '/bin/echo "hello \;echo world"'
	cmp_shell '/bin/echo hello;echo ";hello\;;";'
}

unit_error_semicolons_simple()
{
	cmp_shell ';'
	cmp_shell '; ;'
	cmp_shell '; ; ;'
	cmp_shell '; ; ; ; ;'
	cmp_shell ';;;;'
	cmp_shell ';;'
	cmp_shell ' ;; '
	cmp_shell ';; ;; ;;; ;; ; ;; ; ;;; ; ;;;'
	cmp_shell ';;;;'
}

unit_return()
{
	cmp_shell 'eee ; /bin/echo $?'
	cmp_shell '/bin/echo $?'
}

unit_redirect_replace()
{
	TST_DIR=/tmp/shell_test
	mkdir -p $TST_DIR
	pushd . > /dev/null
	cd $TST_DIR

	cmp_shell '/bin/echo hello world > 1; ls ; cat 1'
	cmp_shell 'printf h> 2; ls ; cat 2'
	printf "hello\nworld\ngood\nmorning\nworld" > test_file
	cmp_shell 'rm -f test_output; cat test_file; grep world < test_file > test_output   ; cat test_file'
	cmp_shell 'rm -f test_output; cat test_file; grep world < test_file > test_output; grep world < test_file > test_output  ; cat test_file'
	popd > /dev/null
	rm -rf $TST_DIR

	mkdir -p $TST_DIR
	pushd . > /dev/null
	cd $TST_DIR

	cmp_shell '/bin/echo hello world > 1; ls ; cat 1'
	cmp_shell '> 2 printf h; ls ; cat 2'
	printf "hello\nworld\ngood\nmorning\nworld" > test_file
	cmp_shell 'rm -f test_output; cat test_file; < test_file grep world> test_output   ; cat test_file'
	cmp_shell 'rm -f test_output; cat test_file; < test_file grep world> test_output; grep world < test_file > test_output  ; cat test_file'
	popd > /dev/null
	rm -rf $TST_DIR
}

unit_redirect_append()
{
	TST_DIR=/tmp/shell_test
	mkdir -p $TST_DIR
	pushd . > /dev/null
	cd $TST_DIR

	cmp_shell '/bin/echo hello world >> 1 ; ls ; cat 1 ; rm 1'
	cmp_shell 'printf a >> 2 ; ls ; cat 2 ; rm 2'
	cmp_shell 'printf b > 3 ; ls >> 3 ; cat 3'
	cmp_shell 'printf c > 4 ; ls >> 4 ; printf eee >> 4 ; echo ";" >> 4 ; cat 4'
	cmp_shell 'printf d > 5 ; ls >> 5 ; printf eee >> 5 ; echo ";" > 5 ; cat 5'


	printf "hello\nworld\ngood\nmorning\nworld" > test_file
	cmp_shell 'rm -f test_output; cat test_file; grep world < test_file >> test_output   ; cat test_file'
	printf "hello\nworld\ngood\nmorning\nworld" > test_file
	cmp_shell 'rm -f test_output; cat test_file; grep world < test_file >> test_output; grep world < test_file > test_output  ; cat test_file'
	popd > /dev/null
	rm -rf $TST_DIR
	
	mkdir -p $TST_DIR
	pushd . > /dev/null
	cd $TST_DIR

	cmp_shell '/bin/echo hello world >> 1 ; ls ; cat 1 ; rm 1'
	cmp_shell '>> 2 printf; ls ; cat 2 ; rm 2'
	cmp_shell '> 3 printf b; ls >> 3 ; cat 3'
	cmp_shell 'printf c > 4 ; ls >> 4 ; printf eee >> 4 ; echo ";" >> 4 ; cat 4'
	cmp_shell 'printf d > 5 ; ls >> 5 ; printf eee >> 5 ; echo ";" > 5 ; cat 5'


	printf "hello\nworld\ngood\nmorning\nworld" > test_file
	cmp_shell 'rm -f test_output; cat test_file; grep world < test_file >> test_output   ; cat test_file'
	printf "hello\nworld\ngood\nmorning\nworld" > test_file
	cmp_shell 'rm -f test_output; cat test_file; grep world < test_file >> test_output; grep world < test_file > test_output  ; cat test_file'
	popd > /dev/null
	rm -rf $TST_DIR
}

unit_priorities()
{
	cmp_shell 'true && echo hello'
	cmp_shell 'true && echo hello ; echo world'
	cmp_shell 'echo hello ; echo world'
	cmp_shell 'true || echo hello'
	cmp_shell 'false || echo hello'
	cmp_shell 'false && echo hello'
	cmp_shell 'true && echo hello ; false || echo hello'
	cmp_shell 'true && echo hello ; true || echo hello'
	cmp_shell 'echo hello && echo world'
	cmp_shell 'echo hello || echo world'
}

unit_tokenizer()
{
	cmp_shell 'echo abc|grep abc'
	cmp_shell 'echo abc;echo abc|grep abc'
	cmp_shell "few';"
}

unit_parenthesis()
{
	cmp_shell '(/bin/echo hello)'
	cmp_shell '(echo hello)'
	cmp_shell '(echo hello | grep hello)'
	cmp_shell '(echo hello | grep -o he)'
	cmp_shell '(echo hello | grep -o hell | grep -p he)'
	cmp_shell 'echo hello ; (echo arg | ls)'
	cmp_shell 'printf "hello\nworld\m" | (grep -o hello | grep -o lo)'
	cmp_shell 'printf "hello\nworld\m" | (grep -o hello | (grep -o lo | grep -o l))'
	cmp_shell 'printf "hello\nworld\m" | ( grep -o hello | (grep -o lo | grep -o l) )'
	cmp_shell 'printf "hello\nworld\m" | ( grep -o hello | ( grep -o lo | grep -o l ) )'
	cmp_shell 'printf "hello\nworld\m"|( grep -o hello | (grep -o lo | grep -o l) )'
	cmp_shell '(echo hello ; export DFG=fuckme); echo $DFG'
	cmp_shell '                   (echo hello; echo world)'
	cmp_shell '                     (echo hello ; echo world)                                '
	#cmp_shell 'ls(w)' #error case
}

unit_backslashs()
{
	cmp_shell '/bin/echo \\'
	cmp_shell "/bin/echo '\\\\'"
	cmp_shell "/bin/echo '\\\\\\'"
	cmp_shell '/bin/echo "\\"'
	cmp_shell '/bin/echo "\\\\"'
	cmp_shell '/bin/echo "\""'
	cmp_shell "/bin/echo '\\'"
	cmp_shell '/bin/echo a\ \ b'
	cmp_shell '/bin/echo "\$"'
	cmp_shell '/bin/echo \$'
	cmp_shell "/bin/echo '\\$'"
	cmp_shell "/bin/echo \"\\\\\'\\\"\\$\""
	cmp_shell 'echo \\\\\\""'
}

unit_escape_var()
{
	export X='\"\"'
	cmp_shell 'echo $X'
	cmp_shell 'echo "$X"'
	export X="\'\'"
	cmp_shell 'echo $X'
	cmp_shell 'echo "$X"'
	export X="\\"
	cmp_shell 'echo $X'
	cmp_shell 'echo "$X"'
	export X='\\\\"'
	cmp_shell 'echo $X'
	cmp_shell 'echo "$X"'
	cmp_shell 'echo "$X""$X"'
	cmp_shell "echo '\$X\"\"\$X\"'"

	cmp_shell 'echo $'
	cmp_shell 'echo \$'
	cmp_shell 'echo \\$'
	cmp_shell 'echo "$"'
	cmp_shell 'echo "$ "'
	cmp_shell 'echo " $ "'
	cmp_shell 'echo "    $    "'
	cmp_shell 'echo $\"'
	cmp_shell 'echo $\\'
	cmp_shell 'echo $%'
	cmp_shell 'echo $/'

	export A="hello   world"
	cmp_shell 'echo $A'
	cmp_shell 'echo "$A"'
}

unit_here_doc()
{
	cmp_shell 'cat <<EOF
hello
world
!
EOF'
	cmp_shell 'cat<<EOF
hello
my
world
!
EOF
'
	cmp_shell '<<EOF cat
hello
my
world
!
EOF
'
	cmp_shell "<<'EOF' cat
hello
myyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy
woooooooooooooooooooooooooooooooooooooooooorlllllllld
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
EOF
"
	cmp_shell '<<EOF cat
EOF
'
}

main()
{
	MY_SHELL=$(abspath ../minishell)
	TST_SHELL='bash --posix'
	SHELL_TEST_NAME='myshell'
	INTERACTIVE="off"
	VERBOSE="off";
	ALL_ARGS="$@"
	TEST_FOLDER=`abspath ./testfolder`
	EXE_FOLDER=`abspath ./executables`
	TRACE_FILE=`abspath ./trace`

	cd "$TEST_FOLDER"
	echo > $TRACE_FILE
	for arg in "$@";
	do
		if [ "$arg" = '-i' ];then
			INTERACTIVE="on";
		fi
		if [ "$arg" = '-v' ];then
			VERBOSE="on";
		fi
		if [ "$arg" = 'unit_all' ];then
			ALL_ARGS="unit_escape_var unit_multiline unit_parenthesis unit_backslashs unit_no_arg unit_arg unit_parsing unit_pipes_env unit_pipes unit_echo unit_pwd unit_exit unit_env_vars unit_builtins_no_arg unit_quotes unit_semicolons unit_return unit_redirect_replace unit_redirect_append"
		fi
	done

	if [ "$INTERACTIVE" = "on" ];then
		interactive;
	else
		for test in $ALL_ARGS;do
			if ! [ "$test" = "-v" ];then
				OUTPUT="$($test)";
				if [ $? == 0 ] && [ -z "$(echo "$OUTPUT" | grep '\[ERROR\]')" ];then
					printf '%-25s [OK]\n' "$test:" | tee -a $TRACE_FILE
				else
					printf '%-25s [KO]\n' "$test:" | tee -a $TRACE_FILE
				fi
				if [ "$VERBOSE" = "on" ];then
					printf "$test:\n%s\n" "$OUTPUT" | tee -a $TRACE_FILE
				else
					printf "$test:\n%s\n" "$OUTPUT" >> $TRACE_FILE
				fi
			fi
		done
	fi
}

make -C ../ --silent
main $@
