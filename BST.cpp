//Project 2 of Alvaro Leon Parra / BST
#include <iostream>
#include<conio.h>
#include<stdlib.h>
#include<fstream>
using namespace std;

struct Node{
	int data;
	Node *right;
	Node *left;
	Node *parent;
};

//Prototypes
void menu();
Node *makeNode(int,Node *);
void insertNode(Node *&,int,Node *);
void showTree(Node *,int);
bool searchNode(Node *,int);
void deleteN(Node *,int);
void deleteNode(Node *);
Node *minimum(Node *);
void switchN(Node *, Node *);
void destroyNode(Node *);
void clearTree(Node *);
void deleteTree(Node *&);

Node *tree = NULL;



int main() {
	
	menu();
	return 0;
}


//Function of the menu
void menu(){
	int data,option,count=0;
	char answer;
	ifstream myfile;
	string myFileName;
	
	cout<< "//WELCOME//\n";
	cout << "Would you like to open a File (Y/y): " << endl;
	cout << "Would you like to continue without opening a file(Press any key): "<<endl;
	cout << "=> ";
	cin >> answer;
	if(answer == 'Y' || answer == 'y'){
		cout<< "Enter a file name to start: ";
		cin >> myFileName;
			
		myfile.open(myFileName);																			// check to see if the file is found , if so this one will continue , if its not found the program will exit.
		if (myfile.is_open())
		{
      	  	cout << "File Opened Successfully." << endl;
        	while ( myfile >> data)	{
        		insertNode(tree,data,NULL);
        		cout<<"Node "<<data<<" inserted successfully."<<endl;
        		showTree(tree,count);
        		system("pause");
        		//cout << "Press 'ENTER' to continue.." ;
        		//cin.ignore();
			}
		}
		else
    	{
     	   	cerr << "File not found!" << endl;
        	exit(1);
    	}
    	myfile.close();
    }
	//else if(answer == 'N' || answer == 'n'){
	
	
//}
	do{
		cout << "\t.:Menu:."<<endl;
		cout << "1. Insert new Node"<<endl;
		cout << "2. Show the tree"<<endl;
		cout << "3. Search for a node"<<endl;
		cout << "4. Delete a node"<<endl;
		cout << "5. Delete Tree"<< endl;
		cout << "6. Exit" << endl;
		cout<<"Option: ";
		cin>> option;
		
		if(option == 1 || option == 2 || option==3 || option ==4 
			|| option == 5 || option == 6){
			
			switch(option){
				case 1: cout<<"\nNumber[0-99]: ";
						cin>>data;
						if (data >=0 && data <=99){
							if(searchNode(tree,data)==true)
							{
								cout << "The value is already on the tree";
							}
							else{
								insertNode(tree,data,NULL); // Insert a new node
							}
							cout <<endl;
							system("pause");
							break;
						}
						else {
							cout << " Try again[0-99]\n";
							system("pause");
							break;
						}
				case 2: cout<< "\nShowing the tree:\n\n";
						showTree(tree,count);
						cout<<endl;
						system("pause");
						break;
					
				case 3: cout<< "\nNode to search for[0-99]: ";
						cin>> data;
						cout << "Looking for["<<data<<"] ->\n";
						if(searchNode(tree,data)==true){
							cout<<"\nThe node "<< data <<" has been found.!"<<endl;
							showTree(tree,count);
						}
						else{
							cout<<"\nThe node hasn't been found.";
						}
						cout << endl;
						system("pause");
						break;
				case 4: cout<<"\nWhat Node would you like to delete?[0-99]: ";
						cin >> data;
						deleteN(tree,data);
						cout<<endl;
						showTree(tree,count);
						cout<<endl;
						system("pause");
						break;
			
				case 5: deleteTree(tree); 
   						cout << "Tree deleted "; 
   						cout<<endl;
						system("pause");
						break;
			
			}
			system("cls");
		
		}
		else if(option !=1 && option !=2 && option !=3 && option !=4
				&& option !=5 && option !=6)						// if something that is not [6][5][4][3][2][1] is inserted , program will say try again and clear input.
		{
			system("cls");
			cin.clear();                   
            cin.ignore(1000, '\n');         
			cout<<"Try again [1][2][3][4][5][6]";
			cout<<"\n";
		}
	}while(option !=6);
	
	cout << "!!SEE YOU SOON!!" << endl;

}
//Function to make a new node.
Node *makeNode(int n,Node *parent)
{
	Node *new_node= new Node();
	
	new_node->data = n;
	new_node->right = NULL;
	new_node->left= NULL;
	new_node->parent=parent;
	
	return new_node;	
}


