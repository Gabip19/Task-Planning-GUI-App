#include "AppGUI.h"
#include "Exceptions.h"
#include <cstdlib>
#include <ctime>
#include <qpainter.h>



void TaskAppGUI::init_GUI_comps()
{
	this->setLayout(main_Hlayout);
	this->setWindowTitle("Aplicatie Planificare Activitati");
	
	// LEFT SIDE
	main_wid_left->setLayout(left_VLayout);

	// Title
	QLabel* title_label_right = new QLabel("Lista de activitati:");
	title_label_right->setFont(QFont("Times", 12));
	left_VLayout->addWidget(title_label_right);

	// Table widget
	my_table_model = new MyTableModel(srv.get_all_tasks());
	table->setModel(my_table_model);
	
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//QStringList header_text;
	//header_text << "TITLU" << "TIP" << "DURATA";
	//table->setHorizontalHeaderLabels(header_text);
	///table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	///table->horizontalHeader()->setStretchLastSection(true);

	//table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	
	left_VLayout->addWidget(table);
	
	left_VLayout->addSpacing(20);

	// Sort buttons widget
	sort_btns_box = new QGroupBox("Sorteaza lista");
	QVBoxLayout* sort_layout = new QVBoxLayout;
	sort_btns_box->setLayout(sort_layout);

	BTN_sort_title = new QRadioButton("Sorteaza dupa titlu");
	BTN_sort_descr = new QRadioButton("Sorteaza dupa descriere");
	BTN_sort_type = new QRadioButton("Sorteaza dupa durata + tip");
	BTN_SORT = new QPushButton("SO&R&TEAZA");
	BTN_sort_title->setChecked(true);

	sort_layout->addWidget(BTN_sort_title);
	sort_layout->addWidget(BTN_sort_descr);
	sort_layout->addWidget(BTN_sort_type);
	sort_layout->addWidget(BTN_SORT);
	
	left_VLayout->addWidget(sort_btns_box);


	main_Hlayout->addWidget(main_wid_left);

	

	// RIGHT SIDE
	main_wid_right->setLayout(right_VLayout);
	
	// Title label
	QLabel* title_label_left = new QLabel("  Date activitate:");
	title_label_left->setFont(QFont("Times", 12));
	right_VLayout->addWidget(title_label_left);

	// Form widget
	QWidget* form_widget = new QWidget;
	QFormLayout* form_layout = new QFormLayout;
	form_widget->setLayout(form_layout);

	// Form elems
	txt_title = new QLineEdit;
	txt_descr = new QLineEdit;
	txt_type = new QLineEdit;
	txt_duration = new QLineEdit;
	form_layout->addRow(new QLabel("Titlu:"), txt_title);
	form_layout->addRow(new QLabel("Descriere:"), txt_descr);
	form_layout->addRow(new QLabel("Tip:"), txt_type);
	form_layout->addRow(new QLabel("Durata:"), txt_duration);
	
	right_VLayout->addWidget(form_widget);


	// Operation Buttons Widget
	QWidget* op_btn_wid = new QWidget;
	QHBoxLayout* op_btn_layout = new QHBoxLayout;
	op_btn_wid->setLayout(op_btn_layout);

	BTN_store_task = new QPushButton("&ADAUGA");
	BTN_modify_task = new QPushButton("&MODIFICA");
	BTN_remove_task = new QPushButton("&STERGE");
	op_btn_layout->addWidget(BTN_store_task);
	op_btn_layout->addWidget(BTN_modify_task);
	op_btn_layout->addWidget(BTN_remove_task);

	right_VLayout->addWidget(op_btn_wid);

	// Filter Buttons + Search Button Widget
	QWidget* filter_btn_wid = new QWidget;
	QHBoxLayout* filter_btn_layout = new QHBoxLayout;
	filter_btn_wid->setLayout(filter_btn_layout);

	BTN_filter_descr = new QPushButton("Filtreaza descriere");
	BTN_filter_type = new QPushButton("Filtreaza tip");
	BTN_search_task = new QPushButton("CAU&TA");
	filter_btn_layout->addWidget(BTN_filter_descr);
	filter_btn_layout->addWidget(BTN_filter_type);
	filter_btn_layout->addWidget(BTN_search_task);

	right_VLayout->addWidget(filter_btn_wid);

	right_VLayout->addSpacing(10);

	// Refresh Button + Get Raport Button
	QWidget* rfr_gr_wid = new QWidget;
	QHBoxLayout* rfr_gr_layout = new QHBoxLayout;
	rfr_gr_wid->setLayout(rfr_gr_layout);

	// Refresh Button
	BTN_rfsh_list = new QPushButton("Re&fresh lista de activitati");
	rfr_gr_layout->addWidget(BTN_rfsh_list);

	// Get Raport Button
	BTN_get_raport = new QPushButton("Raport frecventa tip");
	rfr_gr_layout->addWidget(BTN_get_raport);

	right_VLayout->addWidget(rfr_gr_wid);

	// Store task to current tasks list
	BTN_store_crt_task = new QPushButton("Adauga la activitati curente");
	right_VLayout->addWidget(BTN_store_crt_task);

	// Clear Current Tasks Button
	BTN_clear_crt_tasks = new QPushButton("Goleste lista activitati curente");
	right_VLayout->addWidget(BTN_clear_crt_tasks);

	// Current Tasks Menu Button
	BTN_crt_tasks_menu = new QPushButton("ACTIVITATI &CURENTE");
	right_VLayout->addWidget(BTN_crt_tasks_menu);

	// Current Tasks Painter Button
	BTN_crt_tasks_painter = new QPushButton("&DESENARE ACTIVITATI");
	right_VLayout->addWidget(BTN_crt_tasks_painter);

	// Current Tasks number
	right_VLayout->addSpacing(10);
	crt_tasks_nr_label = new QLabel;
	crt_tasks_nr_label->setIndent(15);
	right_VLayout->addWidget(crt_tasks_nr_label);

	right_VLayout->addStretch();

	// Filter Type Buttons
	//QGroupBox* btns_group = new QGroupBox("Tipuri activitati");
	//QVBoxLayout* btns_group_layout = new QVBoxLayout;
	//btns_group->setLayout(btns_group_layout);
	//map<string, int> types = srv.get_raport();
	//
	//for (const auto& type : types)
	//{
	//	QPushButton* new_btn = new QPushButton(QString::fromStdString(type.first));
	//	BTNs_vec.push_back(new_btn);
	//	btns_group_layout->addWidget(new_btn);
	//}
	//
	//right_VLayout->addWidget(btns_group);

	// Close app button and Undo button
	QWidget* close_btn_wid = new QWidget;
	QHBoxLayout* close_btn_layout = new QHBoxLayout;
	close_btn_wid->setLayout(close_btn_layout);

	BTN_close_app = new QPushButton("E&XIT");
	BTN_undo_act = new QPushButton("&UNDO");
	close_btn_layout->addStretch();
	close_btn_layout->addWidget(BTN_undo_act);
	close_btn_layout->addWidget(BTN_close_app);

	right_VLayout->addWidget(close_btn_wid);

	main_Hlayout->addWidget(main_wid_right);
}


