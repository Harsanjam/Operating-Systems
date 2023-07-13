#include <stdlib.h>
#include <stdio.h>
#include "pri_queue.h"
/** @file pri_queue.c */
static Node_ptr_t head = NULL;

/**
 * Insert a Node into a priority queue.
 * @param priority
 * @param data
 * @author Harsanjam
 */
void PQ_insert(int priority, char * data) {
    Node_ptr_t newNode, tmp;
    newNode = (Node_ptr_t)malloc(sizeof(Node_t));
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;
    
    if (head == NULL) {
        head = newNode;
    } else if (head->priority < priority) {
        newNode->next = head;
        head = newNode;
    } else {
        tmp = head;
        while (tmp->next != NULL && tmp->next->priority >= priority) {
            tmp = tmp->next;
        }
        newNode->next = tmp->next;
        tmp->next = newNode;
    }
}


/**
 * Delete and return the node with the highest priority.
 * @return The highest priority Node.
 */
Node_ptr_t PQ_delete() {
    if (head == NULL) {
        printf("Error: Queue is empty\n");
        return NULL;
    } else {  
        Node_ptr_t return_node = head;
        head = head->next;
        return return_node;
    }
}


/**
 * Do NOT modify this function.
 * @return A pointer to the head of the list.  (NULL if list is empty.)
 */
Node_ptr_t PQ_get_head() {
    return head;
}

/**
 * Do NOT modify this function.
 * @return the number of items in the queue
 */
int PQ_get_size() {
    int size = 0;
    Node_ptr_t tmp;
    for(tmp = head; tmp != NULL; tmp = tmp->next, size++){
    }
    return size;
}
