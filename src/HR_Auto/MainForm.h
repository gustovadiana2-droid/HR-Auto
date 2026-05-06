#pragma once

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;

namespace HRAuto {

    public ref class User {
    public:
        int Id;
        String^ FullName;
        String^ Login;
        String^ Password;
        String^ Role;
        String^ Status;
    };

    public ref class Payslip {
    public:
        String^ Period;
        String^ Accrued;
        String^ Deducted;
        String^ ToPay;
        String^ Status;
    };

    public ref class Database {
    public:
        static List<User^>^ Users = gcnew List<User^>();
        static List<Payslip^>^ Payslips = gcnew List<Payslip^>();
        static User^ CurrentUser = nullptr;

        static Database() {
            User^ admin = gcnew User();
            admin->Id = 1;
            admin->FullName = L"Иванов Иван Иванович";
            admin->Login = L"ivanov";
            admin->Password = L"admin123";
            admin->Role = L"Администратор";
            admin->Status = L"Активен";
            Users->Add(admin);

            User^ hr = gcnew User();
            hr->Id = 2;
            hr->FullName = L"Петрова Мария Сергеевна";
            hr->Login = L"petrova";
            hr->Password = L"hr123";
            hr->Role = L"Кадровик";
            hr->Status = L"Активен";
            Users->Add(hr);

            User^ buh = gcnew User();
            buh->Id = 3;
            buh->FullName = L"Сидоров Алексей Викторович";
            buh->Login = L"sidorov";
            buh->Password = L"buh123";
            buh->Role = L"Бухгалтер";
            buh->Status = L"Заблокирован";
            Users->Add(buh);

            User^ emp = gcnew User();
            emp->Id = 4;
            emp->FullName = L"Козлова Екатерина Дмитриевна";
            emp->Login = L"kozlova";
            emp->Password = L"emp123";
            emp->Role = L"Сотрудник";
            emp->Status = L"Активен";
            Users->Add(emp);

            Payslip^ p1 = gcnew Payslip();
            p1->Period = L"Апрель 2026";
            p1->Accrued = L"65 432";
            p1->Deducted = L"8 506";
            p1->ToPay = L"56 926";
            p1->Status = L"Подтвержден";
            Payslips->Add(p1);

            Payslip^ p2 = gcnew Payslip();
            p2->Period = L"Март 2026";
            p2->Accrued = L"62 150";
            p2->Deducted = L"8 080";
            p2->ToPay = L"54 070";
            p2->Status = L"Отправлен";
            Payslips->Add(p2);

            Payslip^ p3 = gcnew Payslip();
            p3->Period = L"Февраль 2026";
            p3->Accrued = L"58 900";
            p3->Deducted = L"7 657";
            p3->ToPay = L"51 243";
            p3->Status = L"Подтвержден";
            Payslips->Add(p3);

            Payslip^ p4 = gcnew Payslip();
            p4->Period = L"Январь 2026";
            p4->Accrued = L"65 000";
            p4->Deducted = L"8 450";
            p4->ToPay = L"56 550";
            p4->Status = L"Подтвержден";
            Payslips->Add(p4);
        }

        static User^ Authenticate(String^ login, String^ password) {
            for each (User ^ user in Users) {
                if (user->Login == login && user->Password == password) {
                    return user;
                }
            }
            return nullptr;
        }
    };

    public ref class MainForm : public Form {
    private:
        TextBox^ txtLogin;
        TextBox^ txtPassword;
        TextBox^ txtRegFullName;
        TextBox^ txtRegEmail;
        TextBox^ txtRegLogin;
        TextBox^ txtRegPassword;
        ComboBox^ cmbRole;
        DataGridView^ dgvUsers;
        DataGridView^ dgvPayslips;

        Color primaryColor = Color::FromArgb(126, 34, 206);  // Фиолетовый
        Color darkColor = Color::FromArgb(45, 42, 97);
        Color bgColor = Color::FromArgb(240, 242, 255); Color cardColor = Color::White;
        Color grayColor = Color::FromArgb(108, 117, 125);
        Color dangerColor = Color::FromArgb(220, 53, 69);
        Color successColor = Color::FromArgb(40, 167, 69);
        Color warningColor = Color::FromArgb(255, 193, 7);

    public:
        MainForm() {
            this->Text = L"HR-Auto | Автоматизированный документооборот";
            this->Size = Drawing::Size(1100, 750);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->StartPosition = FormStartPosition::CenterScreen;
            this->MaximizeBox = false;
            this->BackColor = bgColor;
            ShowLogin();
        }

    private:
        Panel^ CreateRoundedPanel(int width, int height, Color backColor) {
            Panel^ panel = gcnew Panel();
            panel->Size = Drawing::Size(width, height);
            panel->BackColor = backColor;
            return panel;
        }

        Button^ CreateButton(String^ text, int x, int y, int width, int height, Color backColor, Color foreColor) {
            Button^ btn = gcnew Button();
            btn->Text = text;
            btn->Location = Drawing::Point(x, y);
            btn->Size = Drawing::Size(width, height);
            btn->BackColor = backColor;
            btn->ForeColor = foreColor;
            btn->FlatStyle = FlatStyle::Flat;
            btn->FlatAppearance->BorderSize = 0;
            btn->FlatAppearance->MouseOverBackColor = Color::FromArgb(
                Math::Max(0, backColor.R - 30),
                Math::Max(0, backColor.G - 30),
                Math::Max(0, backColor.B - 30));
            btn->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
            btn->Cursor = Cursors::Hand;
            return btn;
        }

        TextBox^ CreateTextBox(String^ placeholder, int x, int y, int width) {
            TextBox^ txt = gcnew TextBox();
            txt->Text = placeholder;
            txt->ForeColor = grayColor;
            txt->Location = Drawing::Point(x, y);
            txt->Size = Drawing::Size(width, 38);
            txt->Font = gcnew Drawing::Font(L"Segoe UI", 10.5F);
            txt->BorderStyle = BorderStyle::FixedSingle;
            txt->BackColor = Color::FromArgb(248, 249, 255);
            txt->Enter += gcnew EventHandler(this, &MainForm::OnPlaceholderEnter);
            txt->Leave += gcnew EventHandler(this, &MainForm::OnPlaceholderLeave);
            return txt;
        }

        // ========== ЭКРАН ВХОДА ==========
        void ShowLogin() {
            this->Controls->Clear();
            this->BackColor = bgColor;

            // Карточка входа
            Panel^ card = gcnew Panel();
            card->Size = Drawing::Size(430, 400);
            card->Location = Drawing::Point(335, 220);
            card->BackColor = cardColor;
            this->Controls->Add(card);

            // Градиентная панель
            Panel^ gradientPanel = gcnew Panel();
            gradientPanel->Size = Drawing::Size(1100, 280);
            gradientPanel->Location = Drawing::Point(0, 0);
            gradientPanel->BackColor = primaryColor;
            this->Controls->Add(gradientPanel);

            Label^ lblAppName = gcnew Label();
            lblAppName->Text = L"HR-Auto";
            lblAppName->Font = gcnew Drawing::Font(L"Segoe UI", 42.0F, FontStyle::Bold);
            lblAppName->ForeColor = Color::White;
            lblAppName->Location = Drawing::Point(320, 60);
            lblAppName->Size = Drawing::Size(460, 70);
            lblAppName->TextAlign = ContentAlignment::MiddleCenter;
            gradientPanel->Controls->Add(lblAppName);

            Label^ lblAppDesc = gcnew Label();
            lblAppDesc->Text = L"Система автоматизированного документооборота";
            lblAppDesc->Font = gcnew Drawing::Font(L"Segoe UI", 13.0F);
            lblAppDesc->ForeColor = Color::FromArgb(220, 220, 255);
            lblAppDesc->Location = Drawing::Point(240, 140);
            lblAppDesc->Size = Drawing::Size(620, 30);
            lblAppDesc->TextAlign = ContentAlignment::MiddleCenter;
            gradientPanel->Controls->Add(lblAppDesc);



            Label^ lblTitle = gcnew Label();
            lblTitle->Text = L"Вход в аккаунт";
            lblTitle->Font = gcnew Drawing::Font(L"Segoe UI", 18.0F, FontStyle::Bold);
            lblTitle->ForeColor = darkColor;
            lblTitle->Location = Drawing::Point(35, 30);
            lblTitle->AutoSize = true;
            card->Controls->Add(lblTitle);

            Label^ lblLogin = gcnew Label();
            lblLogin->Text = L"Логин";
            lblLogin->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
            lblLogin->ForeColor = darkColor;
            lblLogin->Location = Drawing::Point(40, 80);
            lblLogin->AutoSize = true;
            card->Controls->Add(lblLogin);

            txtLogin = CreateTextBox(L"Введите ваш логин", 40, 105, 350);
            txtLogin->Name = L"txtLogin";
            card->Controls->Add(txtLogin);

            Label^ lblPass = gcnew Label();
            lblPass->Text = L"Пароль";
            lblPass->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
            lblPass->ForeColor = darkColor;
            lblPass->Location = Drawing::Point(40, 160);
            lblPass->AutoSize = true;
            card->Controls->Add(lblPass);

            txtPassword = gcnew TextBox();
            txtPassword->Text = L"Введите ваш пароль";
            txtPassword->ForeColor = grayColor;
            txtPassword->Location = Drawing::Point(40, 185);
            txtPassword->Size = Drawing::Size(350, 38);
            txtPassword->Font = gcnew Drawing::Font(L"Segoe UI", 10.5F);
            txtPassword->BorderStyle = BorderStyle::FixedSingle;
            txtPassword->BackColor = Color::FromArgb(248, 249, 255);
            txtPassword->Enter += gcnew EventHandler(this, &MainForm::OnPassEnter);
            txtPassword->Leave += gcnew EventHandler(this, &MainForm::OnPassLeave);
            card->Controls->Add(txtPassword);

            Button^ btnLogin = CreateButton(L"Войти в систему", 40, 265, 350, 42, primaryColor, Color::White);
            btnLogin->Click += gcnew EventHandler(this, &MainForm::BtnLoginClick);
            card->Controls->Add(btnLogin);

            LinkLabel^ linkForgot = gcnew LinkLabel();
            linkForgot->Text = L"Забыли пароль?";
            linkForgot->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
            linkForgot->Location = Drawing::Point(40, 325);
            linkForgot->AutoSize = true;
            linkForgot->LinkColor = primaryColor;
            linkForgot->ActiveLinkColor = darkColor;
            linkForgot->Click += gcnew EventHandler(this, &MainForm::LinkForgotClick);
            card->Controls->Add(linkForgot);

            LinkLabel^ linkReg = gcnew LinkLabel();
            linkReg->Text = L"Создать аккаунт";
            linkReg->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F, FontStyle::Bold);
            linkReg->Location = Drawing::Point(300, 325);
            linkReg->AutoSize = true;
            linkReg->LinkColor = primaryColor;
            linkReg->ActiveLinkColor = darkColor;
            linkReg->Click += gcnew EventHandler(this, &MainForm::ShowRegister);
            card->Controls->Add(linkReg);
        }

