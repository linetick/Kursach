#include "productswindow_buyer.h"
#include "qsqlrecord.h"
#include "ui_productswindow_buyer.h"

ProductsWindow_Buyer::ProductsWindow_Buyer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProductsWindow_Buyer),
    proxyModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);

    db.getProduct();
    //ui->tableView->setModel(db.getModel());

    //Сигнал
    _BasketWindow = new BasketWindow(this);

    connect(this, &ProductsWindow_Buyer::productAdded, _BasketWindow, &BasketWindow::updateCart);

    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterKeyColumn(-1);
    ui->tableView->setModel(proxyModel);

    connect(ui->Search, &QLineEdit::textChanged, this, [this](const QString &text) {
        proxyModel->setFilterRegularExpression(QRegularExpression(text, QRegularExpression::CaseInsensitiveOption));
    });

    // Махинации с таблицей:
    QHeaderView* horizontalHeader = ui->tableView->horizontalHeader();
    horizontalHeader->setSectionResizeMode(QHeaderView::Stretch); // Растягивает все столбцы равномерно
    //
    ui->tableView->setShowGrid(true); // Показывает сетку таблицы
    ui->tableView->setFrameShape(QFrame::NoFrame); // Убирает рамку вокруг таблицы, если необходимо
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->verticalHeader()->setVisible(false);

    proxyModel->setSourceModel(db.getModel());
}

ProductsWindow_Buyer::~ProductsWindow_Buyer()
{
    delete ui;
}

int ProductsWindow_Buyer::takeID()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        //QMessageBox::warning(this, "Выбор элемента", "Пожалуйста, выберите элемент в таблице."); // тут добавить
        return -1;
    }

    bool correctColumnSelected = false;
    foreach (const QModelIndex &index, selectedIndexes) {
        if (index.column() == 0) { // Предполагаем, что ID_Товара находится в первой колонке
            //correctColumnSelected = true;
            return index.data().toInt();
        }
    }

    if (!correctColumnSelected)
    {
        //QMessageBox::warning(this, "Неверный выбор", "Пожалуйста, выберите ID_Товара в первой колонке.");
        return -1;
    } /*else {
        // Здесь код для обработки корректного выбора, если необходимо
        QMessageBox::information(this, "Корректный выбор", "Выбран ID_Товара.");
    }*/
    return -1;
}

void ProductsWindow_Buyer::on_Return_button_Clicked_clicked()
{
    this->close();
    emit Return();
}


void ProductsWindow_Buyer::on_Add_button_Clicked_clicked()
{
    int selected = takeID();
    if(selected != -1)
    {
        Basket::addToCart(db.getProductById(selected));
        emit productAdded();
    }
}

