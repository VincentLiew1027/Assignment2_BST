#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode* cur) {
	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode* cur) {
	if (cur == NULL) return;
	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode* cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode* cur, int& count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode* cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)) {

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode* cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode* cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode* cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode* cur, BTNode* newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)) {
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode* pre, BTNode* cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)) {
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode* pre, BTNode* cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode* cur) {
	BTNode* is, * isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}


#pragma region Own Functions

bool BST::deepestNodes()
{
	if (root == NULL)
	{
		return false; //empty tree
	}

	int cur_level = 0; // current root or level of the tree
	int level = findLevel(root);
	deepestNodes2(root, cur_level, level);
	return true;
}

void BST::deepestNodes2(BTNode* cur, int cur_level, const int& level)
{
	if (cur == NULL) return;
	cur_level++;

	if (cur_level == level)
	{
		cur->item.print(cout);
		return;
	}
	deepestNodes2(cur->left, cur_level, level);
	deepestNodes2(cur->right, cur_level, level);

}

bool BST::display(int order, int source)
{
	if (root == NULL)
	{
		cout << "The tree is empty. ";
		return false;
	}
	if (source == 1) //print to screen
	{
		if (order == 1) inOrderPrint(); //using the provided inOrderPrint function to print ascending order
		else desc_Print(); // descending order
	}
	else //save to file
	{
		fstream outfile("student-info.txt", ios::out);
		if (!outfile) return false;
		if (order == 1) asc_Save(outfile); // ascending order
		else desc_Save(outfile); // descending order
		outfile.close();
	}

	return true;
}


void BST::desc_Print()
{
	if (root == NULL) return;
	else desc_Print2(root);
	cout << endl;
}

void BST::desc_Print2(BTNode* cur)
{
	if (cur == NULL) return;
	desc_Print2(cur->right);
	cur->item.print(cout);
	desc_Print2(cur->left);
}

void BST::asc_Save(fstream& outfile)
{
	if (root == NULL) return;
	asc_Save2(root, outfile);
	cout << "Successfully save to file.\n";
}

void BST::asc_Save2(BTNode* cur, fstream& outfile)
{
	if (cur == NULL) return;
	asc_Save2(cur->left, outfile);

	cur->item.print(outfile);
	asc_Save2(cur->right, outfile);
}

void BST::desc_Save(fstream& outfile)
{
	if (root == NULL) return;
	desc_Save2(root, outfile);
	cout << "Successfully save to file.\n";
}

void BST::desc_Save2(BTNode* cur, fstream& outfile)
{
	if (cur == NULL) return;
	desc_Save2(cur->right, outfile);
	cur->item.print(outfile);
	desc_Save2(cur->left, outfile);
}

void BST::cloneTree(BTNode* a, BTNode* b) {

	if (a == NULL)

		return;

	b = new BTNode();

	b->item = a->item;

	b->left = b->right = NULL;

	cloneTree(a->left, b->left);

	cloneTree(a->right, b->right);

}

bool BST::CloneSubtree(BST t1, type item)
{
	int key = item.id;

	BTNode* curr = t1.root;

	if (curr == NULL)

		return false;

	// Traverse until root reaches to dead end

	while (curr != NULL) {

		// pass right subtree as new tree

		if (key > curr->item.id)

			curr = curr->right;



		// pass left subtree as new tree

		else if (key < curr->item.id)

			curr = curr->left;

		else

			break; // if the key is found break from the while loop

	}

	// if the key is not found return false





	// cloning the tree

	cloneTree(curr, this->root);
	return true;
}

bool BST::printAncestor(type item)
{
	bool check = false;

	if (root == NULL)
	{
		cout << "The tree is empty.";
		return false;
	}

	if (!printAncestor2(root, item, check))
	{
		cout << "Could not found the matching item. ";
		return false;
	}
	if (check == false) //return false if item do not have ancestor
		return false;
	return true;
}

bool BST::printAncestor2(BTNode* cur, const type& item, bool& check)
{
	if (cur == NULL) return false;
	if (cur->item.compare2(item)) return true;
	//if the item is the ancestor for the target item, print the item
	if (printAncestor2(cur->left, item, check) || printAncestor2(cur->right, item, check))
	{
		cur->item.print(cout);
		check = true; //the target item has ancestor, flag = true
		return true;
	}
	return false;
}

bool BST::printSpiral()
{
	return true;
}

int BST::findLevel(BTNode* cur)
{
	if (cur == NULL)
	{
		return 0;
	}

	int left_level = findLevel(cur->left);
	int right_level = findLevel(cur->right);

	if (left_level > right_level)
	{
		return left_level + 1;
	}
	else
	{
		return right_level + 1;
	}
}

#pragma endregion




