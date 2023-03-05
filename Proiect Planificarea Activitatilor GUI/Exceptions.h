#pragma once
#include <string>
#include <vector>
#include <exception>

using std::string;
using std::vector;


//class VectorException
//{
//
//private:
//
//	string error;
//
//public:
//
//	VectorException(const string vector_error) : error{ vector_error } {};
//
//	string get_error_messages() const
//	{
//		return this->error;
//	}
//
//};


class RepositoryException : public std::exception
{

private:

	string error;

public:

	RepositoryException(const string repo_error) : error{ repo_error } {};

	string get_error_messages() const
	{
		return this->error;
	}

};


class ValidationException : public std::exception
{

private:

	vector<string> errors;

public:

	ValidationException(const vector<string>& errors_list) : errors{ errors_list } {};

	/*
	* Creeaza string-ul cu toate erorile de la validare din vectorul de erori
	* @return (string) un string cu toate mesajele de eroare
	*/
	string get_error_messages() const
	{
		string errors_string = "";

		if (&errors != nullptr)
			for (const auto& err : errors)
			{
				errors_string += err;
			}
			//for (int i = 0; i < errors.size(); i++)
			//	//if (&errors.at(i) != nullptr)
			//	errors_string += errors.at(i);

		return errors_string;
	}

};