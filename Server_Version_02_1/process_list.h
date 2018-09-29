#ifndef PROCESS_LIST_H
#define PROCESS_LIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct process_node{
    pid_t child_pid;
    pid_t father_pid;
    struct process_node *next;
} process_node_t;

void add_node(process_node_t **root, process_node_t *new_node);
process_node_t delete_first_node(process_node_t **root);
process_node_t delete_node_by_pid(process_node_t **root, pid_t del_child_pid);
void delete_list(process_node_t **root);

#endif // PROCESS_LIST_H
