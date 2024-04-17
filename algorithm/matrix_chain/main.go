package main

import (
	"fmt"
	"math"
	"time"
)

func recursive(p []int, i int, j int) int {
	if i+1 == j { // only one matrix is inclusde
		return 0
	}

	minM := math.MaxInt // max int
	for k := i + 1; k < j; k++ {
		val := recursive(p, i, k) + recursive(p, k, j) + p[i]*p[k]*p[j]
		// fmt.Printf("val = %d, minM = %d\n", val, minM)
		if val < minM {
			minM = val
		}
	}
	// fmt.Printf("m[%d, %d] = %d\n", i, j, minM)
	return minM
}

func dp(p []int) (int, [][]int) {
	m := make([][]int, len(p))
	s := make([][]int, len(p))
	for k := range m {
		m[k] = make([]int, len(p))
		s[k] = make([]int, len(p))
	}

	for l := 2; l < len(p); l++ {
		for i := 0; i < len(p)-l; i++ {
			j := l + i
			// fmt.Printf("i = %d, j = %d, l = %d\n", i, j, l)
			m[i][j] = math.MaxInt
			for k := i + 1; k < j; k++ {
				val := m[i][k] + m[k][j] + p[i]*p[k]*p[j]
				if val < m[i][j] {
					m[i][j] = val
					s[i+1][j] = k
				}
			}
		}
	}

	return m[0][len(p)-1], s
}

func printMatrix(s [][]int, i, j int) {
	if i == j {
		fmt.Printf("A%d", i)
		// fmt.Printf("(%d %d)\n", i, j)
	} else {
		if i <= s[i][j] && s[i][j] <= j {
			// fmt.Printf("(%d %d) -> (%d %d), (%d %d)\n", i, j, i, s[i][j], s[i][j]+1, j)
			fmt.Printf("(")
			printMatrix(s, i, s[i][j])
			printMatrix(s, s[i][j]+1, j)
			fmt.Printf(")")
		}
	}
}

func printS(s [][]int) {
	for i := range s {
		for j := range s[i] {
			fmt.Printf("%d ", s[i][j])
		}
		fmt.Println()
	}
}

func main() {
	p := []int{30, 35, 15, 5, 10, 20, 25}
	start := time.Now()
	fmt.Printf("recursive = %d (%d ns)\n", recursive(p, 0, len(p)-1), time.Since(start).Nanoseconds())
	start = time.Now()
	cost, s := dp(p)
	fmt.Printf("dp = %d (%d ns)\n", cost, time.Since(start).Nanoseconds())
	printS(s)
	printMatrix(s, 1, len(p)-1)
}
