#include "adminlogin.h"
#include "dashboard.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   // Open AdminLogin dialog instead of MainWindow

    AdminLogin loginpage;  // Create an AdminLogin object

    loginpage.show();  // Show the AdminLogin dialog

    // now here we are checing user login successfully or not if login successfully dashboard will be appear

    if(loginpage.exec()== QDialog::Accepted){
         //  if login successfully dashboard appear

        Dashboard Dashboardpage; //creating Dashboard object
        Dashboardpage.showMaximized();
        return a.exec(); // Start the event loop for the Dashboard window
    }

    return 0;
}
