#ifndef SIMPLE_ENCRYPTION_CLION_RAILWAYFENCE_H
#define SIMPLE_ENCRYPTION_CLION_RAILWAYFENCE_H

#include "IEncryptor.h"

class RailwayFence : public IEncryptor
{
public:
    QString encrypt(const QString &plaintext, const QString &key) override;
    QString decrypt(const QString &plaintext, const QString &key) override;

private:
    QString _plaintext;
    int _key;
};


#endif //SIMPLE_ENCRYPTION_CLION_RAILWAYFENCE_H
