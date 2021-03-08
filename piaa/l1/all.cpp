#include <vector>
#include <algorithm>
#include <iostream>

class Square{

private:
    int size=0;
    int x_coordinate=0;//top down
    int y_coordinate=0;//from left to right
public:
    Square()=default;
    Square(int s, int x, int y): size(s), x_coordinate(x), y_coordinate(y){}
    ~Square() = default;
    int GetXCoordinate();
    int GetYCoordinate();
    int GetSize();
};

class Handler{

public:  
    bool CheckAllMatrix(int** matrix, int matrix_size, int& x_coordinate, int& y_coordinate, std::vector<Square>& vector, int vector_size);
    void PrintMatrix(int** matrix, int marix_size);
    void PrintVector(std::vector<Square> vector, int vector_size);
    void PopBackVector(int** matrix, int matrix_size, std::vector<Square>& vector, int& vector_size, int& flag);
    int FindNewSizeRightDown(int** matrix, int matrix_size, int x_coordinate, int y_coordinate);
    void SetSquareOfOnes(int** matrix, int matrix_size, int x_coordinate, int y_coordinate, int square_size);
    void SetSquareOfZeros(int** matrix, int matrix_size, int x_coordinate, int y_coordinate, int square_size);

};

int Square::GetXCoordinate(){
    return this->x_coordinate;
}

int Square::GetYCoordinate(){
    return this->y_coordinate;
}

int Square::GetSize(){
    return this->size;
}

int Handler::FindNewSizeRightDown(int** matrix, int matrix_size, int x_coordinate, int y_coordinate){
    int right_size = 1, down_size = 1;
    int i = x_coordinate, j = y_coordinate;

    int max_size = matrix_size-1;
    
    while (right_size <= max_size && j+right_size<matrix_size && matrix[i][j+right_size]!=1 ){
        right_size++;
    } 
    while (down_size <= max_size && i+down_size<matrix_size && matrix[i+down_size][j]!=1 ){
        down_size++;
    }
    int size=std::min(right_size, down_size);
    std::cout<<"Find new square at coordinates: ("<<x_coordinate<<", "<<y_coordinate<<")... Find a square size: "<<size<<"\n";


    return size;
}

void Handler::SetSquareOfOnes(int** matrix, int matrix_size, int x_coordinate, int y_coordinate, int square_size){
    for (int i = x_coordinate; i < x_coordinate + square_size; i++){
        for (int j = y_coordinate; j < y_coordinate + square_size;j++){
            matrix[i][j]=1;
        }
    }
    
}

void Handler::SetSquareOfZeros(int** matrix, int matrix_size, int x_coordinate, int y_coordinate, int square_size){
    for (int i = x_coordinate; i < x_coordinate + square_size; i++){
        for (int j = y_coordinate; j < y_coordinate + square_size;j++){
            matrix[i][j]=0;
        }
    }
    
}

bool Handler::CheckAllMatrix(int** matrix, int matrix_size, int& x_coordinate, int& y_coordinate, std::vector<Square>& vector, int vector_size){
    std::cout<<"Cheking free space in matrix...\n";
    for (int i=0;i<matrix_size;i++){
        for (int j=0;j<matrix_size;j++){
            if (matrix[i][j]==0){
                x_coordinate = i;
                y_coordinate = j;
                std::cout<<"Find free space at coordinates: ("<<x_coordinate<<", "<<y_coordinate<<")\n";
                return true;
            }
        }
    }
    std::cout<<"Free space didn't find\n";
    return false;
}

