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
bool fu = false;
bool aisnake = false;
const int width = 40, height = 20;
string state;
int x = 0, y = 0, fx = 0, fy = 0, ai_x = 0, ai_y = 0, score = 0, lev = 1, len = 0, ailen = 0, totalfruit = 10000;
vector<int> tailx(2000);
vector<int> taily(2000);
vector<int> tailai_x(2000);
vector<int> tailai_y(2000);
enum eDirection { stop = 0, Left, Right, up, down };
eDirection dir;

void SetColor(int foreground, int background = 0) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (background << 4) | foreground);
}

void PlaySoundEffect(const string& sound) {
    if (sound == "eat") {
        PlaySound(TEXT("eat.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    else if (sound == "gameOver") {
        PlaySound(TEXT("gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);

    }
    else  if (sound == "intro") {
        PlaySound(TEXT("INTROSOUND.wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);

    }
}




// // //
void ShowStartMenu(bool& automove, bool& wall, bool& aisnake, int& level) {
    system("cls");

    const int numOptions = 5;
    string options[numOptions] = {
        "\n  --> Choose Movement Mode  ",
        "\n  --> Select Wall Mode  ",
        "\n  --> Enable/Disable AI Snake " ,
        "\n  --> Choose Level " ,
        "\n  --> Start"
    };

    int selectedOption = 0;
    bool menuActive = true;

    while (menuActive) {
        system("cls");

        SetColor(11, 0);
        cout << "================================================\n";
        cout << "                  SNAKE GAME MENU               \n";
        cout << "================================================\n\n";

        SetColor(14, 0);
        for (int i = 0; i < numOptions; ++i) {
            if (i == selectedOption) {
                
                SetColor(10, 0); 
                cout << options[i] << " <--  "; 
                switch (i)
                {
                case 0: cout<<(automove ? "Auto" : "Manual");
                    break;
                case 1: cout << (wall ? "With Walls" : "No Walls");
                    break;
                case 2: cout << (aisnake ? "Enabled" : "Disabled");
                    break;
                case 3:
                    cout << (lev == 1 ? "Easy" : "Hard");
                    break;
                }
            }
            else {
                SetColor(14, 0);
                cout << "      " << options[i] << "\n";
            }
        }

        SetColor(14, 0);
        cout << "\n================================================\n";
        cout << " Use UP/DOWN arrow keys to navigate, ENTER to select.\n";

        
        char key = _getch();
        switch (key) {
        case 72: 
            if (selectedOption > 0) selectedOption--;
            break;
        case 80: 
            if (selectedOption < numOptions - 1) selectedOption++;
            break;
        case 13: 
            switch (selectedOption) {
            case 0: 
                automove = !automove;
                break;
            case 1:
                wall = !wall;
                break;
            case 2: 
                aisnake = !aisnake;
                break;
            case 3: 
                level = (level == 1) ? 2 : 1; 
                break;
            case 4:
                system("cls");
                return;
                break;
            }
            break;
        }
    }
}


void ShowStartScreen() {
    system("cls");
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
        SetColor(11, 0);
        cout << line << endl;
    }


    cout << "\n\n";
    SetColor(14, 0);
    cout << "              S N A K E   G A M E\n";
    cout << "          Developed by Abdullah Maher\n\n";


    string prompt = ">> Press any key to start <<";
    bool visible = true;

    while (!_kbhit()) {
        SetColor(10, 0);
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
}


void ShowGameOverScreen() {
    system("cls");
    PlaySoundEffect("gameOver");
    ailen = 0;
    SetColor(12, 0);
    cout << R"(
   _____                         ____                 
  / ____|                       / __ \                
 | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ 
 | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__|
 | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |   
  \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|   
                                                     
)";
    cout << "\n";
    SetColor(14, 0);
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


bool safe(int new_x, int new_y) {
    for (int i = 0; i < ailen; i++) {
        if ((tailai_x[i] == new_x && tailai_y[i] == new_y) || new_x == x && new_y == y)
            return false;
    }
    for (int i = 0; i < len; i++) {
        if (tailx[i] == new_x && taily[i] == new_y)
        {
            return false;
        }
    }
    return true;
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
    if (aisnake) {
        do {
            ai_x = rand() % (width - 2) + 1;
            ai_y = rand() % height;

        } while ((ai_x == x && ai_y == y) || (len > 0 && [&]() {
            for (int i = 0; i < len; i++) {
                if (tailx[i] == ai_x && taily[i] == ai_y) return true;
            }
            return false;
            }()));
    }
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
    SetColor(14, 0);
    cout << "Level " << lev << " " << state << endl;
    SetColor(7, 0);
    cout << "score= " << 10000 - totalfruit << endl;

    for (int i = 0; i < width; i++) {
        SetColor(0, 10);
        cout << ' ';
    }
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (!aisnake) ai_x = 400, ai_y = 400;
            if (j == 0 || j == width - 1) {
                SetColor(0, 10);
                cout << " ";
            }
            else if (i == y && j == x) {
                SetColor(12, 0);
                cout << 'O';
            }
            else if (i == ai_y && j == ai_x) {
                SetColor(13, 0);
                cout << 'X';
                fu = true;
            }
            else if (i == fy && j == fx) {
                SetColor(9, 0);
                cout << '@';
            }
            else if (goldenFruit && i == gy && j == gx) {
                SetColor(14, 0);
                cout << '$';
            }
            else {
                bool flag = false;
                for (int s = 0; s < len; s++) {
                    if (i == taily[s] && j == tailx[s]) {
                        SetColor(12, 0);
                        cout << 'o';
                        flag = true;
                        break;
                    }
                }


                for (int s = 0; s < ailen; s++) {
                    if (i == tailai_y[s] && j == tailai_x[s]) {
                        SetColor(14, 0);
                        cout << 'x';

                        if (flag == false)flag = true;
                        break;
                    }
                }
                if (!flag) {
                    SetColor(0, 0);
                    cout << ' '; continue;
                }
                //
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width; i++) {
        SetColor(0, 10);
        cout << ' ';
    }
    SetColor(0, 0);
    cout << endl;
}





void ShowPauseMenu(bool& aisnake, bool& GameOver) {
    system("cls");
    SetColor(14, 0);

    const int numOptions = 4;
    string options[numOptions] = {
        "\n  --> Continue Game",
        "\n  --> Toggle AI Snake",
        "\n  --> Go to Main Menu",
        "\n  --> Exit Game"
    };

    int selectedOption = 0;
    bool menuActive = true;

    while (menuActive) {
        system("cls");

        SetColor(11, 0);
        cout << "================================================\n";
        cout << "                   GAME PAUSED                  \n";
        cout << "================================================\n\n";

        SetColor(14, 0);
        for (int i = 0; i < numOptions; ++i) {
            if (i == selectedOption) {
                SetColor(10, 0); 
                cout  << options[i] << " <--\n";
                if (i == 1) cout << (aisnake ? " Enabled" : "  Disabled");
            }
            else {
                SetColor(14, 0);
                cout << "      " << options[i] << "\n";
            }
        }

        SetColor(14, 0);
        cout << "\n================================================\n";
        cout << " Use UP/DOWN arrow keys to navigate, ENTER to select.\n";

        char key = _getch();
        switch (key) {
        case 72: 
            if (selectedOption > 0) selectedOption--;
            break;
        case 80: 
            if (selectedOption < numOptions - 1) selectedOption++;
            break;
        case 13: 
            menuActive = false; 
            break;
        }
    }

    switch (selectedOption) {
    case 0: 
        system("cls");
        return;
    case 1: 
        aisnake = !aisnake;
        setup();
        ShowPauseMenu(aisnake, GameOver);
        break;
    case 2: 
        GameOver = true;
        return;
    case 3: 
        exit(0);
        break;
    }
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 75:
            if (dir != Right) dir = Left;
            break;
        case 77:
            if (dir != Left) dir = Right;
            break;
        case 72:
            if (dir != down) dir = up;
            break;
        case 80:
            if (dir != up) dir = down;
            break;
        case 'x':
            Sleep(70);
            GameOver = true;
            break;
        case 'p':
            ShowPauseMenu(aisnake, GameOver);
            break;

        }
    }
}




void logic() {
    int oldx = tailx[0];
    int oldy = taily[0];
    int oldaix = tailai_x[0];
    int oldaiy = tailai_y[0];
    int prev2x, prev2y;
    int prev2aix, prev2aiy;
    tailx[0] = x;
    taily[0] = y;
    tailai_x[0] = ai_x;
    tailai_y[0] = ai_y;
    for (int i = 1; i < len; i++) {
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = oldx;
        taily[i] = oldy;
        oldy = prev2y;
        oldx = prev2x;
    }
    for (int i = 1; i < ailen; i++) {
        prev2aix = tailai_x[i];
        prev2aiy = tailai_y[i];
        tailai_x[i] = oldaix;
        tailai_y[i] = oldaiy;
        oldaiy = prev2aiy;
        oldaix = prev2aix;
    }

    switch (dir) {
    case Left: x--; break;
    case Right: x++; break;
    case up: y--; break;
    case down: y++; break;
    }
    //ai
    if (aisnake == true) {
        if (ai_x > fx && safe(ai_x - 1, ai_y)) {
            ai_x--;
        }
        else if (ai_y > fy && safe(ai_x, ai_y - 1)) {
            ai_y--;
        }
        else if (ai_y < fy && safe(ai_x, ai_y + 1)) {
            ai_y++;
        }
        else if (ai_x < fx && safe(ai_x + 1, ai_y)) {
            ai_x++;
        }
    }

    //end ai

    if (wall) {
        if (x >= width - 1) x = 0;
        else if (x < 0) x = width - 1;
        if (y >= height) y = 0;
        else if (y < 0) y = height - 1;
    }

    if ((x < 0 || y < 0 || x >= width - 1 || y >= height) && wall == false) {
        cout << "opps";
        Sleep(70);
        GameOver = true;
    }

    for (int i = 0; i < len; i++) {
        if (tailx[i] == x && taily[i] == y) {
            cout << "opps";
            Sleep(70);
            GameOver = true;
        }
    }

    if (x == fx && y == fy) {
        totalfruit--;
        fx = rand() % (width - 2) + 1;
        fy = rand() % (height - 1);

        len++;
        PlaySoundEffect("eat");
    }
    if (ai_x == fx && ai_y == fy) {
        totalfruit++;
        fx = rand() % (width - 2) + 1;
        fy = rand() % (height - 1);
        ailen++;
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
        goldenFruit = false;
        totalfruit -= 5;
        len += 2;
        PlaySoundEffect("eat");
        system("cls");
    }

    if (goldenFruit) {
        goldenTimer--;
        if (goldenTimer <= 0) {
            goldenFruit = false;
        }
    }
    for (int i = 0; i < ailen; i++) {
        if ((x == tailai_x[i] && y == tailai_y[i]) || (x == ai_x && y == ai_y)) {
            Sleep(70);
            GameOver = true;
        }
    }
    if (y == ai_y && x == ai_x) {
        Sleep(70);
        GameOver = true;
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
        int n, mov, ai;
        ShowStartMenu(automove,  wall, aisnake,  lev);
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
            int sleepTime = 0;
            switch (lev) {
            case 1: sleepTime = automove ? 40 : 20; state = "(Easy)"; break;
            case 2: sleepTime = automove ? 0 : 0;  state = "(Hard!!)"; break;
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
