// Copyright 2019, Rory Foster 
// Find anagrams using unicode and json

package main

import (
	"fmt"
	"sort"
	"unicode"
	"encoding/json"
	"log"
)

// String to (U)nicode, (S)orted, (J)son encode, and (S)tring
func str2USJS(s string) string {
	uc := make([]int, 0)

	// Convert to unicode (ignore white space and case)
	for _, v := range s {
		if !unicode.IsSpace(v) {
			uc = append(uc, int(unicode.ToLower(v)))
		}
	}

	// Sort, json encode, and back to string
	sort.Ints(uc)
	je, err := json.Marshal(uc)
	if err != nil {
		log.Fatal(err)
	}
	return string(je)
}

// Test if strings are anagrams (equality) afer sorted conversion
func IsAnagram(s1 string, s2 string) bool {
	if len(s1) != len(s2) {
		return false
	}
	return str2USJS(s1) == str2USJS(s2)
}

// Compare strings and determine if they are anagrams
func main() {
	data := []string { "Just a string", "School master", "The classroom",
			   "A gentleman", "Elegant man", "The eyes", "They see",
			   "Dormitory", "dirty room", "foo bar", "fubar" }

	// Output the original strings to be compared
	fmt.Printf("Given:\n")
	for _, v := range data {
		fmt.Printf("\t\"%s\"\n", v)
	}

	// Report which strings are anagrams
	fmt.Printf("\nAnagrams:\n")
	for i := 0; i + 1 < len(data); i++ {
		if IsAnagram(data[i], data[i+1]) {
			fmt.Printf("\t\"%s\" and \"%s\"\n", data[i], data[i+1])
			continue
		}
	}
}