        // ========== ЭКРАН РЕГИСТРАЦИИ ==========
        void ShowRegister(Object^ sender, EventArgs^ e) {
            this->Controls->Clear();
            this->BackColor = bgColor;

            Panel^ card = gcnew Panel();
            card->Size = Drawing::Size(460, 520);
            card->Location = Drawing::Point(320, 140);
            card->BackColor = cardColor;
            this->Controls->Add(card);

            Panel^ gradientPanel = gcnew Panel();
            gradientPanel->Size = Drawing::Size(1100, 180);
            gradientPanel->Location = Drawing::Point(0, 0);
            gradientPanel->BackColor = primaryColor;
            this->Controls->Add(gradientPanel);

            Label^ lblTitle = gcnew Label();
            lblTitle->Text = L"Создание аккаунта";
            lblTitle->Font = gcnew Drawing::Font(L"Segoe UI", 28.0F, FontStyle::Bold);
            lblTitle->ForeColor = Color::White;
            lblTitle->Location = Drawing::Point(300, 50);
            lblTitle->Size = Drawing::Size(500, 50);
            lblTitle->TextAlign = ContentAlignment::MiddleCenter;
            gradientPanel->Controls->Add(lblTitle);



            // Создаем текстовые поля ДО передачи в AddRegField
            txtRegFullName = gcnew TextBox();
            txtRegEmail = gcnew TextBox();
            txtRegLogin = gcnew TextBox();
            txtRegPassword = gcnew TextBox();

            AddRegField(card, L"Полное имя", 25, txtRegFullName, L"Иванов Иван Иванович");
            AddRegField(card, L"Email", 90, txtRegEmail, L"ivanov@example.com");
            AddRegField(card, L"Логин", 155, txtRegLogin, L"Введите логин");
            AddRegField(card, L"Пароль", 220, txtRegPassword, L"Введите пароль");

            // Для пароля добавляем специальную обработку
            txtRegPassword->Enter -= gcnew EventHandler(this, &MainForm::OnPlaceholderEnter);
            txtRegPassword->Leave -= gcnew EventHandler(this, &MainForm::OnPlaceholderLeave);
            txtRegPassword->Enter += gcnew EventHandler(this, &MainForm::OnRegPassEnter);
            txtRegPassword->Leave += gcnew EventHandler(this, &MainForm::OnRegPassLeave);

            Label^ lblRole = gcnew Label();
            lblRole->Text = L"Роль";
            lblRole->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
            lblRole->ForeColor = darkColor;
            lblRole->Location = Drawing::Point(45, 285);
            lblRole->AutoSize = true;
            card->Controls->Add(lblRole);

            cmbRole = gcnew ComboBox();
            cmbRole->Location = Drawing::Point(45, 310);
            cmbRole->Size = Drawing::Size(370, 38);
            cmbRole->Font = gcnew Drawing::Font(L"Segoe UI", 10.5F);
            cmbRole->Items->Add(L"Сотрудник");
            cmbRole->Items->Add(L"Кадровик");
            cmbRole->Items->Add(L"Бухгалтер");
            cmbRole->Items->Add(L"Администратор");
            cmbRole->SelectedIndex = 0;
            cmbRole->DropDownStyle = ComboBoxStyle::DropDownList;
            cmbRole->BackColor = Color::FromArgb(248, 249, 255);
            card->Controls->Add(cmbRole);

            Button^ btnReg = CreateButton(L"Зарегистрироваться", 45, 370, 370, 42, primaryColor, Color::White);
            btnReg->Click += gcnew EventHandler(this, &MainForm::BtnRegisterClick);
            card->Controls->Add(btnReg);

            LinkLabel^ linkBack = gcnew LinkLabel();
            linkBack->Text = L"← Вернуться ко входу";
            linkBack->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
            linkBack->Location = Drawing::Point(45, 430);
            linkBack->AutoSize = true;
            linkBack->LinkColor = primaryColor;
            linkBack->Click += gcnew EventHandler(this, &MainForm::LinkBackClick);
            card->Controls->Add(linkBack);
        }

        void AddRegField(Panel^ parent, String^ labelText, int yPos, TextBox^ txt, String^ defaultText) {
            Label^ lbl = gcnew Label();
            lbl->Text = labelText;
            lbl->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
            lbl->ForeColor = darkColor;
            lbl->Location = Drawing::Point(45, yPos);
            lbl->AutoSize = true;
            parent->Controls->Add(lbl);

            txt->Location = Drawing::Point(45, yPos + 22);
            txt->Size = Drawing::Size(370, 38);
            txt->Font = gcnew Drawing::Font(L"Segoe UI", 10.5F);
            txt->Text = defaultText;
            txt->ForeColor = grayColor;
            txt->BorderStyle = BorderStyle::FixedSingle;
            txt->BackColor = Color::FromArgb(248, 249, 255);
            txt->Enter += gcnew EventHandler(this, &MainForm::OnPlaceholderEnter);
            txt->Leave += gcnew EventHandler(this, &MainForm::OnPlaceholderLeave);
            parent->Controls->Add(txt);
        }

        // Обработчики для пароля в форме регистрации
        void OnRegPassEnter(Object^ sender, EventArgs^ e) {
            TextBox^ txt = (TextBox^)sender;
            if (txt->ForeColor == grayColor) {
                txt->Text = L"";
                txt->ForeColor = darkColor;
                txt->PasswordChar = '*';
            }
        }

        void OnRegPassLeave(Object^ sender, EventArgs^ e) {
            TextBox^ txt = (TextBox^)sender;
            if (String::IsNullOrWhiteSpace(txt->Text)) {
                txt->PasswordChar = '\0';
                txt->Text = L"Введите пароль";
                txt->ForeColor = grayColor;
            }
        }

        // ========== ГЛАВНАЯ АДМИНКИ ==========
        void ShowAdminDashboard() {
            this->Controls->Clear();
            this->BackColor = bgColor;

            CreateAdminHeader();

            Label^ lblWelcome = gcnew Label();
            lblWelcome->Text = L"Добро пожаловать, " + Database::CurrentUser->FullName + L"!"; lblWelcome->Font = gcnew Drawing::Font(L"Segoe UI", 20.0F, FontStyle::Bold);
            lblWelcome->ForeColor = darkColor;
            lblWelcome->Location = Drawing::Point(25, 85);
            lblWelcome->AutoSize = true;
            this->Controls->Add(lblWelcome);

            Label^ lblSub = gcnew Label();
            lblSub->Text = L"Сводка по системе за сегодня";
            lblSub->Font = gcnew Drawing::Font(L"Segoe UI", 11.0F);
            lblSub->ForeColor = grayColor;
            lblSub->Location = Drawing::Point(25, 118);
            lblSub->AutoSize = true;
            this->Controls->Add(lblSub);

            array<String^>^ titles = { L"Пользователи", L"Сотрудники", L"Активных сессий", L"Отчетов за месяц" };
            array<String^>^ values = { L"24", L"156", L"8", L"12" };
            array<String^>^ icons = { L"👥", L"👤", L"🟢", L"📊" };
            array<Color>^ colors = { primaryColor, successColor, warningColor, Color::FromArgb(111, 66, 193) };

            for (int i = 0; i < 4; i++) {
                Panel^ stat = gcnew Panel();
                stat->Size = Drawing::Size(252, 100);
                stat->Location = Drawing::Point(25 + i * 265, 155);
                stat->BackColor = cardColor;

                Label^ iconLabel = gcnew Label();
                iconLabel->Text = icons[i];
                iconLabel->Font = gcnew Drawing::Font(L"Segoe UI", 28.0F);
                iconLabel->Location = Drawing::Point(15, 15);
                iconLabel->Size = Drawing::Size(55, 55);
                stat->Controls->Add(iconLabel);

                Label^ val = gcnew Label();
                val->Text = values[i];
                val->Font = gcnew Drawing::Font(L"Segoe UI", 26.0F, FontStyle::Bold);
                val->ForeColor = colors[i];
                val->Location = Drawing::Point(70, 12);
                val->AutoSize = true;
                stat->Controls->Add(val);

                Label^ tit = gcnew Label();
                tit->Text = titles[i];
                tit->Font = gcnew Drawing::Font(L"Segoe UI", 9.5F);
                tit->ForeColor = grayColor;
                tit->Location = Drawing::Point(70, 60);
                tit->AutoSize = true;
                stat->Controls->Add(tit);

                this->Controls->Add(stat);
            }

            Label^ lblManage = gcnew Label();
            lblManage->Text = L"Управление системой";
            lblManage->Font = gcnew Drawing::Font(L"Segoe UI", 16.0F, FontStyle::Bold);
            lblManage->ForeColor = darkColor;
            lblManage->Location = Drawing::Point(25, 280);
            lblManage->AutoSize = true;
            this->Controls->Add(lblManage);

            array<String^>^ mTitles = {
                L"👥  Управление пользователями", L"🗄️  Работа с БД", L"🔑  Роли и права",
                L"📋  Журнал действий", L"⚙️  Настройки системы", L"💾  Резервное копирование"
            };
            array<String^>^ mDescs = {
                L"Добавление, редактирование и удаление учетных записей",
                L"Просмотр, редактирование и резервное копирование данных",
                L"Настройка прав доступа для пользователей",
                L"Просмотр логов всех действий в системе",
                L"Общие настройки и параметры системы",
                L"Настройка и управление бэкапами"
            };

            for (int i = 0; i < 6; i++) {
                Panel^ card = gcnew Panel();
                card->Size = Drawing::Size(335, 95);
                card->Location = Drawing::Point(25 + (i % 3) * 350, 315 + (i / 3) * 112);
                card->BackColor = cardColor;
                card->Cursor = Cursors::Hand;
                card->MouseEnter += gcnew EventHandler(this, &MainForm::Card_MouseEnter);
                card->MouseLeave += gcnew EventHandler(this, &MainForm::Card_MouseLeave);

                Label^ cTitle = gcnew Label();
                cTitle->Text = mTitles[i];
                cTitle->Font = gcnew Drawing::Font(L"Segoe UI", 11.5F, FontStyle::Bold);
                cTitle->ForeColor = darkColor;
                cTitle->Location = Drawing::Point(18, 18);
                cTitle->AutoSize = true;
                card->Controls->Add(cTitle);

                Label^ cDesc = gcnew Label();
                cDesc->Text = mDescs[i];
                cDesc->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
                cDesc->ForeColor = grayColor;
                cDesc->Location = Drawing::Point(18, 48);
                cDesc->Size = Drawing::Size(300, 35);
                card->Controls->Add(cDesc);

                if (i == 0) card->Click += gcnew EventHandler(this, &MainForm::ShowUsersTable);

                this->Controls->Add(card);
            }
        }

        void Card_MouseEnter(Object^ sender, EventArgs^ e) {
            Panel^ card = (Panel^)sender;
            card->BackColor = Color::FromArgb(245, 244, 255);
        }

        void Card_MouseLeave(Object^ sender, EventArgs^ e) {
            Panel^ card = (Panel^)sender;
            card->BackColor = cardColor;
        }

