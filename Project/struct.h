#pragma once
#include<string>
#include<vector>
#include<iostream>


using namespace std;

//ASCII avaible charactor is from 32-127


const int alphabet = 96;
struct trieNode {
	trieNode* c[alphabet];
	bool isEnd = false;
	vector<string> mean;

	trieNode() {
		for (int i = 0; i < alphabet; ++i) {
			this->c[i] = nullptr;
		}
		this->mean.resize(0);
	}
};