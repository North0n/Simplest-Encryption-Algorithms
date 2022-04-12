#ifndef SIMPLE_ENCRYPTION_CLION_IENCRYPTOR_H
#define SIMPLE_ENCRYPTION_CLION_IENCRYPTOR_H

#include <QString>
#include <functional>

class IEncryptor
{
public:
    virtual QString encrypt(const QString &plaintext, const QString &key) = 0;
    virtual QString decrypt(const QString &plaintext, const QString &key) = 0;
    virtual ~IEncryptor() = default;
protected:
    QString filterStr(const QString &text, const std::function<bool(const QChar& symbol)> &);
    QString addInvalidChars(const QString &ciphertext, const QString &plaintext,
                            const std::function<bool(const QChar& symbol)> &validCheck);
    static bool isRuLetter(const QChar &symbol);
    static bool isEnLetter(const QChar &symbol);
    static bool isDigit(const QChar &symbol);
};


#endif //SIMPLE_ENCRYPTION_CLION_IENCRYPTOR_H
