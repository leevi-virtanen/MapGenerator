#include <iostream>
#include <vector>
#include <string>


const int cellsize = 3;

class coordinate {
public:
    int x;
    int y;
    coordinate(int coordx, int coordy) {
        x = coordx;
        y = coordy;
    }
};



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
        size = cellsize;
        array.reserve(size * size);
        for (int i = 0; i < size * size; i++) {
            array.push_back(0);
        }
    }
    //returns -1 if outside array size
    int get(coordinate coord) {
        if (coord.x > size || coord.y > size || coord.x < 0 || coord.y < 0) return -1;
        return array[size * coord.x + coord.y];
    }
    //returns false if outside array size
    bool set(coordinate coord, int input) {
        if (coord.x > size || coord.y > size || coord.x < 0 || coord.y < 0) return false;
        array[size * coord.x + coord.y] = input;
        return true;
    }

};



twoarray roomset(std::vector<int> row1, std::vector<int> row2, std::vector<int> row3) {
    twoarray temp{};

    for (int i = 0; i < row1.size(); i++) {
        temp.set(coordinate(0, i), row1[i]);
    }
    for (int i = 0; i < row2.size(); i++) {
        temp.set(coordinate(1, i), row2[i]);
    }
    for (int i = 0; i < row3.size(); i++) {
        temp.set(coordinate(2, i), row3[i]);
    }

    return temp;
}


void place(twoarray& room, twoarray& map, coordinate coord) {
    for (int x = 0; x < room.size; x++) {
        for (int y = 0; y < room.size; y++) {
            if (room.get(coordinate(x, y)) != 0) {
                map.set(coordinate(x + coord.x, y + coord.y), room.get(coordinate(x, y)));
            }
        }
    }

}

bool placeablecheck(twoarray room, twoarray map, coordinate coord) {

    int correctdoorcounter = 0;
    for (int x = 0; x < room.size; x++) {
        for (int y = 0; y < room.size; y++) {

            if (map.get(coordinate(x+coord.x, y+coord.y)) != 0 && room.get(coordinate(x,y)) != 0) {
                return false;
            }
            switch (map.get(coordinate(x + coord.x, y + coord.y))) {
            case 2:
                if (map.get(coordinate(x + coord.x + 1, y + coord.y)) == 4) {
                    correctdoorcounter++;
                }
                else return false;
            case 3:
                if (map.get(coordinate(x + coord.x, y + coord.y+1)) == 5) {
                    correctdoorcounter++;
                }
                else return false;
            case 4:
                if (map.get(coordinate(x + coord.x-1, y + coord.y)) == 2) {
                    correctdoorcounter++;
                }
                else return false;
            case 5:
                if (map.get(coordinate(x + coord.x, y + coord.y - 1)) == 3) {
                    correctdoorcounter++;
                }
                else return false;
            }
        }
    }
    if (correctdoorcounter > 0) {
        return true;
    }
    else return false;
}

void printtwoarray(twoarray room) {
    for (int x = 0; x < room.size; x++) {
        std::string print = "";
        for (int y = 0; y < room.size; y++) {
            print.append(std::to_string(room.get(coordinate(x, y))));
        }
        std::cout << print << std::endl;
    }
}

twoarray rotate(twoarray room) {
    twoarray temp = twoarray();
    for (int x = 0; x < room.size; x++) {
        for (int y = 0; y < room.size; y++) {
            temp.set(coordinate(y, x), room.get(coordinate(x,y)));
        }
    }
    twoarray temp2 = temp;
    for (int x = 0; x < room.size; x++) {
        for (int y = 0; y < room.size; y++) {
            temp.set(coordinate(x, y), temp2.get(coordinate(x, temp2.size - y - 1)));
        }
    }
    for (int x = 0; x < room.size; x++) {
        for (int y = 0; y < room.size; y++) {
            if (temp.get(coordinate(x, y)) > 1 && temp.get(coordinate(x, y)) < 5) {
                temp.set(coordinate(x, y), temp.get(coordinate(x, y)) + 1);
            }
            else if (temp.get(coordinate(x, y)) == 5) {
                temp.set(coordinate(x, y), 2);
            }
        }
    }
    return temp;

}

twoarray rotate(twoarray room, int times) {
    twoarray temp = room;
    for (int i = 0; i < times-1; i++) {
        temp = rotate(temp);
    }
    return temp;
}

void fullPlaceAlgorithm(twoarray& room, twoarray& map, coordinate coord) {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; y++) {
                coordinate newCoord = coordinate(coord.x + x - 1, coord.y + y - 1);
                twoarray currentRoom = rotate(room,z);
                if (placeablecheck(currentRoom, map, newCoord)) {
                    place(currentRoom, map, newCoord);
                }
            }
        }
    }
}


int main()
{
    twoarray map(20);
    std::vector<twoarray> rooms;
    for (int i = 0; i < 6; i++) {
        rooms.push_back(twoarray());
    }

    rooms[0] = roomset({ 1,1,1 }, { 2,0,0 }, { 0,0,0 });
    rooms[1] = roomset({ 1,1,1 }, { 2,1,1 }, { 0,0,0 });
    rooms[2] = roomset({ 1,1,0 }, { 2,1,0 }, { 0,0,0 });
    rooms[3] = roomset({ 1,1,3 }, { 0,0,0 }, { 0,0,0 });
    rooms[4] = roomset({ 1,1,1 }, { 1,1,1 }, { 1,1,3 });
    rooms[5] = roomset({ 5,1,1 }, { 1,1,3 }, { 0,0,0 });

    coordinate pointer = coordinate(0, 0);
    while (pointer.x < map.size && pointer.y < map.size) {

    }

}

