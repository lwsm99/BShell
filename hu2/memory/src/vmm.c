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
Entry * tlb[TLB_SIZE];
Entry * pt[PT_SIZE];
int tlb_counter = 0;
int pt_counter = 0;
int victim_tlb = 0;
int victim_pt = 0;


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

int check_tlb(int pn) {
    // TLB Hit:
    for(int i = 0; i < tlb_counter; i++) {
        if(tlb[i]->pn == pn) {
            return tlb[i]->fn;
        }
    }
    // TLB Miss:
    return -1;
}

int check_pt(int pn) {
    // Pagetable Hit:
    for(int i = 0; i < pt_counter; i++) {
        if(pt[i]->pn == pn) {
            return pt[i]->fn;
        }
    }

    // Page Fault:
    return -1;
}

void addToTLB(Entry *entry) {
    //Add first 16 entries to tlb
    if(tlb_counter < TLB_SIZE) {
        tlb[tlb_counter] = entry;
        tlb_counter++;
    }
    //After 16 entries we land here
    else {
        //Replace the victim in tlb with the entry
        tlb[victim_tlb] = entry;
        //Count up the victim until it hits 15, set back to 0 [FIFO]
        if(victim_tlb < TLB_SIZE) {
            victim_tlb++;
        } else victim_tlb = 0;
    }
}
void addToPT(Entry *entry) {
    //Add first 256 entries to pt
    if(pt_counter < PT_SIZE) {
        pt[pt_counter] = entry;
        pt_counter++;
    }
    //After 256 entries we land here
    else {
        //Replace the victim in pt with the entry
        pt[victim_pt] = entry;
        //Count up the victim until it hits 255, set back to 0 [FIFO]
        if(victim_pt < PT_SIZE) {
            victim_pt++;
        } else victim_pt = 0;
    }
}

Statistics simulate_virtual_memory_accesses(FILE *fd_addresses, FILE *fd_backing) {

    // Initialize statistics
    Statistics stats;
    statistics_initialize(&stats);
    
    // Variables
    int virtual_address;
    int physical_address;
    unsigned char value;
    bool tlb_hit = false;
    bool pt_hit = false;

    char *line = NULL;
    size_t length = 0;
    int read;

    int victim_page = 0;


    // Read Backing Store
    char * backing = mmap(0, PT_SIZE * P_SIZE, PROT_READ, MAP_PRIVATE, fd_backing, 0);
    
    // Initialize Page Table & TLB
    for(int i = 0; i < TLB_SIZE; i++) {
        tlb[i] = NULL;
    }

    for(int i = 0; i < PT_SIZE; i++) {
        pt[i] = NULL;
    }

    while ((read = getline(&line, &length, fd_addresses)) != -1) {
        stats.total_memory_accesses++;

        // Read Address Input
        virtual_address = atoi(line);
        int page_number = (atoi(line) & 0x0000FF00) >> 8;
        int offset = (atoi(line) & 0x000000FF);

        // Initialize Entry
        Entry * entry = malloc(sizeof(Entry *));
        entry->pn = page_number;
        //TODO: Set entry->fn

        // Check if pagenumber is in TLB
        
        // TLB Hit
        if((entry->fn = check_tlb(entry->pn)) != -1) {
            stats.tlb_hits++;
            tlb_hit = true;
            
        }
        // TLB miss
        else {
            // Check if pagenumber is in PT

            // Pagetable Hit
            if((entry->fn = check_pt(entry->pn)) != -1) {
                stats.pagetable_hits++;
                pt_hit = true;
                addToTLB(entry);
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
                //memcpy(phy_mem[entry->fn * F_SIZE], backing + (entry->pn * P_SIZE), P_SIZE);

                /* TODO: Add entry or replace victim with entry in tlb and pt */
                //addToTLB(entry);
                //adToPT(entry);
            }
        }

        //value = phy_mem[entry->fn * F_SIZE + offset];
        physical_address = 10;
        value = (unsigned char)10;

        print_access_results(virtual_address, physical_address, value, tlb_hit, pt_hit);
        tlb_hit = pt_hit = false;
    }
    printf("%d\n", F_SIZE * F_COUNT);
    return stats;
}