void Handler::PopBackVector(int** matrix, int matrix_size, std::vector<Square>& vector, int& vector_size, int& flag){
   
   while (1){
       if (vector_size<=3){
           flag=1;
           std::cout<<"All optimal candidate for filling square was find, stoped cheking\n";
           break;
        } else{
            Square square = vector[vector_size-1];
            if (vector[vector_size-1].GetSize()>=2){
                
                vector.pop_back();
                vector_size-=1;
                this->SetSquareOfZeros(matrix, matrix_size, square.GetXCoordinate(), square.GetYCoordinate(), square.GetSize());
                this->SetSquareOfOnes(matrix, matrix_size, square.GetXCoordinate(), square.GetYCoordinate(), square.GetSize()-1);
                vector.push_back(Square(square.GetSize()-1, square.GetXCoordinate(), square.GetYCoordinate()));
                vector_size+=1;
                break;
            }
            else{
                vector.pop_back();
                vector_size-=1;
                this->SetSquareOfZeros(matrix, matrix_size, square.GetXCoordinate(), square.GetYCoordinate(), square.GetSize());
                continue;
            }
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

int main(){
    
    std::vector <Square> finish;//candidate of result suquence
    std::vector <Square> current;//current path

    int n;
    std::cin>>n;

    int result_size = n*n;

    if (n==2){
        std::cout<<'4'<<"\n";
        std::cout<<"1 1 1\n1 2 1\n2 1 1\n2 2 1\n";
        return 0;
    }

    if (n%2==0){
        result_size = 4;
        finish.push_back(Square(n/2, 0, 0));
        finish.push_back(Square(n/2, 0, n/2));
        finish.push_back(Square(n/2, n/2, 0));
        finish.push_back(Square(n/2, n/2, n/2));
    }
    else{

        int** matrix = new int*[n];

        for (int i=0; i<n; i++){
            matrix[i]= new int[n];
        }

        for (int i=0;i<n;i++){
            for (int j=0;j<n;j++){
                matrix[i][j]=0;
            }
        }

        Handler handler;
        if (n==15){
            current.push_back(Square(n*2/3, 0, 0));
            current.push_back(Square(n/3, 0, n*2/3));
            current.push_back(Square(n/3, n*2/3,0));

            handler.SetSquareOfOnes(matrix, n, 0, 0, n*2/3);
            handler.SetSquareOfOnes(matrix, n, 0, n*2/3, n/3);
            handler.SetSquareOfOnes(matrix, n, n*2/3, 0, n/3);
        }
        else{
            current.push_back(Square(n/2 + 1, 0, 0));
            current.push_back(Square(n/2, 0, n/2+1));
            current.push_back(Square(n/2, n/2+1,0));

            handler.SetSquareOfOnes(matrix, n, 0, 0, n/2+1);
            handler.SetSquareOfOnes(matrix, n, 0, n/2+1, n/2);
            handler.SetSquareOfOnes(matrix, n, n/2+1, 0, n/2);
        }

        int current_x = 0;
        int current_y = 0;
        int current_max_size = 3;
        int new_square_size = 0;
        int flag=0;


        while (!current.empty() && flag!=1){

            std::cout<<"\nCurrent path: ";
            handler.PrintVector(current, current_max_size);
            
            std::cout<<"\nCurrent matrix:\n";
            handler.PrintMatrix(matrix, n);  

            if (n>11 && current_max_size>=n){
                handler.PopBackVector(matrix, n, current, current_max_size, flag);
                continue;
            }

            if (current_max_size>=result_size){
                std::cout<<"Current path size is longer then finish path size, stop cheking further\n";
                handler.PopBackVector(matrix, n, current, current_max_size, flag);
                continue;
            }
            
            if (handler.CheckAllMatrix(matrix, n, current_x, current_y, current, current_max_size)){
                int new_size = handler.FindNewSizeRightDown(matrix, n, current_x, current_y);
                current.push_back(Square(new_size, current_x, current_y));
                current_max_size+=1;
                handler.SetSquareOfOnes(matrix, n, current_x, current_y, new_size);
            }
            else{
                finish = current;
                result_size = current_max_size;
                handler.PopBackVector(matrix, n, current, current_max_size, flag);
            }
        }
        for (int i=0; i<n; i++){
            delete [] matrix[i];
        }
        delete [] matrix;
    }

    
    std::cout<<"\nMinimal result size: "<< result_size<<"\nCoordinates & Sizes of result squares: \n";
    for (int i=0;i<result_size;i++){
        std::cout<<finish[i].GetXCoordinate()+1<<' '<<finish[i].GetYCoordinate()+1<<' '<<finish[i].GetSize()<<'\n';
    }
    return 0;
}