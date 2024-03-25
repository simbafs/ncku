def quicksort(A, p, r):
    if p < r:
        pi = partition(A, p, r)
        quicksort(A, p, pi - 1)
        quicksort(A, pi + 1, r)

def partition(A, p, r):
    pivot = A[r]
    i = p - 1  
    for j in range(p, r):
        if A[j] < pivot:
            i += 1
            A[i], A[j] = A[j], A[i]
    A[i + 1], A[r] = A[r], A[i + 1]
    return i + 1

def quicksort_file(input, output):
    with open(input, 'r') as f:
        lines = f.readlines()
    
    n = int(lines[0].strip())
    keys = [int(line.strip()) for line in lines[1:]]
    
    quicksort(keys, 0, len(keys) - 1)
    
    with open(output, 'w') as f:
        f.write(f"{n}\n")
        for key in keys:
            f.write(f"{key}\n")



quicksort_file('input.txt', 'output.txt')

