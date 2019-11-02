//  Timing of Package sort vs Quick vs Shell 
//
//  Unfortunately, the system sort provided by Golang is slow.  Compare this to
//  the system sort provided by Java, namely Arrays.sort, which is interestingly
//  fast (see sortIntArray.java).  Shell and Quick each completed sorting in about
//  three-quarters of the time of their counterparts in Java for the same size array.
//  There seems to be merit in the claim that Arrays.sort is very efficient compared
//  to sort.Ints for sorting an array of integers initially in descending order.
//
//  Sample output:
//
//	$ go run sortIntSlice.go		$ java sortIntArray.java
//	sort.Ints: 64.323ms			Arrays.sort:  17 msec
//	    Quick: 23.512ms			 Quick Sort:  39 msec
//	    Shell: 31.044ms			 Shell Sort:  48 msec

package main

import ("fmt"; "sort"; "time")

func main() {
	tm_stats(sort.Ints , "sort.Ints:")
	tm_stats(quicksort , "    Quick:")
	tm_stats(shellsort , "    Shell:")
}

func tm_stats(funcp func([]int), msg string) {
	const size = 1000000
	intSlice := make([]int, size)

	// Descending order as a common starting point
	for i,j := 0,size; i < size; i,j = i+1,j-1 {
		intSlice[i] = j
	}

	start := time.Now()
	funcp(intSlice)
	elapsed := time.Since(start)

	// Make sure the sort is correct
	if !sort.IntsAreSorted(intSlice) {
		fmt.Println(msg, "failed")
		return
	}

	// Sort was verified, so print timing data
	fmt.Println(msg, elapsed)
}

func quicksort(slc []int) {
	n := len(slc)
	if n < 2 {
		return
	}

	left, right := 0, n-1
	pivot := left + ((right - left)>>1)
	slc[pivot], slc[right] = slc[right], slc[pivot]

	for i,_ := range slc {
		if slc[i] < slc[right] {
			slc[left], slc[i] = slc[i], slc[left]
			left++
		}
	}

	slc[left], slc[right] = slc[right], slc[left]

	// Activation records, woof
	quicksort(slc[:left])
	quicksort(slc[left+1:])
}

func shellsort(slc []int) {
	n := len(slc)

	for gap := n>>1; gap > 0; gap>>=1  {
		for i := gap; i < n; i++ {
			j, temp := i, slc[i]
			for ; j >= gap && slc[j-gap] > temp; j -= gap {
				slc[j] = slc[j-gap]
			}
			slc[j] = temp
		}
	}
}
