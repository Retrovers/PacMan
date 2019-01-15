#include <iostream>
#include <iomanip>
#include "Nos_fichiers/gridmanagement.h"
#include "type.h" //nos types
#include <stdio.h>
#include <Nos_fichiers/config.h>
#include <Nos_fichiers/game.h>

using namespace std;

void ClearScreen()
{
    cout << "\033[H\033[2J";
}// ClearScreen ()

void Color (const string & Col)
{
    cout << "\033[" << Col.c_str () <<"m";
} // Color ()

void DisplayGrid (const CMat & Mat, CMyParam Params, vector<unsigned> Coins, vector<string> Players)
{
    const unsigned KNbLine = Mat.size ();
    const unsigned KNbCol  = Mat[0].size ();
    Color(Params.MapParamString["BorderColor"]);
    cout << string (KNbCol + 2 , '_');
    Color (KColor.find("KReset")->second);
    cout << setw(15) << Players[0] << " : " <<  Coins[0] << " points" <<  endl;
    for (unsigned i (0); i < KNbLine; ++i)
    {
        Color(Params.MapParamString["BorderColor"]);
        cout << '|';
        Color (KColor.find("KReset")->second);
        for (char c : Mat[i])
        {
            if (c == KEmpty) {
                cout << c;
            } else if (c == Params.MapParamChar["TokenP1"]){
                Color (Params.MapParamString["ColorP1"]);
                cout << c;
                Color (KColor.find("KReset")->second);
            } else if (c == Params.MapParamChar["TokenP2"]) {
                Color (Params.MapParamString["ColorP2"]);
                cout << c;
                Color (KColor.find("KReset")->second);
            } else if (c == Params.MapParamChar["BonusToken"]){
                Color (Params.MapParamString["BonusColor"]);
                cout << c;
                Color (KColor.find("KReset")->second);
            } else if (c == Params.MapParamChar["CoinsToken"]){
                Color(Params.MapParamString["CoinsColor"]);
                cout << c;
                Color (KColor.find("KReset")->second);
            }
        }
        Color(Params.MapParamString["BorderColor"]);
        cout << '|';
        if (i == 0){
            Color (KColor.find("KReset")->second);
            cout << setw(15) << Players[1] << " : " <<  Coins[1] << " points" <<  endl;
        } else {
            cout << endl;
        }
        Color (KColor.find("KReset")->second);
    }
    Color(Params.MapParamString["BorderColor"]);
    cout << string (KNbCol + 2 , '-') << endl;
    Color (KColor.find("KReset")->second);
}// ShowMatrix ()


void InitGrid (CMat & Mat, unsigned NbLine, unsigned NbColumn, CPosition & PosPlayer1, CPosition & PosPlayer2, CMyParam Params)
{
    Mat.resize (NbLine);
    const CVLine KLine (NbColumn, KEmpty);
    for (CVLine &ALine : Mat)
        ALine = KLine;

    PosPlayer1.first = 0;
    PosPlayer1.second = NbColumn - 1;
    Mat [PosPlayer1.first][PosPlayer1.second] = Params.MapParamChar["TokenP1"];
    PosPlayer2.first = NbLine - 1;
    PosPlayer2.second = 0;
    Mat [PosPlayer2.first][PosPlayer2.second] = Params.MapParamChar["TokenP2"];
}//InitMat ()

bool SelectCustomMaps(CMat & Mat, CLang ParamLang){
    vector <string> MapsFiles;
    map <string, string> Lang = ParamLang.MapLangString;
    string ListDirString = listDir();
    string tmp;
    for (unsigned i = 0; i < ListDirString.size(); ++i){
        if (ListDirString[i] == '\n'){
            MapsFiles.push_back(tmp);
            tmp = "";
        } else {
            tmp += ListDirString[i];
        }
    }
    if (MapsFiles.size() == 0) return false;
    cout << Lang["InstructionForSelectCustomMap"] << " :" << endl;
    for (unsigned i = 0; i < MapsFiles.size(); ++i){
          cout << i << ". " << MapsFiles[i] << endl;
    }
    unsigned c;
    while (true){
        cout << Lang["SelectCustomMap"] << " : ";
        cin >> c;
        if (c >= 0 && c <= MapsFiles.size() - 1) break;

    }
    //InitGridCustomMap(Mat, "/Nos_fichiers/maps/" + MapsFiles[i]);
    return true;
}

string listDir(){
    std::string command("ls Nos_fichiers/maps/ 2>1");
        std::array<char, 128> buffer;
        string result;
        FILE* pipe = popen(command.c_str(), "r");
        while (fgets(buffer.data(), 128, pipe) != NULL) {
            result += buffer.data();
        }
        pclose(pipe);
        return result;
}
