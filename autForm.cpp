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
	/*�������� ������ �� ��������������*/
	Database^ autData = gcnew Database("autData");
	list<Table^> tablseList = autData->coutTablesFromRequest();
	/*�������� ������� � ������� �������������� �� ��������������*/
	String^ query = tablseList.back()->getQueryForTable();
	/*������ ������� �������������� ��� ������� �������*/
	OleDbDataReader^ autTabel = autData->doRequest(query, true);
	bool rLogin = false;
	while (autTabel->Read())
	{
		if (tBLogin->Text == autTabel[0]->ToString())
		{
			rLogin = true;
			if (tBPassword->Text == autTabel[1]->ToString())
			{
				/*�������� ��������� ������ ����������*/
				Employee^ employee = gcnew Employee(tBLogin->Text, autTabel[2]->ToString());
				/*�������� ��������� ������ ���� ������*/
				Database^ workData = gcnew Database("workData");
				/*�������� ������� � ������� ����� ����� � ������� ��*/
				workData->doRequest("INSERT INTO [Workers table] VALUES ('"
					+ employee->coutLogin() + "', '" + employee->coutAccessCode() + "', '"
					+ employee->coutTimeIn() + "', '" + employee->coutTimeOut() + "', '" 
					+ employee->coutDataIn() + "')", false);
				/*��������� ����������� ����� ��������������� ������������*/
				User user;
				user.login = employee->coutLogin();
				user.accessCode = employee->coutAccessCode();
				/*�������� ������� � ������� ��������� �������� �� ��������������*/
				query = tablseList.front()->getQueryForTable();
				/*������ ������� ��������� �������� ��� ������� �������*/
				autTabel = autData->doRequest(query, true);

				bool isRollCurrect = false;
				while (autTabel->Read())
				{
					/*
					���������� ���� �������� ������� ��������� �������� � 
					���������� ��������� ��������� �������� ��������������� 
					������������ �������� ��
					*/
					if (Convert::ToString(autTabel[0]) == Convert::ToString(user.accessCode))
					{
						isRollCurrect = true;
						user.actions->write = Convert::ToBoolean(autTabel[2]);
						user.actions->edit = Convert::ToBoolean(autTabel[3]);
						user.actions->del = Convert::ToBoolean(autTabel[4]);
					}
				}
				/*�������� �� ������ ���������� �������������� ����*/
				if (isRollCurrect == false)
				{
					MessageBox::Show("Error!", "This roll doesn`t exist!");
				}
				break;
			}
			else
			{
				/*������ � ������ ��������� ������ ������������*/
				autTabel->Close();
				MessageBox::Show("Wrong password.", "Error!");
				tBPassword->Text = "";
				return System::Void();
			}
		}
	}
	/*������ � ������ ��������� ����� ������������*/
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