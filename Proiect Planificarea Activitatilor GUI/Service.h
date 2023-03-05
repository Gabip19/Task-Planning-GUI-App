#pragma once
#include "Repository.h"
#include "Validator.h"
#include "CurrentTasks.h"
#include "Undo.h"
#include <map>

using std::map;
using std::unique_ptr;


class TasksService
{

private:

	TasksRepositoryAbs& repo;
	TaskValidator& val;

	CurrentTasks& current_tasks_repo;

	vector<unique_ptr<UndoAction>> undo_actions;

public:

	TasksService(TasksRepositoryAbs& task_repo, TaskValidator& task_val, CurrentTasks& cos) noexcept :
		repo{ task_repo },
		val{ task_val },
		current_tasks_repo{ cos }{};

	TasksService(const TasksService& ot) = delete;

	/*
	* Adauga in lista de activitati o noua activitate
	* @param title : titlul activitatii ce se va adauga
	* @param descr : descrierea activitatii ce se va adauga
	* @param type : tipul activitatii ce se va adauga
	* @param duration : durata activitatii ce se va adauga
	* @throw RepositoryException daca activitatea noua exista deja in lista
	* @throw ValidationException daca datele noii activitati nu sunt valide
	*/
	void add_task(string title, string descr, string type, double duration);

	/*
	* Modifica datele unei activitati din lista de activitati
	* @param title : titlu activitatii ce va fi modificata
	* @param type : tipul activitatii ce va fi modificata
	* @param duration : durata activitatii ce va fi modificata
	* @param new_descr : noua descriere a activitatii
	* @param new_type : noul tip al activitatii
	* @param new_duration : noua durata a activitatii
	* @throw RepositoryException daca valorile initiale nu corespund unei activitati din lista
	* @throw RepositoryException daca noile valori corespund unei activitati deja prezente in lista
	* @throw ValidationException daca datele noii activitati nu sunt valide
	*/
	void modify_task(string title, string type, double duration, string new_descr, string new_type, double new_duration);

	/*
	* Sterge din lista de activitati o activitate data
	* @param title : titlul activitatii ce se va sterge
	* @param type : tipul activitatii ce se va sterge
	* @param duration : durata activitatii ce se va sterge
	* @throw RepositoryException daca activitatea nu exista in lista
	* @throw ValidationException daca datele activitatii date nu sunt valide
	*/
	void delete_task(string title, string type, double duration);

	/*
	* Returneaza lista cu toate activitatile
	* @return Referinta la vectorul ce stocheaza toate activitatile :
	* const vector<Task>&
	*/
	const vector<Task>& get_all_tasks() const noexcept;

	/*
	* Returneaza numarul de activitati existente
	* in lista de activitati
	* @return const int - numar elemente din vector
	*/
	const size_t size() const noexcept;

	/*
	* Returneaza numarul de activitati existente
	* in lista de activitati
	* @return const int - numar elemente din vector
	*/
	const size_t size_ct() const noexcept;

	/*
	* Cauta in lista de activitati o activitate cu atributele date
	* @param title : titlul activitatii ce se cauta in lista
	* @param type : tipul activitatii ce se cauta in lista
	* @param duration : duration activitatii ce se cauta in lista
	* @return Referinta la activitatea cautata daca datele introduse
	* corespund unei activitati din lista
	* @throw RepositoryException daca nu exista in lista o activitate cu datele date
	*/
	const Task search_task(string title, string type, double duration) const;

	/*
	* Filtreaza lista de activitati dupa o secventa din descrierea activitatilor
	* @param sequence : secventa a carei aparitie se verifica in cadrul descrierii activitatilor
	* @param filtered_list : referinta la vectorul in care se va creea lista de activitati filtrata
	*/
	void filter_by_descr(string sequence, vector<Task>& filtered_list) const;
	
	/*
	* Filtreaza lista de activitati dupa tipul acestora
	* @param filter_type : tipul dupa care se vor filtra activitatile
	* @param filtered_list : referinta la vectorul in care se va creea lista de activitati filtrata
	*/
	void filter_by_type(string filter_type, vector<Task>& filtered_list) const;

	/*
	* Sorteaza lista de activitati in functie de o optiune data
	* @param sort_list : Lista ce urmeaza a fi sortata
	* @param option : optiunea care decide dupa ce se va face sortarea
	* 1 - sortarea se face alfabetic dupa titlu
	* 2 - sortarea se face dupa lungimea descrierii
	* 3 - sortarea se face crescator dupa durata si alfabetic dupa tip
	* @return Lista ce contine activitatile sortate conform optiunii utilizatorului
	*/
	const vector<Task> general_sort(vector<Task> sort_list, const int option);

	/*
	* Returneaza lista cu toate activitatile curente
	* @return Referinta la vectorul ce stocheaza toate activitatile curente :
	* const vector<Task>&
	*/
	const vector<Task>& get_crt_tasks() const noexcept;

	/*
	* Adauga o activitate dupa titlu in lisa curenta de activitati
	* @param title : titlul activitatii ce se va adauga in lista curenta
	* @throw RepositoryException daca nu exista o activitate cu titlul dat in lista
	*/
	void add_task_ct(string title);

	/*
	* Adauga aleator un numar de activitati in lista de activitati curente
	* @param count : numarul de activitati ce vor fi adaugate
	*/
	void add_random_tasks_ct(const int count);

	/*
	* Sterge toate activitatile din lista curenta de activitati
	*/
	void empty_current_list();

	/*
	* Adauga un observer pt activitatile curente
	*/
	void add_observer(Observer* obs);

	/*
	* Sterge un observer al activitatilor curente
	*/
	void remove_observer(Observer* obs);

	/*
	* Exporta lista de activitati curente in fisier
	* @param file_name - numele fisierului HTML in care se va face exportul
	*/
	void export_current_list(string file_name) const;

	/*
	* Calculeaza frecventa unui anumit tip de activitate
	*/
	map<string, int> get_raport() const;

	/*
	* Reseteaza lista de activitati la cea anterioara ultimei operatii
	* ce a modificat-o
	* @throw RepositoryException daca nu se mai poate face undo
	*/
	void undo();

	/*
	* Populeaza lista de activitati
	*/
	void populate_list();

};


// TESTE
void test_srv_size();
void test_srv_add_task();
void test_srv_modifiy_task();
void test_srv_delete_task();
void test_srv_filter_descr();
void test_srv_filter_type();
void test_srv_search_task();
void test_srv_sort();
void test_size_ct();
void test_add_task_ct();
void test_empty_current_list();
void test_add_random_tasks_ct();
void test_export_ct_list();
void test_get_raport();
void test_undo();