#ifndef SIMPLE_ENCRYPTION_CLION_VIGENEREPROGRESSIVE_H
#define SIMPLE_ENCRYPTION_CLION_VIGENEREPROGRESSIVE_H

#include "IEncryptor.h"

class VigenereProgressive : public IEncryptor
{
public:
    QString encrypt(const QString &plaintext, const QString &key) override;
    QString decrypt(const QString &plaintext, const QString &key) override;
    QChar getSubstitutionEnc(const QChar &symbol, const QChar &keySymbol, int level = 0);
    QChar getSubstitutionDec(const QChar &symbol, const QChar &keySymbol, int level = 0);

private:
    QString _plaintext;
    QString _key;
    static QString alphabet;
};


#endif //SIMPLE_ENCRYPTION_CLION_VIGENEREPROGRESSIVE_H
