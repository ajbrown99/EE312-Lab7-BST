
/*  BST312.h
  CS 312 Fall 2018

  a simple implementation of a binary search tree


*/

#ifndef BST_312_H
#define BST_312_H

#include <cstdlib>  // Provides size_t
#include <iostream>
#include <vector>

using namespace std;

template<class ItemType>
class BST_312 {
public:

    BST_312();

    //Copy constructor
    BST_312(const BST_312 & src);

    ~BST_312();

/****************************
makeEmpty

Function: Removes all the items from the BST.
Preconditions: BST has been initialized
Postconditions: All the items have been removed
*****************************/
    void makeEmpty();

/****************************
isEmpty

Function: Checks to see if there are any items in the BST.
Preconditions: BST has been initialized
Postconditions: Returns true if there are no items in the BST, else false.
*****************************/
    bool isEmpty() const;

/****************************
isFull

Function: Determines if you have any more room to add items to the BST
Preconditions: BST has been initialized
Postconditions: Returns true if there is no more room to add items, else false
*****************************/
    bool isFull() const;

/****************************
insertItem

Function: Adds newItem to the BST.
Preconditions: BST has been initialized and is not full.
Postconditions: newItem is in the proper position for a BST.
*****************************/
    void insertItem(const ItemType &);

/****************************
deleteItem

Function: Removes target from BST.
Preconditions: BST has been initialized.
Postconditions: If found, element has been removed from BST.
*****************************/
    void deleteItem(const ItemType& newItem);

/****************************
countNodes

Function: Counts the number of nodes in the BST
Preconditions: BST has been initialized.
Postconditions: returns the number of nodes in the BST
*****************************/
    int countNodes();

/****************************
preOrderTraversal

Function: Returns the preOder (Node, Left, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> preOrderTraversal();

/****************************
inOrderTraversal

Function: Returns the inOder (Left, Node, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> inOrderTraversal();

/****************************
postOrderTraversal

Function: returns the postOder (Left, Right, Node) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> postOrderTraversal();

/********************
 isItemInTree

Function: Determines if a given Item is in tree.
Preconditions: BST has been initialized.
Postconditions: none
*****************************/

    bool isItemInTree(const ItemType& item);


private:
    struct TreeNode {
        ItemType data;
        TreeNode *left;
        TreeNode *right;
    };

    TreeNode * root;


    void insertItem(TreeNode*& t, const ItemType& newItem);
    void inOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    int countNodes(TreeNode* t) const;
    void deleteNode(TreeNode*& node);
    void makeEmpty(TreeNode*& t);
    void deleteItem(TreeNode*& t, const ItemType& newItem);
    void getPredecessor(TreeNode* t, ItemType& data);
    void preOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void postOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void copyTree(TreeNode*& copy, const TreeNode *originalTree);

    bool findItem(TreeNode* t,const ItemType& item);

};

/*******************************
//Function implementations
********************************/

template<class ItemType>
BST_312<ItemType>::BST_312 ()
{
    root = NULL;
}

template<class ItemType>
BST_312<ItemType>::BST_312(const BST_312 & src)
{
    copyTree(root, src.root);
}

template<class ItemType>
BST_312<ItemType>::~BST_312()
{
    makeEmpty();

}


template<class ItemType>
void BST_312<ItemType>::copyTree(TreeNode*& copy, const TreeNode* originalTree)
{
    if (originalTree == NULL)
        copy = NULL;
    else
    {
        copy = new TreeNode;
        copy->data = originalTree->data;

        copyTree(copy->left, originalTree->left);
        copyTree(copy->right, originalTree->right);
    }
}


template<class ItemType>
void BST_312 <ItemType>::deleteNode(TreeNode*& t)
{
    ItemType info;
    TreeNode *tempPtr;

    tempPtr = t;

    if (t->left == NULL)
    {
        t = t->right;
        delete tempPtr;
    }
    else if (t->right == NULL)
    {
        t = t->left;
        delete tempPtr;
    }
    else
    {
        getPredecessor(t->left, info);
        t->data = info;
        deleteItem(t->left, info);
    }
}



//find largest in left subtree
template<class ItemType>
void BST_312 <ItemType>::getPredecessor(TreeNode* t, ItemType& data)
{

    while (t->right != NULL)
        t = t->right;

    data = t->data;

}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(TreeNode*& t, const ItemType& newItem)
{
    if (t == NULL)
        return;
    else if (newItem < t->data)
        deleteItem(t->left, newItem);
    else if (newItem > t->data)
        deleteItem(t->right, newItem);
    else
        deleteNode(t);
}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(const ItemType& newItem)
{
    deleteItem(root, newItem);

}

//This function deletes the entire BST
template<class ItemType>
void BST_312 <ItemType>::makeEmpty(TreeNode*& t)
{
    //YOUR CODE GOES HERE

    //If no BST,do nothing
    if(t == NULL){
        return;
    }
    
    //recursive call to delete all left subtrees
    makeEmpty(t->left);

    //recursive call to delete all right subtrees
    makeEmpty(t->right);
 
    //delete the node
    deleteNode(t);


}
//Post-condition:the entire BST is deleted

