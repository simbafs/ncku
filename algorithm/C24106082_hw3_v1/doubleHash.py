def h1(k, m):
    return k % m


def h2(k, mm):
    return 1 + k % mm


def h(k, i, m, mm):
    return (h1(k, m) + i * h2(k, mm)) % m

def h_file(input, output):
    with open(input, 'r') as f:
        lines = f.readlines()
    
    m, mm, n = [int(num_str.strip()) for num_str in lines[0].split(',')]
    ks = [int(line.strip()) for line in lines[1:]]

    hasheds = []
    Is = []
    for k in ks:
        i = 0
        while True:
            hashed = h(k, i, m, mm)
            if hashed not in hasheds:
                hasheds.append(hashed)
                Is.append(i)
                break
            i += 1

    # print(sum(Is)/len(Is))

    with open(output, 'w') as f:
        f.write(f"{m},{mm},{n}\n")
        for hashed, i in zip(hasheds, Is):
            f.write(f"{hashed}, {i}\n")

h_file('input.txt', 'output.txt')
