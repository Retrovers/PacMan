#ifndef COINS_H
#define COINS_H

#include <Nos_fichiers/type.h>

std::vector<CPosition> GenerateCoins (const unsigned number, CMat & Mat, CMyParam Params, bool wait = true);
void CoinsAdd(CMat& Mat, std::vector<unsigned>& PlayerCoins, unsigned PlayerNumber, std::vector<CPosition>& Coins, CMyParam Params);

#endif // COINS_H
