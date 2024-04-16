package rbtree

func (T *RBTree) Insert(val int) {
	z := &Node{
		Value: val,
		Color: RED,
		Left:  T.Nil,
		Right: T.Nil,
	}

	// insert z into what it should be
	// y is the previous node of x
	x := T.Root
	var y *Node = T.Nil

	for x != T.Nil {
		y = x
		if z.Value < x.Value {
			x = x.Left
		} else {
			x = x.Right
		}
	}

	z.P = y

	if y == T.Nil {
		// if there is no node in the tree
		T.Root = z
	} else if z.Value < y.Value {
		y.Left = z
	} else {
		y.Right = z
	}

	T.Insert_fixup(z)
}

func (T *RBTree) Insert_fixup(z *Node) {
	// z is red, so if z.P.Color is red, there is an error to be fixed
	for z.P.Color == RED {
		if z.P == z.P.P.Left {
			// z.P is a left child
			y := z.P.P.Right // y is z's uncle
			if y.Color == RED {
				// Case 1: z's uncle is red
				z.P.Color = BLACK
				y.Color = BLACK
				z.P.P.Color = RED
				z = z.P.P // check the grandparent
			} else {
				// z's uncle is black
				// Case 2: if z is a right child
				if z == z.P.Right {
					z = z.P
					T.LeftRotate(z)
				}
				// Case 3 and continue Case 2
				z.P.Color = BLACK
				z.P.P.Color = RED
				T.RightRotate(z.P.P)
			}
		} else {
			// z.P is a right child
			y := z.P.P.Left // y is z's uncle
			if y.Color == RED {
				// Case 1: z's uncle is red
				z.P.Color = BLACK
				y.Color = BLACK
				z.P.P.Color = RED
				z = z.P.P // check the grandparent
			} else {
				// z's uncle is black
				// Case 2: if z is a left child
				if z == z.P.Left {
					z = z.P
					T.RightRotate(z)
				}
				// Case 3 and continue case 2
				z.P.Color = BLACK
				z.P.P.Color = RED
				T.LeftRotate(z.P.P)
			}
		}
	}
	T.Root.Color = BLACK
}
