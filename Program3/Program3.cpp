#include<iostream>

#include<string>

#include<sstream>

#include<fstream>

#include<cstdlib>

using namespace std;

struct Node //Construct a Node Structure
{
	//Variables inside of the Node Structure
	struct Node *Next;

	string Line;
}
*Head; //Beginning Node

class MyEditor  //Construct MyEditor Class
{
public: //Public Variables

	MyEditor() //Make an empty Linked List to Start
	{
		Head = NULL; //Make the list equal to NULL
	}

	Node* CreateNode(string); //Function to Make a node

	void InsertLine(string LinetoInsert, int &LinePosition); //Function to Insert a Line at any Position

	void DeleteALine(int LinePosition); //Function to Delete a line at any Position

	void AddtoEnd(string LinetoInsert); //Function to add a line at any Position

	void ListDisplay(); //Function to Display what is in the text file and what changes have been made

	void HelpDisplay(); //Function to Display the Help screen for instruction

	string Copy(int LinetoCopy); //Function to copy any line

	void Paste(string LinetoInsert, int &LinePosition); //Function to Paste the copied line to any line

	void InstructionBottomDisplay(); //Function to Display the Instructions at the bottom of the screen

	void Save(); //Function to Save the changes made to the text file
};

Node *MyEditor::CreateNode(string Text) //Function to Make a node
{
	struct Node *Store;

	Store = new(struct Node);

	Store->Line = Text;

	Store->Next = NULL;

	return Store;
}

void MyEditor::InsertLine(string LineToInsert, int &LinePosition) //Function to Insert a Line at any Position
{
	struct Node *Node; //Call all of the Node Variables
	struct Node *StoreNode;
	struct Node *EndNode;
	struct Node *NullNode;
	struct Node *PointNode = NULL;

	StoreNode = CreateNode(LineToInsert); //Create a Node with text given

	int Count = 1; //Counter

	PointNode = Head; //Point a Node to the beginning

	EndNode = PointNode; //Start the endnode at the beginning

	while (PointNode != NULL) //While the pointer node is not pointing at NULL
	{
		EndNode = PointNode; //Make the endnode the next place in the list

		PointNode = PointNode->Next; //Point to the next Node in the list

		Count += 1; //Add one to the counter
	}

	PointNode = NULL; //Make the Pointer Node the beginning of the list

	if (LinePosition == 1) //If the line number given is one
	{
		if (Head == NULL) //If the list is empty
		{
			Head = StoreNode; //Make the first node the text given

			Head->Next = NULL; //Make the second node equal to NULL
		}
		else
		{
			PointNode = Head; //Make the pointer node the value of the first element in the list

			Head = StoreNode; //Make the first node the given text

			StoreNode->Next = PointNode; //Point the given text to the next node
		}
	}

	else if (LinePosition > 1 && LinePosition <= Count) //If the line entered is between line 1 and the end
	{
		Node = Head; //Make a node equal to the first Node

		for (int i = 1; i < LinePosition; i++) //Get to the position of the linenumber given
		{
			PointNode = Node; //Make the pointer node the current node
			
			Node = Node->Next; //Then point to the next node
		}
		PointNode->Next = StoreNode; //Point the current node at the text given

		StoreNode->Next = Node; // Point the text given Node at the next node

	}

	else
	{
		for (int i = 1; i < (LinePosition - Count + 1); i++) //If the line to be inserted is greater than the last line
		{			
			NullNode = CreateNode(""); //Create a blank Node

			if (Head == NULL) //If the list is empty
			{
				Head = NullNode; //Make the first node Blank

				EndNode = Head; //Make the first node the end node

				Head->Next = NULL; //Point the only node at NULL
			}

			else
			{

				EndNode->Next = NullNode; //Make a blank node after the last node

				NullNode->Next = NULL; //Point the blank node at Null

				EndNode = NullNode; //Make the last node the blank node
			}
		}

		EndNode->Next = StoreNode; //Once to the position make that node the text given

		StoreNode->Next = NULL; //Point the text given to NULL
	}
}

