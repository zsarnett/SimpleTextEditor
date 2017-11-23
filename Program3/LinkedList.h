#ifndef LINKEDLIST_H

#define LINKEDLIST_H

#include<iostream>

#include<fstream>

#include<string>

#include<sstream>

#include<cstdlib>

using namespace std;

struct Tree_Node
{
	string textLine;

	struct Tree_Node *left, *right;

} *startList;

class listTextEditor
{
public:

	Tree_Node* build(string Expression, int left, int right);

	void Build_Tree(string line);

	void insertLineList(string line, int &linPos);

	void appendToEnd(string line);

	void deleteLineList(int linPos);

	void SaveContents();

	void displayList();

	void displayHelp();

	string Copy(int line);

	void Paste(string line, int linepos);

	void displayInstructions(int NumScreenLines);

	listTextEditor()

	{

	startList = NULL;

	}

private:

	Tree_Node* root;

};

#endif