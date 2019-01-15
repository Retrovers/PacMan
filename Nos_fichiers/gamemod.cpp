#include <iostream>
#include <Nos_fichiers/gamemod.h>
#include <string>
#include <map>
#include <Nos_fichiers/game.h>
#include <Nos_fichiers/gridmanagement.h>
#include <Nos_fichiers/bonus.h>
#include <Nos_fichiers/coins.h>
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

bool MoveToken (CMat & Mat, const char & Move, const unsigned& playerId, CPosition & Pos, CMyParam Params, bool & TripleMove)
{
    char car = Mat [Pos.first][Pos.second];
    Mat [Pos.first][Pos.second] = KEmpty;
    if (Move == Params.MapParamChar["KeyUpP" + to_string(playerId)] && Pos.first > 0) {
        --Pos.first;
        if (TripleMove) Pos.first - 2;
    } else if (Move == Params.MapParamChar["KeyLeftP" + to_string(playerId)] && Pos.second > 0) {
        --Pos.second;
        if (TripleMove) Pos.second - 2;
    } else if (Move == Params.MapParamChar["KeyRightP" + to_string(playerId)] && Pos.second < (Params.MapParamUnsigned["NbColumn"]) - 1) {
        ++Pos.second;
        if (TripleMove) Pos.second + 2;
    } else if (Move == Params.MapParamChar["KeyDownP" + to_string(playerId)] && Pos.first < (Params.MapParamUnsigned["NbRow"]) - 1) {
        ++Pos.first;
        if (TripleMove) Pos.first + 2;
    } else {
        Mat [Pos.first][Pos.second] = car;
        return false;
    }
    if(TripleMove) TripleMove = false;
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
            cout << Lang["ConfirmChoise"] << " : ";
            cin >> choise;
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
        vector<CPosition> Coins = GenerateCoins(4, Mat, Params);
        vector<unsigned> BonusPlayer1, BonusPlayer2;
        cout << Lang["RandomGamePage"] << endl;
        bool Victory = false;
        unsigned PartyNum (1);
        vector<unsigned> PlayersCoins = {0,0};
        while (PartyNum <= 250 && !Victory){
            bool TripleMove = false;
            while(true){
                ClearScreen();
                cout << Lang["RandomGamePage"] << endl;
                DisplayGrid (Mat, Params, PlayersCoins, Players);
                cout << Lang["Step"] << " : " << PartyNum << endl;
                Color (Params.MapParamString["ColorP" + to_string((PartyNum%2)+1)]);
                cout << Players[PartyNum%2];
                Color (KColor.find("KReset")->second);
                cout << ", " << Lang["PlayerPlay"] << endl;
                ShowBonusAvailable((PartyNum%2 == 0 ? BonusPlayer1: BonusPlayer2), Params, ParamLang);
                cout << Lang["EnterMove"] << " : ";
                char Action = getch();
                Action = tolower(Action);
                if (MoveToken (Mat, Action, ((PartyNum%2) + 1) ,(PartyNum%2 == 0 ? PosPlayer1: PosPlayer2), Params, TripleMove)){
                    break;
                } else {
                    BonusUse(Params, (PartyNum%2 == 0 ? BonusPlayer1: BonusPlayer2), (PartyNum%2 == 0 ? PosPlayer1: PosPlayer2), Mat, Action, TripleMove);
                }
                cout << '\a';
            }
            ClearScreen();
            cout << Lang["RandomGamePage"] << endl;
            DisplayGrid (Mat, Params ,PlayersCoins, Players);
            if (PosPlayer1 == PosPlayer2) CoinsKill(PartyNum%2, PlayersCoins, PosPlayer1, PosPlayer2, Mat, Params);
            if (PlayersCoins[(PartyNum%2)] >= Params.MapParamUnsigned["CoinsLimit"]) Victory = true;

            for (unsigned i = 0; i < Bonus.size(); ++i){
                if (PosPlayer1 == Bonus[i]){
                    Bonus.erase(Bonus.begin()+i);
                    BonusAdd(Mat, BonusPlayer1, PosPlayer1, Params, Bonus);
                } else if (PosPlayer2 == Bonus[i]) {
                    BonusAdd(Mat, BonusPlayer2 ,PosPlayer2, Params, Bonus);
                    Bonus.erase(Bonus.begin()+i);
                }
            }
            for (unsigned i = 0; i < Coins.size(); ++i){
                if (PosPlayer1 == Coins[i]){
                    Coins.erase(Coins.begin()+i);
                    CoinsAdd(Mat, PlayersCoins, 0 , Coins, Params);
                } else if (PosPlayer2 == Coins[i]){
                    Coins.erase(Coins.begin()+i);
                    CoinsAdd(Mat, PlayersCoins, 1 , Coins, Params);
                }
            }

            ++PartyNum;
            if (PartyNum == 40 || PartyNum == 70 || PartyNum == 90 || PartyNum == 130) GenerateBonus(1, Mat, Params, false);
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
            cout << Lang["WantRestart"] << " : ";
            cin >> choise;
            if (choise == 0 || choise == 1) break;
        }
        if (choise == 0) break;
    }
}

void PlayCustomMapMod(CLang ParamLang){
    ClearScreen();
    vector<string> Players(2);
    map <string, string> Lang = ParamLang.MapLangString;
    while (true){
        cout << Lang["CustomMapPage"] << endl;
        CMat Mat;
        if (!SelectCustomMaps(Mat, ParamLang)){
            cout << Lang["MapsNotFound"];
            char c;
            cin >> c;
            if (c == 'q') break;
        } else {
            break;
        }
    }
}
