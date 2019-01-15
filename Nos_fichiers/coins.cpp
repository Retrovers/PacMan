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

vector<CPosition> GenerateCoins (const unsigned number, CMat & Mat, CMyParam Params, bool wait){
    unsigned row, collumn;
    vector<CPosition> CoinsCord(number);
    for (unsigned i = 0; i < number; ++i){
        if (wait) sleep(0.5);
        collumn = Random(1, Params.MapParamUnsigned["NbColumn"] - 1);
        if (wait) sleep(0.5);
        row = Random(1, Params.MapParamUnsigned["NbRow"] - 1);
        Mat[row][collumn] = Params.MapParamChar["CoinsToken"];
        CPosition CoinsPos;
        CoinsPos.first = row;
        CoinsPos.second = collumn;
        CoinsCord[i] = CoinsPos;
    }
    return CoinsCord;
}

void CoinsAdd(CMat& Mat, vector<unsigned>& PlayerCoins ,unsigned PlayerNumber, vector<CPosition>& Coins, CMyParam Params){
    PlayerCoins[PlayerNumber] = PlayerCoins[PlayerNumber] + 1;
    Coins.push_back(GenerateCoins(1, Mat, Params , false)[0]);
}

void CoinsKill(unsigned Killer, std::vector<unsigned> & PlayersCoins, CPosition & PosPlayer1, CPosition& PosPlayer2,CMat & Mat, CMyParam Params) {
    if (Killer == 0){
        PlayersCoins[Killer] += PlayersCoins[0];
        PlayersCoins[0] = 0;
        TpAngleEffect(PosPlayer2, Params, Mat);
    } else {
        PlayersCoins[Killer] += PlayersCoins[1];
        PlayersCoins[1] = 0;
        TpAngleEffect(PosPlayer1, Params, Mat);
    }
}
