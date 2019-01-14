#include <iostream>
#include <Nos_fichiers/gamemod.h>
#include <string>
#include <map>
#include <Nos_fichiers/game.h>
#include <Nos_fichiers/gridmanagement.h>
#include <Nos_fichiers/bonus.h>

using namespace std;

void About(CLang ParamLang){
    ClearScreen();
    map <string, string> Lang = ParamLang.MapLangString;
    char c;
    cout << Lang["AboutPage"] << endl << Lang["About"] << endl << Lang["HowExitAbout"];
    while(true){
        c = getch();
        if (c == 'q') break;
    }
}

bool MoveToken (CMat & Mat, const char & Move, const unsigned& playerId, CPosition & Pos, CMyParam Params)
{
    char car = Mat [Pos.first][Pos.second];
    Mat [Pos.first][Pos.second] = KEmpty;
    if (Move == Params.MapParamChar["KeyUpP" + to_string(playerId)] && Pos.first > 0) {
        --Pos.first;
    } else if (Move == Params.MapParamChar["KeyLeftP" + to_string(playerId)] && Pos.second > 0) {
        --Pos.second;
    } else if (Move == Params.MapParamChar["KeyRightP" + to_string(playerId)] && Pos.second < (Params.MapParamUnsigned["NbColumn"]) - 1) {
        ++Pos.second;
    } else if (Move == Params.MapParamChar["KeyDownP" + to_string(playerId)] && Pos.first < (Params.MapParamUnsigned["NbRow"]) - 1) {
        ++Pos.first;
    } else {
        Mat [Pos.first][Pos.second] = car;
        return false;
    }
    Mat [Pos.first][Pos.second] = car;
    return true;
} //MoveToken ()

void PlayRandomGameMod(CLang ParamLang, CMyParam Params){
    ClearScreen();
    vector<string> Players(2);
    map <string, string> Lang = ParamLang.MapLangString;
    while (true){
        cout << Lang["RandomGamePage"] << endl << Lang["InstructionForPlayerName"] << endl
                                       << Lang["Player1"] << " : ";
        cin >> Players[0];
        cout << Lang["Player2"] << " : ";
        cin >> Players[1];
        unsigned choise;
        while (true){
            cout << Lang["ConfirmChoise"];
            cin >> choise;;
            if (choise == 0 || choise == 1) break;
        }
        if (choise == 1) break;
        ClearScreen();
    }
    while (true) {
        ClearScreen();
        cout << "Loading...";
        CMat Mat;
        CPosition PosPlayer1, PosPlayer2;
        InitGrid(Mat, Params.MapParamUnsigned["NbRow"], Params.MapParamUnsigned["NbColumn"], PosPlayer1, PosPlayer2, Params);
        vector<CPosition> Bonus = GenerateBonus(2, Mat, Params);
        vector<unsigned> BonusPlayer1, BonusPlayer2;
        cout << Lang["RandomGamePage"] << endl;
        bool Victory = false;
        const unsigned KSize (10);
        unsigned PartyNum (1);
        const unsigned KMaxPartyNum (KSize * KSize);
        while (PartyNum <= KMaxPartyNum && !Victory){
            while(true){
                ClearScreen();
                cout << Lang["RandomGamePage"] << endl;
                DisplayGrid (Mat, Params);
                cout << Lang["Step"] << " : " << PartyNum << endl;
                Color (Params.MapParamString["ColorP" + to_string((PartyNum%2)+1)]);
                cout << Players[PartyNum%2];
                Color (KColor.find("KReset")->second);
                cout << ", " << Lang["PlayerPlay"] << endl;
                ShowBonusAvailable((PartyNum%2 == 0 ? BonusPlayer1: BonusPlayer2), Params, ParamLang);
                cout << Lang["EnterMove"] << " : ";
                char Action = getch();
                Action = tolower(Action);
                BonusUse(Params, (PartyNum%2 == 0 ? BonusPlayer1: BonusPlayer2), (PartyNum%2 == 0 ? PosPlayer1: PosPlayer2), Mat, Action);
                if (MoveToken (Mat, Action, ((PartyNum%2) + 1) ,(PartyNum%2 == 0 ? PosPlayer1: PosPlayer2), Params)) break;
                cout << '\a';
            }
            ClearScreen();
            cout << Lang["RandomGamePage"] << endl;
            DisplayGrid (Mat, Params);
            if (PosPlayer1 == PosPlayer2) Victory = true;
            for (unsigned i = 0; i < Bonus.size(); ++i){
                if (PosPlayer1 == Bonus[i]){
                    Bonus.erase(Bonus.begin(),Bonus.begin()+i);
                    BonusAdd(Mat, BonusPlayer1, PosPlayer1, Params, Bonus);
                } else if (PosPlayer2 == Bonus[i]) {
                    BonusAdd(Mat, BonusPlayer2 ,PosPlayer2, Params, Bonus);
                    Bonus.erase(Bonus.begin(),Bonus.begin()+i);
                }
            }
            ++PartyNum;
        }
        ClearScreen();
        if (!Victory){
            Color (KColor.find("KMAgenta")->second);
            cout << Lang["NoWinner"] << endl;
        } else {
            Color (KColor.find("KGreen")->second);
            cout << Lang["Congrelation"] << " " <<Players[(PartyNum -1)%2]
                 << " " << Lang["PlayerWin"] << endl;
            Color (KColor.find("KReset")->second);
        }
        unsigned choise = 0;
        while (true){
            cout << Lang["WantRestart"];
            cin >> choise;
            if (choise == 0 || choise == 1) break;
        }
        if (choise == 0) break;
    }
}

void PlayCustomMapMod(CLang ParamLang){
    ClearScreen();
    map <string, string> Lang = ParamLang.MapLangString;
}
