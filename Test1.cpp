#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string.h>

using namespace std;

void Clear(int A[8][8]);//Clears the newly formed array(Fills all places with -1)
void Display(int A[8][8]);//Displays the solution, if stopped press enter key to get the next solution
int Check(int A[8][8], int row, int col);//Displays No. of moves of all the next squares in line
int Lowest(int &A);//takes output of Check() and finds the move with lowest squares to go to, updates so that there is no repetition
void Knight(int A[8][8], int move, int row, int col);//Main Action Happens Here

int row_delta[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int col_delta[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int N = 8;

int main()
{
    int srow, scol;
    int A[8][8];
    int d;
    Clear(A);
    cout<<"Enter Starting row for Knight.\n";
    cin>>srow;
    cout<<"Enter starting coloumn for Knight.\n";
    cin>>scol;
    if(srow<0||scol<0||srow>=N||scol>=N)
        cout<<"Invalid Input";
    else
        Knight(A,1,srow,scol);
    return 0;
}

void Knight(int A[8][8], int move, int row, int col)
{
    int moves, lowest, nrow, ncol;
    if(move == N*N)
    {
        A[row][col] = move;
        Display(A);
        A[row][col] = -1;
        return;
    }
    A[row][col] = move;
    moves = Check(A,row,col);
    do
    {
        lowest = Lowest(moves);
        if(lowest==-1)
            break;
        nrow = row+row_delta[lowest];
        ncol = col+col_delta[lowest];
        //Display(A);
        //Decomment the above line to see the process of selection step by step.
        Knight(A, move+1, nrow, ncol);
    } while (true);
    A[row][col] = -1;
}

void Clear(int A[8][8])
{
    for(int i = 0; i<N; i++)
    {
        for(int j = 0; j<N; j++)
        {
            A[i][j] = -1;
        }
    }
}

void Display(int A[8][8])
{
    cout << "\n     0    1    2    3    4    5    6    7\n";
    cout << "   ---------------------------------------\n";
    for (int i = 0; i < N; i++)
    {
        cout << i <<" | ";
        for (int j = 0; j < N; j++)
        {
            cout << setw(2) << setfill('0') << A[i][j] << " | ";

        }
        cout << "\n   ---------------------------------------\n";
    }
    cin.get();//Comment this to get Output Constantly
}

int Check(int A[8][8], int row, int col)
{
    int nrow, ncol, nnrow, nncol, counter = 0, end = 0;
    for(int i = 0; i <8; i++)
    {
        counter = 0;
        nrow = row + row_delta[i];
        ncol = col + col_delta[i];
        if(ncol>=N||nrow>=N||nrow<0||ncol<0||A[nrow][ncol]>-1)//pos out of bounds
        {
           end = end*10 + 9;
           continue;
        }
        for(int j = 0; j < 8; j++)
        {
            nnrow = nrow + row_delta[j];
            nncol = ncol + col_delta[j];
            if(nnrow==row&&nncol==col)
                continue;
            if(nncol>=N||nnrow>=N||nnrow<0||nncol<0)
            {
                continue;
            }
            if(A[nnrow][nncol]<=-1)
                counter++;
        }
        end = end*10 + counter;
    }
    return end;
}

int Lowest(int &A)
{
    int lowest = 7, cur = 0, cA = A, pos = -1;
    int Arr[8];
    for(int i = 7;i>-1;i--)
    {
        cur = cA%10;
        Arr[i] = cur;
        if(cur<=lowest&&cur<8)
        {
            lowest = cur;
            pos = i;
        }
        cA = cA/10;
    }
    cA = 0;
    if(pos==-1)
        return -1;
    Arr[pos] = 9;
    for(int j = 0;j<8;j++)
        cA = cA*10+Arr[j];
    A = cA;
    return pos;
}