void MyEditor::DeleteALine(int LinePosition) //Function to Delete a line at any Position
{
	struct Node *Node; //Call all the Node Variables
	struct Node *EndNode;
	struct Node *PointNode = NULL;

	if (Head == NULL) //If the list is Empty
	{
		return; //Return since you cant delete anything
	}

	int count = 0; //Make a counter

	EndNode = Head; //Make the endNode the first Node

	while (EndNode != NULL) //While the endNode isnt NULL
	{
		EndNode = EndNode->Next; //Make the Next Node the end Node

		count += 1; //Add one to the counter
	}

	Node = Head; //Make a Node equal to the first Node

	if (LinePosition == 1) //If the desired line Number is one
	{
		Head = Node->Next; //Make the first Node the second Node
	}

	else
	{
		if (LinePosition > 0 && LinePosition <= count) //If it isn't the first Node 
		{
			Node = Head; //Make a node equal to the first node

			for (int i = 1; i < LinePosition; i++) //Get to the position of the Line
			{
				PointNode = Node; //Make the pointer node the current position

				Node = Node->Next; //Make a Node the next position
			}

			PointNode->Next = Node->Next; //Make the current Node equal the next node 
		}

		else //If the line does not exist
		{
			cout << "Sorry.  Unable to delete a nonexistant line." << endl;

			return;
		}
	}
}

void MyEditor::AddtoEnd(string line) //Function to add a line at any Position
{
	struct Node *StoreNode; //Call the Node Variables
	struct Node *EndNode;
	struct Node *PointNode = NULL;

	PointNode = Head; //Make a node the first element

	EndNode = PointNode; //Make an end node the same element

	StoreNode = CreateNode(line); //Make a Node with the given text

	if (Head == NULL) //If the list is empty
	{
		Head = StoreNode; //Make the first node the given text

		Head->Next = NULL;  //Point the given text at Null
	}
	else
	{
		while (PointNode != NULL) //While the current node does equal Null
		{
			EndNode = PointNode; //Make the endNode the current Node

			PointNode = PointNode->Next; //Make a Node the Next Node
		}

		EndNode->Next = StoreNode; //MAke the Node after the last the given text

		StoreNode->Next = NULL; //Point the given text at NULL
	}
}

void MyEditor::Save() //Function to Save the changes made to the text file
{
	//Call all the Variables
	bool first = true; 

	fstream os;

	string name = "textfile.txt";

	struct Node *StoreNode;

	os.open(name.c_str(), std::ofstream::out | std::ofstream::trunc); //Open the file name

	StoreNode = Head; //Make the first Node the store Node

	while (StoreNode != NULL) //While the node doesnt equal NULL
	{
		if (!first) //If it isnt the first line
		{
			os << endl; //Add an endline
		}
		os << StoreNode->Line; //Send the current line into the file

		StoreNode = StoreNode->Next; //Go to the next line

		first = false; //After the first line make this false
	}

	os.close(); //close the file

	return;

}

string MyEditor::Copy(int LinePosition) //Function to copy any line
{
	struct Node *Node, *StoreNode, *EndNode, *PointNode; //Call all the Node Variables

	PointNode = NULL; //Make the pointer Node NULL

	EndNode = Head; //Make the last node the first Node

	int count = 0; //Make a counter

	while (EndNode != NULL) //While the last node isnt Null
	{
		EndNode = EndNode->Next; //Make the last Node the next Node

		count += 1; //Add one to the counter
	}

	if (LinePosition > 0 && LinePosition <= count) //If the line number is between 1 and the last Number
	{
		Node = Head; //Set a Node equal to the first element

		if (LinePosition == 1) //If the number given is one
		{
			if (Head == NULL) //If the list is empty
			{
				PointNode = CreateNode(""); //MAke the point node blank
			}
			else
			{
				PointNode = Head; //Make the pointer Node the first element
			}
		}
	
		else
		{
			for (int i = 1; i < LinePosition; i++) //Get to the position in the line
			{
				PointNode = Node; //Make this the current value
			
				Node = Node->Next; //Make this the next value
			}
			PointNode = PointNode->Next; //Make the pointer Node the next value
		}
		return PointNode->Line; //Return the value of the pointer node
	}
	else //If the line entered doesn't exist
	{
		cout << "Can't copy a Line that is not existent" << endl;
	}
}

