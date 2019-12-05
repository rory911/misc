package main

import (
	"fmt"
	"strings"
)

type Node struct {
	left	*Node
	right	*Node
	data	int
}

// Determine if a binary tree is a Balanced Search Tree (BST)
func (n *Node) isBST(lower, upper int) bool {
	if n == nil {
		return true
	}
	if n.data <= lower || n.data >= upper {
		return false
	}
	return n.left.isBST(lower, n.data) && n.right.isBST(n.data, upper)
}

// Propegate an int slice into a Fully Populated Balanced Binary Tree (FPBBT)
func (n *Node) bldBtree(subnodes []int) {
	n.left  = &Node {nil, nil, subnodes[0]}
	n.right = &Node {nil, nil, subnodes[1]}
	if len(subnodes) < 6   {
		return
	}
	n.left.bldBtree(subnodes[2:])
	n.right.bldBtree(subnodes[4:])
}

// Output 3 levels of a Fully Populated Balanced Binary Tree (FPBBT)
func (n *Node) prt3lFPBBT(k int, msg string) {
	ws := strings.Repeat(" ", k)
	fmt.Printf("\n%v%d\n", ws, n.data)
	fmt.Printf("%v/     \\\n", ws[:k-3])
	fmt.Printf("%s%v         %v\t\t%v %v\n", ws[:k-5], n.left.data,
	    n.right.data, n.isBST(-999, 999), msg)
	fmt.Printf("%s/   \\     /   \\\n", ws[:k-7]);
	fmt.Printf("%s%v     %v   %v     %v\n\n", ws[:k-8], n.left.left.data,
	    n.left.right.data, n.right.left.data, n.right.right.data)
}

// Search for BSTs among FPBBTs
func main() {
	root := Node {nil, nil, 5}

	a := []int {3, 8, 2, 4, 6, 7}
	root.bldBtree(a)
	root.prt3lFPBBT(15, "(expected failure: 7)")

	copy(a, []int {3, 8, 2, 4, 6, 9})
	root.bldBtree(a)
	root.prt3lFPBBT(15, "(expect success)")

	copy(a, []int {3, 8, 3, 4, 6, 9})
	root.bldBtree(a)
	root.prt3lFPBBT(15, "(expected failure: 3)")
}
