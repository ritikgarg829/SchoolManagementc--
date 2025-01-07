#include "student.h"
#include <QTableWidgetItem>
#include <QMessageBox>

StudentSection::StudentSection(QTableWidget *tableWidget)
    : studentTable(tableWidget)
{
}

void StudentSection::addStudent(const QString &id, const QString &name, const QString &grade, const QString &studentclass ,
                                 const QString &address, const QString &rollNumber, const QString &gender)
{
    int rowCount = studentTable->rowCount();
    studentTable->insertRow(rowCount);

    studentTable->setItem(rowCount, 0, new QTableWidgetItem(id));        // ID column
    studentTable->setItem(rowCount, 1, new QTableWidgetItem(name));      // Name column
    studentTable->setItem(rowCount, 2, new QTableWidgetItem(studentclass));  // Class column
    studentTable->setItem(rowCount, 3, new QTableWidgetItem(grade));     // Grade column
    studentTable->setItem(rowCount, 4, new QTableWidgetItem(address));   // Address column
    studentTable->setItem(rowCount, 5, new QTableWidgetItem(rollNumber)); // Roll number column
    studentTable->setItem(rowCount, 6, new QTableWidgetItem(gender));    // Gender column
}

void StudentSection::updateStudent(int row, const QString &studentId, const QString &studentName,
                                    const QString &grade, const QString &address, const QString &studentclass ,
                                    const QString &rollNumber, const QString &gender)
{
    studentTable->item(row, 0)->setText(studentId);
    studentTable->item(row, 1)->setText(studentName);
    studentTable->item(row, 2)->setText(studentclass);
    studentTable->item(row, 3)->setText(grade);
    studentTable->item(row, 4)->setText(address);
    studentTable->item(row, 5)->setText(rollNumber);
    studentTable->item(row, 6)->setText(gender);
}

void StudentSection::deleteStudent(int row)
{
    if (row != -1) {
        studentTable->removeRow(row);
    } else {
        QMessageBox::warning(nullptr, "Delete Error", "No student row selected.");
    }
}

void StudentSection::searchStudent(const QString &studentId, const QString &studentName,
                                    const QString &rollNumber)
{
    bool found = false;

    for (int row = 0; row < studentTable->rowCount(); ++row) {
        bool matches = true;

        if (!studentId.isEmpty() && studentTable->item(row, 0)->text() != studentId) {
            matches = false;
        }
        if (!studentName.isEmpty() && studentTable->item(row, 1)->text() != studentName) {
            matches = false;
        }
        if (!rollNumber.isEmpty() && studentTable->item(row, 5)->text() != rollNumber) {
            matches = false;
        }

        if (matches) {
            studentTable->selectRow(row);
            found = true;
            break;
        }
    }

    if (!found) {
        QMessageBox::information(nullptr, "Search Result", "No student found matching the search criteria.");
    }
}
