// Copyright 2019, Rory Foster
//
// Per interview by Wes Panther on https://livecode.amazon.jobs
// For a list of positive integers, print out pairs that add to
// the specified sum.
//
// Given a set=[8,1,7,2,0,3,14,4] and sum=11, output:
//
//	(8,3), (7,4)
//
package main

import (
        "fmt"
	"sort"
	"time"
	"math/rand"
)

const TARGET	= 37
const size	= 50000

// Uses an identity hash O(N) without any duplicates, does not care about order,
// but cannot handle negative integers.  A possible approach for negative integers
// is to use a separate hash table for the negative indices, especially when upper
// and lower bounds are defined.
func ihashSum(a []int) {
	var h[TARGET + 1]bool

	for _, v := range a {
		if v > TARGET {
			continue
		}
		h[v] = true
	}

	for i, j := 0, len(h) - 1; i < j; i, j = i+1, j-1 {
		if h[i] && h[j]	{
			fmt.Printf("(%v, %v), ", i, j)
		}
	}
}

// Uses sorting O(NlogN), can report duplicates, and works with
// negative integers.
func sortSum(a []int) {
	sort.Ints(a)
	for i, j := 0, len(a)-1; i < j; {
		if a[i] + a[j] < TARGET {
			i++
			continue
		}
		if a[i] + a[j] > TARGET {
			j--
			continue
		}
		fmt.Printf("(%v, %v), ", a[i], a[j])
		i, j = i+1, j-1
	}
}

// Uses brute force O(N^2), reports all duplicates, does not care
// about order, and works with negative integers.
func bruteSum(a []int) {
	for i := 0; i < len(a); i++ {
		for j := i+1; j < len(a); j++ {
			if a[i] + a[j] == TARGET {
				fmt.Printf("(%v, %v), ", a[i], a[j])
			}
		}
	}
}

// Compare timing of each search function.  Actually, the timing
// is unfair on a finer scale.  The print statements throw off the
// results, and heavily penalize reporting duplicates.  Nevertheless,
// on the larger scale, it does help illustrate orders of magnitude
// between the routines.
func main() {
	set := make([]int, size)

	for i := 0; i < size; i++ {
		set[i] = rand.Intn(size + (size>>1))
	}

	start := time.Now()
	ihashSum(set)
	elapsed := time.Since(start)
	fmt.Printf("\b\b  \nihashSum: elapsed time %v\n\n", elapsed)

	start = time.Now()
	sortSum(set)
	elapsed = time.Since(start)
	fmt.Printf("\b\b  \nsortSum: elapsed time %v\n\n", elapsed)

	start = time.Now()
	bruteSum(set)
	elapsed = time.Since(start)
	fmt.Printf("\b\b  \nbruteSum: elapsed time %v\n", elapsed)
}
