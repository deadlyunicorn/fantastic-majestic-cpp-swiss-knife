
#include <iostream>
#include <vector>

#include "global_Functions.h"
#include "Friend_Objects_Functions.h"

using namespace std;



void friendProcedure(string& userInput){
  string filename;
  
  ofstream friendList;

  bar();
  cout << "Hello and welcome to the Friendlist!!" << endl;
  if (userSaidYesTo("Use an existing file?")){

    while(true){

      string tempFilename=getValidInput("Enter filename");
      
      if ( fileExists ( tempFilename ) ){
        filename=tempFilename;
        break;
      };

      cout << "Cannot find file." << endl;
      if ( userSaidYesTo("Retry?") ){
        continue;
      }
      else{
        break;
      };

    }


  }

  if( filename.size() < 1 ){
    filename=getValidInput("Enter a filename to save your friends into");
  }

  while(true){

    cout << "What do you want to do?" << endl;
    optionBar();

    cout << "1: Add a new friend" << endl;
    cout << "2: See all your friends" << endl;
    cout << "3: Compare the age of two friends" << endl;
    cout << "4: Find out about a friend's Zodiac" << endl;
    optionBar();
    cout << "exit: Go to the home menu" << endl;
    optionBar();

    while (true){
        userInput=getNumberInput();

        if(userInput=="!!!"){
              break;
            }

        if( stoi(userInput) < 1 || stoi( userInput ) > 4 ){
          cout << "Please select one of the options listed above!" << endl;
          continue;
        }
        else{
          break;
        }
    }

    if(userInput=="!!!"){
              break;
    }

   


    friendListClass::friendList* tempList=new friendListClass::friendList;
    tempList->generateFromFile(filename);


    if(userInput=="1"){ //Add new friend

        friendList.open(filename,ofstream::out | ofstream::app);


        Friend* newFriend=new Friend;

        newFriend->setFirstName(getValidInput("Enter friend's name"));
        newFriend->setSurName(getValidInput("Enter friend's surname"));
        
        while (true){
          string tempDay=getValidInput("Enter friend's day of birth. \nFor example if it is the 9th of December 2000, \nyou should write '9'");
          try{
            stoi(tempDay);
            if(stoi(tempDay)>0 && stoi(tempDay)<32){
              newFriend->setBirthDay(stoi(tempDay));
              break;
            }
            else{
              cout << "Not a valid day." << endl;
              waitBeforeContinue();
            }
          }
          catch(...){
            cout << "Please enter a number." << endl;
            waitBeforeContinue();

          }
        };

        while (true){
          string tempMonth=getValidInput("Enter friend's month of birth. \nFor example if it is the 9th of December 2000, \nyou should write '12'");
          try{
            stoi(tempMonth);
            if(stoi(tempMonth)>0 && stoi(tempMonth)<13){
              newFriend->setBirthMonth(stoi(tempMonth));
              break;
            }
            else{
              cout << "Not a valid month." << endl;
              waitBeforeContinue();


            }
            
          }
          catch(...){
            cout << "Please enter a number." << endl;
            waitBeforeContinue();

          }
        };

        while (true){
          string tempYear=getValidInput("Enter friend's year of birth. \nFor example if it is the 9th of December 2000, \nyou should write '2000'");
          //I was actually planning initially to accept 'December' and turn it manually to 12, but this is easier for all parties..
          try{
            stoi(tempYear);
            if(stoi(tempYear)>1900 && stoi(tempYear)<2200){ //Sorry future kids..
              newFriend->setBirthYear(stoi(tempYear));
              break;
            }
            else{
              cout << "Not a valid year." << endl;
              waitBeforeContinue();

            }
            
          }
          catch(...){
            cout << "Please enter a number." << endl;
            waitBeforeContinue();

          }
        };

        cout << "Success!" << endl;
        bar();
        cout << newFriend->generate();
        friendList << newFriend->generate();
        bar();
        
        delete newFriend;
        friendList.close();

        waitBeforeContinue();


          
      
    }
    else if(userInput=="2"){ //See all friends
      
      
      cout << "Here is a list of your friends!" << endl;
      cout << "You have " << tempList->getfriendCount() << " friends." << endl;
      cout << tempList->getFriendNames();
      
      waitBeforeContinue();

    }
    else if(userInput=="3"){ //Compare age
      
      int x,y,temp;

      cout << tempList->getFriendNames();
      cout << "Enter the number of your 1st friend" << endl;

      while (true){
      
        temp=stoi(getNumberInput())-1;

        if ( (temp<0) || (temp>tempList->getfriendCount() ) ){
          cout << "Not a valid option." << endl;
        }
        else {
          x=temp;
          break;
        }
      }

      cout << "Enter the number of your 2nd friend" << endl;

      while (true){
      
        temp=stoi(getNumberInput())-1;

        if ( ( temp<0 ) || ( temp>tempList->getfriendCount() )){
          cout << "Not a valid option." << endl;
        }
        else {
          y=temp;
          break;
        }
      };
      Friend First = tempList->getFriendNum(x);
      Friend AgeDifference = tempList->getFriendNum(y)- First;
      cout << tempList->getFriendNum(x).getName() <<" is ";
      // if (AgeDifference.getYear()){}
      cout <<  to_string(AgeDifference.getBirthday()) << " days ";
      cout <<  to_string(AgeDifference.getMonth()) << " months and ";
      if(AgeDifference.getYear()>0){
        cout << to_string(AgeDifference.getYear()) << " years younger";
      }
      else{
        cout << to_string(-AgeDifference.getYear()) << " years older";
      }
      cout << " than " << tempList->getFriendNum(y).getName() << "."<< endl;

      waitBeforeContinue();


    }
    else if(userInput=="4"){ //Friend's Zodiac
      
      int x;

      cout << "Here is a list of your friends!" << endl;
      cout << tempList->getFriendNames();

      cout << "Whose friend to see the Zodiac of?" << endl;

      while (true){
      
        int temp;
        temp=stoi(getNumberInput())-1;

        if ( (temp<0) || (temp>tempList->getfriendCount() ) ){
          cout << "Not a valid option." << endl;
        }
        else {
          x=temp;
          break;
        }
      }

      cout << tempList->getFriendNum(x).getName() << " is a " << tempList->getFriendNum(x).getZodiac() << "!" << endl;
      
      waitBeforeContinue();
    }

    delete tempList;




  }

};


