#include "SearchNode.h"
#include "AVLTree.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "pugiconfig.h"
#include "pugixml.h"
#include "XMLParser.h"

using namespace std;
using namespace pugi;

#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H


class IndexHandler
{
public:
    IndexHandler();                     //Parses upon instantiation
    void parseThings();
    void parseSingles(string);
    void makeTree();                   //Makes the actual tree
    void deleteTree();
    SearchNode* searchData(string searchTerm); //searches for a word, returns a searchNode
    void printTreeToTFIDF();


    XMLParser parse;
    AVLTree<SearchNode> avlEverything;
    ofstream fout;

};

#endif // INDEXHANDLER_H