template<class ItemType>
void BST_312 <ItemType>::makeEmpty()
{
    makeEmpty(root);
    root = NULL;
}

template<class ItemType>
bool BST_312 <ItemType>::isEmpty() const
{
    return root == NULL;
}



template<class ItemType>
bool BST_312 <ItemType>::isFull() const
{
    try
    {
        TreeNode *temp = new TreeNode;
        delete temp;
        return false;
    }
    catch (std::bad_alloc)
    {
        return true;
    }

}

//This function inserts a unique item into the BST
template<class ItemType>
void BST_312 <ItemType>::insertItem(TreeNode*& t, const ItemType& newItem)
{

    //YOUR CODE GOES HERE

    //add the item if no BST
    if(t == NULL){
        t = new TreeNode();
        t->data = newItem;
        return;
    }
    //if less than root,then go to left
    if(newItem < t->data){
        insertItem(t->left,newItem);
    }
    //if bigger than root,then go to the right
    else{
        insertItem(t->right,newItem);
    }

}
//Post-condition:the item was successfully inserted into the BST

template<class ItemType>
void BST_312 <ItemType>::insertItem(const ItemType& newItem)
{
    //YOUR CODE GOES HERE

    //if the item is already in the BST or the BST is full,do NOT insert
    if(isItemInTree(newItem) || isFull()){
        return;
    }
    else{
        insertItem(root,newItem);
    }
}


//this function counts the number of nodes in BST
template<class ItemType>
int BST_312 <ItemType>::countNodes(TreeNode* t) const
{
    //YOUR CODE GOES HERE

    //if root != NULL,then there is at least 1 node
    int totalNodes = 1;

    //counts all left subtrees
    if(t->left != NULL){
        totalNodes = totalNodes + countNodes(t->left);
    }

    //counts all the right subtrees
    if(t->right != NULL){
        totalNodes = totalNodes + countNodes(t->right);
    }
    return totalNodes;

}
//Post-condition:returns the number of nodes in the BST

template<class ItemType>
int BST_312 <ItemType>::countNodes()
{
    //YOUR CODE GOES HERE

    TreeNode *ptr = root;

    int numNodes = 0;
    
    //check to see if BST is empty
    if(isEmpty()){
        return 0;
    }
    numNodes = countNodes(ptr);
    return numNodes;



}

//This function uses a preOrderTraversal to print out the BST
template<class ItemType>
void BST_312 <ItemType>::preOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    //YOUR CODE GOES HERE

    if(t != NULL){
        result.push_back(t->data);
        preOrderTraversal(t->left,result);
        preOrderTraversal(t->right,result);
    }
}
//Post-condition:the result is placed into a vector with the algorithm Node,left,right

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::preOrderTraversal()
{
    //YOUR CODE GOES HERE

    TreeNode *ptr = root;
    vector<ItemType> answer;

    if(ptr == NULL){
        return answer;
    }
    preOrderTraversal(ptr,answer);
    return answer;

}

//This function uses inOderTraversal to print out the BST
template<class ItemType>
void BST_312 <ItemType>::inOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    //YOUR CODE GOES HERE

    if(t != NULL){
        inOrderTraversal(t->left,result);
        result.push_back(t->data);
        inOrderTraversal(t->right,result);
    }


}
//Post-condtion:the result is placed into a vector with the algorithm left,Node,right

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::inOrderTraversal()
{
    //YOUR CODE GOES HERE

    TreeNode *ptr = root;
    vector<ItemType> answer;

    if(ptr == NULL){
        return answer;
    }
    inOrderTraversal(ptr,answer);
    return answer;

}

//this function uses postOrderTraversal to print out the BST
template<class ItemType>
void BST_312 <ItemType>::postOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{

    //YOUR CODE GOES HERE
    if(t != NULL){
        postOrderTraversal(t->left,result);
        postOrderTraversal(t->right,result);
        result.push_back(t->data);
    }
}
//the result is placed into a vector with the algorithm left,right,Node

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::postOrderTraversal()
{
    //YOUR CODE GOES HERE

    TreeNode *ptr = root;
    vector<ItemType> answer;

    if(root == NULL){
        return answer;
    }
    postOrderTraversal(ptr,answer);
    return answer;
}

//this is the helper function for isItemInTree
//it returns true or false whether a specfic item is in the BST
template<class ItemType>
bool BST_312 <ItemType>::findItem(TreeNode* t, const ItemType& item){

    //if the root is NULL,then the item can not 
    //be in the BST
    if(t == NULL){
        return false;
    }
    //if item is less than tree,go left
    else if(item < t->data){
        return findItem(t->left,item);
    }
    //if item is bigger than tree,go right
    else if(t->data < item){
        return findItem(t->right,item);
    }
    else{
        return true;
    }


}
//Post-condition:returns whether or not the item is in the BST

template<class ItemType>
bool BST_312 <ItemType>::isItemInTree(const ItemType& item)
{

  //YOUR CODE GOES HERE

  TreeNode *ptr = root;

  return findItem(ptr,item);

}
#endif

