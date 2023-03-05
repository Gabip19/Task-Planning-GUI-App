#pragma once
#include "Repository.h"


class UndoAction
{
public:	
	virtual void do_undo() = 0;
	virtual ~UndoAction() = default;
};


class UndoAdd : public UndoAction
{
private:
	TasksRepositoryAbs& repo;
	Task added_task;

public:
	UndoAdd(TasksRepositoryAbs& rep, const Task& task) :
		repo{ rep },
		added_task{ task }{};
	
	void do_undo() override
	{
		repo.remove(added_task);
	}
};


class UndoRemove : public UndoAction
{
private:
	TasksRepositoryAbs& repo;
	Task removed_task;

public:
	UndoRemove(TasksRepositoryAbs& rep, const Task& task) :
		repo{ rep },
		removed_task{ task }{};
	
	void do_undo() override
	{
		repo.store(removed_task);
	}
};


class UndoModify : public UndoAction
{
private:
	TasksRepositoryAbs& repo;
	Task old_task;
	Task updated_task;

public:
	UndoModify(TasksRepositoryAbs& rep, const Task& oldtsk, const Task& updtsk) :
		repo{ rep },
		old_task{ oldtsk },
		updated_task{ updtsk }{};
	
	void do_undo() override
	{
		const auto index = repo.find(updated_task);
		repo.update(index, old_task);
	}
};