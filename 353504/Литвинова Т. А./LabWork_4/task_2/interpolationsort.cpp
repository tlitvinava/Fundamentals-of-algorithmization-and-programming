/*#include "interpolationsort.h"

void InterpolationSort::sort(QVector<int>& array)
{
    int n = array.size();
    for (int i = 0; i < n; ++i)
    {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
        //qDebug() << array;
    }
    foundIndex = 0; // Замените на индекс найденного элемента
}

int InterpolationSort::getFoundIndex() const
{
    return foundIndex;
}
*/
#include "interpolationsort.h"
#include <QTextEdit>

void InterpolationSort::sort(QVector<int>& array, QTextEdit* textEdit, int& i)
{
    int n = array.size();
    if(i < n) {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;

        QString sortedArray = "";
        for(int k = 0; k < array.size(); k++) {
            sortedArray += QString::number(array[k]) + " ";
        }
        textEdit->append("Массив после шага " + QString::number(i+1) + ": " + sortedArray);
    }
    foundIndex = 0; // Замените на индекс найденного элемента
}

int InterpolationSort::getFoundIndex() const
{
    return foundIndex;
}
