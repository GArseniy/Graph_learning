table = []
for i in range(8):
    table.append(input())
bool_table = []
for i in range(8):
    bool_table.append([])
    for j in range(8):
        bool_table[i].append(1)
for i in range(8):
    for j in range(8):
        if table[i][j] == 'R':
            for x in range(8):
                bool_table[x][j] = 0
            for y in range(8):
                bool_table[i][y] = 0
        if table[i][j] == 'B':
            for x in range(8):
                for y in range(8):
                    if abs(x-i) == abs(y-j):
                        bool_table[x][y] = 0
summa = 0
for i in range(8):
    summa += sum(bool_table[i])
print(summa)
