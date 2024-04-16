package main

import "rbtree/rbtree"

func main() {
	// construct a new rbtree with 1,2,3,4,5,6
	T := rbtree.NewRBTRee()

	T.Insert(1)
	T.Insert(2)
	T.Insert(3)
	T.Insert(4)
	T.Insert(5)
	T.Insert(6)
	T.Insert(7)
	T.Insert(8)
	T.Print()
}
