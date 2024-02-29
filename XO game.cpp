#include <bits/stdc++.h>
using namespace std;

#define AI 1
#define human 2
#define size 3
#define AI_move 'O'
#define human_move 'X'

void show_board(char board[][size]) 
{
    cout << "\t" << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "\t" << "-----------" << endl;
    cout << "\t" << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "\t" << "-----------" << endl;
    cout << "\t" << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl << endl;
}

void instructions() 
{
    cout << "\nWelcome to Tic-Tac-Toe! 🎉\n";
    cout << "\nHey there! I'm the champion AI. Think you can beat me? 💪\n";
    cout << "\nLet's see how well you know our beloved game of tic-tac-toe. 🤔\n";
    cout << "You will be playing as X and I will play as O. 🕹️\n";
    cout << "Let me tell you the rules beforehand so that you don't cry when you lose. 😏\n";
    cout << "Get three X's in a row - up, down, or diagonally! ⭐\n\n";


    cout << "\t  1 | 2 | 3  \n";
    cout << "\t -----------\n";
    cout << "\t  4 | 5 | 6  \n";
    cout << "\t -----------\n";
    cout << "\t  7 | 8 | 9  \n";
    cout << endl;
}

void initialize(char board[][size]) 
{
    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++) 
        {
            board[i][j] = ' ';
        }
    }
}

void winner(int chance) 
{
    if (chance == AI) 
    {
        cout << "One more victory to my winning streak! Better luck next time, mere human. 😉🏆\n";
    } 
    else if (chance == human) 
    {
        cout << "You have defeated AI! An extraordinary achievement, mortal!\n";
    }
}

bool row(char board[][size]) 
{
    for (int i = 0; i < size; i++) 
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') 
        {
            return true;
        }
    }
    return false;
}

bool column(char board[][size]) 
{
    for (int i = 0; i < size; i++) 
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') 
        {
            return true;
        }
    }
    return false;
}

bool diagonal(char board[][size]) 
{
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') 
    {
        return true;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') 
    {
        return true;
    }
    return false;
}

bool game_over(char board[][size]) 
{
    return (row(board) || column(board) || diagonal(board));
}

int mini_max_algo(char board[][size], int depth, bool is_ai) 
{
    int score = 0, best_score = 0;

    if (game_over(board)) 
    {
        if (is_ai == true) 
        {
            return -10;
        } else 
        {
            return 10;
        }
    } 
    else 
    {
        if (depth < 9) 
        {
            if (is_ai == true) 
            {
                best_score = -999;
                for (int i = 0; i < size; i++) 
                {
                    for (int j = 0; j < size; j++) 
                    {
                        if (board[i][j] == ' ') 
                        {
                            board[i][j] = AI_move;
                            score = mini_max_algo(board, depth + 1, false);
                            board[i][j] = ' ';
                            if (best_score < score) 
                            {
                                best_score = score;
                            }
                        }
                    }
                }
                return best_score;
            } 
            else 
            {
                best_score = 999;
                for (int i = 0; i < size; i++) 
                {
                    for (int j = 0; j < size; j++) 
                    {
                        if (board[i][j] == ' ') 
                        {
                            board[i][j] = human_move;
                            score = mini_max_algo(board, depth + 1, true);
                            board[i][j] = ' ';
                            if (score < best_score) 
                            {
                                best_score = score;
                            }
                        }
                    }
                }
                return best_score;
            }
        } 
        else 
        {
            return 0;
        }
    }
}

int move(char board[][size], int move_idx) 
{
    int x = -1, y = -1, score = 0, best = INT_MIN;

    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++) 
        {
            if (board[i][j] == ' ') 
            {
                board[i][j] = AI_move;
                score = mini_max_algo(board, move_idx + 1, false);
                board[i][j] = ' ';
                if (score > best) 
                {
                    best = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return x * 3 + y;
}

void play(int chance) 
{
    char board[size][size];
    int x = 0, y = 0, idx = 0;

    initialize(board);
    instructions();

    while (game_over(board) == false && idx != size * size) 
    {
        int n;
        if (chance == 1) 
        {
            n = move(board, idx);
            x = n / size;
            y = n % size;

            board[x][y] = AI_move;
            cout << "I made a move at " << n + 1 << ", Getting close to victory! 🌟\n\n";
            show_board(board);
            idx++;
            chance = 2;
        } 
        else if (chance == 2) 
        {
            cout << "You can insert in the following positions:" << endl;
            for (int i = 0; i < size; i++) 
            {
                for (int j = 0; j < size; j++) 
                {
                    if (board[i][j] == ' ') 
                    {
                        cout << i * size + (j + 1) << " ";
                    }
                }
            }

            cout << endl << endl << "Insert the number of your desired position: ";
            cin >> n;

            n--;
            x = n / size;
            y = n % size;

            if (board[x][y] == ' ' && n < 9 && n >= 0) 
            {
                board[x][y] = human_move;
                cout << "Such a silly move! I see all, and victory draws near.\n\n";
                show_board(board);
                idx++;
                chance = 1;
            } 
            else if (board[x][y] != ' ' && n < 9 && n >= 0) 
            {
                cout << "This place has been occupied. Try again. Apparently, humans struggle with visibility. 😂\n";
            } 
            else if (n > 8 || n < 0) 
            {
                cout << "Invalid Position. What a shame... can't even see the numbers now. 😏\n";
            }
        }
    }

    if (game_over(board) == false && idx == size * size) 
    {
        cout << "See, I told you... you can't defeat me. Better luck next time! 😎\n";
    } 
    else 
    {
        if (chance == 1) 
        {
            chance = 2;
        } 
        else 
        {
            chance = 1;
        }
        winner(chance);
    }
}

int main() 
{
    cout << endl << "----------------------------------------" << endl << endl;
    cout << "\tWelcome to Tic-Tac-Toe! 🎮\n";
    cout << endl << "----------------------------------------" << endl << endl;

    char c = 'Y';

    do 
    {
        char choice;
        cout << "START FIRST? (Y/N): ";
        cin >> choice;
        if ((choice == 'Y') || (choice == 'y')) 
        {
            play(human);
        } 
        else if (choice == 'N' || choice == 'n') 
        {
            play(AI);
        } 
        else 
        {
            cout << "\n\nInvalid Choice! Unable to see the letters? 👀\n" << endl;
        }

        cout << "WANT TO QUIT? (Y/N): ";
        cin >> c;
    } 
    while ((c == 'N') || (c == 'n'));

    return 0;
}
