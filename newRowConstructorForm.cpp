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
	/*Создал объект класса базы данных*/
	Database^ workData = gcnew Database("workData");
	/*Получил список таблиц рабочей базы данных*/
	list<Table^> tablseList = workData->coutTablesFromRequest();
	/*
	Данный цикл ищет необходимые поля в таблицах Сотрудники и Организации 
	для заполнения соответствующих ComboBox
	*/
	for each (auto % i in tablseList)
	{
		if (i->coutTableName() == "Сотрудники")
		{
			/*В случае нахождения нужной таблицы создаётся запроса к таблице БД рабочей*/
			String^ query = i->getQueryForTable();
			/*Данные таблицы*/
			OleDbDataReader^ tabel = workData->doRequest(query, true);
			/*Данный цикл размещает на холсте dataGridView1 столбцы*/
			while (tabel->Read())
			{
				cbNames->Items->Add(tabel[1]->ToString());
			}
		}
		if (i->coutTableName() == "Организации")
		{
			/*В случае нахождения нужной таблицы создаётся запроса к таблице БД рабочей*/
			String^ query = i->getQueryForTable();
			/*Данные таблицы*/
			OleDbDataReader^ tabel = workData->doRequest(query, true);
			/*Данный цикл размещает на холсте dataGridView1 столбцы*/
			while (tabel->Read())
			{
				cbOrganizations->Items->Add(tabel[1]->ToString());
			}
		}
	};
	return System::Void();
}
/*
Следующие три события отслеживают изменения в полях Кол-во дней, Суточные, Стоимость билетов и изменяют итоговые 
вычисления согласно обновленным данным
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
	/*Закрытие конструктора*/
	this->Close();
	return System::Void();
}

System::Void simpleData::newRowConstructorForm::bOk_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*Объявление экземпляра класса авторизированного пользователя*/
	User user;
	/*Проверка на заполнение всех пунктов*/
	if (tbDays->Text == "" || cbNames->Text == "" || cbOrganizations->Text == "" || tbHowManyDays->Text == "" ||
		tbMoneyInDay->Text == "" || tbTicketsCost->Text == "" || lRes->Text == "")
	{
		MessageBox::Show("Not all cells are filled!", "Error!");
		return System::Void();
	} 
	else
	{
		/*Создал объект класса базы данных*/
		Database^ workData = gcnew Database("workData");
		/*Формирование запроса на добавление новой строки в таблицу*/
		String^ query = "INSERT INTO [" + user.editTable + "] (ДатаВыезда, ФИО, Организация, КоличествоДней, Суточные, ЦенаБилета, ОбщаяСуммаРасходов) VALUES('"
			+ tbDays->Text + "', '" + cbNames->Text + "', '" + cbOrganizations->Text + "', '"
			+ tbHowManyDays->Text + "', '" + tbMoneyInDay->Text + "', '" + tbTicketsCost->Text + "', '"
			+ lRes->Text + "')";
		MessageBox::Show(query);
		/*Отправка запроса БД на добавление новой строки*/
		workData->doRequest(query, false);
		/*Сообщение об успешном добавлении новой строки*/
		MessageBox::Show("New row was sucsessfully created!", "Message");
		this->Close();
		return System::Void();
	}
}

