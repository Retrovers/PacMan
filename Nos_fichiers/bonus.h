#ifndef BONUS_H
#define BONUS_H
#include <Nos_fichiers/type.h>

std::vector<CPosition> GenerateBonus (const unsigned number, CMat & Mat, CMyParam Params);
void BonusAdd (CMat & Mat, std::vector<unsigned> & BonusPlayer, CPosition & Pos, CMyParam Params);
void NoActionEffect (CMat & Mat, CMyParam Params);
void DoubleDeplacementEffect();
void TpAngleEffect(CPosition & Pos, CMyParam & Params, CMat & Mat);
void BonusUse(const unsigned& effect);
void ShowBonusAvailable(const std::vector<unsigned> & BonusPlayer, CMyParam & Params, const CLang& ParamLang);

#endif // BONUS_H
