#pragma once

namespace simpleData {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для newRowConstructorForm
	/// </summary>
	public ref class newRowConstructorForm : public System::Windows::Forms::Form
	{
	public:
		newRowConstructorForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~newRowConstructorForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ lDays;
	private: System::Windows::Forms::TextBox^ tbDays;
	protected:

	protected:

	private: System::Windows::Forms::Label^ lName;
	private: System::Windows::Forms::ComboBox^ cbNames;
	private: System::Windows::Forms::ComboBox^ cbOrganizations;



	private: System::Windows::Forms::Label^ lOrganization;
	private: System::Windows::Forms::TextBox^ tbHowManyDays;


	private: System::Windows::Forms::Label^ lHowManyDays;
	private: System::Windows::Forms::TextBox^ tbMoneyInDay;


	private: System::Windows::Forms::Label^ lMoneyInDay;
	private: System::Windows::Forms::TextBox^ tbTicketsCost;


	private: System::Windows::Forms::Label^ lTicketsCost;
	private: System::Windows::Forms::Button^ bOk;
	private: System::Windows::Forms::Button^ bCancel;



	private: System::Windows::Forms::Label^ lCost;
	private: System::Windows::Forms::Label^ lRes;



	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(newRowConstructorForm::typeid));
			this->lDays = (gcnew System::Windows::Forms::Label());
			this->tbDays = (gcnew System::Windows::Forms::TextBox());
			this->lName = (gcnew System::Windows::Forms::Label());
			this->cbNames = (gcnew System::Windows::Forms::ComboBox());
			this->cbOrganizations = (gcnew System::Windows::Forms::ComboBox());
			this->lOrganization = (gcnew System::Windows::Forms::Label());
			this->tbHowManyDays = (gcnew System::Windows::Forms::TextBox());
			this->lHowManyDays = (gcnew System::Windows::Forms::Label());
			this->tbMoneyInDay = (gcnew System::Windows::Forms::TextBox());
			this->lMoneyInDay = (gcnew System::Windows::Forms::Label());
			this->tbTicketsCost = (gcnew System::Windows::Forms::TextBox());
			this->lTicketsCost = (gcnew System::Windows::Forms::Label());
			this->bOk = (gcnew System::Windows::Forms::Button());
			this->bCancel = (gcnew System::Windows::Forms::Button());
			this->lCost = (gcnew System::Windows::Forms::Label());
			this->lRes = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// lDays
			// 
			this->lDays->AutoSize = true;
			this->lDays->Location = System::Drawing::Point(12, 40);
			this->lDays->Name = L"lDays";
			this->lDays->Size = System::Drawing::Size(74, 13);
			this->lDays->TabIndex = 0;
			this->lDays->Text = L"Дата выезда";
			// 
			// tbDays
			// 
			this->tbDays->Location = System::Drawing::Point(192, 40);
			this->tbDays->Name = L"tbDays";
			this->tbDays->Size = System::Drawing::Size(178, 20);
			this->tbDays->TabIndex = 1;
			// 
			// lName
			// 
			this->lName->AutoSize = true;
			this->lName->Location = System::Drawing::Point(12, 66);
			this->lName->Name = L"lName";
			this->lName->Size = System::Drawing::Size(34, 13);
			this->lName->TabIndex = 2;
			this->lName->Text = L"ФИО";
			// 
			// cbNames
			// 
			this->cbNames->FormattingEnabled = true;
			this->cbNames->Location = System::Drawing::Point(192, 66);
			this->cbNames->Name = L"cbNames";
			this->cbNames->Size = System::Drawing::Size(178, 21);
			this->cbNames->TabIndex = 3;
			// 
			// cbOrganizations
			// 
			this->cbOrganizations->FormattingEnabled = true;
			this->cbOrganizations->Location = System::Drawing::Point(192, 93);
			this->cbOrganizations->Name = L"cbOrganizations";
			this->cbOrganizations->Size = System::Drawing::Size(178, 21);
			this->cbOrganizations->TabIndex = 5;
			// 
			// lOrganization
			// 
			this->lOrganization->AutoSize = true;
			this->lOrganization->Location = System::Drawing::Point(12, 93);
			this->lOrganization->Name = L"lOrganization";
			this->lOrganization->Size = System::Drawing::Size(74, 13);
			this->lOrganization->TabIndex = 4;
			this->lOrganization->Text = L"Организация";
			// 
			// tbHowManyDays
			// 
			this->tbHowManyDays->Location = System::Drawing::Point(192, 120);
			this->tbHowManyDays->Name = L"tbHowManyDays";
			this->tbHowManyDays->Size = System::Drawing::Size(178, 20);
			this->tbHowManyDays->TabIndex = 7;
			this->tbHowManyDays->TextChanged += gcnew System::EventHandler(this, &newRowConstructorForm::onChangeDays);
			// 
			// lHowManyDays
			// 
			this->lHowManyDays->AutoSize = true;
			this->lHowManyDays->Location = System::Drawing::Point(12, 120);
			this->lHowManyDays->Name = L"lHowManyDays";
			this->lHowManyDays->Size = System::Drawing::Size(68, 13);
			this->lHowManyDays->TabIndex = 6;
			this->lHowManyDays->Text = L"Кол-во дней";
			// 
			// tbMoneyInDay
			// 
			this->tbMoneyInDay->Location = System::Drawing::Point(192, 146);
			this->tbMoneyInDay->Name = L"tbMoneyInDay";
			this->tbMoneyInDay->Size = System::Drawing::Size(178, 20);
			this->tbMoneyInDay->TabIndex = 9;
			this->tbMoneyInDay->TextChanged += gcnew System::EventHandler(this, &newRowConstructorForm::onChangeMoneyInDays);
			// 
			// lMoneyInDay
			// 
			this->lMoneyInDay->AutoSize = true;
			this->lMoneyInDay->Location = System::Drawing::Point(12, 146);
			this->lMoneyInDay->Name = L"lMoneyInDay";
			this->lMoneyInDay->Size = System::Drawing::Size(55, 13);
			this->lMoneyInDay->TabIndex = 8;
			this->lMoneyInDay->Text = L"Суточные";
			// 
			// tbTicketsCost
			// 
			this->tbTicketsCost->Location = System::Drawing::Point(192, 172);
			this->tbTicketsCost->Name = L"tbTicketsCost";
			this->tbTicketsCost->Size = System::Drawing::Size(178, 20);
			this->tbTicketsCost->TabIndex = 11;
			this->tbTicketsCost->TextChanged += gcnew System::EventHandler(this, &newRowConstructorForm::onChangeTicketsCost);
			// 
			// lTicketsCost
			// 
			this->lTicketsCost->AutoSize = true;
			this->lTicketsCost->Location = System::Drawing::Point(12, 172);
			this->lTicketsCost->Name = L"lTicketsCost";
			this->lTicketsCost->Size = System::Drawing::Size(106, 13);
			this->lTicketsCost->TabIndex = 10;
			this->lTicketsCost->Text = L"Стоимость билетов";
			// 
			// bOk
			// 
			this->bOk->Location = System::Drawing::Point(77, 267);
			this->bOk->Name = L"bOk";
			this->bOk->Size = System::Drawing::Size(109, 32);
			this->bOk->TabIndex = 12;
			this->bOk->Text = L"Принять";
			this->bOk->UseVisualStyleBackColor = true;
			this->bOk->Click += gcnew System::EventHandler(this, &newRowConstructorForm::bOk_Click);
			// 
			// bCancel
			// 
			this->bCancel->Location = System::Drawing::Point(192, 267);
			this->bCancel->Name = L"bCancel";
			this->bCancel->Size = System::Drawing::Size(109, 32);
			this->bCancel->TabIndex = 13;
			this->bCancel->Text = L"Отмена";
			this->bCancel->UseVisualStyleBackColor = true;
			this->bCancel->Click += gcnew System::EventHandler(this, &newRowConstructorForm::bCancel_Click);
			// 
			// lCost
			// 
			this->lCost->AutoSize = true;
			this->lCost->Location = System::Drawing::Point(12, 217);
			this->lCost->Name = L"lCost";
			this->lCost->Size = System::Drawing::Size(78, 13);
			this->lCost->TabIndex = 14;
			this->lCost->Text = L"Общая сумма";
			// 
			// lRes
			// 
			this->lRes->AutoSize = true;
			this->lRes->Location = System::Drawing::Point(189, 217);
			this->lRes->Name = L"lRes";
			this->lRes->Size = System::Drawing::Size(16, 13);
			this->lRes->TabIndex = 15;
			this->lRes->Text = L"---";
			// 
			// newRowConstructorForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(382, 327);
			this->Controls->Add(this->lRes);
			this->Controls->Add(this->lCost);
			this->Controls->Add(this->bCancel);
			this->Controls->Add(this->bOk);
			this->Controls->Add(this->tbTicketsCost);
			this->Controls->Add(this->lTicketsCost);
			this->Controls->Add(this->tbMoneyInDay);
			this->Controls->Add(this->lMoneyInDay);
			this->Controls->Add(this->tbHowManyDays);
			this->Controls->Add(this->lHowManyDays);
			this->Controls->Add(this->cbOrganizations);
			this->Controls->Add(this->lOrganization);
			this->Controls->Add(this->cbNames);
			this->Controls->Add(this->lName);
			this->Controls->Add(this->tbDays);
			this->Controls->Add(this->lDays);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"newRowConstructorForm";
			this->Text = L"Конструктор новой командировки";
			this->Load += gcnew System::EventHandler(this, &newRowConstructorForm::newRowConstructorForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void newRowConstructorForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void onChangeDays(System::Object^ sender, System::EventArgs^ e);
	private: System::Void onChangeMoneyInDays(System::Object^ sender, System::EventArgs^ e);
	private: System::Void onChangeTicketsCost(System::Object^ sender, System::EventArgs^ e);
	private: System::Void bCancel_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void bOk_Click(System::Object^ sender, System::EventArgs^ e);
};
}
