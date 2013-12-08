#include "userinterface.h"

UserInterface::UserInterface()
{    
    cout<<"Welcome to the Albright/Siems/Rutz search engine"<<endl;

}

void UserInterface::welcome()
{
    int userchoice = 0;

    while(userchoice != 4)
    {
        printf("%c[0;36;1mPlease choose an option from below: \n",27);
        printf("%c[0m1. Maintenance Mode\n",27);
        cout<<"2. Interactive Functions"<<endl;
        cout<<"3. Stress Test"<<endl;
        cout<<"4. EXIT PROGRAM"<<endl;

        cin >> userchoice;

        if(userchoice == 1)
        {
            maintenanceFunctions();
        }

        if(userchoice == 2)
        {
            interactiveFunctions();
        }

        if(userchoice == 3)
        {
            stressTest();
        }

       if( userchoice != 4 && userchoice != 3 && userchoice != 2 && userchoice != 1)
        {
            cout<<"I'm sorry, that's an invalid option"<<endl;
        }

        if(userchoice == 4)
        {
            cout<<endl;
            cout<<"So it goes. Thanks for using this program"<<endl;
            cout<<endl;
        }
    }

}

//Maintenance
void UserInterface :: maintenanceFunctions()
{
   int userChoice;
   if(index == NULL)
   		index = new IndexHandler();


   printf("%c[1;32mWelcome to Maintenance Function\n", 27);

   while(userChoice != 3)
   {
    userChoice = 0;
    printf("%c[0;32mWould you like to: \n", 27);
    printf("%c[0;m1. Add to the directory \n", 27);
    cout<<"2. Clear the index"<<endl;
    cout<<"3. Return to main screen"<<endl;
    cout<<"CHOICE: ";
    cin >> userChoice;

        //Adds a new file to the working directory
        if(userChoice == 1)
        {
           string fileName;
            cout<<"NAME OF FILE (add doc extension if necessary): ";
            cin>> fileName;
            
            index-> parseSingles(fileName);

            /*string path = "/users/Johna/CutieWs/finalProject/WikiDump/newFile";

            stringstream ss;
            ss << newFileId;
            string fileID;
            ss >> fileID;

            path.append(fileID);

            cout<<"NEW PATH IS: "<<path<<endl;

           int result = rename(fileName.c_str(), path.c_str());
           if(result == 0)
           {
               cout<<"Successfully added to directory"<<endl;
               newFileId++;
           }
           else
           {
               cout<<"Could not add to directory"<<endl;
           }*/
        }

        //Clear index
        if(userChoice == 2)
        {

        }

        else if(userChoice != 1 && userChoice !=2 && userChoice !=3)
        {
            cout<<"Not a valid choice"<<endl;
            cout<<endl;
        }
    }




}

//Interactive
void UserInterface :: interactiveFunctions()
{
     if(index == NULL)
         index = new IndexHandler();
                                  
      int userchoice=0;
   while(userchoice != 4)
   {
       printf("%c[1mWelcome to the interactive mode\n",27);
       printf("%c[0m1. Load AVL tree\n",27);
        cout<<"2. Load the Hash table"<<endl;
        cout<<"3. Search for stuff"<<endl;
        cout<<"4. Try different mode"<<endl;

        cin>>userchoice;

        //Load AVL structure
        if(userchoice == 1)
        {
            index->parseThings();
            index->makeTree();
        }

        //Load Hash table
        if(userchoice == 2)
        {
            index->parseThings();
            index->makeTree();
        }

        //Search
        if(userchoice == 3)
        {
            cout<<"SEARCH: ";
            string userQuery;
            cin.ignore(100, '\n');
            getline(cin, userQuery);

            QueryEngine searchingForTruth(userQuery, index);
            searchingForTruth.doQuery();

            cout<<"DOCUMENTS FOUND: "<<endl;
            cout<<endl;
            searchingForTruth.printDocList();
            cout<<endl;
            cout<<endl;
        }

        if(userchoice == 4)
        {
            //clear everything, go to main page
        }
    }


}

//Stress test
void UserInterface :: stressTest()
{
    printf("%c[1;31mWelcome to stress, fuckers\n",27);

}