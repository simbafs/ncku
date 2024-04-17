package main

import (
	"fmt"
)

var (
	n = 10
	p = []int{0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30}
	r = make([]int, n+1) // r store a rod with length i, what is the maximum revenue
	s = make([]int, n+1) // s store the first cut position
)

func init() {
	for i := range r {
		r[i] = p[i]
		s[i] = 0
	}
}

func main() {
	for i := 1; i <= n; i++ { // a rod with length i
		for j := 1; j <= i; j++ { // cut at j
			// fmt.Printf("r[%d] = %d, p[%d] = %d, r[%d] = %d\n", i, r[i], j, p[j], i-j, r[i-j])
			cut := r[j] + p[i-j]
			if cut > r[i] {
				r[i] = cut
				s[i] = j
			}
		}
		// fmt.Println()
	}

	for i := range r {
		fmt.Printf("r[%d] = %d, s[%d] = %d\n", i, r[i], i, s[i])
	}

	fmt.Println()
	for i, v := range s {
		if v == 0 {
			fmt.Printf("(%d) = (no cut)", i)

		} else {
			fmt.Printf("(%d) = %d", i, v)
		}
		remaining := i - v
		for v > 0 {
			fmt.Printf(" + %d", remaining-s[v])
			v = s[v]
		}
		fmt.Printf(" = %d, p = %d\n", r[i], p[i])

	}
}
