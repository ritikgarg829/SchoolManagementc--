#ifndef TEACHER_H
#define TEACHER_H

#include <QObject>
#include <QTableWidget>

class TeacherSection : public QObject
{
    Q_OBJECT

public:
    explicit TeacherSection(QTableWidget *tableWidget, QObject *parent = nullptr);

    // Add Teacher
    void addTeacher(const QString &id, const QString &name, const QString &grade,
                    const QString &course, const QString &email, const QString &phone,
                    const QString &gender);

    // Update Teacher
    void updateTeacher(int row, const QString &id, const QString &name, const QString &grade,
                       const QString &course, const QString &email, const QString &phone,
                       const QString &gender);

    // Delete Teacher
    void deleteTeacher(int row);

    // Search Teacher by ID, Name, or Email
    void searchTeacher(const QString &id, const QString &name, const QString &email);

private:
    QTableWidget *teacherTableWidget;  // Pointer to the table widget for teachers
};

#endif // TEACHER_H
