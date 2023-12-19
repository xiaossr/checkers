#include "SFML/Graphics.hpp"
#include <bits/stdc++.h>
using namespace sf;
using namespace std;

template <typename T>
bool operator<(const Vector2<T>& left, const Vector2<T>& right) {
    return left.x + left.y < right.x + right.y;
}

template <typename T>
Vector2<T> abs(Vector2<T> coord) {
    return Vector2<T>(abs(coord.x), abs(coord.y));
}

Sprite m[20];
const double ydiff = 37, xdiff = 43, startx[] = {316, 338}, starty = 17, radius = 18;
const vector<int> cntRow = {1, 2, 3, 4, 13, 12, 11, 10, 9, 10, 11, 12, 13, 4, 3, 2, 1}; //, psumRow = {0, 1, 3, 6, 10, 23, 35, 46, 56, 67, 79, 92, 96, 99, 101, 102};
vector<Vector2f> gridPos;
vector<string> loc;
vector<int> spriteCor(20);
map<string, int> color;

void calculatePosition() {
    for(int i = 0; i < cntRow.size(); i++) {
        int curstartx = startx[i % 2] - xdiff * floor(cntRow[i] / 2);
        int curstarty = starty + i * ydiff;
        for(int j = 0; j < cntRow[i]; j++) {
            gridPos.push_back(Vector2f(curstartx, curstarty));
            curstartx += xdiff;
            if(i < 4) loc.push_back("green");
            else if(i >= 13) loc.push_back("red");
            else loc.push_back("");
        }
    }
}

void loadPosition() {
    int k = 0;
    for(int i = 0; i < loc.size(); i++) {
        if(loc[i] == "") continue;
        m[k].setTextureRect(IntRect(color[loc[i]], 0, 791, 800));
        // cout << "set position of " << loc[i] << " to " << pos[i].first << " " << pos[i].second << "\n";
        m[k].setPosition(gridPos[i]);
        spriteCor[k] = i;
        k++;
    }
}

bool isValidPosition(int st, int en) {
    return 1;
}

vector<int> possibleNextMoves(int at) {
    vector<int> ret;
    ret.push_back(at);

    

    return ret;
}

int main()
{
    RenderWindow window(VideoMode(668, 668), "Chinese Checkers!");
    Texture t1, t2;
    t1.loadFromFile("img\\marble.png");
    t2.loadFromFile("img\\board.png");

    Sprite sboard(t2);

    color["green"] = 0;
    color["blue"] = 791*1;
    color["orange"] = 792*2;
    color["purple"] = 793*3;
    color["red"] = 794*4;
    color["yellow"] = 794*5;

    for(int i=0;i<20;i++) {
        m[i].setTexture(t1);
        m[i].setScale(0.045, 0.045);
    }

    calculatePosition();
    loadPosition();

    bool isMove = false;
    Vector2f delt;

    int moveidx = 0;
    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
            
            if(e.type == Event::MouseButtonPressed) {
                if(e.mouseButton.button == Mouse::Left) {
                    for(int i = 0; i < 20; i++)
                        if(m[i].getGlobalBounds().contains(Vector2f(pos))) {
                            isMove = true;
                            moveidx = i;
                            delt = Vector2f(pos) - m[i].getPosition();
                        }
                }
            }

            if(e.type == Event::MouseButtonReleased) {
                if(e.mouseButton.button == Mouse::Left) {
                    isMove = false;
                    int moveto = 0, curvals = 0;
                    Vector2f distToGrid = Vector2f(10000,10000);
                    for(int i = 0; i < gridPos.size(); i++) {
                        if(loc[i] != "" && i != spriteCor[moveidx]) continue;
                        if(abs(gridPos[i] - Vector2f(pos) + Vector2f(17, 17)) < distToGrid) 
                            moveto = i, distToGrid = abs(gridPos[i] - Vector2f(pos) + Vector2f(17, 17));
                    }
                    
                    if(isValidPosition(moveidx, moveto)) {
                        swap(loc[moveidx], loc[moveto]);
                        m[moveidx].setPosition(gridPos[moveto]);
                    }
                }
            }
        }

        if(isMove) {
            m[moveidx].setPosition(Vector2f(pos) - delt);
            vector<int> posnext = possibleNextMoves(moveidx);
        }

        window.clear();
        window.draw(sboard);
        for(int i = 0; i < 20; i++) 
            window.draw(m[i]);
        window.display();
    }

    return 0;
}