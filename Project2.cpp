#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
//Struct initialization 
struct videoGame
{
  enum {MAX_CHAR_LEN = 100};
  char name[MAX_CHAR_LEN];
  int sales;
  char platform[MAX_CHAR_LEN];
  char release[MAX_CHAR_LEN];
  char developer[MAX_CHAR_LEN];
  char publisher[MAX_CHAR_LEN];
  videoGame();
};
const int MAX_VG=100;
//Constructor
videoGame::videoGame(){
  for (int i = 0; i < MAX_CHAR_LEN; i++){
  name[i] = '\0';
  platform[i] = '\0';
  release[i] = '\0';
  developer[i] = '\0';
  publisher[i] = '\0';
  }
  sales = 0;
}
//Reading in the video game
videoGame readVG(ifstream &inFile){
  videoGame VG;
    inFile.get(VG.name, videoGame::MAX_CHAR_LEN,';');
    inFile.ignore(100,';');
    inFile >> VG.sales;
    inFile.ignore(100,';');
    inFile.get(VG.platform, videoGame::MAX_CHAR_LEN,';');
    inFile.ignore(100,';');
    inFile.get(VG.release, videoGame::MAX_CHAR_LEN,';');
    inFile.ignore(100,';');
    inFile.get(VG.developer, videoGame::MAX_CHAR_LEN,';');
    inFile.ignore(100,';');
    inFile.get(VG.publisher, videoGame::MAX_CHAR_LEN);
    inFile.ignore(100,'\n');
    return VG;
  }

//Reading VideoGame data
int readVideoGame(ifstream &inFile, videoGame gameList[]){
int gameCounter = 0;
  while(inFile.peek()!=EOF && gameCounter<MAX_VG){
    gameList[gameCounter] = readVG(inFile);
    gameCounter++;
  }
  return gameCounter;
}
//Printing the data out
void printVGData(videoGame gameList, int entrynum){
  cout << "Game Number " << entrynum << endl;
  cout << "Name: " << gameList.name << endl;
  cout << "Sales: " << gameList.sales << endl;
  cout << "Platform: " << gameList.platform << endl;
  cout << "Release Date: " << gameList.release << endl;
  cout << "Developer: " << gameList.developer << endl;
  cout << "Publisher: " << gameList.publisher << endl;
  cout << endl;
}

//Integer Check
int readInt(const char prompt[]){
    int temp = 0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid Data!" << endl;
        cout << prompt;
        cin >> temp;
    }
    return temp;
}
//Adding Entry to Database
void addEntry(videoGame gameList[], int listSize){
  //If database full
  bool GameReal = false;
  //Checking for valid entry
  for (int index = 0; index < MAX_VG; index++){
    if(strcmp(gameList[index].name,"")==0){
        cout << "Entering information for Game #" << index << endl;
  cout << "Enter Name: ";
  cin.ignore(100,'\n');
  cin.getline(gameList[index].name, listSize);
  //Int Checker
  gameList[index].sales = readInt("Enter sales: ");
  cout << "Enter Platforms (if multiple, type Multi-platform): ";
  cin.ignore(100,'\n');
  cin.getline(gameList[index].platform, listSize);
  cout << "Enter Release Date in this format (example: January 1, 2005): ";
  cin.getline(gameList[index].release, listSize);
  cout << "Enter Developer: ";
  cin.getline(gameList[index].developer, listSize);
  cout << "Enter Publisher: ";
  cin.getline(gameList[index].publisher, listSize);
  cout << endl;
  GameReal = true;
  break;
    }
    }
  if (GameReal == false){
    cout << "The database is full." << endl;
    cout << endl;
  }
  }
  
 
int removeEntry(videoGame gameList[],int newSize){
  int removeIndex = 0;
  cout << "Remove entry between 0 and " << newSize-1 << endl;
  cin >> removeIndex;
  if (removeIndex >= 0 && removeIndex <= newSize-1){
  for (int deleteIndex = removeIndex; deleteIndex < newSize; deleteIndex++){
  gameList[deleteIndex] = gameList[deleteIndex + 1];
  }
    //New Size being made
    newSize--;
    }
  else {
    cout << "Invalid Entry." << endl;
    cout << endl;
  }
  return newSize;
}
//Reloading the file
int reloadFile(videoGame gameList[], int oldSize){
  ifstream gameFile("videogames.txt");
  int newSize=readVideoGame(gameFile,gameList);
  oldSize = newSize;
  cout << "Database successfully reloaded." << endl;
  cout << endl;
  return oldSize;
}

int main(){
 videoGame gameList[MAX_VG];
  ifstream GameFile("videogames.txt");
  int counter = readVideoGame(GameFile, gameList);
  int choice = 0;
  //Menu
  while (choice!=7){
    cout << "Welcome to the Videogame Database" << endl;
    cout << "Please enter an input (1-7): " << endl;
    cout << "1. Reload the database from file" << endl;
    cout << "2. Print database entry" << endl;
    cout << "3. Add new entry" << endl;
    cout << "4. Remove entry" << endl;
    cout << "5. Print all videogames by publisher" << endl;
    cout << "6. Save database to file" << endl;
    cout << "7. Quit" << endl;
    cout << endl;
    cout << endl;
    //Hard Reset
    cout << "CAUTION: " << endl;
    cout << "10. Reset file back to original file" << endl;
    cin >> choice;
    cout << endl;
    //Reload from file
    if (choice==1){
      counter = reloadFile(gameList,counter);
    }
    //Print Videogame
    if (choice==2){
      int VGChoice = 0;
      cout << "Enter a videogame entry between 0 and " << counter-1 << ": ";
      cin >> VGChoice;
      cout << endl;
      if (VGChoice <= counter-1 && VGChoice >=0){
      printVGData(gameList[VGChoice], VGChoice);
        }
      else{
        cout << "Invalid Entry." << endl;
        cout << endl;
      }
    }
    //adding game
    if (choice==3){
      addEntry(gameList,counter);
      //adding one more to the possible list in the database
      counter++;
    }
    if (choice==4){
      counter = removeEntry(gameList,counter);
    }  
  }
}