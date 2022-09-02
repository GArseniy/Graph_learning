n = int(input())
time = 9 * 60 + 0
time += 45
for i in range(1, n):
    time += 45
    if i % 2 == 0:
        time += 15
    else:
        time += 5
print(time // 60, time % 60)
