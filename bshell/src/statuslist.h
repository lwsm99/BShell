#ifndef STATUSLIST_H

#define STATUSLIST_H

typedef struct statuslist {
    void *head;
    struct statusList *tail;
} StatusList;

StatusList * list_append(void * head, StatusList * tail);
StatusList * list_delete(void * head, StatusList * tail);

#endif /* end of include guard: STATUSLIST_H */
