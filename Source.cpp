// Binary Search Tree Implementation in C++
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct BstNode {
	int data;
	BstNode* left;
	BstNode* right;
};


/* bool Search
Searches through the Binary Search Tree until it finds the value
If found returns true, else returns false
*/
bool Search(BstNode* root, int data) {
	if (root == NULL) return false;
	else if (root->data == data) return true;
	else if (data <= root->data) return Search(root->left, data);
	else return Search(root->right, data);
}


/* BstNode* FindMinNode
Finds the node that holds the lowest value held by the Binary Search Tree
*/
BstNode* FindMinNode(BstNode* root) {
	BstNode* min = root;
	if (root->right != NULL && root->left != NULL) 	{
		BstNode *tempLeft;
		tempLeft = root->left;
		min = FindMinNode(tempLeft);
	}
	else if (root->right == NULL && root->left == NULL || root->left == NULL) {
		min = root;
	}
	else if (root->right == NULL) {
		BstNode *tempLeft;
		tempLeft = root->left;
		min = tempLeft;
	}
	cout << "this is the minimum : " << min->data << endl;
	return min;
}


/* int FindMin
Find the min value held within the Binary Search Tree
*/
int FindMin(BstNode* root) {
	if (root == NULL) {
		cout << "Error: Tree is empty" << endl;
		return -1;
	}
	while (root->left != NULL) {
		root = root->left;
	}
	return root->data;
}


/* int FindMax
Finds the max value held within the Binary Search Tree
*/
int FindMax(BstNode* root) {
	if (root == NULL) {
		cout << "Error: Tree is empty" << endl;
		return -1;
	}
	while (root->right != NULL) {
		root = root->right;
	}
	return root->data;
}

/* BstNode* Delete
Deletes a specific BstNode that holds a value in data equal to the value for data
which was passed into the function
*/
BstNode* Delete(BstNode* root, int data) {
	if (root == NULL) return root;
	else if (data < root->data) root->left = Delete(root->left, data);
	else if(data > root->data) root->right = Delete(root->right, data);
	else {
		//If we found the node
		//Case-1: No child
		if (root->left == NULL && root->right == NULL) {
			delete root;
			root = NULL;
		}
		//Case-2: Either right OR left child
		else if (root->left == NULL) {
			BstNode *temp = root;
			root = root->right;
			delete temp;
		}
		else if (root->right == NULL) {
			BstNode *temp = root;
			root = root->left;
			delete temp;
		}
		//Case-3: 2 children
		else {
			BstNode *temp = FindMinNode(root->right);
			root->data = temp->data;
			root->right = Delete(root->right, temp->data);
		}
	}
	return root;
}


/* BstNode* GetNewNode
Creates a new node dynamically and fills it's values
*/
BstNode* GetNewNode(int data) {
	BstNode* newNode = new BstNode();
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}


/* BstNode* Insert
Inserts a new node in the correct position of the tree
*/
BstNode* Insert(BstNode* root, int data) {
	// We can also use a pointer to point and pass in &root to get the address
	if (root == NULL) { //empty tree
		root = GetNewNode(data);
	}
	else if (data <= root->data) {
		root->left = Insert(root->left, data);
	}
	else {
		root->right = Insert(root->right, data);
	}
	return root;
}

/* int FindHeight
Finds the height of a Binary Search Tree or specific node
*/
int FindHeight(BstNode* root) {
	if (root == NULL) return -1;

	return max(FindHeight(root->left), FindHeight(root->right)) + 1;
}

/* void LevelOrder
Allows you to traverse a Binary tree using Level Order Traversal
*/
void LevelOrder(BstNode *root) {
	if (root == NULL) return;
	queue<BstNode*> Q;
	Q.push(root);
	//While there is at least one discovered node
	while (!Q.empty()) {
		BstNode* current = Q.front();
		cout << current->data << " ";
		if (current->left != NULL) Q.push(current->left);
		if (current->right != NULL) Q.push(current->right);
		Q.pop(); //Removes the front element
	}
}

