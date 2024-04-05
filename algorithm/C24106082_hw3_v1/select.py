def swap(arr, i, j):
    arr[i], arr[j] = arr[j], arr[i]


def partition_around(arr, p, r, x):
    i = p - 1
    for j in range(p, r + 1):
        if arr[j] == x:
            swap(arr, j, r)
            break
    x = arr[r]
    for j in range(p, r):
        if arr[j] <= x:
            i += 1
            swap(arr, i, j)
    swap(arr, i + 1, r)
    return i + 1


def select(arr, p, r, i):
    while (r - p + 1) % 5 != 0:
        for j in range(p + 1, r + 1):
            if arr[p] > arr[j]:
                swap(arr, p, j)
        if i == 1:
            return arr[p]
        p += 1
        i -= 1

    group = (r - p + 1) // 5
    for j in range(p, p + group):
        sub_arr = arr[j : j + 5]
        sub_arr.sort()
        arr[j : j + 5] = sub_arr

    x = select(arr, p + 2 * group, p + 3 * group - 1, (group + 1) // 2)
    q = partition_around(arr, p, r, x)
    k = q - p + 1
    if i == k:
        return arr[q]
    elif i < k:
        return select(arr, p, q - 1, i)
    else:
        return select(arr, q + 1, r, i - k)


def select_file(input, output):
    with open(input, "r") as f:
        lines = f.readlines()

    n = int(lines[0].strip())
    keys = [int(line.strip()) for line in lines[1:]]

    result = select(keys, 0, len(keys) - 1, n // 2)

    with open(output, "w") as f:
        f.write(f"{result}\n")


select_file("input.txt", "output.txt")
