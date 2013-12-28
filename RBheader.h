//Name: Allen Hsia
//Date: March 20th 2012
//CSE310 T TH 1:30-2:45
//RBheader.h

#ifndef RBHEADER_H_
#define RBHEADER_H_
#include<iostream>
#include<fstream>
#include<stdio.h>
using namespace std;

class RBheader{

public:
	//struct for creating the node
	struct RBNode
	{
		int color;
		int key;
		struct RBNode *parent, *lchild, *rchild;
	};
	
	//initializing nodes for nill and root
	RBNode *nill;
	RBNode *root;
	
	RBheader();

	//prototypes
	void RBread();
	void treeInsert(RBNode*);
	void RBinsert(RBNode*);
	void insertFixUp(RBNode*);
	void leftRotate(RBNode*);
	void rightRotate(RBNode*);
	void preOrderPrint(RBNode*, ostream&);
	void RBwrite();
	//prototypes
};

#endif