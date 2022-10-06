/*
Max Zurniewicz
10 / 05 / 2021
Lab 8 Tic-Tac_Toe
*/

#include <iostream>                                                     //includes iostream library that includes std::cout
#include <iomanip>                                                      //Includes iomanip library that is needed to use setw()
#include <cstdlib>                                                      //needed to generate random int
#include <random>                                                       //needed to generate random number
#include <time.h>
#include <fstream>

using namespace std;                                                    //We don't have to write std:: infront of every cout

void Title();                                                           //Mentions functions so that the program knows they exist
void Display();                                                         //Mentions functions so that the program knows they exist
int PlayerChoice();
int rand();                                                             //creates a function that generates random input
int checkWin();
int protectData(int);                                                   //Takes in int and returns an int
int compChoice();
double generateNumber(int, int);

char square[10] = { '0', '1', '2', '3', '4', '5','6','7','8','9' };     //creates 10 chars
int choice;
int randomNumber;
int i;
int turnCount;
string placeholder;
char response;

ofstream input;                                                         //creating stream for file
ifstream output;

int main()                                                              //Starts the program
{
    i = 0;
    Title();                                                            //Runs Title() function
    Display();                                                          //Runs Display() function
    input.open("winFile.txt", ios::trunc);                              //opens and clears file
    input.close();                                                      //close file
    while (true)
    {
        while (i == 0)                                                      //while no win occured
        {

            i = PlayerChoice();                                             //player choses
            if (i == 0)                                                     //if no win has occured still
            {
                i = compChoice();                                           //ai generates a move
                Display();                                                  //displays screen
            }
            else
            {
                Display();                                                  //if x won, it will display screen
            }
        }
        input.close();
        cout << "Do you want to play agian?(Y or N)\n";
        cin >> response;
        if (response == 'N')
        {
            output.open("winFile.txt", ios::out);
            if (!output)
            {
                cerr << "Error opening read file";     //cerr is used instead of cout in files
                exit(EXIT_FAILURE);                     //exits out
            }
            while (output >> placeholder)
            {
                cout << placeholder << endl;
            }
            break;
        }
    }
}

void Title()                                                            //Creating Title() function
{
    system("color 8D");                                                 //Created grey backgroud with light purple text
    cout << "Max Zurniewicz" << setw(21) << "09/19/2021\n";             //Displays Name and Date
    cout << "Win Week 4 Lab\tTic-Tac-Toe Project\n";                //Displays Lab name 
    cout << "List of commands used:\n"                                  //Displays promt for list of commands
        << setw(30) << "do while loop\n"                                      //Displays a command used
        << setw(38) << "rand()\n";                             //Displays a command used
    cout << "List of Objectives:\n"                                     //Displays prompt for objectives
        << setw(45) << "Determine winner and column\n\n";                //Displays objectives
}

void Display()                                                          //Creating Display() function
{
    cout << "_________________________________________________\n";                          //Creating top of display
    cout << "|               |               |               |\n";                          //This gap is needed to make display look like a square
    cout << "|\t" << square[1] << "\t|\t" << square[2] << "\t|\t" << square[3] << "\t|\n";  //Prints variables and columns
    cout << "|_______________|_______________|_______________|\n";                          //Prints bottom of the squares
    cout << "|               |               |               |\n";                          //This gap is needed to make display look like a square
    cout << "|\t" << square[4] << "\t|\t" << square[5] << "\t|\t" << square[6] << "\t|\n";  //Prints variables and columns
    cout << "|_______________|_______________|_______________|\n";                          //Prints bottom of the squares
    cout << "|               |               |               |\n";                          //This gap is needed to make display look like a square
    cout << "|\t" << square[7] << "\t|\t" << square[8] << "\t|\t" << square[9] << "\t|\n";  //Prints variables and columns
    cout << "|_______________|_______________|_______________|\n";                          //Prints bottom of display
}
int PlayerChoice()
{
    cout << "Choose square: ";
    cin >> choice;
    choice = protectData(choice);                                  //takes in int and returns int
    square[choice] = 'X';                                   //turns square into x
    
    i = checkWin();                                         //checks for win or draw
    return i;
}

