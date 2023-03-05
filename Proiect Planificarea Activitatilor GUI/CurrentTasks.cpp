#include "CurrentTasks.h"
#include <algorithm>
#include <random>
#include <fstream>

using std::ofstream;


const size_t CurrentTasks::size() const noexcept
{
	return this->current_tasks.size();
}


void CurrentTasks::store_task_ct(const Task& task_to_add)
{
	current_tasks.push_back(task_to_add);
	notify();
}


void CurrentTasks::store_random_tasks(vector<Task> available_tasks, const int count)
{
	clear_all_ct();

	std::shuffle(
		available_tasks.begin(),
		available_tasks.end(),
		std::default_random_engine(std::random_device{}())
	);

	while (current_tasks.size() < count)
	{
		current_tasks.push_back(available_tasks.back());
		available_tasks.pop_back();
	}

	notify();
}


void CurrentTasks::clear_all_ct() noexcept
{
	current_tasks.clear();
	notify();
}


const vector<Task>& CurrentTasks::get_current_tasks() const noexcept
{
	return this->current_tasks;
}


void CurrentTasks::export_list(string file_name) const
{
	file_name = file_name + ".html";
	ofstream fout(file_name);

	fout << "LISTA ACTIVITAI CURENTE:<br><br>";
	int i = 0;

	if (size())
	{
		for (const auto& task : get_current_tasks())
		{
			fout << i << ") " << task << "<br>";
			i++;
		}
	}
	else
		fout << "Lista curenta de activitati este goala.";

	fout.close();
}


void CurrentTasksCVS::export_list(string file_name) const
{
	file_name = file_name + ".cvs";
	ofstream fout(file_name);

	fout << "LISTA ACTIVITAI CURENTE:";
	int i = 0;

	if (size())
	{
		for (const auto& task : get_current_tasks())
		{
			fout << i << ") " << task << "\n";
			i++;
		}
	}
	else
		fout << "Lista curenta de activitati este goala.";

	fout.close();
}


// TESTE

void test_store_task_ct()
{
	CurrentTasks current_list;
	Task task1{ "Titlu1", "desc1", "tip1", 1 };
	Task task2{ "Titlu2", "desc2", "tip2", 2 };
	Task task3{ "Titlu3", "desc3", "tip3", 3 };

	current_list.store_task_ct(task1);
	assert(current_list.get_current_tasks().size() == 1);

	current_list.store_task_ct(task2);
	current_list.store_task_ct(task3);
	assert(current_list.get_current_tasks().size() == 3);

	Task task4{ "Titlu4", "desc4", "tip4", 4 };
	current_list.store_task_ct(task4);
	assert(current_list.get_current_tasks().size() == 4);
}

void test_clear_all_ct()
{
	CurrentTasks current_list;
	Task task1{ "Titlu1", "desc1", "tip1", 1 };
	Task task2{ "Titlu2", "desc2", "tip2", 2 };
	Task task3{ "Titlu3", "desc3", "tip3", 3 };

	current_list.store_task_ct(task1);
	assert(current_list.get_current_tasks().size() == 1);
	current_list.clear_all_ct();
	assert(current_list.get_current_tasks().size() == 0);

	current_list.store_task_ct(task2);
	current_list.store_task_ct(task3);
	assert(current_list.get_current_tasks().size() == 2);
	current_list.clear_all_ct();
	assert(current_list.get_current_tasks().size() == 0);

	Task task4{ "Titlu4", "desc4", "tip4", 4 };
	current_list.store_task_ct(task4);
	assert(current_list.get_current_tasks().size() == 1);
	current_list.clear_all_ct();
	assert(current_list.get_current_tasks().size() == 0);
}
