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
    for (size_t i = 0; i < column; i++)
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
    if (n <= 1)
    {
        return 1;
    }
    return fib(n) + fib(n - 1);
}

bool readLetter(string secretWord, char **map, int maxrow, int maxColumn, int row = 0, int column = 0)
{
    // bool equal = map[row][column] == secretWord[0];
    // string ToPrint = equal ? "True": "False";
    // cout << ToPrint<<endl;

    if (map[row][column] == secretWord[0])
    {
        map[row][column] = '.';
        secretWord = secretWord.substr(1, secretWord.length() - 1);
        bool find = readLetter(secretWord, map, row++, column);
        
        if (!find){
            // if (readLetter(secretWord, map, row+2, column))
        }
    }
    else
    {
        return false;
    }
}

int main()
{
    int personCount;

    cin >> personCount;
    const int PERSONCOUNT = personCount;
    agent *agents = new agent[personCount];

    for (int i = 0; i < personCount; i++)
    {
        agents[i] = initializeAgent(i);
        bool rescue = readLetter(agents[i].hiddenWord, agents[i].map, agents[i].row, agents[i].column);
        agents[i].rescue = rescue;
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