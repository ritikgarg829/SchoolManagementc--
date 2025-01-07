#include "dashboard.h"
#include "ui_dashboard.h"
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QDebug>  // Include QDebug for logging
#include "student.h"
#include "teacher.h"
#include "course.h"
#include "adminlogin.h"

Dashboard::Dashboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dashboardformWidget)
{
    ui->setupUi(this);

     setWindowTitle("Dashboard");

    totalStudents = 0;
    totalCourses = 0;
    totalTeachers = 0;
    updateTotalStudentCountLabel();  // Update label to show initial count
    updateTotalCourseCountLabel();
    updateTotalTeacherCountLabel();


    // ======================== Timer for Updating the Clock ========================


    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Dashboard::updateClock);  // Connect the timer to updateClock
    timer->start(1000);  // Update every second
    updateClock();  // Display the initial time



    // ================================ Menu Handling ==========================
    connect(ui->dashboardleftpannel_listwidget, &QListWidget::currentRowChanged, this, &Dashboard::onMenuChanged);
    ui->dashboardleftpannel_listwidget->setCurrentRow(0);  // Default to Home page
    ui->rightpannel_content_stackwidget->setCurrentIndex(0);  // Show Home page by default

    // Initialize the StudentSection for handling student data logic
    studentSection = new StudentSection(ui->studentdata_tableWidget);
    teacherSection = new TeacherSection(ui->teachertable_widget);
    courseSection = new CourseSection(ui->coursetable_widget);


    // =================== Ensure Table Column Count and Headers ===================
    ui->studentdata_tableWidget->setColumnCount(7);  // Set column count to 6
    ui->studentdata_tableWidget->setHorizontalHeaderLabels({"ID", "Name", "Class", "Grade", "Address", "Roll Number", "Gender"});

    ui->teachertable_widget->setColumnCount(6);  // Example columns for teacher
    ui->teachertable_widget->setHorizontalHeaderLabels({"ID", "Name", "Grade", "Course", "Email", "Phone No"});


    ui->coursetable_widget->setColumnCount(3);  // Example columns for course
    ui->coursetable_widget->setHorizontalHeaderLabels({"ID", "Name", "Course Assign"});

    // ===================== Connect the Table Row Selection Signals ===================
    connect(ui->studentdata_tableWidget, &QTableWidget::itemClicked,
            this, &Dashboard::on_table_row_selected);  // Student table row click

    connect(ui->teachertable_widget, &QTableWidget::itemClicked,
            this, &Dashboard::on_teacher_table_row_selected);  // Teacher table row click

    connect(ui->coursetable_widget, &QTableWidget::itemClicked,
            this, &Dashboard::on_course_table_row_selected);  // course table row click
}

Dashboard::~Dashboard()
{
    delete ui;
    delete studentSection;  // Clean up StudentSection object
    delete teacherSection;  // Clean up TeacherSection object
    delete courseSection; // clean up coursesection object
}


//===============================total students , teachers , course-==============================================//

void Dashboard::updateTotalStudentCountLabel()
{
    ui->totalstudent_label->setText("Total Students: " + QString::number(totalStudents));
}

void Dashboard::updateTotalCourseCountLabel()
{
    ui->totalcourses_label->setText("Total Courses: " + QString::number(totalCourses));
}

void Dashboard::updateTotalTeacherCountLabel()
{
    ui->totalteacher_label->setText("Total Teachers: " + QString::number(totalTeachers));
}



// ===================== Function to Update Clock =========================
void Dashboard::updateClock()
{
    QTime time = QTime::currentTime();
    QString timeString = time.toString("hh:mm:ss AP");  // Display time in 12-hour format
    ui->clock_label->setText(timeString);  // Update the time label
}

// ============================ Handle Menu Changes ========================
void Dashboard::onMenuChanged(int index)
{
    // Switch to the selected section
    switch (index) {
        case 0:
            ui->rightpannel_content_stackwidget->setCurrentIndex(0);  // Home page
            break;
        case 1:
            ui->rightpannel_content_stackwidget->setCurrentIndex(1);  // Students page
            break;
        case 2:
            ui->rightpannel_content_stackwidget->setCurrentIndex(2);  // Teachers page
            break;
        case 3:
            ui->rightpannel_content_stackwidget->setCurrentIndex(3);  // Course page
            break;

        // Add more cases as needed for other sections
        default:
            break;
    }
}

// ===================== Add Student Button Click =========================
void Dashboard::on_add_button_clicked()
{
    studentSection->addStudent(ui->studentid_lineEdit->text(),
                               ui->studentname_lineEdit_2->text(),
                               ui->studentgrade_lineEdit->text(),
                               ui->studentaddress_lineEdit->text(),
                               ui->studentrollnumber_lineEdit->text(),
                               ui->studentclass_lineEdit->text(),
                               ui->studentgender_comboBox->currentText());

    totalStudents++;
    updateTotalStudentCountLabel();

    // Clear the input fields after adding the student
    ui->studentid_lineEdit->clear();
    ui->studentname_lineEdit_2->clear();
    ui->studentgrade_lineEdit->clear();
    ui->studentaddress_lineEdit->clear();
    ui->studentrollnumber_lineEdit->clear();
    ui->studentclass_lineEdit->clear();
    ui->studentgender_comboBox->setCurrentIndex(0);  // Reset gender combo box
}

