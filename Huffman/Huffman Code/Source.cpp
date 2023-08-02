#include "Header.h"

bool cmp_pair(pair<char, int> a, pair<char, int> b) {
    return a.second < b.second;
}

vector<pair<char, int>> build_freq_table(string s) {
    vector<int> freq(96, 0);
    for (char c : s) {
        freq[c - 32]++;
    }
    vector<pair<char, int>> res;
    for (int i = 0; i < 96; i++) {
        if (freq[i] != 0) {
            res.push_back({ (char)(i + 32), freq[i] });
        }
    }
    sort(res.begin(), res.end(), cmp_pair);
    return res;
}

void insert(vector<Node*>& v, Node* node) {
    v.push_back(node);
    int child = v.size() - 1;
    int parent = (child - 1) / 2;
    while (child > 0 && v[child]->freq < v[parent]->freq) {
        swap(v[child], v[parent]);
        child = parent;
        parent = (child - 1) / 2;
    }
}

void downHeap(vector<Node*>& v, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = left + 1;
    if (left < v.size() && v[left]->freq < v[largest]->freq)
        largest = left;
    if (right < v.size() && v[right]->freq < v[largest]->freq)
        largest = right;
    if (largest != index) {
        swap(v[index], v[largest]);
        downHeap(v, largest);
    }
}

Node* top(vector<Node*>& v) {
    Node* res = v[0];
    v[0] = v.back();
    v.pop_back();
    downHeap(v, 0);
    return res;
}

Node* buildTree(const vector<pair<char, int>>& freq) {
    vector<Node*> v;
    v.reserve(freq.size());
    for (auto& i : freq)
        insert(v, new Node(i.first, i.second));
    while (v.size() > 1) {
        Node* left = top(v);
        Node* right = top(v);
        Node* root = new Node('\0', left->freq + right->freq);
        root->left = left;
        root->right = right;
        insert(v, root);
    }
    return v[0];
}

void generateHuffmanCode(Node* root, const string& prefix, vector<string>& HuffmanCode) {
    if (root == nullptr)
        return;
    if (root->data != '\0')
        HuffmanCode[root->data - 32] = prefix;
    generateHuffmanCode(root->left, prefix + '0', HuffmanCode);
    generateHuffmanCode(root->right, prefix + '1', HuffmanCode);
}

string encode(const string& input, vector<string> HuffmanCode) {
    string res;
    for (char c : input)
        res += HuffmanCode[c - 32];
    return res;
}

string decode(const string& encode, Node* root) {
    string res;
    Node* cur = root;
    for (char c : encode) {
        if (c == '0')
            cur = cur->left;
        if (c == '1')
            cur = cur->right;
        if (cur->data != '\0') {
            res += cur->data;
            cur = root;
        }
    }
    return res;
}

void deleteTree(Node*& root) {
    if (root == nullptr)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
    root = nullptr;
}