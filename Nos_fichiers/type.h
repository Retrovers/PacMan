#ifndef TYPE_H
#define TYPE_H
/*!
 * \file type.h
 * \brief Definition of usefull types or aliases for the project
 * \author Alain Casali
 * \author Marc Laporte
 * \version 1.0
 * \date 18 décembre 2018
 */

#include <string>
#include <vector>
#include <map>

/**
 * @brief CVLine : alias to a line of the matrix
 */
typedef std::vector <char> CVLine;

/**
 * @brief CMat : alias to a game grid type
 * @typedef std::vector <CVLine> CMat;
 */
typedef std::vector <CVLine> CMat;

/**
 * @brief CPosition : a pair gathering the coordinates in the grid
 */
typedef std::pair <unsigned, unsigned> CPosition;



/**
 * @brief Struct containing all the authorized keys in the struct CMyParam
 */

/**
 * @brief KAuthorizedKey
 */
struct AuthorizedKey {
/* List of authorized key for the type char in a struct CMyParam*/
const std::vector <std::string> VParamChar {"KeyUpP1", "KeyDownP1", "KeyLeftP1", "KeyRightP1", "TokenP1","KeyUpP2",
                                            "KeyDownP2", "KeyLeftP2", "KeyRightP2","TokenP2", "BonusToken", "KeyBonus1", "KeyBonus2", "KeyBonus1", "KeyBonus2", "CoinsToken"};
/* List of authorized key for the type string in a struct CMyParam*/
const std::vector<std::string> VParamString {"BorderColor", "RowColor", "IndexColor", "MyColor", "ColorP1", "ColorP2", "Lang", "BonusColor", "CoinsColor"};
/* List of authorized key for the type unsigned in a struct CMyParam*/
const std::vector<std::string> VParamUnsigned {"GridSize", "NbRow", "NbColumn", "CoinsLimit"};

const std::vector<std::string> VLang {"WelcomeMenu", "GameMenu", "SelectChoiceForGameModMenu", "RandomMapMenu", "CustomMapMenu", "AboutMenu",
                                      "SelectChoiseForGameModMenu", "ExitMenu", "Goodbye", "About", "HowExitAbout", "AboutPage", "MenuPage",
                                     "RandomGamePage", "Player1", "InstructionForPlayerName", "Player2", "ConfirmChoise", "Bonus_1", "Bonus_2" ,
                                     "PlayerPlay", "EnterMove", "Step", "NoWinner", "Congrelation", "PlayerWin", "WantRestart", "BonusAvailabe", "Press",
                                     "CustomMapPage", "InstructionForSelectCustomMap", "MapsNotFound", "SelectCustomMap", "Command", "Top", "Right", "Left", "Back", "CommandPage"};
};

/**
  * @brief KColor : map between the "human" color and its correspondence for the Unix terminal
  */

const std::map <std::string, std::string> KColor
{
  {"KReset", "0"},
  {"KBlack", "30"},
  {"KRed", "31"},
  {"KGreen", "32"},
  {"KYellow", "33"},
  {"KBlue", "34"},
  {"KMAgenta", "35"},
  {"KCyan", "36"},
  {"KBlackBG", "40"},

};

/**
 * @brief KEmpty : character for an empty cell
 */
const char KEmpty        = ' ';


#include <map>

struct CMyParam {
std::map <std::string, char> MapParamChar;
std::map <std::string, unsigned> MapParamUnsigned;
std::map <std::string, std::string> MapParamString;
};

struct CLang {
    std::map <std::string, std::string> MapLangString;
};


#endif // TYPE_H
