#include "IEncryptor.h"

#include <algorithm>

QString IEncryptor::filterStr(const QString &text, const std::function<bool(const QChar &)> &filter)
{
    QString myPlaintext;
    myPlaintext.reserve(text.length());
    for (const QChar& symbol : text)
        if (filter(symbol))
            myPlaintext.append(symbol);
    return myPlaintext;
}

bool IEncryptor::isRuLetter(const QChar &symbol)
{
    return ((symbol >= L'а' && symbol <= L'я') || (symbol >= L'А' && symbol <= L'Я') || symbol == L'ё' || symbol == L'Ё');
}

bool IEncryptor::isEnLetter(const QChar &symbol)
{
    return (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z');
}

bool IEncryptor::isDigit(const QChar &symbol)
{
    return (symbol >= '0' && symbol <= '9');
}

QString IEncryptor::addInvalidChars(const QString &ciphertext, const QString &plaintext,
                        const std::function<bool(const QChar& symbol)> &validCheck)
{
    QString result;
    result.reserve(qMax(plaintext.length(), ciphertext.length()));
    for (int i = 0, j = 0; i < plaintext.length(); ++i)
        if (validCheck(plaintext[i]))
            result.push_back(ciphertext[j++]);
        else
            result.push_back(plaintext[i]);

    int validLength = static_cast<int>(std::count_if(plaintext.begin(), plaintext.end(), validCheck));
    result.push_back(ciphertext.right(ciphertext.length() - validLength));

    return result;
}
