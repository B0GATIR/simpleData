#include "autForm.h"
#include "appForm.h"
#include "Database.h"
#include <cliext/list>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Data::OleDb;

[STAThread]
int mainAut(array<String^>^ arg)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	simpleData::autForm aut;
	simpleData::appForm api;

	Application::Run(% aut);
	Application::Run(% api);

	int a;
	return 0;
}


System::Void simpleData::autForm::autBtn_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*Создание объект БД аутентификации*/
	Database^ autData = gcnew Database("autData");
	list<Table^> tablseList = autData->coutTablesFromRequest();
	/*Создание запроса к таблице аунтетификации БД аутентификации*/
	String^ query = tablseList.back()->getQueryForTable();
	/*Данные таблицы аунтетификации для столбца логинов*/
	OleDbDataReader^ autTabel = autData->doRequest(query, true);
	bool rLogin = false;
	while (autTabel->Read())
	{
		if (tBLogin->Text == autTabel[0]->ToString())
		{
			rLogin = true;
			if (tBPassword->Text == autTabel[1]->ToString())
			{
				/*Создание экземпляр класса Сотрудника*/
				Employee^ employee = gcnew Employee(tBLogin->Text, autTabel[2]->ToString());
				/*Создание экземпляр класса Базы данных*/
				Database^ workData = gcnew Database("workData");
				/*Создание запроса к таблице учета входа в рабочей БД*/
				workData->doRequest("INSERT INTO [Workers table] VALUES ('"
					+ employee->coutLogin() + "', '" + employee->coutAccessCode() + "', '"
					+ employee->coutTimeIn() + "', '" + employee->coutTimeOut() + "', '" 
					+ employee->coutDataIn() + "')", false);
				/*Заполняем статический класс авторизованного пользователя*/
				User user;
				user.login = employee->coutLogin();
				user.accessCode = employee->coutAccessCode();
				/*Создание запроса к таблице возможных действий БД аутентификации*/
				query = tablseList.front()->getQueryForTable();
				/*Данные таблицы возможных действий для столбца логинов*/
				autTabel = autData->doRequest(query, true);

				bool isRollCurrect = false;
				while (autTabel->Read())
				{
					/*
					Нахождение роли согласно таблице возможных действий и 
					заполнение структуры возможных действий авторизованного 
					пользователя согласно ей
					*/
					if (Convert::ToString(autTabel[0]) == Convert::ToString(user.accessCode))
					{
						isRollCurrect = true;
						user.actions->write = Convert::ToBoolean(autTabel[2]);
						user.actions->edit = Convert::ToBoolean(autTabel[3]);
						user.actions->del = Convert::ToBoolean(autTabel[4]);
					}
				}
				/*Проверка на случай назначения несуществующей роли*/
				if (isRollCurrect == false)
				{
					MessageBox::Show("Error!", "This roll doesn`t exist!");
				}
				break;
			}
			else
			{
				/*Ошибка в случае неверного пароля пользователя*/
				autTabel->Close();
				MessageBox::Show("Wrong password.", "Error!");
				tBPassword->Text = "";
				return System::Void();
			}
		}
	}
	/*Ошибка в случае неверного имени пользователя*/
	if (rLogin == false)
	{
		autTabel->Close();
		MessageBox::Show("Wrong login.", "Error!");
		tBLogin->Text = "";
		tBPassword->Text = "";
		return System::Void();
	}
	autTabel->Close();

	this->Close();
	return System::Void();
}