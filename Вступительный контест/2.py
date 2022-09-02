s = input()
words = s.split()
answer = words[0]
length = len(answer)
for word in words:
    if len(word) > length:
        length = len(word)
        answer = word
print(answer, length, sep='\n')