void MyEditor::Paste(string LinetoInsert, int &LinePosition) //Function to Paste the copied line to any line
{
	struct Node *StoreNode, *Node, *EndNode, *NullNode, *PointNode = NULL; //Call all of the Node Variables

	StoreNode = CreateNode(LinetoInsert); //Create a Node with text given

	int Count = 1; //Counter

	PointNode = Head; //Point a Node to the beginning

	EndNode = PointNode; //Start the endnode at the beginning

	while (PointNode != NULL) //While the pointer node is not pointing at NULL
	{
		EndNode = PointNode; //Make the endnode the next place in the list

		PointNode = PointNode->Next; //Point to the next Node in the list

		Count += 1; //Add one to the counter
	}

	PointNode = NULL; //Make the Pointer Node the beginning of the list

	if (LinePosition == 1) //If the line number given is one
	{
		if (Head == NULL) //If the list is empty
		{
			Head = StoreNode; //Make the first node the text given

			Head->Next = NULL; //Make the second node equal to NULL
		}
		else
		{
			PointNode = Head; //Make the pointer node the value of the first element in the list

			Head = StoreNode; //Make the first node the given text

			StoreNode->Next = PointNode; //Point the given text to the next node
		}
	}

	else if (LinePosition > 1 && LinePosition <= Count) //If the line entered is between line 1 and the end
	{
		Node = Head; //Make a node equal to the first Node

		for (int i = 1; i < LinePosition; i++) //Get to the position of the linenumber given
		{
			PointNode = Node; //Make the pointer node the current node
			
			Node = Node->Next; //Then point to the next node
		}
		PointNode->Next = StoreNode; //Point the current node at the text given

		StoreNode->Next = Node; // Point the text given Node at the next node

	}

	else
	{
		for (int i = 1; i < (LinePosition - Count + 1); i++) //If the line to be inserted is greater than the last line
		{			
			NullNode = CreateNode(""); //Create a blank Node

			if (Head == NULL) //If the list is empty
			{
				Head = NullNode; //Make the first node Blank

				EndNode = Head; //Make the first node the end node

				Head->Next = NULL; //Point the only node at NULL
			}

			else
			{

				EndNode->Next = NullNode; //Make a blank node after the last node

				NullNode->Next = NULL; //Point the blank node at Null

				EndNode = NullNode; //Make the last node the blank node
			}
		}

		EndNode->Next = StoreNode; //Once to the position make that node the text given

		StoreNode->Next = NULL; //Point the text given to NULL
	}
}

void MyEditor::ListDisplay() //Function to Display what is in the text file and what changes have been made
{
	struct Node *StoreNode; //Call the Node Variables

	if (Head == NULL) //If the list is empty
	{
		cout << "" << endl;

		return;
	}
	
	StoreNode = Head; //Make a nod ethe first element

	int Count = 1; //Make a counter
	
	while (StoreNode != NULL) //While the current element does not equal NULL
	{
		cout << Count << "> " << StoreNode->Line << endl; //Print the line number and the value of the line

		StoreNode = StoreNode->Next; //Move to the next line

		Count += 1; //Add one to the counter
	}

	return;
}

void MyEditor::HelpDisplay() //Function to Display the Help screen for instruction
{
	cout << "----------------------------------------------------------" << endl;

	cout << "Welcome to my text editor." << endl;

	cout << ">To insert text at the end of the file, type a line and press enter." << endl;

	cout << ">To insert text at a certain line number, type 'I'" << endl;

	cout << ">To delete a line, type 'D'" << endl;

	cout << ">To copy a line into clipboard, type 'C' followed by a space and the line number." << endl;

	cout << ">To paste a line, type 'P' followed by a space and the line number." << endl;

	cout << ">A text line which has been copied into clipboard recently is the line to be pasted." << endl;

	cout << ">To print all the lines, type 'L' and press enter." << endl;

	cout << ">To exit, type 'E' and press enter." << endl;

	cout << " >To display this introduction, type 'H' and press enter." << endl;

	cout << "----------------------------------------------------------" << endl;
}

void MyEditor::InstructionBottomDisplay() //Function to Display the Instructions at the bottom of the screen
{
	if (system("CLS"))
	{
		system("clear");
	}

	int x = 0;

	while(x != 21)
	{
		printf("\n");
		x += 1;
	}

	printf("-------------------------------------------------------------------");

	cout << endl;

	printf("I <linenum>: insert a line;      D <linenum>: delete a line;");

	cout << endl;

	printf("C <linenum>: copy a line to clipboard;    P <linenum>: paste a line from clipboard");

	cout << endl;

	printf("L: list all lines;    H: print help;       E: to exit");

	printf("\033[%d;%dH", 1,1);
}

