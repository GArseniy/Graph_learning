n = int(input())
data = input()
k = int(input())
numbers = list(map(int, data.split()))
numbers.sort()
length = 1
flag = 1
for i in range(n - 1):
    if numbers[i] == numbers[i+1]:
        length += 1
    else:
        if length == k:
            print(numbers[i], sep=' ')
            flag = 0
        length = 1
if length == k:
    print(numbers[n-1], sep=' ')
    flag = 0
if flag:
    print(0)
