with open("input_numbers.txt") as f:
    list2 = f.readlines()
    lgt = len(list2)
    for x in range(lgt):
        for y in range(lgt):
            for z in range(lgt):
                
                if int(list2[x]) + int(list2[y]) + int(list2[z]) == 2020:
                    print(list2[x],list2[y],list2[z])
                    print(int(list2[x]) * int(list2[y]) * int(list2[z]))
                    break
#first part of day 1 is basically the same, without the [z]-calls :)     