#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "statuslist.h"
#include "debug.h"


StatusList * statuslist_append(Status element, StatusList * tail){
    /*
     * exchange only the list itself
     *
     */
    StatusList * lst = malloc(sizeof(StatusList));
    lst->head=element;
    lst->tail=tail;
    return lst;
}

void statuslist_delete(StatusList ** head_el, Status key){
    // Store head node
    StatusList * temp = *head_el, *prev;
 
    // If head node itself holds the key to be deleted
    if (temp != NULL && &temp->head == &key) {
        head_el = temp->tail; // Changed head
        free(temp); // free old head
        return;
    }
 
    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && &temp->head != &key) {
        prev = temp;
        temp = temp->tail;
    }
 
    // If key was not present in linked list
    if (temp == NULL)
        return;
 
    // Unlink the node from linked list
    prev->tail = temp->tail;
 
    free(temp); // Free memory
}

void statuslist_print(StatusList * head_el) {
    StatusList * lst = head_el;
    printf("PID  PGID STATUS\tPROG");
    while(lst != NULL) {
        printf("%d  %d %s\t%s", lst->head.pid, lst->head.pgid, lst->head.status, lst->head.prog);
        lst = lst->tail;
    }
}