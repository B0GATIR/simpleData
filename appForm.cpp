#include "newRowConstructorForm.h"
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
/*������� ��������� �������� �������� �������� � ������� �� � ������*/
list<String^> getDataValues(System::Windows::Forms::DataGridView^ dataGridView1)
{
	list<String^> values;
	/*���� ��������� ������ data ���������� ��������*/
	int i = 0;
	while (i < dataGridView1->ColumnCount)
	{
		/*�������� �� ���������� ���� ������*/
		if (dataGridView1->Rows[dataGridView1->SelectedCells[0]->RowIndex]->Cells[i]->Value == nullptr)
		{
			MessageBox::Show("Not all cells are filled!", "Error!");
			return values;
		}
		else
		{
			values.push_back(dataGridView1->Rows[dataGridView1->SelectedCells[0]->RowIndex]->Cells[i]->Value->ToString());
		}
		i++;
	}
	return values;
}

System::Void simpleData::appForm::appForm_Load(System::Object^ sender, System::EventArgs^ e)
{
	/*���������� � ������������ ������ ��������������� ������������*/
	User user;
	/*��������, ���� �� ��������� �����������*/
	if (user.login == nullptr)
	{
		this->Close();
	}
	/*������ ������ ������ ���� ������*/
	Database^ workData = gcnew Database("workData");
	/*������� ������ ������ ������� ���� ������*/
	list<Table^> tablseList = workData->coutTablesFromRequest();
	/*���� ��������� ���������� ��������������� ������������ ������� ���� ������*/
	for each (auto % i in tablseList)
	{
		if (Convert::ToInt32(user.accessCode) >= Convert::ToInt32(i->coutAccessCode()))
		{
			cbTableName->Items->Add(i->coutTableName());
		}
	};
	/*
	��������� ������ ������� ������������� �������� ������� ��������������� 
	������������ � ������� � ����� ������ �������� ������ � ��������� action �
	������� ������������ ������ user � accessCode
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
	if (Convert::ToInt32(user.accessCode) <= 21)
	{
		dataGridView1->ReadOnly = true;
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
		if (Convert::ToString(cbTableName->Text) == Convert::ToString(i->coutTableName()))
		{
			/*�������� ����������� ������� ������� ������������*/
			if (Convert::ToInt32(user.accessCode) >= Convert::ToInt32(i->coutAccessCode()))
			{
				/*����������, � ����� �������� �������� ������������*/
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
	if (dataGridView1->ColumnCount != 0)
	{
		if (Convert::ToInt32(user.accessCode) <= 31
			&& Convert::ToInt32(user.accessCode) > 11)
		{
			newRowConstructorForm^ constructor = gcnew newRowConstructorForm;
			constructor->Show();
		}
		else
		{
			/*������ ������ ������� �� ������ dataGridView1*/
			int index = Convert::ToInt32(dataGridView1->Rows[dataGridView1->SelectedCells[0]->RowIndex]->Cells[0]->Value);
			/*������ �������� ��������*/
			list<String^> data = getDataValues(dataGridView1);
			/*�������� �� ������ ���� ���� ��������� �� ��� ������*/
			if (data.size() == 0)
			{
				return System::Void();
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
			/*��������� �� �������� ���������� ����� ������*/
			MessageBox::Show("New row was sucsessfully created!", "Message");
			return System::Void();
		}
	}
	else
	{
		MessageBox::Show("Choose the table!", "Message");
		return System::Void();
	}
}

System::Void simpleData::appForm::bRowUpdate_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*���������� ���������� ������ ����������������� ������������*/
	User user;
	if (dataGridView1->ColumnCount != 0)
	{
		/*������ ����������� ������� �� ������ dataGridView1*/
		int index = Convert::ToInt32(dataGridView1->Rows[dataGridView1->SelectedCells[0]->RowIndex]->Cells[0]->Value);
		/*������ �������� ��������*/
		list<String^> data = getDataValues(dataGridView1);
		/*�������� �� ������ ���� ���� ��������� �� ��� ������*/
		if (data.size() == 0)
		{
			return System::Void();
		}
		/*������ ������ ������ ���� ������*/
		Database^ workData = gcnew Database("workData");
		/*������������ ������� �� ��������� ������ � �������*/
		String^ query = "UPDATE [" + user.editTable + "] SET ";
		/*���������� �������� ������� �������*/
		int j = 0;
		for each (auto % i in data)
		{
			query += j == 0 ? "" : dataGridView1->Columns[j]->HeaderText + "= '" + i + "', ";
			j++;
		};
		query = query->Remove(query->Length - 2);
		query += " WHERE Counter = " + index;
		/*�������� ������� �� �� �������� ������*/
		workData->doRequest(query, false);
		/*��������� �� �������� ��������� ������*/
		MessageBox::Show("Selected row was sucsessfully updated!", "Message");
		return System::Void();
	}
	else
	{
		MessageBox::Show("Choose the table!", "Message");
		return System::Void();
	}
}

System::Void simpleData::appForm::bDeleteRow_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*���������� ���������� ������ ����������������� ������������*/
	User user;
	if (dataGridView1->ColumnCount != 0)
	{
		/*������ ���������� ������� �� ������ dataGridView1*/
		int index = Convert::ToInt32(dataGridView1->Rows[dataGridView1->SelectedCells[0]->RowIndex]->Cells[0]->Value);
		/*������ ������ ������ ���� ������*/
		Database^ workData = gcnew Database("workData");
		/*������������ ������� �� �������� ������ � �������*/
		String^ query = "DELETE FROM [" + user.editTable + "] WHERE Counter = " + index;
		/*�������� ������� �� �� �������� ������*/
		workData->doRequest(query, false);
		/*��������� �� �������� �������� ������*/
		MessageBox::Show("Selected row was sucsessfully deleted!", "Message");
		return System::Void();
	}
	else
	{
		MessageBox::Show("Choose the table!", "Message");
		return System::Void();
	}
}
