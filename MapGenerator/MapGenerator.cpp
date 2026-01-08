
#include <iostream>
#include <vector>

class twoarray {
private:
    std::vector<int> array;

public:
    int size;
    twoarray(int height) {
        size = height;
        array.reserve(size * size);
        for (int i = 0; i < size * size; i++) {
            array.push_back(0);
        }
    }
    twoarray() {
        size = 3;
        array.reserve(size * size);
        for (int i = 0; i < size * size; i++) {
            array.push_back(0);
        }
    }
    int get(int x, int y) {
        return array[size * x + y];
    }
    void set(int x, int y, int input) {
        array[size * x + y] = input;
    }

};

twoarray roomset(std::vector<int> row1, std::vector<int> row2, std::vector<int> row3) {
    twoarray temp = twoarray();

    for (int i = 0; i < row1.size(); i++) {
        
    }

    return temp;
}


int main()
{
    twoarray map(5);
    std::vector<twoarray> rooms;
    for (int i = 0; i < 6; i++) {
        rooms.push_back(twoarray());
    }
    

}

