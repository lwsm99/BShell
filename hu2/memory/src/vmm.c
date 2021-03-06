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

int frame_counter = 0;
int tlb_counter = 0;
int pt_counter = 0;

int victim_frame = 0;
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
        if(victim_tlb >= TLB_SIZE) victim_tlb = 0;
        //Replace the victim in tlb with the entry
        tlb[victim_tlb] = entry;
        victim_tlb++;
    }
}
void addToPT(Entry *entry) {
    for(int i = 0; i < tlb_counter; i++) {
        if(tlb[i]->fn == entry->fn) {
            // 1 2 3 _ 5 6 ... -> 1 2 3 5 6 ...
            for(int j = i; j < tlb_counter - 1; j++) {
                tlb[j] = tlb[j + 1];
            }
            tlb_counter--;
            break;
        }
    }
    //Add first 256 entries to pt
    if(pt_counter < PT_SIZE) {
        pt[pt_counter] = entry;
        pt_counter++;
    }
    //After 256 entries we land here
    else {
        if(victim_pt >= PT_SIZE) victim_pt = 0;
        //Replace the victim in pt with the entry
        pt[victim_pt] = entry;
        victim_pt++;
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
        entry->fn = -1;

        // Check if pagenumber is in TLB
        
        // TLB Hit
        if((entry->fn = check_tlb(entry->pn)) != -1) {
            stats.tlb_hits++;
            stats.pagetable_hits++;
            tlb_hit = true;
            pt_hit = true;
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

                char buffer[F_SIZE];

                //set where to read in backing
                fseek(fd_backing, entry->pn * F_SIZE, SEEK_SET);
                fread(buffer, sizeof(char), F_SIZE, fd_backing);

                // Copy Backingstore Data into physical memory
                if(frame_counter < F_COUNT) {
                    for(int i = frame_counter * F_SIZE, j = 0; i < (frame_counter * F_SIZE) + F_SIZE; i++, j++) {
                        phy_mem[i] = buffer[j];
                    }
                    entry->fn = frame_counter;
                    frame_counter++;
                } else {
                    if(victim_frame >= F_COUNT) victim_frame = 0;
                    for(int i = victim_frame * F_SIZE, j = 0; i < (victim_frame * F_SIZE) + F_SIZE; i++, j++) {
                        phy_mem[i] = buffer[j];
                    }
                    entry->fn = victim_frame;
                    
                    //remove from pt and tlb when old victim_frame is used
                    for(int i = 0; i < tlb_counter; i++) {
                        if(tlb[i]->fn == entry->fn) {
                            tlb[i]->fn = -1;
                            tlb[i]->pn = -1;
                        }
                    }
                    for(int i = 0; i < pt_counter; i++) {
                        if(pt[i]->fn == entry->fn) {
                            pt[i]->fn = -1;
                            pt[i]->pn = -1;
                        }
                    }

                    victim_frame++;
                }

                //Add entry or replace victim with entry in tlb and pt
                addToPT(entry);
                addToTLB(entry);
            }
        }

        physical_address = entry->fn << 8 | offset;
        value = phy_mem[entry->fn * F_SIZE + offset];

        print_access_results(virtual_address, physical_address, value, tlb_hit, pt_hit);
        
        tlb_hit = pt_hit = false;
    }
    return stats;
}