#include "UI.h"
#include <iostream>
#include "Exceptions.h"

using std::cout;
using std::cin;
using std::getline;


void UIConsole::show_ui()
{
	bool running = true;
	while (running)
	{
		try
		{
			print_menu();
			const int option = get_option();
			
			switch (option)
			{
			
			case 1:
				if (&srv != nullptr)
					print_list(srv.get_all_tasks());
				break;
			
			case 2:
				ui_add_task();
				break;
			
			case 3:
				ui_modify_task();
				break;
			
			case 4:
				ui_delete_task();
				break;

			case 5:
				ui_search_task();
				break;

			case 6:
				ui_filter_tasks();
				break;

			case 7:
				ui_sort_tasks();
				break;

			case 8:
				menu_current_tasks();
				break;

			case 9:
				ui_get_raport();
				break;

			case 10:
				ui_export_list();
				break;

			case 11:
				srv.undo();
				cout << "\n\tUndo realizat cu succes.\n";
				break;

			case 0:
				running = false;
				break;
			
			default:
				cout << "\n\tOptiune invalida.\n";
				break;

			}

			cout << "\n\n   Numar elemente lista curenta de activitati: " << srv.size_ct() << "\n";

		}
		catch (const ValidationException& error)
		{
			cout << "\n" << error.get_error_messages();
		}
		catch (const RepositoryException& error)
		{
			cout << "\n" << error.get_error_messages();
		}
		catch (std::invalid_argument&)
		{
			cout << "\n   Optiune trebuie sa fie un numar natural.\n";
		}
	}
}


void UIConsole::print_menu() const
{
	cout << "\n=====================================================\n\n";
	cout << "\tCe operatie doriti sa efectuati:\n";
	cout << "\t1)  Afisati lista de activitati.\n";
	cout << "\t2)  Adaugati o activitate noua.\n";
	cout << "\t3)  Modificati o activitate din lista.\n";
	cout << "\t4)  Stergeti o activitate din lista.\n";
	cout << "\t5)  Cauta o activitate in lista.\n";
	cout << "\t6)  Filtrare activitati.\n";
	cout << "\t7)  Sortare activitati.\n";
	cout << "\t8)  Meniu lista curenta de activitati.\n";
	cout << "\t9)  Calculeaza raport frecventa tip.\n";
	cout << "\t10) Exporta lista de activitati curente in fisier.\n";
	cout << "\t11) Undo.\n";
	cout << "\t0)  EXIT.\n\n";
	cout << "=====================================================\n\n";
	cout << "\tIntroduceti optiunea: ";
}


void UIConsole::print_menu_crt_tasks() const
{
	cout << "\n========= Meniu lista curenta de activitati =========\n\n";
	cout << "\tCe operatie doriti sa efectuati:\n";
	cout << "\t1) Afisati lista activitatilor curente.\n";
	cout << "\t2) Adaugati o activitate dupa titlu.\n";
	cout << "\t3) Adaugati activitati aleatoriu.\n";
	cout << "\t4) Goliti lista activitatilor curente.\n\n";
	cout << "=====================================================\n\n";
	cout << "\tIntroduceti optiunea: ";
}


void UIConsole::print_list(const vector<Task>& task_list) const
{
	if (task_list.size() == 0)
		cout << "\n    Lista de activitati este goala.\n";
	else
	{
		cout << "\nLista de activitati este:\n\n";

		int i = 0;
		for (const auto& task : task_list)
		{
			if (&task != nullptr)
				cout << i << ") " << task << "\n";
			i++;
		}
	}
}


const int UIConsole::get_option() const
{
	string option_string = "";
	cin >> option_string;
	
	const int option = std::stoi(option_string);
	return option;
}


void UIConsole::menu_current_tasks()
{
	print_menu_crt_tasks();
	const int option = get_option();

	switch (option)
	{
	
	case 1:
		print_list(srv.get_crt_tasks());
		break;

	case 2:
		ui_add_task_ct();
		break;

	case 3:
		ui_add_random_tasks_ct();
		break;

	case 4:
		srv.empty_current_list();
		cout << "\n\tLista golita cu succes.\n";
		break;

	default:
		cout << "\n\tOptiune invalida.\n";
		break;

	}
}


void UIConsole::ui_add_task_ct()
{
	string title;
	cin.get();
	cout << "\n   Introduceti titlul: "; getline(cin, title);
	
	srv.add_task_ct(title);
	cout << "\n\tActivitate adaugata cu succes!\n";
}


void UIConsole::ui_add_random_tasks_ct()
{
	int number;
	cout << "\nIntroduceti numarul de activitati pe care vrei sa il generati: ";
	cin >> number;

	if (number > 0 && number <= srv.size())
	{
		srv.add_random_tasks_ct(number);
		cout << "\n\tActivitati adaugate cu succes!\n";
	}
	else
	{
		cout << "\nNumarul trebuie sa fie intre 1 si " << srv.size() << ".\n";
	}
}


void UIConsole::ui_add_task()
{
	cout << "\n\n----===+++ Adauga activitate +++===----\n\n";
	
	string title, descr, type, duration_s;
	double duration = 0.0;
	
	cin.get();
	cout << "   Introduceti titlul: "; getline(cin, title);
	cout << "   Introduceti descrierea: "; getline(cin, descr);
	cout << "   Introduceti tipul: "; getline(cin, type);
	cout << "   Introduceti durata: "; cin >> duration_s;

	duration = std::stod(duration_s);

	srv.add_task(title, descr, type, duration);

	cout << "\n\tActivitate adaugata cu succes!\n";
}


