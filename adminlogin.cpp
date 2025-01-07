#include "adminlogin.h"
#include "ui_adminlogin.h"  // Make sure to include the UI header
#include<QMessageBox>

AdminLogin::AdminLogin(QWidget *parent) :
    QDialog(parent),  // Ensure your constructor uses QDialog if that's the base class
    ui(new Ui::Schoolmanagemnetadminlogin_dialog)  // Use the correct class name here
{
    ui->setupUi(this);  // Set up the UI for the AdminLogin dialog

       setWindowTitle("Admin Login");
}

AdminLogin::~AdminLogin()
{
    delete ui;  // Clean up the UI object
}

void AdminLogin::on_login_button_clicked()
{

     QString username = ui->Username_lineEdit->text();
     QString password = ui->Password_lineEdit->text();

     if(username=="admin" && password=="admin@123"){
         QMessageBox::information(this , "Login" , "Login Successfully");
         accept();
     }
     else if(username=="" && password==""){
         QMessageBox::warning(this , "Login" , "Please Enter the Username and Password");

     }
     else{
         QMessageBox::warning(this , "Login" , "Invalid username or password");
     }
}

void AdminLogin::on_cancel_button_clicked()
{
  this->close();
}
