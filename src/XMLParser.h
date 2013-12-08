/*
 * File:   XMLParser.h
 * Author: Charlie Albright
 *
 * Note: This class structure uses direct implementation of the pugiXML library,
 *       version 1.2: All credit of XML parsing goes to original authors of the
 *       pugiXML library.
 *
 * Created on November 30, 2013, 9:17 PM
 */

#ifndef XMLPARSER_H
#define	XMLPARSER_H

#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <ctype.h>
#include <sstream>

#include "AVLTree.h"
#include "pugiconfig.h"
#include "pugixml.h"
#include "SearchNode.h"

using namespace std;
using namespace pugi;

class XMLParser {
public:
    XMLParser();
    XMLParser(const XMLParser& orig);
    virtual ~XMLParser();

    void runParser();
    void setPointer(AVLTree<SearchNode>* fromAbove);
    void parseSingleFile(string path);

private:
    string directory;
    string xmlPath;
    vector<string> xmlFiles;
    ofstream fout;

    xml_document currentDoc;
    string outputDoc;
    int pageDivider;

    string currentID;
    string currentTitle;
    string currentUsername;
    string currentTimestamp;
    string currentText;

    vector<SearchNode> TF_IDF;
    int numWords;

    AVLTree<SearchNode> * tree;
    AVLTree<SearchNode> localTree;

    void getDirectory();

    void writePageToFile(string &id, string &title, string &timestamp, string
                &username, string &text);

    void sendToAVLTree(string& keyword, string& docID);

    void buildSearchNodes(string& text, string& docID);

};

#endif	/* XMLPARSER_H */
