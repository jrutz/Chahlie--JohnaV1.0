/*
 * File:   SearchNode.h
 * Author: Charlie Albright
 *
 * Created on November 24, 2013, 6:26 PM
 */
#include <string>
#include <vector>
#include <iostream>
#ifndef SEARCHNODE_H
#define	SEARCHNODE_H
using namespace std;

class SearchNode {
public:
    SearchNode();
    SearchNode(string key);
    SearchNode(const SearchNode& orig);
    virtual ~SearchNode();

    int containsDoc(string& doc);

    void setKeyword(string& key);
    string getKeyword();

    void addDocument(string& doc);
    vector<string> getDocuments();

    void addHits(int num);
    void setHits(int index, int num);
    vector<int> getHits();

    void addInstance(string& doc);
    std::ostream& print(std::ostream& out);
    bool operator ==(SearchNode& rhs);
    bool operator <(SearchNode& rhs);
    bool operator >(SearchNode& rhs);
    
    friend std::ostream& operator<<(std::ostream& out, SearchNode& rhs);

private:
    string keyword;
    vector<string> documents;
    vector<int> hits; //# times this keyword is found in respective document
    int numDocs;
};

#endif	/* SEARCHNODE_H */

