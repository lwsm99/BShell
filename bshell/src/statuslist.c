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
    lst->head.prog = strdup(element.prog);
    lst->tail=tail;
    return lst;
}

void statuslist_print(StatusList * head_el) {
    if(head_el == NULL) {
        printf("\n%6s%6s%12s%6s\n", "PID", "PGID", "STATUS", "PROG");
        printf(" ----- ----- ----------- -----\n");
        return;
    }
    StatusList * lst = head_el;
    printf("\n%6s%6s\t%s\t%6s\n", "PID", "PGID", "STATUS", "PROG");
    while(lst != NULL) {
        if(lst->head.running) {
            printf("%6d%6d%10s%6s\n", lst->head.pid, lst->head.pgid, "running", lst->head.prog);
        }
        else if(WIFEXITED(lst->head.status)) {
            printf("%6d%6d\texit(%d)%6s\n", lst->head.pid, lst->head.pgid, WEXITSTATUS(lst->head.status), lst->head.prog); 
        }
        else if(WIFSIGNALED(lst->head.status)) {
            printf("%6d%6d\tsignal(%d)%6s\n", lst->head.pid, lst->head.pgid, WTERMSIG(lst->head.status), lst->head.prog); 
        }
        else {
            /* Irgendwas anderes ist mit dem child passiert */
            lst->head.status = -1;
            fprintf(stderr, "Unknown exit type in pid [%d] with status %d\n", lst->head.pid, lst->head.status);
        } 
        lst = lst->tail;
    }
}