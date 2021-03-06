#ifndef SQUARE
#define SQUARE

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

#endif