// ====================== Update Student Information =========================
void Dashboard::on_update_button_clicked()
{
    int row = ui->studentdata_tableWidget->currentRow();
    if (row != -1) {  // Ensure a row is selected
        // Show a confirmation dialog
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Update Confirmation",
                                      "Are you sure you want to update this student's details?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            // Proceed with update if user confirmed
            studentSection->updateStudent(row,
                                          ui->studentid_lineEdit->text(),
                                          ui->studentname_lineEdit_2->text(),
                                          ui->studentgrade_lineEdit->text(),
                                          ui->studentaddress_lineEdit->text(),
                                          ui->studentrollnumber_lineEdit->text(),
                                          ui->studentclass_lineEdit->text(),
                                          ui->studentgender_comboBox->currentText());
        }
    } else {
        QMessageBox::warning(nullptr, "Update Error", "No student row selected.");
    }
}

// ===================== Delete Student Row =========================
void Dashboard::on_delete_button_clicked()
{
    int row = ui->studentdata_tableWidget->currentRow();
    if (row != -1) {
        // Show a confirmation dialog
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Delete Confirmation",
                                      "Are you sure you want to delete this student?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            // Proceed with deletion if user confirmed
            studentSection->deleteStudent(row);
            totalStudents--;
            updateTotalStudentCountLabel();

        }
    } else {
        QMessageBox::warning(nullptr, "Delete Error", "No student row selected.");
    }
}

// =================== Find Student by ID, Roll Number, or Name =======================
void Dashboard::on_find_button_clicked()
{
    studentSection->searchStudent(ui->studentid_lineEdit->text(),
                                  ui->studentname_lineEdit_2->text(),
                                  ui->studentrollnumber_lineEdit->text());
}

// ===================== Row Selection for Editing =========================
void Dashboard::on_table_row_selected(QTableWidgetItem *item)
{
    int row = item->row();  // Get the row index of the selected item

    // Get the values from the selected row in the student table
    QString studentId = ui->studentdata_tableWidget->item(row, 0)->text();
    QString studentName = ui->studentdata_tableWidget->item(row, 1)->text();
    QString studentClass = ui->studentdata_tableWidget->item(row, 2)->text();
    QString grade = ui->studentdata_tableWidget->item(row, 3)->text();
    QString address = ui->studentdata_tableWidget->item(row, 4)->text();
    QString rollNumber = ui->studentdata_tableWidget->item(row, 5)->text();
    QString gender = ui->studentdata_tableWidget->item(row, 6)->text();

    // Set the values in the UI fields for editing
    ui->studentid_lineEdit->setText(studentId);
    ui->studentname_lineEdit_2->setText(studentName);
    ui->studentclass_lineEdit->setText(studentClass);
    ui->studentgrade_lineEdit->setText(grade);
    ui->studentaddress_lineEdit->setText(address);
    ui->studentrollnumber_lineEdit->setText(rollNumber);
    ui->studentgender_comboBox->setCurrentText(gender);
}

// ====================== Add Teacher Button Click =========================
void Dashboard::on_teacher_add_button_clicked()
{
    // Add teacher logic
    teacherSection->addTeacher(ui->teacherid_lineEdit->text(),
                               ui->teachername_lineEdit->text(),
                               ui->teachergrade_lineEdit->text(),
                               ui->teachercourse_lineEdit->text(),
                               ui->teacheremail_lineEdit->text(),
                               ui->teacherphoneno_lineEdit->text(),
                               ui->teachergender_comboBox->currentText());
    totalTeachers++;
    updateTotalTeacherCountLabel();

    // Clear teacher input fields after adding
    ui->teacherid_lineEdit->clear();
    ui->teachername_lineEdit->clear();
    ui->teachergrade_lineEdit->clear();
    ui->teachercourse_lineEdit->clear();
    ui->teacheremail_lineEdit->clear();
    ui->teacherphoneno_lineEdit->clear();
    ui->teachergender_comboBox->setCurrentIndex(0);
}

// ====================== Update Teacher Information =========================
void Dashboard::on_teacher_update_button_clicked()
{
    int row = ui->teachertable_widget->currentRow();  // Get the current row of the selected item
    qDebug() << "Selected Row: " << row;  // Debug log to check if row is selected correctly
    if (row != -1) {
        // Show confirmation dialog
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Update Confirmation",
                                      "Are you sure you want to update this teacher's details?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            teacherSection->updateTeacher(row,
                                          ui->teacherid_lineEdit->text(),
                                          ui->teachername_lineEdit->text(),
                                          ui->teachergrade_lineEdit->text(),
                                          ui->teachercourse_lineEdit->text(),
                                          ui->teacheremail_lineEdit->text(),
                                          ui->teacherphoneno_lineEdit->text(),
                                          ui->teachergender_comboBox->currentText());
        }
    } else {
        QMessageBox::warning(nullptr, "Update Error", "No teacher row selected.");
    }
}



