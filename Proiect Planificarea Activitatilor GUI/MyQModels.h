#pragma once
#include "Task.h"
#include <vector>
#include <QAbstractTableModel>

using std::vector;


class MyTableModel : public QAbstractTableModel
{
private:
	vector<Task> tasks_list;
public:
	MyTableModel(const vector<Task>& tasks) : tasks_list{ tasks } {}
	
	int rowCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return tasks_list.size();
	}
	
	int columnCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return 3;
	}
	
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override
	{
		if (role == Qt::DisplayRole)
		{
			Task task = tasks_list[index.row()];
			if (index.column() == 0)
				return QString::fromStdString(task.get_title());
			else if (index.column() == 1)
				return QString::fromStdString(task.get_type());
			else if (index.column() == 2)
				return QString::number(task.get_duration());
		}
		else if (role == Qt::UserRole)
		{
			Task task = tasks_list[index.row()];
			return QString::fromStdString(task.get_descr());
		}
		return QVariant{};
	}

	void set_tasks(const vector<Task>& tasks)
	{
		this->tasks_list = tasks;
		auto top_left = createIndex(0, 0);
		auto bottom_right = createIndex(rowCount(), columnCount());

		emit dataChanged(top_left, bottom_right);
		emit layoutChanged();
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override
	{
		if (role == Qt::DisplayRole)
		{
			if (orientation == Qt::Horizontal)
			{
				if (section == 0)
					return QString{ "TITLU" };
				else if (section == 1)
					return QString{ "TIP" };
				else if (section == 2)
					return QString{ "DURATA" };
			}
			else if (orientation == Qt::Vertical)
				return QString("%1").arg(section);
		}
		return QVariant{};
	}
};


class MyListModel : public QAbstractListModel
{
private:
	vector<Task> tasks_list;
public:
	MyListModel(const vector<Task> tasks) : tasks_list{ tasks } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return tasks_list.size();
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override
	{
		if (role == Qt::DisplayRole)
		{
			Task task = tasks_list[index.row()];
			return QString::fromStdString(task.get_title());
		}
		else if (role == Qt::UserRole)
		{
			Task task = tasks_list[index.row()];
			QString rez = QString::fromStdString(task.get_type()) + "///";
			rez += QString::fromStdString(task.get_descr()) + "///";
			rez += QString::number(task.get_duration());
			return rez;
		}
		return QVariant{};
	}

	void set_tasks(const vector<Task>& tasks)
	{
		this->tasks_list = tasks;
		auto top = createIndex(0, 0);
		auto bottom = createIndex(rowCount(), 0);
		emit dataChanged(top, bottom);
		emit layoutChanged();
	}
};