        void CreateAdminHeader() {
            Panel^ header = gcnew Panel();
            header->Size = Drawing::Size(1100, 65);
            header->BackColor = cardColor;
            header->Location = Drawing::Point(0, 0);
            this->Controls->Add(header);

            Label^ logo = gcnew Label();
            logo->Text = L"⚡ HR-Auto";
            logo->Font = gcnew Drawing::Font(L"Segoe UI", 18.0F, FontStyle::Bold);
            logo->ForeColor = primaryColor;
            logo->Location = Drawing::Point(25, 18);
            logo->AutoSize = true;
            header->Controls->Add(logo);

            array<String^>^ navs = { L"Главная", L"Пользователи", L"Настройки", L"Отчеты" };
            for (int i = 0; i < 4; i++) {
                Button^ btn = gcnew Button();
                btn->Text = navs[i];
                btn->Location = Drawing::Point(240 + i * 135, 14);
                btn->Size = Drawing::Size(120, 38);
                btn->FlatStyle = FlatStyle::Flat;
                btn->FlatAppearance->BorderSize = 0;
                btn->BackColor = cardColor;
                btn->ForeColor = grayColor;
                btn->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);
                btn->Cursor = Cursors::Hand;
                btn->FlatAppearance->MouseOverBackColor = Color::FromArgb(245, 244, 255);

                if (i == 0) {
                    btn->ForeColor = primaryColor;
                    btn->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
                    btn->Click += gcnew EventHandler(this, &MainForm::BtnHomeClick);
                }
                if (i == 1) btn->Click += gcnew EventHandler(this, &MainForm::ShowUsersTable);
                header->Controls->Add(btn);
            }

            Label^ userName = gcnew Label();
            userName->Text = L"👤 Администратор";
            userName->Font = gcnew Drawing::Font(L"Segoe UI", 9.5F);
            userName->ForeColor = darkColor;
            userName->Location = Drawing::Point(840, 23);
            userName->AutoSize = true;
            header->Controls->Add(userName);

