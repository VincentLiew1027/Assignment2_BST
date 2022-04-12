#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	<string>
#include	"BST.h"
#include    "Student.h"

using namespace std;

bool readFile(char *, BST *);
int menu();

int main() {
	//testing
	BST s;
	int option, order, source;
	char studentFile[25] = "stundet.txt";

	
	do
	{
		Student s1; //to store user input
		option = menu();
		switch (option)
		{
		case 1:
			if (readFile(studentFile, &s))
				cout << "Successfully read the file.\n";
			else
				cout << "Unable to read the file.\n";
			break;
			
		case 2:
			cout << "The deepest nodes are: \n";
			if (!s.deepestNode())
				cout << "The tree is empty.\n";
			break;
		case 3:
			cout << "How would you like to display the student information?\n"
				<< "1. Print to screen.\n"
				<< "2. Save to file.\n"
				<< "\nEnter your choice: ";
			cin >> source;
			while (source < 1 || source > 2)
			{
				cout << "\nInvalid choice. Please enter again: ";
				cin >> source;
			}
			cout << "\nIn what order you wish to display the student information ? \n"
				<< "1. Ascending order.\n"
				<< "2. Descending order.\n"
				<< "\nEnter your choice: ";
			cin >> order;
			while (order < 1 || order > 2)
			{
				cout << "\nInvalid choice. Please enter again: ";
				cin >> order;
			}
			if (!s.display(order, source))
				
				cout << "Unable to display the student information.\n";
			break;
		case 4:
			cout << "Clone Subtree ";
			cin >> s1.id;
			if (!s.CloneSubtree())
				cout << "Unable to print the subtree.\n";
			else
				cout << "SubTree clone succesfully" << endl;
			break;
		case 5:
			cout << "Please enter the student ID that you would like to check for the student's ancestors: ";
				cin >> s1.id;
			if (!s.printAncestor(s1))
				cout << "There is no ancestor for this item.\n";
			break;
		case 6:
			cout << "Print Spiral" << endl << endl;
			
			break;
		
		default:
			
				cout << "The program is exiting.\n";
		}

		system("pause");
		system("cls");
	} while (option != 8);
	return 0;
}

bool readFile(char *filename, BST *s) //task 1
{
	fstream infile(filename, ios::in);
	int counter = 0; //count the number of student records successfully recorded
	if (!infile) return false;
	else
	{
		string remover; //remove useless line
		while (getline(infile, remover, '='))
		{
			Student s1;
			if (infile.eof())
				break;
			infile >> s1.id;
			getline(infile, remover, '=');
			infile.get();
			infile.getline(s1.name, 30);
			getline(infile, remover, '=');
			infile.get();
			infile.getline(s1.address, 100);
			getline(infile, remover, '=');
			infile.get();
			infile.getline(s1.DOB, 20);
			getline(infile, remover, '=');
			infile.get();
			infile.getline(s1.phone_no, 10);
			getline(infile, remover, '=');
			infile.get();
			infile.getline(s1.course, 5);
			getline(infile, remover, '=');
			infile >> s1.cgpa;
			
			if (!s->insert(s1))
					cout << "Unable to insert records with student ID: " <<
					s1.id << endl;
				counter++;
		}
	}
	cout << "\nThe number of student records successfully read: " << counter << endl;
	infile.close();
	return true;
}

int menu()
{
	int choice;
	cout << "(1) Read data to BST\n"
		<< "(2) Print deepest nodes\n"
		<< "(3) Display student\n"
		<< "(4) Clone Subtree\n"
		<< "(5) Print Ancestor\n"
		<< "(6) Print Spiral\n"
		<< "(7) Exit\n\n"
		<< "Please enter your choice: ";
	cin >> choice;
	while (choice < 1 || choice > 7)
	{
		cout << "\nInvalid choice. Please enter again: ";
		cin >> choice;
	}
	return choice;
}