void TaskAppGUI::connect_comps()
{
	// Elemente Tabel Stanga si Form Texts Dreapta
	QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
			auto sel_items_indexes = table->selectionModel()->selectedIndexes();
			if (sel_items_indexes.isEmpty())
			{
				txt_title->setText("");
				txt_descr->setText("");
				txt_type->setText("");
				txt_duration->setText("");
			}
			else
			{
				auto sel_row_index = sel_items_indexes.at(0).row();
				auto cell0 = table->model()->index(sel_row_index, 0);
				auto cell1 = table->model()->index(sel_row_index, 1);
				auto cell2 = table->model()->index(sel_row_index, 2);

				auto title_str = table->model()->data(cell0, Qt::DisplayRole).toString();
				auto type_str = table->model()->data(cell1, Qt::DisplayRole).toString();
				auto duration_str = table->model()->data(cell2, Qt::DisplayRole).toString();
				auto descr_str = table->model()->data(sel_items_indexes.at(0), Qt::UserRole).toString();
				
				txt_title->setText(title_str);
				txt_descr->setText(descr_str);
				txt_type->setText(type_str);
				txt_duration->setText(duration_str);
			}
		}
	);

	// Sort Button
	QObject::connect(BTN_SORT, &QPushButton::clicked, this, &TaskAppGUI::GUI_sort_taks);

	// Store Button
	QObject::connect(BTN_store_task, &QPushButton::clicked, this, &TaskAppGUI::GUI_add_task);

	// Modify Button
	QObject::connect(BTN_modify_task, &QPushButton::clicked, this, &TaskAppGUI::GUI_modify_task);

	// Remove Button
	QObject::connect(BTN_remove_task, &QPushButton::clicked, this, &TaskAppGUI::GUI_remove_task);

	// Filter by description
	QObject::connect(BTN_filter_descr, &QPushButton::clicked, this, &TaskAppGUI::GUI_filter_descr);

	// Filter by type
	QObject::connect(BTN_filter_type, &QPushButton::clicked, this, &TaskAppGUI::GUI_filter_type);

	// Search Button
	QObject::connect(BTN_search_task, &QPushButton::clicked, this, &TaskAppGUI::GUI_search_task);

	// Refresh list Button
	QObject::connect(BTN_rfsh_list, &QPushButton::clicked, [&]() {
			reload_table(srv.get_all_tasks());
			reload_crt_tasks_number();
		}
	);

	// Add task to current tasks list
	QObject::connect(BTN_store_crt_task, &QPushButton::clicked, this, &TaskAppGUI::GUI_add_crt_task);

	// Clear current tasks
	QObject::connect(BTN_clear_crt_tasks, &QPushButton::clicked, [&]() {
			srv.empty_current_list();
		}
	);

	// Get Raport Button
	QObject::connect(BTN_get_raport, &QPushButton::clicked, this, &TaskAppGUI::GUI_get_raport);

	// Current Task Menu Button
	QObject::connect(BTN_crt_tasks_menu, &QPushButton::clicked, [&]() {
			CurrentTasksMENU* crt_menu = new CurrentTasksMENU(srv);
			//crt_menu->setWindowModality(Qt::ApplicationModal);
			crt_menu->show();
		}
	);

	// Current Tasks Painter Button
	QObject::connect(BTN_crt_tasks_painter, &QPushButton::clicked, [&]() {
			CosReadOnlyGUI* tasks_painter = new CosReadOnlyGUI(srv);
			tasks_painter->show();
		}
	);

	// Type Freq Buttons
	for (const auto& button : BTNs_vec)
	{
		QObject::connect(button, &QPushButton::clicked, [&]() {
				map<string, int> raport = srv.get_raport();

				QString type = button->text();
				int freq = raport[type.toStdString()];

				QMessageBox::information(this, type, QString::number(freq));
			}
		);
	}

	// Undo Button
	QObject::connect(BTN_undo_act, &QPushButton::clicked, this, &TaskAppGUI::GUI_undo_act);

	// Close App Button
	QObject::connect(BTN_close_app, &QPushButton::clicked, [&]() {
			int ret = QMessageBox::question(this, "EXIT APPLICATION", "Esti sigur ca vrei sa inchizi aplicatia?");
			if (ret == QMessageBox::Yes)
				this->close();
		}
	);
}


