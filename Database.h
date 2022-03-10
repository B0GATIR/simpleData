#pragma once

#include<cliext/list> //Библиотека для работы с list
#include<ctime>
#include<time.h>
/*Стандратное пространство имён за исключением cliext*/
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Data::OleDb;
using namespace cliext;
/*Статический класс авторизованного пользователя*/
static ref class User
{
public:
	static String^ login;
	static String^ accessCode;
};
/*Класс сотрудника, работающего с приложением*/
ref class Employee
{
private:
	String^ login; //Логин сотрулника
	String^ timeIn; //Время авторизации
	String^ dataIn; //Дата авторизации
	String^ timeOut; //Время прекращения работы
	String^ accessCode; //Код доступа
public:
	/*Контсруктор*/
	Employee(String^ name, String^ code)
	{
		login = name;
		accessCode = code;
		/*Вычисялет время авторизации сотрудника*/
		struct tm ltm;
		time_t now = time(0);
		localtime_s(&ltm, &now);
		String^ min = ltm.tm_min < 10 ? "0" + ltm.tm_min : Convert::ToString(ltm.tm_min);
		String^ hour = ltm.tm_hour < 10 ? "0" + ltm.tm_hour : Convert::ToString(ltm.tm_hour);
		timeIn = hour + ":" + min;
		dataIn = Convert::ToString(ltm.tm_mday) + "." + Convert::ToString(ltm.tm_mon + 1) + "." + Convert::ToString(ltm.tm_year + 1900);
	}
	Employee(String^ name, String^ code, String^ tIn, String^ dIn)
	{
		login = name;
		accessCode = code;
		timeIn = tIn;
		dataIn = dIn;
	}
	/*Вычисялет время прекращения работы*/
	void getTimeOut()
	{
		struct tm ltm;
		time_t now = time(0);
		localtime_s(&ltm, &now);
		String^ min = ltm.tm_min < 10 ? "0" + ltm.tm_min : Convert::ToString(ltm.tm_min);
		String^ hour = ltm.tm_hour < 10 ? "0" + ltm.tm_hour : Convert::ToString(ltm.tm_hour);
		timeOut = hour + ":" + min;
	}
	/*
	Эти четыре функции возвращают приватные поля экземпляра
	класса сотрудника
	*/
	String^ coutAccessCode() { return accessCode; };
	String^ coutLogin() { return login; }
	String^ coutTimeIn() { return timeIn; }
	String^ coutDataIn() { return dataIn; }
	String^ coutTimeOut() { return timeOut; }
};
/*Класс таблиц в БД*/
ref class Table
{
private:
	String^ tableName; //Имя таблицы
	String^ accessCode; //Код доступа

public:
	/*Конструктор*/
	Table(String^ num, String^ text)
	{
		accessCode = num;
		tableName = text;
	}
	/*Функция возвращает приватное поле securiteCode*/
	String^ coutAccessCode() { return accessCode; }
	String^ coutTableName() { return tableName; }
	/*Функция формирует SQL запрос на таблицу для БД*/
	String^ getQueryForTable() 
	{
		return "SELECT * FROM " + "[" + tableName + "]";
	}
};
/*Класс БД, является основным в приложении*/
ref class Database
{
private:

	list<Table^> tables; //таблицы БД
	String^ href; //адресс БД
	/*Приватная процедура заполняет tables экземплярами класса Table*/
	void getTablesFromRequest(OleDbDataReader^ dbReaderTables)
	{
		while (dbReaderTables->Read())
		{
			Table^ tableProt = gcnew Table(dbReaderTables[1]->ToString(), dbReaderTables[0]->ToString());
			tables.push_back(tableProt);
		}
	}

public:
	/*
	Функция принимает текст запроса, с которым обращается к БД
	через откртый канал, который закрывается в ручную. Вторым аргументом 
	принимается булево выражение, указывающее о типе запроса: 
	входящем или исходящем.
	*/
	OleDbDataReader^ doRequest(String^ query, bool get)
	{
		OleDbConnection^ dbConect = gcnew OleDbConnection(href);

		dbConect->Open(); //Открываем канал
		OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConect);
		/*Провека на получение ответа от БД*/
		if (get)
		{
			OleDbDataReader^ dbReader = dbCommand->ExecuteReader();
			if (dbReader->HasRows == false)
			{
				MessageBox::Show("Error!");
			}
			return dbReader;
		}
		else
		{
			if (dbCommand->ExecuteNonQuery() != 1)
			{
				MessageBox::Show("Error!");
				dbConect->Close();
			}
		}
	};
	/*"Устарело!" Функция выводит массив экземпляров класса Table*/
	list<Table^> coutTablesFromRequest()
	{
		return tables;
	}

	/*Консутрктор, принимает в качестве аргумента необходимую БД*/
	Database(String^ type)
	{
		/*
		Имеется две БД:
			autData - хранит таблицу информации о сотрудниках,
			таблицу кодов доступа с описанными возможностями,
			таблицу таблиц данной БД с кодами доступа.
			workData - рабочая БД содержание которой описано в ТЗ
			(ещё не построена)
		*/
		if (type == "autData")
		{
			href = "provider=Microsoft.ACE.OLEDB.12.0; Data Source=autData.mdb"; //БД доступа
		}
		else if (type == "workData")
		{
			href = "provider=Microsoft.ACE.OLEDB.12.0; Data Source=workData.mdb"; //БД рабочая
		}
		else
		{
			MessageBox::Show("Error!");
		}
		/*
		Заполнение массива таблиц согласно ответу, полученному от БД
		по запросу на таблицу TableNames. Также нагялдный пример
		применения функции отправки запроса.
		*/
		OleDbDataReader^ dbTables = doRequest("SELECT * FROM [TableNames]", true);
		getTablesFromRequest(dbTables);
		dbTables->Close();
	};
};