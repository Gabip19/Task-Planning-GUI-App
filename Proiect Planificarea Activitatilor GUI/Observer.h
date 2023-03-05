#pragma once

#include <vector>
#include <algorithm>

using std::vector;


class Observer
{
public:
	virtual void update() = 0;
};


class Observable
{
private:
	vector<Observer*> observers;
public:
	void add_observer(Observer* obs)
	{
		observers.push_back(obs);
	}
	void remove_observer(Observer* obs)
	{
		observers.erase(std::find(observers.begin(), observers.end(), obs));
	}
protected:
	void notify()
	{
		for (auto obs : observers)
			obs->update();
	}
};