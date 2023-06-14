#include<iostream>
#include<ios>
#include<iomanip>
#include<vector>
#include<time.h>
#include<string>

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
    int IA_Input{};

    std::vector<char> board (NUM_SQUARES,EMPTY);
    std::vector<int> availableBoxes = {0,1,2,3,4,5,6,7,8};
    char winState = 'N';
    //First turn is X turn
    char actualTurn = PLAYER_X;

    Welcome();

    //Get player and IA symbol
    player = GetPlayerSymbol();
    IA = player==PLAYER_X? PLAYER_O : PLAYER_X;

    std::cout<<"\nPlayer: "<<player<<std::endl;
    std::cout<<"IA: "<<IA<<std::endl;


    while(winState == NO_ONE){ 
       
        DrawChoiceBoard(board); 
        if(actualTurn == player){
            std::cout<<std::endl<<"It is your turn, pick a box"<<std::endl;
            playerInput = getPlayerInput(availableBoxes);
            board[playerInput] = player;
            actualTurn = IA;
        }
        else{
            std::cout<<std::endl<<"It is my turn"<<std::endl;
            int randomIAIndex = rand()%availableBoxes.size();
            IA_Input = availableBoxes[randomIAIndex];
            board[IA_Input] = IA;
            availableBoxes.erase(availableBoxes.begin() + randomIAIndex);
            actualTurn = player;
        }
        
        
        winState = winner(board);

    } 
    std::cout<<"\nFinal board"<<std::endl;
    DrawChoiceBoard(board); 
    if(winState == TIE){
        std::cout<<"\nIt's a Tie"<<std::endl;
        //Add salty IA rechallenge
    }
    else{
        if(winState == IA){
            std::cout<<"And I have won!!"<<std::endl;
            //Add a random IA win phrase
        }
        else{
            std::cout<<"And you have won, what a a surprise!!";
            //Add salty IA loose phares 
        }
    }

    
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
    return AskYesNo(" do you want to start?")? PLAYER_X : PLAYER_O;

}
bool AskYesNo(std::string question)
{
    std::string answer;

    do {
        std::cout << question << "(y/n)";
        std::getline(std::cin, answer);

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

    //Vertical lines check
    for(int i = 0; i< board.size(); i +=3){
        if(board[i]!= EMPTY && board[i] == board[i+1] && board[i+1] == board[i+2]){
        return board[i];
    }
    }
    //Horizontal lines check
    for(int i = 0; i< board.size(); i++){
        if(board[i]!= EMPTY && board[i] == board[i+3] && board[i+3] == board[i+6]){
        return board[i];
    }
    }
    //Diagonal check
    if(board[0]!= EMPTY && board[0] == board[4] && board[4] == board[8]){
        return board[0];
    }
     if(board[2]!= EMPTY && board[2] == board[4] && board[4] == board[6]){
        return board[2];
    }

    //Tie check
    for(int i  = 0; i<board.size(); i++){
        if(board[i] == EMPTY){
            return 'N';
        }
    }

    //Default
    return 'T';
   
}

