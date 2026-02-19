#include "AddProductDialog.h"
#include "ui_AddProductDialog.h"
#include <QDebug>
#include <QMessageBox>

AddProductDialog::AddProductDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::AddProductDialog)
{
    ui->setupUi(this);

    // Set window title and optional styling
    setWindowTitle("Add Product");

    ui->priceSpinBox->setMaximum(1e9);
    ui->priceSpinBox->setDecimals(2);

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
    p.url = ui->storeLineEdit->text();
    p.price = ui->priceSpinBox->value();
    p.lastChecked = QDateTime::currentDateTime();

    if (p.name.isEmpty() || p.url.isEmpty() || p.price <= 0.0) {
        QMessageBox::warning(this, "Incomplete Data",
            "Please fill all fields:\n"
            "- Product Name\n"
            "- Product URL\n"
            "- Price (must be greater than 0)");
        return;
    }

    emit productSubmitted(p); // notify MainWindow / TaskManager

    hide(); // Close dialog without blocking main window
}

// Called when "Cancel" button is clicked
void AddProductDialog::onCancelClicked()
{
    hide(); // simply hide the dialog
}
