#pragma once
#include "Task.h"


class TaskValidator
{

public:

	TaskValidator() = default;

	/*
	* O activitate este valida daca:
	*	Titlul are cel putin trei caractere
	*	Descrierea are cel putin trei caractere
	*	Tipul are cel putin doua caractere
	*	Durata in format HH.MM nu depaseste 12 ore,
	*		nu este negativa si are un numar de minute
	*		ce nu depaseste 59
	*/

	/*
	* Valideaza datele unei activitati
	* @param task_tov : activitate ce urmeaza sa fie validata
	* @throws ValidationException daca datele activitatii nu sunt valide
	*/
	void validate(const Task& task_tov) const;

};


// TESTE
void test_validate_task();