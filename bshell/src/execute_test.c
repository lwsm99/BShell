#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell.h"
#include "helper.h"
#include "command.h"
#include <signal.h>
#include <errno.h>
#include <pwd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "statuslist.h"
#include "debug.h"
#include "execute.h"
#include <sys/wait.h>
#include <sys/resource.h>
#include <setjmp.h>

#define READ 0
#define WRITE 1

/* do not modify this */
#ifndef NOLIBREADLINE
#include <readline/history.h>
#endif /* NOLIBREADLINE */

extern int shell_pid;
extern int fdtty;
int exit_status;

StatusList *statuslist;
pid_t signalPid = 0;
int sig = 0;

/* do not modify this */
#ifndef NOLIBREADLINE
static int builtin_hist(char ** command){

    register HIST_ENTRY **the_list;
    register int i;
    printf("--- History --- \n");

    the_list = history_list ();
    if (the_list)
        for (i = 0; the_list[i]; i++)
            printf ("%d: %s\n", i + history_base, the_list[i]->line);
    else {
        printf("history could not be found!\n");
    }

    printf("--------------- \n");
    return 0;
}
#endif /*NOLIBREADLINE*/
void unquote(char * s){
	if (s!=NULL){
		if (s[0] == '"' && s[strlen(s)-1] == '"'){
	        char * buffer = calloc(sizeof(char), strlen(s) + 1);
			strcpy(buffer, s);
			strncpy(s, buffer+1, strlen(buffer)-2);
                        s[strlen(s)-2]='\0';
			free(buffer);
		}
	}
}

void unquote_command_tokens(char ** tokens){
    int i=0;
    while(tokens[i] != NULL) {
        unquote(tokens[i]);
        i++;
    }
}

void unquote_redirect_filenames(List *redirections){
    List *lst = redirections;
    while (lst != NULL) {
        Redirection *redirection = (Redirection *)lst->head;
        if (redirection->r_type == R_FILE) {
            unquote(redirection->u.r_file);
        }
        lst = lst->tail;
    }
}

void unquote_command(Command *cmd){
    List *lst = NULL;
    switch (cmd->command_type) {
        case C_SIMPLE:
        case C_OR:
        case C_AND:
        case C_PIPE:
        case C_SEQUENCE:
            lst = cmd->command_sequence->command_list;
            while (lst != NULL) {
                SimpleCommand *cmd_s = (SimpleCommand *)lst->head;
                unquote_command_tokens(cmd_s->command_tokens);
                unquote_redirect_filenames(cmd_s->redirections);
                lst = lst->tail;
            }
            break;
        case C_EMPTY:
        default:
            break;
    }
}

// void handleBackground(int value) {
//     pid_t pid;
//     while(1) {
//         pid = waitpid(-1, NULL, WNOHANG);
//         if(pid == 0) {
//             return;
//         } else if(pid == -1) {
//             return;
//         } else {
//             StatusList *temp = statuslist;
//             while(statuslist != NULL) {
//                 if(statuslist->head.pid == pid) {
//                     statuslist->head.status = "dead";
//                 }
//                 statuslist = statuslist->tail;
//             }
//             statuslist = temp;
//         }
//     }
// }

void handleBackground(int value) {
    StatusList *temp = statuslist;
    char * status_str = malloc(50);
    pid_t kidpid;
    int status;
    while((kidpid = waitpid(-1, &status, WNOHANG)) > 0) {
        if(WIFEXITED(status)) {
            exit_status = WEXITSTATUS(status);
            snprintf(status_str, 50, "exit(%d)", status);
            while(statuslist != NULL) {
                if(statuslist->head.pid == kidpid) {
                    statuslist->head.status = status_str;
                }
                statuslist = statuslist->tail;
            }
        }
        else if(WIFSIGNALED(status)) {
            exit_status = WTERMSIG(status);
            snprintf(status_str, 50, "signal(%d)", status);
            while(statuslist != NULL) {
                if(statuslist->head.pid == kidpid) {
                    statuslist->head.status = status_str;
                }
                statuslist = statuslist->tail;
            }
        }
        else {
            /* Irgendwas anderes ist mit dem child passiert */
            statuslist->head.status = "this shouldn't happen";
        }
    }
    statuslist = temp;
}


