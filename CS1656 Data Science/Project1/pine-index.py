import sys
import os, json, re, nltk, string
import json
import glob
from nltk.stem import PorterStemmer
from nltk.tokenize import sent_tokenize, word_tokenize
from nltk.corpus import stopwords

#nltk.download('stopwords')
def readFile():
    ps = PorterStemmer()
    fullList = [];
    some_list_of_input_files = glob.glob('input/*.txt')
    print(some_list_of_input_files)
    # argv is your commandline arguments, argv[0] is your program name, so skip it
    for n in some_list_of_input_files:
        wordList = dict()
        print(n) #print out the filename we are currently processing
        input = open(n, "r")
        # do some processing
        n = n[6:]
        lines = input.readlines()
        for line in lines:
            line = line.lower()
            line = re.sub(r'[^\w\s]','',line)
            line = " ".join([word for word in line.split() if not word.isdigit()])
            line = [w for w in line.split() if w not in stopwords.words('english')]
            for w in line:
                newWord = ps.stem(w)
                if (newWord in wordList):
                    # do something
                    for key, val in wordList.items():
                        if (key == newWord):
                            for k in val:
                                # if key is equal to the doc name, then increment value by 1
                                if (k == n):
                                    val[k] = val[k] + 1
                else:
                    # create a new word in wordList
                    wordList[newWord] = {n : 1}
            fullList.append(wordList)
            input.close()
    with open("inverted-index.json", 'w') as outfile:
        json.dump(fullList, outfile)
def main():
    readFile()


if __name__ == '__main__':
    main()
