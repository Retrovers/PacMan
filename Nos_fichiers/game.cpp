#include <iostream>
#include <unistd.h>
#include "game.h"
#include "config.h"
#include "gridmanagement.h"
#include "gamemod.h"
#include <termios.h>
#include <stdlib.h>


#include <map>
using namespace std;

void welcome(CMyParam & Param){
    ClearScreen();
    cout << "Bonjour et bienvenue sur le jeu ! / Hello and welcome on our game !" << endl
         << "Pour commancer selectionez une langue parmis cette liste / For start, select one language : " << endl
         << "1. Francais" << endl << "2. English" << endl << "3.Espagna" << endl;
    while (true) {
        cout << "Ecrire le numero de la langue / Write the number of your language : ";
        unsigned lang;
        cin >> lang;
        if (lang >= 1 && lang <= 3) {
            GenerateConfig(lang, Param);
            ClearScreen();
            break;
        }
    }
}

unsigned Random (unsigned min, unsigned max){
    unsigned r;
    while (true){
        r = rand() % (max - min + 1) + min;
        if (min <= r && r <= max) break;
    }
    return r;
}
int ppal (void) {
    srand(time(NULL));
    CMyParam Params;
    CLang ParamLang;
    InitParams(Params);
    if(!LoadParams(Params, "config/config.yaml")) {
        welcome(Params);
    }
    LoadLang(Params.MapParamString["Lang"], ParamLang);
    map <string, string> Lang = ParamLang.MapLangString;

    ClearScreen();
    while (true) {
        unsigned GameMod;
        while (true){
            cout  << Lang ["MenuPage"] << endl << Lang["GameMenu"] << endl << Lang["RandomMapMenu"] << endl << Lang["CustomMapMenu"] << endl
                                        << Lang["Command"] << endl << Lang["AboutMenu"] << endl << Lang["ExitMenu"] << endl;
            while (true){
               cout << Lang["SelectChoiceForGameModMenu"] << " : ";
               cin >> GameMod;
               if (GameMod == 5) {
                   ClearScreen();
                   cout << Lang["Goodbye"] << endl;
                   exit(1);
               }
               if (GameMod >= 1 && GameMod <= 4) break;
            }
            ClearScreen();
            switch (GameMod) {
            case 1:
                PlayRandomGameMod(ParamLang, Params);
                break;
            case 2:
                PlayCustomMapMod(ParamLang);
                break;
            case 3:
                Command(ParamLang, Params);
                break;
            case 4 :
                About(ParamLang);
                break;
            default:
                cerr << "Programme corrompu !";
                break;
            }
            ClearScreen();
        }
    }
    return 0;
} //ppal ()

char getch() {
    char buf = 0;
    struct termios old = { 0 };
    fflush(stdout);
    if (tcgetattr(0, &old) < 0) perror("tcsetattr()");
    old.c_lflag    &= ~ICANON;   // local modes = Non Canonical mode
    old.c_lflag    &= ~ECHO;     // local modes = Disable echo.
    old.c_cc[VMIN]  = 1;         // control chars (MIN value) = 1
    old.c_cc[VTIME] = 0;         // control chars (TIME value) = 0 (No time)
    if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0) perror("read()");
    old.c_lflag    |= ICANON;    // local modes = Canonical mode
    old.c_lflag    |= ECHO;      // local modes = Enable echo.
    if (tcsetattr(0, TCSADRAIN, &old) < 0) perror ("tcsetattr ~ICANON");
    return buf;
 }
