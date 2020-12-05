with open(r"C:\Users\Steppo\Projekte\pyth\adventofcode\day2\input.txt", "r") as f:
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
        if pwdr >= int(upper):
            a = password[int(lower)-1] == character
            b = password[int(upper)-1] == character
            if (a or b) and not (a and b):
                gesamt = gesamt + 1
                
        
                    
                    
        #print(password)
    print(gesamt)        
    print("done")