void TaskAppGUI::reload_table(const vector<Task>& tasks_list)
{
	///	table->clearContents();
	///	table->setRowCount(tasks_list.size());
	///	int row_num = 0;
	///
	///	for (const auto& task : tasks_list)
	///	{
	///		table->setItem(row_num, 0, new QTableWidgetItem(QString::fromStdString(task.get_title())));
	///		table->setItem(row_num, 1, new QTableWidgetItem(QString::fromStdString(task.get_type())));
	///		table->setItem(row_num, 2, new QTableWidgetItem(QString::number(task.get_duration())));
	///		table->item(row_num, 0)->setData(Qt::UserRole, QString::fromStdString(task.get_descr()));
	///		++row_num;
	///	}

	my_table_model->set_tasks(tasks_list);
}


void TaskAppGUI::reload_crt_tasks_number()
{
	QString string = "Nr. activitati curente: ";
	string += QString::number(srv.size_ct());
	crt_tasks_nr_label->setText(string);
}


void TaskAppGUI::GUI_add_task()
{
	auto title_str = txt_title->text().toStdString();
	auto descr_str = txt_descr->text().toStdString();
	auto type_str = txt_type->text().toStdString();
	auto duration_db = txt_duration->text().toDouble();

	try
	{
		srv.add_task(title_str, descr_str, type_str, duration_db);
		reload_table(srv.get_all_tasks());
		QMessageBox::information(this, "INFO", "Activitate adaugata cu succes.");
	}
	catch (RepositoryException& expt)
	{
		QMessageBox::warning(this, "EROARE", QString::fromStdString(expt.get_error_messages()));
	}
	catch (ValidationException& expt)
	{
		QMessageBox::warning(this, "EROARE", QString::fromStdString(expt.get_error_messages()));
	}
}


