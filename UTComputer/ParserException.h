/**
* \file OperatorException.h
* \brief Gere les exceptions des operateurs
* \author Thibaut ROY, Romain HUBER
* \version 0.1
* \date 12 Juin 2016
*/

#pragma once
#include <exception>
#include <string>

/*! \class ParserException
* \brief Gere les exceptions du parser (tokenizer et parser).
*/
class ParserException : public std::exception {
	std::string info; /*!< \brief Contient la description de l'erreur*/
public:
	/**
	*  \brief Creer l'exception à partir de la description de l'erreur.
	*
	*  \param str : Description de l'erreur.
	*/
	ParserException(const std::string& str) :info(str) {}

	/**
	*  \brief Getter de l'info.
	*
	*  \return std::string : retourne la description de l'erreur.
	*/
	std::string getInfo() const { return info; }
};