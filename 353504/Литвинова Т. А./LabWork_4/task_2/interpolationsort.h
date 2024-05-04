#ifndef INTERPOLATIONSORT_H
#define INTERPOLATIONSORT_H

#include <QVector>
#include <QDebug>
#include <QTextEdit>

class InterpolationSort
{
public:
    void sort(QVector<int>& array);
    int getFoundIndex() const;
    void sort(QVector<int>& array, QTextEdit* textEdit, int& i);


private:
    int foundIndex = -1;
    //void sort(QVector<int>& array, QTextEdit* textEdit, int& i);

};

#endif // INTERPOLATIONSORT_H
