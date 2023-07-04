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

struct Node {
	string data;
	Node* pNext;
};
struct Stack {
	Node* pHead = nullptr;

	void push(string s) {
		Node* pNew = new Node;
		pNew->data = s;
		pNew->pNext = this->pHead;
		this->pHead = pNew;
	}
	void removeNode(string s) {
		Node* cur = this->pHead;
		if (cur == nullptr) {
			return;
		}
		
		if (this->pHead->data == s) {
			cur = this->pHead;
			this->pHead = this->pHead->pNext;
			delete cur;
			return;
		}
		while (cur->pNext) {
			if (cur->pNext->data == s) {
				Node* tmp = cur->pNext;
				cur->pNext = cur->pNext->pNext;
				delete tmp;
			}
			cur = cur->pNext;
		}
	}
	vector<string> viewList() {
		Node* cur = pHead;
		vector<string> ans;
		ans.resize(0);
		if (cur == nullptr) return ans;
		while (cur) {
			ans.push_back(cur->data);
			cur = cur->pNext;
		}
		return ans;
	}
};
