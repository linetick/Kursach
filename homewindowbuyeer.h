#ifndef HOMEWINDOWBUYEER_H
#define HOMEWINDOWBUYEER_H

#include <QDialog>
#include "productswindow_buyer.h"
#include "historywindow.h"
#include "personalaccountwindow.h"
#include "basketwindow.h"

namespace Ui {
class HomeWindowBuyeer;
}

class HomeWindowBuyeer : public QDialog
{
    Q_OBJECT

public:
    explicit HomeWindowBuyeer(QWidget *parent = nullptr);
    ~HomeWindowBuyeer();

signals:
    void openProductsWindow();
    void openHistoryWindow();
    void openPersonalAccWindow();
    void openBasketWindow();

private slots:
    void on_Products_button_Clicked_clicked();

    void on_Basket_button_Clicked_clicked();

    void on_History_button_Clicked_clicked();

    void on_PAccount_button_Clicked_clicked();

private:
    Ui::HomeWindowBuyeer *ui;
    ProductsWindow_Buyer *_ProductsWindow_Buyer;
    HistoryWindow *_HistoryWindow;
    PersonalAccountWindow *_PersonalAccountWindow;
    BasketWindow *_BasketWindow;
};

#endif // HOMEWINDOWBUYEER_H
