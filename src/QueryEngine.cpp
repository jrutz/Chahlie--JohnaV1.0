#include "QueryEngine.h"

QueryEngine::QueryEngine() {
    query = "";
}

QueryEngine::QueryEngine(string q, IndexHandler *handle) {
    query = q;
    handleTree = handle;
}

QueryEngine::~QueryEngine() {

}


//Gets the searchNodes from the index
void QueryEngine::getSearchNodesFromIndex()
{
    vector<string> searchWordsAre = getSearchWords();
    while(!searchWordsAre.empty())
    {
        SearchNode *temporary = NULL;
        temporary = handleTree->searchData(searchWordsAre.back());
        if(temporary!=NULL)
        {
            SearchNodeList.push_back(temporary);
        }
        
        searchWordsAre.pop_back();
    }
}

bool QueryEngine::doQuery() {
    //Break the query into AND, OR, NOT categories processQuery();
    if(!processQuery()) {
        return false;
    }

        //Get class with word/document info and put in SearchNodeList
        //buildFabricatedDocs();

    //Get search nodes that are applicable ot the query
    getSearchNodesFromIndex();


    //do AND, OR, and NOT to determine list of documents needed by query
    vector<int> docHits; //parallel with docList... holds total hits per word
    vector<SearchNode*> ANDNodes;
    vector<SearchNode*> NOTNodes;
    SearchNode* SNptr;
    for (int i = 0; i < SearchNodeList.size(); i++) {
        if(find(ANDWords.begin(), ANDWords.end(), SearchNodeList[i]->getKeyword()) != ANDWords.end()) {
            //cout << "AND Word Found!" << endl;
            SNptr = SearchNodeList[i];
            ANDNodes.push_back(SNptr);
        } else if(find(ORWords.begin(), ORWords.end(), SearchNodeList[i]->getKeyword()) != ORWords.end()) {
            //cout << "OR Word Found!" << endl;
            for (int j = 0; j < SearchNodeList[i]->getDocuments().size(); j++) {
                docList.push_back(SearchNodeList[i]->getDocuments()[j]);
                docHits.push_back(SearchNodeList[i]->getHits()[j]);
            }
        } else if (find(NOTWords.begin(), NOTWords.end(), SearchNodeList[i]->getKeyword()) != NOTWords.end()) {
            //cout << "NOT Word Found!" << endl;
            SNptr = SearchNodeList[i];
            NOTNodes.push_back(SNptr);
        } else {
            //cout << "Not found: \"" << SearchNodeList[i].getKeyword() << "\""<< endl;
        }
    }

    //Process AND words
    //cout << "Processing AND words..." << endl;
    bool wordInDocFlag = true;
    if (ANDNodes.size() != 0) {
        for (int j = 0; j < ANDNodes[0]->getDocuments().size(); j++) {
            for (int i = 1; i < ANDNodes.size(); i++) {
                if(!ANDNodes[i]->containsDoc(ANDNodes[0]->getDocuments()[j])) {
                    wordInDocFlag = false;
                    break;
                } else {
                    ANDNodes[0]->setHits(j, ANDNodes[0]->getHits()[j] + ANDNodes[i]->containsDoc(ANDNodes[0]->getDocuments()[j]));
                }
            }
            if (wordInDocFlag) {
                docList.push_back(ANDNodes[0]->getDocuments()[j]);
                docHits.push_back(ANDNodes[0]->getHits()[j]);
            }
            wordInDocFlag = true;
        }
    }

    //Go through NOTWords, remove all docs
    //cout << "Removing NOT words..." << endl;
    for (int i = 0; i < docList.size(); i++) {
        for (int j = 0; j < NOTNodes.size(); j++) {
            for (int k = 0; k < NOTNodes[j]->getDocuments().size(); k++) {
                if (NOTNodes[j]->getDocuments()[k] == docList[i]) {
                    docList.erase(docList.begin() + i);
                    docHits.erase(docHits.begin() + i);
                }
            }
        }
    }

    //Print docList before removing duplicates
    // cout << "Printing docList..." << endl;
    // for (int i = 0; i < docList.size(); i++) {
    // 	cout << "---" << docList[i] << "  " << docHits[i] << endl;
    // }

    //Remove duplicates from docList
    //cout << "Removing duplicates..." << endl;
    vector<int> removeTheseIndices;
    for (int i = 0; i < docList.size(); i++) {
        for (int j = i + 1; j < docList.size(); j++) {
            if (docList[i] == docList[j] && !(find(removeTheseIndices.begin(), removeTheseIndices.end(), i) != removeTheseIndices.end())) {
                //cout << "duplicates at " << i << " and " << j << endl;
                removeTheseIndices.push_back(i);
                docHits[j] += docHits[i];
            }
        }
    }
    for (int i = removeTheseIndices.size() - 1; i >= 0; i--) {
        //cout << "Erasing " << removeTheseIndices[i] << "..." << endl;
        docList.erase(docList.begin() + removeTheseIndices[i]);
        docHits.erase(docHits.begin() + removeTheseIndices[i]);
    }

    //Print finished docList
    // cout << "Printing finished docList..." << endl;
    // for (int i = 0; i < docList.size(); i++) {
    // 	cout << "---" << docList[i] << "  " << docHits[i] << endl;
    // }

    //Order the list based on "hits" defined in the class with word/doc info
    for (int i = 0; i < docList.size(); i++) {
        for (int j = i + 1; j < docList.size(); j++) {
            if (docHits[i] < docHits[j]) {
                //swap elements i and j
                swap(docHits[i], docHits[j]);
                swap(docList[i], docList[j]);
            }
        }
    }

    //Print sorted docList
    // cout << "Printing sorted docList..." << endl;
    // for (int i = 0; i < docList.size(); i++) {
    // 	cout << "---" << docList[i] << "  " << docHits[i] << endl;
    // }

    return true;

}

