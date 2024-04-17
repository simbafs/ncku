package main

import (
	"fmt"
	"time"
)

func recursive(X, Y string) int {
	x := len(X) - 1
	y := len(Y) - 1
	if x == -1 || y == -1 { // if one string is empty
		return 0
	}

	// fmt.Printf("%s, %s\n", X, Y)

	if X[x] == Y[y] {
		return recursive(X[:x], Y[:y]) + 1
	} else {
		return max(
			recursive(X[:x], Y),
			recursive(X, Y[:y]),
		)
	}
}

const (
	DIAGONAL = iota
	UP
	LEFT
)

func dp(X, Y string) (int, [][]int) {
	X = " " + X
	Y = " " + Y
	c := make([][]int, len(X))
	s := make([][]int, len(X))
	for k := range c {
		c[k] = make([]int, len(Y))
		s[k] = make([]int, len(Y))
	}

	for x := 1; x < len(X); x++ {
		for y := 1; y < len(Y); y++ {
			if X[x] == Y[y] {
				c[x][y] = c[x-1][y-1] + 1
				s[x][y] = DIAGONAL
			} else {
				if c[x-1][y] > c[x][y] {
					c[x][y] = c[x-1][y]
					s[x][y] = UP
				} else {
					c[x][y] = c[x][y-1]
					s[x][y] = LEFT
				}
			}
		}
	}

	return c[len(X)-1][len(Y)-1], s
}

func printLCS(X, Y string, s [][]int) {
	fmt.Printf("  ")
	for _, y := range Y {
		fmt.Printf("%c ", y)
	}
	fmt.Println()
	for _, row := range s {
		for _, col := range row {
			switch col {
			case DIAGONAL:
				fmt.Printf("\\ ")
			case UP:
				fmt.Printf("| ")
			case LEFT:
				fmt.Printf("- ")

			}
		}
		fmt.Println()
	}

	x := len(X) 
	y := len(Y) 
	for x > 0 && y > 0 {
		switch s[x][y] {
		case DIAGONAL:
			x--
			y--
			fmt.Printf("%c", Y[y])
		case UP:
			x--
		case LEFT:
			y--
		}
	}
	fmt.Println("(reversed)")

}

func main() {
	// X := "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA"
	// Y := "GTCGTTCGGAATGCCGTTGCTCTGTAAA"
	X := "BDCABA"
	Y := "ABCBDAB"

	start := time.Now()
	fmt.Printf("recursive: %d (%d ns)\n",
		recursive(X, Y),
		time.Since(start).Nanoseconds(),
	)
	start = time.Now()
	length, s := dp(X, Y)
	fmt.Printf("dp: %d (%d ns)\n",
		length,
		time.Since(start).Nanoseconds(),
	)
	printLCS(X, Y, s)
}
