#ifndef HISTORYWINDOW_H
#define HISTORYWINDOW_H

#include <QDialog>
#include "database.h"
#include "qsortfilterproxymodel.h"

namespace Ui {
class HistoryWindow;
}

class HistoryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryWindow(QWidget *parent = nullptr);
    ~HistoryWindow();

    int takeID();
    void showZakaz(int a);
    void ShowDelivery();
    void styleButton(bool a);

signals:
    void Return();

public slots:
    void onCellDoubleClicked(const QModelIndex &index);

private slots:
    void on_Return_button_clicked_clicked();

    void on_pushButton_clicked();

    void on_ReturnToDelivery_button_Clicked_clicked();

protected:
    void showEvent(QShowEvent *event);

private:
    Ui::HistoryWindow *ui;
    DataBase db;
    QSortFilterProxyModel *proxyModel;
    bool check = false;
};

#endif // HISTORYWINDOW_H
