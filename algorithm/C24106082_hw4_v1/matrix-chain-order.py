def matrix_chain(p, n):
    m = [[0.0 for _ in range(n + 1)] for _ in range(n + 1)]
    s = [[0.0 for _ in range(n + 1)] for _ in range(n + 1)]

    for l in range(2, n + 1):
        # print(f"{l = }")
        for i in range(1, n - l + 1 + 1):
            # print(f"{i = }")
            j = i + l - 1
            m[i][j] = float("inf")
            for k in range(i, j - 1 + 1):
                # print(f"{i = }, {j = }, {k = }, {l = }")
                # print(
                #     f"{m[i][k] = }, {m[k + 1][j] = }, {p[i - 1] = }, {p[k] = }, {p[j] = }"
                # )
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]
                # print(f"{q = }, {m[i][j] = }")
                # print()
                if q < m[i][j]:
                    m[i][j] = q
                    s[i][j] = k

    return m, s


# return matrix chain in string S
def print_matrix_chain(s, i, j, S):
    if i == j:
        S += f"A{i}"
    else:
        S += "("
        S = print_matrix_chain(s, i, s[i][j], S)
        S = print_matrix_chain(s, s[i][j] + 1, j, S)
        S += ")"
    return S


def matrix_file(input, output):
    with open(input, "r") as f:
        lines = f.readlines()

    p = [int(line.strip()) for line in lines]

    # print(p)
    m, s = matrix_chain(p, len(p) - 1)
    # for r in m:
    #     for c in r:
    #         print(f"{c:.2f}", end="\t")
    #     print()
    #
    # print()
    #
    # for r in s:
    #     for c in r:
    #         print(f"{c:.2f}", end="\t")
    #     print()
    print(int(m[1][len(p) - 1]))
    print(print_matrix_chain(s, 1, len(p) - 1, ""))

    with open(output, "w") as f:
        f.write(f"{int(m[1][len(p) - 1])}\n")
        f.write(f'{print_matrix_chain(s, 1, len(p) - 1, "")}\n')


matrix_file("input.txt", "output.txt")
