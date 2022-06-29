#ifndef STATUSLIST_H

#define STATUSLIST_H

typedef struct {
    pid_t pid;
    pid_t pgid;
    char * status;
    char * prog;
} Status;

typedef struct statuslist {
    Status head;
    struct statuslist *tail;
} StatusList;

StatusList * statuslist_append(Status head, StatusList * tail);
void statuslist_delete(StatusList ** head_el, Status key);
void statuslist_print(StatusList * head_el);

#endif /* end of include guard: STATUSLIST_H */
