#!/usr/bin/python3

def part01(inputfile): #second try, missed the 'break' to stop for the line.
    with open(inputfile) as f:
        total = 0
        for line in f:
            rucksack = line
            comp1 = rucksack[:len(line)//2]
            comp2 = rucksack[len(line)//2:]
            for x in comp1:
                if x in comp2:
                    #print(x,rucksack)
                    if (ord(x) >= 65) & (ord(x) <= 90):
                        total += ord(x)-38
                        break
                    elif (ord(x) >= 97) & (ord(x) <=122):
                        total += ord(x)-96
                        break
    print("part01 =", total)

           
def part02(inputfile): #first try
    with open(inputfile) as f:
        total = 0
        count = 0
        currentrucksack = []
        for line in f: #constructing rucksacks:
            currentrucksack.append(line)
            count+=1
            if count == 3:
                for x in currentrucksack[0]:
                    if (x in currentrucksack[1]) & (x in currentrucksack[2]):
                        if (ord(x) >= 65) & (ord(x) <= 90):
                            total += ord(x)-38
                            break
                        elif (ord(x) >= 97) & (ord(x) <=122):
                            total += ord(x)-96
                            break
                currentrucksack = []
                count = 0          
        print("part02 =", total)

part01('input.txt')
part02('input.txt')