static int execute_fork(SimpleCommand *cmd_s, int background) {
    char ** command = cmd_s->command_tokens;
    pid_t pid, wpid;
    int pip[2];
    pipe(pip);

    if(background != 0) {
        struct sigaction sa;
        void handleBackground(int value);
        sigfillset(&sa.sa_mask);
        sa.sa_handler = handleBackground;
        sa.sa_flags = 0;
        sigaction(SIGCHLD, &sa, NULL);
    }

    pid = fork();
    if (pid==0) {
        /* Set status */
        Status sts;
        sts.pgid = getpid();
        sts.pid = getpid();
        sts.status = "running";
        sts.prog = command[0];
        
        /* Send status to parent */
        close(pip[0]);
        if (write(pip[1], &sts, sizeof(Status)) == -1) {
            printf("Error when writing!\n");
        }
        close(pip[1]);
        /* child */
        signal(SIGINT, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
        /* REDIRECTIONS */
        if (cmd_s->redirections != NULL) {
            List * rdList = cmd_s->redirections;
            while(rdList != NULL) {
                Redirection * redirection = rdList->head;
                int fd;

                if(redirection->r_mode == M_WRITE || redirection->r_mode == M_APPEND) {
                    if(redirection->r_type == R_FILE) {
                        if(redirection->r_mode == M_WRITE) {
                            if((fd = open(redirection->u.r_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR)) == -1) {
                                fprintf(stderr, "%s: ", redirection->u.r_file);
                                perror("");
                                exit(EXIT_FAILURE);
                            }
                        }
                        else {
                            if((fd = open(redirection->u.r_file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IXUSR)) == -1) {
                                fprintf(stderr, "%s: ", redirection->u.r_file);
                                perror("");
                                exit(EXIT_FAILURE);
                            }
                        }
                        dup2(fd, STDOUT_FILENO);
                    }
                    else {
                        dup2(redirection->u.r_fd, STDOUT_FILENO);
                    }
                }

                if(redirection->r_mode == M_READ) {
                    
                    if(redirection->r_type == R_FILE) {
                        if ((fd = open(redirection->u.r_file, O_RDWR, S_IRUSR | S_IWUSR | S_IXUSR)) == -1) {
                            fprintf(stderr, "%s: ", redirection->u.r_file);
                            perror("");
                            exit(EXIT_FAILURE);
                        }
                        dup2(fd, STDIN_FILENO);
                    }
                    else {
                        dup2(redirection->u.r_fd, STDIN_FILENO);
                    }
                }

                //fclose(redirection->u.r_file);
                rdList = rdList->tail;
            }
        }
        if (execvp(command[0], command) == -1){
            fprintf(stderr, "-bshell: %s : command not found \n", command[0]);
            perror("");
        }
        /*exec only return on error*/
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("shell");

    } else {
        /* Receive status from child */
        Status temp;
        close(pip[1]);
        if (read(pip[0], &temp, sizeof(Status)) == -1) {
            printf("Error when reading!\n");
        }

        close(pip[0]); 
        statuslist = statuslist_append(temp, statuslist);

        /* parent */
        setpgid(pid, pid);

        if (background != 0) {
            tcsetpgrp(fdtty, pid);
            tcsetpgrp(fdtty, shell_pid);
        }

        if (background == 0) {
            /* wait only if no background process */
            tcsetpgrp(fdtty, pid);
            
            int status;
            StatusList * lst = statuslist;
            char * status_str = malloc(50);

            while(statuslist->head.pid != pid) {
                statuslist = statuslist->tail;
                if(statuslist == NULL) {
                    fprintf(stderr, "Couldn't find pid in statuslist: %d", pid);
                    exit(EXIT_FAILURE);
                }
            }

            wpid= waitpid(pid, &status, 0);
            if(WIFEXITED(status)) {
                exit_status = WEXITSTATUS(status);
                snprintf(status_str, 50, "exit(%d)", status);
                statuslist->head.status = status_str;
            }
            else if(WIFSIGNALED(status)) {
                exit_status = WTERMSIG(status);
                snprintf(status_str, 50, "signal(%d)", status);
                statuslist->head.status = status_str;
            }
            else {
                /* Irgendwas anderes ist mit dem child passiert */
                statuslist->head.status = "this shouldn't happen";
            }

            statuslist = lst; // ptr back to head element
            tcsetpgrp(fdtty, shell_pid);
            return 0;
        }
    }
    return 0;
}

static int do_execute_simple(SimpleCommand *cmd_s, int background){
    if (cmd_s==NULL){
        return 0;
    }
    if (strcmp(cmd_s->command_tokens[0],"exit")==0) {
        exit(0);
    } else if (strcmp(cmd_s->command_tokens[0],"cd")==0) {
        if(cmd_s->command_token_counter == 1) {
            chdir(getenv("HOME"));
            return 0;
        }
        else {
            if(chdir(cmd_s->command_tokens[1]) == -1) {
                fprintf(stderr, "%s: ", cmd_s->command_tokens[1]);
                perror("");
                return(1);
            }
            chdir(cmd_s->command_tokens[1]);
            return 0;
        }
    } else if (strcmp(cmd_s->command_tokens[0],"status")==0) {
        //printf("Status cool\n");
        statuslist_print(statuslist);
        StatusList *temp = NULL;
        while(statuslist != NULL) {
            int res = strcmp(statuslist->head.status, "running");
            if(res != 0) {
                statuslist = statuslist->tail;
            } else {
                temp = statuslist_append(statuslist->head, temp);
                statuslist = statuslist->tail;
            }
        }
        statuslist = temp;
        printf("\n");
        return 0;
/* do not modify this */
#ifndef NOLIBREADLINE
    } else if (strcmp(cmd_s->command_tokens[0],"hist")==0){
        return builtin_hist(cmd_s->command_tokens);
#endif /* NOLIBREADLINE */
    } else {
        return execute_fork(cmd_s, background);
    }
    fprintf(stderr, "This should never happen!\n");
    exit(1);
}

/*
 * check if the command is to be executed in back- or foreground.
 *
 * For sequences, the '&' sign of the last command in the
 * sequence is checked.
 *
 * returns:
 *      0 in case of foreground execution
 *      1 in case of background execution
 *
 */
int check_background_execution(Command * cmd){
    List * lst = NULL;
    int background =0;
    switch(cmd->command_type){
    case C_SIMPLE:
        lst = cmd->command_sequence->command_list;
        background = ((SimpleCommand*) lst->head)->background;
        break;
    case C_OR:
        lst = cmd->command_sequence->command_list;
        while (lst !=NULL){
            background = ((SimpleCommand*) lst->head)->background;
            lst=lst->tail;
        }
    case C_AND:
        lst = cmd->command_sequence->command_list;
        while (lst !=NULL){
            background = ((SimpleCommand*) lst->head)->background;
            lst=lst->tail;
        }
    case C_PIPE:
        lst = cmd->command_sequence->command_list;
        while (lst !=NULL){
            background = ((SimpleCommand*) lst->head)->background;
            lst=lst->tail;
        }
    case C_SEQUENCE:
        /*
         * last command in sequence defines whether background or
         * forground execution is specified.
         */
        lst = cmd->command_sequence->command_list;
        while (lst !=NULL){
            background = ((SimpleCommand*) lst->head)->background;
            lst=lst->tail;
        }
        break;
    case C_EMPTY:
    default:
        break;
    }
    return background;
}

static int execute_pipe(List * list, int length) {
    List * lst = list;
    SimpleCommand *item = list->head;
    int pipe_length = length - 1, pip[pipe_length][2], statusPipe[length][2];
    pid_t pids[length];

    for(int i = 0; i < pipe_length; i++) {
        if(pipe2(pip[i], O_CLOEXEC) == -1) {
            fprintf(stderr, "Error when piping: pipe[%d] failed!\n", i);
            exit(1);
        }
    }

    for(int i = 0; i < length; i++) {
        if(pipe2(statusPipe[i], O_CLOEXEC) == -1) {
            fprintf(stderr, "Error when piping: statusPipe[%d] failed!\n", i);
            exit(1);
        }
    }

    for(int i = 0; i < length; i++) {
        if(i != 0) {
            lst = lst->tail;
            item = lst->head;
        }

        pids[i] = fork();

        if(pids[i] == 0) {
            Status sts;
            
            sts.pgid = getpgid(getpid());
            sts.pid = getpid();
            sts.status = "running";
            sts.prog = item->command_tokens[0];
            
            setpgid(0, pids[0]);
            tcsetpgrp(fdtty, getpgid(0));
            signal(SIGINT, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);

            if(i != 0) dup2(pip[i - 1][READ], STDIN_FILENO);
            if(i != pipe_length) dup2(pip[i][WRITE], STDOUT_FILENO);

            close(statusPipe[i][READ]);
            write(statusPipe[i][WRITE], &sts, sizeof(Status));

            for(int k = 0; k < pipe_length; k++) {
                close(pip[k][READ]);
                close(pip[k][WRITE]);
                if(k != 1) close(statusPipe[k][READ]);
                close(statusPipe[k][WRITE]);
            }

            execvp(item->command_tokens[0], item->command_tokens);
        }
    }

    // Parent

    setpgid(pids[pipe_length], pids[0]);
    tcsetpgrp(fdtty, pids[0]);

    for(int i = 0; i < pipe_length; i++) {
        close(pip[i][READ]);
        close(pip[i][WRITE]);
    }

    for(int i = 0; i < length; i++) {
        Status temp;
        close(statusPipe[i][WRITE]);
        read(statusPipe[i][READ], &temp, sizeof(Status));
        close(statusPipe[i][READ]);
        statuslist = statuslist_append(temp, statuslist);
    }

    for(int i = 0; i < length; i++) {
        int status;
        StatusList * lst = statuslist;
        char * status_str = malloc(50);

        while(statuslist->head.pid != pids[i]) {
            statuslist = statuslist->tail;
            if(statuslist == NULL) {
                fprintf(stderr, "Couldn't find pid in statuslist: %d", pids[i]);
                exit(EXIT_FAILURE);
            }
        }

        waitpid(-1, &status, 0);
        
        if(WIFEXITED(status)) {
            exit_status = WEXITSTATUS(status);
            snprintf(status_str, 50, "exit(%d)", status);
            while(statuslist != NULL) {
                if(statuslist->head.pgid == getpgid(getpid())) {
                    statuslist->head.status = status_str;
                }
                statuslist = statuslist->tail;
            }
        }
        else if(WIFSIGNALED(status)) {
            exit_status = WTERMSIG(status);
            snprintf(status_str, 50, "signal(%d)", status);
            while(statuslist != NULL) {
                if(statuslist->head.pgid == getpgid(getpid())) {
                    statuslist->head.status = status_str;
                }
                statuslist = statuslist->tail;
            }
        }
        else {
            /* Irgendwas anderes ist mit dem child passiert */
            statuslist->head.status = "this shouldn't happen";
        }

        statuslist = lst; // ptr back to head element

    }
    tcsetpgrp(fdtty, shell_pid);
    return 0;
}

int execute(Command * cmd){
    unquote_command(cmd);

    int res=0, length = 0;
    List * lst=NULL;

    int execute_in_background=check_background_execution(cmd);
    switch(cmd->command_type){
    case C_EMPTY:
        break;
    case C_SIMPLE:
        res=do_execute_simple((SimpleCommand*) cmd->command_sequence->command_list->head, execute_in_background);
        fflush(stderr);
        break;

    case C_OR:
        lst = cmd->command_sequence->command_list;
        do {
            res=do_execute_simple((SimpleCommand*) lst->head, execute_in_background);
            lst=lst->tail;
        }
        while (lst != NULL && exit_status != 0);
        break;
    case C_AND:
        lst = cmd->command_sequence->command_list;
        while (lst != NULL && exit_status == 0) {
            res=do_execute_simple((SimpleCommand*) lst->head, execute_in_background);
            lst=lst->tail;
        }
        break;
    case C_SEQUENCE: 
        lst = cmd->command_sequence->command_list;
        while (lst != NULL) {
            res=do_execute_simple((SimpleCommand*) lst->head, execute_in_background);
            lst=lst->tail;
        }
        break;
    case C_PIPE:
        lst = cmd->command_sequence->command_list;
        length = cmd->command_sequence->command_list_len;
        res = execute_pipe(lst, length);
        break;
    default:
        printf("[%s] unhandled command type [%i]\n", __func__, cmd->command_type);
        break;
    }
    return res;
}