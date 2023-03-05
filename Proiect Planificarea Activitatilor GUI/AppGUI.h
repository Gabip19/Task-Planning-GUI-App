#pragma once
#include "Service.h"
#include "Observer.h"
#include "MyQModels.h"
#include <qwidget.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qformlayout.h>
#include <qlistwidget.h>
#include <qtablewidget.h>
#include <qheaderview.h>
#include <qradiobutton.h>
#include <qgroupbox.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qmessagebox.h>


class CurrentTasksMenu;
class CosReadOnlyGUI;

class TaskAppGUI : public QWidget, public Observer
{
private:

	TasksService& srv;

	// WIDGETS
	QWidget* main_wid_left = new QWidget;
	QWidget* main_wid_right = new QWidget;
	///QTableWidget* table;
	QTableView* table = new QTableView;
	MyTableModel* my_table_model;
	QLineEdit* txt_title;
	QLineEdit* txt_descr;
	QLineEdit* txt_type;
	QLineEdit* txt_duration;
	QLabel* crt_tasks_nr_label;
	
	// LAYOUTS
	QHBoxLayout* main_Hlayout = new QHBoxLayout;
	QVBoxLayout* left_VLayout = new QVBoxLayout;
	QVBoxLayout* right_VLayout = new QVBoxLayout;
	QGroupBox* sort_btns_box;

	// BUTTONS
	QRadioButton* BTN_sort_title;
	QRadioButton* BTN_sort_descr;
	QRadioButton* BTN_sort_type;
	QPushButton* BTN_SORT;
	QPushButton* BTN_store_task;
	QPushButton* BTN_modify_task;
	QPushButton* BTN_remove_task;
	QPushButton* BTN_filter_descr;
	QPushButton* BTN_filter_type;
	QPushButton* BTN_search_task;
	QPushButton* BTN_rfsh_list;
	QPushButton* BTN_get_raport;
	QPushButton* BTN_store_crt_task;
	QPushButton* BTN_clear_crt_tasks;
	QPushButton* BTN_crt_tasks_menu;
	QPushButton* BTN_crt_tasks_painter;
	QPushButton* BTN_undo_act;
	QPushButton* BTN_close_app;
	vector<QPushButton*> BTNs_vec;
	
	// FUNCTIONS
	void init_GUI_comps();
	void connect_comps();
	void reload_table(const vector<Task>& tasks_list);
	void reload_crt_tasks_number();
	void GUI_add_task();
	void GUI_modify_task();
	void GUI_remove_task();
	void GUI_search_task();
	void GUI_undo_act();
	void GUI_filter_descr();
	void GUI_filter_type();
	void GUI_sort_taks();
	void GUI_get_raport();
	void GUI_add_crt_task();
	
	// OBSERVERS FCT
	void update() override;

public:
	TaskAppGUI(TasksService& srv_) : srv{ srv_ }
	{
		srv.add_observer(this);
		init_GUI_comps();
		connect_comps();
		//reload_table(srv.get_all_tasks());
		reload_crt_tasks_number();
	}
	~TaskAppGUI()
	{
		srv.remove_observer(this);
	}
};


class CurrentTasksMENU : public QWidget, public Observer
{
private:

	TasksService& srv;

	// WIDGETS
	QWidget* main_wid_left = new QWidget;
	QWidget* main_wid_right = new QWidget;
	///QTableWidget* table;
	///QListWidget* list;
	QListView* list;
	MyListModel* my_list_model;
	QLineEdit* txt_title;
	QLineEdit* txt_descr;
	QLineEdit* txt_type;
	QLineEdit* txt_duration;
	QLineEdit* txt_rnd_num;
	QLineEdit* txt_file_name;

	// LAYOUTS
	QHBoxLayout* main_Hlayout = new QHBoxLayout;
	QVBoxLayout* left_VLayout = new QVBoxLayout;
	QVBoxLayout* right_VLayout = new QVBoxLayout;

	// BUTTONS
	QPushButton* BTN_add_rnd;
	QPushButton* BTN_export_list;
	QPushButton* BTN_clear_list;
	QPushButton* BTN_close_menu;

	// FUNCTIONS
	void init_GUI_comps();
	void connect_comps();
	void reload_table(const vector<Task>& crt_tasks_list);
	void reload_list(const vector<Task>& crt_tasks_list);

	// OBSERVERS FCT
	void update() override;

public:
	CurrentTasksMENU(TasksService& srv_) : srv{ srv_ }
	{
		setAttribute(Qt::WA_DeleteOnClose);
		srv.add_observer(this);
		init_GUI_comps();
		connect_comps();
		reload_list(srv.get_crt_tasks());
	}
	~CurrentTasksMENU()
	{
		srv.remove_observer(this);
	}
};


class CosReadOnlyGUI: public QWidget, public Observer
{
private:

	TasksService& srv;

	void paintEvent(QPaintEvent* ev) override;

	// OBSERVERS FCT
	void update() override;

public:
	CosReadOnlyGUI(TasksService& srv_) : srv{ srv_ }
	{
		setAttribute(Qt::WA_DeleteOnClose);
		setWindowTitle("Desenare Activitati Curente");
		srv.add_observer(this);
		update();
	}
	~CosReadOnlyGUI()
	{
		srv.remove_observer(this);
	}
};