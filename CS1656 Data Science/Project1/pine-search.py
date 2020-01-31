import sys
import os, json, re, nltk, string
import json
from nltk.stem import PorterStemmer
from nltk.tokenize import sent_tokenize, word_tokenize
from nltk.corpus import stopwords
import math

def searchForWord():
    ps = PorterStemmer()
    tf = -1
    with open('inverted-index.json') as data_file:
        data = json.load(data_file)
    #print(data)
    with open('keywords.txt') as f:
        content = f.readlines()
    for keyword in content:
        print("_________________________________________________")
        print()
        print("keywords == " + keyword)
        fullWeightList = []
        individualWeightDict = dict()
        newKeyWord = keyword.lower()
        newKeyWord = re.sub(r'[^\w\s]','',newKeyWord)
        newKeyWord = " ".join([word for word in newKeyWord.split() if not word.isdigit()])
        newKeyWord = [w for w in newKeyWord.split() if w not in stopwords.words('english')]
        for w in newKeyWord:
            newWord = ps.stem(w)
            # initialize data structure for storing document data per word
            docNum = dict()
            documentRelevence = 0
            for dictionary in data:
                for word, value in dictionary.items():
                    if (word == newWord):
                        for document, number in value.items():
                            #print(document)
                            #print(number)
                            docNum.update({document : number})
                            documentRelevence = documentRelevence + 1
            # After iterating through the entire data structure
            #print(documentRelevence) # nDoc
            #print(len(data)) # N, number of total documents
            for doc, num in docNum.items():
                #print("document= " + doc)
                weightW = (1 + math.log2(num)) * (math.log2((len(data) / documentRelevence)))
                if doc in individualWeightDict:
                    individualWeightDict[doc].append({w : weightW})
                else:
                    individualWeightDict.update({doc : [{w : weightW}]})
                #print("weight(" + w + "): " + str(weightW))
        #print(individualWeightDict)
        # Finally print out everything to the console
        for docu, list in individualWeightDict.items():
            score = 0
            print("file= " + docu)
            for diction in list:
                for finalWord, finalWeight in diction.items():
                    score = score + finalWeight
                    print("weight(" + finalWord + "): " + str(finalWeight))
            print("final Score= " + str(score))
            print()



def main():
    searchForWord()


if __name__ == '__main__':
    main()
