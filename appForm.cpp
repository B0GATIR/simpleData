#include "appForm.h"
#include "autForm.h"
#include "Database.h"
#include <cliext/list>

using namespace System;
using namespace System::Windows::Forms;

int mainApp(array<String^>^ arg)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	return 0;
}


System::Void simpleData::appForm::appForm_Load(System::Object^ sender, System::EventArgs^ e)
{
	/*������ ������ ������ ���� ������*/
	Database^ workData = gcnew Database("workData");
	/*������� ������ ������ ������� ���� ������*/
	list<Table^> tablseList = workData->coutTablesFromRequest();
	/*���������� � ������������ ������ ��������������� ������������*/
	User user;
	/*���� ��������� ���������� ��������������� ������������ ������� ���� ������*/
	for each (auto % i in tablseList)
	{
		if (Convert::ToInt32(user.accessCode) >= Convert::ToInt32(i->coutAccessCode()))
		{
			lblEnableTables->Text += i->coutTableName() + "\n";
		}
	};
	/*
	��������� ��� ������� ������������� �������� ������� ��������������� 
	������������ � ��� ��� ���� ������ �������� ������ � ��������� action �
	������� ������������ ������ user
	*/
	if (user.actions->edit == false)
	{
		bNewRow->Enabled = false;
	}
	if (user.actions->write == false)
	{
		bRowUpdate->Enabled = false;
	}
	if (user.actions->del == false)
	{
		bDeleteRow->Enabled = false;
	}

	return System::Void();
}

System::Void simpleData::appForm::bDownload_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*������� ������ dataGridView1*/
	dataGridView1->Columns->Clear();
	/*������ ������ ������ ���� ������*/
	Database^ workData = gcnew Database("workData");
	list<Table^> tablseList = workData->coutTablesFromRequest();
	/*���� ��������� ����� ������� ��������� � ���� ����� tbTableName*/
	for each (auto % i in tablseList)
	{
		if (Convert::ToString(tbTableName->Text) == Convert::ToString(i->coutTableName()))
		{
			/*� ������ ���������� ������ ������� �������� ������� � ������� �� �������*/
			String^ query = i->getQueryForTable();
			/*������ �������*/
			OleDbDataReader^ tabel = workData->doRequest(query, true);
			/*������ ���� ��������� �� ������ dataGridView1 �������*/
			int i = 0;
			while (i < tabel->FieldCount)
			{
				dataGridView1->Columns->Add("", Convert::ToString(tabel->GetName(i)));
				i++;
			}
			/*������ ���� ��������� �� ������ dataGridView1 ������*/
			int j = 0;
			while (tabel->Read())
			{
				/*� ������ ����� ����� ��������� ����� ������ � ������ ������ ����������� �������*/
				dataGridView1->Rows->Add();
				i = 0;
				while (i < tabel->FieldCount)
				{
					dataGridView1->Rows[j]->Cells[i]->Value = tabel[i];
					i++;
				}
				j++;
			}
		}
	};

	return System::Void();
}

System::Void simpleData::appForm::bNewRow_Click(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}

System::Void simpleData::appForm::bRowUpdate_Click(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}

System::Void simpleData::appForm::bDeleteRow_Click(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}
