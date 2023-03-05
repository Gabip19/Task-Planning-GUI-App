#include "Service.h"
#include "Exceptions.h"
#include <algorithm>
#include <vector>
#include <fstream>

using std::sort;
using std::copy_if;
using std::back_inserter;
using std::make_unique;


void TasksService::add_task(string title, string descr, string type, double duration)
{
	Task new_task{ title, descr, type, duration };
	val.validate(new_task);

	const auto& all_tasks = get_all_tasks();
	const auto& it = std::find(all_tasks.begin(), all_tasks.end(), new_task);

	if (it == all_tasks.end())
	{
		repo.store(new_task);
		undo_actions.push_back(make_unique<UndoAdd>(repo, new_task));
	}
	else
	{
		throw RepositoryException("Activitatea data exista deja in lista.\n");
	}
}


void TasksService::modify_task(string title, string type, double duration, string new_descr, string new_type, double new_duration)
{
	Task task_to_update{ title, "   ", type, duration };
	
	const __int64 index = repo.find(task_to_update);

	if (index != -1)
	{
		task_to_update = repo.get_all_tasks().at(index);
		Task updated_task{ title, new_descr, new_type, new_duration };

		if (repo.find(updated_task) != -1)
		{
			throw RepositoryException("Noile date corespund deja unei activitati din lista.");
		}

		val.validate(updated_task);
		repo.update(index, updated_task);

		undo_actions.push_back(make_unique<UndoModify>(repo, task_to_update, updated_task));
	}
	else
	{
		throw RepositoryException("Activitatea data nu exista in lista.\n");
	}
}


void TasksService::delete_task(string title, string type, double duration)
{
	Task task_to_del{ title, "   ", type, duration };
	val.validate(task_to_del);

	const auto index = repo.find(task_to_del);
	if (index >= 0)
	{
		task_to_del = repo.get_all_tasks().at(index);
		repo.remove(task_to_del);
		
		undo_actions.push_back(make_unique<UndoRemove>(repo, task_to_del));
		return;
	}
	throw RepositoryException("Activitatea data nu exista in lista.\n");
}


const vector<Task>& TasksService::get_all_tasks() const noexcept
{
	return repo.get_all_tasks();
}


const size_t TasksService::size() const noexcept
{
	return repo.size();
}


const size_t TasksService::size_ct() const noexcept
{
	return current_tasks_repo.size();
}


const Task TasksService::search_task(string title, string type, double duration) const
{
	Task task_to_search{ title, "   ", type, duration };
	val.validate(task_to_search);

	const auto& it = std::find(get_all_tasks().begin(), get_all_tasks().end(), task_to_search);

	if (it != get_all_tasks().end())
	{
		if (&repo != nullptr)
		{
			return *it;
		}
	}
	throw RepositoryException("Lista nu contine o activitate cu datele date.\n");
}


void TasksService::filter_by_descr(string sequence, vector<Task>& filtered_list) const
{
	filtered_list.clear();
	const vector<Task>& all_tasks = repo.get_all_tasks();

	copy_if(
		all_tasks.begin(), 
		all_tasks.end(), 
		back_inserter(filtered_list), 
		[sequence](const Task& task) {
			return task.get_descr().find(sequence) != string::npos;
		}
	);
}


void TasksService::filter_by_type(string filter_type, vector<Task>& filtered_list) const
{
	filtered_list.clear();
	const vector<Task>& all_tasks = repo.get_all_tasks();

	copy_if(
		all_tasks.begin(),
		all_tasks.end(),
		back_inserter(filtered_list),
		[filter_type](const Task& task) {
			return task.get_type() == filter_type;
		}
	);
}


const vector<Task> TasksService::general_sort(vector<Task> sort_list, const int option)
{
	if (option == 1)
	{
		sort(
			sort_list.begin(),
			sort_list.end(),
			[](const Task& t1, const Task& t2) {
				return (t1.get_title() < t2.get_title());
			}
		);
	}
	else if (option == 2)
	{
		sort(
			sort_list.begin(),
			sort_list.end(),
			[](const Task& t1, const Task& t2) {
				return (t1.get_descr().length() < t2.get_descr().length());
			}
		);
	}
	else
	{
		sort(
			sort_list.begin(),
			sort_list.end(),
			[](const Task& t1, const Task& t2) {
				if (t1.get_duration() < t2.get_duration())
					return true;
				else if (t1.get_duration() == t2.get_duration())
				{
					if (t1.get_type() < t2.get_type())
						return true;
					else return false;
				}
				return false;
			}
		);
	}

	return sort_list;
}


