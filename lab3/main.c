#include <stdio.h>
#include <stdlib.h>
#define PAGE_ENTRIES 256
#define BIN "BACKING_STORE.bin"
#define TLB_MAX 3

int page_table[PAGE_ENTRIES];

typedef struct tlb
{
    struct tlb *next;
    int page_number;
    int frame_number;
} tlb_t;

int consult_tlb(tlb_t *TLB, int page_number);
tlb_t *add_to_tlb(tlb_t *TLB, int page_number, int frame_number);
void print_tlb(tlb_t *TLB);

int main(int argc, char *argv[])
{

    FILE *addresses, *memory;
    tlb_t *TLB = NULL;
    unsigned int address, counter = 0;

    TLB = add_to_tlb(TLB, 10, 20);
    TLB = add_to_tlb(TLB, 30, 40);
    TLB = add_to_tlb(TLB, 50, 60);
    TLB = add_to_tlb(TLB, 13, 7);

    print_tlb(TLB);
    /* if (argc < 2 || !(addresses = fopen(argv[1], "r")))
        return 1;

    memory = fopen(BIN, "rb");

    for (int i = 0; i < PAGE_ENTRIES; i++)
        page_table[i] = -1;

    while (fscanf(addresses, "%d,", &address) > 0)
    {
        int page_number = address >> 8;
        frame_number = consult_tlb(TLB, page_number);
        if (frame_number == -1)
        {
            // tlb miss
            if (page_table[page_number] == -1)
                page_table[page_number] = counter++ << 8;
            // add to tlb?
        }

        int physical = address & 0xff | page_table[page_number];
        char read = 0;

        fseek(memory, address, SEEK_SET);
        fread(&read, sizeof(read), 1, memory);
        printf("Virtual address: %d Physical address: %d Value: %X, %d\n", address, physical, read, read);
    }

    fclose(addresses);

    return 0; */
}

int consult_tlb(tlb_t *TLB, int page_number)
{
    if (TLB == NULL)
        return -1;
    if (TLB->page_number == page_number)
        return TLB->frame_number;
    return consult_tlb(TLB->next, page_number);
}

void print_tlb(tlb_t *TLB)
{
    if (TLB == NULL)
    {
        printf("NULL\n");
        return;
    }
    printf("page: %d, frame: %d\n|\nV\n", TLB->page_number, TLB->frame_number);
    print_tlb(TLB->next);
}

int resize_tlb(tlb_t *TLB, int counter) {
    if (TLB->next == NULL && counter == TLB_MAX) {
        free(TLB);
        return counter;
    }
    return resize_tlb(TLB->next, counter++);

}

tlb_t *add_to_tlb(tlb_t *TLB, int page_number, int frame_number)
{

    tlb_t *new_entry = malloc(sizeof(tlb_t));
    new_entry->page_number = page_number;
    new_entry->frame_number = frame_number;
    new_entry->next = TLB;
    resize_tlb(new_entry, 0);
    return new_entry;
}