            Button^ btnLogout = CreateButton(L"Выход", 970, 18, 95, 32,
                Color::FromArgb(248, 215, 218), dangerColor);
            btnLogout->Click += gcnew EventHandler(this, &MainForm::BtnLogoutClick);
            header->Controls->Add(btnLogout);
        }

        void CreateEmployeeHeader() {
            Panel^ header = gcnew Panel();
            header->Size = Drawing::Size(1100, 65);
            header->BackColor = cardColor;
            header->Location = Drawing::Point(0, 0);
            this->Controls->Add(header);

            Label^ logo = gcnew Label();
            logo->Text = L"⚡ HR-Auto";
            logo->Font = gcnew Drawing::Font(L"Segoe UI", 18.0F, FontStyle::Bold);
            logo->ForeColor = primaryColor;
            logo->Location = Drawing::Point(25, 18);
            logo->AutoSize = true;
            header->Controls->Add(logo);

            array<String^>^ navs = { L"Главная", L"Расчетные листки", L"Справки" };
            for (int i = 0; i < 3; i++) {
                Button^ btn = gcnew Button();
                btn->Text = navs[i];
                btn->Location = Drawing::Point(240 + i * 160, 14);
                btn->Size = Drawing::Size(140, 38);
                btn->FlatStyle = FlatStyle::Flat;
                btn->FlatAppearance->BorderSize = 0;
                btn->BackColor = cardColor;
                btn->ForeColor = grayColor;
                btn->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);
                btn->Cursor = Cursors::Hand;
                btn->FlatAppearance->MouseOverBackColor = Color::FromArgb(245, 244, 255);

                if (i == 0) {
                    btn->ForeColor = primaryColor;
                    btn->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
                    btn->Click += gcnew EventHandler(this, &MainForm::BtnHomeClick);
                }
                if (i == 1) btn->Click += gcnew EventHandler(this, &MainForm::ShowPayslips);
                header->Controls->Add(btn);
            }

            Label^ userName = gcnew Label();
            userName->Text = L"👤 Козлова Е.Д.";
            userName->Font = gcnew Drawing::Font(L"Segoe UI", 9.5F);
            userName->ForeColor = darkColor;
            userName->Location = Drawing::Point(840, 23);
            userName->AutoSize = true;
            header->Controls->Add(userName);

            Button^ btnLogout = CreateButton(L"Выход", 980, 18, 80, 32,
                Color::FromArgb(248, 215, 218), dangerColor);
            btnLogout->Click += gcnew EventHandler(this, &MainForm::BtnLogoutClick);
            header->Controls->Add(btnLogout);
        }

        // ========== ТАБЛИЦА ПОЛЬЗОВАТЕЛЕЙ ==========
        void ShowUsersTable(Object^ sender, EventArgs^ e) {
            this->Controls->Clear();
            this->BackColor = bgColor;
            CreateAdminHeader();

            Label^ lblTitle = gcnew Label();
            lblTitle->Text = L"Управление пользователями";
            lblTitle->Font = gcnew Drawing::Font(L"Segoe UI", 20.0F, FontStyle::Bold);
            lblTitle->ForeColor = darkColor;
            lblTitle->Location = Drawing::Point(25, 85);
            lblTitle->AutoSize = true;
            this->Controls->Add(lblTitle);

            Label^ lblSub = gcnew Label();
            lblSub->Text = L"Просмотр и редактирование учетных записей";
            lblSub->Font = gcnew Drawing::Font(L"Segoe UI", 11.0F);
            lblSub->ForeColor = grayColor;
            lblSub->Location = Drawing::Point(25, 120);
            lblSub->AutoSize = true;
            this->Controls->Add(lblSub);

            Button^ btnAdd = CreateButton(L"+ Добавить пользователя", 880, 75, 180, 38, primaryColor, Color::White);
            btnAdd->Click += gcnew EventHandler(this, &MainForm::ShowRegister);
            this->Controls->Add(btnAdd);

            dgvUsers = gcnew DataGridView();
            dgvUsers->Location = Drawing::Point(25, 155);
            dgvUsers->Size = Drawing::Size(1050, 470);
            dgvUsers->ReadOnly = true;
            dgvUsers->AllowUserToAddRows = false;
            dgvUsers->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            dgvUsers->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            dgvUsers->BackgroundColor = cardColor;
            dgvUsers->BorderStyle = BorderStyle::None;
            dgvUsers->RowHeadersVisible = false;
            dgvUsers->EnableHeadersVisualStyles = false;
            dgvUsers->ColumnHeadersDefaultCellStyle->BackColor = Color::FromArgb(248, 249, 255);
            dgvUsers->ColumnHeadersDefaultCellStyle->ForeColor = darkColor;
            dgvUsers->ColumnHeadersDefaultCellStyle->Font = gcnew Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
            dgvUsers->ColumnHeadersHeight = 40;
            dgvUsers->RowsDefaultCellStyle->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);
            dgvUsers->RowsDefaultCellStyle->ForeColor = darkColor;
            dgvUsers->RowsDefaultCellStyle->BackColor = cardColor;
            dgvUsers->AlternatingRowsDefaultCellStyle->BackColor = Color::FromArgb(252, 252, 255);
            dgvUsers->RowTemplate->Height = 42;
            dgvUsers->GridColor = Color::FromArgb(240, 242, 255);
            dgvUsers->DefaultCellStyle->SelectionBackColor = Color::FromArgb(232, 230, 255);
            dgvUsers->DefaultCellStyle->SelectionForeColor = darkColor;

            dgvUsers->Columns->Add(L"colID", L"ID");
            dgvUsers->Columns->Add(L"colFIO", L"ФИО");
            dgvUsers->Columns->Add(L"colLogin", L"ЛОГИН");
            dgvUsers->Columns->Add(L"colRole", L"РОЛЬ");
            dgvUsers->Columns->Add(L"colStatus", L"СТАТУС");
            dgvUsers->Columns->Add(L"colActions", L"ДЕЙСТВИЯ");

            for each (User ^ user in Database::Users) {
                String^ statusIcon = user->Status == L"Активен" ? L"🟢 " : L"🔴 ";
                dgvUsers->Rows->Add(user->Id, user->FullName, user->Login,
                    user->Role, statusIcon + user->Status, L"✏️  🗑️");
            }

            this->Controls->Add(dgvUsers);

            Panel^ infoBar = gcnew Panel();
            infoBar->Location = Drawing::Point(25, 640);
            infoBar->Size = Drawing::Size(1050, 35);
            infoBar->BackColor = Color::FromArgb(232, 244, 253);

            Label^ lblInfo = gcnew Label();
            lblInfo->Text = L"📊 База данных: HR-Auto | Последнее резервное копирование: 27.04.2026 23:00";
            lblInfo->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
            lblInfo->ForeColor = Color::FromArgb(12, 84, 96);
            lblInfo->Location = Drawing::Point(15, 8);
            lblInfo->AutoSize = true;
            infoBar->Controls->Add(lblInfo);

            this->Controls->Add(infoBar);
        }



        // ========== ЛИЧНЫЙ КАБИНЕТ ==========
        void ShowEmployeeDashboard() {
            this->Controls->Clear();
            this->BackColor = bgColor;
            CreateEmployeeHeader();

            Panel^ profileCard = gcnew Panel();
            profileCard->Size = Drawing::Size(1050, 130);
            profileCard->Location = Drawing::Point(25, 85);
            profileCard->BackColor = cardColor;
            this->Controls->Add(profileCard);

            Label^ avatar = gcnew Label();
            avatar->Text = L"👤";
            avatar->Font = gcnew Drawing::Font(L"Segoe UI", 30.0F);
            avatar->Location = Drawing::Point(25, 25);
            avatar->Size = Drawing::Size(55, 55);
            profileCard->Controls->Add(avatar);

            Label^ lblName = gcnew Label();
            lblName->Text = Database::CurrentUser->FullName;
            lblName->Font = gcnew Drawing::Font(L"Segoe UI", 18.0F, FontStyle::Bold);
            lblName->ForeColor = darkColor;
            lblName->Location = Drawing::Point(95, 25);
            lblName->AutoSize = true;
            profileCard->Controls->Add(lblName);

            Label^ lblPosition = gcnew Label();
            lblPosition->Text = L"Менеджер по продажам | Табельный номер: 042";
            lblPosition->Font = gcnew Drawing::Font(L"Segoe UI", 10.5F);
            lblPosition->ForeColor = grayColor;
            lblPosition->Location = Drawing::Point(95, 60);
            lblPosition->AutoSize = true;
            profileCard->Controls->Add(lblPosition);

            Label^ lblDate = gcnew Label();
            lblDate->Text = L"Принят: 15.03.2024";
            lblDate->Font = gcnew Drawing::Font(L"Segoe UI", 9.5F);
            lblDate->ForeColor = grayColor;
            lblDate->Location = Drawing::Point(95, 85);
            lblDate->AutoSize = true;
            profileCard->Controls->Add(lblDate);

            array<String^>^ iTitles = { L"Должность", L"Дата приема", L"Оклад" };
            array<String^>^ iValues = { L"Менеджер по продажам", L"15.03.2024", L"55 000 ₽" };

            for (int i = 0; i < 3; i++) {
                Panel^ card = gcnew Panel();
                card->Size = Drawing::Size(252, 95);
                card->Location = Drawing::Point(25 + i * 265, 240);
                card->BackColor = cardColor;

                Label^ tit = gcnew Label();
                tit->Text = iTitles[i];
                tit->Font = gcnew Drawing::Font(L"Segoe UI", 9.5F);
                tit->ForeColor = grayColor;
                tit->Location = Drawing::Point(18, 18);
                tit->AutoSize = true;
                card->Controls->Add(tit);

                Label^ val = gcnew Label();
                val->Text = iValues[i];
                val->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
                val->ForeColor = primaryColor;
                val->Location = Drawing::Point(18, 48);
                val->AutoSize = true;
                card->Controls->Add(val);

                this->Controls->Add(card);
            }

            Label^ lblActions = gcnew Label();
            lblActions->Text = L"Доступные действия";
            lblActions->Font = gcnew Drawing::Font(L"Segoe UI", 16.0F, FontStyle::Bold);
            lblActions->ForeColor = darkColor;
            lblActions->Location = Drawing::Point(25, 360);
            lblActions->AutoSize = true;
            this->Controls->Add(lblActions);

            Panel^ pCard = gcnew Panel();
            pCard->Size = Drawing::Size(510, 80);
            pCard->Location = Drawing::Point(25, 400);
            pCard->BackColor = cardColor;
            pCard->Cursor = Cursors::Hand;
            pCard->Click += gcnew EventHandler(this, &MainForm::ShowPayslips);
            pCard->MouseEnter += gcnew EventHandler(this, &MainForm::Card_MouseEnter);
            pCard->MouseLeave += gcnew EventHandler(this, &MainForm::Card_MouseLeave);

            Label^ pIcon = gcnew Label();
            pIcon->Text = L"📄";
            pIcon->Font = gcnew Drawing::Font(L"Segoe UI", 15.0F);
            pIcon->Location = Drawing::Point(22, 22);
            pIcon->AutoSize = true;
            pCard->Controls->Add(pIcon);

            Label^ pTitle = gcnew Label();
            pTitle->Text = L"Расчетные листки";
            pTitle->Font = gcnew Drawing::Font(L"Segoe UI", 13.0F, FontStyle::Bold);
            pTitle->ForeColor = darkColor;
            pTitle->Location = Drawing::Point(60, 15);
            pTitle->AutoSize = true;
            pCard->Controls->Add(pTitle);

            Label^ pDesc = gcnew Label();
            pDesc->Text = L"Просмотр и скачивание расчетных листков за все периоды";
            pDesc->Font = gcnew Drawing::Font(L"Segoe UI", 9.5F);
            pDesc->ForeColor = grayColor;
            pDesc->Location = Drawing::Point(60, 42);
            pDesc->AutoSize = true;
            pCard->Controls->Add(pDesc);
            this->Controls->Add(pCard);

            Panel^ dCard = gcnew Panel();
            dCard->Size = Drawing::Size(510, 80);
            dCard->Location = Drawing::Point(550, 400);
            dCard->BackColor = cardColor;
            dCard->MouseEnter += gcnew EventHandler(this, &MainForm::Card_MouseEnter);
            dCard->MouseLeave += gcnew EventHandler(this, &MainForm::Card_MouseLeave);

            Label^ dIcon = gcnew Label();
            dIcon->Text = L"📋";
            dIcon->Font = gcnew Drawing::Font(L"Segoe UI", 15.0F);
            dIcon->Location = Drawing::Point(22, 22);
            dIcon->AutoSize = true;
            dCard->Controls->Add(dIcon);

            Label^ dTitle = gcnew Label();
            dTitle->Text = L"Запрос справки";
            dTitle->Font = gcnew Drawing::Font(L"Segoe UI", 13.0F, FontStyle::Bold);
            dTitle->ForeColor = darkColor;
            dTitle->Location = Drawing::Point(60, 15);
            dTitle->AutoSize = true;
            dCard->Controls->Add(dTitle);

            Label^ dDesc = gcnew Label();
            dDesc->Text = L"Формирование и отправка запроса на получение справки";
            dDesc->Font = gcnew Drawing::Font(L"Segoe UI", 9.5F);
            dDesc->ForeColor = grayColor;
            dDesc->Location = Drawing::Point(60, 42);
            dDesc->AutoSize = true;
            dCard->Controls->Add(dDesc);
            this->Controls->Add(dCard);
        }

        // ========== РАСЧЕТНЫЕ ЛИСТКИ ==========
        void ShowPayslips(Object^ sender, EventArgs^ e) {
            this->Controls->Clear();
            this->BackColor = bgColor;
            CreateEmployeeHeader();

            Label^ lblTitle = gcnew Label();
            lblTitle->Text = L"Мои расчетные листки";
            lblTitle->Font = gcnew Drawing::Font(L"Segoe UI", 20.0F, FontStyle::Bold);
            lblTitle->ForeColor = darkColor;
            lblTitle->Location = Drawing::Point(25, 85);
            lblTitle->AutoSize = true;
            this->Controls->Add(lblTitle);

            Label^ lblSub = gcnew Label();
            lblSub->Text = L"Просмотр и скачивание расчетных листков";
            lblSub->Font = gcnew Drawing::Font(L"Segoe UI", 11.0F);
            lblSub->ForeColor = grayColor;
            lblSub->Location = Drawing::Point(30, 123);
            lblSub->AutoSize = true;
            this->Controls->Add(lblSub);

            ComboBox^ cmbYear = gcnew ComboBox();
            cmbYear->Location = Drawing::Point(920, 85);
            cmbYear->Size = Drawing::Size(155, 35);
            cmbYear->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);
            cmbYear->DropDownStyle = ComboBoxStyle::DropDownList;
            cmbYear->Items->Add(L"2024");
            cmbYear->Items->Add(L"2025");
            cmbYear->Items->Add(L"2026");
            cmbYear->SelectedIndex = 2;
            this->Controls->Add(cmbYear);

            dgvPayslips = gcnew DataGridView();
            dgvPayslips->Location = Drawing::Point(25, 150);
            dgvPayslips->Size = Drawing::Size(1050, 430);
            dgvPayslips->ReadOnly = true;
            dgvPayslips->AllowUserToAddRows = false;
            dgvPayslips->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            dgvPayslips->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            dgvPayslips->BackgroundColor = cardColor;
            dgvPayslips->BorderStyle = BorderStyle::None;
            dgvPayslips->RowHeadersVisible = false;
            dgvPayslips->EnableHeadersVisualStyles = false;
            dgvPayslips->ColumnHeadersDefaultCellStyle->BackColor = Color::FromArgb(248, 249, 255);
            dgvPayslips->ColumnHeadersDefaultCellStyle->ForeColor = darkColor;
            dgvPayslips->ColumnHeadersDefaultCellStyle->Font = gcnew Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
            dgvPayslips->ColumnHeadersHeight = 40;
            dgvPayslips->RowsDefaultCellStyle->Font = gcnew Drawing::Font(L"Segoe UI", 10.5F);
            dgvPayslips->RowsDefaultCellStyle->ForeColor = darkColor;
            dgvPayslips->RowsDefaultCellStyle->BackColor = cardColor;
            dgvPayslips->AlternatingRowsDefaultCellStyle->BackColor = Color::FromArgb(252, 252, 255);
            dgvPayslips->RowTemplate->Height = 45;
            dgvPayslips->GridColor = Color::FromArgb(240, 242, 255);
            dgvPayslips->DefaultCellStyle->SelectionBackColor = Color::FromArgb(232, 230, 255);
            dgvPayslips->DefaultCellStyle->SelectionForeColor = darkColor;

            dgvPayslips->Columns->Add(L"colPeriod", L"ПЕРИОД");
            dgvPayslips->Columns->Add(L"colAccrued", L"НАЧИСЛЕНО");
            dgvPayslips->Columns->Add(L"colDeducted", L"УДЕРЖАНО");
            dgvPayslips->Columns->Add(L"colToPay", L"К ВЫПЛАТЕ");
            dgvPayslips->Columns->Add(L"colStatus", L"СТАТУС");
            dgvPayslips->Columns->Add(L"colActions", L"ДЕЙСТВИЯ");

            for each (Payslip ^ p in Database::Payslips) {
                dgvPayslips->Rows->Add(p->Period, p->Accrued + L" ₽",
                    p->Deducted + L" ₽", p->ToPay + L" ₽",
                    p->Status, L"📥 Скачать");
            }

            this->Controls->Add(dgvPayslips);

            Panel^ infoBar = gcnew Panel();
            infoBar->Location = Drawing::Point(25, 595);
            infoBar->Size = Drawing::Size(1050, 35);
            infoBar->BackColor = Color::FromArgb(232, 244, 253);

            Label^ lblInfo = gcnew Label();
            lblInfo->Text = L"📋 Для подтверждения ознакомления с расчетным листком нажмите кнопку \"Подтвердить\" в строке листка";
            lblInfo->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
            lblInfo->ForeColor = Color::FromArgb(12, 84, 96);
            lblInfo->Location = Drawing::Point(15, 8);
            lblInfo->AutoSize = true;
            infoBar->Controls->Add(lblInfo);

            this->Controls->Add(infoBar);
        }

        // ========== ОБРАБОТЧИКИ ==========
        void OnPlaceholderEnter(Object^ sender, EventArgs^ e) {
            TextBox^ txt = (TextBox^)sender;
            if (txt->ForeColor == grayColor) {
                txt->Text = L"";
                txt->ForeColor = darkColor;
            }
        }

        void OnPlaceholderLeave(Object^ sender, EventArgs^ e) {
            TextBox^ txt = (TextBox^)sender;
            if (String::IsNullOrWhiteSpace(txt->Text)) {
                if (txt == txtLogin) txt->Text = L"Введите ваш логин";
                else if (txt == txtRegLogin) txt->Text = L"Введите логин";
                else if (txt == txtRegPassword) {
                    txt->Text = L"Введите пароль";
                    txt->PasswordChar = '\0';
                }
                else if (txt == txtRegFullName) txt->Text = L"Иванов Иван Иванович";
                else if (txt == txtRegEmail) txt->Text = L"ivanov@example.com";
                txt->ForeColor = grayColor;
            }
        }

        void OnPassEnter(Object^ sender, EventArgs^ e) {
            if (txtPassword->ForeColor == grayColor) {
                txtPassword->Text = L"";
                txtPassword->ForeColor = darkColor;
                txtPassword->PasswordChar = '*';
            }
        }

        void OnPassLeave(Object^ sender, EventArgs^ e) {
            if (String::IsNullOrWhiteSpace(txtPassword->Text)) {
                txtPassword->Text = L"Введите ваш пароль";
                txtPassword->ForeColor = grayColor;
                txtPassword->PasswordChar = '\0';
            }
        }

        void BtnLoginClick(Object^ sender, EventArgs^ e) {
            String^ login = txtLogin->Text;
            String^ pass = txtPassword->Text;
            if (login == L"Введите ваш логин") login = L"";
            if (pass == L"Введите ваш пароль") pass = L"";

            if (String::IsNullOrWhiteSpace(login) || String::IsNullOrWhiteSpace(pass)) {
                MessageBox::Show(L"Пожалуйста, заполните все поля!", L"Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            User^ user = Database::Authenticate(login, pass);
            if (user != nullptr) {
                Database::CurrentUser = user;
                if (user->Role == L"Администратор") {
                    ShowAdminDashboard();
                }
                else if (user->Role == L"Кадровик") {
                    ShowHRDashboard();
                }
                else if (user->Role == L"Бухгалтер") {
                    ShowBuhDashboard();
                }
                else if (user->Role == L"Сотрудник") {
                    ShowEmployeeDashboard();
                }
            }
            else {
                MessageBox::Show(L"Неверный логин или пароль!", L"Ошибка входа",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void BtnRegisterClick(Object^ sender, EventArgs^ e) {
            // Проверяем, что текстовые поля существуют
            if (txtRegFullName == nullptr || txtRegEmail == nullptr ||
                txtRegLogin == nullptr || txtRegPassword == nullptr) {
                MessageBox::Show(L"Ошибка инициализации формы!", L"Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            // Проверка заполнения полей
            if (String::IsNullOrWhiteSpace(txtRegFullName->Text) ||
                txtRegFullName->ForeColor == grayColor) {
                MessageBox::Show(L"Пожалуйста, укажите ФИО!", L"Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                txtRegFullName->Focus();
                return;
            }

            if (String::IsNullOrWhiteSpace(txtRegEmail->Text) ||
                txtRegEmail->ForeColor == grayColor) {
                MessageBox::Show(L"Пожалуйста, укажите Email!", L"Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                txtRegEmail->Focus();
                return;
            }

            // Простая проверка email
            String^ email = txtRegEmail->Text->Trim();
            if (!email->Contains(L"@") || !email->Contains(L".")) {
                MessageBox::Show(L"Пожалуйста, укажите корректный Email!\n\nПример: user@company.ru",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                txtRegEmail->Focus();
                return;
            }

            if (String::IsNullOrWhiteSpace(txtRegLogin->Text) ||
                txtRegLogin->ForeColor == grayColor) {
                MessageBox::Show(L"Пожалуйста, укажите логин!", L"Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                txtRegLogin->Focus();
                return;
            }

            if (txtRegLogin->Text->Length < 3) {
                MessageBox::Show(L"Логин должен содержать минимум 3 символа!", L"Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                txtRegLogin->Focus();
                return;
            }

            if (String::IsNullOrWhiteSpace(txtRegPassword->Text) ||
                txtRegPassword->ForeColor == grayColor) {
                MessageBox::Show(L"Пожалуйста, укажите пароль!", L"Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                txtRegPassword->Focus();
                return;
            }

            if (txtRegPassword->Text->Length < 4) {
                MessageBox::Show(L"Пароль должен содержать минимум 4 символа!", L"Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                txtRegPassword->Focus();
                return;
            }

            // Проверка уникальности логина
            for each (User ^ user in Database::Users) {
                if (user->Login == txtRegLogin->Text) {
                    MessageBox::Show(L"Пользователь с таким логином уже существует!\nПожалуйста, выберите другой логин.",
                        L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    txtRegLogin->Focus();
                    txtRegLogin->SelectAll();
                    return;
                }
            }

            User^ newUser = gcnew User();
            newUser->Id = Database::Users->Count + 1;
            newUser->FullName = txtRegFullName->Text->Trim();
            newUser->Login = txtRegLogin->Text->Trim();
            newUser->Password = txtRegPassword->Text;
            newUser->Role = cmbRole->SelectedItem->ToString();
            newUser->Status = L"Активен";
            Database::Users->Add(newUser);

            MessageBox::Show(L"Регистрация успешна!\n\nЛогин: " + newUser->Login +
                L"\nРоль: " + newUser->Role + L"\n\nТеперь вы можете войти в систему.",
                L"Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
            ShowLogin();
        }

        void BtnLogoutClick(Object^ sender, EventArgs^ e) {
            Database::CurrentUser = nullptr;
            ShowLogin();
        }

        void BtnHomeClick(Object^ sender, EventArgs^ e) {
            if (Database::CurrentUser != nullptr) {
                if (Database::CurrentUser->Role == L"Администратор" ||
                    Database::CurrentUser->Role == L"Кадровик" ||
                    Database::CurrentUser->Role == L"Бухгалтер")
                    ShowAdminDashboard();
                else ShowEmployeeDashboard();
            }
        }

        void LinkForgotClick(Object^ sender, EventArgs^ e) {
            MessageBox::Show(L"Для восстановления пароля обратитесь к администратору системы.\nEmail: admin@hr-auto.ru",
                L"Восстановление пароля");
        }

        void LinkBackClick(Object^ sender, EventArgs^ e) {
            ShowLogin();
        }
        // ========== ЭКРАН КАДРОВИКА ==========
        void ShowHRDashboard() {
            this->Controls->Clear();
            this->BackColor = bgColor;
            CreateHRHeader();

            Label^ lblWelcome = gcnew Label();
            lblWelcome->Text = L"Добро пожаловать, " + Database::CurrentUser->FullName + L"!";
            lblWelcome->Font = gcnew Drawing::Font(L"Segoe UI", 20.0F, FontStyle::Bold);
            lblWelcome->ForeColor = darkColor;
            lblWelcome->Location = Drawing::Point(25, 85);
            lblWelcome->AutoSize = true;
            this->Controls->Add(lblWelcome);

            Label^ lblSub = gcnew Label();
            lblSub->Text = L"Отдел кадров - управление персоналом";
            lblSub->Font = gcnew Drawing::Font(L"Segoe UI", 11.0F);
            lblSub->ForeColor = grayColor;
            lblSub->Location = Drawing::Point(25, 118);
            lblSub->AutoSize = true;
            this->Controls->Add(lblSub);

            // Карточки статистики
            array<String^>^ titles = { L"Всего сотрудников", L"Работают", L"В отпуске", L"На больничном" };
            array<String^>^ values = { L"156", L"142", L"8", L"6" };
            array<String^>^ icons = { L"👥", L"✅", L"🏖️", L"🏥" };
            array<Color>^ colors = { primaryColor, successColor, warningColor, Color::FromArgb(220, 53, 69) };

            for (int i = 0; i < 4; i++) {
                Panel^ stat = gcnew Panel();
                stat->Size = Drawing::Size(252, 100);
                stat->Location = Drawing::Point(25 + i * 265, 155);
                stat->BackColor = cardColor;

                Label^ iconLabel = gcnew Label();
                iconLabel->Text = icons[i];
                iconLabel->Font = gcnew Drawing::Font(L"Segoe UI", 23.0F);
                iconLabel->Location = Drawing::Point(15, 15);
                iconLabel->Size = Drawing::Size(45, 45);
                stat->Controls->Add(iconLabel);

                Label^ val = gcnew Label();
                val->Text = values[i];
                val->Font = gcnew Drawing::Font(L"Segoe UI", 26.0F, FontStyle::Bold);
                val->ForeColor = colors[i];
                val->Location = Drawing::Point(70, 12);
                val->AutoSize = true;
                stat->Controls->Add(val);

                Label^ tit = gcnew Label();
                tit->Text = titles[i];
                tit->Font = gcnew Drawing::Font(L"Segoe UI", 9.5F);
                tit->ForeColor = grayColor;
                tit->Location = Drawing::Point(70, 57);
                tit->AutoSize = true;
                stat->Controls->Add(tit);

                this->Controls->Add(stat);
            }

            // Функциональные блоки
            Label^ lblFunctions = gcnew Label();
            lblFunctions->Text = L"Кадровые операции";
            lblFunctions->Font = gcnew Drawing::Font(L"Segoe UI", 16.0F, FontStyle::Bold);
            lblFunctions->ForeColor = darkColor;
            lblFunctions->Location = Drawing::Point(25, 280);
            lblFunctions->AutoSize = true;
            this->Controls->Add(lblFunctions);

            array<String^>^ fTitles = {
                L"📝  Прием сотрудника", L"📄  Увольнение",
                L"📁  Личные дела", L"⏰  Табель учета",
                L"📅  Отпуска", L"📑  Справки"
            };
            array<String^>^ fDescs = {
                L"Оформление нового сотрудника и создание приказа",
                L"Оформление увольнения и расчет компенсации",
                L"Просмотр и редактирование личных дел",
                L"Учет рабочего времени и больничных",
                L"Оформление и учет отпусков сотрудников",
                L"Формирование справок для сотрудников"
            };

            for (int i = 0; i < 6; i++) {
                Panel^ card = gcnew Panel();
                card->Size = Drawing::Size(335, 95);
                card->Location = Drawing::Point(25 + (i % 3) * 350, 315 + (i / 3) * 112);
                card->BackColor = cardColor;
                card->Cursor = Cursors::Hand;
                card->MouseEnter += gcnew EventHandler(this, &MainForm::Card_MouseEnter);
                card->MouseLeave += gcnew EventHandler(this, &MainForm::Card_MouseLeave);

                Label^ cTitle = gcnew Label();
                cTitle->Text = fTitles[i];
                cTitle->Font = gcnew Drawing::Font(L"Segoe UI", 11.5F, FontStyle::Bold);
                cTitle->ForeColor = darkColor;
                cTitle->Location = Drawing::Point(18, 18);
                cTitle->AutoSize = true;
                card->Controls->Add(cTitle);

                Label^ cDesc = gcnew Label();
                cDesc->Text = fDescs[i]; cDesc->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
                cDesc->ForeColor = grayColor;
                cDesc->Location = Drawing::Point(18, 48);
                cDesc->Size = Drawing::Size(300, 35);
                card->Controls->Add(cDesc);

                int index = i;
                card->Click += gcnew EventHandler(this, &MainForm::HRCardClick);

                this->Controls->Add(card);
            }
        }

        void HRCardClick(Object^ sender, EventArgs^ e) {
            Panel^ card = (Panel^)sender;
            Label^ title = (Label^)card->Controls[0];

            if (title->Text->Contains(L"Прием")) {
                ShowEmployeeForm(L"Прием сотрудника");
            }
            else if (title->Text->Contains(L"Увольнение")) {
                ShowEmployeeForm(L"Увольнение сотрудника");
            }
            else if (title->Text->Contains(L"Личные дела")) {
                ShowPersonalFiles();
            }
            else if (title->Text->Contains(L"Табель")) {
                ShowTimeTracker();
            }
            else {
                MessageBox::Show(L"Раздел в разработке", L"Информация");
            }
        }

        void ShowEmployeeForm(String^ title) {
            this->Controls->Clear();
            this->BackColor = bgColor;
            CreateHRHeader();

            Label^ lblTitle = gcnew Label();
            lblTitle->Text = title;
            lblTitle->Font = gcnew Drawing::Font(L"Segoe UI", 20.0F, FontStyle::Bold);
            lblTitle->ForeColor = darkColor;
            lblTitle->Location = Drawing::Point(25, 85);
            lblTitle->AutoSize = true;
            this->Controls->Add(lblTitle);

            Panel^ form = gcnew Panel();
            form->Size = Drawing::Size(800, 400);
            form->Location = Drawing::Point(150, 140);
            form->BackColor = cardColor;
            this->Controls->Add(form);

            Label^ lblFIO = gcnew Label();
            lblFIO->Text = L"ФИО сотрудника";
            lblFIO->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
            lblFIO->ForeColor = darkColor;
            lblFIO->Location = Drawing::Point(40, 30);
            lblFIO->AutoSize = true;
            form->Controls->Add(lblFIO);

            TextBox^ txtFIO = gcnew TextBox();
            txtFIO->Location = Drawing::Point(40, 55);
            txtFIO->Size = Drawing::Size(350, 35);
            txtFIO->Font = gcnew Drawing::Font(L"Segoe UI", 10.5F);
            txtFIO->Text = L"Иванов Иван Иванович";
            form->Controls->Add(txtFIO);

            Label^ lblPos = gcnew Label();
            lblPos->Text = L"Должность";
            lblPos->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
            lblPos->ForeColor = darkColor;
            lblPos->Location = Drawing::Point(420, 30);
            lblPos->AutoSize = true;
            form->Controls->Add(lblPos);

            ComboBox^ cmbPos = gcnew ComboBox();
            cmbPos->Location = Drawing::Point(420, 55);
            cmbPos->Size = Drawing::Size(340, 35);
            cmbPos->Font = gcnew Drawing::Font(L"Segoe UI", 10.5F);
            cmbPos->Items->Add(L"Менеджер");
            cmbPos->Items->Add(L"Разработчик");
            cmbPos->Items->Add(L"Бухгалтер");
            cmbPos->Items->Add(L"HR-менеджер");
            cmbPos->Items->Add(L"Аналитик");
            cmbPos->SelectedIndex = 0;
            form->Controls->Add(cmbPos);

            Label^ lblDep = gcnew Label();
            lblDep->Text = L"Отдел";
            lblDep->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
            lblDep->ForeColor = darkColor;
            lblDep->Location = Drawing::Point(40, 105);
            lblDep->AutoSize = true;
            form->Controls->Add(lblDep);

            ComboBox^ cmbDep = gcnew ComboBox();
            cmbDep->Location = Drawing::Point(40, 130);
            cmbDep->Size = Drawing::Size(350, 35);
            cmbDep->Font = gcnew Drawing::Font(L"Segoe UI", 10.5F);
            cmbDep->Items->Add(L"IT");
            cmbDep->Items->Add(L"Продажи");
            cmbDep->Items->Add(L"Бухгалтерия");
            cmbDep->Items->Add(L"Кадры");
            cmbDep->Items->Add(L"Маркетинг");
            cmbDep->SelectedIndex = 0;
            form->Controls->Add(cmbDep);

            Label^ lblDate = gcnew Label();
            lblDate->Text = L"Дата " + (title->Contains(L"Прием") ? L"приема" : L"увольнения");
            lblDate->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
            lblDate->ForeColor = darkColor;
            lblDate->Location = Drawing::Point(420, 105);
            lblDate->AutoSize = true;
            form->Controls->Add(lblDate);

            DateTimePicker^ dtpDate = gcnew DateTimePicker();
            dtpDate->Location = Drawing::Point(420, 130);
            dtpDate->Size = Drawing::Size(340, 35);
            dtpDate->Font = gcnew Drawing::Font(L"Segoe UI", 10.5F);
            dtpDate->Format = DateTimePickerFormat::Short;
            dtpDate->Value = DateTime::Now;
            form->Controls->Add(dtpDate);

            if (title->Contains(L"Прием")) {
                Label^ lblSalary = gcnew Label();
                lblSalary->Text = L"Оклад (руб.)";
                lblSalary->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
                lblSalary->ForeColor = darkColor;
                lblSalary->Location = Drawing::Point(40, 180);
                lblSalary->AutoSize = true;
                form->Controls->Add(lblSalary);

                NumericUpDown^ numSalary = gcnew NumericUpDown();
                numSalary->Location = Drawing::Point(40, 205);
                numSalary->Size = Drawing::Size(350, 35);
                numSalary->Font = gcnew Drawing::Font(L"Segoe UI", 10.5F);
                numSalary->Minimum = 20000;
                numSalary->Maximum = 500000;
                numSalary->Value = 50000;
                numSalary->ThousandsSeparator = true;
                numSalary->Increment = 5000;
                form->Controls->Add(numSalary);

                Button^ btnSave = CreateButton(L"Оформить прием", 40, 280, 200, 42, successColor, Color::White);
                btnSave->Click += gcnew EventHandler(this, &MainForm::BtnHRSaveClick);
                form->Controls->Add(btnSave);
            }
            else {
                Label^ lblReason = gcnew Label();
                lblReason->Text = L"Причина увольнения";
                lblReason->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
                lblReason->ForeColor = darkColor;
                lblReason->Location = Drawing::Point(40, 180);
                lblReason->AutoSize = true;
                form->Controls->Add(lblReason);

                TextBox^ txtReason = gcnew TextBox();
                txtReason->Location = Drawing::Point(40, 205);
                txtReason->Size = Drawing::Size(720, 70);
                txtReason->Font = gcnew Drawing::Font(L"Segoe UI", 10.5F);
                txtReason->Multiline = true;
                txtReason->Text = L"По собственному желанию";
                form->Controls->Add(txtReason);

                Button^ btnSave = CreateButton(L"Оформить увольнение", 40, 300, 200, 42, dangerColor, Color::White);
                btnSave->Click += gcnew EventHandler(this, &MainForm::BtnHRSaveClick);
                form->Controls->Add(btnSave);
            }

            Button^ btnBack = CreateButton(L"Назад", 260, title->Contains(L"Прием") ? 280 : 300, 200, 42, grayColor, Color::White);
            btnBack->Click += gcnew EventHandler(this, &MainForm::BtnBackToHRClick);
            form->Controls->Add(btnBack);
        }

        void ShowPersonalFiles() {
            this->Controls->Clear();
            this->BackColor = bgColor;
            CreateHRHeader();

            Label^ lblTitle = gcnew Label();
            lblTitle->Text = L"Личные дела сотрудников";
            lblTitle->Font = gcnew Drawing::Font(L"Segoe UI", 20.0F, FontStyle::Bold);
            lblTitle->ForeColor = darkColor;
            lblTitle->Location = Drawing::Point(25, 85);
            lblTitle->AutoSize = true;
            this->Controls->Add(lblTitle);

            DataGridView^ dgv = gcnew DataGridView();
            dgv->Location = Drawing::Point(25, 140);
            dgv->Size = Drawing::Size(1050, 500);
            dgv->ReadOnly = true;
            dgv->AllowUserToAddRows = false;
            dgv->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            dgv->BackgroundColor = cardColor;
            dgv->BorderStyle = BorderStyle::None;
            dgv->RowHeadersVisible = false;
            dgv->EnableHeadersVisualStyles = false;
            dgv->ColumnHeadersDefaultCellStyle->BackColor = Color::FromArgb(248, 249, 255);
            dgv->ColumnHeadersDefaultCellStyle->ForeColor = darkColor;
            dgv->ColumnHeadersDefaultCellStyle->Font = gcnew Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
            dgv->ColumnHeadersHeight = 40;
            dgv->RowTemplate->Height = 40;

            dgv->Columns->Add(L"colID", L"ID");
            dgv->Columns->Add(L"colFIO", L"ФИО");
            dgv->Columns->Add(L"colPos", L"ДОЛЖНОСТЬ");
            dgv->Columns->Add(L"colDep", L"ОТДЕЛ");
            dgv->Columns->Add(L"colDate", L"ДАТА ПРИЕМА");
            dgv->Columns->Add(L"colStatus", L"СТАТУС");

            dgv->Rows->Add(1, L"Иванов И.И.", L"Директор", L"Администрация", L"01.01.2024", L"Работает");
            dgv->Rows->Add(2, L"Петрова М.С.", L"HR-менеджер", L"Кадры", L"15.01.2024", L"Работает");
            dgv->Rows->Add(3, L"Сидоров А.В.", L"Бухгалтер", L"Бухгалтерия", L"01.02.2024", L"Работает");
            dgv->Rows->Add(4, L"Козлова Е.Д.", L"Менеджер", L"Продажи", L"15.03.2024", L"Работает");
            dgv->Rows->Add(5, L"Новиков П.С.", L"Разработчик", L"IT", L"01.04.2024", L"Отпуск");

            this->Controls->Add(dgv);

            Button^ btnBack = CreateButton(L"← Назад", 25, 660, 150, 38, primaryColor, Color::White);
            btnBack->Click += gcnew EventHandler(this, &MainForm::BtnBackToHRClick);
            this->Controls->Add(btnBack);
        }

        void ShowTimeTracker() {
            this->Controls->Clear();
            this->BackColor = bgColor;
            CreateHRHeader();

            Label^ lblTitle = gcnew Label();
            lblTitle->Text = L"Табель учета рабочего времени";
            lblTitle->Font = gcnew Drawing::Font(L"Segoe UI", 20.0F, FontStyle::Bold);
            lblTitle->ForeColor = darkColor;
            lblTitle->Location = Drawing::Point(25, 85);
            lblTitle->AutoSize = true;
            this->Controls->Add(lblTitle);

            Label^ lblSub = gcnew Label();
            lblSub->Text = L"Апрель 2026";
            lblSub->Font = gcnew Drawing::Font(L"Segoe UI", 14.0F, FontStyle::Bold);
            lblSub->ForeColor = primaryColor;
            lblSub->Location = Drawing::Point(25, 120);
            lblSub->AutoSize = true;
            this->Controls->Add(lblSub);

            DataGridView^ dgv = gcnew DataGridView();
            dgv->Location = Drawing::Point(25, 160);
            dgv->Size = Drawing::Size(1050, 450);
            dgv->AllowUserToAddRows = false;
            dgv->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            dgv->BackgroundColor = cardColor;
            dgv->BorderStyle = BorderStyle::None;
            dgv->RowHeadersVisible = false;
            dgv->EnableHeadersVisualStyles = false;
            dgv->ColumnHeadersDefaultCellStyle->BackColor = Color::FromArgb(248, 249, 255);
            dgv->ColumnHeadersDefaultCellStyle->ForeColor = darkColor;
            dgv->ColumnHeadersDefaultCellStyle->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F, FontStyle::Bold);
            dgv->ColumnHeadersHeight = 40;
            dgv->RowTemplate->Height = 35;

            dgv->Columns->Add(L"colFIO", L"СОТРУДНИК");
            dgv->Columns->Add(L"colDays", L"ОТРАБОТАНО ДНЕЙ");
            dgv->Columns->Add(L"colSick", L"БОЛЬНИЧНЫХ");
            dgv->Columns->Add(L"colVac", L"ОТПУСК");
            dgv->Columns->Add(L"colOver", L"ПЕРЕРАБОТКИ");

            dgv->Rows->Add(L"Иванов И.И.", L"22", L"0", L"0", L"0");
            dgv->Rows->Add(L"Петрова М.С.", L"20", L"0", L"0", L"2");
            dgv->Rows->Add(L"Сидоров А.В.", L"22", L"0", L"0", L"0");
            dgv->Rows->Add(L"Козлова Е.Д.", L"18", L"2", L"0", L"0");
            dgv->Rows->Add(L"Новиков П.С.", L"0", L"0", L"14", L"0");

            this->Controls->Add(dgv);

            Button^ btnBack = CreateButton(L"← Назад", 25, 630, 150, 38, primaryColor, Color::White);
            btnBack->Click += gcnew EventHandler(this, &MainForm::BtnBackToHRClick);
            this->Controls->Add(btnBack);
        }

        void CreateHRHeader() {
            Panel^ header = gcnew Panel();
            header->Size = Drawing::Size(1100, 65);
            header->BackColor = cardColor;
            header->Location = Drawing::Point(0, 0);
            this->Controls->Add(header);

            Label^ logo = gcnew Label();
            logo->Text = L"⚡ HR-Auto | Кадровый учет";
            logo->Font = gcnew Drawing::Font(L"Segoe UI", 16.0F, FontStyle::Bold);
            logo->ForeColor = primaryColor;
            logo->Location = Drawing::Point(25, 18);
            logo->AutoSize = true;
            header->Controls->Add(logo);

            array<String^>^ navs = { L"Главная", L"Прием", L"Увольнение", L"Личные дела"};
            for (int i = 0; i < 4; i++) {
                Button^ btn = gcnew Button();
                btn->Text = navs[i];
                btn->Location = Drawing::Point(380 + i * 130, 14);
                btn->Size = Drawing::Size(110, 38);
                btn->FlatStyle = FlatStyle::Flat;
                btn->FlatAppearance->BorderSize = 0;
                btn->BackColor = cardColor;
                btn->ForeColor = grayColor;
                btn->Font = gcnew Drawing::Font(L"Segoe UI", 9.5F);
                btn->Cursor = Cursors::Hand;
                btn->FlatAppearance->MouseOverBackColor = Color::FromArgb(245, 244, 255);

                if (i == 0) {
                    btn->ForeColor = primaryColor;
                    btn->Font = gcnew Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
                    btn->Click += gcnew EventHandler(this, &MainForm::BtnHRHomeClick);
                }
                else if (i == 1) {
                    btn->Click += gcnew EventHandler(this, &MainForm::BtnHRPSClick);
                }
                else if (i == 2) {
                    btn->Click += gcnew EventHandler(this, &MainForm::BtnHRUSClick);
                }
                else if (i == 3) {
                    btn->Click += gcnew EventHandler(this, &MainForm::BtnHRPFClick);
                }
                header->Controls->Add(btn);
            }

            Label^ userName = gcnew Label();
            userName->Text = L"👤 Кадровик";
            userName->Font = gcnew Drawing::Font(L"Segoe UI", 9.5F);
            userName->ForeColor = darkColor;
            userName->Location = Drawing::Point(910, 23);
            userName->AutoSize = true;
            header->Controls->Add(userName);

            Button^ btnLogout = CreateButton(L"Выход", 1000, 18, 65, 32,
                Color::FromArgb(248, 215, 218), dangerColor);
            btnLogout->Click += gcnew EventHandler(this, &MainForm::BtnLogoutClick);
            header->Controls->Add(btnLogout);
        }

        void BtnHRPSClick(Object^ sender, EventArgs^ e) {
            ShowEmployeeForm(L"Прием сотрудника");;
        }

        void BtnHRUSClick(Object^ sender, EventArgs^ e) {
            ShowEmployeeForm(L"Увольнение сотрудника");;
        }

        void BtnHRPFClick(Object^ sender, EventArgs^ e) {
            ShowPersonalFiles();
        }

        void BtnHRHomeClick(Object^ sender, EventArgs^ e) {
            ShowHRDashboard();
        }

        void BtnBackToHRClick(Object^ sender, EventArgs^ e) {
            ShowHRDashboard();
        }

        void BtnHRSaveClick(Object^ sender, EventArgs^ e) {
            MessageBox::Show(L"Операция успешно выполнена!\nДанные сохранены в системе.", L"Успех",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
            ShowHRDashboard();
        }




        // ========== ЭКРАН БУХГАЛТЕРА ==========
        void ShowBuhDashboard() {
            this->Controls->Clear();
            this->BackColor = bgColor;
            CreateBuhHeader();

            Label^ lblWelcome = gcnew Label();
            lblWelcome->Text = L"Добро пожаловать, " + Database::CurrentUser->FullName + L"!";
            lblWelcome->Font = gcnew Drawing::Font(L"Segoe UI", 20.0F, FontStyle::Bold);
            lblWelcome->ForeColor = darkColor;
            lblWelcome->Location = Drawing::Point(25, 85);
            lblWelcome->AutoSize = true;
            this->Controls->Add(lblWelcome);

            Label^ lblSub = gcnew Label();
            lblSub->Text = L"Бухгалтерия - расчет заработной платы";
            lblSub->Font = gcnew Drawing::Font(L"Segoe UI", 11.0F);
            lblSub->ForeColor = grayColor;
            lblSub->Location = Drawing::Point(25, 123);
            lblSub->AutoSize = true;
            this->Controls->Add(lblSub);

            // Финансовые показатели
            array<String^>^ titles = { L"Фонд оплаты", L"НДФЛ к уплате", L"Страховые взносы", L"Средняя ЗП" };
            array<String^>^ values = { L"8 450 000 ₽", L"1 098 500 ₽", L"2 535 000 ₽", L"54 167 ₽" };
            array<String^>^ icons = { L"💰", L"📊", L"🏦", L"📈" };

            for (int i = 0; i < 4; i++) {
                Panel^ stat = gcnew Panel();
                stat->Size = Drawing::Size(252, 100);
                stat->Location = Drawing::Point(25 + i * 265, 155);
                stat->BackColor = cardColor;

                Label^ iconLabel = gcnew Label();
                iconLabel->Text = icons[i];
                iconLabel->Font = gcnew Drawing::Font(L"Segoe UI", 23.0F);
                iconLabel->Location = Drawing::Point(15, 15);
                iconLabel->Size = Drawing::Size(45, 45);
                stat->Controls->Add(iconLabel);

                Label^ val = gcnew Label();
                val->Text = values[i];
                val->Font = gcnew Drawing::Font(L"Segoe UI", 18.0F, FontStyle::Bold);
                val->ForeColor = primaryColor;
                val->Location = Drawing::Point(70, 12);
                val->AutoSize = true;
                stat->Controls->Add(val);

                Label^ tit = gcnew Label();
                tit->Text = titles[i];
                tit->Font = gcnew Drawing::Font(L"Segoe UI", 9.5F);
                tit->ForeColor = grayColor;
                tit->Location = Drawing::Point(70, 52);
                tit->AutoSize = true;
                stat->Controls->Add(tit);

                this->Controls->Add(stat);
            }

            // Функциональные блоки
            Label^ lblFunctions = gcnew Label();
            lblFunctions->Text = L"Расчетные операции";
            lblFunctions->Font = gcnew Drawing::Font(L"Segoe UI", 16.0F, FontStyle::Bold);
            lblFunctions->ForeColor = darkColor;
            lblFunctions->Location = Drawing::Point(25, 280);
            lblFunctions->AutoSize = true;
            this->Controls->Add(lblFunctions);

            array<String^>^ fTitles = {
                L"💰  Начисления", L"📉  Удержания",
                L"📄  Расчетные листки", L"📊  Ведомость",
                L"🏛️  Отчет ФНС", L"📋  Отчет СФР"
            };
            array<String^>^ fDescs = {
                L"Расчет окладов, премий и надбавок",
                L"Расчет НДФЛ, алиментов и прочих удержаний",
                L"Формирование и рассылка расчетных листков",
                L"Сводная ведомость по заработной плате",
                L"Подготовка отчетности для налоговой",
                L"Подготовка отчетности в Социальный фонд"
            };

            for (int i = 0; i < 6; i++) {
                Panel^ card = gcnew Panel();
                card->Size = Drawing::Size(335, 95);
                card->Location = Drawing::Point(25 + (i % 3) * 350, 315 + (i / 3) * 112);
                card->BackColor = cardColor;
                card->Cursor = Cursors::Hand;
                card->MouseEnter += gcnew EventHandler(this, &MainForm::Card_MouseEnter);
                card->MouseLeave += gcnew EventHandler(this, &MainForm::Card_MouseLeave);

                Label^ cTitle = gcnew Label();
                cTitle->Text = fTitles[i];
                cTitle->Font = gcnew Drawing::Font(L"Segoe UI", 11.5F, FontStyle::Bold);
                cTitle->ForeColor = darkColor;
                cTitle->Location = Drawing::Point(18, 18);
                cTitle->AutoSize = true;
                card->Controls->Add(cTitle);

                Label^ cDesc = gcnew Label();
                cDesc->Text = fDescs[i];
                cDesc->Font = gcnew Drawing::Font(L"Segoe UI", 9.0F);
                cDesc->ForeColor = grayColor;
                cDesc->Location = Drawing::Point(18, 48);
                cDesc->Size = Drawing::Size(300, 35);
                card->Controls->Add(cDesc);

                int index = i;
                card->Click += gcnew EventHandler(this, &MainForm::BuhCardClick);

                this->Controls->Add(card);
            }
        }

        void BuhCardClick(Object^ sender, EventArgs^ e) {
            Panel^ card = (Panel^)sender;
            Label^ title = (Label^)card->Controls[0];

            if (title->Text->Contains(L"Начисления")) {
                ShowSalaryTable(L"Расчет начислений");
            }
            else if (title->Text->Contains(L"Удержания")) {
                ShowSalaryTable(L"Расчет удержаний");
            }
            else if (title->Text->Contains(L"Расчетные листки")) {
                ShowPayslipsList();
            }
            else if (title->Text->Contains(L"Ведомость")) {
                ShowSalaryReport();
            }
            else {
                MessageBox::Show(L"Раздел в разработке", L"Информация");
            }
        }

        void ShowSalaryTable(String^ title) {
            this->Controls->Clear();
            this->BackColor = bgColor;
            CreateBuhHeader();

            Label^ lblTitle = gcnew Label();
            lblTitle->Text = title;
            lblTitle->Font = gcnew Drawing::Font(L"Segoe UI", 20.0F, FontStyle::Bold);
            lblTitle->ForeColor = darkColor;
            lblTitle->Location = Drawing::Point(25, 85);
            lblTitle->AutoSize = true;
            this->Controls->Add(lblTitle);

            Label^ lblPeriod = gcnew Label();
            lblPeriod->Text = L"Период: Апрель 2026";
            lblPeriod->Font = gcnew Drawing::Font(L"Segoe UI", 12.0F);
            lblPeriod->ForeColor = primaryColor;
            lblPeriod->Location = Drawing::Point(25, 120);
            lblPeriod->AutoSize = true;
            this->Controls->Add(lblPeriod);

            Button^ btnCalc = CreateButton(L"🔄 Пересчитать", 880, 80, 180, 38, primaryColor, Color::White);
            this->Controls->Add(btnCalc);

            DataGridView^ dgv = gcnew DataGridView();
            dgv->Location = Drawing::Point(25, 150);
            dgv->Size = Drawing::Size(1050, 480);
            dgv->ReadOnly = true;
            dgv->AllowUserToAddRows = false;
            dgv->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            dgv->BackgroundColor = cardColor;
            dgv->BorderStyle = BorderStyle::None;
            dgv->RowHeadersVisible = false;
            dgv->EnableHeadersVisualStyles = false;
            dgv->ColumnHeadersDefaultCellStyle->BackColor = Color::FromArgb(248, 249, 255);
            dgv->ColumnHeadersDefaultCellStyle->ForeColor = darkColor;
            dgv->ColumnHeadersDefaultCellStyle->Font = gcnew Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
            dgv->ColumnHeadersHeight = 40;
            dgv->RowTemplate->Height = 40;

            if (title->Contains(L"Начисления")) {
                dgv->Columns->Add(L"colFIO", L"СОТРУДНИК");
                dgv->Columns->Add(L"colBase", L"ОКЛАД");
                dgv->Columns->Add(L"colBonus", L"ПРЕМИЯ");
                dgv->Columns->Add(L"colOver", L"ПЕРЕРАБОТКИ");
                dgv->Columns->Add(L"colTotal", L"ИТОГО НАЧИСЛЕНО");

                dgv->Rows->Add(L"Иванов И.И.", L"100 000", L"25 000", L"0", L"125 000");
                dgv->Rows->Add(L"Петрова М.С.", L"60 000", L"10 000", L"5 000", L"75 000");
                dgv->Rows->Add(L"Козлова Е.Д.", L"55 000", L"8 000", L"0", L"63 000");
            }
            else {
                dgv->Columns->Add(L"colFIO", L"СОТРУДНИК");
                dgv->Columns->Add(L"colNDFL", L"НДФЛ (13%)");
                dgv->Columns->Add(L"colAlim", L"АЛИМЕНТЫ");
                dgv->Columns->Add(L"colOther", L"ПРОЧИЕ");
                dgv->Columns->Add(L"colTotal", L"ИТОГО УДЕРЖАНО");

                dgv->Rows->Add(L"Иванов И.И.", L"16 250", L"0", L"0", L"16 250");
                dgv->Rows->Add(L"Петрова М.С.", L"9 750", L"0", L"0", L"9 750");
                dgv->Rows->Add(L"Козлова Е.Д.", L"8 190", L"12 600", L"0", L"20 790");
            }

            this->Controls->Add(dgv);

            Button^ btnBack = CreateButton(L"← Назад", 25, 650, 150, 38, primaryColor, Color::White);
            btnBack->Click += gcnew EventHandler(this, &MainForm::BtnBackToBuhClick);
            this->Controls->Add(btnBack);
        }

        void ShowPayslipsList() {
            this->Controls->Clear();
            this->BackColor = bgColor;
            CreateBuhHeader();

            Label^ lblTitle = gcnew Label();
            lblTitle->Text = L"Формирование расчетных листков";
            lblTitle->Font = gcnew Drawing::Font(L"Segoe UI", 20.0F, FontStyle::Bold);
            lblTitle->ForeColor = darkColor;
            lblTitle->Location = Drawing::Point(25, 85);
            lblTitle->AutoSize = true;
            this->Controls->Add(lblTitle);

            Button^ btnGenerate = CreateButton(L"📄 Сформировать все", 880, 80, 180, 38, successColor, Color::White);
            this->Controls->Add(btnGenerate);

            DataGridView^ dgv = gcnew DataGridView();
            dgv->Location = Drawing::Point(25, 140);
            dgv->Size = Drawing::Size(1050, 500);
            dgv->ReadOnly = true;
            dgv->AllowUserToAddRows = false;
            dgv->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            dgv->BackgroundColor = cardColor;
            dgv->BorderStyle = BorderStyle::None;
            dgv->RowHeadersVisible = false;
            dgv->EnableHeadersVisualStyles = false;
            dgv->ColumnHeadersDefaultCellStyle->BackColor = Color::FromArgb(248, 249, 255);
            dgv->ColumnHeadersDefaultCellStyle->ForeColor = darkColor;
            dgv->ColumnHeadersHeight = 40;
            dgv->RowTemplate->Height = 40;

            dgv->Columns->Add(L"colFIO", L"СОТРУДНИК");
            dgv->Columns->Add(L"colAccrued", L"НАЧИСЛЕНО");
            dgv->Columns->Add(L"colDeducted", L"УДЕРЖАНО");
            dgv->Columns->Add(L"colToPay", L"К ВЫПЛАТЕ");
            dgv->Columns->Add(L"colStatus", L"СТАТУС");
            dgv->Columns->Add(L"colAction", L"ДЕЙСТВИЕ");

            dgv->Rows->Add(L"Иванов И.И.", L"125 000 ₽", L"16 250 ₽", L"108 750 ₽", L"✅ Сформирован", L"📥 PDF");
            dgv->Rows->Add(L"Петрова М.С.", L"75 000 ₽", L"9 750 ₽", L"65 250 ₽", L"✅ Сформирован", L"📥 PDF");
            dgv->Rows->Add(L"Козлова Е.Д.", L"63 000 ₽", L"20 790 ₽", L"42 210 ₽", L"⏳ Ожидает", L"📥 PDF");

            this->Controls->Add(dgv);

            Button^ btnBack = CreateButton(L"← Назад", 25, 650, 150, 38, primaryColor, Color::White);
            btnBack->Click += gcnew EventHandler(this, &MainForm::BtnBackToBuhClick);
            this->Controls->Add(btnBack);
        }

        void ShowSalaryReport() {
            this->Controls->Clear();
            this->BackColor = bgColor;
            CreateBuhHeader();

            Label^ lblTitle = gcnew Label();
            lblTitle->Text = L"Сводная ведомость по заработной плате";
            lblTitle->Font = gcnew Drawing::Font(L"Segoe UI", 20.0F, FontStyle::Bold);
            lblTitle->ForeColor = darkColor;
            lblTitle->Location = Drawing::Point(25, 85);
            lblTitle->AutoSize = true;
            this->Controls->Add(lblTitle);

            Label^ lblPeriod = gcnew Label();
            lblPeriod->Text = L"Апрель 2026";
            lblPeriod->Font = gcnew Drawing::Font(L"Segoe UI", 14.0F, FontStyle::Bold); lblPeriod->ForeColor = primaryColor;
            lblPeriod->Location = Drawing::Point(25, 120);
            lblPeriod->AutoSize = true;
            this->Controls->Add(lblPeriod);

            // Итоговые суммы
            Panel^ summaryPanel = gcnew Panel();
            summaryPanel->Size = Drawing::Size(1050, 80);
            summaryPanel->Location = Drawing::Point(25, 160);
            summaryPanel->BackColor = cardColor;

            Label^ lblTotalAccrued = gcnew Label();
            lblTotalAccrued->Text = L"Всего начислено: 263 000 ₽";
            lblTotalAccrued->Font = gcnew Drawing::Font(L"Segoe UI", 14.0F, FontStyle::Bold);
            lblTotalAccrued->ForeColor = successColor;
            lblTotalAccrued->Location = Drawing::Point(30, 15);
            lblTotalAccrued->AutoSize = true;
            summaryPanel->Controls->Add(lblTotalAccrued);

            Label^ lblTotalDeducted = gcnew Label();
            lblTotalDeducted->Text = L"Всего удержано: 46 790 ₽";
            lblTotalDeducted->Font = gcnew Drawing::Font(L"Segoe UI", 14.0F, FontStyle::Bold);
            lblTotalDeducted->ForeColor = dangerColor;
            lblTotalDeducted->Location = Drawing::Point(30, 45);
            lblTotalDeducted->AutoSize = true;
            summaryPanel->Controls->Add(lblTotalDeducted);

            Label^ lblTotalToPay = gcnew Label();
            lblTotalToPay->Text = L"К выплате: 216 210 ₽";
            lblTotalToPay->Font = gcnew Drawing::Font(L"Segoe UI", 16.0F, FontStyle::Bold);
            lblTotalToPay->ForeColor = primaryColor;
            lblTotalToPay->Location = Drawing::Point(750, 25);
            lblTotalToPay->AutoSize = true;
            summaryPanel->Controls->Add(lblTotalToPay);

            this->Controls->Add(summaryPanel);

            DataGridView^ dgv = gcnew DataGridView();
            dgv->Location = Drawing::Point(25, 260);
            dgv->Size = Drawing::Size(1050, 360);
            dgv->ReadOnly = true;
            dgv->AllowUserToAddRows = false;
            dgv->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            dgv->BackgroundColor = cardColor;
            dgv->BorderStyle = BorderStyle::None;
            dgv->RowHeadersVisible = false;
            dgv->EnableHeadersVisualStyles = false;
            dgv->ColumnHeadersDefaultCellStyle->BackColor = Color::FromArgb(248, 249, 255);
            dgv->ColumnHeadersDefaultCellStyle->ForeColor = darkColor;
            dgv->ColumnHeadersHeight = 40;
            dgv->RowTemplate->Height = 40;

            dgv->Columns->Add(L"colFIO", L"СОТРУДНИК");
            dgv->Columns->Add(L"colAccrued", L"НАЧИСЛЕНО");
            dgv->Columns->Add(L"colNDFL", L"НДФЛ");
            dgv->Columns->Add(L"colOther", L"ПРОЧИЕ УДЕРЖАНИЯ");
            dgv->Columns->Add(L"colToPay", L"К ВЫПЛАТЕ");

            dgv->Rows->Add(L"Иванов И.И.", L"125 000", L"16 250", L"0", L"108 750");
            dgv->Rows->Add(L"Петрова М.С.", L"75 000", L"9 750", L"0", L"65 250");
            dgv->Rows->Add(L"Козлова Е.Д.", L"63 000", L"8 190", L"12 600", L"42 210");

            this->Controls->Add(dgv);

            Button^ btnBack = CreateButton(L"← Назад", 25, 640, 150, 38, primaryColor, Color::White);
            btnBack->Click += gcnew EventHandler(this, &MainForm::BtnBackToBuhClick);
            this->Controls->Add(btnBack);
        }

        void CreateBuhHeader() {
            Panel^ header = gcnew Panel();
            header->Size = Drawing::Size(1100, 65);
            header->BackColor = cardColor;
            header->Location = Drawing::Point(0, 0);
            this->Controls->Add(header);

            Label^ logo = gcnew Label();
            logo->Text = L"⚡ HR-Auto | Расчет зарплаты";
            logo->Font = gcnew Drawing::Font(L"Segoe UI", 16.0F, FontStyle::Bold);
            logo->ForeColor = primaryColor;
            logo->Location = Drawing::Point(25, 18);
            logo->AutoSize = true;
            header->Controls->Add(logo);

            array<String^>^ navs = { L"Главная", L"Расчетные листки", L"Отчеты ФНС", L"Отчеты СФР"};
            for (int i = 0; i < 4; i++) {
                Button^ btn = gcnew Button();
                btn->Text = navs[i];
                btn->Location = Drawing::Point(380 + i * 130, 14);
                btn->Size = Drawing::Size(120, 38);
                btn->FlatStyle = FlatStyle::Flat;
                btn->FlatAppearance->BorderSize = 0;
                btn->BackColor = cardColor;
                btn->ForeColor = grayColor;
                btn->Font = gcnew Drawing::Font(L"Segoe UI", 9.5F);
                btn->Cursor = Cursors::Hand;
                btn->FlatAppearance->MouseOverBackColor = Color::FromArgb(245, 244, 255);

                if (i == 0) {
                    btn->ForeColor = primaryColor;
                    btn->Font = gcnew Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
                    btn->Click += gcnew EventHandler(this, &MainForm::BtnBuhHomeClick);
                }
                header->Controls->Add(btn);
            }

            Label^ userName = gcnew Label();
            userName->Text = L"👤 Бухгалтер";
            userName->Font = gcnew Drawing::Font(L"Segoe UI", 9.5F);
            userName->ForeColor = darkColor;
            userName->Location = Drawing::Point(910, 23);
            userName->AutoSize = true;
            header->Controls->Add(userName);

            Button^ btnLogout = CreateButton(L"Выход", 1000, 18, 65, 32,
                Color::FromArgb(248, 215, 218), dangerColor);
            btnLogout->Click += gcnew EventHandler(this, &MainForm::BtnLogoutClick);
            header->Controls->Add(btnLogout);
        }

        void BtnBuhHomeClick(Object^ sender, EventArgs^ e) {
            ShowBuhDashboard();
        }

        void BtnBackToBuhClick(Object^ sender, EventArgs^ e) {
            ShowBuhDashboard();
        }


    };
}