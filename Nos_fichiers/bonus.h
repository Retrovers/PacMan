#ifndef BONUS_H
#define BONUS_H
#include <Nos_fichiers/type.h>

/*!
 * \brief Genere tous les bonus
 * \param[out] CMat Mat retourne avec la map avec les bonus generé
 * \param[out] vector<CPosition> donne le vecteur avec les coordonée de tous les bonus
 * \param[in] CMyParam Params variables donnant acces au parametres
 * \param[in] bool wait = true variable qui dit si on doit mettre de la latence entre les generations de nombre aleatoire
 * @fn std::vector<CPosition> GenerateBonus (const unsigned number, CMat & Mat, CMyParam Params, bool wait = true);
 */
std::vector<CPosition> GenerateBonus (const unsigned number, CMat & Mat, CMyParam Params, bool wait = true);

/*!
 * \brief Ajout de bonus dans le vector du player
 * \param[out] std::vector<unsigned> BonusPlayer retourne le vecteur du player avec le bonus qu'il a gagné
 * \param[in] CLang ParamLang contient la map correspondant au traduction
 * \param[out] std::vector<CPosition> Bonus Retourne les bonus disponibles
 * \param[out] CPosition & Pos Retourne une position
 * \param[out] CMat & Mat retourne la matrice
 * @fn void BonusAdd (CMat & Mat, std::vector<unsigned> & BonusPlayer, CPosition & Pos, CMyParam Params, std::vector<CPosition> & Bonus)
 */
void BonusAdd (CMat & Mat, std::vector<unsigned> & BonusPlayer, CPosition & Pos, CMyParam Params, std::vector<CPosition> & Bonus);

/*!
 * \brief Regenere un nouveau bonus et l'ajoute au vecteur bonus
 * \param[in] CMyParam Params variables donnant acces au parametres
 * \param[out] CMat Mat retourne la matrice avec un nouveau bonus
 * \param[out] std::vector<CPosition> Bonus retourne le vecteur bonus avec un nouveau bonus
 * @fn void NoActionEffect (CMat & Mat, CMyParam Params, std::vector<CPosition> & Bonus);
 */
void NoActionEffect (CMat & Mat, CMyParam Params, std::vector<CPosition> & Bonus);

/*!
 * \brief Teleporte le jouer dans un des coins de la carte
 * \param[in] CMyParam Params variables donnant acces au parametres
 * \param[out] CMat Mat retourne la matrice avec la nouvelles positions du joueur
 * \param[out] CPosition & Pos Retourne la nouvelle position
 * @fn void TpAngleEffect(CPosition & Pos,const CMyParam Params, CMat & Mat);
 */
void TpAngleEffect(CPosition & Pos,const CMyParam Params, CMat & Mat);

/*!
 * \brief Gere l'activation du bonus
 * \param[in] CMyParam Params variables donnant acces au parametres
 * \param[in] const char & Action donne la touche qui a etait tappé par le joueur
 * \param[out] std::vector<unsigned> & BonusPlayer retourne le veteurs avec les bonus attribué au joueur
 * \param[out] CPosition & Pos Retourne la nouvelle position
 * \param[out] CMat Mat retourne la matrice avec la nouvelles positions du joueur ou avec les modifications
 * \param[out] bool & TripleMove retourne un boolean si le triple mouvement est activé
 * @fn void BonusUse(CMyParam Params, std::vector<unsigned> & BonusPlayer, CPosition & Pos, CMat & Mat, const char & Action, bool & TripleMove);
 */
void BonusUse(CMyParam Params, std::vector<unsigned> & BonusPlayer, CPosition & Pos, CMat & Mat, const char & Action, bool & TripleMove);
/*!

 * \brief Affiche les bonus disponlibles pour le joueur
 * \param[in] std::vector<unsigned> & BonusPlayer donne le vecteurs contenant les bonus du joueur
 * \param[in] CLang & ParamLang contient la map correspondant au traduction
 * \param[in] CMyParam Params variables donnant acces au parametres
 * @fn void ShowBonusAvailable(const std::vector<unsigned> & BonusPlayer, CMyParam & Params, const CLang& ParamLang);
 */
void ShowBonusAvailable(const std::vector<unsigned> & BonusPlayer, CMyParam & Params, const CLang& ParamLang);

#endif // BONUS_H
