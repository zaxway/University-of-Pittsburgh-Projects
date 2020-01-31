import sys, os, csv, collections
from itertools import permutations, combinations

outputFile = sys.argv[2]
supportConstant = sys.argv[3]
confidenceConstant = sys.argv[4]

supportConstant = float(supportConstant)
confidenceConstant = float(confidenceConstant)

def removeDups(oldList):
    newList = []
    for letter in oldList:
        if letter not in newList:
            newList.append(letter)
    return newList

def countLetters(list, sub):
    count = 0
    sub = set(sub)
    for l in list:
        l = set(l)
        if (sub.issubset(l)):
            count = count + 1;
    return count

def readFile():
    input = open(sys.argv[1], 'r') # open the input file to be read
    output = open(outputFile, 'w') # write to the output file
    writer = csv.writer(output, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)

    lines = input.readlines()
    fullList = [] # list for letters in subarrays 2D array
    fullList2 = [] # list for all letters combined, 1D array
    numTransactions = len(lines)
    for line in lines:
        lineArr = [x.strip() for x in line.split(',')]
        i = 0
        subList = [];
        for letter in lineArr:
            if (i >= 1):
                subList.append(letter)
                fullList2.append(letter)
            i = i + 1
        fullList.append(subList)
    # Need a unique list of all letters used
    uniqueLetterList = removeDups(fullList2)
    permStr = ''.join(uniqueLetterList)
    for j in range(1, len(uniqueLetterList) + 1):
        for p in list(combinations(permStr, j)):
            # p is one permuation
            # check how many times p is a subset of fullList
            count = countLetters(fullList, p)
            supportPercent = count / numTransactions
            # check if supportPercent is greater than argument
            if (supportPercent >= supportConstant):
                supportPercent2 = format(supportPercent, '.4f')
                writer.writerow(['S', str(supportPercent2), ''.join(p)])
                print("S, " + str(supportPercent2) + ", " + ''.join(p))

    for j in range (2, len(uniqueLetterList) + 1):
        for p in list(permutations(permStr, j)):
            if (j == 2):
                countFullPerm = countLetters(fullList, p)
                supportPercentFullPerm = countFullPerm / numTransactions # This is supportPercent that we want to include in final output
                countOnePerm = countLetters(fullList, p[0])
                confidencePerm = countFullPerm / countOnePerm
                if (confidencePerm >= confidenceConstant and supportPercentFullPerm >= supportConstant):
                    supportPercentFullPerm2 = format(supportPercentFullPerm, '.4f')
                    confidencePerm2 = format(confidencePerm, '.4f')
                    writer.writerow(['R', str(supportPercentFullPerm2), str(confidencePerm2), p[0], " => ", p[1]])
                    print("R, " + str(supportPercentFullPerm2) + ", " + str(confidencePerm2) + ", " + p[0] + " => " + p[1])
            else:
                countFullPerm = countLetters(fullList, p)
                supportPercentFullPerm = countFullPerm / numTransactions
                for m in range(1, len(p)):
                    initCount = []
                    for n in range(0, m):
                        initCount.append(p[n])
                    countOnePerm = countLetters(fullList, initCount)
                    if (countOnePerm != 0):
                        confidencePerm = countFullPerm / countOnePerm
                        if (confidencePerm >= confidenceConstant and supportPercentFullPerm >= supportConstant):
                            s1 = set(initCount)
                            s2 = set(p)
                            setToPrint = s2.difference(s1)
                            supportPercentFullPerm2 = format(supportPercentFullPerm, '.4f')
                            confidencePerm2 = format(confidencePerm, '.4f')
                            writer.writerow(['R', str(supportPercentFullPerm2), str(confidencePerm2), ''.join(initCount), " => ", ''.join(setToPrint)])
                            print("R, " + str(supportPercentFullPerm2) + ", " + str(confidencePerm2) + ", " + ''.join(initCount) + " => " + ''.join(setToPrint))

def main():
    readFile()

if __name__ == '__main__':
    main()
