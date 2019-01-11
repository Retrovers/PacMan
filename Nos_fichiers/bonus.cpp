#include <iostream>
#include <Nos_fichiers/gamemod.h>
#include <string>
#include <Nos_fichiers/gridmanagement.h>
#include <Nos_fichiers/bonus.h>

using namespace std;

vector<CPosition> GenerateBonus (const unsigned number, CMat & Mat, CMyParam Params){
    unsigned row, collumn;
    vector<CPosition> BonusCord(number);
    srand(time(NULL));
    for (unsigned i = 0; i < number; ++i){
        collumn = rand()%(Params.MapParamUnsigned["NbColumn"] - 1 + 1) + 1;
        row = rand()%(Params.MapParamUnsigned["NbRow"] - 1 + 1) + 1;
        Mat[row][collumn] = Params.MapParamChar["BonusToken"];
        CPosition BonusPos;
        BonusPos.first = row;
        BonusPos.second = collumn;
        BonusCord[i] = BonusPos;
    }
    return BonusCord;
}

void BonusAdd (vector<unsigned>, CMat & Mat, CMyParam Param) {
    unsigned Posibility = 3;
    unsigned effect = rand()%(Posibility - 1 + 1) + 1;
    if (effect = 0) {
        NoActionEffect(Mat, Params);
    } else {
        BonusPlayer.resize(BonusPlayer.size() +1 );
        BonusPlayer[BonusPlayer.size() - 1] = effect;
    }
}

void BonusUse(const unsigned effect, CMat & Mat, vector<unsigned> BonusPlayer, CPosition & Pos, CMyParam Params){
    switch (effect) {
    case 1 :
        DoubleDeplacementEffect();
        break;
    case 2 :
        TpAngleEffect(Pos);
        break;
    default:
        break;
    }
}

void NoActionEffect(CMat & Mat, CMyParam Params){
    GenerateBonus(1, Mat, Params);
}
void DoubleDeplacementEffect(){

}
void TpAngleEffect(CPosition & Pos, CMyParam & Params, CMat & Mat) {
    unsigned angle = rand() % 2;
    char car = Mat [Pos.first][Pos.second];
    Mat [Pos.first][Pos.second] = KEmpty;
    if (angle == 0){
        Pos.first = Params.MapParamUnsigned["NbColumn"] - 1;
        Pos.second = 0;
    } else if (angle == 1){
        Pos.first = 0;
        Pos.second = Params.MapParamUnsigned["NbRow"] - 1;
    }
    Mat [Pos.first][Pos.second] = car;
}
