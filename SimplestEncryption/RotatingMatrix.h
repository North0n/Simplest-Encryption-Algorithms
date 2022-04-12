#ifndef SIMPLE_ENCRYPTION_CLION_ROTATINGMATRIX_H
#define SIMPLE_ENCRYPTION_CLION_ROTATINGMATRIX_H

#include "IEncryptor.h"

#include <QPoint>
#include <QVector>

class RotatingMatrix : public IEncryptor
{
public:
    QString encrypt(const QString &plaintext, const QString &key) override;
    QString decrypt(const QString &plaintext, const QString &key) override;

private:
    QString _plaintext;
    QVector<QPoint> _notches = {
            {0, 0},
            {1, 3},
            {2, 2},
            {3, 1}
    };
    int _matrixSize = 4;
    int _blockSize = _matrixSize * _matrixSize;

    void rotateNotchesRight();
};

#endif //SIMPLE_ENCRYPTION_CLION_ROTATINGMATRIX_H
