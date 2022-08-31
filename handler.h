#pragma once

#ifndef __HANDLER_H__
#define __HANDLER_H__



class BookHandler
{
private:
	vector<User> UserList;
	vector<Book> BookList;

public:
	BookHandler()
	{}

	void InsertBook(string bookName, string bookKind, int bookNum) // 관리자 권한
	{
		BookList.push_back(Book(bookName, bookKind, bookNum));
	}

	void RentalBook(string _id) // 사용자 
	{

		int rentalnum;

		cout << "현재 전시되어 있는 책 목록입니다 \n";

		for (unsigned int i = 0; i < BookList.size(); i++)
			cout << "\n-" << i + 1 << ". " << BookList[i].GetBname() << '-' << "\n\n";

		printf("대여하실 책 번호를 입력해주세요 : ");
		cin >> rentalnum;

		//cout << "확인:" <<  book_Name << '\n';

		printf("------------------ 책 정보 -------------------\n");
		printf("              \n");
		cout << "  name : " << BookList[rentalnum - 1].GetBname() << "    \n";
		cout << "  kind : " << BookList[rentalnum - 1].GetBkind() << "    \n";
		printf("  count: %d    \n", BookList[rentalnum - 1].GetBnum());
		printf("               \n");
		printf("----------------------------------------------\n");

		printf("\n");

		int sel;
		printf("대여하시려면 1, 대여하지 않으시면 2를 입력해주세요 : ");
		cin >> sel;

		if (sel == 1)
		{
			if (BookList[rentalnum - 1].GetBnum() >= 1)
			{
				for (unsigned int i = 0; i < UserList.size(); i++)
				{
					if (UserList[i].GetId() == _id)
					{
						UserList[i].insertList(BookList[rentalnum - 1].GetBname());
						break;
					}
				}
				printf("\n대여가 완료되었습니다.\n\n");
				BookList[rentalnum - 1].setBnum("Rental");
			}
			else
				printf("\n현재 대여가 불가능한 책입니다.\n\n");

			return;
		}
		else
		{
			printf("\n메뉴화면으로 돌아갑니다.\n\n");
			return;
		}


	}




	void ReturnBook(string _id) // 사용자
	{
		int returnnum;
		int idx;
		int cnt = 1;



		for (unsigned int i = 0; i < UserList.size(); i++)
		{
			if (UserList[i].GetId() == _id)
			{

				if (!UserList[i].GetList().empty())
				{

					printf("현재 대여중인 책 목록입니다.\n");
					list<string> tmplist = UserList[i].GetList();
					auto it = tmplist.begin();

					for (it; it != tmplist.end(); it++)
					{
						printf("\n");
						cout << cnt << ". " << *it << "\n\n";
						cnt++;
					}
				}

				else
					printf("현재 대여중인 책이 없습니다. \n");

				idx = i;
				break;
			}
		}

		if (!UserList[idx].GetList().empty())
		{
			printf("반납하실 책 번호를 입력해주세요 : ");
			cin >> returnnum;

			string book_name;
			list<string> tmplist = UserList[idx].GetList();
			auto it = tmplist.begin();
			cnt = 1;
			for (it; it != tmplist.end();)
			{
				if (cnt == returnnum)
				{
					book_name = *it;
					printf("------------------ 책 제목 -------------------\n");
					cout << " name : " << book_name << '\n';
					printf("----------------------------------------------\n");

					int sel;
					printf("반납하시려면 1, 반납하지 않으시면 2를 입력해주세요 : ");
					cin >> sel;

					if (sel == 1)
					{
						tmplist.erase(it++);

						//UserList[idx].eraseList(it);
						printf("반납이 완료되었습니다.\n");


						UserList[idx].SetList(tmplist);
						for (unsigned int i = 0; i < BookList.size(); i++)
						{
							if (BookList[i].GetBname() == book_name)
							{
								BookList[i].setBnum("Return");
								break;
							}
						}
						return;
					}

					else
					{
						printf("메뉴화면으로 돌아갑니다.\n");
						return;
					}


				}
				else
					it++;
				cnt++;
			}
		}
		return;

	}

	void CheckBookList() const
	{
		for (unsigned int i = 0; i < BookList.size(); i++)
			cout << '-' << BookList[i].GetBname() << '-' << '\n';
	}

	vector<Book> GetBookList() const
	{
		return BookList;
	}

	vector<User> GetUserList() const
	{
		return UserList;
	}

	void SetUserList(string _id, string _name, string _birth)
	{
		UserList.push_back(User(_id, _name, _birth));
	}

	void ShowAllBookInfo() const // 현재 등록된 책 정보들 출력
	{
		printf("\n");
		printf("--------------------------------------------------------------------------------\n");
		for (unsigned int i = 0; i < BookList.size(); i++)
		{

			BookList[i].ShowBookInfo();
			cout << '\n';
		}

		printf("--------------------------------------------------------------------------------\n");
	}
};

#endif
#pragma once
