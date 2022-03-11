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
	/*Создал объект класса базы данных*/
	Database^ workData = gcnew Database("workData");
	/*Получил список таблиц рабочей базы данных*/
	list<Table^> tablseList = workData->coutTablesFromRequest();
	/*Обратиллся к статичесокму классу авторизованного пользователя*/
	User user;
	/*Цикл проверяет достуепные авторизованному пользователю таблицы базы данных*/
	for each (auto % i in tablseList)
	{
		if (Convert::ToInt32(user.accessCode) >= Convert::ToInt32(i->coutAccessCode()))
		{
			lblEnableTables->Text += i->coutTableName() + "\n";
		}
	};
	/*
	Следующие три условия устанавливают значение доступа авторизованного 
	пользователя к той или иной кнопке согласно данным в структуре action в
	объекте статического класса user
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
	/*Объявление экземпляра класса авторизированного пользователя*/
	User user;
	/*Очистка холста dataGridView1*/
	dataGridView1->Columns->Clear();
	/*Создал объект класса базы данных*/
	Database^ workData = gcnew Database("workData");
	list<Table^> tablseList = workData->coutTablesFromRequest();
	/*Цикл совершает поиск таблицы указанной в поле ввода tbTableName*/
	for each (auto % i in tablseList)
	{
		if (Convert::ToString(tbTableName->Text) == Convert::ToString(i->coutTableName()))
		{
			/*Проверка доступности уискомой таблицы пользователю*/
			if (Convert::ToInt32(user.accessCode) >= Convert::ToInt32(i->coutAccessCode()))
			{
				/*Обозначаем, с какой таблице йработает пользователь*/
				user.editTable = i->coutTableName();
				/*В случае нахождения нужной таблицы создаётся запроса к таблице БД рабочей*/
				String^ query = i->getQueryForTable();
				/*Данные таблицы*/
				OleDbDataReader^ tabel = workData->doRequest(query, true);
				/*Данный цикл размещает на холсте dataGridView1 столбцы*/
				int i = 0;
				while (i < tabel->FieldCount)
				{
					dataGridView1->Columns->Add("", Convert::ToString(tabel->GetName(i)));
					i++;
				}
				/*Данный цикл размещает на холсте dataGridView1 строки*/
				int j = 0;
				while (tabel->Read())
				{
					/*С каждым щагом цикла создается новая строка и каждая ячейка заполняется данными*/
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
	/*Объявление экземпляра класса авторизированного пользователя*/
	User user;
	/*Индекс нового столбца на холсте dataGridView1*/
	int index = dataGridView1->CurrentRow->Index;
	/*Массив значений столбцов*/
	list<String^> data;
	/*Цикл заполняет списко data значениями столбцов*/
	int i = 0;
	while (i < dataGridView1->ColumnCount)
	{
		/*Проверка на заполнение всех таблиц*/
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
	/*Создал объект класса базы данных*/
	Database^ workData = gcnew Database("workData");
	/*Формирование запроса на добавление новой строки в таблицу*/
	String^ query = "INSERT INTO [" + user.editTable + "] VALUES(";
	/*Заполнение значений каждого столбца*/
	for each (auto % i in data)
	{
		query += "'" + i + "',";
	};
	query = query->Remove(query->Length - 1);
	query += ")";
	/*Отправка запроса БД на добавление новой строки*/
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
