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
    int row = 3, column = 8;

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
        // mapLine = i == 0 ? "i......h" : i == 1 ? "........"
        //    : "abcd.efg";
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
void printFlags(char **map, int row, int column, int direction, int ip, int jp)
{
    int rowView = ip;
    int columnView = jp;

    if (direction == 0)
    {
        columnView += 1;
    }
    else if (direction == 1)
    {
        rowView += 1;
        columnView += 1;
    }
    else if (direction == 2)
    {
        rowView += 1;
    }
    else if (direction == 3)
    {
        rowView += 1;
        columnView -= 1;
    }

    else if (direction == 4)
    {

        columnView -= 1;
    }
    else if (direction == 5)
    {
        rowView -= 1;
        columnView -= 1;
    }
    else if (direction == 6)
    {
        rowView -= 1;
    }
    else if (direction == 7)
    {
        rowView -= 1;
        columnView += 1;
    }

    cout << "---------------" << endl;
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            if (ip == i && jp == j)
            {
                cout << 'A';
            }
            else if (rowView == i && columnView == j)
            {
                cout << 'V';
            }
            else
            {

                cout << map[i][j];
            }
        }
        cout << endl;
    }
    cout << "---------------" << endl;
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

    cout << "rowRotate" << endl;
    char firstColumn[column];
    // int index = 0;

    for (size_t i = 0; i < column; i++)
    {
        firstColumn[i] = map[row - 1][i];
    }

    for (int i = row-1; i >= 0; i--)
    {

        for (int j = 0; j < column; j++)
        {
            if (i <= 0)
            {

                map[i][j] = firstColumn[j];
            }
            else
            {
                map[i][j] = map[i - 1][j];
            }
        }
    }
    
    // print(map, row, column);
}
void rotateColumn(char **map, int row, int column)
{
    cout << "columnRotate" << endl;
    char firstColumn[row];
    int index = 0;

    for (size_t i = 0; i < row; i++)
    {
        firstColumn[i] = map[i][0];
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
    print(map, row, column);
}

//backtraking
void rotate(int moment, char **map, int maxRow, int maxColumn)
{
    if (moment % 2 == 0)
    {
        rotateRow(map, maxRow, maxColumn);
    }
    else
    {
        rotateColumn(map, maxRow, maxColumn);
    }
}

bool indexOf(int *arr, char toSearch, char **map, int maxRow, int maxColumn, int row = 0, int column = 0)
{
    bool find = false;
    if (map[row][column] == toSearch)
    {
        arr[0] = row;
        arr[1] = column;
        map[row][column] = '-';
        find = true;
    }
    // cout << "entre aqui"<<endl;

    if (maxColumn - 1 > column && !find)
        find = indexOf(arr, toSearch, map, maxRow, maxColumn, row, column + 1);
    else if (maxRow - 1 > row && !find)
        find = indexOf(arr, toSearch, map, maxRow, maxColumn, row + 1, 0);

    return find;
}

int searchFromSide(char secretChar, char **map, int maxRow, int maxColumn, int row = 0, int column = 0, int direction = 0, int count = 0)
{
    bool find = false;
    int toReturn = -1;
    // derecha
    if (maxColumn - 1 > column && !find && map[row][column + 1] != '-')
    {
        printFlags(map, maxRow, maxColumn, 0, row, column);

        toReturn = map[row][column + 1] == secretChar ? 0 : -1;
        find = toReturn != -1 ? true : false;
    }
    // derecha abajo

    if (maxRow - 1 > row && maxColumn - 1 > column && !find && map[row + 1][column + 1] != '-')
    {
        printFlags(map, maxRow, maxColumn, 1, row, column);

        toReturn = map[row + 1][column + 1] == secretChar ? 1 : -1;
        find = toReturn != -1 ? true : false;
    }
    // abajo
    if (maxRow - 1 > row && !find && map[row + 1][column] != '-')
    {
        printFlags(map, maxRow, maxColumn, 2, row, column);

        toReturn = map[row + 1][column] == secretChar ? 2 : -1;
        find = toReturn != -1 ? true : false;
    }
    // abajo izq
    if (column > 0 && maxRow - 1 > row && !find && map[row + 1][column - 1] != '-')
    {
        printFlags(map, maxRow, maxColumn, 3, row, column);

        toReturn = map[row + 1][column - 1] == secretChar ? 3 : -1;
        find = toReturn != -1 ? true : false;
    }
    // izq

    if (column > 0 && !find && map[row][column - 1] != '-')
    {
        printFlags(map, maxRow, maxColumn, 4, row, column);

        toReturn = map[row][column - 1] == secretChar ? 4 : -1;
        find = toReturn != -1 ? true : false;
    }
    // izq arriba

    if (row > 0 && column > 0 && !find && map[row - 1][column - 1] != '-')
    {
        printFlags(map, maxRow, maxColumn, 5, row, column);

        toReturn = map[row - 1][column - 1] == secretChar ? 5 : -1;
        find = toReturn != -1 ? true : false;
    }
    //  arriba
    if (row > 0 && !find && map[row - 1][column] != '-')
    {
        printFlags(map, maxRow, maxColumn, 6, row, column);

        toReturn = map[row - 1][column] == secretChar ? 6 : -1;
        find = toReturn != -1 ? true : false;
    }
    // derecha  arriba

    if (row > 0 && maxColumn - 1 > column && !find && map[row - 1][column + 1] != '-')
    {
        printFlags(map, maxRow, maxColumn, 7, row, column);

        toReturn = map[row - 1][column + 1] == secretChar ? 7 : -1;
        find = toReturn != -1 ? true : false;
    }
    return toReturn;
}

bool readLetter(string secretword, char **map, int maxRow, int maxColumn, char oldChar, int row = 0, int column = 0, int letterCount = 1, int moment = 1)
{
    bool find = false;
    string newWord = secretword;

    moment += 1;
    if (newWord[0] == map[row][column])
    {
        letterCount += 1;
        oldChar = map[row][column];
        map[row][column] = '-';

        newWord = newWord.substr(1, newWord.length() - 1);

        if (newWord.length() <= 0)
        {
            return true;
        }
    }

    int directionOfmyChar = searchFromSide(newWord[0], map, maxRow, maxColumn, row, column);

    if (letterCount > 3 && fibonacciSuccession(moment))
    {
        rotate(moment, map, maxRow, maxColumn);
        directionOfmyChar = searchFromSide(newWord[0], map, maxRow, maxColumn, row, column);
    }


    if (directionOfmyChar == 0)
    {
        find = readLetter(newWord, map, maxRow, maxColumn, oldChar, row, column + 1, letterCount, moment);
        map[row][column] = oldChar;
        directionOfmyChar = searchFromSide(newWord[0], map, maxRow, maxColumn, row, column);
    }
    if (directionOfmyChar == 1)
    {
        find = readLetter(newWord, map, maxRow, maxColumn, oldChar, row + 1, column + 1, letterCount, moment);
        map[row][column] = oldChar;
        directionOfmyChar = searchFromSide(newWord[0], map, maxRow, maxColumn, row, column);
    }
    if (directionOfmyChar == 2)
    {
        find = readLetter(newWord, map, maxRow, maxColumn, oldChar, row + 1, column, letterCount, moment);
        map[row][column] = oldChar;
        directionOfmyChar = searchFromSide(newWord[0], map, maxRow, maxColumn, row, column);
    }
    if (directionOfmyChar == 3)
    {
        find = readLetter(newWord, map, maxRow, maxColumn, oldChar, row + 1, column - 1, letterCount, moment);
        map[row][column] = oldChar;
        directionOfmyChar = searchFromSide(newWord[0], map, maxRow, maxColumn, row, column);
    }
    if (directionOfmyChar == 4)
    {
        find = readLetter(newWord, map, maxRow, maxColumn, oldChar, row, column - 1, letterCount, moment);
        map[row][column] = oldChar;
        directionOfmyChar = searchFromSide(newWord[0], map, maxRow, maxColumn, row, column);
    }
    if (directionOfmyChar == 5)
    {
        find = readLetter(newWord, map, maxRow, maxColumn, oldChar, row - 1, column - 1, letterCount, moment);
        map[row][column] = oldChar;
        directionOfmyChar = searchFromSide(newWord[0], map, maxRow, maxColumn, row, column);
    }
    if (directionOfmyChar == 6)
    {
        find = readLetter(newWord, map, maxRow, maxColumn, oldChar, row - 1, column, letterCount, moment);
        map[row][column] = oldChar;
        directionOfmyChar = searchFromSide(newWord[0], map, maxRow, maxColumn, row, column);
    }
    if (directionOfmyChar == 7)
    {
        find = readLetter(newWord, map, maxRow, maxColumn, oldChar, row - 1, column + 1, letterCount, moment);
        map[row][column] = oldChar;
        directionOfmyChar = searchFromSide(newWord[0], map, maxRow, maxColumn, row, column);
    }

    return find;
}

int main()
{
    int personCount;

    cin >> personCount;
    agent *agents = new agent[personCount];

    for (int i = 0; i < personCount; i++)
    {
        agents[i] = initializeAgent(i);
        int arr[2] = {0, 0};
        bool rescue = false;

        if (indexOf(arr, agents[i].hiddenWord[0], agents[i].map, agents[i].row, agents[i].column))
        {
            cout << arr[0] << arr[1] << endl;
            rescue = readLetter(agents[i].hiddenWord.substr(1, agents[i].hiddenWord.length() - 1), agents[i].map, agents[i].row, agents[i].column, agents[i].hiddenWord[0] ,arr[0], arr[1]);
        }

        agents[i].rescue = rescue;
    }

    for (int i = 0; i < personCount; i++)
    {
        string toPrint = agents[i].rescue == true ? "Debe ser rescatado inmediatamente" : "No debe ser rescatado";
        cout <<"Agente #" <<agents[i].agentNumber + 1 << " " << toPrint << endl;
        delete agents[i].map;
    }

    return 0;
}