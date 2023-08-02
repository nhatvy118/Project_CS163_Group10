#include "Header.h"

int main() {
    string test;
    getline(cin, test);
    vector<pair<char, int>> freq_table = build_freq_table(test);
    Node* root = buildTree(freq_table);
    vector<string> HuffmanCode(96, "");
    generateHuffmanCode(root, "", HuffmanCode);

    //Huffman Code


    for (int i = 0; i < 96; i++) {
        if (!HuffmanCode[i].empty())
            cout << (char) (i + 32) << ":" << HuffmanCode[i] << endl;
    }


    string tst = encode(test, HuffmanCode);
    cout << tst << endl;
    cout << decode(tst, root) << endl;
    deleteTree(root);
}