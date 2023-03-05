#include "Task.h"


string Task::get_title() const
{
	return this->title;
}

string Task::get_descr() const
{
	return this->descr;
}

string Task::get_type() const
{
	return this->type;
}

double Task::get_duration() const noexcept
{
	return this->duration;
}


void Task::set_title(const string new_title)
{
	this->title = new_title;
}

void Task::set_descr(const string new_descr)
{
	this->descr = new_descr;
}

void Task::set_type(const string new_type)
{
	this->type = new_type;
}

void Task::set_duration(const double new_duration) noexcept
{
	this->duration = new_duration;
}


bool Task::operator==(const Task& ot) const noexcept
{
	if (this->title != ot.title)
		return false;
	if (this->type != ot.type)
		return false;
	if (this->duration != ot.duration)
		return false;
	return true;
}


ostream& operator<<(ostream& os, const Task& task)
{
	os << "TITLU: " + task.title + "  |  DESCRIERE: " + task.descr + "  |  TIP: " + task.type + "  |  DURATA: " << task.duration;
	return os;
}


// TESTE

void test_get_set()
{
	Task task1{ "Task1", "desc1", "tip1", 3.6 };
	assert(task1.get_title() == "Task1");
	assert(task1.get_descr() == "desc1");
	assert(task1.get_type() == "tip1");
	assert(task1.get_duration() == 3.6);

	Task task2{ "Task2", "desc2", "tip2", 12.1 };
	assert(task2.get_title() == "Task2");
	assert(task2.get_descr() == "desc2");
	assert(task2.get_type() == "tip2");
	assert(task2.get_duration() == 12.1);

	task2.set_title("Task nou");
	task2.set_descr("descriere noua");
	task2.set_type("tip nou");
	task2.set_duration(5.6);

	assert(task2.get_title() == "Task nou");
	assert(task2.get_descr() == "descriere noua");
	assert(task2.get_type() == "tip nou");
	assert(task2.get_duration() == 5.6);
}

void test_equal_tasks()
{
	Task task1{ "Task1", "desc1", "tip1", 3.6 };
	Task task2{ "Task1", "desc1123123", "tip1", 3.6 };

	assert(task1 == task2);

	Task task3{ "Task3", "desc1", "tip1", 3.6 };
	Task task4{ "Task1", "de421", "tip2", 3.6 };
	Task task5{ "Task1", "fdsaas", "tip1", 4.70 };

	assert((task1 == task3) == false);
	assert((task1 == task4) == false);
	assert((task1 == task5) == false);

	Task task6{ "Task1", "alta desc", "tip2", 3.6 };
	Task task7{ "Task1", "alta desc iar", "tip2", 3.6 };

	assert(task4 == task6);
	assert(task4 == task7);
	assert(task6 == task7);
}