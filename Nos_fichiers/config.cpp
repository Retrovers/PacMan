#include <string>
#include "config.h"
#include "game.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;
void InitParams (CMyParam & Param){

    //Move Keys
    Param.MapParamChar["KeyUp"] = 'z';
    Param.MapParamChar["KeyDown"] = 's';
    Param.MapParamChar["KeyLeft"] = 'q';
    Param.MapParamChar["KeyRight"] = 'd';
    Param.MapParamChar["KeyBonus1"] = 'v';
    Param.MapParamChar["KeyBonus2"] = 'b';
    Param.MapParamChar["TokenP1"] = 'Y';
    Param.MapParamChar["TokenP2"] = 'X';
    Param.MapParamChar["BonusToken"] = 'O';

    //Size of grid — suppose to be a rectangle
    Param.MapParamUnsigned["NbColumn"] = 20;
    Param.MapParamUnsigned["NbRow"] = 10;

    //Display Colors
    Param.MapParamString["ColorP1"] = "Green";
    Param.MapParamString["ColorP2"] = "Red" ;
    Param.MapParamString["BorderColor"] = "BlackBG";
    Param.MapParamString["BonusColor"] = "Yellow";
    Param.MapParamString["Lang"] = "fr";

}

void LoadLang(const string & l, CLang & Lang){
    ifstream File("Nos_fichiers/lang/" + l + ".yaml");
    if (File.is_open()){
        string line;
        AuthorizedKey ak;
        while (getline (File,line)) {
            bool isVal = false;
            string key,val;
            for (unsigned i = 0;i < line.length(); ++i) {
                if (line[i] == ' ' && line[i + 1] == ':' && line[i + 2] == ' '){
                    isVal = true;
                    i = i + 2;
                } else {
                    if (isVal){
                        val += line[i];
                    } else {
                        key += line[i];
                    }
                }
            }
            if (std::find(ak.VLang.begin(), ak.VLang.end(), key)!=ak.VLang.end()){
                Lang.MapLangString[key] = val;
                continue;
            }
            cout << "Impossible de charger le fichier de langue !" << endl;
            exit(1);
        }
    }
}

bool LoadParams (CMyParam & Param, const string & FileName) {
    ifstream File(FileName);
    if (File.is_open()){
        string line;
        AuthorizedKey ak;
        while (getline (File,line)) {
            bool isVal = false;
            string key,val;
            for (unsigned i = 0;i < line.length(); ++i) {
                if (line[i] == ' ' && line[i + 1] == ':' && line[i + 2] == ' '){
                    isVal = true;
                    i = i + 2;
                } else {
                    if (isVal){
                        val += line[i];
                    } else {
                        key += line[i];
                    }
                }
            }
            if (std::find(ak.VParamChar.begin(), ak.VParamChar.end(), key)!=ak.VParamChar.end()){
                Param.MapParamChar[key] = val[0];
                continue;
            }
            if (std::find(ak.VParamString.begin(), ak.VParamString.end(),key)!=ak.VParamString.end()){
                Param.MapParamString[key] = val;
                continue;
            }
            if (std::find(ak.VParamUnsigned.begin(), ak.VParamUnsigned.end(),key)!=ak.VParamUnsigned.end()){
                Param.MapParamUnsigned[key] = stoul(val,nullptr);
                continue;
            }
            cout << "Le fichier config.yaml a ete modifie de facon illegale ! " << endl << "Restaurer une copie d'origine pour pouvoir jouer." << endl;
            exit(1);
        }
        Param.MapParamString["ColorP1"] = KColor.find("K" + Param.MapParamString["ColorP1"])->second;
        Param.MapParamString["BorderColor"] = KColor.find("K" + Param.MapParamString["BorderColor"])->second;
        Param.MapParamString["ColorP2"] = KColor.find("K" + Param.MapParamString["ColorP2"])->second;
        Param.MapParamString["BonusColor"] = KColor.find("K" + Param.MapParamString["BonusColor"])->second;
        Param.MapParamString["CoinsColor"] = KColor.find("K" + Param.MapParamString["CoinsColor"])->second;
        return true;
    } else {
        return false;
    }
}

void GenerateConfig(unsigned lang_id, CMyParam & Param){
    string lang;
    switch (lang_id) {
    case 1:
        lang = "fr";
        break;
    case 2 :
        lang = "en";
        break;
    case 3 :
        lang = "ar";
        break;
    default:
        cerr << "Erreur ! ";
        exit(1);
        break;
    }
    Param.MapParamString["Lang"] = lang;
    ofstream configFile ("config/config.yaml");
    for (auto it = Param.MapParamChar.begin(); it != Param.MapParamChar.end(); ++it){
        configFile << it->first << " : " << it->second << endl;
    }
    for (auto it = Param.MapParamString.begin(); it != Param.MapParamString.end(); ++it){
        configFile << it->first << " : " << it->second << endl;
    }
    for (auto it = Param.MapParamUnsigned.begin(); it != Param.MapParamUnsigned.end(); ++it){
        configFile << it->first << " : " << it->second << endl;
    }
    configFile.close();
}
