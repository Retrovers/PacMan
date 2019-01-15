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
} // GenerateCoins()

void CoinsAdd(CMat& Mat, vector<unsigned>& PlayerCoins ,unsigned PlayerNumber, vector<CPosition>& Coins, CMyParam Params){
    PlayerCoins[PlayerNumber] = PlayerCoins[PlayerNumber] + 1;
    Coins.push_back(GenerateCoins(1, Mat, Params , false)[0]);
}

void CoinsKill(unsigned Killer, std::vector<unsigned> & PlayersCoins, CPosition & PosPlayer1, CPosition& PosPlayer2,CMat & Mat, CMyParam Params) {
    if (Killer == 0){
        PlayersCoins[Killer] += PlayersCoins[1];
        PlayersCoins[1] = 0;
        PosPlayer2.first = Params.MapParamUnsigned["NbRow"] - 1;
        PosPlayer2.second = 0;
        Mat [PosPlayer2.first][PosPlayer2.second] = Params.MapParamChar["TokenP2"];
    } else {
        PlayersCoins[Killer] += PlayersCoins[0];
        PlayersCoins[0] = 0;
        PosPlayer1.first = 0;
        PosPlayer1.second = Params.MapParamUnsigned["NbCollumn"] - 1;
        Mat [PosPlayer1.first][PosPlayer1.second] = Params.MapParamChar["TokenP1"];
    }
}
