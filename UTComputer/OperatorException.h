/**
* \file OperatorException.h
* \brief Gere les exceptions des operateurs
* \author Thibaut ROY, Romain HUBER
* \version 0.1
* \date 12 Juin 2016
*/


#pragma once 

#include <string>

/*! \class OperatorException
* \brief Gere les exceptions des operateurs.
*/
class OperatorException {
	std::string info; /*!< \brief Contient la description de l'erreur*/
public:
	/**
	*  \brief Creer l'exception à partir de la description de l'erreur.
	*
	*  \param str : Description de l'erreur.
	*/
	OperatorException(const std::string& str) :info(str){}

	/**
	*  \brief Getter de l'info.
	*
	*  \return std::string : retourne la description de l'erreur.
	*/
	std::string getInfo() const { return info; }
};