void TaskAppGUI::GUI_modify_task()
{
	auto new_descr_str = txt_descr->text().toStdString();
	auto new_type_str = txt_type->text().toStdString();
	auto new_duration_db = txt_duration->text().toDouble();

	try
	{
		auto selected_item = table->selectionModel()->selectedIndexes();
		if (selected_item.isEmpty())
		{
			QMessageBox::warning(this, "EROARE", "Nicio activitate selectata.");
		}

		auto title_str = table->model()->data(selected_item.at(0), Qt::DisplayRole).toString();
		auto type_str = table->model()->data(selected_item.at(1), Qt::DisplayRole).toString();
		auto duration_str = table->model()->data(selected_item.at(2), Qt::DisplayRole).toString();
		
		srv.modify_task(
			title_str.toStdString(), 
			type_str.toStdString(), 
			duration_str.toDouble(),
			new_descr_str, 
			new_type_str, 
			new_duration_db
		);

		reload_table(srv.get_all_tasks());
		QMessageBox::information(this, "INFO", "Activitate modificata cu succes.");
	}
	catch (RepositoryException& expt)
	{
		QMessageBox::warning(this, "EROARE", QString::fromStdString(expt.get_error_messages()));
	}
	catch (ValidationException& expt)
	{
		QMessageBox::warning(this, "EROARE", QString::fromStdString(expt.get_error_messages()));
	}
}


void TaskAppGUI::GUI_remove_task()
{
	auto title_str = txt_title->text().toStdString();
	auto type_str = txt_type->text().toStdString();
	auto duration_db = txt_duration->text().toDouble();

	try
	{
		srv.delete_task(title_str, type_str, duration_db);
		reload_table(srv.get_all_tasks());
		QMessageBox::information(this, "INFO", "Activitate stearsa cu succes.");
	}
	catch (RepositoryException& expt)
	{
		QMessageBox::warning(this, "EROARE", QString::fromStdString(expt.get_error_messages()));
	}
	catch (ValidationException& expt)
	{
		QMessageBox::warning(this, "EROARE", QString::fromStdString(expt.get_error_messages()));
	}
}


void TaskAppGUI::GUI_search_task()
{
	auto title_str = txt_title->text().toStdString();
	auto type_str = txt_type->text().toStdString();
	auto duration_db = txt_duration->text().toDouble();

	try
	{
		const Task& found_task = srv.search_task(title_str, type_str, duration_db);
		string task_str = "TITLU: " + found_task.get_title() + "\n";
		task_str += "DESCRIERE: " + found_task.get_descr() + "\n";
		task_str += "TIP: " + found_task.get_type() + "\nDURATA: ";
		
		QString task_Qstr = QString::fromStdString(task_str);
		task_Qstr += QString::number(found_task.get_duration());

		QMessageBox::information(this, "Activitatea cautata este:", task_Qstr);
	}
	catch (RepositoryException& expt)
	{
		QMessageBox::warning(this, "EROARE", QString::fromStdString(expt.get_error_messages()));
	}
	catch (ValidationException& expt)
	{
		QMessageBox::warning(this, "EROARE", QString::fromStdString(expt.get_error_messages()));
	}
}


void TaskAppGUI::GUI_undo_act()
{
	try
	{
		srv.undo();
		reload_table(srv.get_all_tasks());
	}
	catch (RepositoryException& expt)
	{
		QMessageBox::warning(this, "EROARE", QString::fromStdString(expt.get_error_messages()));
	}
}


void TaskAppGUI::GUI_filter_descr()
{
	vector<Task> filtered_list;
	string sequence = txt_descr->text().toStdString();
	srv.filter_by_descr(sequence, filtered_list);
	reload_table(filtered_list);
}