bool QueryEngine::processQuery() {
    stringstream ss;

    ss << query;
    string temp;

    //Flags
    bool ANDFlag = true;
    bool ORFlag = false;
    bool NOTFlag = false;

    while (!ss.eof()) {
        ss >> temp;

        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

        if (temp == "and") {
            ANDFlag = true;
            ORFlag = false;
            NOTFlag = false;
            continue;
        } else if (temp == "or") {
            ANDFlag = false;
            ORFlag = true;
            NOTFlag = false;
            continue;
        } else if (temp == "not") {
            ANDFlag = false;
            ORFlag = false;
            NOTFlag = true;
            continue;
        }


        if (ANDFlag && !(find(ORWords.begin(), ORWords.end(), temp) != ORWords.end()) && !(find(NOTWords.begin(), NOTWords.end(), temp) != NOTWords.end())) {
            ANDWords.push_back(temp);
            allWords.push_back(temp);
        } else if (ORFlag && !(find(ANDWords.begin(), ANDWords.end(), temp) != ANDWords.end()) && !(find(NOTWords.begin(), NOTWords.end(), temp) != NOTWords.end())) {
            ORWords.push_back(temp);
            allWords.push_back(temp);
        } else if (NOTFlag && !(find(ORWords.begin(), ORWords.end(), temp) != ORWords.end()) && !(find(ANDWords.begin(), ANDWords.end(), temp) != ANDWords.end())) {
            NOTWords.push_back(temp);
            allWords.push_back(temp);
        } else {
            return false;
        }
    }

    return true;
}

vector<string> QueryEngine::getSearchWords() {
    return allWords;
}

void QueryEngine::printWords() {

    cout << "allWords:" << endl;
    for (int i = 0; i < allWords.size(); i++) {
        cout << "   " << allWords[i] << endl;
    }

    cout << "ANDWords:" << endl;
    for (int i = 0; i < ANDWords.size(); i++) {
        cout << "   " << ANDWords[i] << endl;
    }

    cout << "ORWords:" << endl;
    for (int i = 0; i < ORWords.size(); i++) {
        cout << "   " << ORWords[i] << endl;
    }

    cout << "NOTWords:" << endl;
    for (int i = 0; i < NOTWords.size(); i++) {
        cout << "   " << NOTWords[i] << endl;
    }

}

void QueryEngine::printDocList() {
    for (int i = 0; i < docList.size(); i++) {
        cout << ">>> " << docList[i] << " <<<" << endl;
    }
}

void QueryEngine::buildFabricatedDocs() {

    //build list of documents
    vector<string> docs;
    docs.push_back("d0");
    docs.push_back("d1");
    docs.push_back("d2");
    docs.push_back("d3");
    docs.push_back("d4");

    string tempStr = "dallas";
    SearchNode temp1 = SearchNode(tempStr);
    temp1.addDocument(docs[0]);
    temp1.addHits(3);
    temp1.addDocument(docs[3]);
    temp1.addHits(2);
    SearchNodeList.push_back(&temp1);

    tempStr = "seattle";
    SearchNode temp2 = SearchNode(tempStr);
    temp2.addDocument(docs[3]);
    temp2.addHits(6);
    SearchNodeList.push_back(&temp2);

    tempStr = "memphis";
    SearchNode temp3 = SearchNode(tempStr);
    temp3.addDocument(docs[0]);
    temp3.addHits(10);
    temp3.addDocument(docs[1]);
    temp3.addHits(4);
    temp3.addDocument(docs[2]);
    temp3.addHits(6);
    SearchNodeList.push_back(&temp3);

    tempStr = "book";
    SearchNode temp4 = SearchNode(tempStr);
    temp4.addDocument(docs[4]);
    temp4.addHits(9);
    temp4.addDocument(docs[3]);
    temp4.addHits(4);
    temp4.addDocument(docs[2]);
    temp4.addHits(10);
    SearchNodeList.push_back(&temp4);

}