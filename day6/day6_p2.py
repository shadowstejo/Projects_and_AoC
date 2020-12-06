
with open('answers.txt') as f:
    asdf = f.read()
    groups = asdf.split("\n\n")
    answer = 0
    occurences = 0
    for group in groups:
        grouplines = group.split("\n") #einzelne gruppenAntworten
        for string in grouplines: #personenAntworten
            for char in string: #a,b,c,d...Antwort pro person
                if all(char in string for string in grouplines):
                    occurences += 1
                    group.replace(char, "")
                while occurences >= 1:
                    answer += 1
                    occurences = 0
                    string.replace(char, "")
                string.replace(char, "") #Problem, zählt mehrmals pro gruppe. replaced irgendwie nicht.
    print(answer)
        
from collections import Counter ##zählt anzahl an characters

with open('answers.txt') as f:
    gruppen = f.read().strip().split('\n\n')
    answer = 0
    for line in groups:
        answer += sum([len([x for x in Counter(line).values() if x == len(line.split('\n'))])])
    print(answer)                
# problem hier, letzte spalte wird nicht gelesen, da nur 1x linebreak in file.
# added 1 \n at end of file and it works.
