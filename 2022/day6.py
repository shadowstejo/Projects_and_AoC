#!/usr/bin/python3


def part01(inputfile):
    with open(inputfile) as f:
        alles = f.read()
        #print(alles)
        index = 0
        for x in range(0,len(alles)):
            if x == 4090:
                break
            else:
                if(alles[x]!=alles[x+1] and alles[x]!=alles[x+2] and alles[x]!=alles[x+3]):
                    if(alles[x+1]!=alles[x+2] and alles[x+1]!=alles[x+3]):
                        if(alles[x+2]!=alles[x+3]):
                            print("found",x+4)
                            break
                else:
                    x+=1

# Python program to illustrate string
# with unique characters using
# brute force technique

def uniqueCharacters(str):
	
	# If at any time we encounter 2
	# same characters, return false
	for i in range(len(str)):
		for j in range(i + 1,len(str)):
			if(str[i] == str[j]):
				return False;

	# If no duplicate characters
	# encountered, return true
	return True;


def part02(inputfile):
    with open(inputfile) as f:
        alles = f.read()
        checksum = 0
        teststring = ""
        for x in range(0,len(alles)):
            if x== 4080:
                break
            else:
                teststring += alles[x:x+13]
            if uniqueCharacters(teststring):
                print("found",x+13)
            else:
                teststring = ""
part01('input.txt')
part02('input.txt')
