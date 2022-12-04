#!/usr/bin/python3

def part01(inputfile): #first try 11388 - too high | second try: 473: too low #maximum 1000 | in the end it was close with 524, didn't transform them to int()'s ....
    with open(inputfile) as f:
        total = 0
        for line in f:
            d = line.replace(',','-').split('-') #make it easier
            
            section_one = line.split(",")[0]
            section_two = line.split(",")[1]   #easier than all of this here...
            sof=int(section_one.split("-")[0])
            sos=int(section_one.split("-")[1])
            stf=int(section_two.split("-")[0]) #missed int(..) in the beginning. this now works
            sts=int(section_two.split("-")[1])

            if((sof >= stf)&(sos<=sts)): #first case where section_one is in section_two
               total += 1
            elif((stf >=sof)&(sts <=sos)): #second case, where section_two is in section_one
                total += 1
            else:
               total=total
                
        return total

def part02(inputfile):
    with open(inputfile) as f:
        total = 0
        for line in f:
            d = line.replace(',','-').split('-')
            
            section_one = line.split(",")[0]
            section_two = line.split(",")[1]
            sof=int(section_one.split("-")[0])
            sos=int(section_one.split("-")[1])
            stf=int(section_two.split("-")[0])
            sts=int(section_two.split("-")[1])
            if((stf <=sos) & (stf >= sof)):
                total +=1
            elif((sts <=sos)&(sts>=sof)):
                total +=1
            elif((sof <=sts)&(sof >=stf)):
                total +=1
            elif ((sos<=sts)&(sos >=stf)):
                total +=1
    return total

print("part 1 =", part01('input.txt'))
print("part 2 =", part02('input.txt'))
