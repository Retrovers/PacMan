#ifndef CONFIG_H
#define CONFIG_H

/**
 * \file config.h
 * \brief Paramters' definition and associated functions
 * \author Alain Casali
 * \author Marc Laporte
 * \version 1.0
 * \date 18 décembre 2018
 */

#include "type.h"

/**
 * @brief Initialize the set of parameters from scratch
 * @param[out] Param : List of usefull parameters
 * @fn void InitParams (CMyParam & Param);
 */

void InitParams (CMyParam & Param);

/**
 * @brief Load the set of parameters from a YAML file
 * @param[out] Param : List of usefull parameters
 * @param[in] FileName : Path to the file to load
 * @fn void LoadParams (CMyParam & Param);
 * @return 0 if everything is OK, return 2 if it can't load the file
 */

bool LoadParams (CMyParam & Param, const std::string & FileName);
void LoadLang(const std::string & l, CLang & Lang);
void GenerateConfig(unsigned lang, CMyParam & Param);


#endif // PARAMS_H
