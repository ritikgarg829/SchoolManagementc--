#include "teacher.h"
#include <QTableWidgetItem>
#include <QMessageBox>

TeacherSection::TeacherSection(QTableWidget *tableWidget, QObject *parent)
    : QObject(parent), teacherTableWidget(tableWidget) {}

void TeacherSection::addTeacher(const QString &id, const QString &name, const QString &grade,
                                 const QString &course, const QString &email, const QString &phone,
                                 const QString &gender)
{
    int row = teacherTableWidget->rowCount();  // Get the next available row
    teacherTableWidget->insertRow(row);  // Insert a new row at the end of the table

    // Set the teacher data in the corresponding columns
    teacherTableWidget->setItem(row, 0, new QTableWidgetItem(id));
    teacherTableWidget->setItem(row, 1, new QTableWidgetItem(name));
    teacherTableWidget->setItem(row, 2, new QTableWidgetItem(grade));
    teacherTableWidget->setItem(row, 3, new QTableWidgetItem(course));
    teacherTableWidget->setItem(row, 4, new QTableWidgetItem(email));
    teacherTableWidget->setItem(row, 5, new QTableWidgetItem(phone));
    teacherTableWidget->setItem(row, 6, new QTableWidgetItem(gender));
}

void TeacherSection::updateTeacher(int row, const QString &id, const QString &name, const QString &grade,
                                    const QString &course, const QString &email, const QString &phone,
                                    const QString &gender)
{
    // Update the teacher data in the selected row
    teacherTableWidget->item(row, 0)->setText(id);
    teacherTableWidget->item(row, 1)->setText(name);
    teacherTableWidget->item(row, 2)->setText(grade);
    teacherTableWidget->item(row, 3)->setText(course);
    teacherTableWidget->item(row, 4)->setText(email);
    teacherTableWidget->item(row, 5)->setText(phone);
    teacherTableWidget->item(row, 6)->setText(gender);
}

void TeacherSection::deleteTeacher(int row)
{
    // Delete the teacher row from the table
    teacherTableWidget->removeRow(row);
}

void TeacherSection::searchTeacher(const QString &id, const QString &name, const QString &email)
{
    for (int row = 0; row < teacherTableWidget->rowCount(); ++row) {
        bool match = true;

        if (!id.isEmpty() && teacherTableWidget->item(row, 0)->text() != id) {
            match = false;
        }
        if (!name.isEmpty() && teacherTableWidget->item(row, 1)->text() != name) {
            match = false;
        }
        if (!email.isEmpty() && teacherTableWidget->item(row, 4)->text() != email) {
            match = false;
        }

        if (match) {
            teacherTableWidget->selectRow(row);  // Select the matching row
            return;
        }
    }

    // Show a message if no match found
    QMessageBox::information(nullptr, "Search Result", "No teacher found matching the search criteria.");
}
