#include<iostream>
#include<ios>
#include<iomanip>
#include<vector>
#include<time.h>
#include<string>
#include<algorithm>

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
int getPlayerInput(const std::vector<char> & board);
int _IATurn(std::vector<char> board, char IA, char player);
int  checkValidInput();
bool checkDigit(char check);
char winner(const std::vector<char>  & board);
std::string TiePhrase();
std::string WinPhrase();
std::string LoosePhrase();
void AnounceWinner(std::vector<char> board, char winState, char IA, char player);
void IATurn(std::vector<char> &board, char IA, char player);
void PlayerTurn(std::vector<char> &board, char player);
void chooseSimbols(char &player, char &IA);

int main(){
    
    do{
        char player{};
        char IA{};
        std::vector<char> board (NUM_SQUARES,EMPTY);
        char winState = NO_ONE; 
        char actualTurn = PLAYER_X;     //First turn is X turn

        Welcome();

        chooseSimbols(player,IA);
        
        while(winState == NO_ONE){  
            DrawChoiceBoard(board); 
            if(actualTurn == player){
                PlayerTurn(board,player);
            }
            else{
                IATurn(board, IA, player);
            }
            actualTurn = actualTurn==player? IA : player;       
            winState = winner(board);
        } 
        AnounceWinner(board, winState, IA, player);
        
    }while(AskYesNo("Do you want to play again?"));
    
    return 0;
}

void Welcome(){

    std::cout<<"\n\n\n\n\n\n\n****Welcome to TicTacToe****"<<std::endl;
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

    std::cout<<"Box numbers: "<<std::endl;        
    std::cout<<"_____________"<<std::endl;
    std::cout<<"| 0 | 1 | 2 | "<<std::endl;
    std::cout<<"_____________"<<std::endl;
    std::cout<<"| 3 | 4 | 5 | "<<std::endl;
    std::cout<<"_____________"<<std::endl;
    std::cout<<"| 6 | 7 | 8 | "<<std::endl;
    std::cout<<"_____________"<<std::endl;

    std::cout<<"Actual board: "<<std::endl;    
    std::cout<<"_____________"<<std::endl;
    std::cout<<"| "<< board[0]<<" | "<<board[1]<<" | "<<board[2]<<" | "<<std::endl;
    std::cout<<"_____________"<<std::endl;
    std::cout<<"| "<< board[3]<<" | "<<board[4]<<" | "<<board[5]<<" | "<<std::endl;
    std::cout<<"_____________"<<std::endl;
    std::cout<<"| "<< board[6]<<" | "<<board[7]<<" | "<<board[8]<<" | "<<std::endl;
    std::cout<<"_____________"<<std::endl;
}
int getPlayerInput(const std::vector<char> & board){
    
    int temporalPlayerInput{};
    bool isBoxedUsed = true;
    int spaceToErase{};


    do{
        temporalPlayerInput = checkValidInput();
        if(board[temporalPlayerInput] != EMPTY){
            std::cout<<"That boxed is already used"<<std::endl;
        }
        else{
            isBoxedUsed = false;
        }
        
    }while(isBoxedUsed);



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

std::string TiePhrase(){
    std::vector<std::string> phrase = {"Is this the best you can do?","Booooring, let's play again", "Let's do it again, I need to win", "It isn't winning but still better than loose", "I was just warming up, let's do it again"};
    
    //Random choices
    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand()%phrase.size();
    return phrase[randomIndex];
}
std::string WinPhrase(){
    std::vector<std::string> phrase = {"Better than i expected","You're truly the best", "Perfection must be your last name", "Imposible no one can defeat me", "You got lucky, next time I'll win", "Trully unexpected", "Pure luck, let me show you"};

    //Random choices
    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand()%phrase.size();
    return phrase[randomIndex];
}
std::string LoosePhrase(){
    std::vector<std::string> phrase = {"Ez", "Skill issues?", "As expected", "Like if you ever got an oportunity", "Do you want to loose again?", "This is skill at its biggest", "And once again I prove my supperiority"};

    //Random choices
    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand()%phrase.size();
    return phrase[randomIndex];
}

int _IATurn(std::vector<char> board, char IA, char player){

    int move = 0;
    

    while(move < board.size()){
        if(board[move] == EMPTY){
            board[move] = IA;
            if(winner(board)==IA){
                return move;
            }
            else{
                board[move] = EMPTY;
            }
        }
        move++;
    }

    move = 0;
    while(move < board.size()){
        
        if(board[move] == EMPTY){
            board[move] = player;
            if(winner(board)==player){
                return move;
            }
            else{
                board[move] = EMPTY;
            }
        }
        move++;
    }

    if(board[4]== EMPTY){ //Board center
        return 4;
    }

    std::vector<int> bestChoices = {0,2,4,8}; //Board corners
    std::random_shuffle(bestChoices.begin(), bestChoices.end());
    for(int i = 0; i<bestChoices.size(); i++){
        if(board[bestChoices[i]]== EMPTY){
            return bestChoices[i];
        }
    }

    std::vector<int> lastChoices = {1,3,5,7}; //Board cross
    std::random_shuffle(lastChoices.begin(), lastChoices.end());
    for(int i = 0; i<lastChoices.size(); i++){
        if(board[lastChoices[i]] == EMPTY){
            return lastChoices[i];
        }
    }
    

    return 0;
}

void AnounceWinner(std::vector<char> board, char winState, char IA, char player){
    std::cout<<"\nFinal board"<<std::endl;
        DrawChoiceBoard(board); 
        if(winState == TIE){
            std::cout<<"\nIt's a Tie"<<std::endl;
            std::cout<<TiePhrase()<<std::endl;
        }
        else{
            if(winState == IA){
                std::cout<<"And I have won!!"<<std::endl;
                std::cout<<LoosePhrase()<<std::endl;
            }
            else{
                std::cout<<"And you have won, what a a surprise"<<std::endl;
                std::cout<<WinPhrase()<<std::endl;
            }
        }
}
void IATurn(std::vector<char> &board, char IA, char player){
    int IA_Input{};
    std::cout<<std::endl<<"It is my turn"<<std::endl; 
    IA_Input = _IATurn(board, IA, player);
    std::cout<<"I have picked: "<<IA_Input<<std::endl;
    board[IA_Input] = IA;
}
void PlayerTurn(std::vector<char> &board, char player){
    int playerInput{};
    std::cout<<std::endl<<"It is your turn"<<std::endl;
    std::cout<<"Pick a box: "<<std::endl;
    playerInput = getPlayerInput(board);
    board[playerInput] = player;
}

void chooseSimbols(char &player, char &IA){
    player = GetPlayerSymbol();
    IA = player==PLAYER_X? PLAYER_O : PLAYER_X;
    std::cout<<"\nPlayer: "<<player<<std::endl;
    std::cout<<"IA: "<<IA<<std::endl;
}