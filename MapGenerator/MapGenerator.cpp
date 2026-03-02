#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

//What times what size the rooms will be
const int cellsize = 3;



class coordinate {
public:
    __int16 x;
    __int16 y;
    coordinate(__int16 coordx, __int16 coordy) : x(coordx), y(coordy) {}
};

class PlacedRoom {
public:
    unsigned __int16 roomId;
    coordinate coord;
    unsigned __int8 rotation;


    PlacedRoom(unsigned __int16 id, coordinate c, unsigned __int16 rot) : roomId(id), coord(c.x, c.y), rotation(rot) {}
};


class twoarray {
private:
    std::vector<unsigned __int8> array;

public:
    unsigned __int8 size;
    twoarray(unsigned __int8 height) {
        size = height;
        array.reserve(size * size);
        for (unsigned __int16 i = 0; i < size * size; i++) {
            array.push_back(0);
        }
    }
    twoarray() {
        size = cellsize;
        array.reserve(size * size);
        for (unsigned __int8 i = 0; i < size * size; i++) {
            array.push_back(0);
        }
    }
    //returns -1 if outside array size
    unsigned __int8 get(coordinate coord) {
        if (coord.x >= size || coord.y >= size || coord.x < 0 || coord.y < 0) return -1;
        return array[size * coord.x + coord.y];
    }
    //returns false if outside array size
    bool set(coordinate coord, __int8 input) {
        if (coord.x >= size || coord.y >= size || coord.x < 0 || coord.y < 0) return false;
        array[size * coord.x + coord.y] = input;
        return true;
    }

};


//rooms are defined as matrices with numbers from 1-5, that always start in the 0,0 coordinate of the room matrix. 1 are walls to fill what doors don't and 2-5 are doors. 2 = right, 3 = down, 4 = left, 5 = up. One cell can only hold one door.

//(1,1),(3,1) be defined as (wall on the top and left, wall on the top and right), (door on the left wall on the bottom, wall on the right and bottom)


twoarray roomset(std::vector<unsigned __int8> row1, std::vector<unsigned __int8> row2, std::vector<unsigned __int8> row3) {
    twoarray temp{};

    for (unsigned __int8 i = 0; i < row1.size(); i++) {
        temp.set(coordinate(0, i), row1[i]);
    }
    for (unsigned __int8 i = 0; i < row2.size(); i++) {
        temp.set(coordinate(1, i), row2[i]);
    }
    for (unsigned __int8 i = 0; i < row3.size(); i++) {
        temp.set(coordinate(2, i), row3[i]);
    }

    return temp;
}


void place(twoarray& room, twoarray& map, coordinate coord) {
    for (unsigned __int8 x = 0; x < room.size; x++) {
        for (unsigned __int8 y = 0; y < room.size; y++) {
            if (room.get(coordinate(x, y)) != 0) {
                map.set(coordinate(x + coord.x, y + coord.y), room.get(coordinate(x, y)));
            }
        }
    }

}

bool placeablecheck(twoarray& room, twoarray& map, coordinate& coord) {
    unsigned __int8 correctdoorcounter = 0;
    unsigned __int8 falsedoorcounter = 0;

    for (unsigned __int8 x = 0; x < room.size; x++) {
        for (unsigned __int8 y = 0; y < room.size; y++) {
            unsigned __int8 mapX = x + coord.x;
            unsigned __int8 mapY = y + coord.y;

            unsigned __int8 roomVal = room.get(coordinate(x, y));
            unsigned __int8 mapVal = map.get(coordinate(mapX, mapY));

            if (mapVal != 0 && roomVal != 0) {
                return false;
            }

            switch (roomVal) {
            case 2:
                if (map.get(coordinate(mapX, mapY + 1)) == 4) {
                    correctdoorcounter++;
                }
                else {
                    falsedoorcounter++;
                }
                break;
            case 3:
                if (map.get(coordinate(mapX + 1, mapY)) == 5) {
                    correctdoorcounter++;
                }
                else {
                    falsedoorcounter++;
                }
                break;
            case 4:
                if (map.get(coordinate(mapX, mapY - 1)) == 2) {
                    correctdoorcounter++;
                }
                else {
                    falsedoorcounter++;
                }
                break;
            case 5:
                if (map.get(coordinate(mapX - 1, mapY)) == 3) {
                    correctdoorcounter++;
                }
                else {
                    falsedoorcounter++;
                }
                break;
            }

        }
    }

    if (correctdoorcounter > 0) {
        return true;
    }
    else return false;
}

void printtwoarray(twoarray& room) {
    for (unsigned __int8 x = 0; x < room.size; x++) {
        std::string print = "";
        for (unsigned __int8 y = 0; y < room.size; y++) {
            print.append(std::to_string(room.get(coordinate(x, y))));
        }
        std::cout << print << std::endl;
    }
}

