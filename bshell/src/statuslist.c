#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "statuslist.h"
#include "debug.h"


StatusList * list_append(void * element, StatusList * tail){
    /*
     * exchange only the list itself
     *
     */
    StatusList * lst = malloc(sizeof(StatusList));
    lst->head=element;
    lst->tail=tail;
    return lst;
}

StatusList * list_delete(void * element, StatusList * tail){
    lst->head=element;
    lst->tail=tail;
    return lst;
}
