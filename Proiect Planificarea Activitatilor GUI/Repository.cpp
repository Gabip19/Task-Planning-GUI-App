#include "Repository.h"
#include <algorithm>


void TasksRepository::store(const Task& new_task)
{
	this->tasks_list.push_back(new_task);
}


void TasksRepository::update(const __int64 index, const Task& updated_task)
{
	tasks_list.at(index) . set_descr( updated_task.get_descr() );
	tasks_list.at(index) . set_type( updated_task.get_type() );
	tasks_list.at(index) . set_duration( updated_task.get_duration() );
}


bool TasksRepository::remove(const Task& task_to_remove)
{
	const auto& it = std::find(tasks_list.begin(), tasks_list.end(), task_to_remove);

	if (it != tasks_list.end())
	{
		this->tasks_list.erase(it);
		return true;
	}

	return false;
}


const vector<Task>& TasksRepository::get_all_tasks() const noexcept
{
	return this->tasks_list;
}


const size_t TasksRepository::size() const noexcept
{
	return this->tasks_list.size();
}


const __int64 TasksRepository::find(const Task& task_to_search) const
{
	const auto& it = std::find(tasks_list.begin(), tasks_list.end(), task_to_search);
	if (it != tasks_list.end())
	{
		return it - tasks_list.begin();
	}
	return -1;
}



// CELALALT REPO CU MAP

//TasksRepositoryMAP::TasksRepositoryMAP(TasksRepositoryMAP&& ot) : 
//	tasks_map{ ot.tasks_map }, 
//	vec_tasks{ ot.vec_tasks }
//{
//	ot.vec_tasks = nullptr;
//};


void TasksRepositoryMAP::store(const Task& new_task)
{
	tasks_map[new_task.get_title()] = new_task;
}


void TasksRepositoryMAP::update(const __int64 index, const Task& updated_task)
{
	tasks_map[updated_task.get_title()] . set_descr( updated_task.get_descr() );
	tasks_map[updated_task.get_title()] . set_type( updated_task.get_type() );
	tasks_map[updated_task.get_title()] . set_duration( updated_task.get_duration() );
}


bool TasksRepositoryMAP::remove(const Task& task_to_remove)
{
	if (this->tasks_map.erase(task_to_remove.get_title()))
		return true;
	return false;
}


const vector<Task>& TasksRepositoryMAP::get_all_tasks() const noexcept
{
	this->vec_tasks->clear();
	for (const auto& elem : tasks_map)
	{
		vec_tasks->push_back(elem.second);
	}
	return *(this->vec_tasks);
}


const size_t TasksRepositoryMAP::size() const noexcept
{
	return tasks_map.size();
}


const __int64 TasksRepositoryMAP::find(const Task& task_to_search) const
{
	const vector<Task>& all_tasks = get_all_tasks();
	const auto& it = std::find(all_tasks.begin(), all_tasks.end(), task_to_search);
	if (it != all_tasks.end())
	{
		return it - all_tasks.begin();
	}
	return -1;
}


// TESTE

void test_repo_store()
{
	TasksRepository repo;
	
	Task task1{ "task1", "desc1", "type1", 4.2};
	repo.store(task1);
	assert(repo.size() == 1);
	assert(repo.get_all_tasks().at(0).get_title() == "task1");
	assert(repo.get_all_tasks().at(0).get_descr() == "desc1");
	assert(repo.get_all_tasks().at(0).get_type() == "type1");
	assert(repo.get_all_tasks().at(0).get_duration() == 4.2);

	Task task2{ "task2", "desc2", "type2", 51.3 };
	repo.store(task2);
	assert(repo.size() == 2);
	assert(repo.get_all_tasks().at(1).get_title() == "task2");
	assert(repo.get_all_tasks().at(1).get_descr() == "desc2");
	assert(repo.get_all_tasks().at(1).get_type() == "type2");
	assert(repo.get_all_tasks().at(1).get_duration() == 51.3);

	Task task3{ "task3", "desc3", "type3", 22.0 };
	repo.store(task3);
	assert(repo.size() == 3);
	assert(repo.get_all_tasks().at(2).get_title() == "task3");
	assert(repo.get_all_tasks().at(2).get_descr() == "desc3");
	assert(repo.get_all_tasks().at(2).get_type() == "type3");
	assert(repo.get_all_tasks().at(2).get_duration() == 22.0);
}

