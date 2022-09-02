from functools import lru_cache


@lru_cache(None)
def rec(number):
    if number == 0:
        return [[]]
    if number == 1:
        return [[1]]
    result = []
    for i in range(number):
        pred = rec(i)
        for j in range(len(pred)):
            if pred[j] and number - i < pred[j][0]:
                continue
            copy = [number - i] + pred[j]
            result.append(copy)
    return result


n = int(input())
arr = rec(n)
for i in range(len(arr)):
    print(*(arr[len(arr) - i - 1]))
