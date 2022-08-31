
#pragma once

#include <iostream>
#include <string>



using namespace std;

#ifndef __BOOK_H__
#define __BOOK_H__


class Book
{
private:
	string Bname; // 책 이름
	string Bkind; // 책 종류 
	int Bnum; // 책 수량  1개이상이어야 대여가능. 반납시 + 1 대여시 - 1

public:
	Book(string _Bname, string _Bkind, int _Bnum) : Bname(_Bname), Bkind(_Bkind), Bnum(_Bnum)
	{}

	string GetBname() const
	{
		return Bname;
	}

	string GetBkind() const
	{
		return Bkind;
	}

	int GetBnum() const
	{
		return Bnum;
	}

	void setBnum(string s) // s가 대여면 -1 s가 반납이면 + 1
	{

		if (s == "Rental")
			Bnum--;


		else if (s == "Return")
		{
			Bnum++;
		}
	}

	void ShowBookInfo() const
	{
		cout << "책 제목 : " << Bname << '\n';
		cout << "책 종류 : " << Bkind << '\n';
		cout << "책 개수 : " << Bnum << '\n';
	}

};

#endif
