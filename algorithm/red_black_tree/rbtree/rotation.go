package rbtree

//       |                       |
//       y                       x
//      / \       Left          / \
//     x   c     <======       a   y
//    / \        ======>          / \
//   a   b        Right          b   c

func (T *RBTree) LeftRotate(x *Node) {
	// assume y is not Nil
	y := x.Right

	// b
	x.Right = y.Left
	if y.Left != T.Nil {
		y.Left.P = x
	}

	// x.p
	y.P = x.P
	if x.P == T.Nil {
		// x is root
		T.Root = y
	} else if x.P.Left == x {
		// x is a left child of some node
		x.P.Left = y
	} else {
		// x is a right child of some node
		x.P.Right = y
	}

	// x
	x.P = y
	y.Left = x
}

func (T *RBTree) RightRotate(y *Node) {
	// assume x is not Nil
	x := y.Left

	// b
	y.Left = x.Right
	if x.Right != T.Nil {
		x.Right.P = y
	}

	// y.p
	x.P = y.P
	if y.P == T.Nil {
		// y is root
		T.Root = x
	} else if y.P.Left == y {
		// y is a left child of some node
		y.P.Left = x
	} else {
		// y is a right child of some node
		y.P.Right = x
	}

	// y
	y.P = x
	x.Right = y
}
