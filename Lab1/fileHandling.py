file = open("fileHandling.txt","r")
match_word = "engineering"
count = 0
for i in file:
    i = i.lower()
    count += i.count(match_word)
print(f'{match_word} appeared {count} times')