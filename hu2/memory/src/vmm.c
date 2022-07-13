#include "vmm.h"
#include "output_utility.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

/*** DEFINES ***/
#define PT_SIZE 256
#define P_SIZE 256
#define TLB_SIZE 16
#define F_SIZE 256
#define F_COUNT 64
#define PHY_MEM_SIZE F_COUNT * F_SIZE


/*** GLOBAL VARIABLES ***/
char phy_mem[PHY_MEM_SIZE];


/*** METHODS ***/

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
    
    // Variables
    int virtual_address;
    int physical_address;
    char * value;
    bool tlb_hit = false;
    bool pt_hit = false;

    char *line = NULL;
    size_t length = 0;
    int read;

    Entry * pt[PT_SIZE];
    Entry * tlb[TLB_SIZE];
    int victim_page = 0;


    // Read Backing Store
    char * backing = mmap(0, PT_SIZE * P_SIZE, PROT_READ, MAP_PRIVATE, fd_backing, 0);

    // Initialize Page Table & TLB
    for(int i = 0; i < PT_SIZE; i++) {
        pt[i] = NULL;
    }

    for(int i = 0; i < TLB_SIZE; i++) {
        tlb[i] = NULL;
    }

    while ((read = getline(&line, &length, fd_addresses)) != -1) {
        stats.total_memory_accesses++;

        // Read Address Input
        int page_number = (atoi(line) & 0x0000FF00) >> 8;
        int offset = (atoi(line) & 0x000000FF);

        // Initialize Entry
        Entry * entry = malloc(sizeof(Entry *));
        entry->pn = page_number;

        // Check if pagenumber is in TLB
        
        // TLB Hit
        if((entry->fn = check_tlb) != -1) {
            stats.tlb_hits++;
            tlb_hit = true;
            
        }
        // TLB miss
        else {
            // Check if pagenumber is in PT

            // Pagetable Hit
            if((entry->fn = check_pt) != -1) {
                stats.pagetable_hits++;
                pt_hit = true;
            }
            // Page Fault 
            else {

                // FIFO for victim page
                if(victim_page < PT_SIZE) {
                    entry->pn = victim_page;
                    victim_page++;
                }
                else {
                    victim_page = 0;
                }

                // Copy Backingstore Data into physical memory

                memcpy(phy_mem[entry->fn * F_SIZE], backing + (entry->pn * P_SIZE), P_SIZE);
            }
        }

        value = phy_mem[entry->fn * F_SIZE + offset];

        print_access_results(virtual_address, physical_address, value, tlb_hit, pt_hit);
    }

    return stats;
}

int check_tlb(int pn) {

    // TODO: Implement TLB

    // TLB Hit:
    // return tlb->fn;

    // TLB Miss:
    return -1;
}

int check_pt(int pn) {

    // TODO: Implement PT checker

    // Pagetable Hit:
    // return pt->fn;

    // Page Fault:
    return -1;
}
