# *Synopsis*
Synopsis is written in Python and C++ and is designed to condense a body of text to gather a quick synopsis.
Through the use of Genism to embed a word into 3D space using its built-in Word2Vec Word mover model as well as text comparison in C++ Synopsis effectively generates a quick and effective summary of any body of the text.

I wrote this program because I didn't have enough time to attend my Computer Science: Water Pressure class but still wanted to get a gist of what the class discussed during a given day. I normally would've resorted to watching a recorded lecture, but this class offered no such alternative. To address this issue, I noticed that ZOOM auto-generated class transcripts at the end of each class, which gave a second by the second report of what was being said.

I used this program to generate the most relevant sentences to include in my weekly summative discussion post, instead of having to watch each lecture.
The following parts of this document will help you use this program with any document you desire.

## Methods
1. Finding a body of text
2. Using Genism's word2vec functionality
3. Implementing a custom SVM
4. Using the Law of Cosines to calculate the vector difference within the 3D space
5. Assigning a similarity score
6. Using similarity score to find other similar sentences
7. Using similar sentences to eliminate redundant sentences and leave only the most important ones using a collection of binary trees
8. Returning the desired length of text

## Model
THe model I chose to use for this project was google's news headline model due ito its size and similarity in the material that I wanted to analyze. 

## Functionality
1. Part one -> Python
2. Parth two -> C++

## Statistics


### Authors
@t0rke
