table = []
for i in range(8):
    table.append(input())
breaking = 0
summa = 0
for i in range(8):
    for j in range(8):
        # Ладьи в вертикалях и горизонталях
        for k in range(8):
            if table[i][k] == 'R':
                breaking = 1
                break
        if breaking:
            breaking = 0
            continue
        for k in range(8):
            if table[k][j] == 'R':
                breaking = 1
                break
        if breaking:
            breaking = 0
            continue
        # Слоны по диагоналям
        minim_i_j = min(i, j)
        copy_i = i - minim_i_j
        copy_j = j - minim_i_j
        while (copy_i < 8) and (copy_j < 8):
            if table[copy_i][copy_j] == 'B':
                breaking = 1
                break
            copy_i += 1
            copy_j += 1
        if breaking:
            breaking = 0
            continue
        copy_i = i
        copy_j = j
        while copy_i < (8 - 1) and copy_j > 0:
            copy_i += 1
            copy_j -= 1
        while copy_i >= 0 and copy_j < 8:
            if table[copy_i][copy_j] == 'B':
                breaking = 1
                break
            copy_i -= 1
            copy_j += 1
        if breaking:
            breaking = 0
            continue
        summa += 1
print(summa)
