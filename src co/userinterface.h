#include "indexhandler.h"
#include "QueryEngine.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>

#ifndef USERINTERFACE_H
#define USERINTERFACE_H


class UserInterface
{
private:
    int newFileId = 1;
    IndexHandler *index;

public:
    UserInterface();
    //Maintenance
    void welcome();
    void maintenanceFunctions();
        //Add to directory
        //Clear index
    //Interactive
    void interactiveFunctions();
        //Load AVL structure
        //Load Hash table
        //Search
    void stressTest();
    //Stress test
};

#endif // USERINTERFACE_H

