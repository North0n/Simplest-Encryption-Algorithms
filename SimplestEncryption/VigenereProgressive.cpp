#include "VigenereProgressive.h"

#include <QMessageBox>

QString alphabet{"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"};

QString VigenereProgressive::encrypt(const QString &plaintext, const QString &key)
{
    _key = filterStr(key, isRuLetter);
    if (_key == "") {
        QMessageBox::warning(nullptr, "Неверный ключ", "Ключ должен содержать хотя бы один допустимый символ");
        return "";
    }
    _plaintext = filterStr(plaintext, isRuLetter);
    _plaintext = _plaintext.toUpper();
    _key = _key.toUpper();

    QString ciphertext;
    ciphertext.reserve(plaintext.length());
    for (int i = 0; i < _plaintext.length(); ++i) {
        ciphertext.push_back(getSubstitutionEnc(_plaintext[i], _key[i % _key.length()], i / _key.length()));
    }

    QString result = addInvalidChars(ciphertext, plaintext, isRuLetter);
    return result;
}

QString VigenereProgressive::decrypt(const QString &plaintext, const QString &key)
{
    _key = filterStr(key, isRuLetter);
    if (_key == "") {
        QMessageBox::warning(nullptr, "Неверный ключ", "Ключ должен содержать хотя бы один допустимый символ");
        return "";
    }
    _plaintext = filterStr(plaintext, isRuLetter);
    _plaintext = _plaintext.toUpper();
    _key = _key.toUpper();

    QString ciphertext;
    ciphertext.reserve(plaintext.length());
    for (int i = 0; i < _plaintext.length(); ++i) {
        ciphertext.push_back(getSubstitutionDec(_plaintext[i], _key[i % _key.length()], i / _key.length()));
    }

    QString result = addInvalidChars(ciphertext, plaintext, isRuLetter);
    return result;
}

QChar VigenereProgressive::getSubstitutionDec(const QChar &symbol, const QChar &keySymbol, int level)
{
    return ::alphabet[(::alphabet.length() + ::alphabet.indexOf(symbol) - (::alphabet.indexOf(keySymbol) + level) % ::alphabet.length()) % (::alphabet.length())];
}

QChar VigenereProgressive::getSubstitutionEnc(const QChar &symbol, const QChar &keySymbol, int level)
{
    return ::alphabet[(::alphabet.indexOf(symbol) + (::alphabet.indexOf(keySymbol) + level) % ::alphabet.length()) % (::alphabet.length())];
}
