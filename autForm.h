#pragma once

namespace simpleData {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для autForm
	/// </summary>
	public ref class autForm : public System::Windows::Forms::Form
	{
	public:
		autForm(void)
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
		~autForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ autBtn;
	protected:

	private: System::Windows::Forms::TextBox^ tBPassword;

	private: System::Windows::Forms::TextBox^ tBLogin;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(autForm::typeid));
			this->autBtn = (gcnew System::Windows::Forms::Button());
			this->tBPassword = (gcnew System::Windows::Forms::TextBox());
			this->tBLogin = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// autBtn
			// 
			this->autBtn->Location = System::Drawing::Point(77, 151);
			this->autBtn->Name = L"autBtn";
			this->autBtn->Size = System::Drawing::Size(130, 51);
			this->autBtn->TabIndex = 0;
			this->autBtn->Text = L"Войти";
			this->autBtn->UseVisualStyleBackColor = true;
			this->autBtn->Click += gcnew System::EventHandler(this, &autForm::autBtn_Click);
			// 
			// tBPassword
			// 
			this->tBPassword->Location = System::Drawing::Point(50, 103);
			this->tBPassword->Name = L"tBPassword";
			this->tBPassword->PasswordChar = '*';
			this->tBPassword->Size = System::Drawing::Size(190, 20);
			this->tBPassword->TabIndex = 1;
			// 
			// tBLogin
			// 
			this->tBLogin->Location = System::Drawing::Point(50, 55);
			this->tBLogin->Name = L"tBLogin";
			this->tBLogin->Size = System::Drawing::Size(190, 20);
			this->tBLogin->TabIndex = 2;
			// 
			// autForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->tBLogin);
			this->Controls->Add(this->tBPassword);
			this->Controls->Add(this->autBtn);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"autForm";
			this->Text = L"Авторизация";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void autBtn_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
