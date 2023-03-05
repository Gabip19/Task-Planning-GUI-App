#include "ProiectPlanificareaActivitatilorGUI.h"
#include <QtWidgets/QApplication>
#include "AppGUI.h"
#include "TEST repo_map.h"


void test_all()
{
	test_get_set();
	test_repo_store();
	test_repo_update();
	test_repo_remove();
	test_repo_size();
	test_equal_tasks();
	test_repo_find();
	test_validate_task();
	test_srv_add_task();
	test_srv_modifiy_task();
	test_srv_delete_task();
	test_srv_size();
	test_srv_search_task();
	test_srv_filter_descr();
	test_srv_filter_type();
	test_srv_sort();
	test_size_ct();
	test_store_task_ct();
	test_clear_all_ct();
	test_add_task_ct();
	test_empty_current_list();
	test_add_random_tasks_ct();
	test_export_ct_list();
	test_get_raport();
	test_undo();
	test_repo_map();
}


void run_app(int argc, char* argv[])
{
	TasksRepository repo;
	CurrentTasks crt_repo;
	TaskValidator val;
	TasksService srv{ repo, val, crt_repo };
	srv.populate_list();

	QApplication app(argc, argv);
	TaskAppGUI wGUI{ srv };
	wGUI.show();
	app.exec();
}


int main(int argc, char *argv[])
{
	test_all();
	run_app(argc, argv);
	return 0;
}