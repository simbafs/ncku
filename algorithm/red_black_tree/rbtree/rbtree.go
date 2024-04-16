package rbtree

import "fmt"

type RBTree struct {
	Root *Node
	Nil  *Node
}

type Color string

const (
	RED   Color = "R"
	BLACK Color = "B"
)

type Node struct {
	Value int
	Left  *Node
	Right *Node
	P     *Node
	Color Color
}

func (T *RBTree) print(level int, n *Node) {
	if n == T.Nil {
		return
	}
	T.print(level+1, n.Right)
	fmt.Printf("%*s%d(%s)\n", level*4, "", n.Value, n.Color)
	T.print(level+1, n.Left)
}

func (T *RBTree) Print() {
	fmt.Println("---------")
	T.print(0, T.Root)
	fmt.Println("---------")
}

func NewRBTRee() *RBTree {
	Nil := &Node{
		Value: 0,
		Color: BLACK,
	}
	return &RBTree{
		Root: Nil,
		Nil:  Nil,
	}
}
