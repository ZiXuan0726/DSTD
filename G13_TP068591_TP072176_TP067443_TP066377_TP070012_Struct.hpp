#pragma once
#include <iostream>
#include <string>

using namespace std;

struct TreeNode {
	string name;
	int totalScore;
	TreeNode* left;
	TreeNode* right;
};

struct QueueNode {
	TreeNode* treeNode;
	QueueNode* next;
};
