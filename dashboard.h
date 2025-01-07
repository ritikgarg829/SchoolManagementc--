#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QComboBox>
#include "student.h"
#include "teacher.h"
#include "course.h"

namespace Ui {
class dashboardformWidget;
}

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

private slots:
    void updateClock();  // Updates the clock on the UI
    void onMenuChanged(int index);  // Handles menu changes

//--------------------------------------------------------------------------------------------------------------------
    void on_add_button_clicked();  // Called when Add button is clicked
    void on_update_button_clicked();  // Called when Update button is clicked
    void on_delete_button_clicked();  // Called when Delete button is clicked
    void on_find_button_clicked();  // Called when Find button is clicked

    // Called when a row in the table is selected
    void on_table_row_selected(QTableWidgetItem *item);
//-------------------------------------------------------------------------------------------------------------------
    // Teacher-related slot functions
    void on_teacher_add_button_clicked();  // Called when Add button in Teacher section is clicked
    void on_teacher_update_button_clicked();  // Called when Update button in Teacher section is clicked
    void on_teacher_delete_button_clicked();  // Called when Delete button in Teacher section is clicked
    void on_teacher_find_button_clicked();  // Called when Find button in Teacher section is clicked

    // Called when a row in the teacher table is selected
    void on_teacher_table_row_selected(QTableWidgetItem *item);  // Add this line
//--------------------------------------------------------------------------------------------------------------------


    void on_course_add_button_clicked();

    void on_course_update_button_clicked();

    void on_course_delete_button_clicked();

    void on_course_find_button_clicked();

     void on_course_table_row_selected(QTableWidgetItem *item);  // Add this line

//----------------------------------------------------------------------------------------------------
     void on_logout_button_clicked();

private:
    Ui::dashboardformWidget *ui;
    StudentSection *studentSection;  // Pointer to the StudentSection object for handling student data
    TeacherSection *teacherSection;  // Declare teacherSection pointer to handle teacher data
    CourseSection *courseSection;
    int totalStudents;
    int totalTeachers;
    int totalCourses;
    void updateTotalStudentCountLabel();
        void updateTotalCourseCountLabel();
        void updateTotalTeacherCountLabel();
};

#endif // DASHBOARD_H
