#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <tuple>
#include <list>
#include <algorithm>
#include <string>


#include "Book.h"
#include "User.h"
#include "handler.h"
#include "mySql.h"


using namespace std;


int main()
{
	printf("------------------------------------------------------------------------------------------\n");
	printf("------------------------------ 도서관리 프로그램 Made by BGC -----------------------------\n");
	printf("------------------------------------------------------------------------------------------\n");


	printf("\n");

	BookHandler manager;

	// MySQL 설정 /////////////////////////////////////////////////
	MYSQL *connection = NULL, conn;


	mysql_init(&conn);

	// mysql 연결
	connection = mysql_real_connect(&conn, HOST, USER, PASS, DB_NAME, 3306, (char *)NULL, 0);

	// 연결 실패 
	if (connection == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s\n", mysql_error(&conn));
		return 1;
	}
	mysql_query(&conn, "set names euckr"); // 한글깨짐 방지 

										   /////  BOOK ///////////////////////////////////////////////////
	MYSQL_RES *sql_result_book;
	MYSQL_ROW sql_row_book;
	int query_stat_book;
	vector<tuple<string, string, string>> Bookv; // 책 정보를 담아 둘 벡터
												 // name, kind , num 순



	query_stat_book = mysql_query(connection, "select * from book");
	if (query_stat_book != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}

	sql_result_book = mysql_store_result(connection);

	while ((sql_row_book = mysql_fetch_row(sql_result_book)) != NULL)
	{
		Bookv.push_back({ sql_row_book[0],sql_row_book[1],sql_row_book[2] });
	}

	for (unsigned int i = 0; i < Bookv.size(); i++)
	{
		manager.InsertBook(get<0>(Bookv[i]), get<1>(Bookv[i]), stoi(get<2>(Bookv[i])));
	}

	mysql_free_result(sql_result_book);

	////////////////////////////////////////////////////////////

	/////////////////// USER /////////////////////////////////////////////////////

	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;
	int query_stat;
	vector<tuple<string, string, string, string>> Userv; // 회원정보를 담아 둘 벡터
														 // id , pass , name , birth 순

	query_stat = mysql_query(connection, "select * from user");
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}

	sql_result = mysql_store_result(connection);



	//"ID 비밀번호 이름 생년월일" 저장
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
		manager.SetUserList(sql_row[0], sql_row[2], sql_row[3]);
		//UserList.push_back(User(sql_row[0], sql_row[2], sql_row[3]));
		Userv.push_back({ sql_row[0],sql_row[1],sql_row[2],sql_row[3] });
	}

	mysql_free_result(sql_result);
	////////////////////////////////////////////////////////////////////////////


	while (1)
	{

		//////////////////////////////////////////////////////////


		//////// 대여나 반납으로 인해 책의 개수가 변했는지 확인하고 Update 문 적용 ////////

		/*cout << "실행\n";
		for (unsigned int i = 0; i < Bookv.size(); i++)
		{
		int _bnum = manager.GetBookList()[i].GetBnum();

		if (_bnum != stoi(get<2>(Bookv[i])))
		{
		char query_book_rental[255];

		cout << "Bunm확인 : " << manager.GetBookList()[i].GetBnum() << '\n';
		::sprintf(query_book_rental, "update book set num = " "%d" " where name = " "'%s'", manager.GetBookList()[i].GetBnum(),get<0>(Bookv[i]).c_str());
		query_stat_book = mysql_query(connection, query_book_rental);
		if (query_stat_book != 0)
		{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
		}
		}

		}
		*/

		///////////////////////////////////////////////////////////////////////////////


		printf("------ MENU -------\n");
		printf("||               ||\n");
		printf("||  1. Sign in   ||\n");
		printf("||  2. Sign up   ||\n");
		printf("||  3. Stop      ||\n");
		printf("||               ||\n");
		printf("-------------------\n");

		printf("\n");


		int select;

		printf("회원이시면 로그인(1), 비회원이시면 회원가입(2)을 해주세요 --> ");
		scanf("%d", &select);

		getchar(); // 공백제거

		if (select == 1)
		{
			string login_id, login_pass;
			bool idcheck = false; // 아이디가 존재하는지 확인

			printf("아이디를 입력해주세요 : ");
			cin >> login_id;

			for (unsigned int i = 0; i < Userv.size(); i++)
			{
				if (get<0>(Userv[i]) == login_id)
				{
					idcheck = true;
					printf("비밀번호를 입력해주세요 : ");
					cin >> login_pass;

					while (get<1>(Userv[i]) != login_pass)
					{
						printf("올바르지 않은 비밀번호입니다.\n");
						printf("다시 입력해주세요 : ");
						cin >> login_pass;
					}

					if (login_id == "admin")
					{
						printf("관리자 로그인 되었습니다.\n");
						while (1) // 관리자 메뉴 
						{
							printf("-------- MENU ---------\n");
							printf("||                   ||\n");
							printf("||  1. Insert Book   ||\n");
							printf("||  2. Stop          ||\n");
							printf("||                   ||\n");
							printf("-----------------------\n");

							printf("\n");

							int sel_admin;
							printf("새로운 책을 입력하시려면 1번, 종료하시려면 2번을 입력해주세요  : ");
							cin >> sel_admin;

							if (sel_admin == 1)
							{


								char book_name[40], book_kind[20];
								char book_num[20];
								char query_book[255];

								getchar();
								printf("등록할 책 제목을 입력해주세요 : ");
								::fgets(book_name, 40, stdin);
								CHOP(book_name);


								printf("등록할 책 종류를 입력해주세요 : ");
								::fgets(book_kind, 20, stdin);
								CHOP(book_kind);

								printf("등록할 책 개수를 입력해주세요 : ");
								::fgets(book_num, 20, stdin);
								CHOP(book_num);

								::sprintf(query_book, "insert into book values " "('%s', '%s' , '%d')", book_name, book_kind, stoi(book_num));
								query_stat_book = mysql_query(connection, query_book);
								if (query_stat_book != 0)
								{
									fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
									return 1;
								}
								printf("책이 정상적으로 등록되었습니다.\n\n");
								manager.InsertBook(book_name, book_kind, stoi(book_num));
								//mysql_close(connection);


							}

							else if (sel_admin == 2)
								break;

							else
							{
								printf("잘못된 입력입니다. \n\n");
								printf("1 혹은 2만 입력가능합니다. \n\n");
								printf("\n");
							}
						}
					}
					else
					{
						cout << '\n';
						cout << "사용자 " << login_id << " 로그인 되었습니다.\n";
						cout << '\n';

						manager.GetBookList();
						// 여기서 기능 
						while (1)
						{
							printf("------ MENU --------\n");
							printf("||                ||\n");
							printf("||  1. 도서목록   ||\n");
							printf("||  2. 대여목록   ||\n");
							printf("||  3. 도서대여   ||\n");
							printf("||  4. 도서반납   ||\n");
							printf("||  5. 로그아웃   ||\n");
							printf("||                ||\n");
							printf("--------------------\n");

							printf("\n");

							printf("메뉴에서 기능을 선택해주세요 --> ");

							int select2;
							cin >> select2;

							if (select2 == 1)
							{
								manager.ShowAllBookInfo();
							}

							else if (select2 == 2)
							{
								for (unsigned int i = 0; i < manager.GetUserList().size(); i++)
								{
									if (manager.GetUserList()[i].GetId() == login_id)
									{
										cout << "---------------------------------------------\n";
										manager.GetUserList()[i].ShowRentalInfo();
										cout << "---------------------------------------------\n";
										break;
									}
								}

							}

							else if (select2 == 3)
							{
								manager.RentalBook(login_id);
								//////// 대여나 반납으로 인해 책의 개수가 변했는지 확인하고 Update 문 적용 ////////

								for (unsigned int i = 0; i < Bookv.size(); i++)
								{
									int _bnum = manager.GetBookList()[i].GetBnum();

									if (_bnum != stoi(get<2>(Bookv[i])))
									{
										char query_book_rental[255];



										::sprintf(query_book_rental, "update book set num = " "%d" " where name = " "'%s'", manager.GetBookList()[i].GetBnum(), get<0>(Bookv[i]).c_str());
										query_stat_book = mysql_query(connection, query_book_rental);
										if (query_stat_book != 0)
										{
											fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
											return 1;
										}
									}

								}


								///////////////////////////////////////////////////////////////////////////////

							}

							else if (select2 == 4)
							{
								//////// 대여나 반납으로 인해 책의 개수가 변했는지 확인하고 Update 문 적용 ////////

								for (unsigned int i = 0; i < Bookv.size(); i++)
								{
									int _bnum = manager.GetBookList()[i].GetBnum();

									if (_bnum != stoi(get<2>(Bookv[i])))
									{
										char query_book_rental[255];


										::sprintf(query_book_rental, "update book set num = " "%d" " where name = " "'%s'", manager.GetBookList()[i].GetBnum() + 1, get<0>(Bookv[i]).c_str());
										query_stat_book = mysql_query(connection, query_book_rental);
										if (query_stat_book != 0)
										{
											fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
											return 1;
										}
									}


								}

								manager.ReturnBook(login_id);


								///////////////////////////////////////////////////////////////////////////////

							}

							else if (select2 == 5)
							{
								printf("로그아웃 되었습니다\n");
								printf("\n");
								break;
							}

							else
							{
								printf("잘못된 입력입니다.\n");
								printf("1 ~ 5 사이의 값을 입력해주세요 . \n\n");
							}

						}
					}




				}
			}

			while (!idcheck)
			{
				printf("존재하지 않는 아이디입니다.\n\n");
				printf("다시 입력해주세요 : ");
				cin >> login_id;

				for (unsigned int i = 0; i < Userv.size(); i++)
				{
					if (get<0>(Userv[i]) == login_id)
					{
						idcheck = true;
						printf("비밀번호를 입력해주세요 : ");
						cin >> login_pass;

						while (get<1>(Userv[i]) != login_pass)
						{
							printf("올바르지 않은 비밀번호입니다.\n\n");
							printf("다시 입력해주세요 : ");
							cin >> login_pass;
						}
						printf("로그인 되었습니다.\n\n");
						//printf("메뉴에서 기능을 선택해주세요.\n");
						// 여기서 기능 


						// 여기서 기능 
						while (1)
						{
							printf("------ MENU --------\n");
							printf("||                ||\n");
							printf("||  1. 도서목록   ||\n");
							printf("||  2. 대여목록   ||\n");
							printf("||  3. 도서대여   ||\n");
							printf("||  4. 도서반납   ||\n");
							printf("||  5. 로그아웃   ||\n");
							printf("||                ||\n");
							printf("--------------------\n");

							printf("\n");

							printf("메뉴에서 기능을 선택해주세요 --> ");

							int select2;
							cin >> select2;

							if (select2 == 1)
							{
								manager.ShowAllBookInfo();
							}

							else if (select2 == 2)
							{
								for (unsigned int i = 0; i < manager.GetUserList().size(); i++)
								{
									if (manager.GetUserList()[i].GetId() == login_id)
									{
										cout << "---------------------------------------------\n";
										manager.GetUserList()[i].ShowRentalInfo();
										cout << "---------------------------------------------\n";
										break;
									}
								}

							}

							else if (select2 == 3)
							{
								manager.RentalBook(login_id);
								//////// 대여나 반납으로 인해 책의 개수가 변했는지 확인하고 Update 문 적용 ////////

								for (unsigned int i = 0; i < Bookv.size(); i++)
								{
									int _bnum = manager.GetBookList()[i].GetBnum();

									if (_bnum != stoi(get<2>(Bookv[i])))
									{
										char query_book_rental[255];

										
										::sprintf(query_book_rental, "update book set num = " "%d" " where name = " "'%s'", manager.GetBookList()[i].GetBnum(), get<0>(Bookv[i]).c_str());
										query_stat_book = mysql_query(connection, query_book_rental);
										if (query_stat_book != 0)
										{
											fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
											return 1;
										}
									}

								}


								///////////////////////////////////////////////////////////////////////////////
								break;
							}

							else if (select2 == 4)
							{

								//////// 대여나 반납으로 인해 책의 개수가 변했는지 확인하고 Update 문 적용 ////////

								for (unsigned int i = 0; i < Bookv.size(); i++)
								{
									int _bnum = manager.GetBookList()[i].GetBnum();
									cout << "확인 : " << _bnum << ',' << stoi(get<2>(Bookv[i])) << '\n';
									if (_bnum != stoi(get<2>(Bookv[i])))
									{
										char query_book_rental[255];

										
										::sprintf(query_book_rental, "update book set num = " "%d" " where name = " "'%s'", manager.GetBookList()[i].GetBnum() + 1, get<0>(Bookv[i]).c_str());
										query_stat_book = mysql_query(connection, query_book_rental);
										if (query_stat_book != 0)
										{
											fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
											return 1;
										}
									}

								}
								manager.ReturnBook(login_id);

								///////////////////////////////////////////////////////////////////////////////
								break;
							}

							else if (select2 == 5)
							{
								printf("로그아웃 되었습니다\n");
								printf("\n");
								break;
							}

							else
							{
								printf("잘못된 입력입니다.\n");
								printf("1 ~ 5 사이의 값을 입력해주세요 . \n\n");
							}

						}
					}
				}
			}


		}
		else if (select == 2)
		{


			char id[20], pass[20], name[20], birth[20]; // 회원가입할 때 입력할 항목
			char query[255];


			printf("이름을 입력해주세요 : ");
			::fgets(name, 20, stdin);
			CHOP(name);


			printf("주민등록번호 앞자리를 입력해주세요 : ");
			::fgets(birth, 20, stdin);
			CHOP(birth);

			printf("ID를 입력해주세요 : ");
			::fgets(id, 20, stdin);
			CHOP(id);
			for (unsigned int i = 0; i < Userv.size(); i++)
			{
				while (get<0>(Userv[i]) == id)
				{
					printf("이미 존재하는 ID입니다\n\n");
					printf("다른 ID를 입력해주세요 : ");
					::fgets(id, 20, stdin);
					CHOP(id);
				}
			}


			printf("비밀번호를 입력해주세요 : ");
			::fgets(pass, 20, stdin);
			CHOP(pass);

			::sprintf(query, "insert into user values " "('%s', '%s' , '%s', '%s')", id, pass, name, birth);
			query_stat = mysql_query(connection, query);
			if (query_stat != 0)
			{
				fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
				return 1;
			}
			Userv.push_back({ id,pass,name,birth });
			manager.SetUserList(id, pass, birth);
			cout << "회원가입이 완료되었습니다\n\n";

			//mysql_close(connection);
		}
		else if (select == 3)
		{
			printf("\n");
			printf("\n");
			printf("종료합니다.\n");
			printf("\n");
			printf("\n");
			break;
		}

		else
		{
			printf("잘못된 값을 입력하셨습니다.\n\n");
			printf("1 ~ 3 사이의 값을 입력해주세요 . \n\n");
		}
	}

	mysql_close(connection); // 프로그램 종료시 mysql연결도 해제
	return 0;
}