int protectData(int choice)
{
    while (choice < 1 || choice > 9 || square[choice] == 'X' || square[choice] == 'O' || cin.fail())        //checks if choice is a valid option 
    {
        while (cin.fail())                                                                                  //if wrong data type
        {
            cin.clear();                                                                                    //it will clear and ignore users input
            cin.ignore();
        }
        cout << "\rChoose a valid square: ";                                                                //asks user to reinput a score until they enter a valid score
        cin >> choice;
    }
    return choice;                                                                                          //returns choice
}

int checkWin()
{
    
    for (int i = 1; i <= 7; i += 3)                                                                               //for loop to check for horizontal wins
    {
        if (square[i] == square[i + 1] && square[i + 1] == square[i + 2])                                               //checks for all 3 horizontal wins
        {
            if (square[i] == 'X')                                                                                       //checks if x won
            {
                cout << "Player 1 has won with a horizontal " << i << ", " << i + 1 << ", " << i + 2 << "!\n";                                                                                            
            }

            if (square[i] == 'O')                                                                                       //checks if O won
            {
                cout << "Player 2 has won with a horizontal " << i << ", " << i + 1 << ", " << i + 2 << "!\n";                                                                                              
            }
            input << square[i] << " has won with a horizontal " << i << "-" << i + 1 << "-" << i + 2 << endl;           //writes into file
            //input.close();
            return 1;                                                                                                   //signifies end of game
        }
    }


    for (int i = 1; i <= 3; i += 1)                                                                                     //for loop to check for vertical wins
    {
        if (square[i] == square[i + 3] && square[i + 3] == square[i + 6])                                               //checks for all 3 vertical wins
        {
            if (square[i] == 'X')                                                                                        //checks if x won
            {
                cout << "Player 1 has won with a vertical " << i << ", " << i + 3 << ", " << i + 6 << "!\n";
            }
            if (square[i] == 'O')                                                                                       //checks if O won
            {
                cout << "Player 2 has won with a vertical " << i << ", " << i + 3 << ", " << i + 6 << "!\n";
            }
            input << square[i] << " has won with a vertical " << i << "-" << i + 3 << "-" << i + 6 << endl;             //writes into file
            //input.close();
            return 1;
        }
    }
    if (square[1] == square[5] && square[5] == square[9])                                                               //checks for diagonal win
    {
        if (square[1] = 'X')                                                                                            //checks if x won
        {
            cout << ("Player 1 has won with a diagonal 1-5-9!\n");
        }
        else  if (square[1] = 'O')                                                                                      //checks if O won    
        {
            cout << ("Player 2 has won with a diagonal 1-5-9!\n");
        }
        
        input << square[1] << "has won with a diagonal 1-5-9" << endl;                                                  //writes into file
        //input.close(); 
        return 1;
    }
    else if (square[3] == square[5] && square[5] == square[7])                                                          //checks for diagonal win
    {
        if (square[1] = 'X')                                                                                            //checks if x won
        {
            cout << ("Player 1 has won with a diagonal 3-5-7!\n");
        }
        else if (square[1] = 'O')                                                                                       //checks if O won 
        {
            cout << ("Player 2 has won with a diagonal 3-5-7!\n");
        }
        input << square[1] << "has won with a diagonal 3-5-7" << endl;                                                  //writes into files
        //input.close();
        return 1;  
    }
    else if (square[1] != '1' && square[2] != '2' && square[3] != '3' && square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7] != '7' && square[8] != '8' && square[9] != '9')  //checks if all squares have been used which signifies a drawn game
    {
        cout << ("Game Drawn");
        input << "Game Drawn" << endl;
        //input.close();
        return 1;                               //returns 1(which signifies end of game)
      
    }
    else                                        //if no draw or win happened
    {
       // input.close()
        return 0;                                   //returns 0
    }
   
}
int compChoice()
{
    do
    {
        srand(time(NULL));                              //allows for truly random number to be generated
        randomNumber = generateNumber(1, 10);              //assigns a random number (1-9)
    } while (square[randomNumber] == 'X' || square[randomNumber] == 'O');         //if square has already been chosen, it will find another random number (1-9)

    square[randomNumber] = 'O';  //turns square into O

    i = checkWin();         //checks if win occured
    return i;               //i is returned and lets program know if win occured
}

double generateNumber(int x, int y)
{
    std::uniform_real_distribution<double> distribution(x, y);  // produces random number in range x <= # < y
    std::random_device rd;										//generates a sequence of uniformly distributed random numbers(not pseudo random)
    std::default_random_engine generator(rd());					//default random engine generates pseudo random numbers but since we combined them this is truly random
    return distribution(generator);
}

