// de columna a fila
void rotateColumn(char **map, int row, int column)
{
    char firstColumn[column];
    int index = 0;

    for (size_t i = 0; i < column; i++)
    {
        firstColumn[i] = map[0][i];
    }
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            if (i < row - 1)
            {

                map[j][i] = map[i + 1][j];
            }
            else
            {
                map[j][i] = firstColumn[index];
                index += 1;
            }
        }
    }
}