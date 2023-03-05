#include "Task.h"
#include "Validator.h"
#include "Exceptions.h"
#include <vector>

using std::vector;


void TaskValidator::validate(const Task& task_tov) const
{
	vector<string> errors_list;
	
	if (task_tov.get_title().length() < 3)
		errors_list.push_back("Titlul trebuie sa aiba cel putin trei caractere.\n");
	if (task_tov.get_descr().length() < 3)
		errors_list.push_back("Descrierea trebuie sa aiba cel putin trei caractere.\n");
	if (task_tov.get_type().length() < 2)
		errors_list.push_back("Tipul trebuie sa aiba cel putin doua caractere.\n");
	if (task_tov.get_duration() <= 0)
		errors_list.push_back("Durata nu poate fi mai mica decat 0.\n");
	if (task_tov.get_duration() > 12)
		errors_list.push_back("Durata nu poate fi mai mare de 12 ore.\n");
	if (task_tov.get_duration() - static_cast<int>(task_tov.get_duration()) > 0.59)
		errors_list.push_back("Minutele nu pot depasi 59.\n");

	if (errors_list.size() > 0)
		throw ValidationException(errors_list);
}


// TESTE

void test_validate_task()
{
	TaskValidator val;

	Task task1{ "Titlu", "Descriere", "Tip", 4.5 };
	try
	{
		val.validate(task1);
		assert(true);
	}
	catch (ValidationException&)
	{
		assert(false);
	}

	Task task2{ "Titlu", "Descriere", "Tip", 4.5 };
	try
	{
		val.validate(task2);
		assert(true);
	}
	catch (ValidationException&)
	{
		assert(false);
	}

	Task task3{ "Ti", "Descriere", "Tip", 4.5 };
	try
	{
		val.validate(task3);
		assert(false);
	}
	catch (ValidationException&)
	{
		assert(true);
	}

	Task task4{ "Titlu", "De", "Tip", 4.5 };
	try
	{
		val.validate(task4);
		assert(false);
	}
	catch (ValidationException&)
	{
		assert(true);
	}

	Task task5{ "Titlu", "Descriere", "T", 4.5 };
	try
	{
		val.validate(task5);
		assert(false);
	}
	catch (ValidationException&)
	{
		assert(true);
	}

	Task task6{ "Titlu", "Descriere", "Tip", 4.60 };
	try
	{
		val.validate(task6);
		assert(false);
	}
	catch (ValidationException&)
	{
		assert(true);
	}

	Task task7{ "Titlu", "Descriere", "Tip", 12.4 };
	try
	{
		val.validate(task7);
		assert(false);
	}
	catch (ValidationException&)
	{
		assert(true);
	}

	Task task8{ "Ti", "Descriere", "T", 4.60 };
	try
	{
		val.validate(task8);
		assert(false);
	}
	catch (ValidationException&)
	{
		assert(true);
	}

	Task task9{ "Ti", "De", "T", 12.70 };
	try
	{
		val.validate(task9);
		assert(false);
	}
	catch (ValidationException&)
	{
		assert(true);
	}
	
	Task task10{ "Titlu", "Descriere", "Tip", 0 };
	try
	{
		val.validate(task10);
		assert(false);
	}
	catch (ValidationException&)
	{
		assert(true);
	}

	Task task11{ "Titlu", "Descriere", "Tip", -11.4 };
	try
	{
		val.validate(task11);
		assert(false);
	}
	catch (ValidationException&)
	{
		assert(true);
	}
}