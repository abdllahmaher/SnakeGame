#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <mmsystem.h>
#include <limits>

#pragma comment(lib, "winmm.lib")
using namespace std;
void SetColor(int color);
bool goldenFruit = false;
int gx, gy;
int goldenTimer = 0;
int highScore = 0;
bool GameOver;
bool follow;
bool wall;
bool automove;
const int width = 60, height = 20;
string state;
int x = 0, y = 0, fx = 0, fy = 0, score = 0, lev = 1, len = 0;
vector<int> tailx(2000);
vector<int> taily(2000);
enum eDirection { stop = 0, Left, Right, up, down };
eDirection dir;

void PlaySoundEffect(const string& sound) {
    if (sound == "eat") {
        PlaySound(TEXT("eat.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    else if (sound == "gameOver") {
        PlaySound(TEXT("gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);

    }else  if (sound == "intro") {
        PlaySound(TEXT("intro.wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);

    }
}

void ShowStartScreen() {
    system("cls");


    PlaySoundEffect("intro");


    vector<string> art = {
        "                            __..._               ",
        "                        ..-'      o.            ",
        "                     .-'            :           ",
        "                 _..'             .'__..--<     ",
        "          ...--""                 '-.           ",
        "      ..-'                       __.'           ",
        "    .'                  ___...--'                ",
        "   :        ____....---'                         ",
        "  :       .'                                     ",
        " :       :           _____                       ",
        " :      :    _..--"""     """--..__              ",
        ":       :  .'                      ""i--.       ",
        ":       '.:                         :    '.     ",
        ":         '--...___i---""""--..___.'      :     ",
        " :                 ""---...---""          :     ",
        "  '.                                     :      ",
        "    '-.                                 :       ",
        "       '--...                         .'        ",
        "         :   ""---....._____.....---""          ",
        "         '.    '.                                ",
        "           '-..  '.                              ",
        "               '.  :                             ",
        "          fsc   : .'                             ",
        "               /  :                              ",
        "             .'   :                              ",
        "           .' .--'                               ",
        "          '--'                                    "
    };


    for (auto& line : art) {
        SetColor(11);
        cout << line << endl;
    }


    SetColor(14);
    cout << "\n\n";
    cout << "              S N A K E   G A M E\n";
    cout << "          Developed by Abdullah Maher\n\n";


    string prompt = ">> Press any key to start <<";
    bool visible = true;

    while (!_kbhit()) {
        SetColor(10);
        if (visible) {
            cout << prompt;
        }
        else {
            for (int i = 0; i < prompt.size(); i++) cout << " ";
        }
        cout << "\r";
        visible = !visible;
        Sleep(500);
    }

    _getch();
    PlaySound(NULL, NULL, 0);
    system("cls");
}



void ShowGameOverScreen() {
    system("cls");
    PlaySoundEffect("gameOver");
    SetColor(12);
    cout << R"(
   _____                         ____                 
  / ____|                       / __ \                
 | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ 
 | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__|
 | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |   
  \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|   
                                                     
)";
    cout << "\n";
    SetColor(14);
    cout << "Your score: " << score << "\n";
    if (score > highScore) {
        highScore = score;
        cout << "New High Score!\n";
    }
    cout << "High score: " << highScore << "\n\n";

    cout << "Press 'r' to replay or any other key to exit...\n";
    char choice = _getch();
    if (choice != 'r' && choice != 'R') {
        exit(0);
    }
    PlaySound(NULL, NULL, 0);
    system("cls");
}




void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}




void setup() {
    GameOver = false;
    if (automove) {
        dir = Right;
    }
    else {
        dir = stop;
    }
    x = width / 2;
    y = height / 2;
    do {
        fx = rand() % (width - 2) + 1;
        fy = rand() % height;

    } while ((fx == x && fy == y) || (len > 0 && [&]() {
        for (int i = 0; i < len; i++) {
            if (tailx[i] == fx && taily[i] == fy) return true;
        }
        return false;
        }()));
}





void draw() {
    COORD coord = { 0, 0 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    if (!wall) cout << "DO NOT HIT THE WALL!\n";
    SetColor(14);
    cout << "Level " << lev << " " << state << endl;
    SetColor(7);
    cout << "score= " << score << endl;

    for (int i = 0; i < width; i++) {
        SetColor(10);
        cout << '#';
    }
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1) {
                SetColor(10);
                cout << "#";
            }
            else if (i == y && j == x) {
                SetColor(12);
                cout << 'O';
            }
            else if (i == fy && j == fx) {
                SetColor(9);
                cout << '@';
            }
            else if (goldenFruit && i == gy && j == gx) {
                SetColor(14);
                cout << '$';
            }
            else {
                bool flag = false;
                for (int s = 0; s < len; s++) {
                    if (i == taily[s] && j == tailx[s]) {
                        SetColor(15);
                        cout << 'o';
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    SetColor(7);
                    cout << ' ';
                }
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width; i++) {
        SetColor(10);
        cout << '#';
    }
    cout << endl;
}



void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            if (dir != Right) dir = Left;
            break;
        case 'd':
            if (dir != Left) dir = Right;
            break;
        case 'w':
            if (dir != down) dir = up;
            break;
        case 's':
            if (dir != up) dir = down;
            break;
        case 'x':
            PlaySoundEffect("gameOver");
            cout << "opps";
            Sleep(30);
            GameOver = true;
            break;
        }
    }
}

void logic() {
    int oldx = tailx[0];
    int oldy = taily[0];
    int prev2x, prev2y;
    tailx[0] = x;
    taily[0] = y;
    for (int i = 1; i < len; i++) {
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = oldx;
        taily[i] = oldy;
        oldy = prev2y;
        oldx = prev2x;
    }

    switch (dir) {
    case Left: x--; break;
    case Right: x++; break;
    case up: y--; break;
    case down: y++; break;
    }

    if (wall) {
        if (x >= width - 1) x = 0;
        else if (x < 0) x = width - 1;
        if (y >= height) y = 0;
        else if (y < 0) y = height - 1;
    }

    if ((x < 0 || y < 0 || x >= width - 1 || y >= height) && wall == false) {
        cout << "opps";
        PlaySoundEffect("gameOver");
        Sleep(30);
        GameOver = true;
    }

    for (int i = 0; i < len; i++) {
        if (tailx[i] == x && taily[i] == y) {
            PlaySoundEffect("gameOver");
            cout << "opps";

            Sleep(30);
            GameOver = true;
        }
    }

    if (x == fx && y == fy) {
        score++;
        fx = rand() % (width - 2) + 1;
        fy = rand() % (height - 1);

        len++;
        PlaySoundEffect("eat");
    }

    if (!goldenFruit && rand() % 100 == 0) {
        int cntr = 0;
        do {
            gx = rand() % 4 < 2 ? rand() % 3 : width - 1 - rand() % 3;
            gy = rand() % 4 < 2 ? rand() % 3 : height - 1 - rand() % 3;
            cntr++;
        } while ((gx == x && gy == y) || cntr < 20);

        goldenFruit = true;
        goldenTimer = 100;
    }

    if (goldenFruit && x == gx && y == gy) {
        score += 5;
        len += 2;
        goldenFruit = false;
        PlaySoundEffect("eat");
    }

    if (goldenFruit) {
        goldenTimer--;
        if (goldenTimer <= 0) {
            goldenFruit = false;
        }
    }
}

int main() {

    srand(time(0));
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = false;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    ShowStartScreen();

    while (true) {
        DWORD startTime = GetTickCount();
        int n, mov;
        cout << "Choose the Movement mode (1: automove / 2: manual move): ";
        cin >> mov;
        automove = (mov == 1);
        cout << "Choose the mode (1: no walls / 2: with walls): ";
        cin >> n;
        cout << endl;
        cout << "choose the level (1/2/3) : ";
        cin >> lev;
        cin.ignore(10000, '\n');

        wall = (n != 1);
        system("cls");

        score = 0;
        len = 0;
        setup();

        while (!GameOver) {
            DWORD elapsed = GetTickCount() - startTime;
            if (elapsed > 15000) lev = 2;
            if (elapsed > 30000) lev = 3;

            draw();
            input();
            logic();

            int sleepTime=70;
            switch (lev) {
            case 1: sleepTime = automove ? 100 : 70; state = "(Easy)"; break;
            case 2: sleepTime = automove ? 60 : 40; state = "(Medium!)"; break;
            case 3: sleepTime = automove ? 30 : 0;  state = "(Hard!!)"; break;
            }
            if (dir == up || dir == down) {
                sleepTime += 10;
            }
            Sleep(sleepTime);
        }

        ShowGameOverScreen();
        GameOver = false;
    }
}
