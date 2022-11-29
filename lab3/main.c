#include <stdio.h>
#include <stdlib.h>
#define PAGE_ENTRIES 256
#define BIN "BACKING_STORE.bin"

int page_table[PAGE_ENTRIES];

int main(int argc, char *argv[])
{
    FILE *addresses, *memory;
    unsigned int address, counter = 0;

    if (argc < 2 || !(addresses = fopen(argv[1], "r")))
        return 1;

    memory = fopen(BIN, "rb");

    for (int i = 0; i < PAGE_ENTRIES; i++)
        page_table[i] = -1;

    while (fscanf(addresses, "%d,", &address) > 0)
    {
        int page_number = address >> 8;
        if (page_table[page_number] == -1)
            page_table[page_number] = counter++ << 8;

        int physical = address & 0xff | page_table[page_number];
        char read = 0;

        fseek(memory, physical, SEEK_SET);
        fread(&read, sizeof(read), 1, memory);
        printf("Virtual address: %d Physical address: %d Value: %X, %d\n", address, physical, read, read);
    }

    fclose(addresses);

    return 0;
}
