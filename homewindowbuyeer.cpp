#include "homewindowbuyeer.h"
#include "ui_homewindowbuyeer.h"

HomeWindowBuyeer::HomeWindowBuyeer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomeWindowBuyeer)
{
    ui->setupUi(this);

    _ProductsWindow_Buyer = new ProductsWindow_Buyer(this);
    _HistoryWindow = new HistoryWindow(this);
    _BasketWindow = new BasketWindow(this);
    _PersonalAccountWindow = new PersonalAccountWindow(this);

    connect(this, &HomeWindowBuyeer::openProductsWindow, //Открыть продукты
            this, &HomeWindowBuyeer::close);
    connect(this, &HomeWindowBuyeer::openProductsWindow,
            _ProductsWindow_Buyer, &ProductsWindow_Buyer::exec);
    connect(_ProductsWindow_Buyer, &ProductsWindow_Buyer::Return,
            this, &ProductsWindow_Buyer::show);
    //------------------
    connect(this, &HomeWindowBuyeer::openHistoryWindow, //Открыть историю покупок
            this, &HomeWindowBuyeer::close);
    connect(this, &HomeWindowBuyeer::openHistoryWindow,
            _HistoryWindow, &HistoryWindow::exec);
    connect(_HistoryWindow, &HistoryWindow::Return,
            this, &HistoryWindow::show);
    //-------------------
    connect(this, &HomeWindowBuyeer::openBasketWindow, //Открыть окно корзины
            this, &HomeWindowBuyeer::close);
    connect(this, &HomeWindowBuyeer::openBasketWindow,
            _BasketWindow, &BasketWindow::exec);
    connect(_BasketWindow, &BasketWindow::Return,
            this, &BasketWindow::show);
    //--------------------
    connect(this, &HomeWindowBuyeer::openPersonalAccWindow,
            this, &HomeWindowBuyeer::close);
    connect(this, &HomeWindowBuyeer::openPersonalAccWindow,
            _PersonalAccountWindow, &PersonalAccountWindow::exec);
    connect(_PersonalAccountWindow, &PersonalAccountWindow::Return,
            this, &PersonalAccountWindow::show);
}

HomeWindowBuyeer::~HomeWindowBuyeer()
{
    delete ui;
}

void HomeWindowBuyeer::on_Products_button_Clicked_clicked()
{
    emit openProductsWindow();
}


void HomeWindowBuyeer::on_Basket_button_Clicked_clicked()
{
    emit openBasketWindow();
}


void HomeWindowBuyeer::on_History_button_Clicked_clicked()
{
    emit openHistoryWindow();
}


void HomeWindowBuyeer::on_PAccount_button_Clicked_clicked()
{
    emit openPersonalAccWindow();
}

