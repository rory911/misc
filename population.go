//  Given a list of people with date of birth (DoB) and date of death (DoD),
//  find the year with the highest population.  — Gayle Laakmann McDowell

package main

import ("fmt")

func
main() {
        people := [][]int{{1975,1749,1664,1975,1803,2003,1893,1893,1995},  // DoB
                          {2020,1806,1725,2007,1911,2010,1947,1893,2004},} // DoD

	population(people)
}

func
population(people [][]int) {
	births, deaths, alive, census, year := 0, 1, 0, 0, 0
	nextBirth := inOrder(people[births], 0)
	nextDeath := inOrder(people[deaths], 0)

	for i := 0; i < len(people[births]); i++ {
		//  The living
		if (nextBirth > 0) {
			alive += howMany(people[births], nextBirth)
			if (alive > census) {
				census = alive
				year = nextBirth
			}
			nextBirth = inOrder(people[births], nextBirth)
		} else {
			fmt.Println("The largest population was", census,
				"people alive in", year)
			return
		}

		//  The dead
		for nextDeath < nextBirth {
			alive -= howMany(people[deaths], nextDeath)
			nextDeath = inOrder(people[deaths], nextDeath)
			if (nextDeath < 0) {
			}
		}
	}
}

func
inOrder(people []int, prev int) int {
	min := maxYear(people)

	if (min == prev) {
		return 0
	}

	for i := 0; i < len(people); i++ {
		if (people[i] < min && people[i] > prev) {
			min = people[i]
		}
	}

	return min
}

func
maxYear(people []int) int {
	max := 0

	for i := 0; i < len(people); i++ {
		if (people[i] > max) {
			max = people[i]
		}
	}
	return max
}

func
howMany(people []int, year int) int {
	count := 0
	for i := 0; i < len(people); i++ {
		if (people[i] == year) {
			count++
		}
	}
	return count
}
