#pragma once
#include <string>
#include <assert.h>
#include <iostream>

using std::string;
using std::ostream;
using std::cout;


class Task
{

private:

	string title;
	string descr;
	string type;
	double duration;

public:

	/*
	* Creeaza o noua activitate
	* @param title: Titlul activitatii
	* @param descr: Descrierea activitatii
	* @param type: Tipul activitatii
	* @param duration: Durata activitatii
	*/
	Task() = default;

	Task(const string title, const string descr, const string type, const double duration) :
		title{ title },
		descr{ descr },
		type{ type },
		duration{ duration } {}

	// Copy constructor
	Task(const Task& ot) :
		title{ ot.title },
		descr{ ot.descr },
		type{ ot.type },
		duration{ ot.duration } {/*cout << "COPY CONSTR CALLED.\n";*/};

	// Getters

	string get_title() const;
	string get_descr() const;
	string get_type() const;
	double get_duration() const noexcept;

	// Setters

	void set_title(const string new_title);
	void set_descr(const string new_descr);
	void set_type(const string new_type);
	void set_duration(const double new_duration) noexcept;

	/*
	* Definim actiunea operatorului == asupra elementelor de tip Task
	* @param ot : activitatea cu care vom compara
	* @return (bool) 
	*	true - daca cele doua activitati au acelasi titlu, tip si durata /
	*	false - altfel
	*/
	bool operator==(const Task& ot) const noexcept;

	/*
	* Definim actiunea operatorului << din cadrul stream-ului de output
	* asupra elementelor de tip Task
	*/
	friend ostream& operator<<(ostream& os, const Task& task);

};


// TESTE
void test_get_set();
void test_equal_tasks();