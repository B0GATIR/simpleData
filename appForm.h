#pragma once

namespace simpleData {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для appForm
	/// </summary>
	public ref class appForm : public System::Windows::Forms::Form
	{
	public:
		appForm(void)
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
		~appForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::GroupBox^ groupBoxActions;
	private: System::Windows::Forms::Button^ bDeleteRow;
	private: System::Windows::Forms::Button^ bRowUpdate;
	private: System::Windows::Forms::Button^ bNewRow;
	private: System::Windows::Forms::Button^ bDownload;
	private: System::Windows::Forms::ComboBox^ cbTableName;








	protected:

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(appForm::typeid));
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->groupBoxActions = (gcnew System::Windows::Forms::GroupBox());
			this->cbTableName = (gcnew System::Windows::Forms::ComboBox());
			this->bDeleteRow = (gcnew System::Windows::Forms::Button());
			this->bRowUpdate = (gcnew System::Windows::Forms::Button());
			this->bNewRow = (gcnew System::Windows::Forms::Button());
			this->bDownload = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->groupBoxActions->SuspendLayout();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(10, 11);
			this->dataGridView1->Margin = System::Windows::Forms::Padding(2);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->Size = System::Drawing::Size(605, 547);
			this->dataGridView1->TabIndex = 0;
			// 
			// groupBoxActions
			// 
			this->groupBoxActions->Controls->Add(this->cbTableName);
			this->groupBoxActions->Controls->Add(this->bDeleteRow);
			this->groupBoxActions->Controls->Add(this->bRowUpdate);
			this->groupBoxActions->Controls->Add(this->bNewRow);
			this->groupBoxActions->Controls->Add(this->bDownload);
			this->groupBoxActions->Location = System::Drawing::Point(619, 11);
			this->groupBoxActions->Margin = System::Windows::Forms::Padding(2);
			this->groupBoxActions->Name = L"groupBoxActions";
			this->groupBoxActions->Padding = System::Windows::Forms::Padding(2);
			this->groupBoxActions->Size = System::Drawing::Size(190, 547);
			this->groupBoxActions->TabIndex = 1;
			this->groupBoxActions->TabStop = false;
			this->groupBoxActions->Text = L"Действия";
			// 
			// cbTableName
			// 
			this->cbTableName->FormattingEnabled = true;
			this->cbTableName->Location = System::Drawing::Point(16, 66);
			this->cbTableName->Name = L"cbTableName";
			this->cbTableName->Size = System::Drawing::Size(162, 21);
			this->cbTableName->TabIndex = 4;
			// 
			// bDeleteRow
			// 
			this->bDeleteRow->Location = System::Drawing::Point(16, 495);
			this->bDeleteRow->Margin = System::Windows::Forms::Padding(2);
			this->bDeleteRow->Name = L"bDeleteRow";
			this->bDeleteRow->Size = System::Drawing::Size(162, 43);
			this->bDeleteRow->TabIndex = 3;
			this->bDeleteRow->Text = L"Удалить";
			this->bDeleteRow->UseVisualStyleBackColor = true;
			this->bDeleteRow->Click += gcnew System::EventHandler(this, &appForm::bDeleteRow_Click);
			// 
			// bRowUpdate
			// 
			this->bRowUpdate->Location = System::Drawing::Point(16, 448);
			this->bRowUpdate->Margin = System::Windows::Forms::Padding(2);
			this->bRowUpdate->Name = L"bRowUpdate";
			this->bRowUpdate->Size = System::Drawing::Size(162, 43);
			this->bRowUpdate->TabIndex = 2;
			this->bRowUpdate->Text = L"Обновить";
			this->bRowUpdate->UseVisualStyleBackColor = true;
			this->bRowUpdate->Click += gcnew System::EventHandler(this, &appForm::bRowUpdate_Click);
			// 
			// bNewRow
			// 
			this->bNewRow->Location = System::Drawing::Point(16, 401);
			this->bNewRow->Margin = System::Windows::Forms::Padding(2);
			this->bNewRow->Name = L"bNewRow";
			this->bNewRow->Size = System::Drawing::Size(162, 43);
			this->bNewRow->TabIndex = 1;
			this->bNewRow->Text = L"Добавить";
			this->bNewRow->UseVisualStyleBackColor = true;
			this->bNewRow->Click += gcnew System::EventHandler(this, &appForm::bNewRow_Click);
			// 
			// bDownload
			// 
			this->bDownload->Location = System::Drawing::Point(16, 17);
			this->bDownload->Margin = System::Windows::Forms::Padding(2);
			this->bDownload->Name = L"bDownload";
			this->bDownload->Size = System::Drawing::Size(162, 43);
			this->bDownload->TabIndex = 0;
			this->bDownload->Text = L"Загрузить";
			this->bDownload->UseVisualStyleBackColor = true;
			this->bDownload->Click += gcnew System::EventHandler(this, &appForm::bDownload_Click);
			// 
			// appForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(812, 567);
			this->Controls->Add(this->groupBoxActions);
			this->Controls->Add(this->dataGridView1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"appForm";
			this->Text = L"Учет командировочных расходов";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &appForm::onClose);
			this->Load += gcnew System::EventHandler(this, &appForm::appForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->groupBoxActions->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void bDownload_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void bNewRow_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void bRowUpdate_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void bDeleteRow_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void appForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void onClose(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e);
};
}
