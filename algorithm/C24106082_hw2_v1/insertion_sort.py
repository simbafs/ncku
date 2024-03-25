def insertion_sort(A):
    for i in range(1, len(A)):
        key = A[i]
        j = i - 1
        while j >= 0 and key < A[j]:
            A[j + 1] = A[j]
            j -= 1
        A[j + 1] = key


def sort_file(inut, output):
    with open(inut, "r") as f:
        lines = f.readlines()

    n = int(lines[0].strip())
    keys = [int(line.strip()) for line in lines[1:]]

    insertion_sort(keys)

    with open(output, "w") as f:
        f.write(f"{n}\n")
        for key in keys:
            f.write(f"{key}\n")


sort_file("input.txt", "output.txt")
