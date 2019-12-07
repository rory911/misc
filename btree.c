#include <stdio.h> 
#include <stdlib.h> 
  
/* Binary tree (btree) node  */
struct node 
{ 
	int data; 
	struct node *left;
        struct node *right; 
}; 
  
static int		max(int a, int b); 
static int		height(struct node* node); 
  
/*
 * Compute the diameter, or width, of a btree as the number of nodes along the
 * longest path between two nodes.  Historically, a single node tree can have
 * a height equal width equal to 1 or 0 depending upon whether it is defined by
 * the number of nodes or by the number of edges. For clarity, it is defined
 * here as 1 and represents the number of nodes.  Therefore, diameter will be
 * the maximum of the following:
 *
 *    1) Diameter of left subtree 
 *    2) Diameter of right subtree 
 *    3) Height of left subtree + height of right subtree + 1
 *
 */
static int
diameter(struct node *tree) 
{ 
	int lheight, rheight, ldiameter, rdiameter; 

	/* Empty tree */
	if (tree == NULL) 
		return (0); 

	/* Height of left and right sub-trees */
	lheight = height(tree->left); 
	rheight = height(tree->right); 
	     
	/* Diameter of left and right sub-trees */
	ldiameter = diameter(tree->left);
	rdiameter = diameter(tree->right); 
    
	return (max(lheight + rheight + 1, max(ldiameter, rdiameter))); 
}  
  
/*
 * Compute the height of a btree as the number of nodes along the
 * longest path from the root node down to the farthest leaf node.
 */
static int
height(struct node* tree) 
{ 
	/* Empty tree */ 
	if(tree == NULL) 
		return (0); 
	     
	return (1 + max(height(tree->left), height(tree->right))); 
}  
  
/* Allocate a node with the given data and NULL left and right pointers. */
static struct node*
newNode(int data) 
{ 
	struct node* node = (struct node*) malloc(sizeof(struct node)); 
	if (node == NULL)
		exit(EXIT_FAILURE);

	node->data = data; 
	node->left = node->right = NULL; 
	return(node); 
} 
  
static int
max(int a, int b) 
{ 
	return (a >= b)? a: b; 
}     
  
int
main() 
{ 
	struct node *root = newNode(1); 

	root->left = newNode(2); 
	root->right = newNode(3); 
	root->left->left = newNode(4); 
	root->left->right = newNode(5); 
      
	printf("For binary tree:\n");
	printf("      1\n");
	printf("     / \\\n");
	printf("    2   3\n");
	printf("   / \\\n");
	printf("  4   5\n\n");
	printf("Diameter is %d\n", diameter(root)); 
	printf("Height is %d\n", height(root));
	return(0);
} 
