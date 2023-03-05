#pragma once
#include "Task.h"
#include <vector>
#include "Observer.h"

using std::vector;


class CurrentTasks: public Observable
{
protected:

	// lista activitatilor curente
	vector<Task> current_tasks;

public:

	/*
	* Constructorul default pentru clasa
	*/
	CurrentTasks() = default;

	/*
	* Returneaza numarul de activitati din lista curenta
	* @return const int - numar elemente din vector
	*/
	const size_t size() const noexcept;

	/*
	* Adauga o activitate in lista de activitati curente
	* @param task_to_add : activitatea ce se va adauga in lista curenta
	*/
	void store_task_ct(const Task& task_to_add);

	/*
	* Adauga aleator un numar de activitati in lista de activitati curente
	* @param available_tasks : lista activitatilor din care se vor extrage activitatile
	* @param count : numarul de activitati ce vor fi adaugate
	*/
	void store_random_tasks(vector<Task> available_tasks, const int count);

	/*
	* Goleste lista de activitati curente
	*/
	void clear_all_ct() noexcept;

	/*
	* Returneaza lista cu toate activitatile curente
	* @return Referinta la vectorul ce stocheaza toate activitatile curente :
	* const vector<Task>&
	*/
	const vector<Task>& get_current_tasks() const noexcept;

	/*
	* Exporta lista de activitati curente in fisier
	* @param file_name - numele fisierului HTML in care se va face exportul
	*/
	virtual void export_list(string file_name) const;

};


class CurrentTasksCVS : public CurrentTasks
{
public:
	void export_list(string file_name) const override;
};


// TESTE
void test_store_task_ct();
void test_clear_all_ct();