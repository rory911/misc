package main

import (
	"fmt"
	"math/rand"
	"sync"
)

const	N = 200
var	random, rank, sorted  [N]int

// O(N) loop to rank a given element, then vector into a sorted array
//
func findRank(self int, wg *sync.WaitGroup) {
	defer wg.Done()
	rank[self] = 0
	for i := range random {
		if random[i] < random[self] ||
		    (random[i] == random[self] && i < self) {
			rank[self]++
		}
	}
	sorted[rank[self]] = random[self]
}

// Parallel rank sort, aka enumeration sort
//
func main() {
	var wg sync.WaitGroup

	// Generate a random array of integers
	for i := range random {
		random[i] = rand.Intn(N<<3)
	}
	fmt.Println(random, "\n")

	// Sort with each thread determining its given rank
	for i := range random {
		wg.Add(1)
		go findRank(i, &wg)
	}
	wg.Wait()
	fmt.Println(sorted)
}
