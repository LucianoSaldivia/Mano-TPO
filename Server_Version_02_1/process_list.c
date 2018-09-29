#include <stdlib.h>
#include <stdio.h>
#include "process_list.h"

/**
 * @brief Agrega un nodo a la lista, new_node ya debe estar reservado
 * @param root Puntero al primer nodo de la lista
 * @param new_node Nodo a agregar
 */
void add_node(process_node_t **root, process_node_t *new_node){
    process_node_t *local_node = *root;

    if(local_node == NULL){
        // Primer nodo de la lista
        *root = new_node;
        (*root)->next = NULL;
        return;
    }

    // Busco el ultimo nodo
    while(local_node->next != NULL){
        local_node = local_node->next;
    }

    // Agrego el nodo nuevo al final
    new_node->next = NULL;
    local_node->next = new_node;
}

/**
 * @brief Elimina el primer nodo de la lista
 * @param root Puntero al primer nodo de la lista
 * @return El nodo eliminado, si child_pid es -1, no se encontro el nodo
 */
process_node_t delete_first_node(process_node_t **root){
    process_node_t *local_node = *root;
    process_node_t ret_node;

    ret_node.child_pid = -1;

    // Lista vacia
    if(local_node == NULL){
        return ret_node;
    }

    ret_node = *local_node;
    *root = local_node->next;

    free(local_node);

    return ret_node;
}

/**
 * @brief Elimina un nodo de la lista mediante el pid del hijo requerido
 * @param root Puntero al primer nodo de la lista
 * @param del_child_pid Process ID del hijo a eliminar en la lista
 * @return El nodo eliminado, si child_pid es -1, no se encontro el nodo
 */
process_node_t delete_node_by_pid(process_node_t **root, pid_t del_child_pid){
    process_node_t *prev_node = *root;
    process_node_t *del_node;
    process_node_t ret_node;

    ret_node.child_pid = -1;

    // Si no hay lista vuelvo sin hacer nada
    if(prev_node == NULL){
        return ret_node;
    } else{
        del_node = prev_node->next;
    }

    if(prev_node->child_pid == del_child_pid){
        // El nodo a eliminar es el primero
        *root = del_node;
        ret_node = *prev_node;

        free(prev_node);

        return ret_node;
    }

    // Encuentro el nodo a eliminar
    while((del_node->child_pid != del_child_pid) && (del_node != NULL)){
        prev_node = prev_node->next;
        del_node = del_node->next;
    }

    // Si no se encontro el PID
    if(del_node == NULL){
        return ret_node;
    }

    prev_node->next = del_node->next;
    ret_node = *del_node;
    free(del_node);

    return ret_node;
}

/**
 * @brief Elimina totalmente la lista
 * @param root Puntero al primer nodo de la lista
 */
void delete_list(process_node_t **root){
    process_node_t *local_node = *root;
    process_node_t *aux_node;

    if(*root == NULL){
        return;
    }

    // Elimino los nodos de la lista
    do{
        aux_node = local_node->next;
        free(local_node);
        local_node = aux_node;
    }while(local_node != NULL);

    return;
}