void test_repo_update()
{
	TasksRepository repo;

	Task task1{ "task1", "desc1", "type1", 4.2 };
	Task task1_update{ "   ", "desc_noua1", "tip1_nou", 6.22 };
	repo.store(task1);
	repo.update(0, task1_update);
	
	assert(repo.get_all_tasks().at(0).get_title() == "task1");
	assert(repo.get_all_tasks().at(0).get_descr() == "desc_noua1");
	assert(repo.get_all_tasks().at(0).get_type() == "tip1_nou");
	assert(repo.get_all_tasks().at(0).get_duration() == 6.22);

	Task task2{ "task2", "desc2", "type2", 51.3 };
	Task task2_update{ "   ", "desc_noua2", "tip2_nou", 16.21 };
	repo.store(task2);
	repo.update(1, task2_update);

	assert(repo.get_all_tasks().at(1).get_title() == "task2");
	assert(repo.get_all_tasks().at(1).get_descr() == "desc_noua2");
	assert(repo.get_all_tasks().at(1).get_type() == "tip2_nou");
	assert(repo.get_all_tasks().at(1).get_duration() == 16.21);

	Task task3{ "task3", "desc3", "type3", 22.0 };
	Task task3_update{ "   ", "desc3", "tip1_nou", 22.0 };
	repo.store(task3);
	repo.update(2, task3_update);
	
	assert(repo.get_all_tasks().at(2).get_title() == "task3");
	assert(repo.get_all_tasks().at(2).get_descr() == "desc3");
	assert(repo.get_all_tasks().at(2).get_type() == "tip1_nou");
	assert(repo.get_all_tasks().at(2).get_duration() == 22.0);
}

void test_repo_remove()
{
	TasksRepository repo;

	Task task1{ "task1", "desc1", "type1", 4.2 };
	repo.store(task1);

	Task task2{ "task2", "desc2", "type2", 51.3 };
	repo.store(task2);

	Task task3{ "task3", "desc3", "type3", 22.0 };
	repo.store(task3);

	assert(repo.remove(task1) == true);
	assert(repo.remove(task1) == false);
	assert(repo.size() == 2);
	assert(repo.get_all_tasks().at(0) == task2);

	assert(repo.remove(task3) == true);
	assert(repo.remove(task3) == false);
	assert(repo.size() == 1);

	assert(repo.remove(task2) == true);
	assert(repo.remove(task2) == false);
	assert(repo.size() == 0);

	assert(repo.remove(task2) == false);
}

void test_repo_size()
{
	TasksRepository repo;

	assert(repo.size() == 0);

	Task task1{ "task1", "desc1", "type1", 4.2 };
	repo.store(task1);
	assert(repo.size() == 1);

	Task task2{ "task2", "desc2", "type2", 1.3 };
	repo.store(task2);
	assert(repo.size() == 2);

	Task task3{ "task3", "desc3", "type3", 5.12 };
	repo.store(task3);
	assert(repo.size() == 3);

	Task task4{ "task4", "desc4", "type4", 10.4 };
	Task task5{ "task5", "desc5", "type5", 15.12 };

	repo.store(task4);
	repo.store(task5);
	assert(repo.size() == 5);
}

void test_repo_find()
{
	TasksRepository repo;

	Task task1{ "task1", "desc1", "type1", 4.2 };
	repo.store(task1);

	Task task2{ "task2", "desc2", "type2", 51.3 };
	repo.store(task2);

	Task task3{ "task3", "desc3", "type3", 22.0 };
	repo.store(task3);

	Task task4{ "task4", "desc4", "type4", 21.1 };
	Task task5{ "task5", "desc5", "type5", 2.0 };

	assert(repo.find(task1) == 0);
	assert(repo.find(task2) == 1);
	assert(repo.find(task3) == 2);
	assert(repo.find(task4) == -1);
	assert(repo.find(task5) == -1);
}