#include "Handler.h"
#include <algorithm>
#include <iostream>

int Handler::FindNewSizeRightDown(int** matrix, int matrix_size, int x_coordinate, int y_coordinate){
    int right_size = 1, down_size = 1;
    int i = x_coordinate, j = y_coordinate;

    int max_size = matrix_size-1;

    while (right_size <= max_size && j+right_size<matrix_size && matrix[i][j+right_size-1]!=1 ){
        right_size++;
    } 
    while (down_size <= max_size && i+down_size<matrix_size && matrix[i+down_size-1][j]!=1 ){
        down_size++;
    }

    return std::min(right_size, down_size);
}

int Handler::FindNewSizeDownLeft(int** matrix, int matrix_size, int x_coordinate, int y_coordinate){
    int left_size = 1, down_size = 1;
    int i = x_coordinate, j = y_coordinate;
    int max_size = matrix_size-1;

    while (left_size <= max_size && j-left_size>=0 && matrix[i][j-left_size]!=1){
        left_size++;
    } 
    while (down_size <= max_size && i+down_size<matrix_size && matrix[i+down_size-1][j]!=1){
        down_size++;
    }

    return std::min(left_size, down_size);
}

int Handler::FindNewSizeLeftUp(int** matrix, int matrix_size, int x_coordinate, int y_coordinate){
    int left_size = 1, up_size = 1;
    int i = x_coordinate, j = y_coordinate;
    int max_size = matrix_size-1;

    while (left_size <= max_size && j-left_size >= 0 && matrix[i][j-left_size]!=1){
        left_size++;
    } 
    while (up_size <= max_size && i-up_size >=0 && matrix[i-up_size][j]!=1){
        up_size++;
    }
    
    return std::min(left_size, up_size);
}

int Handler::FindNewSizeUpRight(int** matrix, int matrix_size, int x_coordinate, int y_coordinate){
    int right_size = 1, up_size = 1;
    int i = x_coordinate, j = y_coordinate;
    int max_size = matrix_size-1;

    while (right_size <= max_size && j+right_size<matrix_size && matrix[i][j+right_size-1]!=1){
        right_size++;
    } 
    while (up_size <= max_size && i-up_size<matrix_size && matrix[i-up_size][j]!=1 ){
        up_size++;
    }

    return std::min(right_size, up_size);
}

void Handler::SetSquareOfOnes(int** matrix, int matrix_size, int x_coordinate, int y_coordinate, int square_size){
    for (int i = x_coordinate; i < x_coordinate + square_size; i++){
        for (int j = y_coordinate; j < y_coordinate + square_size;j++){
            matrix[i][j]=1;
        }
    }
    
}

void Handler::SetSquareOfZeros(int** matrix, int matrix_size, int x_coordinate, int y_coordinate, int square_size){
    std::cout<<"Set zero at "<<x_coordinate<<' '<<y_coordinate<<" Size: "<<square_size<<"\n";
    for (int i = x_coordinate; i < x_coordinate + square_size; i++){
        for (int j = y_coordinate; j < y_coordinate + square_size;j++){
            matrix[i][j]=0;
        }
    }
    
}

bool Handler::CheckRightPath(int** matrix, int matrix_size, int x_coordinate, int y_coordinate, int check_size){
    if (y_coordinate + check_size < matrix_size && matrix[x_coordinate][y_coordinate+check_size]!=1){
        return true;
    }
    return false;
}

bool Handler::CheckLeftPath(int** matrix, int matrix_size, int x_coordinate, int y_coordinate, int check_size){
    if (y_coordinate - check_size>= 0 && matrix[x_coordinate][y_coordinate - check_size]!=1){
        return true;
    }
    return false;
}

bool Handler::CheckDownPath(int** matrix, int matrix_size, int x_coordinate, int y_coordinate, int check_size){
    //std::cout<<x_coordinate<<' '<<y_coordinate<<' '<<check_size<<' '<<matrix_size<<" \n";
    if (x_coordinate + check_size < matrix_size && matrix[x_coordinate + check_size][y_coordinate]!=1){
        //std::cout<<"ok\n";
        return true;    
    }
    return false;
}

bool Handler::CheckUpPath(int** matrix, int matrix_size, int x_coordinate, int y_coordinate, int check_size){
    if (x_coordinate - check_size >= 0 && matrix[x_coordinate - check_size][y_coordinate]!=1){
        return true;
    }
    return false;
}

bool Handler::CheckAllMatrix(int** matrix, int matrix_size, int& x_coordinate, int& y_coordinate){
    for (int i=0;i<matrix_size;i++){
        for (int j=0;j<matrix_size;j++){
            if (matrix[i][j]==0){
                x_coordinate = i;
                y_coordinate = j;
                return true;
            }
        }
    }
    return false;
}

void Handler::PopBackVector(int** matrix, int matrix_size, std::vector<Square>& vector, int& vector_size){
    Square square;
    while (!vector.empty() && square.GetSize()<=2 ){
        std::cout<<"\nDELETE Vector: ";
        this->PrintVector(vector, vector_size);

        square = vector[vector_size-1];
        vector.pop_back();
        vector_size-=1;
        this->SetSquareOfZeros(matrix, matrix_size, square.GetXCoordinate(), square.GetYCoordinate(), square.GetSize());
        if (square.GetSize()>2){
            this->SetSquareOfOnes(matrix, matrix_size, square.GetXCoordinate(), square.GetYCoordinate(), square.GetSize()-1);
            vector.push_back(Square(square.GetSize()-1, square.GetXCoordinate(), square.GetYCoordinate()));
            vector_size=1;
            break;
        }
    }

}

void Handler::PrintMatrix(int** matrix, int matrix_size){
    for (int i=0;i<matrix_size;i++){
        for (int j=0;j<matrix_size;j++){
            std::cout<<matrix[i][j]<<' ';
        }
        std::cout<<'\n';
    }
}

void Handler::PrintVector(std::vector<Square> vector, int vector_size){
    for (int i=0;i<vector_size;i++){
        std::cout<<vector[i].GetSize()<<' '<<vector[i].GetXCoordinate()<<' '<<vector[i].GetYCoordinate()<<", ";
    }
    std::cout<<"\n";
}