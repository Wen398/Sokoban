#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>

using namespace std;

class oop {
private:
    vector<vector<char>> map;
    vector<vector<int>> position;
public:
    oop(const string& filename);
    bool isOpen();
    void createMap(const string& filename);
    void addInitialPosition(char c, int x, int y);
    void displayMap() const;
    void movePlayer(char direction);
    bool isValidMove(int x, int y, int dx, int dy) const;
    bool isStuck();
    bool isGameOver();
};

oop::oop(const string& filename) {
    createMap(filename);
}

bool oop::isOpen() {
    if(map.size() == 0)
        return false;
    return true;
}

void oop::createMap(const string& filename) {
    map.clear();
    position.clear();
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cerr << "can't open the file" << endl;
        system("pause");
        return;
    }

    string line;
    position.resize(3);
    int x = 0;
    bool flag = true;
    while (getline(ifs, line)) {
        if(flag) {
            flag = false;
            continue;
        }
        vector<char> row;
        for (char c : line) {
            if(c == '0' || c == '1' || c == '2')
                addInitialPosition(c, row.size(), x);
            row.push_back(c);
        }
        x++;
        map.push_back(row);
    }

    ifs.close();
}

void oop::addInitialPosition(char c, int x, int y) {
    int num = c - '0';
    for(int i = 0; i < 2; i ++) {
        position[num].push_back(y);
        position[num].push_back(x);
    }
}

bool oop::isValidMove(int x, int y, int dx, int dy) const {
    if(map[x][y] != '/') {
        if(map[x][y] == '1')
            if(map[x + dx][y + dy] == '-' || map[x + dx][y + dy] == '2')
                return true;
        else
            return false;
        return true;
    }
    return false;
}


void oop::movePlayer(char direction) {

    int playerX = position[0][0];
    int playerY = position[0][1];

    int dx = 0, dy = 0;
    bool over = false;

    switch (direction) {
        case 'w':
            dx = -1;
            over = true;
            break;
        case 's':
            dx = 1;
            over = true;
            break;
        case 'a':
            dy = -1;
            over = true;
            break;
        case 'd':
            dy = 1;
            over = true;
            break;
        default:
            return;
    }

    int newX = playerX + dx;
    int newY = playerY + dy;

    if(over && isValidMove(newX, newY, dx, dy)) {

        for(int i = 0; i < position[2].size(); i+=2) {
            if(position[2][i] == playerX && position[2][i+1] == playerY) {
                map[playerX][playerY] = '2';
                break;
            }
            map[playerX][playerY] = '-';
        }
        if(map[newX][newY] == '1') {
            for(int i = 0; i < position[1].size(); i+=2) {
                if(position[1][i] == newX && position[1][i+1] == newY) {
                    position[1][i] = newX + dx;
                    position[1][i+1] = newY + dy;
                    map[newX + dx][newY + dy] = '1';
                    break;
                }
            }
        }

        map[newX][newY] = '0';
        position[0][0] = newX;
        position[0][1] = newY;

    }
    return;
}



void oop::displayMap() const {
    system("cls");
    for (const auto& row : map) {
        for (char c : row) cout << c;
        cout << std::endl;
    }
    cout << "press [w-a-s-d] to control the character, [r] to reset, [esc] to exit." << endl;
}

bool oop::isStuck() {
    for(int i = 0; i < position[1].size(); i+=2) {
        int x = position[1][i];
        int y = position[1][i+1];
        if((map[x+1][y] == '/' || map[x-1][y] == '/') && (map[x][y+1] == '/' || map[x][y-1] == '/'))
            return true;
    }
    return false;
}

bool oop::isGameOver(){

    for(int i = 0; i < position[1].size(); i+=2) {
        if(position[0][1] == position[2][i] && position[0][1] == position[2][i+1])
            return false;
    }

    for(auto line : map) {
        for(auto ch : line) {
            if(ch == '2')
                return false;
        }
    }
    return true;
}

int main()
{
    while(true) {
        cout << "Please enter the name of the map." << endl;
        string mapName;
        cin >> mapName;
        oop game(mapName);
        system("cls");
        if(!game.isOpen())
            continue;
        game.displayMap();

        while (true) {
            char input = getch();
            if(input == 'r')
                game.createMap(mapName);
            if(input == 27) {
                cout << "Thank you for playing!" << endl;
                return 0;
            }
            game.movePlayer(input);
            game.displayMap();

            if (game.isGameOver()) {
                std::cout << "Congratulation!" << std::endl;
                system("pause");
                break;
            }

            if(game.isStuck()) {
                cout << "The box is stuck, please press R to remake the map" << endl;
                system("pause");
            }
        }

        system("cls");
    }



    return 0;
}
