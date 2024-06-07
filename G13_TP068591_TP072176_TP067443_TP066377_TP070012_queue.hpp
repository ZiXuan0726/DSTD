#pragma once
#include <iostream>
#include <string>
#include "G13_TP068591_TP072176_TP067443_TP066377_TP070012_Struct.hpp"
using namespace std;



class Queue {
public:
	QueueNode* front;
	QueueNode* rear;
	QueueNode* NewQueue;
	int size = 0;

	Queue() {
		front = NULL;
		rear = NULL;
	}

	bool isEmpty() {
		if (front == NULL && rear == NULL)
			return true;
		else
			return false;
	}

	void enqueue(TreeNode* node) { // insert at the end
		//cout << "4" << endl;
		QueueNode* temp = new QueueNode();
		temp->treeNode = node;
		//cout << "5" << endl;
		temp->next = nullptr;

		if (isEmpty()) {
			front = temp;
			rear = temp;
			size++;
			return;
		}
		rear->next = temp;
		rear = temp;
		size++;
		return;
	}

	TreeNode* dequeue() {
		if (isEmpty()) {
			cout << "Queue is empty" << endl;
			return NULL;
		}
		QueueNode* temp = front;
		front = front->next;
		if (front == nullptr) {
			rear = nullptr;
		}
		TreeNode* data = temp->treeNode;
		delete temp;
		size--;
		return data;
	}

	QueueNode* copyData(TreeNode* node) {
		//cout << "10" << endl;
		if (node == NULL) {
			return NULL;
		}
		//cout << "11" << endl;
		QueueNode* newNode = new QueueNode();
		TreeNode* temp = new TreeNode();
		//cout << "12" << endl;
		temp->name = node->name;
		temp->totalScore = node->totalScore;
		newNode->treeNode = temp;
		//cout << "14" << endl;
		return newNode;
	}


};
