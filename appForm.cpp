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

System::Void simpleData::appForm::bDownload_Click(System::Object^ sender, System::EventArgs^ e)
{
	Database^ workData = gcnew Database("workData");
	list<Table^> tablseList = workData->coutTablesFromRequest();
	String^ query = tablseList.front()->getQueryForTable();
	OleDbDataReader^ workersTabel = workData->doRequest(query, true);

	list<Employee^> usersAutificationHistoryTable;
	while (workersTabel->Read())
	{
		Employee^ user = gcnew Employee(workersTabel[0]->ToString(),
			workersTabel[1]->ToString(), workersTabel[2]->ToString(), workersTabel[4]->ToString());
		usersAutificationHistoryTable.push_back(user);
	}

	Employee^ user = usersAutificationHistoryTable.back();

	for each (auto% i in tablseList)
	{
		if (Convert::ToInt32(user->coutAccessCode()) >= Convert::ToInt32(i->coutAccessCode()))
		{
			MessageBox::Show(i->coutTableName());
		}
	}
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
