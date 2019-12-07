#include <stdio.h>
#include <stdlib.h>
#include <mcheck.h>

//
// A collection of routines for single linked lists
//

typedef struct node {
	struct node *link;
	int value;
} node_t;


static void
insert(node_t *new, node_t *head)
{
	node_t *node = head;

	while (node->link != head) {
		if (new->value < node->link->value)
			break;
		node = node->link;
	}

	new->link = node->link;
	node->link = new;
}

static node_t *
delete(int val, node_t *head)
{
	node_t *node = head;
	node_t *dnode;

	while (node->link != head) {
		if (val == node->link->value) {
			dnode = node->link;
			node->link = node->link->link;
			return (dnode);
		}
		node = node->link;
	}

	return (NULL);
}

static void
invert(node_t *head)
{
	node_t	*prev;
	node_t	*curr = head;
	node_t	*next = head->link;

	while (next != head) {
		prev = curr;
		curr = next;
		next = next->link;
		curr->link = prev;
	}

	head->link = curr;
	head = curr;
}

static void
printlist(node_t *head, char *msg)
{
	node_t *node = head->link;

	printf("%s", msg);
	while (node != head) {
		printf("%2d, ", node->value);
		node = node->link;
	}
	printf("\b\b  \n\n");
}

static node_t *
construct(int num)
{
	node_t *head, *node = malloc(sizeof(node_t));
	if (node == NULL)
		exit(EXIT_FAILURE);
	head = node;
	node->value = 0;

	for (int i = 1; i < num; ++i) {
		node->link = malloc(sizeof(node_t));
		if (node->link == NULL)
			exit(EXIT_FAILURE);
		node->link->value = i;
		node = node->link;
	}

	node->link = head;
	return (head);
}

static void
destroy(node_t *head)
{
	node_t *dnode, *node = head->link;

	while (node != head) {
		dnode = node;
		node = node->link;
		free(dnode);
	}

	free(head);
}

int
main()
{
	node_t *node, *head;

#ifdef DEBUG
	mtrace();
#endif

	/* Generate a linked list */
	head = construct(12);
	printlist(head, "\nOriginal:  ");

	/* Invert a linked list */
	invert(head);
	printlist(head, "Reversed:  ");

	/* Restore the list and remove a node */
	invert(head);
	printlist(head, "Restored:  ");
	node = delete(3, (node_t *)head);
	printlist(head, "Delete 3:  ");

	/* Sorted linked list insert of a node */
	node->value = 7;
	insert(node, head);
	printlist(head, "Insert 7:  ");
	destroy(head);
}