twoarray rotate(twoarray room) {
    twoarray temp = twoarray();
    for (unsigned __int8 x = 0; x < room.size; x++) {
        for (unsigned __int8 y = 0; y < room.size; y++) {
            temp.set(coordinate(y, x), room.get(coordinate(x, y)));
        }
    }
    twoarray temp2 = temp;
    for (unsigned __int8 x = 0; x < room.size; x++) {
        for (unsigned __int8 y = 0; y < room.size; y++) {
            temp.set(coordinate(x, y), temp2.get(coordinate(x, temp2.size - y - 1)));
        }
    }
    for (unsigned __int8 x = 0; x < room.size; x++) {
        for (unsigned __int8 y = 0; y < room.size; y++) {
            int val = temp.get(coordinate(x, y));

            if (val == 2) {
                temp.set(coordinate(x, y), 3);
            }
            else if (val == 3) {
                temp.set(coordinate(x, y), 4);
            }
            else if (val == 4) {
                temp.set(coordinate(x, y), 5);
            }
            else if (val == 5) {
                temp.set(coordinate(x, y), 2);
            }
        }
    }
    return temp;
}

twoarray rotate(twoarray room, unsigned __int8 times) {
    twoarray temp = room;
    for (unsigned __int8 i = 0; i < times; i++) {
        temp = rotate(temp);
    }
    return temp;
}

bool fullPlaceAlgorithm(int roomId, twoarray& room, twoarray& map, coordinate coord, std::vector<PlacedRoom>& trackingList) {
    for (unsigned __int8 x = 0; x < 3; x++) {
        for (unsigned __int8 y = 0; y < 3; y++) {
            for (unsigned __int8 r = 0; r < 4; r++) {
                coordinate newCoord = coordinate(coord.x + x - 1, coord.y + y - 1);
                twoarray currentRoom = rotate(room, r);

                if (placeablecheck(currentRoom, map, newCoord)) {
                    place(currentRoom, map, newCoord);

                    trackingList.push_back(PlacedRoom(roomId, newCoord, r));

                    return true;
                }
            }
        }
    }
    return false;
}


int main()
{


    twoarray map(30);
    std::vector<twoarray> rooms;
    for (int i = 0; i < 6; i++) {
        rooms.push_back(twoarray());
    }



    //define rooms here
    rooms[0] = roomset({ 5,5,1 }, { 3,2,0 }, { 0,0,0 });
    rooms[1] = roomset({ 4,1,1 }, { 2,1,1 }, { 0,0,0 });
    rooms[2] = roomset({ 5,1,0 }, { 2,1,0 }, { 0,0,0 });
    rooms[3] = roomset({ 1,1,3 }, { 0,0,0 }, { 0,0,0 });
    rooms[4] = roomset({ 5,1,1 }, { 1,1,1 }, { 1,1,3 });
    rooms[5] = roomset({ 5,1,1 }, { 1,1,3 }, { 0,0,0 });

    std::vector<PlacedRoom> placedRoomsList;

    //set first room here
    place(rooms[0], map, coordinate(15, 15));
    placedRoomsList.push_back(PlacedRoom(0, coordinate(15, 15), 0));

    srand(time(NULL));
    std::random_device rd;
    std::mt19937 g(rd());

    std::vector<coordinate> allCoords;
    for (unsigned __int16 x = 0; x < map.size; x++) {
        for (unsigned __int16 y = 0; y < map.size; y++) {
            allCoords.push_back(coordinate(x, y));
        }
    }

    bool mapChanged = true;
    while (mapChanged) {
        mapChanged = false;

        std::shuffle(allCoords.begin(), allCoords.end(), g);

        for (coordinate currentCoord : allCoords) {
            unsigned __int16 startRandom = rand() % rooms.size();
            for (unsigned __int16 i = 0; i < rooms.size(); i++) {
                unsigned __int16 r = (startRandom + i) % rooms.size();

                if (fullPlaceAlgorithm(r, rooms[r], map, currentCoord, placedRoomsList)) {
                    mapChanged = true;
                    break;
                }
            }
        }
    }


    printtwoarray(map);

    std::cout << "\n--- Generation Complete ---\n";
    std::cout << "Total Rooms Placed: " << placedRoomsList.size() << "\n\n";
    for (unsigned __int16 i = 0; i < placedRoomsList.size(); i++) {
        std::cout << "Room [" << placedRoomsList[i].roomId << "] "
            << "at (" << placedRoomsList[i].coord.x << ", " << placedRoomsList[i].coord.y << ") "
            << "Rotated " << placedRoomsList[i].rotation * 90 << " degrees.\n";
    }


}