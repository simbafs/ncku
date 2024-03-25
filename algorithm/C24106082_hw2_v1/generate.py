import random

result = list(range(1, 5001))

random.shuffle(result)

with open("random.txt", "w") as f:
    f.write(str(len(result)) + "\n")
    for i in result:
        f.write(str(i) + "\n")
