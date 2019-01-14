#include <iostream>
#include <map>
#include <Nos_fichiers/gamemod.h>
#include <string>
#include <Nos_fichiers/gridmanagement.h>
#include <Nos_fichiers/bonus.h>
#include <Nos_fichiers/game.h>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

using namespace std;

vector<CPosition> GenerateBonus (const unsigned number, CMat & Mat, CMyParam Params, bool wait){
    unsigned row, collumn;
    vector<CPosition> BonusCord(number);
    for (unsigned i = 0; i < number; ++i){
        if (wait) sleep(1);
        collumn = Random(1, Params.MapParamUnsigned["NbColumn"]);
        if (wait) sleep(1);
        row = Random(1, Params.MapParamUnsigned["NbRow"]);
        Mat[row][collumn] = Params.MapParamChar["BonusToken"];
        CPosition BonusPos;
        BonusPos.first = row;
        BonusPos.second = collumn;
        BonusCord[i] = BonusPos;
    }
    return BonusCord;
}
void ShowBonusAvailable(const vector<unsigned> & BonusPlayer, CMyParam & Params,const CLang & ParamLang) {
    map <string, string> Lang = ParamLang.MapLangString;
    if (BonusPlayer.size() != 0){
        cout << Lang["BonusAvailabe"] << " : ";
        for (unsigned i = 0; i < BonusPlayer.size(); ++i){
            cout << Lang["Bonus_" + to_string(BonusPlayer[i])] << "(" << Lang["Press"] << " "
                                                               << Params.MapParamChar["KeyBonus" + to_string(BonusPlayer[i])] << "),";
        }
        cout << endl;
    }
}

void BonusAdd (CMat & Mat, vector<unsigned> & BonusPlayer, CPosition & Pos, CMyParam Params, vector<CPosition> & Bonus) {
    unsigned Posibility = 3;
    unsigned effect = Random(0, Posibility);
    if (effect == 0) {
        NoActionEffect(Mat, Params, Bonus);
    } else {
        BonusPlayer.push_back(effect);
    }
}

void BonusUse(CMyParam Params, vector<unsigned> & BonusPlayer, CPosition & Pos, CMat & Mat, const char & Action){
    if (Action == Params.MapParamChar["KeyBonus1"]){
        for (unsigned i = 0; i < BonusPlayer.size(); ++i){
            if (BonusPlayer[i] == 1){
                DoubleDeplacementEffect();
                BonusPlayer.erase(BonusPlayer.begin(),BonusPlayer.begin()+i);
            }
        }
    } else if (Action == Params.MapParamChar["KeyBonus2"]){
        for (unsigned i = 0; i < BonusPlayer.size(); ++i){
            cout << i;
            if (BonusPlayer[i] == 2){
                TpAngleEffect(Pos, Params, Mat);
                BonusPlayer.erase(BonusPlayer.begin(),BonusPlayer.begin()+i);
            }
        }
    }
}

void NoActionEffect(CMat & Mat, CMyParam Params, vector<CPosition> & Bonus){
    Bonus.push_back(GenerateBonus(1, Mat, Params, false)[0]);
}
void DoubleDeplacementEffect(){

}
void TpAngleEffect(CPosition & Pos, CMyParam Params, CMat & Mat) {
    unsigned angle = Random(0, 1);
    char car = Mat [Pos.first][Pos.second];
    Mat [Pos.first][Pos.second] = KEmpty;
    if (angle == 0){
        Pos.first = 0;
        Pos.second = 0;
    } else if (angle == 1){
        Pos.first = Params.MapParamUnsigned["NbRow"] - 1;
        Pos.second = Params.MapParamUnsigned["NbColumn"] - 1;
    }
    Mat[Pos.first][Pos.second] = car;
}
