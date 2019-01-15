#ifndef GAMEMOD_H
#define GAMEMOD_H

#include <Nos_fichiers/type.h>

void About(CLang ParamLang);
void PlayRandomGameMod(CLang ParamLang, CMyParam Params);
void PlayCustomMapMod(CLang ParamLang);
bool MoveToken (CMat & Mat, const char & Move, CPosition & Pos, CMyParam Params, bool & TripleMove);

void Command(CLang ParamLang, CMyParam Params);
#endif // GAMEMOD_H
