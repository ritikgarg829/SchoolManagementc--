#ifndef STUDENTSECTION_H
#define STUDENTSECTION_H

#include <QTableWidget>

class StudentSection
{
public:
    StudentSection(QTableWidget *tableWidget);
    void addStudent(const QString &studentId, const QString &studentName,
                    const QString &grade, const QString &address,
                    const QString &rollNumber, const QString &studentclass , const QString &gender);

    void updateStudent(int row, const QString &studentId, const QString &studentName,
                       const QString &grade, const QString &address,
                       const QString &rollNumber, const QString &studentclass, const QString &gender);

    void deleteStudent(int row);
    void searchStudent(const QString &studentId, const QString &studentName,
                       const QString &rollNumber);

private:
    QTableWidget *studentTable;
};

#endif // STUDENTSECTION_H
