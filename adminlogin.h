#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <QDialog>  // Ensure the base class is QDialog, because your UI class is a QDialog
#include "ui_adminlogin.h"  // This is generated from the adminlogin.ui file

class AdminLogin : public QDialog  // Ensure your class inherits from QDialog
{
    Q_OBJECT

public:
    explicit AdminLogin(QWidget *parent = nullptr);
    ~AdminLogin();

private slots:
    void on_login_button_clicked();

    void on_cancel_button_clicked();

private:
    Ui::Schoolmanagemnetadminlogin_dialog *ui;  // Use the correct name from the generated UI class
};

#endif // ADMINLOGIN_H
