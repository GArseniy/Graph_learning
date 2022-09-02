with open("input1.txt") as f:
    x, y = list(map(int, f.readline().split()))
    table = [[]] * y
    for j in range(y):
        row = f.readline()
        table[j] = [[]] * x
        for i in range(x):
            table[j][i] = row[i]
print(*table, sep='\n')


adjacency_list = [[]] * (x*y)
for j in range(y):
    for i in range(x):
        if table[j][i] != '#':
            adjacency_list[j * x + i] = []
            if i + 1 < x and table[j][i + 1] != '#':
                adjacency_list[j * x + i].append(j * x + i + 1)
            if i - 1 >= 0 and table[j][i - 1] != '#':
                adjacency_list[j * x + i].append(j * x + i - 1)
            if j + 1 < y and table[j + 1][i] != '#':
                adjacency_list[j * x + i].append((j + 1) * x + i)
            if j - 1 >= 0 and table[j - 1][i] != '#':
                adjacency_list[j * x + i].append((j - 1) * x + i)
for i in range(len(adjacency_list)):
    print(i, ":\t", adjacency_list[i], sep='')


