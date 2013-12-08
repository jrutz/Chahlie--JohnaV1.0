/*
 * File:   XMLParser.cpp
 * Author: Charlie Albright
 *
 * Created on November 30, 2013, 9:17 PM
 */

#include "XMLParser.h"
#include "SearchNode.h"


XMLParser::XMLParser()
{

    directory = "WikiDump";
    xmlPath = "/users/Johna/CutieWs/finalProject/AlbrightRutzSiemsSE/src/WikiDump/";   //To Johna's directory
    pageDivider = 1;
    numWords = 0;
    getDirectory();
}

XMLParser::XMLParser(const XMLParser& orig) {
}

XMLParser::~XMLParser() {
}


void XMLParser::getDirectory()
{
    DIR *dp;
    struct dirent *dirp;
    if((dp = opendir(directory.c_str())) == NULL)
    {
        cout<< "Error(" << errno << ") opening " << directory << endl;
    }

    while((dirp = readdir(dp)) != NULL)
    {
        xmlFiles.push_back(string(dirp->d_name));
    }
    closedir(dp);
}

void XMLParser::runParser()
{
    for(int i = 0; i < xmlFiles.size(); i++)
    {
        string currentPath = xmlPath + xmlFiles[i];
        cout<<"CURRENT PATH: "<<currentPath<<endl;
        xml_parse_result result = currentDoc.load_file(currentPath.c_str(), parse_default | encoding_auto);
        cout << "Load Result: " << result.description() << endl;
        cout << xmlFiles[i] << endl;
        pageDivider = atoi(currentID.c_str()) + 1;

        string pageDividerString;

        stringstream ss;
        ss << pageDivider;
        ss >> pageDividerString;

        outputDoc = "Wikipages-" + pageDividerString + ".txt";
        fout.open(outputDoc.c_str());
        //FIX STUPID DOCUMENT NAMING NUMBER SCHTUFF

        for(xml_node page = currentDoc.child("mediawiki").child("page"); page; page = page.next_sibling("page"))
        {
            currentID = page.child_value("id");
            currentTitle = page.child_value("title");
            currentUsername = page.child("revision").child("contributor").child_value("username");
            currentTimestamp = page.child("revision").child("contributor").child_value("timestamp");
            currentText = page.child("revision").child_value("text");

            writePageToFile(currentID, currentTitle, currentTimestamp, currentUsername, currentText);
            buildSearchNodes(currentText, currentID);

        }
        cout<<xmlFiles[i]<<" parsed"<<endl;
        fout.close();
    }
}

void XMLParser::writePageToFile(string& id, string& title, string& timestamp,
        string& username, string& text)
{
    fout << id << endl;
    fout << title << endl;
    fout << username << endl;
    fout << timestamp << endl;
    fout << text << endl;
    fout << "<--||-->" << endl;
}

void XMLParser::sendToAVLTree(string& keyword, string& docID)
{
    if(tree->isEmpty())
    {
        cout<<"WORD:"<<keyword<<"~~~"<<endl;
        SearchNode* s = new SearchNode(keyword);
        s->addInstance(docID);
        tree->insert(*s);
    }
    else
    {
        //cout<<"WORD:"<<keyword<<"~~~"<<endl;
        SearchNode* s = new SearchNode(keyword);
        SearchNode* result = NULL;
        //cout<<"RESULT BEFORE SEARCH: "<<result<<endl;
        bool newWord = tree->search(*s, result);
        //cout<<"RESULT AFTER SEARCH: "<<result<<endl;
        if(newWord)
        {
            //cout<<"INCREMENTING word:"<<keyword<<endl;
            result->addInstance(docID);
        }
        else
        {
            //cout<<"ADDING WORD:"<<keyword<<endl;
            s->addInstance(docID);
            tree->insert(*s);
        }
    }
}

void XMLParser::buildSearchNodes(string& text, string& docID)
{
    stringstream ss;
    ss << text;
    string word;
    while(ss >> word)
    {
        sendToAVLTree(word, docID);
    }

}

void XMLParser::setPointer(AVLTree<SearchNode>* fromAbove)
{
    tree = fromAbove;
}
