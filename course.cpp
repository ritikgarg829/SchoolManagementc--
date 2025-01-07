#include "course.h"
#include <QTableWidgetItem>
#include <QMessageBox>

CourseSection::CourseSection(QTableWidget *tableWidget, QObject *parent)
    : QObject(parent), courseTableWidget(tableWidget) {}

void CourseSection::addCourse(const QString &id, const QString &name, const QString &courseassign)
{
    int row = courseTableWidget->rowCount();  // Get the next available row
    courseTableWidget->insertRow(row);  // Insert a new row at the end of the table

    // Set the teacher data in the corresponding columns
    courseTableWidget->setItem(row, 0, new QTableWidgetItem(id));
    courseTableWidget->setItem(row, 1, new QTableWidgetItem(name));
    courseTableWidget->setItem(row, 2, new QTableWidgetItem(courseassign));
}

void CourseSection::updateCourse(int row, const QString &id, const QString &name, const QString &courseassign)
{
    // Update the teacher data in the selected row
    courseTableWidget->item(row, 0)->setText(id);
    courseTableWidget->item(row, 1)->setText(name);
    courseTableWidget->item(row, 2)->setText(courseassign);

}

void CourseSection::deleteCourse(int row)
{
    // Delete the teacher row from the table
    courseTableWidget->removeRow(row);
}

void CourseSection::searchCourse(const QString &id, const QString &name, const QString &courseassign)
{
    for (int row = 0; row < courseTableWidget->rowCount(); ++row) {
        bool match = true;

        if (!id.isEmpty() && courseTableWidget->item(row, 0)->text() != id) {
            match = false;
        }
        if (!name.isEmpty() && courseTableWidget->item(row, 1)->text() != name) {
            match = false;
        }

        if (match) {
            courseTableWidget->selectRow(row);  // Select the matching row
            return;
        }
    }

    // Show a message if no match found
    QMessageBox::information(nullptr, "Search Result", "No course  found matching the search criteria.");
}
