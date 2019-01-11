#include <iostream>
#include <iomanip>
#include "gridmanagement.h"

#include "type.h" //nos types


using namespace std;



void ClearScreen()
{
    cout << "\033[H\033[2J";
}// ClearScreen ()

void Color (const string & Col)
{
    cout << "\033[" << Col.c_str () <<"m";
} // Color ()

template <class T, class U>
void ShowMap (const map<T,U> & AMap){
    for (const pair <T,U> & Val : AMap)                cout << "Cle : " << Val.first << "   "             << "Valeur : " << Val.second << endl;
    cout << endl;
}// ShowMap ()

void DisplayGrid (const CMat & Mat, CMyParam Params)
{
    const unsigned KNbLine = Mat.size ();
    const unsigned KNbCol  = Mat[0].size ();
    Color(Params.MapParamString["BorderColor"]);
    cout << string (KNbCol + 2 , '_') << endl;
    Color (KColor.find("KReset")->second);
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
            }
        }
        Color(Params.MapParamString["BorderColor"]);
        cout << '|' << endl;
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
