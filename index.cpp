#include <iostream>
#include <string>

using namespace std;
//agent stuct and functions
struct agent
{
    int agentNumber;
    bool rescue;
    char **map;
    int row;
    int column;
    string hiddenWord;
};

agent initializeAgent(int number)
{
    int row, column;

    string mapLine, hiddenWord;
    cin >> row >> column;
    cin >> hiddenWord;

    agent newAgent;
    newAgent.agentNumber = number;
    newAgent.row = row;
    newAgent.column = column;
    newAgent.hiddenWord = hiddenWord;

    //initialize array
    newAgent.map = new char *[row];
    for (size_t j = 0; j < row; j++)
    {
        newAgent.map[j] = new char[column];
    }

    //if string lenght is equal row lenght asign string to map
    for (size_t i = 0; i < row; i++)
    {
        cin >> mapLine;
        for (size_t j = 0; j < column; j++)
        {

            newAgent.map[i][j] = mapLine[j] != NULL ? mapLine[j] : '.';
        }
    }

    return newAgent;
}

//functionality
void print(char **map, int row, int column)
{
    cout << "---------------" << endl;
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            cout << map[i][j];
        }
        cout << endl;
    }
}
int fib(int n)
{
    if (n == 0)
    {
        return 0;
    }
    else if (n == 1 || n == 2)
    {
        return 1;
    }
    return fib(n - 1) + fib(n - 2);
}

bool fibonacciSuccession(int n)
{
    int i = 3;
    int fibonacci = 0;
    do
    {
        fibonacci = fib(i);
        i++;
    } while (fibonacci < n);

    return fibonacci == n;
}

void rotateRow(char **map, int row, int column)
{
    char firstColumn[row];
    int index = 0;

    for (size_t i = 0; i < column; i++)
    {
        firstColumn[i] = map[i][0];
    }
    for (size_t i = 0; i < column; i++)
    {
        for (size_t j = 0; j < row; j++)
        {
            if (i < row - 1)
            {

                map[i][j] = map[i + 1][j];
            }
            else
            {
                map[i][j] = firstColumn[index];
                index += 1;
            }
        }
    }
}
void rotateColumn(char **map, int row, int column)
{

    char firstColumn[column];
    int index = 0;

    for (size_t i = 0; i < column; i++)
    {
        firstColumn[i] = map[0][i];
        // cout << map[0][i] <<endl;
    }

    for (size_t i = 0; i < row; i++)
    {

        for (size_t j = 0; j < column; j++)
        {
            if (j < column - 1)
            {

                map[i][j] = map[i][j + 1];
            }
            else
            {
                map[i][j] = firstColumn[index];
                index += 1;
            }
        }
    }
}

//backtraking
void rotate(int moment, char **map, int maxRow, int maxColumn)
{
    if (moment % 2 == 0)
    {
        rotateColumn(map, maxRow, maxColumn);
    }
    else
    {
        rotateRow(map, maxRow, maxColumn);
    }
}

bool readLetter(string secretWord, char **map, int maxrow, int maxColumn, int row = 0, int column = 0, int letterCount = 0, int moment = 0)
{
    bool find = true;
    moment += 1;
    // print(map, maxrow, maxColumn);

    if (map[row][column] == secretWord[0])
    {
        map[row][column] = '.';
        letterCount += 1;
        secretWord = secretWord.substr(1, secretWord.length() - 1);

        if (secretWord.length() > 0)
        {

            if (letterCount >= 4 && fibonacciSuccession(letterCount))
            {
                rotate(moment, map, maxrow, maxColumn);
            }

            if (maxrow - 1 > row)
            {
                find = readLetter(secretWord, map, maxrow, maxColumn, row + 1, column, letterCount, moment);
                if (find)
                {
                    return true;
                }
            }
            else if (maxColumn - 1 > column)
            {
                find = readLetter(secretWord, map, maxrow, maxColumn, 0, column + 1, letterCount, moment);
                if (find)
                {
                    return true;
                }
            }
        }
        else
        {
            return true;
        }
    }
    else
    {
        if (maxrow - 1 > row)
        {
            find = readLetter(secretWord, map, maxrow, maxColumn, row + 1, column, letterCount, moment);
            if (find)
            {
                return true;
            }
        }
        else if (maxColumn - 1 > column)
        {
            find = readLetter(secretWord, map, maxrow, maxColumn, 0, column + 1, letterCount, moment);
            if (find)
            {
                return true;
            }
        }

        return false;
    }
}

int main()
{
    int personCount;

    cin >> personCount;
    // const int PERSONCOUNT = personCount;
    agent *agents = new agent[personCount];

    for (int i = 0; i < personCount; i++)
    {
        agents[i] = initializeAgent(i);
        bool rescue = readLetter(agents[i].hiddenWord, agents[i].map, agents[i].row, agents[i].column);
        agents[i].rescue = rescue;
        // rotateColumn(agents[i].map, agents[i].row, agents[i].column);
        // print(agents[i].map, agents[i].row, agents[i].column);
    }

    // print(agents[0].map, agents[0].row, agents[0].column);

    for (int i = 0; i < personCount; i++)
    {
        string toPrint = agents[i].rescue == true ? "Need Help" : "Do Not";
        cout << agents[i].agentNumber + 1 << " " << toPrint << endl;
        delete agents[i].map;
    }

    return 0;
}