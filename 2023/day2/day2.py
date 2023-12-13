#!/usr/bin/python3

def part1(file,red,green,blue):
    total = 0
    maxred = red
    maxgreen = green
    maxblue = blue
    with open(file) as f:
        games = f.read().split("\n")
        for game in games:
            draws = game.split(";")
                #das kriegt grade das letzte game als: ['Game 100: 1 red, 1 green, 9 blue', ' 6 blue, 4 green, 3 red',' 2 red' ...]
            for draw in draws:
                color = draw.split(",")
                #kill the "Game ###" before first draw
                #if "Game" in draw:
                    
                    

    print("Part 1 ist:",total,draws)



part1('input.txt',12,13,14)
