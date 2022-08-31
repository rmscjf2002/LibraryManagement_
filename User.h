#pragma once

#ifndef __USER_H__
#define __USER_H__


class User
{
private:
	string id, name, birth;
	list<string> rentalList;


public:
	User(string _id, string _name, string _birth) : id(_id), name(_name), birth(_birth)
	{}

	string GetId() const
	{
		return id;
	}

	string GetName() const
	{
		return name;
	}

	string GetBirth() const
	{
		return birth;
	}

	list<string> GetList() const
	{
		return rentalList;
	}

	void SetList(list<string> _list)
	{
		rentalList.clear();

		while (!_list.empty())
		{
			rentalList.push_back(_list.front());
			_list.pop_front();
		}

	}

	void insertList(string _name)
	{
		rentalList.push_back(_name);
	}

	void eraseList(list<string>::iterator _iter)
	{
		rentalList.erase(_iter);
	}

	void ShowRentalInfo() const
	{
		auto iter = rentalList.begin();

		for (iter; iter != rentalList.end(); iter++)
		{
			cout << *iter << "\n\n";
		}
	}

};

#endif
#pragma once
