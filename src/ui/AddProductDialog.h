#pragma once

#include <QDialog>
#include <QDateTime>
#include "TaskManager.h" // for Product struct
#include "Product.h"

namespace Ui { class AddProductDialog; }

// Dialog for adding a new product
class AddProductDialog : public QDialog {
    Q_OBJECT
public:
    explicit AddProductDialog(QWidget* parent = nullptr);
    ~AddProductDialog();

signals:
    // Emitted when user fills fields and clicks "Add Product"
    void productSubmitted(const Product& product);

private slots:
    void onSubmitClicked(); // Connected to Add Product button
    void onCancelClicked(); // Connected to Cancel button

private:
    Ui::AddProductDialog* ui;
};
