#include <iostream>
#include <unistd.h>
#include "game.h"
#include "config.h"
#include "gridmanagement.h"
#include "gamemod.h"
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>


#include <map>
using namespace std;

void welcome(CMyParam & Param){
    ClearScreen();
    cout << "Bonjour et bienvenue sur le jeu ! / Hello and welcome on our game !" << endl
         << "Pour commancer selectionez une langue parmis cette liste / For start, select one language : " << endl
         << "1. Francais" << endl << "2. English" << endl << "3.ةيبرعلا" << endl;
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
int ppal (void)
{
    srand(time(NULL));
    CMyParam Params;
    CLang ParamLang;
    InitParams(Params);
    if(!LoadParams(Params, "Nos_fichiers/config/config.yaml")) {
        welcome(Params);
    }
    LoadLang(Params.MapParamString["Lang"], ParamLang);
    map <string, string> Lang = ParamLang.MapLangString;

    ClearScreen();
    while (true) {
        unsigned GameMod;
        while (true){
            cout  << Lang ["MenuPage"] << endl << Lang["GameMenu"] << endl << Lang["RandomMapMenu"] << endl << Lang["CustomMapMenu"] << endl
                                        << Lang["AboutMenu"] << endl << Lang["ExitMenu"] << endl;
            while (true){
               cout << Lang["SelectChoiceForGameModMenu"];
               cin >> GameMod;
               if (GameMod == 4) {
                   ClearScreen();
                   cout << Lang["Goodbye"] << endl;
                   exit(1);
               }
               if (GameMod >= 1 && GameMod <= 3) break;
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

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