const vector<Task>& TasksService::get_crt_tasks() const noexcept
{
	return current_tasks_repo.get_current_tasks();
}


void TasksService::add_task_ct(string title)
{
	const vector<Task>& all_tasks = get_all_tasks();
	
	const auto& it = std::find_if(
		all_tasks.begin(),
		all_tasks.end(),
		[title](const Task& task) {
			return task.get_title() == title;
		}
	);
	
	if (it != all_tasks.end())
	{
		const vector<Task>& current_tasks = current_tasks_repo.get_current_tasks();
		
		const auto& it2 = std::find(current_tasks.begin(), current_tasks.end(), *it);
		
		if (it2 == current_tasks.end())
		{
			current_tasks_repo.store_task_ct(*it);
		}
		else
			throw RepositoryException("Activitatea cu titlul se afla deja in lista curenta.");
	}
	else
		throw RepositoryException("Nu exista activitati cu numele dat in lista.");
}


void TasksService::add_random_tasks_ct(const int count)
{
	current_tasks_repo.store_random_tasks(get_all_tasks(), count);
}


void TasksService::empty_current_list()
{
	current_tasks_repo.clear_all_ct();
}


void TasksService::add_observer(Observer* obs)
{
	current_tasks_repo.add_observer(obs);
}


void TasksService::remove_observer(Observer* obs)
{
	current_tasks_repo.remove_observer(obs);
}


void TasksService::export_current_list(string file_name) const
{
	current_tasks_repo.export_list(file_name);
}


map<string, int> TasksService::get_raport() const
{
	map<string, int> type_freq;
	for (const auto& task : get_all_tasks())
	{
		if (type_freq.find(task.get_type()) == type_freq.end())
		{
			type_freq[task.get_type()] = 1;
		}
		else
		{
			type_freq[task.get_type()] += 1;
		}
	}
	return type_freq;
}


void TasksService::undo()
{
	if (undo_actions.empty())
		throw RepositoryException("\tNu se mai poate face undo.\n");

	undo_actions.back()->do_undo();
	undo_actions.pop_back();
}


void TasksService::populate_list()
{
	add_task("Nume vechi", "Cuvinte", "bowling", 3.2);
	add_task("Nume nou", "Descriere mai lunga", "teme", 0.05);
	add_task("Alte activitati", "Fara descriere", "scoala", 10.11);
	add_task("Task nou", "Alta descriere", "sport", 10.11);
	add_task("Nu mai am idei", "Descriere activitate", "facultate", 0.10);
	add_task("Alt titlu", "Activitatea de alt tip", "alt tip2", 3.2);
	add_task("Fara teme", "Nu am idei", "alte teme", 10.5);
	add_task("Titlu", "Cuvinte pentru activitatetete", "alt tip", 3.2);
	add_task("Activitate scoala", "Teme pentru facultate", "alte teme", 2.12);
	add_task("Inca un task", "Vineri seara", "bowling", 1.21);
	add_task("Curs geometrie", "Scriu doar chestii random", "sport", 0.20);
	add_task("Nume iar", "Nu mai am idei", "facultate", 5.12);
	add_task("Generez taskuri", "Proiect la OOP", "teme", 0.15);
	add_task("Populez lista", "8 prezente la sport", "sport", 11.0);
	add_task("Titlu de activitate", "Dau test la AG", "facultate", 3.2);
}


// TESTE

void test_srv_size()
{
	TaskValidator val;
	TasksRepository repo;
	CurrentTasks ct;
	const TasksService srv{ repo, val, ct };

	assert(srv.size() == 0);

	Task task1{ "task1", "desc1", "type1", 4.2 };
	repo.store(task1);
	assert(srv.size() == 1);

	Task task2{ "task2", "desc2", "type2", 1.3 };
	repo.store(task2);
	assert(srv.size() == 2);

	Task task3{ "task3", "desc3", "type3", 5.12 };
	repo.store(task3);
	assert(srv.size() == 3);

	Task task4{ "task4", "desc4", "type4", 10.4 };
	Task task5{ "task5", "desc5", "type5", 15.12 };

	repo.store(task4);
	repo.store(task5);
	assert(srv.size() == 5);
}

