file = open("day7.txt")
vls = []
def cardVal(card):
    cardTypes = ["J", "2", "3", "4", "5", "6", "7", "8", "9", "T", "Q", "K", "A"]
    return cardTypes.index(card)

def countOccurrences(cards, card, joker = True):
    ret = 0
    for x in cards:
        if x == card or (x == "J" and joker):
            ret += 1
    return ret

def handType(cards):
    for c in cards:
        c = countOccurrences(cards, c)
        if c == 5:
            return 6
    for c in cards:
        c = countOccurrences(cards, c)
        if c == 4:
            return 5
    gotta2 = False
    gotta3 = False
    jokingFullhouse = True
    jokerLeftover = True
    tried = []
    for c in cards:
        if c in tried:
            continue
        tried.append(c)
        if c == "J":
            continue
        if countOccurrences(cards, c, jokerLeftover) == 2:
            gotta2 = True
            jokerLeftover = False
            continue
        if countOccurrences(cards, c, jokerLeftover) == 3:
            gotta3 = True
            jokerLeftover = False
        else:
            jokingFullhouse = False
    #print(cards, "gotta 2:", gotta2, "gotta 3:", gotta3, "joker leftover?", jokerLeftover, "joker fullhouse?", jokingFullhouse)
    if (gotta2 and gotta3) or (gotta3 and jokingFullhouse):
        return 4
    for c in cards:
        if countOccurrences(cards, c) == 3:
            return 3
        if countOccurrences(cards, c) > 3:
            print("==== FATAL ERROR 2:", cards)
    ## magic.
    pairs = 0
    leftovers = None
    jokerLeftover = True
    tried = []
    for c in cards:
        if c in tried:
            continue
        tried.append(c)
        if countOccurrences(cards, c, jokerLeftover) == 2:
            pairs += 1
            jokerLeftover = False
            if c == "J":
                print("==== FATAL ERROR:", cards)
        else:
            leftovers = c
    return pairs
    
for line in file.readlines():
    lineS = line.split(" ")
    cards = lineS[0]
    bid = int(lineS[1])
    val = handType(cards) * (13 ** 5) + cardVal(cards[0]) * (13 ** 4) + cardVal(cards[1]) * (13 ** 3) + cardVal(cards[2]) * (13 ** 2) + cardVal(cards[3]) * 13 + cardVal(cards[4])
    vls.append([cards, bid, val, handType(cards)])

vls.sort(key = lambda x: x[2])
ret = 0
for x in range(0, len(vls)):
    print(vls[x])
    ret += (x + 1) * vls[x][1]
print(ret)

## ERRONEOUS VALUE: 249115150 (Too Low)
## ERRONEOUS VALUE: 249577091 (Unknown)
## ERRONEOUS VALUE: 249600833 (Unknown)
## ERRONEOUS VALUE: 249319479 (Unknown)
## ERRONEOUS VALUE: 249446523 (Unknown)
