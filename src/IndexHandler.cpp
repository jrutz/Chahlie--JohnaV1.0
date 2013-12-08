#include "indexhandler.h"


IndexHandler::IndexHandler()                     //Parses upon instantiation
{
    parse.setPointer(&avlEverything);
}


void IndexHandler::parseThings()
{
    parse.runParser();
    printTreeToTFIDF();
}


void IndexHandler::parseSingles(string filePath)
{
    parse.parseSingleFile(filePath);
}

void IndexHandler::makeTree()                    //Makes the actual tree
{
 
}



void IndexHandler::deleteTree()
{

}


//This is assuming that the word is in there at all - what if it isn't?
//Null word automatically defaults to keyword = ""
SearchNode* IndexHandler::searchData(string searchTerm)      //searches for a word, returns a searchNode
    {
        SearchNode searchTermNode; 
        SearchNode* returnNode;

        searchTermNode.setKeyword(searchTerm);
        bool queryResult = avlEverything.search(searchTermNode, returnNode);

        return returnNode;
    }

void IndexHandler::printTreeToTFIDF()
{
    fout.open("TFIDF.txt");
    avlEverything.printToFile(fout);
}