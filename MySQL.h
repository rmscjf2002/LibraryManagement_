#pragma once

#ifndef __MYSQL_H__
#define __MYSQL_H__

// mysql 관련 헤더파일 

#include <my_global.h>
#include <mysql.h>
#pragma comment(lib, "libmysql.lib")
////////////////////////////

// mysql 관련 define //

#define HOST "localhost"
#define USER "root"
#define PASS "134655"
#define DB_NAME "library"
#define CHOP(x) x[strlen(x) -1 ] = '\0' 

///////////////////////

#endif
#pragma once
