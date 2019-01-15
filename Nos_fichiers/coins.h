#ifndef COINS_H
#define COINS_H

#include <Nos_fichiers/type.h>

/*!
 * \brief Genere tous les bonus
 * \param[out] CMat Mat retourne avec la map avec les pieces generée
 * \param[out] vector<CPosition> donne le vecteur avec les coordonée de toutes les pieces
 * \param[in] CMyParam Params variables donnant acces au parametres
 * \param[in] bool wait = true variable qui dit si on doit mettre de la latence entre les generations de nombre aleatoire
 * @fn std::vector<CPosition> GenerateCoins (const unsigned number, CMat & Mat, CMyParam Params, bool wait = true);
 */
std::vector<CPosition> GenerateCoins (const unsigned number, CMat & Mat, CMyParam Params, bool wait = true);

/*!
 * \brief Ajout de bonus dans le vector du player
 * \param[out] std::vector<unsigned> BonusPlayer retourne le vecteur du player avec le bonus qu'il a gagné
 * \param[in] CLang ParamLang contient la map correspondant au traduction
 * \param[out] std::vector<CPosition> Bonus Retourne les bonus disponibles
 * \param[out] CPosition & Pos Retourne une position
 * \param[out] CMat & Mat retourne la matrice
 * @fn void CoinsAdd(CMat& Mat, std::vector<unsigned>& PlayerCoins, unsigned PlayerNumber, std::vector<CPosition>& Coins, CMyParam Params);
 */
void CoinsAdd(CMat& Mat, std::vector<unsigned>& PlayerCoins, unsigned PlayerNumber, std::vector<CPosition>& Coins, CMyParam Params);

void CoinsKill(unsigned Killer, std::vector<unsigned> & PlayersCoins, CPosition & PosPlayer1, CPosition
               & PosPlayer2,CMat & Mat, CMyParam Params);
#endif // COINS_H
