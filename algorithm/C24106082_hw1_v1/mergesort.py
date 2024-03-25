def merge(left, right):
    sorted_list = []
    l = r = 0

    while l < len(left) and r < len(right):
        if left[l] < right[r]:
            sorted_list.append(left[l])
            l += 1
        else:
            sorted_list.append(right[r])
            r += 1

    if l < len(left):
        sorted_list.extend(left[l:])

    if r < len(right):
        sorted_list.extend(right[r:])

    return sorted_list


def mergeSort(arr):
    if len(arr) <= 1:
        return arr

    middle = len(arr) // 2

    left_half = mergeSort(arr[:middle])
    right_half = mergeSort(arr[middle:])

    return merge(left_half, right_half)


def sort_keys_from_file(input, output):
    with open(input, "r") as file:
        lines = file.readlines()
        n = int(lines[0].strip())
        keys = [int(line.strip()) for line in lines[1 : n + 1]]

    sorted_keys = mergeSort(keys)

    with open(output, "w") as file:
        file.write(f"{len(sorted_keys)}\n")
        for key in sorted_keys:
            file.write(f"{key}\n")


sort_keys_from_file("./1.in", "./1.out")
sort_keys_from_file("./2.in", "./2.out")
sort_keys_from_file("./3.in", "./3.out")
sort_keys_from_file("./4.in", "./4.out")
