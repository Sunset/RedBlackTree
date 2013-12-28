//Name: Allen Hsia
//Date: March 20th 2012
//CSE310 T TH 1:30-2:45
//RBread.cpp
//Main function that calls the rbheader file to do the RB insert
//In this file, it takes in the file and reads it the sepcific values to put in a binary search tree and puts it in one.
//After that it'll take the next few digits to insert and send those digits with the original tree into a Red black insert tree.
//Within the red black insert, it'll do all the necessary changes, left rotate and right rotate, insertFixUp and insert.
//After all is done it'll print out the tree using pre-order format.
#include<iostream>
#include<fstream>
#include<stdio.h>
#include "RBheader.h"
using namespace std;

//constructor for the nodes
RBheader::RBheader(){
	//creating new nodes
	root = new RBNode();
	nill = new RBNode();
	//defining properties of a nill node
	nill->lchild = nill->rchild = nill->parent = nill;
	nill->color = 1;
	//defining properties of a root
	root = nill;
//	root->key = 9999999;
}

//reads in files from the input.txt 
void RBheader::RBread(){

	ifstream input;

	input.open("input.txt");//opens txt

	int N, color, key,numtoInsert, newKey;

	input >> N; //the amount of numbers in the tree

	//a for loop to read in the numbers with their colors
	for (int i = 0; i<N; i++)
	{
		input >> color;// 1 for black, 0 for red
		input >> key;//the value of the node

		//making a node out of the color and key that was read in
		RBNode* newNode = new RBNode;
		newNode->color = color;
		newNode->key= key;
		newNode->lchild=nill;
		newNode->rchild=nill;

		//insert the values into the root (making a tree)
		treeInsert(newNode);
	}

	input >> numtoInsert;//the amount of numbers to insert after reading

	//a for loop for the amount of numbers to read in.
	for (int j = 0; j<numtoInsert; j++)
	{
		input  >> newKey; // the number to insert

		//making a new node out of the number that was read
		RBNode* newKeyNode = new RBNode;
		newKeyNode->color = 0; //inserted number is always red node
		newKeyNode->key= newKey;
		newKeyNode->lchild=nill;
		newKeyNode->rchild=nill;

		RBinsert(newKeyNode);//insert node and the tree into a RedBlack insert function

		//after insertion is done, print it out
		RBwrite();//send to write to display tree

	}
	//close the input file
	input.close();
}

//binary tree insert. Inserting the values into a tree before doing red black tree properties
//function is from the book
void RBheader::treeInsert(RBNode* z){
	RBNode* y = new RBNode;
	RBNode* x = new RBNode;

	x = root;
	y = nill;

	while(x != nill)
	{ 
		y = x;
		if (z->key < x->key)
		{
			x = x->lchild;
		}
		else {
			x = x->rchild;
		}
	}
	z->parent = y;
	if(y == nill){
		root = z;
	}
	else if(z->key < y->key){
		y->lchild = z;
	}
	else{
		y->rchild = z;
	}
}

//doing a RBinsert function. THis function takes in the binary tree already made
//but then insert a new node with a Red Black Tree property
//Function is from the book
void RBheader::RBinsert(RBNode* z){
	RBNode* y = nill;
	RBNode* x = root;
	while(x != nill)
	{ 
		y = x;
		if (z->key < x->key)
		{
			x = x->lchild;
		}
		else {
			x = x->rchild;
		}
	}
	z->parent = y;
	if(y == nill){
		root = z;
	}
	else if(z->key < y->key){
		y->lchild = z;
	}
	else{
		y->rchild = z;
	}
	z->lchild = nill;
	z->rchild = nill;
	z->color = 0;
	//sending to fixup
	insertFixUp(z);
}
//this function recolors the nodes incase there is a violation
//function is from the book
void RBheader::insertFixUp(RBNode* z){
	while(z->parent->color==0){
		if(z->parent==z->parent->parent->lchild)
		{
			RBNode* y = z->parent->parent->rchild;
			if(y->color==0){
				z->parent->color=1;				//case1
				y->color=1;						//case1
				z->parent->parent->color = 0;	//case1
				z = z->parent->parent;	//case1
			}
			else { 
				if(z== z->parent->rchild)
				{
					z = z->parent;				//case2
					leftRotate(z);			//case2
				}
				z->parent->color = 1;			//case3
				z->parent->parent->color = 0;	//case3
				rightRotate(z->parent->parent);//case3
			}
		}

		else
		{
			RBNode* y = z->parent->parent->lchild;
			if (y->color==0)
			{
				z->parent->color = 1;			//case1
				y->color = 1;					//case1
				z->parent->parent->color = 0;	//case1
				z = z->parent->parent;			//case1
			}
			else {
				if(z== z->parent->lchild)
				{
					z = z->parent;				//case2
					rightRotate(z);			//case2
				}
				z->parent->color = 1;			//case3
				z->parent->parent->color = 0;	//case3
				leftRotate(z->parent->parent);//case3
			}
		}
	}//end of while loop
	root->color = 1;
}

//does the leftrotate procedure. This is a redblack procedure that's done
//function is in the book
void RBheader::leftRotate(RBNode* x){
	RBNode* y =x->rchild;
	x->rchild =y->lchild;
	if (y->lchild != nill){
		y->lchild->parent =x;
	}
	y->parent =x->parent;
	if (x->parent==nill){
		root =y;
	}
	else if(x==x->parent->lchild)
	{
		x->parent->lchild=y;
	}
	else
	{
		x->parent->rchild=y;
	}
	y->lchild=x;
	x->parent=y;
}

//does the rightrotate procedure. This is a redblack procedure that's done
//function is in the book
void RBheader::rightRotate(RBNode* x){
	RBNode* y =x->lchild;
	x->lchild =y->rchild;
	if (y->rchild != nill){
		y->rchild->parent =x;
	}
	y->parent =x->parent;
	if (x->parent==nill){
		root =y;
	}
	else if(x==x->parent->lchild)
	{
		x->parent->lchild=y;
	}
	else
	{
		x->parent->rchild=y;
	}
	y->rchild=x;
	x->parent=y;
}

//RB write function.
//it takes the tree that we did edits on and prints it out
void RBheader::RBwrite()
{
	ofstream OutStream;
	OutStream.open("output.txt", ios::app);
	//sends to another function to do a pre-order print
	preOrderPrint(root, OutStream);
	OutStream<<"\n";
	OutStream.close();
}

//prints the tree in preorder print
void RBheader::preOrderPrint(RBNode* next, ostream& output)
{
	if(next == nill)
		return;
	//prints the tree!
	output << next ->color << " " << next->key << endl;
	//recursion to print the next few nodes
	preOrderPrint(next->lchild,output);
	preOrderPrint(next->rchild,output);
}

