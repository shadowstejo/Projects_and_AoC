#import sys
#
#with open('input.txt') as f:
 #   zahlen = f.read().split("\n")
  #  counted = [50,32,17,18,6,12,24,43,14,40,15,25,19,22,44,41,30,21,7,31,35,38,28,46,1]
   # counted2 = [50,32,17,18,6,12,24,43,14,40,15,25,19,22,44,41,30,21,7,31,35,38,28,46,1]
    #count = 0
    #countedcount = 0
    #for zahl in zahlen:
     #       for x,y in zip(counted,counted2):
      #          if zahl != x + y:
       #             print(zahl)
        #            sys.exit()
         #       else:
          #          counted.append(zahl)
           #         counted2.append(zahl)
            #        del counted[0]
             #       del counted2[0]

f = open("input.txt")
zahlen = f.read().strip().split('\n')
zahlen = [int(n) for n in zahlen]
counted = []

def checknum(ergebnis, group):
    for i in range(len(group)):
        for j in range(len(group)):
            if i != j:
                if group[i]+group[j] == ergebnis:
                    return True
    return False

def part1():
    for k in range(25, len(zahlen)):
        ergebnis = zahlen[k]
        group = zahlen[k-25:k]
        if not checknum(ergebnis, group):
            return ergebnis

def part2(ergebnis):
    for m in zahlen:
        if sum(counted) >= ergebnis:
            for n in range(len(counted)):
                if sum(counted[n:]) == ergebnis and len(counted[n:])>1:
                    return min(counted[n:]) + max(counted[n:])
            del counted[0]
            counted.append(m)
        elif sum(counted) < ergebnis:
            counted.append(m)


print(part1())
print(part2(part1()))
