#pragma once
#include "Service.h"
#include <iostream>


class UIConsole
{

private:

	TasksService& srv;

public:

	UIConsole(TasksService& task_service) noexcept : srv{ task_service } {};

	UIConsole(const UIConsole& ot) = delete;

	/*
	* Declanseaza rularea meniului programului
	*/
	void show_ui();

	/*
	* Printeaza meniul programului in consola
	*/
	void print_menu() const;

	/*
	* Printeaza meniul pentru lista de activitati curente
	*/
	void print_menu_crt_tasks() const;

	/*
	* Meniul listei de activitati curente
	*/
	void menu_current_tasks();

	/*
	* UI adauga activitate in lista de activitati curente
	*/
	void ui_add_task_ct();

	/*
	* UI adauga aleator activitati in lisa activitatilor curente
	*/
	void ui_add_random_tasks_ct();

	/*
	* Citeste optiunea utilizatorului
	*/
	const int get_option() const;

	/*
	* Printeaza lista de activitati
	*/
	void print_list(const vector<Task>& task_list) const;

	/*
	* UI adauga activitate
	*/
	void ui_add_task();

	/*
	* UI modifica activitate
	*/
	void ui_modify_task();

	/*
	* UI sterge activitate
	*/
	void ui_delete_task();

	/*
	* UI cautare activitate
	*/
	void ui_search_task() const;

	/*
	* UI filtrare
	*/
	void ui_filter_tasks() const;

	/*
	* UI sortare
	*/
	void ui_sort_tasks() const;

	/*
	* Afiseaza raport frecventa tip
	*/
	void ui_get_raport() const;

	/*
	* UI exporta lista de activitati in fisier
	*/
	void ui_export_list() const;

	/*
	* Populeaza lista de activitati
	*/
	void populate_list();

};