#pragma once
#include "Task.h"
#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;


class TasksRepositoryAbs
{
public:

	TasksRepositoryAbs() noexcept {};
	TasksRepositoryAbs(const TasksRepositoryAbs& ot) = delete;

	/*
	* Adauga in lista de activitati o noua activitate
	* @param new_task : noua activitate ce va fi adaugata in lista
	*/
	virtual void store(const Task& new_task) = 0;

	/*
	* Modifica datele unei activitati din lista de activitati
	* @param index : indexul activitatii ce urmeaza sa fie modificata
	* @param updated_task : activitatea cu datele actualizate
	*/
	virtual void update(const __int64 index, const Task& updated_task) = 0;

	/*
	* Sterge o activitate din lista de activitati
	* @param task_to_remove : activitatea ce va fi eliminata din lista
	* @return (bool) true - daca activitatea a fost stearsa cu succes / false altfel
	*/
	virtual bool remove(const Task& task_to_remove) = 0;

	/*
	* Returneaza lista cu toate activitatile
	* @return Referinta la vectorul ce stocheaza toate activitatile :
	* const vector<Task>&
	*/
	virtual const vector<Task>& get_all_tasks() const noexcept = 0;

	/*
	* Returneaza numarul de activitati existente
	* in lista de activitati
	* @return const int - numar elemente din vector
	*/
	virtual const size_t size() const noexcept = 0;

	/*
	* Determina daca o activitate se afla in lista de activitati
	* @return (int) pozitia activitatii in lista / -1 - daca aceasta
	* nu se afla in lista de activitati
	*/
	virtual const __int64 find(const Task& task_to_search) const = 0;

};


class TasksRepository : public TasksRepositoryAbs
{

private:

	// lista de activitati
	vector<Task> tasks_list;

public:

	TasksRepository() noexcept {};
	TasksRepository(const TasksRepository& ot) = delete;

	/*
	* Adauga in lista de activitati o noua activitate
	* @param new_task : noua activitate ce va fi adaugata in lista
	*/
	void store(const Task& new_task) override;

	/*
	* Modifica datele unei activitati din lista de activitati
	* @param index : indexul activitatii ce urmeaza sa fie modificata
	* @param updated_task : activitatea cu datele actualizate
	*/
	void update(const __int64 index, const Task& updated_task) override;

	/*
	* Sterge o activitate din lista de activitati
	* @param task_to_remove : activitatea ce va fi eliminata din lista
	* @return (bool) true - daca activitatea a fost stearsa cu succes / false altfel
	*/
	bool remove(const Task& task_to_remove) override;

	/*
	* Returneaza lista cu toate activitatile
	* @return Referinta la vectorul ce stocheaza toate activitatile : 
	* const vector<Task>&
	*/
	const vector<Task>& get_all_tasks() const noexcept override;

	/*
	* Returneaza numarul de activitati existente
	* in lista de activitati
	* @return const int - numar elemente din vector
	*/
	const size_t size() const noexcept override;

	/*
	* Determina daca o activitate se afla in lista de activitati
	* @return (int) pozitia activitatii in lista / -1 - daca aceasta
	* nu se afla in lista de activitati
	*/
	const __int64 find(const Task& task_to_search) const override;

};


class TasksRepositoryMAP : public TasksRepositoryAbs
{

private:

	// lista de activitati
	unordered_map<string, Task> tasks_map;
	vector<Task>* vec_tasks;

public:

	TasksRepositoryMAP() 
	{
		vec_tasks = new vector<Task>;
	};
	
	TasksRepositoryMAP(const TasksRepositoryMAP& ot) = delete;
	
	//TasksRepositoryMAP(TasksRepositoryMAP&& ot);
	
	~TasksRepositoryMAP()
	{
		delete vec_tasks;
	}

	/*
	* Adauga in lista de activitati o noua activitate
	* @param new_task : noua activitate ce va fi adaugata in lista
	*/
	void store(const Task& new_task) override;

	/*
	* Modifica datele unei activitati din lista de activitati
	* @param index : indexul activitatii ce urmeaza sa fie modificata
	* @param updated_task : activitatea cu datele actualizate
	*/
	void update(const __int64 index, const Task& updated_task) override;

	/*
	* Sterge o activitate din lista de activitati
	* @param task_to_remove : activitatea ce va fi eliminata din lista
	* @return (bool) true - daca activitatea a fost stearsa cu succes / false altfel
	*/
	bool remove(const Task& task_to_remove) override;

	/*
	* Returneaza lista cu toate activitatile
	* @return Referinta la vectorul ce stocheaza toate activitatile :
	* const vector<Task>&
	*/
	const vector<Task>& get_all_tasks() const noexcept override;

	/*
	* Returneaza numarul de activitati existente
	* in lista de activitati
	* @return const int - numar elemente din vector
	*/
	const size_t size() const noexcept override;

	/*
	* Determina daca o activitate se afla in lista de activitati
	* @return (int) pozitia activitatii in lista / -1 - daca aceasta
	* nu se afla in lista de activitati
	*/
	const __int64 find(const Task& task_to_search) const override;

};


// TESTE
void test_repo_store();
void test_repo_update();
void test_repo_remove();
void test_repo_size();
void test_repo_find();