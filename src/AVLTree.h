/*
 * File:   AVLTree.h
 * Author: Charlie Albright
 *
 * NOTE: This AVL Tree has been modified and adapted from an outside source
 * to work in this project. Original implementation developed by Br. David
 * Carlson, last updated August 27, 2009.
 * LINK: http://cis.stvincent.edu/html/tutorials/swd/avltrees/avltrees.html
 *
 * Created on November 14, 2013, 12:01 PM
 */

#include <iostream>
#include <fstream>

#ifndef AVLTREE_H
#define	AVLTREE_H
#include "DataStore.h"
const int LEFTHEAVY = -1;
const int BALANCED = 0;
const int RIGHTHEAVY = 1;

using namespace std;
template <class T>
class AVLTree : public DataStore<T>
{
private:

    class AVLNode
    {
    public:
        AVLNode(T& val):left(NULL), right(NULL), balance(0), data(val) {}
        friend class AVLTree;

    private:
        T data;
        AVLNode* left;
        AVLNode* right;
        int balance;
    };

    AVLNode* root;

    void singleRotateRight(AVLNode *& parent);
    void singleRotateLeft(AVLNode *& parent);
    void doubleRotateRight(AVLNode *& parent);
    void doubleRotateLeft(AVLNode *& parent);

    void updateLeftTree(AVLNode *& parent, bool & fixBalance);
    void updateRightTree(AVLNode *& parent, bool & fixBalance);
    void AVLInsert(AVLNode *& tree, T  data, bool & fixBalance);
    void freeNode(AVLNode *& node);
    void clearTree();
    void clearSubtree(AVLNode *& current);
    bool searchHelper(T& searchData, T* &resultData, AVLNode*& current);
    
    void printHelper(std::ostream& out, AVLNode*& current);

public:

    AVLTree();
    AVLTree(const AVLTree& orig);
    ~AVLTree();

    void insert(T newData);
    bool search(T& searchData, T* &resultData);
    bool isEmpty();
    
    void printToFile(std::ostream& out);

};

template <class T>
AVLTree<T>::AVLTree()
{
    root = NULL;
}

template <class T>
AVLTree<T>::~AVLTree()
{

}


template <class T>
void AVLTree<T>::singleRotateRight(AVLNode*& parent)
{
    //cout<<"SRR"<<endl;
    AVLNode* leftChild;
    leftChild = parent->left;
    leftChild->balance = BALANCED;
    parent->balance = BALANCED;
    parent->left = leftChild->right;
    leftChild->right = parent;
    parent = leftChild;
}

template <class T>
void AVLTree<T>::singleRotateLeft(AVLNode *& parent)
{
    //cout<<"SRL"<<endl;
    AVLNode* rightChild;
    rightChild = parent->right;
    rightChild->balance = BALANCED;
    parent->balance = BALANCED;
    parent->right = rightChild->left;
    rightChild->left = parent;
    parent = rightChild;
}

template <class T>
void AVLTree<T>::doubleRotateRight(AVLNode*& parent)
{
    AVLNode* leftChild = parent->left;
    AVLNode* newParent = leftChild->right;

    if(newParent->balance == RIGHTHEAVY)
    {

        parent->balance = BALANCED;
        leftChild->balance = LEFTHEAVY;
    }
    else if(newParent->balance == BALANCED)
    {

        parent->balance = BALANCED;
        leftChild->balance = BALANCED;
    }
    else
    {

        parent->balance = RIGHTHEAVY;
        leftChild->balance = BALANCED;
    }

    newParent->balance = BALANCED;
    leftChild->right = newParent->left;
    newParent->left = leftChild;
    parent->left = newParent->right;
    newParent->right = parent;
    parent = newParent;
}

template <class T>
void AVLTree<T>::doubleRotateLeft(AVLNode*& parent)
{
    AVLNode* rightChild = parent->right;
    AVLNode* newParent = rightChild->left;


    if(newParent->balance == LEFTHEAVY)
    {

        parent->balance = BALANCED;
        rightChild->balance = RIGHTHEAVY;
    }
    else if(newParent->balance == BALANCED)
    {

        parent->balance = BALANCED;
        rightChild->balance = BALANCED;
    }
    else
    {

        parent->balance = LEFTHEAVY;
        rightChild->balance = BALANCED;
    }

    newParent->balance = BALANCED;
    rightChild->left = newParent->right;
    newParent->right = rightChild;
    parent->right = newParent->left;
    newParent->left = parent;
    parent = newParent;
}

