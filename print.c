#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char    buffer[1024 + 1];
	ssize_t	n;
	ssize_t	i;

	n = 1024;
	while (n == 1024)
	{
		n = read(0, buffer, 1024);
		i = -1;
		while (++i <= n)
			printf("\\x%.2x", buffer[i]);
		printf("\n");
	}
	return (0);
}