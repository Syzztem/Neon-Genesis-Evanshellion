#include <unistd.h>

int main(void)
{
	write(1, "\0 ", 2);
	return (0);
}
