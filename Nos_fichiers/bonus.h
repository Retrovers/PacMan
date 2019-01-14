#ifndef BONUS_H
#define BONUS_H
#include <Nos_fichiers/type.h>

std::vector<CPosition> GenerateBonus (const unsigned number, CMat & Mat, CMyParam Params, bool wait = true);
void BonusAdd (CMat & Mat, std::vector<unsigned> & BonusPlayer, CPosition & Pos, CMyParam Params, std::vector<CPosition> & Bonus);
void NoActionEffect (CMat & Mat, CMyParam Params, std::vector<CPosition> & Bonus);
void DoubleDeplacementEffect();
void TpAngleEffect(CPosition & Pos,const CMyParam Params, CMat & Mat);
void BonusUse(CMyParam Params, std::vector<unsigned> & BonusPlayer, CPosition & Pos, CMat & Mat, const char & Action, bool & TripleMove);
void ShowBonusAvailable(const std::vector<unsigned> & BonusPlayer, CMyParam & Params, const CLang& ParamLang);

#endif // BONUS_H
