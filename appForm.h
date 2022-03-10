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
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->groupBoxActions = (gcnew System::Windows::Forms::GroupBox());
			this->bDownload = (gcnew System::Windows::Forms::Button());
			this->bNewRow = (gcnew System::Windows::Forms::Button());
			this->bRowUpdate = (gcnew System::Windows::Forms::Button());
			this->bDeleteRow = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->groupBoxActions->SuspendLayout();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(13, 13);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->Size = System::Drawing::Size(807, 673);
			this->dataGridView1->TabIndex = 0;
			// 
			// groupBoxActions
			// 
			this->groupBoxActions->Controls->Add(this->bDeleteRow);
			this->groupBoxActions->Controls->Add(this->bRowUpdate);
			this->groupBoxActions->Controls->Add(this->bNewRow);
			this->groupBoxActions->Controls->Add(this->bDownload);
			this->groupBoxActions->Location = System::Drawing::Point(842, 13);
			this->groupBoxActions->Name = L"groupBoxActions";
			this->groupBoxActions->Size = System::Drawing::Size(229, 673);
			this->groupBoxActions->TabIndex = 1;
			this->groupBoxActions->TabStop = false;
			this->groupBoxActions->Text = L"Действия";
			// 
			// bDownload
			// 
			this->bDownload->Location = System::Drawing::Point(7, 175);
			this->bDownload->Name = L"bDownload";
			this->bDownload->Size = System::Drawing::Size(216, 53);
			this->bDownload->TabIndex = 0;
			this->bDownload->Text = L"Загрузить";
			this->bDownload->UseVisualStyleBackColor = true;
			this->bDownload->Click += gcnew System::EventHandler(this, &appForm::bDownload_Click);
			// 
			// bNewRow
			// 
			this->bNewRow->Location = System::Drawing::Point(7, 234);
			this->bNewRow->Name = L"bNewRow";
			this->bNewRow->Size = System::Drawing::Size(216, 53);
			this->bNewRow->TabIndex = 1;
			this->bNewRow->Text = L"Добавить";
			this->bNewRow->UseVisualStyleBackColor = true;
			this->bNewRow->Click += gcnew System::EventHandler(this, &appForm::bNewRow_Click);
			// 
			// bRowUpdate
			// 
			this->bRowUpdate->Location = System::Drawing::Point(7, 293);
			this->bRowUpdate->Name = L"bRowUpdate";
			this->bRowUpdate->Size = System::Drawing::Size(216, 53);
			this->bRowUpdate->TabIndex = 2;
			this->bRowUpdate->Text = L"Обновить";
			this->bRowUpdate->UseVisualStyleBackColor = true;
			this->bRowUpdate->Click += gcnew System::EventHandler(this, &appForm::bRowUpdate_Click);
			// 
			// bDeleteRow
			// 
			this->bDeleteRow->Location = System::Drawing::Point(7, 352);
			this->bDeleteRow->Name = L"bDeleteRow";
			this->bDeleteRow->Size = System::Drawing::Size(216, 53);
			this->bDeleteRow->TabIndex = 3;
			this->bDeleteRow->Text = L"Удалить";
			this->bDeleteRow->UseVisualStyleBackColor = true;
			this->bDeleteRow->Click += gcnew System::EventHandler(this, &appForm::bDeleteRow_Click);
			// 
			// appForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1083, 698);
			this->Controls->Add(this->groupBoxActions);
			this->Controls->Add(this->dataGridView1);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"appForm";
			this->Text = L"appForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->groupBoxActions->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void bDownload_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void bNewRow_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void bRowUpdate_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void bDeleteRow_Click(System::Object^ sender, System::EventArgs^ e);
};
}
