n = int(input())
data = input()
k = int(input())
numbers = list(map(int, data.split()))
maxim = max(numbers)
count_of_number = [0]*(maxim+1)
for i in numbers:
    count_of_number[i] += 1
flag = 1
for i in range(len(count_of_number)):
    if count_of_number[i] == k:
        print(i, end=' ')
        flag = 0
if flag:
    print(0)