int main(int argc, char *argv[])
{

	//if(argc != 2)
	//{
	//	cout << "Number of arguments is wrong. Please include only the program name and the textfile in that order!" << endl;
	//	return 0;
	//}

	//Call all the variables;
	fstream file("Textfile.txt", ios::in);

	MyEditor MyEditor;

	string lines;
	
	string line;

	string CopyNode = "NULL";

	string Store;

	string First = "";

	string Second = "";

	string input;

	bool ValidNumber;

	bool flag = true;

	int count = 1;

	int LineNumber;

	if(!file.fail()) //If the file opens
	{
		while (!file.eof()) //While not at the end of the file
		{
			getline(file, lines); //Get the each line

			MyEditor.InsertLine(lines, count); //Insert each line into the list

			count += 1; //Add one to the counter
		}
	}
	file.close(); //Close the file

	MyEditor.InstructionBottomDisplay(); //Display the bottom Instructions

	MyEditor.ListDisplay(); //Display the List

	while (flag == true) //While the flag equals true
	{
		//Define Variables
		First = "";

		Second = "";

		cout << ">";

		getline(cin, input); //Get the user input

		istringstream linein(input); //Split the input
	
		linein >> First; //1st input

		linein >> Second; //2nd input

		ValidNumber = (Second.find_first_not_of("0123456789") == string::npos); //To see if the second value is a number

		if(input == "I" || input =="i") //If the input is an I
		{			
			cout << ">";

			getline(cin,input); //Get the user input

			MyEditor.AddtoEnd(input); //Call the add to end function
		}

		else if(input == "D" || input =="d") //If the input is D
		{
			cout << "Please enter the line you would like to delete!" << endl;
		}

		else if(input == "P" || input =="p") //If the input is P
		{
			cout << "Please enter the line you would like to be pasted!" << endl;
		}

		else if(input == "C" || input =="c") //If the input is C
		{
			cout << "Please enter the line you would like to be copied into the clipboard!" << endl;
		}

		else if(First == "I" || input =="i") //If the first input is I
		{
			if(ValidNumber) //And the second input is a number
			{
				cout << Second << "> ";

				istringstream(Second) >> LineNumber; //Convert the input to a integer

				getline(cin, line); //Get the user input for the text wanted

				MyEditor.InsertLine(line, LineNumber); //Call the insert function
			}

			else //If the line number is not in range
			{
				cout << "Invalid Line number" << endl;
			}
		}

		else if(First == "D" || input =="d") //If the first input is a D
		{
			if(ValidNumber) //and the second input is a Number
			{
				istringstream(Second) >> LineNumber; //Convert the second input into a Integer

				MyEditor.DeleteALine(LineNumber); //Call the delete function
			}
			else //If the line is out of range
			{
				cout << "Invalid Line number" << endl;
			}
		}

		else if(First == "C" || input =="c") //If the first input is a C
		{
			if(ValidNumber) //and the second input is a number
			{
				istringstream(Second) >> LineNumber; //Convert the second input to an integer

				Store = MyEditor.Copy(LineNumber); //Call the copy function

				if (Store != "NULL") //if the copy function does not returns "NULL"
				{
					CopyNode = Store; //Make the Copy Node the return Value
				}
			}
			else //If the second value is out of range
			{
				cout << "Invalid Line number" << endl;
			}
		}

		else if(First == "P" || input =="p") //If the first input is a P
		{
			if(ValidNumber) //If the second input is a number
			{
				if(CopyNode == "NULL") //If There as not been a copy Node given yet
				{
					cout << "There is nothing copied into the clipboard" << endl;
				}
				else
				{
					istringstream(Second) >> LineNumber; //Convert the second input to an integer

					MyEditor.Paste(CopyNode, LineNumber); //Call the Paste function
				}
			}
			else //If the second value is out of range
			{
				cout << "Invalid Line number" << endl;
			}
		}

		else if(input == "L" || input =="l") //if the input is an L
		{
			MyEditor.InstructionBottomDisplay(); //Call the Bottom Display Function

			MyEditor.ListDisplay(); // Call the list Function
		}

		else if(input == "H" || input =="h") //If the input is an H
		{
			if (system("CLS"))
			{
				system("clear"); //Clear the Screen
			}

			MyEditor.HelpDisplay(); //Call the display function
		}

		else if(input == "E" || input =="e") //If the input is an E
		{
			MyEditor.Save(); //Call the save Function

			flag = false; //MAke the Flag False
		}

		else //If the command is not recognized
		{
			cout << "Invalid Command!" << endl;
		}
	}
	return 0; //Quit the program
}