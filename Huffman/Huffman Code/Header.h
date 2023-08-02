#ifndef HUFFMAN_HEADER_H
#define HUFFMAN_HEADER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Node {
    char data;
    int freq;
    Node* left, * right;

    Node(char c, int f) {
        this->data = c;
        this->freq = f;
        this->left = this->right = nullptr;
    }
};

bool cmp_pair(pair<char, int> a, pair<char, int> b);

void insert(vector<Node*>& v, Node* node);

void downHeap(vector<Node*>& v, int index);

Node* top(vector<Node*>& v);

Node* buildTree(const vector<pair<char, int>>& freq);

void generateHuffmanCode(Node* root, const string& prefix, vector<string>& HuffmanCode);

string encode(const string& input, vector<string> HuffmanCode);

string decode(const string& encode, Node* root);

vector<pair<char, int>> build_freq_table(string s);

void deleteTree(Node*& root);

#endif