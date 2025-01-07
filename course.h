#ifndef COURSE_H
#define COURSE_H

#include "QObject"
#include "QTableWidget"


class CourseSection: public QObject
{
    Q_OBJECT

public:
    explicit CourseSection(QTableWidget *tableWidget, QObject *parent = nullptr);

    // Add Course
    void addCourse(const QString &id, const QString &name, const QString &courseassign);

    // Update course
    void updateCourse(int row, const QString &id, const QString &name, const QString &courseassign);

    // Delete course
    void deleteCourse(int row);

    // Search course by ID , Name
    void searchCourse(const QString &id, const QString &name, const QString &courseassign);

private:
    QTableWidget *courseTableWidget;  // Pointer to the table widget for Course
};

#endif // TEACHER_H

