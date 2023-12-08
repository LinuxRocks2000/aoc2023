file = open("day7.txt")
vls = []
def cardVal(card):
    cardTypes = ["2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"]
    return cardTypes.index(card)

def countOccurrences(cards, card):
    ret = 0
    for x in cards:
        if x == card:
            ret += 1
    return ret

def handType(cards):
    if countOccurrences(cards, cards[0]) == 5:
        return 6
    if countOccurrences(cards, cards[0]) == 4 or countOccurrences(cards, cards[1]) == 4:
        return 5
    gotta2 = False
    gotta3 = False
    for c in cards:
        if countOccurrences(cards, c) == 2:
            gotta2 = True
        if countOccurrences(cards, c) == 3:
            gotta3 = True
    if gotta2 and gotta3:
        return 4
    for c in cards:
        if countOccurrences(cards, c) == 3:
            return 3
    ## magic.
    pairs = 0
    for c in cards:
        if countOccurrences(cards, c) == 2:
            pairs += 1
    return pairs/2
    
for line in file.readlines():
    lineS = line.split(" ")
    cards = lineS[0]
    bid = int(lineS[1])
    val = handType(cards) * (13 ** 5) + cardVal(cards[0]) * (13 ** 4) + cardVal(cards[1]) * (13 ** 3) + cardVal(cards[2]) * (13 ** 2) + cardVal(cards[3]) * 13 + cardVal(cards[4])
    vls.append([cards, bid, val])

vls.sort(key = lambda x: x[2])
ret = 0
for x in range(0, len(vls)):
    ret += (x + 1) * vls[x][1]
print(ret)
