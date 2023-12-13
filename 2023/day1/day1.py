#!/usr/bin/python3

def part1(file):
    numbers = ["0","1","2","3","4","5","6","7","8","9"]
    with open(file) as f:
        total = 0
        lines = f.read().split("\n")
        for line in lines:
            firstnumb = 0
            lastnumb = 0
            for char in line:
                if char in numbers :
                    total += int(char) * 10
                    break
            for char in line[::-1]:
                if char in numbers:
                    total += int(char)
                    break                
    print("Part 1 ist:", total)

def part2(file):
    numbers = ["0","1","2","3","4","5","6","7","8","9"]
    spellt = {"one":1, "two":2, "three":3, "four":4, "five":5, "six":6, "seven":7, "eight":8, "nine":9}
    sprev = {"eno":1,"owt":2,"eerht":3,"ruof":4,"evif":5,"xis":6,"neves":7,"thgie":8,"enin":9}


    with open(file) as f:
        total = 0
        lines = f.read().split("\n")
        for line in lines:
            for zahl in spellt:
                if zahl in line:
                    

                    total += spellt[zahl]
                    break
            for zahl in sprev:
                if zahl in line[::-1]:
                    total += sprev[zahl]

    print("Part 2 ist:", total,"noch falsch")

part1('input.txt')
part2('input.txt')
