#include <unistd.h>

int main(void)
{
    char    buffer[1024 + 1];
    ssize_t n;

    n = 1024;
    while (n > 0)
    {
        n = read(0, buffer, 1024);
        //buffer[n] = '\n';
        write(1, buffer, n);
        write(1, "\n", 1);
    }
    
}