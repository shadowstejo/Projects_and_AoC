x_liste = [1, 3, 5, 7, 1] #rechtsverschiebungen
y_liste = [1, 1, 1, 1, 2] #linksverschiebungen

def calc_trees(right, down, lines):
    x = right
    y = down
    baum = 0
    while y < len(lines):
        if x > len(lines[y]) - 1:
            x = x % len(lines[y])
        if lines[y][x] == '#':
            baum += 1
        x += right
        y += down
    return baum

with open('treeslope.txt') as f:
    lines = [line for line in f]
    lines = [list(line.rstrip()) for line in lines]
    
    print(calc_trees(3,1,lines)) #berechnet(und printet) 3,1
    
    all_trees = 1
    for (right, down) in zip(x_liste, y_liste): #mit zip nimmt er je ein argument.
        all_trees *= calc_trees(right, down, lines) #lines unverändert, x,y aus listen

    print(all_trees)
