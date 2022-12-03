#!/usr/bin/python3

def part01(fileopen):
    with open(fileopen) as f:
        maxbatch = 0
        currentbatch = 0
        for line in f:
            if line != '\n':
                currentbatch += int(line)
                if currentbatch > maxbatch:
                    maxbatch = currentbatch
            else:
                currentbatch = 0   
        print(maxbatch)
def part02(fileopen):
    with open(fileopen) as f:
        mb = 0
        mb2 = 0
        mb3 = 0
        current = 0
        grandtotal= 0
        for line in f:
            if line!='\n':
                current += int(line)
                if current >= mb:
                    mb3 = mb2
                    mb2 = mb
                    mb = current
                elif current >= mb2:
                    mb3 = mb2
                    mb2 = current
                elif current >= mb3:
                    mb3 = current
            else:
                current = 0
        grandtotal += mb3+mb2+mb
        print(mb,mb2,mb3,grandtotal)
        
part01('input.txt')
part02('input.txt')
