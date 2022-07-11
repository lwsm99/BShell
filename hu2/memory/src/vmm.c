#include "vmm.h"
#include "output_utility.h"

#include <stdio.h>
char * pagetable;
/**
 * Initialized a statistics object to zero.
 * @param stats A pointer to an uninitialized statistics object.
 */
static void statistics_initialize(Statistics *stats) {
    stats->tlb_hits = 0;
    stats->pagetable_hits = 0;
    stats->total_memory_accesses = 0;
}

Statistics simulate_virtual_memory_accesses(FILE *fd_addresses, FILE *fd_backing) {
    // Initialize statistics
    Statistics stats;
    statistics_initialize(&stats);
    int address;
     char *line;
    int len;
    create_pagetable();
    /*
    while(read = getline(&line, &len, fp) != -1){
      address = atoi(line);
      get_physical_address(address);
    */
    // TODO: Implement your solution

    return stats;
}

//translates the logical into physical address.
int translate_address( int address){
int page_number = (address & 0x000FF00) >> 8;
int offset = (address & 0x000000FF);
printf("%d,%d\n", page_number, offset);
}

void create_pagetable(){
    // size of pageTable is 256 Bytes(2^8)
    int size = 256;
    pagetable = malloc(256);
}
