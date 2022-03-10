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
	/*Создание запроса к таблице аунтетификации БД аутентификации*/
	String^ query = autData->coutTablesFromRequest().back()->getQueryForTable();
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

				//MessageBox::Show(employee->coutLogin() + " " + employee->coutAccessCode(), employee->coutTimeIn());
				break;
			}
			else
			{
				autTabel->Close();
				MessageBox::Show("Wrong password.", "Error!");
				tBLogin->Text = "";
				tBPassword->Text = "";
				return System::Void();
			}
		}
	}
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