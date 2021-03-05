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
    bool CheckAllMatrix(int** matrix, int matrix_size, int& x_coordinate, int& y_coordinate);
    void PrintMatrix(int** matrix, int marix_size);
    void PrintVector(std::vector<Square> vector, int vector_size);
    void PopBackVector(int** matrix, int matrix_size, std::vector<Square>& vector, int& vector_size);
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

    return std::min(right_size, down_size);
}

int Handler::FindNewSizeDownLeft(int** matrix, int matrix_size, int x_coordinate, int y_coordinate){
    int left_size = 1, down_size = 1;
    int i = x_coordinate, j = y_coordinate;
    int max_size = matrix_size-1;

    while (left_size <= max_size && j-left_size>=0 && matrix[i][j-left_size]!=1){
        left_size++;
    } 
    while (down_size <= max_size && i+down_size<matrix_size && matrix[i+down_size][j]!=1){
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

    while (right_size <= max_size && j+right_size<matrix_size && matrix[i][j+right_size]!=1){
        right_size++;
    } 
    while (up_size <= max_size && i-up_size>=0 && matrix[i-up_size][j]!=1 ){
        up_size++;
    }
    //std::cout<<"Right size: "<<right_size<<" Up size: "<<up_size<<"\n";
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
    //std::cout<<"Set zero at "<<x_coordinate<<' '<<y_coordinate<<" Size: "<<square_size<<"\n";
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
        //std::cout<<"\nDELETE Vector: ";
        //this->PrintVector(vector, vector_size);

        square = vector[vector_size-1];
        vector.pop_back();
        vector_size-=1;
        this->SetSquareOfZeros(matrix, matrix_size, square.GetXCoordinate(), square.GetYCoordinate(), square.GetSize());
        if (square.GetSize()>2){
            this->SetSquareOfOnes(matrix, matrix_size, square.GetXCoordinate(), square.GetYCoordinate(), square.GetSize()-1);
            vector.push_back(Square(square.GetSize()-1, square.GetXCoordinate(), square.GetYCoordinate()));
            vector_size+=1;
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

int main(){
    
    std::vector <Square> finish;//candidate of result suquence
    std::vector <Square> current;//current path

    int n;
    std::cin>>n;

    int result_size = n*n;

    if (n%4==0){
        result_size = 4;
        finish.push_back(Square(n/2, 0, 0));
        finish.push_back(Square(n/2, 0, n/2));
        finish.push_back(Square(n/2, n/2, 0));
        finish.push_back(Square(n/2, n/2, n/2));
    }
    else{

    
        current.push_back(Square(n-1, 0, 0));
        

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
        handler.SetSquareOfOnes(matrix, n, 0,0,n-1);

        int current_x = 0;
        int current_y = n-1;
        int current_max_size = 1;
        
        


        while (!current.empty() && current[0].GetSize()>=2){
            //if (current_max_size)

            //std::cout<<"\nVector: ";
            //handler.PrintVector(current, current_max_size);
            //std::cout<<"Matrix:\n";

            //handler.PrintMatrix(matrix, n);
            
            
            //std::cout<<"Current coordinates: "<<current_x<<' '<< current_y<<'\n';
            //std::cout<<"\n";
            int new_square_size = 0;

            //std::cout<<"Checking RIGHT path"<<' '<<current_x<<' '<<current_y<<'\n';
            if (handler.CheckRightPath(matrix, n, current_x, current_y, 1)){

            // std::cout<<"Yes\n";
                new_square_size = handler.FindNewSizeRightDown(matrix, n, current_x, current_y);
                handler.SetSquareOfOnes(matrix, n, current_x, current_y, new_square_size);
                current.push_back(Square(new_square_size, current_x, current_y));
                current_max_size+=1;
             
                
                if (handler.CheckRightPath(matrix, n, current_x, current_y, new_square_size)){
                    current_y+=new_square_size;
                    //std::cout<<"Now find follow free cell(Right)"<<' '<<current_x<<' '<<current_y<<'\n';
                    
                    continue;
                }

                current_y+=new_square_size - 1;
                
                if (handler.CheckDownPath(matrix, n, current_x, current_y, new_square_size)){
                    current_x+=new_square_size;
                    //std::cout<<"Now find follow free cell(Down)"<<' '<<current_x<<' '<<current_y<<'\n';
                    
                    continue;
                }

                current_x+=new_square_size - 1;
                
                if (handler.CheckLeftPath(matrix, n, current_x, current_y, new_square_size)){
                    current_y-=new_square_size;
                    //std::cout<<"Now find follow free cell(Left)"<<' '<<current_x<<' '<<current_y<<'\n';
                    
                    
                    continue;
                }

                current_y-=new_square_size-1;

                if (handler.CheckUpPath(matrix, n, current_x, current_y, new_square_size)){
                    current_x-=new_square_size;
                    //std::cout<<"Now find follow free cell(Up)"<<' '<<current_x<<' '<<current_y<<'\n';
                    
                    continue;
                }
                current_x-=new_square_size - 1;
                //current_y-=
                // если никуда не смогли пойти
                if (handler.CheckAllMatrix(matrix, n, current_x, current_y)){
                    continue;
                }
                else{
                    //std::cout<<"Current max size(Right): "<<current_max_size<<"\n";
                    if (result_size>current_max_size){
                        result_size = current_max_size;
                        finish = current;
                    }
                    handler.PopBackVector(matrix, n, current, current_max_size);
                    if (handler.CheckAllMatrix(matrix, n, current_x, current_y)){}
                    //
                    continue;
                }

            }   
            //std::cout<<"Checking DOWN path"<<' '<<current_x<<' '<<current_y<<'\n';
            if (handler.CheckDownPath(matrix, n, current_x, current_y, 1)){
                //std::cout<<"Yes\n";
                new_square_size = handler.FindNewSizeDownLeft(matrix, n, current_x, current_y);
                //current_y-=new_square_size-1;
                handler.SetSquareOfOnes(matrix, n, current_x, current_y-new_square_size+1, new_square_size);
                current.push_back(Square(new_square_size, current_x, current_y-new_square_size+1));
                current_max_size+=1;

                //current_y+=new_square_size-1;

                if (handler.CheckDownPath(matrix, n, current_x, current_y, new_square_size)){
                    current_x+=new_square_size;
                    //std::cout<<"Now find follow free cell(Down)"<<' '<<current_x<<' '<<current_y<<'\n';
                    
                    continue;
                }

                current_x+=new_square_size - 1;
                
                if (handler.CheckLeftPath(matrix, n, current_x, current_y, new_square_size)){
                    current_y-=new_square_size;
                    //std::cout<<"Now find follow free cell(Left)"<<' '<<current_x<<' '<<current_y<<'\n';
                    
                    continue;
                }

                current_y-=new_square_size-1;

                if (handler.CheckUpPath(matrix, n, current_x, current_y, new_square_size)){
                    current_x-=new_square_size;
                // std::cout<<"Now find follow free cell(Up)"<<' '<<current_x<<' '<<current_y<<'\n';
                    
                    continue;
                }
                current_x-=new_square_size - 1;
                current_y+=new_square_size-1;
                // если никуда не смогли пойти
                if (handler.CheckAllMatrix(matrix, n, current_x, current_y)){
                    continue;
                }
                else{
                    //std::cout<<"Current max size(Down): "<<current_max_size<<"\n";
                    if (result_size>current_max_size){
                        result_size = current_max_size;
                        finish = current;
                    }
                    handler.PopBackVector(matrix, n, current, current_max_size);
                    if (handler.CheckAllMatrix(matrix, n, current_x, current_y)){}
                    continue;
                }
            
            }   
            //std::cout<<"Checking LEFT path"<<' '<<current_x<<' '<<current_y<<'\n';
            if (handler.CheckLeftPath(matrix, n, current_x, current_y, 1)){
                //std::cout<<"Yes\n";
                
                new_square_size = handler.FindNewSizeLeftUp(matrix, n, current_x, current_y);
                //current_x-=new_square_size-1;
                //current_y-=new_square_size-1;
                handler.SetSquareOfOnes(matrix, n, current_x-new_square_size+1, current_y-new_square_size+1, new_square_size);
                current.push_back(Square(new_square_size, current_x-new_square_size+1, current_y-new_square_size+1));
                current_max_size+=1;

                if (handler.CheckLeftPath(matrix, n, current_x, current_y, new_square_size)){
                    current_y-=new_square_size;
                    //std::cout<<"Now find follow free cell(Left)"<<' '<<current_x<<' '<<current_y<<'\n';
                    
                    continue;
                }

                current_y-=new_square_size-1;

                if (handler.CheckUpPath(matrix, n, current_x, current_y, new_square_size)){
                    current_x-=new_square_size;
                    //std::cout<<"Now find follow free cell(Up)"<<' '<<current_x<<' '<<current_y<<'\n';
                    
                    continue;
                }
                //current_x-=new_square_size - 1;
                current_y+=new_square_size-1;

                
                // если никуда не смогли пойти
                if (handler.CheckAllMatrix(matrix, n, current_x, current_y)){
                    continue;
                }
                else{
                    //std::cout<<"Current max size(Left): "<<current_max_size<<"\n";
                    if (result_size>current_max_size){
                        result_size = current_max_size;
                        finish = current;
                    }
                    handler.PopBackVector(matrix, n, current, current_max_size);
                    if (handler.CheckAllMatrix(matrix, n, current_x, current_y)){}
                    continue;
                }
        
            }       
            //std::cout<<"Checking UP path"<<' '<<current_x<<' '<<current_y<<'\n';
            if (handler.CheckUpPath(matrix, n, current_x, current_y, 1)){
                //std::cout<<"Yes\n";
                new_square_size = handler.FindNewSizeUpRight(matrix, n, current_x, current_y);
                
                handler.SetSquareOfOnes(matrix, n, current_x-new_square_size+1, current_y, new_square_size);
                current.push_back(Square(new_square_size, current_x-new_square_size+1, current_y));
                current_max_size+=1;
                //current_x-=new_square_size-1;

                if (handler.CheckUpPath(matrix, n, current_x, current_y, new_square_size)){
                    current_x-=new_square_size;
                    //std::cout<<"Now find follow free cell(Up)"<<' '<<current_x<<' '<<current_y<<'\n';
                    
                    continue;
                }
                //current_x-=new_square_size - 1;
                // если никуда не смогли пойти
                if (handler.CheckAllMatrix(matrix, n, current_x, current_y)){
                    continue;
                }
                else{
                    //std::cout<<"Current max size(Up): "<<current_max_size<<"\n";
                    if (result_size>current_max_size){
                        result_size = current_max_size;
                        finish = current;
                    }
                    handler.PopBackVector(matrix, n, current, current_max_size);
                    if (handler.CheckAllMatrix(matrix, n, current_x, current_y)){}
                    continue;
                }
        
            }

            //std::cout<<"Checking else\n";
            

                if(handler.CheckAllMatrix(matrix, n, current_x, current_y)==0){
                    //std::cout<<"Current max size(Else): "<<current_max_size<<"\n";
                    if (result_size>current_max_size){
                        result_size = current_max_size;
                        finish = current;
                    }
                    handler.PopBackVector(matrix, n, current, current_max_size);
                    if (handler.CheckAllMatrix(matrix, n, current_x, current_y)){}
                    continue;

                }
                else{
                    //if (matrix[current_x][current_y]==0){
                        matrix[current_x][current_y]=1;
                        current_max_size+=1;
                        current.push_back(Square(1,current_x, current_y));
                        continue;
                    //}
                }

        }


        for (int i=0; i<n; i++){
            delete [] matrix[i];
        }
        delete [] matrix;

    }
        //std::cout<<"Result size: "<<result_size<<"\n";

    //TODO
    std::cout<<result_size<<"\n";
    for (int i=0;i<result_size;i++){
        std::cout<<finish[i].GetXCoordinate()+1<<' '<<finish[i].GetYCoordinate()+1<<' '<<finish[i].GetSize()<<'\n';
    }

    

    return 0;
}
