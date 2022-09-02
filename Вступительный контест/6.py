counts = list(map(int, (input().split())))
N = counts[0]
M = counts[1]
arr = [0] * N
for it in range(M):
    line = input()
    data = list(map(int, line.split()))
    if data[0] == 1:
        for i in range(data[1], data[2]):
            arr[i] += data[3]
    else:
        summa = 0
        for i in range(data[1], data[2]):
            summa += arr[i]
        print(summa)