//Function to insert nodes on the tree.

void insertNode(Node *&tree,int n,Node *parent)
{
	if(tree == NULL){ // If the tree is empty.
		Node *new_node = makeNode(n,parent);
		tree = new_node;
	}
	else{		// If the tree has one node or more.
		int valueRoot = tree->data;  // Obtain value of the root.
		if(n<valueRoot){			// If the element is less than the root it will go to the left .
			insertNode(tree->left,n,tree);
		}
		else{						// If the element is more than the root it will go to the right.
			insertNode(tree->right,n,tree);  
		}
	}
	
}

//Function to show the tree
void showTree(Node *tree, int count)
{
	if(tree == NULL){			//If the tree is empty.
		return;
	}
	else{
		showTree(tree->right,count+1);
		for(int i=0;i<count;i++){
			cout<<"   ";
		}
		cout<<tree->data<<endl;
		showTree(tree->left,count+1);
	}
}

//Function to search for an element on the tree
bool searchNode(Node *tree,int n)
{
//	cout<< tree->data << "->";
	if(tree == NULL){			//If the tree is empty , returns false.
		return false;
	}
	else if(tree->data == n){	//If the node its equal to the int , returns true.
		return true;
	}
	else if(n< tree->data){
		cout << "Searching at node: " << tree -> data << endl;
		return searchNode(tree->left,n);
	}
	else{
		cout << "Searching at node: " << tree -> data << endl;
		return searchNode(tree->right,n);
	}
}

// Function to delete a node
void deleteN(Node *tree,int n)
{
	if(tree == NULL){		// If the tree is empty
		return;
	}
	else if(n < tree->data){		// If the value is less than the node
		deleteN(tree->left,n);	// Search in the left subtree
	}
	else if(n > tree->data){
		deleteN(tree->right,n);
	}
	else{
		deleteNode(tree);
	}
	
}
//Function to determine the node most left possible
Node *minimum(Node *tree){
	if(tree == NULL){		//If the tree is empty
		return NULL;		// Return Null
	} 
	if(tree->left){			// If there is a left child
		return minimum(tree->left);	// We look for the most left child
	}
	else{	// If it doesnt have a child
		return tree;	// Return the same node
	}
}
//Function to switch two Nodes to point to the parent when deliting
void switchN(Node *tree,Node *newNode){
	if(tree->parent){	//If there is a parent, we have to point to the new child
		if(tree->parent->left){
			if(tree->data == tree->parent->left->data){
				tree->parent->left = newNode;
			}
		}
		else if(tree->parent->right){
		
			if(tree->data ==tree->parent->right->data){
			tree->parent->right = newNode;
			}
		}
	}
	if(newNode){	// If the is a child , we have to point it to the new parent
		newNode->parent = tree->parent;
	}
}

//Function to destroy the deleted Node
void destroyNode(Node *node){
	node->left = NULL;
	node->right	= NULL;
	
	delete node;
}

// Function to delete the found node
void deleteNode(Node *nodeDelete)
{
	if(nodeDelete->left && nodeDelete->right){   // If there is a right and left child
		Node *younger = minimum(nodeDelete->right);
		nodeDelete->data = younger->data;
		deleteNode(younger);
	}
	else if(nodeDelete->left){			// If there is only a left child
		switchN(nodeDelete,nodeDelete->left);
		destroyNode(nodeDelete);
	}
	else if(nodeDelete->right){			//If there is only a right child
		switchN(nodeDelete,nodeDelete->right);
		destroyNode(nodeDelete);
	}
	else {			// If it's a leaf
		switchN(nodeDelete,NULL);
		destroyNode(nodeDelete);	
	}
}

// Function to clear the tree
void clearTree(Node *node) 
{ 
    if (node == NULL) return; 
  
    // first delete both subtrees 
    clearTree(node->left); 
    clearTree(node->right); 
  
    // then delete the node 
    cout << "Deleting node: " << node->data << endl; 
    //destroyNode(node);
    delete node;
} 

// Function that Deletes a tree and sets the root as NULL 
void deleteTree(Node*& node_root) 
{ 
    clearTree(node_root); 
    node_root = NULL; 
} 