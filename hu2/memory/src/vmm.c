#include "vmm.h"
#include "output_utility.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    // TODO: Implement your solution

    char *line = NULL;
    size_t length = 0;
    int read;

    while ((read = getline(&line, &length, fd_addresses)) != -1) {
        int page_number = (atoi(line) & 0x0000FF00) >> 8;
        int offset = (atoi(line) & 0x000000FF);
    }

    return stats;
}