void TaskAppGUI::GUI_filter_type()
{
	vector<Task> filtered_list;
	string type_str = txt_type->text().toStdString();
	srv.filter_by_type(type_str, filtered_list);
	reload_table(filtered_list);
}


void TaskAppGUI::GUI_sort_taks()
{
	int option = 0;
	if (BTN_sort_title->isChecked())
		option = 1;
	else if (BTN_sort_descr->isChecked())
		option = 2;
	else if (BTN_sort_type->isChecked())
		option = 3;

	const vector<Task> sorted_list = srv.general_sort(srv.get_all_tasks(), option);
	reload_table(sorted_list);
}


void TaskAppGUI::GUI_get_raport()
{
	map<string, int> result_map = srv.get_raport();

	QTableWidget* raport_table = new QTableWidget(result_map.size(), 2);
	
	QStringList header_labels;
	header_labels << "Tip" << "Frecventa";
	raport_table->setHorizontalHeaderLabels(header_labels);
	raport_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
	int index = 0;
	for (const auto& pair : result_map)
	{
		raport_table->setItem(index, 0, new QTableWidgetItem(QString::fromStdString(pair.first)));
		raport_table->setItem(index, 1, new QTableWidgetItem(QString::number(pair.second)));
		++index;
	}

	raport_table->setWindowModality(Qt::ApplicationModal);
	raport_table->show();
}


void TaskAppGUI::GUI_add_crt_task()
{
	auto task_title = txt_title->text().toStdString();

	try
	{
		srv.add_task_ct(task_title);
		QMessageBox::information(this, "INFO", "Activitate adaugata la lista curenta.");
	}
	catch (RepositoryException& expt)
	{
		QMessageBox::warning(this, "EROARE", QString::fromStdString(expt.get_error_messages()));
	}
}


void TaskAppGUI::update()
{
	reload_crt_tasks_number();
}




// CURRENT TASK MENU

void CurrentTasksMENU::init_GUI_comps()
{
	this->setLayout(main_Hlayout);
	this->setWindowTitle("Meniu activitati curente");

	// LEFT SIDE
	main_wid_left->setLayout(left_VLayout);

	// Title Label
	QLabel* title_label = new QLabel("Lista activitati curente:");
	title_label->setFont(QFont("Times", 12));
	left_VLayout->addWidget(title_label);

	// Tasks Table
	/*
	table = new QTableWidget{ 0, 3 };

	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	QStringList header_text;
	header_text << "TITLU" << "TIP" << "DURATA";
	table->setHorizontalHeaderLabels(header_text);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);

	left_VLayout->addWidget(table);

	main_Hlayout->addWidget(main_wid_left);
	*/

	// Varianta cu lista
	//list = new QListWidget;
	//list->setSelectionMode(QAbstractItemView::SingleSelection);
	my_list_model = new MyListModel(srv.get_crt_tasks());
	list = new QListView;
	list->setModel(my_list_model);
	list->setSelectionMode(QAbstractItemView::SingleSelection);
	left_VLayout->addWidget(list);
	main_Hlayout->addWidget(main_wid_left);

	// RIGHT SIDE
	main_wid_right->setLayout(right_VLayout);

	// Title label
	QLabel* title_label_r = new QLabel("  Date activitate:");
	title_label_r->setFont(QFont("Times", 12));
	right_VLayout->addWidget(title_label_r);

	// Form widget
	QWidget* form_widget = new QWidget;
	QFormLayout* form_layout = new QFormLayout;
	form_widget->setLayout(form_layout);

	// Form elems
	txt_title = new QLineEdit;
	txt_descr = new QLineEdit;
	txt_type = new QLineEdit;
	txt_duration = new QLineEdit;
	form_layout->addRow(new QLabel("Titlu:"), txt_title);
	form_layout->addRow(new QLabel("Descriere:"), txt_descr);
	form_layout->addRow(new QLabel("Tip:"), txt_type);
	form_layout->addRow(new QLabel("Durata:"), txt_duration);

	right_VLayout->addWidget(form_widget);

	// ADD RANDOM TASKS
	// Form Layout
	QWidget* rnd_form_wid = new QWidget;
	QFormLayout* rnd_form_layout = new QFormLayout;
	rnd_form_wid->setLayout(rnd_form_layout);
	txt_rnd_num = new QLineEdit;
	rnd_form_layout->addRow(new QLabel("Numar activitati:"), txt_rnd_num);
	
	right_VLayout->addWidget(rnd_form_wid);

	// ADD RND button
	BTN_add_rnd = new QPushButton("&Adauga activitati aleatoriu");
	rnd_form_layout->addWidget(BTN_add_rnd);

	// Export list
	txt_file_name = new QLineEdit;
	rnd_form_layout->addRow(new QLabel("Nume fisier export:"), txt_file_name);
	// Export list button
	BTN_export_list = new QPushButton("&Exporta");
	rnd_form_layout->addWidget(BTN_export_list);

	right_VLayout->addSpacing(15);

	// Clear list button
	BTN_clear_list = new QPushButton("&Goleste lista");
	right_VLayout->addWidget(BTN_clear_list);

	right_VLayout->addStretch();

	// Close Button widget
	QWidget* close_btn_wid = new QWidget;
	QHBoxLayout* close_btn_layout = new QHBoxLayout;
	close_btn_wid->setLayout(close_btn_layout);
	BTN_close_menu = new QPushButton("E&XIT");

	close_btn_layout->addStretch();
	close_btn_layout->addWidget(BTN_close_menu);

	right_VLayout->addWidget(close_btn_wid);

	main_Hlayout->addWidget(main_wid_right);
}


