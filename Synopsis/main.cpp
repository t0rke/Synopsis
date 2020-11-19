//
//  main.cpp
//  Synopsis
//
//  Created by Suneeth Torke on 11/2/20.
//

#include <iostream>

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

struct compare {
    bool operator()(const std::pair<std::string,int> &lhs, const std::pair<std::string,int> &rhs) const {
        return (lhs.second > rhs.second);
    }
};

void strip(string &str) {
    replace(str.begin(), str.end(), '-', ' ');
    remove(str.begin(), str.end(), '\'');
    replace(str.begin(), str.end(), '\n', ' ');
    string j = "0123456789.-?!/$^~<>=+\":;{}(),";
    
    for (char i: j) str.erase(std::remove(str.begin(), str.end(), i), str.end());
    transform(begin(str), end(str), begin(str), [](char c){return std::tolower(c);});
}

// implementation of the different of COSINES matrices
vector<string> generate_lines(string filename) {
    ifstream inf;
    string line;
    vector<string> temp;
    vector<string> list;
    inf.open(filename);
    if (!inf) {
        cerr << "Coudn't open " + filename + ".txt" << endl;
        exit(1);
    }
    while (getline(inf, line) && line.length() > 1) {
        //strip(line);
        list.push_back(line);
        cout << line << endl;
    }
    return list;
}

vector<vector<double>> get_matrix(size_t size) {
    vector<vector<double>> matrix;
    ifstream inf("matrix.txt");
    matrix.resize(size, vector<double>(size));
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            inf >> matrix[i][j];
        }
    }
    return matrix;
}

vector<pair<string,int>> generate_features(string &body) {
    vector<pair<string, int>> corpus;
    string word;
    vector<string> list;
    stringstream ss(body);
    
    // splits the string into a vector of strings
    while (ss >> word) list.emplace_back(word);
    
    size_t word_count = list.size();
    // puts duplicate elements size by side
    sort(begin(list), end(list));
        
    string root = list.front();
    int dupes = 0;
    // calculates the frequency of every word by counting duplicate neighbors
    for (size_t i = 0; i < word_count; ++i) {
        if (root == list[i]) ++dupes;
        else {
            corpus.push_back({root, dupes});
            root = list[i];
            dupes = 1;
        }
    }
    // sorts in decending order
    sort(begin(corpus), end(corpus), compare());
    cout << "Created Corpus:" << endl;
    return corpus;
}
// converts a string to  a vec rather shittly
vector<string> string_to_vec(string &input) {
    vector<string> list;
    string temp;
    stringstream ss(input);

    while (ss >> temp) {
        list.emplace_back(temp);
    }
    return list;
}

double cosine_distance(vector<double> sent1, vector<double> sent2) {
    double dot = 0.0, denom_a = 0.0, denom_b = 0.0 ;
     for(unsigned int i = 0; i < sent1.size(); ++i) {
        dot += sent1[i] * sent2[i] ;
        denom_a += sent1[i] * sent1[i] ;
        denom_b += sent2[i] * sent2[i] ;
    }
    return dot / (sqrt(denom_a) * sqrt(denom_b)) ;
}

double similarity(string sentence1_in, string sentence2_in) {
    const vector<string> sentence1 = string_to_vec(sentence1_in);
    const vector<string> sentence2 = string_to_vec(sentence1_in);
    vector<string> full = sentence1;
    full.insert(full.end(), sentence2.begin(), sentence2.end());
                
    vector<double> sent_one(full.size()), sent_two(full.size());
    
    for (size_t i = 0; i < sentence1.size(); ++i) {
        for (size_t j = 0; j < full.size(); ++j) {
            if (sentence1[i] == full[j]) {
                sent_one[i] += 1;
            }
        }
    }
    for (size_t i = 0; i < sentence2.size(); ++i) {
        for (size_t j = 0; j < full.size(); ++j) {
            if (sentence2[i] == full[j]) {
                sent_two[i] += 1;
            }
        }
    }
    // 1 - distance shows how close they are
    return 1 - cosine_distance(sent_one, sent_two);
}

vector<vector<double>> construct_similarity_matrix(vector<string> sentences) {
    vector<double> temp(0, sentences.size());
    vector<vector<double>> similarity_matrix(sentences.size(), vector<double>(sentences.size(), -99));
    
    for (size_t i = 0; i < sentences.size(); ++i) {
        for (size_t j = 0; j < sentences.size(); ++j) {
            if (sentences[i] == sentences[j]) continue;
            similarity_matrix[i][j] = similarity(sentences[i], sentences[j]);
            //cout << similarity_matrix[i][j];
        }
        //cout << endl;
    }
    for (size_t t = 0; t < similarity_matrix.size(); ++t) {
        for (size_t s = 0; s < similarity_matrix.size(); ++s) {
            cout << similarity_matrix[t][s];
        }
        cout << endl;
    }
    return similarity_matrix;
}



int main(int argc, const char * argv[]) {
    // insert code here...
    //vector<string> sentences = generate_lines("Sept28.txt");
    const vector<vector<double>> matrix = get_matrix(303);
    
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            //cout << matrix[i][j] << " ";
        }
       // cout << "\n";
    }
    
    //construct_similarity_matrix(sentences);
    //std::cout << "Hello, World!\n";
    return 0;
}
