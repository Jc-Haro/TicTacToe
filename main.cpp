#include<iostream>
#include<ios>
#include<iomanip>
#include<vector>
#include<time.h>

const int NUM_SQUARES = 9;
const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';
const char NO_ONE = 'N';
const char TIE = 'T';

void Welcome();
char GetPlayerSymbol();
void DrawChoiceBoard(std::vector<char> board);
bool AskYesNo(std::string question);
int getPlayerInput(std::vector<int> & availableBoxes);
int  checkValidInput();
bool checkDigit(char check);
char winner(const std::vector<char>  & board);

int main(){

    char player;
    char IA;

    int playerInput{};

    std::vector<char> board (NUM_SQUARES,EMPTY);
    std::vector<int> availableBoxes = {0,1,2,3,4,5,6,7,8};

    Welcome();

    //Get player and IA symbol
    player = GetPlayerSymbol();
    IA = player==PLAYER_X? PLAYER_O : PLAYER_X;

    std::cout<<"\n\nPlayer:"<<player<<"\n\n";
    std::cout<<"\n\nPlayer"<<IA<<"\n\n";
    do{
        DrawChoiceBoard(board);  
        playerInput = getPlayerInput(availableBoxes);
        board[playerInput] = player;
    }while(availableBoxes.size()>0);

    DrawChoiceBoard(board);  
    
    return 0;
}

void Welcome(){

    std::cout<<"****Welcome to TicTacToe****"<<std::endl;
    std::cout<<"Today you will be facing me, get ready"<<std::endl;

}
char GetPlayerSymbol(){
    std::vector<std::string> startPhrases = {"I feel generous, so", "I want to give you a chance, so","Anyway I will win, so","This will not change the result but,"};
    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand()%startPhrases.size();
    std::cout<<startPhrases[randomIndex];
    return AskYesNo("do you want to start?")? PLAYER_X : PLAYER_O;

}
bool AskYesNo(std::string question)
{
    std::string answer;

    do {
        std::cout << question << "(y/n)";
        getline(std::cin, answer);

    } while (answer[0] != 'y' && answer[0] != 'n');

    if (answer[0] == 'y')
    {
        return true;
    }
    else{
      return false;  
    }

    
}
void DrawChoiceBoard(std::vector<char> board){
    
    std::cout<<"_____________"<<std::endl;
    std::cout<<"| "<< board[0]<<" | "<<board[1]<<" | "<<board[2]<<" | "<<std::endl;
    std::cout<<"_____________"<<std::endl;
    std::cout<<"| "<< board[3]<<" | "<<board[4]<<" | "<<board[5]<<" | "<<std::endl;
    std::cout<<"_____________"<<std::endl;
    std::cout<<"| "<< board[6]<<" | "<<board[7]<<" | "<<board[8]<<" | "<<std::endl;
    std::cout<<"_____________"<<std::endl;
}
int getPlayerInput(std::vector<int> & availableBoxes){
    
    int temporalPlayerInput{};
    bool isBoxedUsed = true;
    int spaceToErase{};

    std::cout<<"Pick a box: ";

    do{
        temporalPlayerInput = checkValidInput();
        for(int i = 0; i<availableBoxes.size(); i++){
            if(availableBoxes[i]==temporalPlayerInput){
                isBoxedUsed = false;
                spaceToErase = i;
            }
        }
        if(isBoxedUsed){
            std::cout<<"That boxed is already used"<<std::endl;
        }

    }while(isBoxedUsed);

    availableBoxes.erase(availableBoxes.begin() + spaceToErase);

    return temporalPlayerInput;
    
}
int  checkValidInput(){

    std::string temporalPlayerInput{};
    bool isValid = false;
   
    do{
        
       std::getline(std::cin,temporalPlayerInput);
       isValid = checkDigit(temporalPlayerInput[0]);
       if(!isValid){
        std::cout<<"Invalid input"<<std::endl;
       }

    }while(!isValid);

    return int(temporalPlayerInput[0]-48);
}
bool checkDigit(char check){
    return check == '0' ||check == '1' ||check == '2' ||check == '3' ||check == '4' ||check == '5' ||check == '6' ||check == '7' ||check == '8';
}
char winner(const std::vector<char>  & board){

}