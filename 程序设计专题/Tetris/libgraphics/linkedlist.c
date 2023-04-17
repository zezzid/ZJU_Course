/*
 * File: linkedlist.c
 * -------------
 * This file implements the linkedlist.h abstraction.
 */

#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

#ifndef New
#define New(T) (T)malloc(sizeof(*(T)NULL))
#define FreeBlock(T) free(T)
#endif

/* Exported entries */


/*
 * Function: NewLinkedList
 * Usage: linkedlist = NewLinkedList();
 * --------------------------
 * This function allocates and returns an empty linked list (including a head
 * node only).
 */

linkedlistADT NewLinkedList(void)
{
    linkedlistADT head;

    head = New(linkedlistADT);
    head->dataptr = NULL;
	head->next = NULL;
    return (head);
}

/*
 * Function: FreeLinkedList
 * Usage: FreeLinkedList(head);
 * ------------------------
 * This function frees the storage associated with linked list.
 */

void FreeLinkedList(linkedlistADT head)
{
	linkedlistADT nodeptr, nextnodeptr;

	nodeptr = head;
	while (nodeptr != NULL) {
	    nextnodeptr = nodeptr->next;
		if (nodeptr != head) FreeBlock(nodeptr->dataptr);
		FreeBlock(nodeptr);
		nodeptr = nextnodeptr;
	}
}

/*
 * Function: SearchNode
 * Usage: nodeptr = SerachNode(linkedlist, obj, equalfunptr);
 * ---------------------------
 * This function searches the obj in the linked list, return the node pointer if
 * find out the obj, renturn NULL otherwise.
 */

linkedlistADT SearchNode(linkedlistADT head, void *obj,
                         bool (*equalfunptr)(void *obj1, void *obj2))
{
	linkedlistADT nodeptr;
	
	if (obj == NULL) return NULL;
	nodeptr = head->next;
	while (nodeptr != NULL) {
		if ((*equalfunptr)(nodeptr->dataptr, obj)) return nodeptr;
	}
	return NULL;
}

/*
 * Function: InsertNode
 * Usage: InsertNode(linkedlist, nodeptr, obj);
 * ----------------------------
 * This function ineserts the data value after the nodeptr node of the linked
 * list. if nodeptr is NULL, append the obj to the tail of the linked list.
 */

linkedlistADT InsertNode(linkedlistADT head, linkedlistADT nodeptr, void *obj)
{
	linkedlistADT ptr;

	if (obj == NULL) return NULL;
	if (nodeptr == NULL) { /*append the obj to the tail*/
		nodeptr = head;
		while (nodeptr->next != NULL) nodeptr = nodeptr->next;
	}
	ptr = New(linkedlistADT); /*New a node*/
	ptr->dataptr = obj;  /*Set the data ptr of the node*/
	ptr->next = nodeptr->next;
	nodeptr->next = ptr;
	return ptr;
}

/*
 * Function: DeleteNode
 * Usage: nodeptr = DeleteNode(linkedlist, obj, equalfunptr);
 * ------------------------------
 * This function deletes the node with the data obj of the linked list. it returns
 * the pointer of the node if found, NULL otherwise.
 */

linkedlistADT DeleteNode(linkedlistADT head, void *obj,
                         bool (*equalfunptr)(void *obj1, void *obj2))
{
	linkedlistADT nodeptr, prenodeptr;

	if (obj == NULL) return NULL;
	prenodeptr = head;
    nodeptr = head->next;
	while (nodeptr != NULL) {
		if ((*equalfunptr)(nodeptr->dataptr, obj)) break;
	    prenodeptr = nodeptr;
        nodeptr = nodeptr->next;
	}
	if (nodeptr != NULL) /*found*/
	    prenodeptr->next = nodeptr->next;
	return nodeptr;
}

/*
 * Function: TraverseLinkedList
 * Usage: TraverseLinkedList(linkedlist, void (*traversefunptr)(void *obj));
 * ------------------------------
 * This function traverses the linked list, and process the node value obj using
 * the function which funptr points to.
 */

void TraverseLinkedList(linkedlistADT head, void (*traversefunptr)(void *obj))
{
	linkedlistADT nodeptr;

	if (traversefunptr == NULL) return;
	nodeptr = head->next;
	while (nodeptr != NULL) {
		(*traversefunptr)(nodeptr->dataptr);
		nodeptr = nodeptr->next;
	}
}

/*
 * Function: ithNode
 * Usage: obj = ithNode(linkedlist, index);
 * ------------------------------
 * This function return the pointer of the index-th node of the linked list.
 */

void *ithNodeobj(linkedlistADT head, int index)
{
	linkedlistADT nodeptr;
	int count = 0;

	nodeptr = head->next;
	while (nodeptr != NULL) {
		if (++count == index) break;
		nodeptr = nodeptr->next;
	}
	if (nodeptr != NULL)
        return nodeptr->dataptr;
	return NULL;
}

/*
 * Function: NextNode
 * Usage: nextnodeptr = NextNode(linkedlist, nodeptr);
 * ------------------------------
 * This function return the pointer of the next node of the node nodeptr.
 */

linkedlistADT NextNode(linkedlistADT head, linkedlistADT nodeptr)
{
	if (nodeptr != NULL) return nodeptr->next;
	return NULL;
}

/*
 * Function: NodeObj
 * Usage: obj = NodeObj(linkedlist, nodeptr);
 * ------------------------------
 * This function return the dataptr of the node nodeptr points to.
 */

void *NodeObj(linkedlistADT head, linkedlistADT nodeptr)
{
	if (nodeptr != NULL) return nodeptr->dataptr;
	return NULL;
}
