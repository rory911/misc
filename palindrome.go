package main

import ( "fmt" )

const N = 32	// Upper limit of bit count

//
// Copy to slice and test the ends toward the middle with O(N) worst case,
// and working storage has a 1:32 ratio to input size.
//
func is_pal1(val uint) bool {
	var	siz int
	var	slc [N]uint

	for siz = 0; siz < N && val > 0; siz,val = siz+1,val>>1 {
		slc[siz] = val & 1
	}

	// Leading zeros are stripped at 'siz'
	fmt.Printf("%13s ", fmt.Sprint(slc[:siz]))

	for i,j := 0,siz-1; i < j; i,j = i+1,j-1 {
		if slc[i] != slc[j] {
			return false
		}
	}
	return true
}

//
// Reverse bits and test for equality with O(N) worst case and 1:1 ratio to input.
//
func is_pal2(val uint) bool {
	fwd, rev := val, uint(0)
	for ; val > 0; val >>= 1 {
		rev <<= 1
		if (val & 1) == 1 {
			rev |= 1
		}
	}
	return fwd == rev
}

//
// Bitwise palindrome as per Amazon interview of 12/10/19.  Alas, the
// more space efficient approach occurred to me later. 
//
func main() {
	var	i uint

	for i = 0; i < N ; i++ {
		fmt.Printf("%2d  %6v %6v\n", i, is_pal1(i), is_pal2(i))
	}
}
