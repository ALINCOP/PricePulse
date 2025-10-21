#include "AddProductDialog.h"
#include "ui_AddProductDialog.h"
#include <QDebug>

AddProductDialog::AddProductDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::AddProductDialog)
{
    ui->setupUi(this);

    // Set window title and optional styling
    setWindowTitle("Add Product");

    // Connect buttons to slots
    connect(ui->addButton, &QPushButton::clicked, this, &AddProductDialog::onSubmitClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &AddProductDialog::onCancelClicked);
}

AddProductDialog::~AddProductDialog() {
    delete ui;
}

// Called when "Add Product" button is clicked
void AddProductDialog::onSubmitClicked()
{
    Product p;
    p.name = ui->productLineEdit->text();
    p.store = ui->storeLineEdit->text();
    p.price = ui->priceSpinBox->value();
    p.lastChecked = QDateTime::currentDateTime();

    emit productSubmitted(p); // notify MainWindow / TaskManager

    hide(); // Close dialog without blocking main window
}

// Called when "Cancel" button is clicked
void AddProductDialog::onCancelClicked()
{
    hide(); // simply hide the dialog
}
