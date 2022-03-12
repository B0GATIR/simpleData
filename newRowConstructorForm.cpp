#include "newRowConstructorForm.h"
#include "appForm.h"
#include "Database.h"
#include <cliext/list>

using namespace System;
using namespace System::Windows::Forms;

int mainNewRowConstructor(array<String^>^ arg)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	return 0;
}

System::Void simpleData::newRowConstructorForm::newRowConstructorForm_Load(System::Object^ sender, System::EventArgs^ e)
{
	/*������ ������ ������ ���� ������*/
	Database^ workData = gcnew Database("workData");
	/*������� ������ ������ ������� ���� ������*/
	list<Table^> tablseList = workData->coutTablesFromRequest();
	/*
	������ ���� ���� ����������� ���� � �������� ���������� � ����������� 
	��� ���������� ��������������� ComboBox
	*/
	for each (auto % i in tablseList)
	{
		if (i->coutTableName() == "����������")
		{
			/*� ������ ���������� ������ ������� �������� ������� � ������� �� �������*/
			String^ query = i->getQueryForTable();
			/*������ �������*/
			OleDbDataReader^ tabel = workData->doRequest(query, true);
			/*������ ���� ��������� �� ������ dataGridView1 �������*/
			while (tabel->Read())
			{
				cbNames->Items->Add(tabel[1]->ToString());
			}
		}
		if (i->coutTableName() == "�����������")
		{
			/*� ������ ���������� ������ ������� �������� ������� � ������� �� �������*/
			String^ query = i->getQueryForTable();
			/*������ �������*/
			OleDbDataReader^ tabel = workData->doRequest(query, true);
			/*������ ���� ��������� �� ������ dataGridView1 �������*/
			while (tabel->Read())
			{
				cbOrganizations->Items->Add(tabel[1]->ToString());
			}
		}
	};
	return System::Void();
}
/*
��������� ��� ������� ����������� ��������� � ����� ���-�� ����, ��������, ��������� ������� � �������� �������� 
���������� �������� ����������� ������
*/
System::Void simpleData::newRowConstructorForm::onChangeDays(System::Object^ sender, System::EventArgs^ e)
{
	int ticketsCost = tbTicketsCost->Text == "" ? 0 : Convert::ToInt32(tbTicketsCost->Text);
	int howManyDays = tbHowManyDays->Text == "" ? 0 : Convert::ToInt32(tbHowManyDays->Text);
	int moneyInDay = tbMoneyInDay->Text == "" ? 0 : Convert::ToInt32(tbMoneyInDay->Text);
	int cost = ticketsCost * 2 + howManyDays * moneyInDay;
	lRes->Text = Convert::ToString(Convert::ToInt32(cost));
	return System::Void();
}

System::Void simpleData::newRowConstructorForm::onChangeMoneyInDays(System::Object^ sender, System::EventArgs^ e)
{
	int ticketsCost = tbTicketsCost->Text == "" ? 0 : Convert::ToInt32(tbTicketsCost->Text);
	int howManyDays = tbHowManyDays->Text == "" ? 0 : Convert::ToInt32(tbHowManyDays->Text);
	int moneyInDay = tbMoneyInDay->Text == "" ? 0 : Convert::ToInt32(tbMoneyInDay->Text);
	int cost = ticketsCost * 2 + howManyDays * moneyInDay;
	lRes->Text = Convert::ToString(Convert::ToInt32(cost));
	return System::Void();
}

System::Void simpleData::newRowConstructorForm::onChangeTicketsCost(System::Object^ sender, System::EventArgs^ e)
{
	int ticketsCost = tbTicketsCost->Text == "" ? 0 : Convert::ToInt32(tbTicketsCost->Text);
	int howManyDays = tbHowManyDays->Text == "" ? 0 : Convert::ToInt32(tbHowManyDays->Text);
	int moneyInDay = tbMoneyInDay->Text == "" ? 0 : Convert::ToInt32(tbMoneyInDay->Text);
	int cost = ticketsCost * 2 + howManyDays * moneyInDay;
	lRes->Text = Convert::ToString(Convert::ToInt32(cost));
	return System::Void();
}

System::Void simpleData::newRowConstructorForm::bCancel_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*�������� ������������*/
	this->Close();
	return System::Void();
}

System::Void simpleData::newRowConstructorForm::bOk_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*���������� ���������� ������ ����������������� ������������*/
	User user;
	/*�������� �� ���������� ���� �������*/
	if (tbDays->Text == "" || cbNames->Text == "" || cbOrganizations->Text == "" || tbHowManyDays->Text == "" ||
		tbMoneyInDay->Text == "" || tbTicketsCost->Text == "" || lRes->Text == "")
	{
		MessageBox::Show("Not all cells are filled!", "Error!");
		return System::Void();
	} 
	else
	{
		/*������ ������ ������ ���� ������*/
		Database^ workData = gcnew Database("workData");
		/*������������ ������� �� ���������� ����� ������ � �������*/
		String^ query = "INSERT INTO [" + user.editTable + "] (����������, ���, �����������, ��������������, ��������, ����������, ������������������) VALUES('"
			+ tbDays->Text + "', '" + cbNames->Text + "', '" + cbOrganizations->Text + "', '"
			+ tbHowManyDays->Text + "', '" + tbMoneyInDay->Text + "', '" + tbTicketsCost->Text + "', '"
			+ lRes->Text + "')";
		MessageBox::Show(query);
		/*�������� ������� �� �� ���������� ����� ������*/
		workData->doRequest(query, false);
		/*��������� �� �������� ���������� ����� ������*/
		MessageBox::Show("New row was sucsessfully created!", "Message");
		this->Close();
		return System::Void();
	}
}

