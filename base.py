import logging
from math import trunc

import gensim.downloader as api

model = api.load('word2vec-google-news-300')  # import google's news Model
from nltk.corpus import stopwords
from nltk import download

download('stopwords')  # Download stopwords list.
stop_words = stopwords.words('english')

logging.basicConfig(format='%(asctime)s : %(levelname)s : %(message)s', level=logging.INFO)

sentence_obama = 'Obama speaks to the media in Illinois'
sentence_president = 'The president greets the press in Chicago'


def sanitize(sentence):
    return [w for w in sentence.lower().split() if w not in stop_words]

model.init_sims(replace=True)  # normalises to reduce cosine and euclid dist variability

import re
import os

regex = re.compile('[^a-zA-Z]')
file = open("Sept28th.txt", "r+")

# print(stop_words)

from time import time

start = time()

# reads line by line
count = 0
sentences = []
rawsentences = []
while True:
    count += 1
    line = file.readline()
    if not line:
        break
    if len(line) < 250:
        continue
    rawsentences.append(line)
    # strips the non-letter characters and replaces by space
    line = line.replace('\'', '')
    line = line.replace('\n', '')
    line = regex.sub(' ', line)
    line = re.sub(' +', ' ', line)
    line = line.strip()
    line = line.lower()
    # line = [w for w in line if w not in stop_words]
    sentences.append(sanitize(line))
file.close()
print("cleaned")

with open("sentences.txt", 'w') as f:
    for item in sentences:
        f.write("%s\n" % item)

with open("rawsentences.txt", 'w') as f:
    for item in rawsentences:
        f.write("%s" % item)

sentence_count = len(sentences)
matrix = [[0 for i in range(sentence_count)] for j in range(sentence_count)]
count = 0
print("Iteration: ")
for i in range(len(matrix)):
    for j in range(len(matrix[i])):
        count = count + 1
        matrix[i][j] = model.wmdistance(sentences[i], sentences[j])

print(count)

# matrixPy = np.array(matrix)
# np.trunc(matrixPy, decs=4)
with open("matrix.txt", 'w') as f:
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            f.write("%.4f " % matrix[i][j])
        f.write("\n")
