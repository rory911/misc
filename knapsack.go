package main

import (
	"fmt"
	"log"
)

type Stick struct {
	name	string
	weight	int
	volume	int
}

var boards = []Stick {
	{           "Aipa",  9, 150},
	{        "Arakawa", 13,  35},
	{      "Chemistry", 11,  70},
	{"Channel Islands", 27,  60},
	{         "Delray", 153, 200},
	{            "DHD", 50, 160},
	{       "Firewire", 15,  60},
	{   "Haydenshapes", 43,  75},
	{  "JS Industries", 22,  80},
	{             "KG", 23,  31},
	{           "Lost", 52,  10},
	{          "Pyzel", 42,  70},
	{          "Rusty",  7,  20},
	{       "Takayama",  4,  50},
	// Not included below 435
	{"_bar_",	    48,  10},
	{"_boo_",	   180,  12},
	{"_foo_",	    32,  30},
	{"_fubar_",	    73,  40},
	{"_goo_",	    68,  45},
	{"_howzit_",	    39,  40},
	{"_koo_",	    24,  15},
	{"_zoo_",	    30,  10},
}

// Optimum quiver for a surf trip using volume, weight, 0-1 knapsack.
// This code is not efficient, but instead is intuitive wrt recursion.
//
func knapsack(N, capacity int) ([]Stick, int) {
	// Nothing to do
	if N < 0 || capacity <= 0 {
		return nil, 0
	}

	// If the Nth item exceeds weight capacity, ignore it and
	// use the current quiver.
	if boards[N].weight > capacity {
		return knapsack(N - 1, capacity)
	}

	// Either the Nth item is part of the optimum solution and it
	// should be included, or it is not and it should be ignored.
	//
	// [1] Include the Nth item (increase the quiver)
	incQuiver, incVolume := knapsack(N - 1, capacity - boards[N].weight)
	incQuiver = append(incQuiver, boards[N])
	incVolume += boards[N].volume

	// or
	//
	// [2] Exclude the Nth item and use the current quiver.
	currQuiver, currVolume := knapsack(N - 1, capacity)

	// Maximum of [1] or [2]
	if incVolume > currVolume {
		return incQuiver, incVolume
	} else {
		return currQuiver, currVolume
	}
}

// Output which boards have been picked for the trip based on weight
func quiver(pick []Stick, totalVolume int) {
	cumWeight, cumVolume := 0, 0
	for i := range pick {
		fmt.Printf("%16v\t%4v\t%4v\n", pick[i].name, pick[i].weight, pick[i].volume)
		cumWeight += pick[i].weight
		cumVolume += pick[i].volume
	}
	if cumVolume != totalVolume {
		log.Fatalf("Bad volume: %v != %v\n", cumVolume, totalVolume)
	}
	fmt.Printf("%16v\t%4v\t%4v\n", " ", "____", "____")
	fmt.Printf("%16v\t%4v\t%4v\t", "Total:", cumWeight, cumVolume)
}

// Find a quiver with maximum volume for the given weight capacity 
func main() {
	maxWeight := []int {415, 5, 210, 435, 120, 75}

	for _, v := range maxWeight {
		quiver(knapsack(len(boards) - 1, v))
		fmt.Printf("(%s %v)\n\n\n===\n\n", "maximum weight", v)
	}
}
