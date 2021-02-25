#include "parser.h"

int main(int ac, char **av)
{
	iter_argv(av + 1, print_exec_path);
	return (0);
}