void test_srv_add_task()
{
	TaskValidator val;
	TasksRepository repo;
	CurrentTasks ct;
	TasksService srv{ repo, val, ct };

	srv.add_task("task1", "desc1", "type1", 4.2);
	assert(srv.get_all_tasks().at(0).get_title() == "task1");
	assert(srv.get_all_tasks().at(0).get_descr() == "desc1");
	assert(srv.get_all_tasks().at(0).get_type() == "type1");
	assert(srv.get_all_tasks().at(0).get_duration() == 4.2);

	srv.add_task("task2", "desc2", "type2", 2.3);
	assert(srv.get_all_tasks().at(1).get_title() == "task2");
	assert(srv.get_all_tasks().at(1).get_descr() == "desc2");
	assert(srv.get_all_tasks().at(1).get_type() == "type2");
	assert(srv.get_all_tasks().at(1).get_duration() == 2.3);

	srv.add_task("task3", "desc3", "type3", 11.0);
	assert(srv.get_all_tasks().at(2).get_title() == "task3");
	assert(srv.get_all_tasks().at(2).get_descr() == "desc3");
	assert(srv.get_all_tasks().at(2).get_type() == "type3");
	assert(srv.get_all_tasks().at(2).get_duration() == 11.0);

	try
	{
		srv.add_task("task3", "desc3", "type3", 11.0);
		//assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}

	try
	{
		srv.add_task("task2", "desc3sdf", "type2", 2.3);
		//assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}
}

void test_srv_modifiy_task()
{
	TaskValidator val;
	TasksRepository repo;
	CurrentTasks ct;
	TasksService srv{ repo, val, ct };

	srv.add_task("task1", "desc1", "type1", 4.2);
	srv.add_task("task2", "desc2", "type2", 2.3);
	srv.add_task("task3", "desc3", "type3", 11.0);

	srv.modify_task("task1", "type1", 4.2, "descr_noua1", "tip_nou1", 5.3);
	assert(srv.get_all_tasks().at(0).get_title() == "task1");
	assert(srv.get_all_tasks().at(0).get_descr() == "descr_noua1");
	assert(srv.get_all_tasks().at(0).get_type() == "tip_nou1");
	assert(srv.get_all_tasks().at(0).get_duration() == 5.3);

	srv.modify_task("task2", "type2", 2.3, "descr_noua2", "tip_nou2", 3.4);
	assert(srv.get_all_tasks().at(1).get_title() == "task2");
	assert(srv.get_all_tasks().at(1).get_descr() == "descr_noua2");
	assert(srv.get_all_tasks().at(1).get_type() == "tip_nou2");
	assert(srv.get_all_tasks().at(1).get_duration() == 3.4);

	srv.modify_task("task3", "type3", 11.0, "descr_noua3", "tip_nou3", 11.5);
	assert(srv.get_all_tasks().at(2).get_title() == "task3");
	assert(srv.get_all_tasks().at(2).get_descr() == "descr_noua3");
	assert(srv.get_all_tasks().at(2).get_type() == "tip_nou3");
	assert(srv.get_all_tasks().at(2).get_duration() == 11.5);

	try
	{
		srv.modify_task("task4", "tip", 2.4, "durata", "tip_nou", 3.2);
		//assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}

	srv.add_task("task1", "descr_noua3", "tip_nou3", 11.5);

	try
	{
		srv.modify_task("task1", "tip_nou1", 5.3, "descr_noua3", "tip_nou3", 11.5);
		//assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}
}

void test_srv_delete_task()
{
	TaskValidator val;
	TasksRepository repo;
	CurrentTasks ct;
	TasksService srv{ repo, val, ct };
	
	srv.add_task("task1", "desc1", "type1", 4.2);
	srv.add_task("task2", "desc2", "type2", 2.3);
	srv.add_task("task3", "desc3", "type3", 11.0);

	srv.delete_task("task1", "type1", 4.2);
	assert(srv.size() == 2);

	srv.delete_task("task3", "type3", 11.0);
	assert(srv.size() == 1);

	Task a{ "task2", "desc2", "type2", 2.3 };
	assert(srv.get_all_tasks().at(0) == a);

	try
	{
		srv.delete_task("task1", "type1", 4.2);
		//assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}

	try
	{
		srv.delete_task("task3", "type3", 11.0);
		//assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}
}

void test_srv_filter_descr()
{
	TaskValidator val;
	TasksRepository repo;
	CurrentTasks ct;
	TasksService srv{ repo, val, ct };

	srv.add_task("task1", "desc1", "type1", 4.2);
	srv.add_task("task2", "desc2cuv", "type2", 2.3);
	srv.add_task("task3", "desc3alt", "type3", 11.0);

	vector<Task> filtered_list;
	srv.filter_by_descr("desc", filtered_list);
	assert(filtered_list.size() == 3);

	srv.filter_by_descr("cuv", filtered_list);
	assert(filtered_list.size() == 1);

	srv.add_task("task4", "descalt123", "type7", 10.0);
	srv.filter_by_descr("alt", filtered_list);
	assert(filtered_list.size() == 2);
}

void test_srv_filter_type()
{
	TaskValidator val;
	TasksRepository repo;
	CurrentTasks ct;
	TasksService srv{ repo, val, ct };

	srv.add_task("task1", "desc1", "type1", 4.2);
	srv.add_task("task2", "desc2", "type2", 2.3);
	srv.add_task("task3", "desc3", "type3", 11.0);
	srv.add_task("task4", "desc4", "type1", 11.0);

	vector<Task> filtered_list;
	srv.filter_by_type("type1", filtered_list);
	assert(filtered_list.size() == 2);

	srv.filter_by_type("type2", filtered_list);
	assert(filtered_list.size() == 1);

	srv.filter_by_type("type7", filtered_list);
	assert(filtered_list.size() == 0);
}

void test_srv_search_task()
{
	TaskValidator val;
	TasksRepository repo;
	CurrentTasks ct;
	TasksService srv{ repo, val, ct };

	srv.add_task("task1", "desc1", "type1", 4.2);
	srv.add_task("task2", "desc2", "type2", 2.3);
	srv.add_task("task3", "desc3", "type3", 11.0);

	Task task1{ "task1", "desc1", "type1", 4.2 };
	Task task2{ "task2", "desc2", "type2", 2.3 };
	Task task3{ "task3", "desc3", "type3", 11.0 };
	assert(srv.search_task("task1", "type1", 4.2) == task1);
	assert(srv.search_task("task2", "type2", 2.3) == task2);
	assert(srv.search_task("task3", "type3", 11.0) == task3);

	try
	{
		srv.search_task("task2", "type1", 4.2);
		//assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}

	try
	{
		srv.search_task("task1", "type1", 4.1);
		//assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}
}

void test_srv_sort()
{
	TaskValidator val;
	TasksRepository repo;
	CurrentTasks ct;
	TasksService srv{ repo, val, ct };

	srv.add_task("Nume vechi", "Cuvinte", "bowling", 3.2);
	srv.add_task("Nume nou", "Descriere mai lunga", "teme", 0.05);
	srv.add_task("Alte activitati", "Fara descriere", "scoala", 10.11);
	srv.add_task("Task nou", "Alta descriere", "sport", 10.11);
	srv.add_task("Nu mai am idei", "Descriere activitate", "facultate", 0.10);
	srv.add_task("Alt titlu", "Activitatea de alt tip", "alt tip2", 3.2);
	srv.add_task("Fara teme", "Nu am idei", "alte teme", 0.05);
	srv.add_task("Titlu", "Cuvinte pentru activitatetete", "alt tip", 3.2);

	vector<Task> sorted_by_title = srv.general_sort(srv.get_all_tasks(), 1);
	assert(sorted_by_title.at(0).get_title() == "Alt titlu");
	assert(sorted_by_title.at(1).get_title() == "Alte activitati");
	assert(sorted_by_title.at(7).get_title() == "Titlu");
	
	vector<Task> sorted_by_descr = srv.general_sort(srv.get_all_tasks(), 2);
	assert(sorted_by_descr.at(0).get_descr() == "Cuvinte");
	assert(sorted_by_descr.at(1).get_descr() == "Nu am idei");
	assert(sorted_by_descr.at(7).get_descr() == "Cuvinte pentru activitatetete");

	vector<Task> sorted_by_duration = srv.general_sort(srv.get_all_tasks(), 3);
	assert(sorted_by_duration.at(0).get_duration() == 0.05);
	assert(sorted_by_duration.at(0).get_type() == "alte teme");
	assert(sorted_by_duration.at(1).get_duration() == 0.05);
	assert(sorted_by_duration.at(1).get_type() == "teme");
	assert(sorted_by_duration.at(7).get_duration() == 10.11);
	assert(sorted_by_duration.at(7).get_type() == "sport");
}

void test_size_ct()
{
	TaskValidator val;
	TasksRepository repo;
	CurrentTasks ct;
	TasksService srv{ repo, val, ct };

	srv.add_task("Nume vechi", "Cuvinte", "bowling", 3.2);
	srv.add_task("Nume nou", "Descriere mai lunga", "teme", 0.05);
	srv.add_task("Alte activitati", "Fara descriere", "scoala", 10.11);

	assert(srv.size_ct() == 0);

	srv.add_task_ct("Nume vechi");
	assert(srv.size_ct() == 1);

	srv.add_task_ct("Nume nou");
	srv.add_task_ct("Alte activitati");
	assert(srv.size_ct() == 3);
}

void test_add_task_ct()
{
	TaskValidator val;
	TasksRepository repo;
	CurrentTasks ct;
	TasksService srv{ repo, val, ct };

	srv.add_task("Nume vechi", "Cuvinte", "bowling", 3.2);
	srv.add_task("Nume nou", "Descriere mai lunga", "teme", 0.05);
	srv.add_task("Alte activitati", "Fara descriere", "scoala", 10.11);
	srv.add_task("Task nou", "Alta descriere", "sport", 10.11);
	srv.add_task("Nu mai am idei", "Descriere activitate", "facultate", 0.10);

	assert(srv.get_crt_tasks().size() == 0);
	
	srv.add_task_ct("Nume vechi");
	assert(srv.get_crt_tasks().size() == 1);
	assert(srv.get_crt_tasks().at(0).get_title() == "Nume vechi");
	assert(srv.get_crt_tasks().at(0).get_descr() == "Cuvinte");
	assert(srv.get_crt_tasks().at(0).get_type() == "bowling");
	assert(srv.get_crt_tasks().at(0).get_duration() == 3.2);
	try
	{
		srv.add_task_ct("Nume vechi");
		//assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}

	srv.add_task_ct("Nume nou");
	assert(srv.get_crt_tasks().size() == 2);
	assert(srv.get_crt_tasks().at(1).get_title() == "Nume nou");
	assert(srv.get_crt_tasks().at(1).get_descr() == "Descriere mai lunga");
	assert(srv.get_crt_tasks().at(1).get_type() == "teme");
	assert(srv.get_crt_tasks().at(1).get_duration() == 0.05);
	try
	{
		srv.add_task_ct("Nume nou");
		//assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}

	try
	{
		srv.add_task_ct("Fara nume");
		//assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}

	try
	{
		srv.add_task_ct("Nu exista");
		//assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}
}

void test_empty_current_list()
{
	TaskValidator val;
	TasksRepository repo;
	CurrentTasks ct;
	TasksService srv{ repo, val, ct };

	assert(srv.get_crt_tasks().size() == 0);
	srv.add_task("Nume vechi", "Cuvinte", "bowling", 3.2);
	srv.add_task("Nume nou", "Descriere mai lunga", "teme", 0.05);
	srv.add_task("Alte activitati", "Fara descriere", "scoala", 10.11);

	srv.add_task_ct("Nume vechi");
	assert(srv.get_crt_tasks().size() == 1);
	srv.empty_current_list();
	assert(srv.get_crt_tasks().size() == 0);

	srv.add_task_ct("Nume vechi");
	srv.add_task_ct("Nume nou");
	srv.add_task_ct("Alte activitati");
	assert(srv.get_crt_tasks().size() == 3);
	srv.empty_current_list();
	assert(srv.get_crt_tasks().size() == 0);
}

void test_add_random_tasks_ct()
{
	TaskValidator val;
	TasksRepository repo;
	CurrentTasks ct;
	TasksService srv{ repo, val, ct };

	srv.add_task("Nume vechi", "Cuvinte", "bowling", 3.2);
	srv.add_task("Nume nou", "Descriere mai lunga", "teme", 0.05);
	srv.add_task("Alte activitati", "Fara descriere", "scoala", 10.11);
	srv.add_task("Task nou", "Alta descriere", "sport", 10.11);
	srv.add_task("Nu mai am idei", "Descriere activitate", "facultate", 0.10);
	srv.add_task("Alt titlu", "Activitatea de alt tip", "alt tip2", 3.2);
	srv.add_task("Fara teme", "Nu am idei", "alte teme", 0.05);
	srv.add_task("Titlu", "Cuvinte pentru activitatetete", "alt tip", 3.2);

	srv.add_random_tasks_ct(3);
	assert(srv.get_crt_tasks().size() == 3);

	srv.empty_current_list();
	assert(srv.get_crt_tasks().size() == 0);
	srv.add_random_tasks_ct(0);
	assert(srv.get_crt_tasks().size() == 0);

	srv.empty_current_list();
	assert(srv.get_crt_tasks().size() == 0);
	srv.add_random_tasks_ct(1);
	assert(srv.get_crt_tasks().size() == 1);

	srv.empty_current_list();
	assert(srv.get_crt_tasks().size() == 0);
	srv.add_random_tasks_ct(8);
	assert(srv.get_crt_tasks().size() == 8);
}

void test_export_ct_list()
{
	TaskValidator val;
	TasksRepository repo;
	CurrentTasks ct;
	TasksService srv{ repo, val, ct };

	srv.export_current_list("test");

	srv.add_task("Nume vechi", "Cuvinte", "bowling", 3.2);
	srv.add_task("Nume nou", "Descriere mai lunga", "teme", 0.05);
	srv.add_task("Alte activitati", "Fara descriere", "scoala", 10.11);

	srv.add_task_ct("Nume vechi");
	srv.add_task_ct("Nume nou");
	srv.add_task_ct("Alte activitati");

	srv.export_current_list("test");
	std::ifstream fin("test.html");

	char line[200];
	fin.getline(line, 200, EOF);

	fin.close();


	TaskValidator val1;
	TasksRepository repo1;
	CurrentTasksCVS ct1;
	TasksService srv1{ repo1, val1, ct1 };

	srv1.export_current_list("test");

	srv1.add_task("Nume vechi", "Cuvinte", "bowling", 3.2);
	srv1.add_task("Nume nou", "Descriere mai lunga", "teme", 0.05);
	srv1.add_task("Alte activitati", "Fara descriere", "scoala", 10.11);

	srv1.add_task_ct("Nume vechi");
	srv1.add_task_ct("Nume nou");
	srv1.add_task_ct("Alte activitati");

	srv1.export_current_list("test");
	std::ifstream fin1("test.html");

	fin1.getline(line, 200, EOF);

	fin1.close();
}

void test_get_raport()
{
	TaskValidator val;
	TasksRepository repo;
	CurrentTasks ct;
	TasksService srv{ repo, val, ct };

	srv.add_task("Nume vechi", "Cuvinte", "sport", 3.2);
	srv.add_task("Nume nou", "Descriere mai lunga", "teme", 0.05);
	srv.add_task("Alte activitati", "Fara descriere", "scoala", 10.11);
	srv.add_task("Task nou", "Alta descriere", "sport", 10.11);
	srv.add_task("Nu mai am idei", "Descriere activitate", "sport", 0.10);
	srv.add_task("Alt titlu", "Activitatea de alt tip", "teme", 3.2);
	srv.add_task("Fara teme", "Nu am idei", "scoala", 0.05);
	srv.add_task("Titlu", "Cuvinte pentru activitatetete", "facultate", 3.2);

	map<string, int> type_freq = srv.get_raport();

	assert(type_freq["sport"] == 3);
	assert(type_freq["teme"] == 2);
	assert(type_freq["facultate"] == 1);
	assert(type_freq["scoala"] == 2);
	assert(type_freq["tip"] == 0);
}

void test_undo()
{
	TaskValidator val;
	TasksRepository repo;
	CurrentTasks ct;
	TasksService srv{ repo, val, ct };

	srv.add_task("Task1", "descr1", "tip1", 1.1);
	srv.add_task("Task2", "descr2", "tip2", 2.2);
	srv.add_task("Task3", "descr3", "tip3", 3.3);

	assert(srv.size() == 3);
	srv.modify_task("Task1", "tip1", 1.1, "descnoua", "tipnou", 1.2);
	srv.delete_task("Task3", "tip3", 3.3);
	assert(srv.size() == 2);

	srv.undo();
	assert(srv.size() == 3);
	assert(srv.get_all_tasks().at(2).get_title() == "Task3");
	assert(srv.get_all_tasks().at(2).get_descr() == "descr3");
	assert(srv.get_all_tasks().at(2).get_type() == "tip3");
	assert(srv.get_all_tasks().at(2).get_duration() == 3.3);

	srv.undo();
	assert(srv.get_all_tasks().at(1).get_title() == "Task2");
	assert(srv.get_all_tasks().at(1).get_descr() == "descr2");
	assert(srv.get_all_tasks().at(1).get_type() == "tip2");
	assert(srv.get_all_tasks().at(1).get_duration() == 2.2);

	srv.undo();
	assert(srv.size() == 2);
	srv.undo();
	assert(srv.size() == 1);
	srv.undo();
	assert(srv.size() == 0);

	try
	{
		srv.undo();
		//assert(false);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}
}