#include <bits/stdc++.h>
using namespace std;

class Player
{
    string name;
    char symbol;

public:
    Player()
    {
        this->name = " ";
        this->symbol = ' ';
    }

    //setter method
    void setName(string x)
    {
        this->name = x;
    }

    //setter method
    void setSymbol(char x)
    {
        this->symbol = x;
    }

    //getter method
    string getName()
    {
        return this->name;
    }

    //getter method
    char getSymbol()
    {
        return this->symbol;
    }
};

class Canvas
{
    char board[3][3];
    int boardLength;

public:
    Canvas()
    {
        //initialise the board;
        this->boardLength = 3;
    }
    void display()
    {
        cout << "\n";
        for (int i = 0; i < boardLength; i++)
        {
            cout << "\n";
            for (int j = 0; j < boardLength; j++)
            {
                cout << "["<< board[i][j] << "] ";
            }
        }
        cout << "\n";
    }

    void clearBoard()
    {
        for (int i = 0; i < boardLength; i++)
            for (int j = 0; j < boardLength; j++)
            {
                this->board[i][j] = ' ';
            }
    }

    bool updateBoard(int r, int c, char symbol)
    {
        if (r < 0 || r >= boardLength || c < 0 || c >= boardLength)
        { //invalid row,col
            return false;
        }
        if (board[r][c] != ' ')
        { //location not empty
            return false;
        }

        //all ok, update the board
        this->board[r][c] = symbol;
        return true;
    }

    bool isFullBoard()
    {
        for (int i = 0; i < boardLength; i++)
        {
            for (int j = 0; j < boardLength; j++)
            {
                //compare with empty
                if (this->board[i][j] == ' ')
                {
                    return false;
                }
            }
        }
        return true;
    }
    //getter methods
    int getRows()
    {
        return boardLength;
    }
    int getCols()
    {
        return boardLength;
    }
    int valueAtCoordinate(int r, int c)
    {
        return this->board[r][c];
    }
};
class TicTacToe
{
    vector<Player> players;
    Canvas canvas;

public:
    TicTacToe()
    {

        for (int i = 0; i < 2; i++)
        {
            this->players.push_back(Player());
            this->canvas = Canvas();
        }
    }

    //win rules
    bool checkWins(char symbol)
    {
        int r = this->canvas.getRows();
        int c = this->canvas.getCols();

        //check for rows
        for (int i = 0; i < 3; i++)
        {
            char v1 = this->canvas.valueAtCoordinate(i, 0);
            char v2 = this->canvas.valueAtCoordinate(i, 1);
            char v3 = this->canvas.valueAtCoordinate(i, 2);
            if (v1 == symbol and v2 == symbol and v3 == symbol)
            { 
                 
                return true;
            }
        }
        //check for cols
        for (int i = 0; i < 2; i++)

        {
            char v1 = this->canvas.valueAtCoordinate(0, i);
            char v2 = this->canvas.valueAtCoordinate(1, i);
            char v3 = this->canvas.valueAtCoordinate(2, i);
            if (v1 == symbol and v2 == symbol and v3 == symbol)
            {
              
                return true;
            }
        }
        //check for diagonal
        int flag = 0;
        for (int i = 0; i < 2; i++)
        {
            int temp = this->canvas.valueAtCoordinate(i, i);
            if (temp != symbol)
            {
                flag = 1;
                break;
            }
        }
            if (flag == 0)
            {
                
              return true;
            }
            
        

        //check for reverse diagonal
        flag = 0;
        for (int i = 0; i < 2; i++)

        {
            int temp = this->canvas.valueAtCoordinate(i, r - i - 1);
            if (temp != symbol)
            {
                flag = 1;
                break;
            }
         }
         if (flag == 0)
            {
                 
                return true;
            }
           
        
        return false;
    }

    void play()
    {
        //setup player names and symbols
        char symbols[] = {'X', 'O'};
        for (int i = 0; i < 2; i++)
        {
            string name;
            cout << "\nEnter name for player:  ";
            cin >> name;
            this->players[i].setName(name);
            this->players[i].setSymbol(symbols[i]);
            cout << "\nyour symbol is "<< symbols[i];
        }

        //setup board
        this->canvas.clearBoard();

        //local variable for temporary and logical purposes
        bool isDraw = true;
        int current = 0; //voidault

        //play
        this->canvas.display();
        while (not this->canvas.isFullBoard())
        {
            string name = this->players[current].getName();
            char sym = this->players[current].getSymbol();
            int r, c;

            cout << name << "("<< sym << ")"<< "plays {\n";
            cout << "\nrow coordinate (0-2) ";
            cin >> r;
            cout << "\ncol coordinate (0-2) ";
            cin >> c;
            if (this->canvas.updateBoard(r, c, sym))
            {
                this->canvas.display();
                //check for win
                if (this->checkWins(sym))
                {
                    cout <<"\n"<< name << "("<< sym << ") WINS!!!!!";
                    isDraw = false;
                    break;
                }
                //change the player
                current = (current + 1) % 2;
            }
            else
            {
                cout << "Invalid Move by"<< name << " kindly play again.\n";

                if (isDraw)
                {
                    cout << "Game Draw!!!";
                }
            }
        }
    }
};
int main()
{
    TicTacToe t = TicTacToe();
    char ch = 'y';
    while (ch == 'y' or ch == 'Y')
    {
        t.play();
        cout << ("play again? ");
        cin >> ch;
    }
    return 0;
}
