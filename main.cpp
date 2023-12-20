#define SFML_STATIC

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
const vector<vector<int>> diagonals[3] = {{
        // {10}, 
        {11, 23}, 
        {12, 24, 35}, 
        {13, 25, 36, 46}, 
        {0, 1, 3, 6, 14, 26, 37, 47, 56, 65, 75, 86, 98}, 
        {2, 4, 7, 15, 27, 38, 48, 57, 66, 76, 87, 99}, 
        {5, 8, 16, 28, 39, 49, 58, 67, 77, 88, 100}, 
        {9, 17, 29, 40, 50, 59, 68, 78, 89, 101}, 
        {18, 30, 41, 51, 60, 69, 79, 90, 102}, 
        {19, 31, 42, 52, 61, 70, 80, 91, 103, 111}, 
        {20, 32, 43, 53, 62, 71, 81, 92, 104, 112, 115}, 
        {21, 33, 44, 54, 63, 72, 82, 93, 105, 113, 116, 118}, 
        {22, 34, 45, 55, 64, 73, 83, 94, 106, 114, 117, 119, 120}, 
        {74, 84, 95, 107}, 
        {85, 96, 108}, 
        {98, 109}
        // {110}
    }, {
        // {98},
        {86,99},
        {75,87,100},
        {65,76,88,101},
        {10,23,35,46,56,66,77,89,102,111,115,118,120},
        {11,24,36,47,57,67,78,90,103,112,116,119},
        {12,25,37,48,58,68,79,91,104,113,117},
        {13,26,38,49,59,69,80,92,105,114},
        {14,27,39,50,60,70,81,93,101},
        {6,15,28,40,51,61,71,82,94,107},
        {3,7,16,29,41,52,62,72,83,95,108},
        {1,4,8,17,30,42,53,63,73,84,96,109},
        {0,2,5,9,18,31,43,54,64,74,85,97,110},
        {19,32,44,55},
        {20,33,45},
        {21,34}
        // {22}
    }, {
        // {0},
        {1, 2},
        {3, 4, 5},
        {6, 7, 8, 9},
        {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22},
        {23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34},
        {35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45},
        {46, 47, 48, 49, 50, 51, 52, 53, 54, 55},
        {56, 57, 58, 59, 60, 61, 62, 63, 64},
        {65, 66, 67, 68, 69, 70, 71, 72, 73, 74},
        {75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85},
        {86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97},
        {98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110},
        {111, 112, 113, 114},
        {115, 116, 117},
        {118, 119}
        // {120}
    }};

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
    // check each diagonal
    for(int dd = 0; dd < 3; dd++) {
        // if two are adjacent return true
        // go to first marble on diagonal in either direction and check if that spot (doubled) is en
        for(auto diag : diagonals[dd]) {
            int fst = -1, fen = -1;
            for(int i = 0; i < diag.size(); i++) {
                if(diag[i] == st) fst = i;
                else if(diag[i] == en) fen = i;
            }

            if(fst == -1 || fen == -1) continue;

            if(fst == fen + 1 || fst + 1 == fen) return 1;
            if(abs(fst - fen) & 1) return 0;

            int mid = min(fst, fen) + (abs(fst - fen) + 1) / 2;
            if(loc[diag[mid]] == "") return 0;

            int cnt = 0;
            for(int i = min(fst, fen) + 1; i < max(fst, fen); i++) {
                if(loc[diag[i]] != "") ++ cnt;
            }
            if(cnt != 1) return 0;
            return 1;
        }
    }
    return 0;
}

vector<int> possibleNextMoves(int st) {
    vector<int> ret;
    ret.push_back(st);

    // for each diagonal, check adjacent and nearest marble -> double distance
    for(int dd = 0; dd < 3; dd++) {
        // if two are adjacent return true
        // go to first marble on diagonal in either direction and check if that spot (doubled) is en
        for(auto diag : diagonals[dd]) {
            int fst = -1;
            for(int i = 0; i < diag.size(); i++) {
                if(diag[i] == st) fst = i;
            }

            if(fst == -1) continue;

            for(int i = fst + 1; i < diag.size(); i++) {
                if(i == fst + 1 && loc[diag[i]] == "") ret.push_back(diag[i]);
                if(loc[diag[i]] != "") {
                    int nx = i + i - fst;
                    if(nx < diag.size() && loc[diag[nx]] == "")
                        ret.push_back(diag[nx]);
                    break;
                }
            }
            for(int i = fst - 1; i >= 0; i--) {
                if(i == fst - 1 && loc[diag[i]] == "") ret.push_back(diag[i]);
                if(loc[diag[i]] != "") {
                    int nx = i - (fst - i);
                    if(nx < diag.size() && loc[diag[nx]] == "")
                        ret.push_back(diag[nx]);
                    break;
                }
            }
        }
    }

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
                    
                    if(!isValidPosition(spriteCor[moveidx], moveto)) moveto = spriteCor[moveidx];
                    swap(loc[spriteCor[moveidx]], loc[moveto]);
                    spriteCor[moveidx] = moveto;
                    m[moveidx].setPosition(gridPos[moveto]);
                }
            }
        }

        window.clear();
        window.draw(sboard);
        if(isMove) {
            m[moveidx].setPosition(Vector2f(pos) - delt);
            vector<int> posnext = possibleNextMoves(spriteCor[moveidx]);
            for(auto p : posnext) {
                CircleShape circ(radius);
                circ.setFillColor(sf::Color(100, 250, 50));
                circ.setPosition(gridPos[p]);

                window.draw(circ);
            }
        }

        for(int i = 0; i < 20; i++) 
            window.draw(m[i]);
        window.display();
    }

    return 0;
}