void UIConsole::ui_modify_task()
{
	cout << "\n\n----===+++ Modifica activitate +++===----\n\n";

	string title, type, duration_s;
	double duration = 0.0;

	cin.get();
	cout << "   Introduceti titlul: "; getline(cin, title);
	cout << "   Introduceti tipul: "; getline(cin, type);
	cout << "   Introduceti durata: "; cin >> duration_s;

	duration = std::stod(duration_s);


	string new_descr, new_type, new_duration_s;
	double new_duration = 0.0;

	cin.get();
	cout << "\n   Introduceti noua descriere: "; getline(cin, new_descr);
	cout << "   Introduceti noul tip: "; getline(cin, new_type);
	cout << "   Introduceti noua durata: "; cin >> new_duration_s;

	new_duration = std::stod(new_duration_s);

	srv.modify_task(title, type, duration, new_descr, new_type, new_duration);

	cout << "\n\tActivitate a fost modificata cu succes!\n";
}


void UIConsole::ui_delete_task()
{
	cout << "\n\n----===+++ Sterge activitate +++===----\n\n";

	string title, type, duration_s;
	double duration = 0.0;
	
	cin.get();
	cout << "   Introduceti titlul: "; getline(cin, title);
	cout << "   Introduceti tipul: "; getline(cin, type);
	cout << "   Introduceti durata: "; cin >> duration_s;

	duration = std::stod(duration_s);

	srv.delete_task(title, type, duration);

	cout << "\n\tActivitate stearsa cu succes!\n";
}


void UIConsole::ui_search_task() const
{
	cout << "\n\n----===+++ Cauta activitate +++===----\n\n";

	string title, type, duration_s;
	double duration = 0.0;

	cin.get();
	cout << "   Introduceti titlul: "; getline(cin, title);
	cout << "   Introduceti tipul: "; getline(cin, type);
	cout << "   Introduceti durata: "; cin >> duration_s;

	duration = std::stod(duration_s);

	const Task& found_task = srv.search_task(title, type, duration);

	cout << "\nActivitatea cu datele introduse este: \n";
	cout << "\n" << found_task << "\n";
}


void UIConsole::ui_filter_tasks() const
{
	cout << "\n\n----===+++ Filtreaza activitati +++===----\n\n";

	cout << "   1) Filtrati dupa o secventa din descrierea activitatii.\n";
	cout << "   2) Filtrati dupa tipul activitatii.\n";
	cout << "\n\tIntroduceti optiunea: ";
	
	const int option = get_option();

	if (option == 1)
	{
		string sequence;
		cin.get();
		cout << "  Introduceti secventa dupa care vreti sa filtrati: ";
		getline(cin, sequence);

		vector<Task> filtered_list;
		srv.filter_by_descr(sequence, filtered_list);
		
		print_list(filtered_list);
	}
	else if (option == 2)
	{
		string filter_type;
		cin.get();
		cout << "  Introduceti tipul dupa care vreti sa filtrati: ";
		getline(cin, filter_type);

		vector<Task> filtered_list;
		srv.filter_by_type(filter_type, filtered_list);

		print_list(filtered_list);
	}
	else
		cout << "\n\tOptiune invalida.\n";
}


void UIConsole::ui_sort_tasks() const
{
	cout << "\n\n----===+++ Sorteaza activitati +++===----\n\n";

	cout << "   1) Sortati activitatile dupa titlu.\n";
	cout << "   2) Sortati activitatile dupa lungimea descrierii.\n";
	cout << "   3) Sortati activitatile dupa durata + tip.\n";
	cout << "\n\tIntroduceti optiunea: ";

	const int option = get_option();

	if (option >= 1 && option <= 3)
	{
		vector<Task> sorted_list = srv.general_sort(srv.get_all_tasks(), option);

		print_list(sorted_list);
	}
	else
		cout << "\n\tOptiune invalida.\n";
}


void UIConsole::ui_get_raport() const
{
	map<string, int> type_freq = srv.get_raport();
	
	cout << "\n\tRaport frecventa tip:\n";
	
	for (const auto& el : type_freq)
	{
		cout << "\tTip: " << el.first << "\tFrecventa: " << el.second << "\n";
	}
	cout << "\n";
}


void UIConsole::ui_export_list() const
{
	string file_name;
	cin.get();
	cout << "\n   Introduceti titlul numele fisierului fara extensie: "; cin >> file_name;

	srv.export_current_list(file_name);
	cout << "\n\tExport realizat cu succes!\n";
}


void UIConsole::populate_list()
{
	srv.add_task("Nume vechi", "Cuvinte", "bowling", 3.2);
	srv.add_task("Nume nou", "Descriere mai lunga", "teme", 0.05);
	srv.add_task("Alte activitati", "Fara descriere", "scoala", 10.11);
	srv.add_task("Task nou", "Alta descriere", "sport", 10.11);
	srv.add_task("Nu mai am idei", "Descriere activitate", "facultate", 0.10);
	srv.add_task("Alt titlu", "Activitatea de alt tip", "alt tip2", 3.2);
	srv.add_task("Fara teme", "Nu am idei", "alte teme", 10.5);
	srv.add_task("Titlu", "Cuvinte pentru activitatetete", "alt tip", 3.2);
	srv.add_task("Activitate scoala", "Teme pentru facultate", "alte teme", 2.12);
	srv.add_task("Inca un task", "Vineri seara", "bowling", 1.21);
	srv.add_task("Curs geometrie", "Scriu doar chestii random", "sport", 0.20);
	srv.add_task("Nume iar", "Nu mai am idei", "facultate", 5.12);
	srv.add_task("Generez taskuri", "Proiect la OOP", "teme", 0.15);
	srv.add_task("Populez lista", "8 prezente la sport", "sport", 11.0);
	srv.add_task("Titlu de activitate", "Dau test la AG", "facultate", 3.2);
}