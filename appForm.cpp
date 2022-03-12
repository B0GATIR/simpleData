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
/*Функция совершает проверку значенйи столбцов и заносит их в список*/
list<String^> getDataValues(System::Windows::Forms::DataGridView^ dataGridView1)
{
	list<String^> values;
	/*Цикл заполняет список data значениями столбцов*/
	int i = 0;
	while (i < dataGridView1->ColumnCount)
	{
		/*Проверка на заполнение всех таблиц*/
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
	/*Обратиллся к статичесокму классу авторизованного пользователя*/
	User user;
	/*Проверка, была ли совершена авторизация*/
	if (user.login == nullptr)
	{
		this->Close();
	}
	/*Создал объект класса базы данных*/
	Database^ workData = gcnew Database("workData");
	/*Получил список таблиц рабочей базы данных*/
	list<Table^> tablseList = workData->coutTablesFromRequest();
	/*Цикл проверяет достуепные авторизованному пользователю таблицы базы данных*/
	for each (auto % i in tablseList)
	{
		if (Convert::ToInt32(user.accessCode) >= Convert::ToInt32(i->coutAccessCode()))
		{
			cbTableName->Items->Add(i->coutTableName());
		}
	};
	/*
	Следующие четыре условия устанавливают значение доступа авторизованного 
	пользователя к кнопкам и полям таблиц согласно данным в структуре action в
	объекте статического класса user и accessCode
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
		if (Convert::ToString(cbTableName->Text) == Convert::ToString(i->coutTableName()))
		{
			/*Проверка доступности искомой таблицы пользователю*/
			if (Convert::ToInt32(user.accessCode) >= Convert::ToInt32(i->coutAccessCode()))
			{
				/*Обозначаем, с какой таблицей работает пользователь*/
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
			/*Индекс нового столбца на холсте dataGridView1*/
			int index = Convert::ToInt32(dataGridView1->Rows[dataGridView1->SelectedCells[0]->RowIndex]->Cells[0]->Value);
			/*Массив значений столбцов*/
			list<String^> data = getDataValues(dataGridView1);
			/*Проверка на случай если были заполнены не все строки*/
			if (data.size() == 0)
			{
				return System::Void();
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
			/*Сообщение оь успешном добавлении новой строки*/
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
	/*Объявление экземпляра класса авторизированного пользователя*/
	User user;
	if (dataGridView1->ColumnCount != 0)
	{
		/*Индекс изменяемого столбца на холсте dataGridView1*/
		int index = Convert::ToInt32(dataGridView1->Rows[dataGridView1->SelectedCells[0]->RowIndex]->Cells[0]->Value);
		/*Массив значений столбцов*/
		list<String^> data = getDataValues(dataGridView1);
		/*Проверка на случай если были заполнены не все строки*/
		if (data.size() == 0)
		{
			return System::Void();
		}
		/*Создал объект класса базы данных*/
		Database^ workData = gcnew Database("workData");
		/*Формирование запроса на изменение строки в таблице*/
		String^ query = "UPDATE [" + user.editTable + "] SET ";
		/*Заполнение значений каждого столбца*/
		int j = 0;
		for each (auto % i in data)
		{
			query += j == 0 ? "" : dataGridView1->Columns[j]->HeaderText + "= '" + i + "', ";
			j++;
		};
		query = query->Remove(query->Length - 2);
		query += " WHERE Counter = " + index;
		/*Отправка запроса БД на изменеие строки*/
		workData->doRequest(query, false);
		/*Сообщение об успешном изменении строки*/
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
	/*Объявление экземпляра класса авторизированного пользователя*/
	User user;
	if (dataGridView1->ColumnCount != 0)
	{
		/*Индекс удаляемого столбца на холсте dataGridView1*/
		int index = Convert::ToInt32(dataGridView1->Rows[dataGridView1->SelectedCells[0]->RowIndex]->Cells[0]->Value);
		/*Создал объект класса базы данных*/
		Database^ workData = gcnew Database("workData");
		/*Формирование запроса на удаление строки в таблице*/
		String^ query = "DELETE FROM [" + user.editTable + "] WHERE Counter = " + index;
		/*Отправка запроса БД на удаление строки*/
		workData->doRequest(query, false);
		/*Сообщение об успешном удалении строки*/
		MessageBox::Show("Selected row was sucsessfully deleted!", "Message");
		return System::Void();
	}
	else
	{
		MessageBox::Show("Choose the table!", "Message");
		return System::Void();
	}
}
