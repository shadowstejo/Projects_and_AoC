#!/usr/bin/python3

def part01(fileopen):  #first attempt
    with open(fileopen) as f:
        a = 'A'
        b = 'B'
        c = 'C'
        y = 'Y'
        x = 'X'
        z = 'Z'
        total = 0
        for line in f:
            if (a in line) & (x in line):
                total += 4
            elif (a in line) & (y in line):
                total += 8
            elif (a in line) & (z in line):
                total += 3
            elif (b in line) & (x in line):
                total += 1
            elif (b in line) & (y in line):
                total += 5
            elif (b in line) & (z in line):
                total += 9
            elif (c in line) & (x in line):
                total +=7
            elif (c in line) & (y in line):
                total += 2
            elif (c in line) & (z in line):
                total += 6
            else:
                print("error im code")
        print(total)

def part02(fileopen):  #also first try
    with open(fileopen) as f:
        a = 'A'
        b = 'B'
        c = 'C'
        y = 'Y'
        x = 'X'
        z = 'Z'
        total = 0
        for line in f:
            if (a in line) & (x in line): #rock, lose -> rock vs scicc = 3
                total += 3
            elif (a in line) & (y in line): #rock, draw -> 4
                total += 4
            elif (a in line) & (z in line): #rock, win -> paper, win 8
                total += 8
            elif (b in line) & (x in line): #paper, lose -> 1
                total += 1
            elif (b in line) & (y in line): #paper, draw -> 5
                total += 5
            elif (b in line) & (z in line): #paper, win -> 9
                total += 9
            elif (c in line) & (x in line): #scic, lose -> 2
                total +=2
            elif (c in line) & (y in line): #scic, draw -> 6
                total += 6
            elif (c in line) & (z in line): #scic, win -> 7
                total += 7
            else:
                print("error im code")
        print(total)


part01('input.txt')
part02('input.txt')
