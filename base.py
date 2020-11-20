import re
import os
import csv

regex = re.compile('[^a-zA-Z]')

file = open("sources/Sept28.txt", "r+")
with open("common/stopwords.txt") as f:
    stop_words = f.read().splitlines()

# print(stop_words)

from time import time

start = time()

# reads line by line
count = 0
sentences = []
while True:
    count += 1
    line = file.readline()
    if not line:
        break
    # if len(line) < 100:
    #     continue
    # strips the non-letter characters and replaces by space
    line = line.replace('\'', '')
    line = line.replace('\n', '')
    line = regex.sub(' ', line)
    line = re.sub(' +', ' ', line)
    line = line.strip()
    line = line.lower()
    # line = [w for w in line if w not in stop_words]
    sentences.append(line)
file.close()
print("cleaned")

with open('sources/sentences.txt', 'w') as f:
    for item in sentences:
        f.write("%s\n" % item)

from gensim.models import Word2Vec

model = Word2Vec(sentences)

sentence_count = len(sentences)
matrix = [[0 for i in range(sentence_count)] for j in range(sentence_count)]

for i in range(len(matrix)):
    start = time()
    for j in range(len(matrix[i])):
        matrix[i][j] = model.wv.wmdistance(sentences[i], sentences[j])

print('Operations took')
print(time() - start)

with open("sources/matrix.txt", "w+") as my_csv:
    csvWriter = csv.writer(my_csv, delimiter=' ')
    csvWriter.writerows(matrix)



