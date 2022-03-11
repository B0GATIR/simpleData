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
	/*���������� ���������� ������ ����������������� ������������*/
	User user;
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
			/*�������� ����������� �������� ������� ������������*/
			if (Convert::ToInt32(user.accessCode) >= Convert::ToInt32(i->coutAccessCode()))
			{
				/*����������, � ����� ������� ��������� ������������*/
				user.editTable = i->coutTableName();
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
				tabel->Close();
				return System::Void();
			}
			else 
			{
				MessageBox::Show("Permition denied!", "Warning!");
				return System::Void();
			}
		}
	};
}

System::Void simpleData::appForm::bNewRow_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*���������� ���������� ������ ����������������� ������������*/
	User user;
	/*������ ������ ������� �� ������ dataGridView1*/
	int index = dataGridView1->CurrentRow->Index;
	/*������ �������� ��������*/
	list<String^> data;
	/*���� ��������� ������ data ���������� ��������*/
	int i = 0;
	while (i < dataGridView1->ColumnCount)
	{
		/*�������� �� ���������� ���� ������*/
		if (dataGridView1->Rows[index]->Cells[i]->Value == nullptr)
		{
			MessageBox::Show("Not all cells are filled!", "Error!");
			return System::Void();
		}
		else 
		{
			data.push_back(dataGridView1->Rows[index]->Cells[i]->Value->ToString());
		}
		i++;
	}
	/*������ ������ ������ ���� ������*/
	Database^ workData = gcnew Database("workData");
	/*������������ ������� �� ���������� ����� ������ � �������*/
	String^ query = "INSERT INTO [" + user.editTable + "] VALUES(";
	/*���������� �������� ������� �������*/
	for each (auto % i in data)
	{
		query += "'" + i + "',";
	};
	query = query->Remove(query->Length - 1);
	query += ")";
	/*�������� ������� �� �� ���������� ����� ������*/
	workData->doRequest(query, false);
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
