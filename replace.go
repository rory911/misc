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

	fmt.Printf("Original: %s\n", a);

	for i, v := range a {
		if (v != 'a') {
			continue
		}
		p = i + (cnt * len(s)) + 1
		a = append(a[:p], append(s, a[p:]...)...)
		cnt++
	}

	fmt.Printf("Replaced: %s\n",a)
}
