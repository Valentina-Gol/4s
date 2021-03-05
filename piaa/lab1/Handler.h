#ifndef HANDLER
#define HANDLER
#include <vector>
#include "Square.h"

class Handler{

public:  
    bool CheckAllMatrix(int** matrix, int matrix_size, int& x_coordinate, int& y_coordinate);
    void PopBackVector(int** matrix, int matrix_size, std::vector<Square>& vector, int vector_size);
    int FindNewSizeRightDown(int** matrix, int matrix_size, int x_coordinate, int y_coordinate);
    int FindNewSizeDownLeft(int** matrix, int matrix_size, int x_coordinate, int y_coordinate);
    int FindNewSizeLeftUp(int** matrix, int matrix_size, int x_coordinate, int y_coordinate);
    int FindNewSizeUpRight(int** matrix, int matrix_size, int x_coordinate, int y_coordinate);
    void SetSquareOfOnes(int** matrix, int matrix_size, int x_coordinate, int y_coordinate, int square_size);
    void SetSquareOfZeros(int** matrix, int matrix_size, int x_coordinate, int y_coordinate, int square_size);
    bool CheckRightPath(int** matrix, int matrix_size, int x_coordinate, int y_coordinate, int check_size);
    bool CheckLeftPath(int** matrix, int matrix_size, int x_coordinate, int y_coordinate, int check_size);
    bool CheckDownPath(int** matrix, int matrix_size, int x_coordinate, int y_coordinate, int check_size);
    bool CheckUpPath(int** matrix, int matrix_size, int x_coordinate, int y_coordinate, int check_size);
};

#endif 