#include <stdio.h>
#include <stdlib.h>
#define PAGE_ENTRIES 256

int page_table[PAGE_ENTRIES];

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;
    const char *filename = argv[1];

    FILE *addresses = fopen(filename, "r");
    FILE *memory = fopen("BACKING_STORE.bin", "r");

    if (!addresses)
        return 1;

    unsigned int number;
    int counter = 0;

    for (int i = 0; i < PAGE_ENTRIES; i++)
    {
        i[page_table] = -1;
    }

    while (fscanf(addresses, "%d,", &number) > 0)
    {
        int page_number = number >> 8;
        if (page_table[page_number] == -1)
        {
            page_table[page_number] = counter;
            counter++;
        }

        int physical = number & 0xff | (page_table[page_number] << 8);

        fseek(memory, physical, SEEK_SET);
        char read = 0;
        fread(&read, sizeof(read), 1, memory);
        read = read & 0xff;
        printf("Virtual address: %d Physical address: %d Value: %X, %d\n", number, physical, read, read);
    }

    fclose(addresses);

    return 0;
}





