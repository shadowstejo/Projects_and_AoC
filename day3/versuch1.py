import math
with open('treeslope.txt') as f:
    lines = f.readlines()
    x = 3
    y = 1
    trees = 0
    while y < len(lines):
        if x > len(lines[y]) - 1:
            x = x % len(lines[y])
        if lines[y][x] == '#':
            trees += 1
        x += 3
        y += 1
    print(trees)



    lines = [line for line in f]
    height = len(lines)
    width = len(lines[0])
    lines = [list(line.rstrip()) for line in lines]


    all_trees = 1
    for (x, y) in zip(right_list, down_list):
        all_trees *= calc_trees(right, down, lines)

    print(all_trees)
