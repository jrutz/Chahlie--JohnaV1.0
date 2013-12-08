
#ifndef QUERY_ENGINE_H
#define QUERY_ENGINE_H
#include "indexhandler.h"

//SearchNode - Container class used by QueryEngine to organize the query

using namespace std;

class QueryEngine {

private:
    string query;

    vector<string> docList;		//THE IMPORTANT LIST OF DOCS (should be
                                //created and ordered after the doQuery function)

    vector<string> allWords;	//All the search words in the query
    vector<string> ANDWords;    //Words that MUST be in the document
    vector<string> ORWords;	    //Words that must be in the document AT LEAST ONCE
    vector<string> NOTWords;	//Words that CANNOT be in the document

    vector<SearchNode*> SearchNodeList;	//List of documents and keywords

    //Break the query into AND, OR, NOT categories
    bool processQuery();

public:
    QueryEngine();
    QueryEngine(string q, IndexHandler *handle);
    ~QueryEngine();

    bool doQuery();
    vector<string> getSearchWords();  //Returns all words (AND, OR, and NOT)
    IndexHandler* handleTree;

    //For debugging purposes...
    void printWords();
    void printDocList();
    void buildFabricatedDocs();


    //GETTERS AND SETTERS
    string getQuery();
    void setQuery(string q);


    void getSearchNodesFromIndex();

};

#endif