template <class T>
void AVLTree<T>::updateRightTree(AVLNode*& parent, bool& fixBalance)
{
    AVLNode* rightChild = parent->right;

    //cout<<"UPDATING RIGHT TREE!!!!"<<endl;
    if(rightChild->balance == RIGHTHEAVY)
    {
        singleRotateLeft(parent);
        fixBalance = false;
    }
    else if(rightChild->balance == LEFTHEAVY)
    {
        doubleRotateLeft(parent);
        fixBalance = false;
    }
}

template <class T>
void AVLTree<T>::updateLeftTree(AVLNode*& parent, bool& fixBalance)
{
    AVLNode* leftChild = parent->left;

    //cout<<"UPDATING LEFT TREE!!!!"<<endl;
    if(leftChild->balance == LEFTHEAVY)
    {
        singleRotateRight(parent);
        fixBalance = false;
    }
    else if(leftChild->balance == RIGHTHEAVY)
    {
        doubleRotateRight(parent);
        fixBalance = false;
    }
}

template <class T>
void AVLTree<T>::AVLInsert(AVLNode*& tree, T data, bool& fixBalance)
{
    bool rebalanceCurrentNode;
    if(tree != NULL && tree->left != NULL && tree->left->right != NULL)
    if(tree->left->right == tree)
    {
        cout<<"BACK AND FORTH LIKE A SUBWAY CAR"<<endl; //Don't ask
        exit(2);
    }
    if(tree == NULL)
    {
        //cout<<"Word added!"<<endl;
        tree = new AVLNode(data);
        tree->left = NULL;
        tree->right = NULL;
        fixBalance = true;
    }
    else if(data == tree->data)
    {
        //cout<<"Inserted duplicate"<<endl;
    }
    else if(data < tree->data)
    {
        //cout<<"inserting left"<<endl;
        AVLInsert(tree->left, data, rebalanceCurrentNode);

        if(rebalanceCurrentNode)
        {
            if(tree->balance == LEFTHEAVY)
                updateLeftTree(tree, fixBalance);
            else if(tree->balance == BALANCED)
            {
                tree->balance = LEFTHEAVY;
                fixBalance = true;
            }
            else
            {
                tree->balance = BALANCED;
                fixBalance = false;
            }
        }
        else
            fixBalance = false;
    }
    else
    {
        //cout<<"inserting right"<<endl;
        AVLInsert(tree->right, data, rebalanceCurrentNode);

        if (rebalanceCurrentNode)
        {
            if (tree->balance == LEFTHEAVY)
            {
                tree->balance = BALANCED;
                fixBalance = false;
            }
            else if (tree->balance == BALANCED)
            {
                tree->balance = RIGHTHEAVY;
                fixBalance = true;
            }
            else
                updateRightTree(tree, fixBalance);
        }
        else
            fixBalance = false;
    }
}

template <class T>
void AVLTree<T>::freeNode(AVLNode *& node)
{
    delete node;
}

template <class T>
void AVLTree<T>::clearTree()
{
    clearSubtree(root);
    root = NULL;
}

template <class T>
void AVLTree<T>::clearSubtree(AVLNode*& current)
{
    if(current != NULL)
    {
        clearSubtree(current->left);
        clearSubtree(current->right);
        freeNode(current);
    }
}

template <class T>
void AVLTree<T>::insert(T newData)
{
    bool fixBalance = false;
    AVLInsert(root, newData, fixBalance);
}

template <class T>
bool AVLTree<T>::searchHelper(T& searchData, T* &resultData, AVLNode*& current)
{

    if(searchData == current->data)
    {
        //cout<<"SEARCH GOOD"<<endl;
        resultData = &(current->data);
        return true;
    }
    else if(searchData > current->data)
    {
        if(current->right == NULL)
        {
            //cout<<"SEARCH BAD"<<endl;
            return false;
        }
        else
            return searchHelper(searchData, resultData, current->right);
    }
    else if(searchData < current->data)
    {
        if(current->left == NULL)
        {
            //cout<<"SEARCH BAD"<<endl;
            return false;
        }
        else
            return searchHelper(searchData, resultData, current->left);
    }
}

template <class T>
bool AVLTree<T>::search(T& searchData, T* &resultData)
{
    return searchHelper(searchData, resultData, root);
}

template <class T>
bool AVLTree<T>::isEmpty()
{
    if(root == NULL)
        return true;
    else
        return false;
}

template <class T>
void AVLTree<T>::printHelper(std::ostream& out, AVLNode*& current)
{
    if(current->left == NULL)
    {
        out << current->data << endl;
        if(current->right != NULL)
            printHelper(out, current->right);
    }
    else
    {
        printHelper(out, current->left);
        out << current->data << endl;
        if(current->right != NULL)
            printHelper(out, current->right);
    }
}

template <class T>
void AVLTree<T>::printToFile(std::ostream& out)
{
    printHelper(out, root);
}

#endif	/* AVLTREE_H */

