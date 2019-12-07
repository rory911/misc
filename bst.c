#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h>
#include <string.h>

/* BST Boundary limits */
#define	LOWER	-999999999
#define	UPPER	999999999

/* Binary tree node  */
typedef struct node { 
	int data; 
	struct node *left;
        struct node *right; 
} node_t; 


/* Determine whether btree is BST */
static bool
validBST(node_t *np, int lower, int upper)
{
	if (np == NULL)
		return(true);

	if (np->data < lower || np->data > upper)
		return(false);
        
        return(validBST(np->left, lower, np->data-1) &&
	    validBST(np->right, np->data+1, upper));
}

/* Allocate a node with the specified value and NULL pointers */
static node_t *
newNode(int data) 
{ 
	node_t *node = (node_t *) malloc(sizeof(struct node)); 
	if (node == NULL)
		exit(EXIT_FAILURE);

	node->data = data; 
	node->left = node->right = NULL; 
	return(node);
} 

/* Print 3 levels of a btree with simple values [0-9], and check for BST */
static void
print_btree(node_t *np)
{
	printf("\n        %d\n", np->data);
	printf("      /   \\\n");
	printf("    %c       %c       Binary Search Tree:  %s\n",
	    (np->left) ? (char)('0' + np->left->data) : (char)('!' - 1),
	    (np->right) ? (char)('0' + np->right->data) : (char)('!' - 1),
	    validBST(np, LOWER, UPPER) ? "TRUE" : "FALSE");
	printf("   / \\     / \\\n");
	printf("  %c   %c   %c   %c\n",
	    (np->left->left) ? (char)(np->left->left->data + '0') : (char)('!' - 1),
	    (np->left->right) ? (char)(np->left->right->data + '0') : (char)('!' - 1),
	    (np->right->left) ? (char)(np->right->left->data + '0')  : (char)('!' - 1),
	    (np->right->right) ? (char)(np->right->right->data + '0') : (char)('!' - 1));
}

/* Test and output the results */
int
main() 
{ 
	node_t *root = newNode(4); 

	root->left = newNode(2); 
	root->right = newNode(5); 
	root->left->left = newNode(1); 
	root->left->right = newNode(6); 
	print_btree(root);
	printf("Exected failure: 6 > 4\n");

	root->left->right->data = 3; 
	print_btree(root);

	root->right->right = newNode(9); 
	print_btree(root);

	root->right->right->data = 0; 
	print_btree(root);
	printf("Exected failure: 0 < 5\n\n");
	exit(0);
} 
