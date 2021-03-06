#include <iostream>
#include "Square.h"
#include "Handler.h"

#include <vector>


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
        int new_square_size = 0;
        


        while (!current.empty() && current[0].GetSize()>=2 && current[0].GetSize()<n){

            //TODO
            /*if (current[0].GetSize()==2){
                if (!handler.CkeckSizeInVector(current, current_max_size) ){
                    int cur_x=current_x;
                    int cur_y=current_y;
                    if (!handler.CheckAllMatrix(matrix, n, current_x, current_y)){
                        handler.PrintVector(current, current_max_size);
                        std::cout<<"BREAK"<<"\n";
                        break;
                    }
                    else{
                        current_x=cur_x;
                        current_y=cur_y;
                    }
                }
            }*/

            std::cout<<"\nVector: ";
            handler.PrintVector(current, current_max_size);
            /*
            std::cout<<"Matrix:\n";
            std::cout<<"Current coordinates: "<<current_x<<' '<< current_y<<'\n';
            handler.PrintMatrix(matrix, n);
`           */
            
            //std::cout<<" max size "<<result_size<<"\n";

            if (current_max_size>=result_size){
                handler.PopBackVector(matrix, n, current, current_max_size);
                if (handler.CheckAllMatrix(matrix, n, current_x, current_y)){}
            }
            
            //if (matrix[current_x][current_y]==1){
            //    if (handler.CheckAllMatrix(matrix, n, current_x, current_y)){}
            //}

            //std::cout<<"Current coordinates: "<<current_x<<' '<< current_y<<'\n';
            //std::cout<<"\n";
            

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