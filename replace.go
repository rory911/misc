package main

import "fmt"

//
// Replace 'a' with 'abc' in the array 'aefdacba'
//
// As per request from Mehmet Yildiz of Cadence Design Systems, Austin, Texas.
// Because the target string starts the replacement string, the code can simply
// shift and add to solve the problem.
//
func main() {
	cnt, p := 0, 0
	arr := []byte("aefdacba")	// original array
	sub := []byte("bc")		// subarray used for replacement

	fmt.Printf("Original: %s\n", arr);

	for i, v := range arr {
		if (v != 'a') {
			continue
		}
		p = i + (cnt * len(sub)) + 1
		arr = append(arr[:p], append(sub, arr[p:]...)...)
		cnt++
	}

	fmt.Printf("Replaced: %s\n", arr)
}
