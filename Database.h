#pragma once

#include<cliext/list> //���������� ��� ������ � list
#include<ctime>
#include<time.h>
/*����������� ������������ ��� �� ����������� cliext*/
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Data::OleDb;
using namespace cliext;
/*����������� ����� ��������������� ������������*/
static ref class User
{
public:
	static String^ login;
	static String^ accessCode;
};
/*����� ����������, ����������� � �����������*/
ref class Employee
{
private:
	String^ login; //����� ����������
	String^ timeIn; //����� �����������
	String^ dataIn; //���� �����������
	String^ timeOut; //����� ����������� ������
	String^ accessCode; //��� �������
public:
	/*�����������*/
	Employee(String^ name, String^ code)
	{
		login = name;
		accessCode = code;
		/*��������� ����� ����������� ����������*/
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
	/*��������� ����� ����������� ������*/
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
	��� ������ ������� ���������� ��������� ���� ����������
	������ ����������
	*/
	String^ coutAccessCode() { return accessCode; };
	String^ coutLogin() { return login; }
	String^ coutTimeIn() { return timeIn; }
	String^ coutDataIn() { return dataIn; }
	String^ coutTimeOut() { return timeOut; }
};
/*����� ������ � ��*/
ref class Table
{
private:
	String^ tableName; //��� �������
	String^ accessCode; //��� �������

public:
	/*�����������*/
	Table(String^ num, String^ text)
	{
		accessCode = num;
		tableName = text;
	}
	/*������� ���������� ��������� ���� securiteCode*/
	String^ coutAccessCode() { return accessCode; }
	String^ coutTableName() { return tableName; }
	/*������� ��������� SQL ������ �� ������� ��� ��*/
	String^ getQueryForTable() 
	{
		return "SELECT * FROM " + "[" + tableName + "]";
	}
};
/*����� ��, �������� �������� � ����������*/
ref class Database
{
private:

	list<Table^> tables; //������� ��
	String^ href; //������ ��
	/*��������� ��������� ��������� tables ������������ ������ Table*/
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
	������� ��������� ����� �������, � ������� ���������� � ��
	����� ������� �����, ������� ����������� � ������. ������ ���������� 
	����������� ������ ���������, ����������� � ���� �������: 
	�������� ��� ���������.
	*/
	OleDbDataReader^ doRequest(String^ query, bool get)
	{
		OleDbConnection^ dbConect = gcnew OleDbConnection(href);

		dbConect->Open(); //��������� �����
		OleDbCommand^ dbCommand = gcnew OleDbCommand(query, dbConect);
		/*������� �� ��������� ������ �� ��*/
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
	/*"��������!" ������� ������� ������ ����������� ������ Table*/
	list<Table^> coutTablesFromRequest()
	{
		return tables;
	}

	/*�����������, ��������� � �������� ��������� ����������� ��*/
	Database(String^ type)
	{
		/*
		������� ��� ��:
			autData - ������ ������� ���������� � �����������,
			������� ����� ������� � ���������� �������������,
			������� ������ ������ �� � ������ �������.
			workData - ������� �� ���������� ������� ������� � ��
			(��� �� ���������)
		*/
		if (type == "autData")
		{
			href = "provider=Microsoft.ACE.OLEDB.12.0; Data Source=autData.mdb"; //�� �������
		}
		else if (type == "workData")
		{
			href = "provider=Microsoft.ACE.OLEDB.12.0; Data Source=workData.mdb"; //�� �������
		}
		else
		{
			MessageBox::Show("Error!");
		}
		/*
		���������� ������� ������ �������� ������, ����������� �� ��
		�� ������� �� ������� TableNames. ����� ��������� ������
		���������� ������� �������� �������.
		*/
		OleDbDataReader^ dbTables = doRequest("SELECT * FROM [TableNames]", true);
		getTablesFromRequest(dbTables);
		dbTables->Close();
	};
};