/* void Preorder
Traverses a Binary tree in order of DLR
*/
void Preorder(BstNode *root) {
	if (root == NULL) return;
	cout << root->data << " ";
	Preorder(root->left);
	Preorder(root->right);
}

bool IsSorted(int maxValue, int minValue) {
	if (minValue <= maxValue) return true;
	else return false;
}

/* void Inorder
Traverses a Binary tree in order of LDR
*/
bool Inorder(BstNode *root, int maxValue, int minValue) {
	if (root == NULL) return true;
	if (IsSorted(maxValue, root->data) && IsSorted(root->data, minValue)) {
		Inorder(root->left, root->data, minValue);
		cout << root->data << " ";
		Inorder(root->right, maxValue, root->data);
		return true;
	}
	else {
		Inorder(root->left, root->data, minValue);
		cout << root->data << " ";
		Inorder(root->right, maxValue, root->data);
		return false;
	}
}


/* void Postorder
Traverses a Binary tree in order of LRD
*/
void Postorder(BstNode *root) {
	if (root == NULL) return;
	Postorder(root->left);
	Postorder(root->right);
	cout << root->data << " ";
}

/* bool IsSubtreeLesser
Checks if all elements of a given subtree are less than the passed in value
*/
bool IsSubtreeLesser(BstNode *root, int value) {
	if (root == NULL) return true;
	if (root->data <= value && IsSubtreeLesser(root->left, value)
		&& IsSubtreeLesser(root->right, value)) return true;
	else return false;
}


/* bool IsSubtreeGreater
Checks if all elements of a given subtree are greater than the passed in value
*/
bool IsSubtreeGreater(BstNode *root, int value) {
	if (root == NULL) return true;
	if (root->data <= value && IsSubtreeGreater(root->left, value)
		&& IsSubtreeGreater(root->right, value)) return true;
	else return false;
}

/* bool IsBinarySearchTree
Checks if a Binary Tree qualifies as a Binary Search Tree or not
*/
bool IsBinarySearchTree(BstNode *root) {
	if (root == NULL) return true;
	if (IsSubtreeLesser(root->left, root->data) && IsSubtreeGreater(root->right, root->data)
		&& IsBinarySearchTree(root->left) && IsBinarySearchTree(root->right)) return true;
	else return false;
}

/* bool IsBstUtil
Checks if a Binary Tree is a Binary Search Tree or not also allowing for duplicates (best performance)
Replace >= and <= with > and < respectively if you would like to not allow duplicates in order to quality as BST
*/
bool IsBstUtil(BstNode *root, int minValue, int maxValue) {
	if (root == NULL) return true;
	if (root->data >= minValue && root->data <= maxValue
		&& IsBstUtil(root->left, minValue, root->data)
		&& IsBstUtil(root->right, root->data, maxValue))
		return true;
	else return false;
}

/* bool BetterIsBinarySearchTree
Calls IsBstUtil and passes it the necessary values
*/
bool BetterIsBinarySearchTree(BstNode* root) {
	return IsBstUtil(root, INT_MIN, INT_MAX);
}

int main() {
	BstNode* root = NULL; //Create an empty tree
	root = Insert(root, 15);
	Insert(root, 10);
	Insert(root, 20);
	Insert(root, 25);
	Insert(root, 8);
	Insert(root, 12);
	Insert(root, 17);
	Insert(root, 1);
	Insert(root, 12);

	int min = FindMin(root);

	cout << "The minimum value in the Binary Search Tree is : " << min << endl;

	if (BetterIsBinarySearchTree(root)) {
		cout << "This is indeed a Binary Search Tree" << endl;
	}
	else {
		cout << "This is NOT a Binary Search Tree" << endl;
	}

	if (!Inorder(root, INT_MAX, INT_MIN)) {
		cout << "It is NOT a binary tree" << endl;
	}
	else {
		cout << "it is BST" << endl;
	}
}