void CurrentTasksMENU::connect_comps()
{
	// Elemente tabel stanga si form texts dreapta
	/*QObject::connect(table, &QTableWidget::itemSelectionChanged, [&]() {
			auto selected_items = table->selectedItems();
			if (selected_items.isEmpty())
			{
				txt_title->setText("");
				txt_descr->setText("");
				txt_type->setText("");
				txt_duration->setText("");
			}
			else
			{
				auto title_str = selected_items.at(0)->text();
				auto type_str = selected_items.at(1)->text();
				auto duration_str = selected_items.at(2)->text();
				auto descr_str = selected_items.at(0)->data(Qt::UserRole).toString();

				txt_title->setText(title_str);
				txt_descr->setText(descr_str);
				txt_type->setText(type_str);
				txt_duration->setText(duration_str);
			}
		}
	);*/

	// List items si form text dreapta
	//QObject::connect(list, &QListWidget::itemSelectionChanged, [&]() {
	//		auto selected_items = list->selectedItems();
	//		if (selected_items.isEmpty())
	//		{
	//			txt_title->setText("");
	//			txt_descr->setText("");
	//			txt_type->setText("");
	//			txt_duration->setText("");
	//		}
	//		else
	//		{
	//			auto title_str = selected_items.at(0)->text();
	//			auto texts = selected_items.at(0)->data(Qt::UserRole).toString();
	//
	//			QStringList text_list = texts.split("///");
	//			QString type_str = text_list.at(0);
	//			QString descr_str = text_list.at(1);
	//			QString duration_str = text_list.at(2);
	//
	//			txt_title->setText(title_str);
	//			txt_descr->setText(descr_str);
	//			txt_type->setText(type_str);
	//			txt_duration->setText(duration_str);
	//		}
	//	}
	//);

	// List View si Forms dreapta
	QObject::connect(list->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
			auto selected_item = list->selectionModel()->selectedIndexes();
			if (selected_item.isEmpty())
			{
				txt_title->setText("");
				txt_descr->setText("");
				txt_type->setText("");
				txt_duration->setText("");
			}
			else
			{
				auto& selected_index = selected_item.at(0);
				auto title_str = selected_index.data(Qt::DisplayRole).toString();
				auto data_txt_list = selected_index.data(Qt::UserRole).toString().split("///");

				auto& type_str = data_txt_list.at(0);
				auto& descr_str = data_txt_list.at(1);
				auto& duration_str = data_txt_list.at(2);

				txt_title->setText(title_str);
				txt_descr->setText(descr_str);
				txt_type->setText(type_str);
				txt_duration->setText(duration_str);
			}
		}
	);

	// Add random tasks
	QObject::connect(BTN_add_rnd, &QPushButton::clicked, [&]() {
			int number = txt_rnd_num->text().toInt();
			if (0 < number && number <= srv.size())
			{
				srv.add_random_tasks_ct(number);
				QMessageBox::information(this, "INFO", "Activitati adaugate cu succes.");
			}
			else
			{
				QString message = "Numarul trebuie sa fie cuprins intre 0 si " + QString::number(srv.size());
				QMessageBox::warning(this, "EROARE", message);
			}
		}
	);

	// Export list
	QObject::connect(BTN_export_list, &QPushButton::clicked, [&]() {
			auto file_name = txt_file_name->text().toStdString();
			srv.export_current_list(file_name);
			QMessageBox::information(this, "INFO", "Export realizat cu succes.");
		}
	);

	// Clear current tasks list
	QObject::connect(BTN_clear_list, &QPushButton::clicked, [&]() {
			srv.empty_current_list();
			QMessageBox::information(this, "INFO", "Lista curenta de activitati a fost golita.");
		}
	);
	
	// Close App Button
	QObject::connect(BTN_close_menu, &QPushButton::clicked, [&]() {
			this->close();
		}
	);
}


