with open('input.txt') as f:
    string = f.read()
    floor = 0
    counted = 0
    for char in string:
        if char == '(':
            floor += 1
            counted += 1
        elif char == ')':
            floor -= 1
            counted += 1
        else:
            floor = floor
            counted += 1
        if floor == -1: #breaks if floor == -1
            print(counted) 
            break
    print(floor)
        
