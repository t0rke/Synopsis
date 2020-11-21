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
    if (!inf) cerr << "Coudn't open " + filename + ".txt\n";
    while (getline(inf, line)) list.push_back(line);
    return list;
}

vector<vector<double>> get_matrix(size_t size) {
    vector<vector<double>> matrix;
    ifstream inf("matrix.txt");
    matrix.resize(size, vector<double>(size));
    for (size_t i = 0; i < size; ++i)
        for (size_t j = 0; j < size; ++j) inf >> matrix[i][j];
    return matrix;
}

vector<pair<string,int>> generate_features(const vector<string> &stop_words) {
    vector<pair<string, int>> corpus;
    std::ifstream in("sentences.txt");
    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string body = buffer.str();
    stringstream ss(body);
    string word;
    vector<string> list;
    
    while (ss >> word) list.emplace_back(word);
    size_t word_count = list.size();
    sort(begin(list), end(list));
        
    string root = list.front();
    int dupes = 0;
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
    cout << "Removing Stopwords: ->\n";
    for (size_t i = 0; i < corpus.size(); ++i) {
        for (size_t j = 0; j < stop_words.size(); ++j) {
            if (corpus[i].first == stop_words[j]) {
                corpus.erase(begin(corpus), begin(corpus) + i);
                cout << "   Erasing: " << stop_words[j] << endl;
            }
        }
    }
    cout << "Created Corpus:" << endl;
    return corpus;
}

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

vector<string> generate_stops(string filename) {
    ifstream inf(filename);
    vector<string> list;
    stringstream buffer;

    buffer << inf.rdbuf();
    string temp, file = buffer.str();
    stringstream ss(file);
    while (ss >> temp) list.emplace_back(temp);
    return list;
}

vector<double> calculate_simmilarity_scores(const vector<vector<double>> &matrix ) {
    const size_t bound = matrix.size();
    vector<double>sentence_simmilarity;
    sentence_simmilarity.reserve(bound);
    size_t sentence_count = 0;
    for (size_t i  = 0; i < bound; ++i) {
        //double sum = 0;
        double min = 100;
        size_t index = 0;
        ++sentence_count;
        cout << setprecision(10);
        for (size_t j = 0; j < bound; ++j) {
            //sum = sum + matrix[i][j];
            if (i == j) continue;
            else if(matrix[i][j] < min) {
                min = matrix[i][j];
                index = j;
            }
        }
        sentence_simmilarity.emplace_back(min);
        cout << sentence_count << " most similar to " << index + 1 << " COS -> " << min << "\n";
        //cout << min << endl;
    }
    return sentence_simmilarity;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    const vector<string> sentences = generate_lines("sentences.txt");
    const vector<vector<double>> matrix = get_matrix(sentences.size());
    const vector<pair<string, int>> features = generate_features(generate_stops("stopwords.txt"));
    const vector<double> sentence_score = calculate_simmilarity_scores(matrix);
    cout << sentences[15] << endl;
    cout << sentences[16] << endl;
    //construct_similarity_matrix(sentences);
    //std::cout << "Hello, World!\n";
    return 0;
}

// 1. Find the sentences with the greatest number of matches
// 2. Group these sentences together as important and select one sentence out of each of these groups to display IF and only if They contain at least ONE feature!
