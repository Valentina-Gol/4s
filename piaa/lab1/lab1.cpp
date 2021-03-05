#include <iostream>
#include "Square.h"
#include "Handler.h"

#include <vector>


int main(){
    int result_size = 0;
    std::vector <Square> finish;//candidate of result suquence
    std::vector <Square> current;//current path

    int n;
    std::cin>>n;

    //TODO если чётные, то 4
    
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

        handler.PrintMatrix(matrix, n);
        std::cout<<"\nVector: ";
        handler.PrintVector(current, current_max_size);
        
        std::cout<<"Current coordinates: "<<current_x<<' '<< current_y<<'\n';
        std::cout<<"\n";
        int new_square_size = 0;

        std::cout<<"Checking RIGHT path"<<' '<<current_x<<' '<<current_y<<'\n';
        if (handler.CheckRightPath(matrix, n, current_x, current_y, 1)){

            std::cout<<"Yes\n";
            new_square_size = handler.FindNewSizeRightDown(matrix, n, current_x, current_y);
            handler.SetSquareOfOnes(matrix, n, current_x, current_y, new_square_size);
            current.push_back(Square(new_square_size, current_x, current_y));
            current_max_size+=1;
            
            if (handler.CheckRightPath(matrix, n, current_x, current_y, new_square_size)){
                current_y+=new_square_size;
                std::cout<<"Now find follow free cell(Right)"<<' '<<current_x<<' '<<current_y<<'\n';
                
                continue;
            }

            current_y+=new_square_size - 1;
            
            if (handler.CheckDownPath(matrix, n, current_x, current_y, new_square_size)){
                current_x+=new_square_size;
                std::cout<<"Now find follow free cell(Down)"<<' '<<current_x<<' '<<current_y<<'\n';
                
                continue;
            }

            current_x+=new_square_size - 1;
            
            if (handler.CheckLeftPath(matrix, n, current_x, current_y, new_square_size)){
                current_y-=new_square_size;
                std::cout<<"Now find follow free cell(Left)"<<' '<<current_x<<' '<<current_y<<'\n';
                
                continue;
            }

            current_y-=new_square_size-1;

            if (handler.CheckUpPath(matrix, n, current_x, current_y, new_square_size)){
                current_x-=new_square_size;
                std::cout<<"Now find follow free cell(Up)"<<' '<<current_x<<' '<<current_y<<'\n';
                
                continue;
            }
            current_x-=new_square_size - 1;
            // если никуда не смогли пойти
            if (handler.CheckAllMatrix(matrix, n, current_x, current_y)){
                continue;
            }
            else{
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
        std::cout<<"Checking DOWN path"<<' '<<current_x<<' '<<current_y<<'\n';
        if (handler.CheckDownPath(matrix, n, current_x, current_y, 1)){
            std::cout<<"Yes\n";
            new_square_size = handler.FindNewSizeDownLeft(matrix, n, current_x, current_y);
            //current_y-=new_square_size-1;
            handler.SetSquareOfOnes(matrix, n, current_x, current_y-new_square_size+1, new_square_size);
            current.push_back(Square(new_square_size, current_x, current_y));
            current_max_size+=1;

            //current_y+=new_square_size-1;

            if (handler.CheckDownPath(matrix, n, current_x, current_y, new_square_size)){
                current_x+=new_square_size;
                std::cout<<"Now find follow free cell(Down)"<<' '<<current_x<<' '<<current_y<<'\n';
                
                continue;
            }

            current_x+=new_square_size - 1;
            
            if (handler.CheckLeftPath(matrix, n, current_x, current_y, new_square_size)){
                current_y-=new_square_size;
                std::cout<<"Now find follow free cell(Left)"<<' '<<current_x<<' '<<current_y<<'\n';
                
                continue;
            }

            current_y-=new_square_size-1;

            if (handler.CheckUpPath(matrix, n, current_x, current_y, new_square_size)){
                current_x-=new_square_size;
                std::cout<<"Now find follow free cell(Up)"<<' '<<current_x<<' '<<current_y<<'\n';
                
                continue;
            }
            current_x-=new_square_size - 1;
            // если никуда не смогли пойти
            if (handler.CheckAllMatrix(matrix, n, current_x, current_y)){
                continue;
            }
            else{
                 if (result_size>current_max_size){
                    result_size = current_max_size;
                    finish = current;
                }
                handler.PopBackVector(matrix, n, current, current_max_size);
                if (handler.CheckAllMatrix(matrix, n, current_x, current_y)){}
                continue;
            }
        
        }   
        std::cout<<"Checking LEFT path"<<' '<<current_x<<' '<<current_y<<'\n';
        if (handler.CheckLeftPath(matrix, n, current_x, current_y, 1)){
            std::cout<<"Yes\n";
            
            new_square_size = handler.FindNewSizeLeftUp(matrix, n, current_x, current_y);
            //current_x-=new_square_size-1;
            //current_y-=new_square_size-1;
            handler.SetSquareOfOnes(matrix, n, current_x-new_square_size+1, current_y-new_square_size+1, new_square_size);
            current.push_back(Square(new_square_size, current_x, current_y));
            current_max_size+=1;

            if (handler.CheckLeftPath(matrix, n, current_x, current_y, new_square_size)){
                current_y-=new_square_size;
                std::cout<<"Now find follow free cell(Left)"<<' '<<current_x<<' '<<current_y<<'\n';
                
                continue;
            }

            current_y-=new_square_size-1;

            if (handler.CheckUpPath(matrix, n, current_x, current_y, new_square_size)){
                current_x-=new_square_size;
                std::cout<<"Now find follow free cell(Up)"<<' '<<current_x<<' '<<current_y<<'\n';
                
                continue;
            }
            current_x-=new_square_size - 1;
            // если никуда не смогли пойти
            if (handler.CheckAllMatrix(matrix, n, current_x, current_y)){
                continue;
            }
            else{
                 if (result_size>current_max_size){
                    result_size = current_max_size;
                    finish = current;
                }
                handler.PopBackVector(matrix, n, current, current_max_size);
                if (handler.CheckAllMatrix(matrix, n, current_x, current_y)){}
                continue;
            }
       
        }       
        std::cout<<"Checking UP path"<<' '<<current_x<<' '<<current_y<<'\n';
        if (handler.CheckUpPath(matrix, n, current_x, current_y, 1)){
            std::cout<<"Yes\n";
            new_square_size = handler.FindNewSizeUpRight(matrix, n, current_x, current_y);
            current_x-=new_square_size;
            handler.SetSquareOfOnes(matrix, n, current_x, current_y, new_square_size);
            current.push_back(Square(new_square_size, current_x, current_y));
            current_max_size+=1;

             if (handler.CheckUpPath(matrix, n, current_x, current_y, new_square_size)){
                current_x-=new_square_size;
                std::cout<<"Now find follow free cell(Up)"<<' '<<current_x<<' '<<current_y<<'\n';
                
                continue;
            }
            current_x-=new_square_size - 1;
            // если никуда не смогли пойти
            if (handler.CheckAllMatrix(matrix, n, current_x, current_y)){
                continue;
            }
            else{
                 if (result_size>current_max_size){
                    result_size = current_max_size;
                    finish = current;
                }
                handler.PopBackVector(matrix, n, current, current_max_size);
                if (handler.CheckAllMatrix(matrix, n, current_x, current_y)){}
                continue;
            }
      
        }

        std::cout<<"Checking else\n";
        
        if (matrix[current_x][current_y]==0){
            matrix[current_x][current_y]=1;
            current_max_size+=1;
            current.push_back(Square(1,current_x, current_y));
            continue;
        }else{
            if(handler.CheckAllMatrix(matrix, n, current_x, current_y)==0){
                if (result_size>current_max_size){
                    result_size = current_max_size;
                    finish = current;
                }
                handler.PopBackVector(matrix, n, current, current_max_size);
                if (handler.CheckAllMatrix(matrix, n, current_x, current_y)){}
                continue;

            }
            else{
                continue;
            }
            
        }




    }

    //TODO
    for (int i=0;i<result_size;i++){
        std::cout<<"RESULT "<<finish[i].GetSize()<<' '<<finish[i].GetXCoordinate()<<' '<<finish[i].GetYCoordinate()<<'\n';
    }

    for (int i=0; i<n; i++){
        delete [] matrix[i];
    }
    delete [] matrix;

    return 0;
}