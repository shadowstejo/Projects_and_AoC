#6169 too low
#6170.....

with open('answers.txt') as f:
    asdf = f.read()
    groups = asdf.split("\n\n")
    answer = 0
    for group in groups:
        clean = group.replace("\n", "")
        answer =  answer + len(set(clean))
    print(answer)
