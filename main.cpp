// Sample driver
// EE 312 Fall 2018
//
// The BST should work for any data type or object.
// Other user created objects must have the << operator overloaded for 
// output.
//

#include <iostream>
#include <fstream>
#include "BST312.h"

using namespace std;

template <typename T>
void print(vector<T> vec){
    for(int i = 0 ; i < vec.size() ; i++){
        cout << vec[i] << endl;;
    }
}

int main() {

    ifstream inFile;
    inFile.open("test.txt");

    BST_312<string> bst;
   
    string s;
    inFile >> s;
    while (inFile) {;
        cout << "inserting ... " << s << endl;
        bst.insertItem(s);
        inFile >> s;
    }

    cout << "postorder traversal is " << endl;
    print(bst.postOrderTraversal());
    cout << endl;

    cout << "preorder traversal is " << endl;
    print(bst.preOrderTraversal());
    cout << endl;

    cout << "inorder traversal is " << endl;
    print(bst.inOrderTraversal());
    cout << endl;

    cout << "Remove items " << endl;
    cout << "number of nodes in tree before delete is " << bst.countNodes() << endl;
    s = "tree";
    bst.deleteItem(s);
    print(bst.postOrderTraversal());
    cout << endl;
    cout << "number of nodes in tree after delete is " << bst.countNodes() << endl;
    cout << endl;

    cout << "Remove items 2" << endl;
    cout << "number of nodes in tree before delete is " << bst.countNodes() << endl;
    s = "a";
    bst.deleteItem(s);
    print(bst.postOrderTraversal());
    cout << endl;
    cout << "number of nodes in tree after delete is " << bst.countNodes() << endl;
    cout << endl;

    s = "212";
    cout << "Is 212 in the BST?" << endl;
    if(bst.isItemInTree(s)){
        cout << "Yes" << endl;
    }
    else{
        cout << "No" << endl;
    }

    s = "the";
    cout << "Is the in the BST?" << endl;
    if(bst.isItemInTree(s)){
        cout << "Yes" << endl;
    }
    else{
        cout << "No" << endl;
    }

    bst.makeEmpty();

    cout << endl << "The number of nodes after I make the BST empty is " << bst.countNodes();

    s = "AJ is a God";
    bst.insertItem(s);
    cout << endl << "postorder traversal is " << endl;
    print(bst.postOrderTraversal());
    cout << endl;



}

