#include <iostream>
#include <string>

using namespace std;
//agent stuct and functions
struct agent
{
    int agentNumber;
    bool rescue;
    char **map;
    int field;
    int column;
    string hiddenWord;
};

agent initializeAgent(int number)
{
    int field, column;

    string mapLine, hiddenWord;
    cin >> field >> column;
    cin >> hiddenWord;

    agent newAgent;
    newAgent.agentNumber = number;
    newAgent.field = field;
    newAgent.column = column;
    newAgent.hiddenWord = hiddenWord;

    //initialize array
    newAgent.map = new char *[field];
    for (size_t j = 0; j < field; j++)
    {
        newAgent.map[j] = new char[column];
    }

    //if string lenght is equal field lenght asign string to map
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
void print(char **map, int field, int column)
{
    cout << "---------------" << endl;
    for (size_t i = 0; i < field; i++)
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

bool readLetter(string secretWord, char **map, int maxField, int maxColumn, int field = 0, int column = 0)
{
   
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
        bool rescue =readLetter(agents[i].hiddenWord, agents[i].map, agents[i].field, agents[i].column);
        agents[i].rescue = rescue;
    }

    // print(agents[0].map, agents[0].field, agents[0].column);

    for (int i = 0; i < personCount; i++)
    {
        string toPrint = agents[i].rescue == true ? "Need Help" : "Do Not";
        cout << agents[i].agentNumber + 1<<" "<< toPrint << endl;
        delete agents[i].map;
    }

    return 0;
}