void CurrentTasksMENU::reload_table(const vector<Task>& crt_tasks_list)
{
	//table->clearContents();
	//table->setRowCount(crt_tasks_list.size());
	//int row_num = 0;

	//for (const auto& task : crt_tasks_list)
	//{
	//	table->setItem(row_num, 0, new QTableWidgetItem(QString::fromStdString(task.get_title())));
	//	table->setItem(row_num, 1, new QTableWidgetItem(QString::fromStdString(task.get_type())));
	//	table->setItem(row_num, 2, new QTableWidgetItem(QString::number(task.get_duration())));
	//	table->item(row_num, 0)->setData(Qt::UserRole, QString::fromStdString(task.get_descr()));
	//	++row_num;
	//}
}


void CurrentTasksMENU::reload_list(const vector<Task>& crt_tasks_list)
{
	///list->clear();
	///for (const auto& task : crt_tasks_list)
	///{
	///	auto item = new QListWidgetItem(QString::fromStdString(task.get_title()));
	///	list->addItem(item);
	///	QString texts = QString::fromStdString(task.get_type()) + "///";
	///	texts += QString::fromStdString(task.get_descr()) + "///";
	///	texts += QString::number(task.get_duration());
	///	item->setData(Qt::UserRole, texts);
	///}
	my_list_model->set_tasks(crt_tasks_list);
}


void CurrentTasksMENU::update()
{
	reload_list(srv.get_crt_tasks());
}




// CURRENT TASK READ ONLY

void CosReadOnlyGUI::paintEvent(QPaintEvent* ev)
{
	setPalette(QPalette(Qt::darkCyan));
	QPainter p{ this };
	p.setBackgroundMode(Qt::OpaqueMode);

	srand(time(0));
	//p.drawRect(0, 0, 50, 50);
	//p.drawRect(width()-50, 0, 50, 50);
	//p.drawRect(width()-50, height()-50, 50, 50);
	//p.drawRect(0, height()-50, 50, 50);

	for (const auto& task : srv.get_crt_tasks())
	{
		int shape_to_draw = rand() % 4;
		int position_x = 20 + rand() % (width() - 141);	// intre 20 si width - 120
		int position_y = 20 + rand() % (height() - 141);
		int _height = 50 + rand() % 51; // nr intre 50 si 100
		int _width = 50 + rand() % 51;

		vector<QColor> colors = {
			Qt::red,
			Qt::blue,
			Qt::green,
			Qt::yellow,
			Qt::gray,
			Qt::black,
			Qt::magenta,
			Qt::cyan,
			Qt::white,
			Qt::darkMagenta,
			Qt::darkGreen,
		};

		int color_type = rand() % colors.size();
		QColor color = colors.at(color_type);

		p.setBrush(QBrush(color));

		switch (shape_to_draw)
		{
		case 0:
			p.drawEllipse(position_x, position_y, _width, _height);
			break;
		case 1:
			p.drawRect(position_x, position_y, _width, _height);
			break;
		case 2:
			p.drawRect(position_x, position_y, _width, _width);
			break;
		case 3:
			p.drawEllipse(position_x, position_y, _height, _height);
			break;
		default:
			break;
		}
	}
}


void CosReadOnlyGUI::update()
{
	repaint();
}