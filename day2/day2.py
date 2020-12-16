with open("input.txt") as f:
    list2 = f.readlines()
    lgt = len(list2)
    gesamt = 0
    for x in range(lgt):
        lower = list2[x].split("-")[0]
        upper = list2[x].partition(" ")[0].partition("-")[2]
        character = list2[x].split(":")[0].partition(" ")[2]
        password = list2[x].split(": ")[1].partition("\n")[0]
        #print(lower,upper,character,password)
        pwdr = len(password)
        if password.count(character) >= int(lower) and password.count(character) <= int(upper):
            gesamt = gesamt + 1
                
        
                    
                    
        #print(password)
    print(gesamt)        
    print("done")
