#include <stdio.h>

int main(int argc, char *argv[])
{
    char c;
    if (argc < 2)
        return 1;
    const char *filename = argv[1];

    FILE *addresses = fopen(filename, "r");

    if (!addresses)
        return 1;

    unsigned int number;
    while (fscanf(addresses, "%d,", &number) > 0)
    {
        printf("%X, %X, %X, %d\n", number, number >> 8, number & 0xff, number);
    }

    fclose(addresses);

    return 0;
}