/*
 * File:   SearchNode.cpp
 * Author: charlie
 *
 * Created on November 24, 2013, 6:26 PM
 */

#include "SearchNode.h"

SearchNode::SearchNode()
{
    keyword = "";
    numDocs = 0;
}

SearchNode::SearchNode(string key)
{
    keyword = key;
    numDocs = 0;
}

SearchNode::SearchNode(const SearchNode& orig)
{
    keyword = orig.keyword;
    documents = orig.documents;
    hits = orig.hits;
    numDocs = orig.numDocs;
}

SearchNode::~SearchNode()
{

}

int SearchNode::containsDoc(string& doc)
{
    for (int i = 0; i < documents.size(); i++) {
        if (doc == documents[i]) {
            return hits[i];
        }
    }
    return 0;
}


void SearchNode::setKeyword(string& key)
{
    keyword = key;
}

string SearchNode::getKeyword()
{
    return keyword;
}

void SearchNode::addDocument(string& doc)
{
    documents.push_back(doc);
    numDocs++;
}

vector<string> SearchNode::getDocuments()
{
    return documents;
}

void SearchNode::addHits(int num)
{
    hits.push_back(num);
}

void SearchNode::setHits(int index, int num) {
    hits[index] = num;
}

vector<int> SearchNode::getHits()
{
    return hits;
}

void SearchNode::addInstance(string& doc)
{
    if(documents.empty())
    {
        documents.push_back(doc);
        hits.push_back(1);
        numDocs++;
    }
    else
    {
        bool newDoc = true;
        for(int i = 0; i < documents.size(); i++)
        {
            //cout<<"-"<<i<<"- TRYING "<<doc<<endl;
            if(doc.compare(documents[i]) == 0)
            {
                //cout<<"COMPARED"<<endl;
                hits[i]++;
                newDoc = false;
            }
            //cout<<"TRY DONE"<<endl;
        }
        if(newDoc == true)
        {
            documents.push_back(doc);
            hits.push_back(1);
            numDocs++;
        }
    }
}

bool SearchNode::operator ==(SearchNode& rhs)
{
    if(this->keyword.compare(rhs.keyword) == 0)
        return true;
    else
        return false;
}

bool SearchNode::operator <(SearchNode& rhs)
{
    if(this->keyword.compare(rhs.keyword) < 0)
        return true;
    else
        return false;
}

bool SearchNode::operator >(SearchNode& rhs)
{
    if(this->keyword.compare(rhs.keyword) > 0)
        return true;
    else
        return false;
}

std::ostream& SearchNode::print(std::ostream& out)
{
    out << keyword << " = ";
    out << documents[0];
    for(int i = 1; i < numDocs; i++)
    {
        out << ", " << documents[i];
    }
    out << endl;
    return out;
}

std::ostream& operator<<(std::ostream& out, SearchNode& rhs)
{
    return rhs.print(out);
}


