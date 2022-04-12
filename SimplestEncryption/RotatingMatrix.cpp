#include "RotatingMatrix.h"

#include <algorithm>
#include <QStringList>

QString RotatingMatrix::encrypt(const QString &plaintext, const QString &key)
{
    Q_UNUSED(key);
    _plaintext = filterStr(plaintext, isEnLetter);
    _notches = {
            {0, 0},
            {1, 3},
            {2, 2},
            {3, 1}
    };
    QString ciphertext;
    ciphertext.reserve(_plaintext.length());

    // Заполнение матрицы
    int index = 0;
    int blocksCount = (int)_plaintext.length() / _blockSize;
    for (int i = 0; i <= blocksCount; ++i)
    {
        QStringList matrix(_matrixSize, QString(_matrixSize, 'x'));
        for (int j = 0; j < 4; ++j)
        {
            std::sort(_notches.begin(), _notches.end(),
                      [](const QPoint &point1, const QPoint &point2)
                      { return point1.x() < point2.x(); });
            for (int k = 0; k < _notches.length() && index < _plaintext.length(); ++k)
                matrix[_notches[k].x()][_notches[k].y()] = _plaintext[index++];
            rotateNotchesRight();
        }
        ciphertext.push_back(matrix.join(""));
    }

    QString result = addInvalidChars(ciphertext, plaintext, isEnLetter);
    return result;
}

QString RotatingMatrix::decrypt(const QString &plaintext, const QString &key)
{
    Q_UNUSED(key);
    _plaintext = filterStr(plaintext, isEnLetter);
    _notches = {
            {0, 0},
            {1, 3},
            {2, 2},
            {3, 1}
    };
    QString ciphertext;
    ciphertext.reserve(_plaintext.length());

    // Заполнение матрицы
    int index = 0;
    int blocksCount = (int)_plaintext.length() / _blockSize;
    for (int i = 0; i <= blocksCount; ++i)
    {
        QStringList matrix(_matrixSize, QString(_matrixSize, 'x'));
        int elementsCount = (i != blocksCount) ? _blockSize : ((int)_plaintext.length() % _blockSize);
        for (int j = 0; j < elementsCount; ++j) {
            matrix[j / _matrixSize][j % _matrixSize] = _plaintext[index++];
        }
        for (int j = 0; j < elementsCount; ++j) {
            ciphertext.push_back(matrix[_notches[j % 4].x()][_notches[j % 4].y()]);
            if (j % 4 == 3) {
                rotateNotchesRight();
                std::sort(_notches.begin(), _notches.end(),
                          [](const QPoint &point1, const QPoint &point2)
                          { return point1.x() < point2.x(); });
            }
        }
    }
    QString result = addInvalidChars(ciphertext, plaintext, isEnLetter);
    return result;
}

void RotatingMatrix::rotateNotchesRight()
{
    for (auto & point : _notches) {
        point = QPoint(point.y(), _matrixSize - point.x() - 1);
    }
}
