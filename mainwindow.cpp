#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    //Подключение к бд
//    db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName("D:\\SQL\\DataBases\\Kurs.db");

    //инициализация окон

    _RegistrWindoww = new RegistrWindoww(this); //окно регистрации
    _HomeWindowAdmin = new HomeWindowAdmin(this);
    _HomeWindowManager = new HomeWindowManager(this);
    _HomeWindowBuyeer = new HomeWindowBuyeer(this);

    connect(this, &MainWindow::openRegistrWindow,
            this, &MainWindow::close);
    connect(this, &MainWindow::openRegistrWindow,
            _RegistrWindoww, &RegistrWindoww::exec);
    connect(_RegistrWindoww, &RegistrWindoww::openMainWindow,
            this, &MainWindow::show);

    connect(this, &MainWindow::openHomeWindowAdmin, this, &MainWindow::close);
    connect(this, &MainWindow::openHomeWindowAdmin, _HomeWindowAdmin, &HomeWindowAdmin::exec);

    connect(this, &MainWindow::openHomeWindowManager, this, &MainWindow::close);
    connect(this, &MainWindow::openHomeWindowManager, _HomeWindowManager, &HomeWindowManager::exec);

    connect(this, &MainWindow::openHomeWindowBuyer, this, &MainWindow::close);
    connect(this, &MainWindow::openHomeWindowBuyer, _HomeWindowBuyeer, &HomeWindowManager::exec);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*QString checkCredentialsAndGetRole(const QString& login, const QString& password) {
    QSqlQuery query;
    query.prepare("SELECT \"Роль\" FROM \"Люди\" WHERE \"Логин\" = :login AND \"Пароль\" = :password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Ошибка при выполнении запроса:" << query.lastError().text();
            return QString(); // Возвращает пустую строку в случае ошибки
    }

    if (query.next()) {
        return query.value(0).toString(); // Возвращает роль, если найдена запись
    }

    return QString(); // Возвращает пустую строку, если запись не найдена
} */

void MainWindow::on_pushButton_clicked() //Нажата кнопка войти
{
    // тут должен быть запрос в бд
    // тут должно быть условие (по роли)

    if(db.open())
    {
        QMessageBox::information(nullptr, "ошибка", "Ошибка");

    }
    //else QMessageBox::information(nullptr, "нету ошибки", "Чики пуки");

    QString login = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QString role = DB.checkCredentials(login, password);
//    if(login == "Админ")
//    {
//        emit openHomeWindowAdmin();
//    }

   if(role == "Администратор")
    {
        emit openHomeWindowAdmin();
    }
    if(role == "Менеджер")
    {
        emit openHomeWindowManager();
    }
    if(role == "Покупатель")
    {
        emit openHomeWindowBuyer();
    }
    if(role == "Ошибка")
    {
        QMessageBox::information(nullptr, "Ошибка", "Неправильно введённый логин или пароль");
    }


}


void MainWindow::on_pushButton_2_clicked() // Нажата кнопка регистрация
{
    emit openRegistrWindow();
}

