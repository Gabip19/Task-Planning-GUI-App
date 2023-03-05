#include "TEST repo_map.h"
#include "Repository.h"


void test_repo_map()
{
	test_repo_map_store();
	test_repo_map_update();
	test_repo_map_remove();
	test_repo_map_size();
	test_repo_map_find();
}

void test_repo_map_store()
{
	TasksRepositoryMAP repo;

	Task task1{ "task1", "desc1", "type1", 4.2 };
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

void test_repo_map_update()
{
	TasksRepositoryMAP repo;

	Task task1{ "task1", "desc1", "type1", 4.2 };
	Task task1_update{ "task1", "desc_noua1", "tip1_nou", 6.22 };
	repo.store(task1);
	repo.update(0, task1_update);

	assert(repo.get_all_tasks().at(0).get_title() == "task1");
	assert(repo.get_all_tasks().at(0).get_descr() == "desc_noua1");
	assert(repo.get_all_tasks().at(0).get_type() == "tip1_nou");
	assert(repo.get_all_tasks().at(0).get_duration() == 6.22);

	Task task2{ "task2", "desc2", "type2", 51.3 };
	Task task2_update{ "task2", "desc_noua2", "tip2_nou", 16.21 };
	repo.store(task2);
	repo.update(1, task2_update);

	assert(repo.get_all_tasks().at(1).get_title() == "task2");
	assert(repo.get_all_tasks().at(1).get_descr() == "desc_noua2");
	assert(repo.get_all_tasks().at(1).get_type() == "tip2_nou");
	assert(repo.get_all_tasks().at(1).get_duration() == 16.21);

	Task task3{ "task3", "desc3", "type3", 22.0 };
	Task task3_update{ "task3", "desc3", "tip1_nou", 22.0 };
	repo.store(task3);
	repo.update(2, task3_update);

	assert(repo.get_all_tasks().at(2).get_title() == "task3");
	assert(repo.get_all_tasks().at(2).get_descr() == "desc3");
	assert(repo.get_all_tasks().at(2).get_type() == "tip1_nou");
	assert(repo.get_all_tasks().at(2).get_duration() == 22.0);
}

void test_repo_map_remove()
{
	TasksRepositoryMAP repo;

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

void test_repo_map_size()
{
	TasksRepositoryMAP repo;

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

void test_repo_map_find()
{
	TasksRepositoryMAP repo;

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