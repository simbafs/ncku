nil = None
RED = "red"
BLACK = "black"


class Node:
    def __init__(self, key):
        self.key = key
        self.left = nil
        self.right = nil
        self.p = nil
        self.color = RED


nil = Node(None)
nil.color = BLACK
nil.left = nil
nil.right = nil
nil.p = nil


class RedBlackTree:
    def __init__(self):
        self.nil = nil
        self.root = self.nil


def left_rotate(T, x):
    y = x.right
    x.right = y.left
    if y.left != T.nil:
        y.left.p = x
    y.p = x.p
    if x.p == T.nil:
        T.root = y
    elif x == x.p.left:
        x.p.left = y
    else:
        x.p.right = y
    y.left = x
    x.p = y


def right_rotate(T, x):
    y = x.left
    x.left = y.right
    if y.right != T.nil:
        y.right.p = x
    y.p = x.p
    if x.p == T.nil:
        T.root = y
    elif x == x.p.right:
        x.p.right = y
    else:
        x.p.left = y
    y.right = x
    x.p = y


def RB_insert(T, z):
    x = T.root
    y = T.nil
    while x != T.nil:
        y = x
        if z.key < x.key:
            x = x.left
        else:
            x = x.right
    z.p = y
    if y == T.nil:
        T.root = z
    elif z.key < y.key:
        y.left = z
    else:
        y.right = z
    z.left = T.nil
    z.right = T.nil
    z.color = RED
    RB_insert_fixup(T, z)


def RB_insert_fixup(T, z):
    while z.p.color == RED:
        if z.p == z.p.p.left:
            y = z.p.p.right
            if y.color == RED:
                z.p.color = BLACK
                y.color = BLACK
                z.p.p.color = RED
                z = z.p.p
            else:
                if z == z.p.right:
                    z = z.p
                    left_rotate(T, z)
                z.p.color = BLACK
                z.p.p.color = RED
                right_rotate(T, z.p.p)
        else:
            y = z.p.p.left
            if y.color == RED:
                z.p.color = BLACK
                y.color = BLACK
                z.p.p.color = RED
                z = z.p.p
            else:
                if z == z.p.left:
                    z = z.p
                    right_rotate(T, z)
                z.p.color = BLACK
                z.p.p.color = RED
                left_rotate(T, z.p.p)
    T.root.color = BLACK


def print_tree(x):
    if x != nil:
        print(f"{x.key} {x.color} -> ({x.left.key}, {x.right.key})")
        print_tree(x.left)
        print_tree(x.right)


def preorder_tree_walk(x, s=""):
    if x != nil:
        s += f"{x.key} {x.color}\n"
        s = preorder_tree_walk(x.left, s)
        s = preorder_tree_walk(x.right, s)
    return s


def matrix_file(input, output):
    with open(input, "r") as f:
        lines = f.readlines()

    nodes = [int(line.strip()) for line in lines[1:]]

    T = RedBlackTree()
    for node in nodes:
        z = Node(node)
        RB_insert(T, z)

    # print_tree(T.root)
    print(preorder_tree_walk(T.root))

    with open(output, "w") as f:
        f.write(preorder_tree_walk(T.root))


matrix_file("input.txt", "output.txt")
