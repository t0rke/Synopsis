# *Synopsis*
Synopsis is written in Python and C++ and is designed to condense a body of text to gather a quick synopsis.
Through the use of Genism to embed a word into 3D space using its built-in Word2Vec Word mover model as well as text comparison in C++ Synopsis effectively generates a quick and effective summary of any body of the text.

I used this program to generate the most relevant sentences to include in my weekly summative discussion post, instead of having to watch each lecture.
The following parts of this document will help you use this program with any document you desire.

## Methods

I wrote this program because I didn't have enough time to attend my Computer Science: Water Pressure class but still wanted to get a gist of what the class discussed during a given day. I normally would've resorted to watching a recorded lecture, but this class offered no such alternative. To address this issue, I noticed that ZOOM auto-generated class transcripts at the end of each class, which gave a second by the second report of what was being said.

This program works is the following order:
**Python:**
1. Sanitizing the target text body
2. Filtering the resulting sentences by length, duplicates etc.
3. Initializing the model and using the word mover method
4. Comparing every sentence with every other sentence, to get a similarity matrix
5. Normalizing the Matrix
**C++**
1. Interpretting the generated data
2. Using the Law of Cosines to calculate the vector difference within the 3D space
5. Assigning a similarity score
6. Using similarity score to find other similar sentences
7. Using similar sentences to eliminate redundant sentences and leave only the most important ones using a collection of binary trees
8. Returning the desired length of text

## Model
The model I chose to use for this project was google's news headline model due ito its size and similarity in the material that I wanted to analyze. Since I was analyzing transcript it is likely that most,if not all of the words were contained within this corpora.

## Functionality
To use this program replace `sentences.txt` default with your desired text and run the python section of the program with a Python 3.7 interpreter.

Run the C++ section of the program and it will utilize the `matrix.txt` file that has been populated by the python portion. The program will print the the most relevant sentences with their time stamps into the console.

**sample matching output:**
```bash
10 most similar to 16 COS -> 0
11 most similar to 114 COS -> 0
12 most similar to 39 COS -> 0.9616
13 most similar to 69 COS -> 0
14 most similar to 60 COS -> 0.8816
15 most similar to 24 COS -> 0
16 most similar to 122 COS -> 0
17 most similar to 6 COS -> 1.022
18 most similar to 77 COS -> 0
```

### Authors
@t0rke