// ===================== Delete Teacher Row =========================
void Dashboard::on_teacher_delete_button_clicked()
{
    int row = ui->teachertable_widget->currentRow();
    if (row != -1) {
        // Show a confirmation dialog
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Delete Confirmation",
                                      "Are you sure you want to delete this teacher?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            // Proceed with deletion if user confirmed
            teacherSection->deleteTeacher(row);
            totalTeachers--;
            updateTotalTeacherCountLabel();
        }
    } else {
        QMessageBox::warning(nullptr, "Delete Error", "No teacher row selected.");
    }
}

// =================== Find Teacher by ID, Name, or Email =======================
void Dashboard::on_teacher_find_button_clicked()
{
    teacherSection->searchTeacher(ui->teacherid_lineEdit->text(),
                                  ui->teachername_lineEdit->text(),
                                  ui->teacheremail_lineEdit->text());
}

// ===================== Row Selection for Editing =========================
void Dashboard::on_teacher_table_row_selected(QTableWidgetItem *item)
{
    int row = item->row();  // Get the row index of the selected item

    // Get the values from the selected row in the teacher table
    QString teacherId = ui->teachertable_widget->item(row, 0)->text();
    QString teacherName = ui->teachertable_widget->item(row, 1)->text();
    QString teacherGrade = ui->teachertable_widget->item(row, 2)->text();
    QString teacherCourse = ui->teachertable_widget->item(row, 3)->text();
    QString teacherEmail = ui->teachertable_widget->item(row, 4)->text();
    QString teacherPhoneNo = ui->teachertable_widget->item(row, 5)->text();

    // Set the values in the UI fields for editing
    ui->teacherid_lineEdit->setText(teacherId);
    ui->teachername_lineEdit->setText(teacherName);
    ui->teachergrade_lineEdit->setText(teacherGrade);
    ui->teachercourse_lineEdit->setText(teacherCourse);
    ui->teacheremail_lineEdit->setText(teacherEmail);
    ui->teacherphoneno_lineEdit->setText(teacherPhoneNo);
}


//-------------------------------------------course section----------------------------------------------------

// ====================== Add Course Button Click =========================
void Dashboard::on_course_add_button_clicked()
{
    // Add course logic
    courseSection->addCourse(ui->courseid_lineEdit->text(),
                               ui->coursename_lineEdit->text(),
                               ui->courseassign_lineEdit->text());

    totalCourses++;
   updateTotalCourseCountLabel();

    // Clear course input fields after adding
    ui->courseid_lineEdit->clear();
    ui->coursename_lineEdit->clear();
    ui->courseassign_lineEdit->clear();

}

// ====================== Update course Information =========================
void Dashboard::on_course_update_button_clicked()
{
    int row = ui->coursetable_widget->currentRow();  // Get the current row of the selected item
    if (row != -1) {
        // Show confirmation dialog
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Update Confirmation",
                                      "Are you sure you want to update this Course's details?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            courseSection->updateCourse(row,
                                         ui->courseid_lineEdit->text(),
                                         ui->coursename_lineEdit->text(),
                                         ui->courseassign_lineEdit->text());
        }
    } else {
        QMessageBox::warning(nullptr, "Update Error", "No course row selected.");
    }
}



// ===================== Delete course Row =========================
void Dashboard::on_course_delete_button_clicked()
{
    int row = ui->coursetable_widget->currentRow();
    if (row != -1) {
        // Show a confirmation dialog
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Delete Confirmation",
                                      "Are you sure you want to delete this course?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            // Proceed with deletion if user confirmed
            courseSection->deleteCourse(row);
            totalCourses--;
            updateTotalCourseCountLabel();
        }
    } else {
        QMessageBox::warning(nullptr, "Delete Error", "No course row selected.");
    }
}

// =================== Find course by ID, Name =======================
void Dashboard::on_course_find_button_clicked()
{
    courseSection->searchCourse(ui->courseid_lineEdit->text(),
                                  ui->coursename_lineEdit->text(),
                                ui->courseassign_lineEdit->text());

}

// ===================== Row Selection for Editing =========================
void Dashboard::on_course_table_row_selected(QTableWidgetItem *item)
{
    int row = item->row();  // Get the row index of the selected item

    // Get the values from the selected row in the teacher table
    QString courseId = ui->coursetable_widget->item(row, 0)->text();
    QString courseName = ui->coursetable_widget->item(row, 1)->text();
    QString courseassign = ui->coursetable_widget->item(row, 2)->text();


    // Set the values in the UI fields for editing
    ui->courseid_lineEdit->setText(courseId);
    ui->coursename_lineEdit->setText(courseName);
    ui->courseassign_lineEdit->setText(courseassign);

}



void Dashboard::on_logout_button_clicked()
{

    // Close the current Dashboard window
      this->close();

      // Create and show the AdminLogin window
      AdminLogin *adminLoginWindow = new AdminLogin();
      adminLoginWindow->show();

}
