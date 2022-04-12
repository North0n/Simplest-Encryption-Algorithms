#include "RailwayFence.h"

#include <QMessageBox>

QString RailwayFence::encrypt(const QString &plaintext, const QString &key)
{
    // Фильтрация входных данных по допустимым символам
    QString parsedKey = filterStr(key, isDigit);
    _key = parsedKey != "" ? parsedKey.toInt() : 0;
    if (_key <= 0) {
        QMessageBox::warning(nullptr, "Неверный ключ", "Ключ должен быть больше нуля");
        return "";
    }
    if (_key == 1)
        return plaintext;
    _plaintext = filterStr(plaintext, isRuLetter);

    // Разбиение по рядам
    QVector<QString> rows(_key);
    for (auto &row : rows)
        row.reserve(_plaintext.length() / _key);
    int period = 2 * (_key - 1);
    int mod, row;
    for (int i = 0; i < _plaintext.length(); ++i) {
        mod = i % period;
        row = _key - 1 - qAbs(_key - 1 - mod);
        rows[row].push_back(_plaintext[i]);
    }

    // Создание шифротекста
    QString ciphertext;
    ciphertext.reserve(_plaintext.length());
    for (const auto& row : rows)
        ciphertext.push_back(row);

    QString result = addInvalidChars(ciphertext, plaintext, isRuLetter);

    return result;
}

QString RailwayFence::decrypt(const QString &plaintext, const QString &key)
{
    // Фильтрация входных данных по допустимым символам
    QString parsedKey = filterStr(key, isDigit);
    _key = parsedKey != "" ? parsedKey.toInt() : 0;
    if (_key <= 0) {
        QMessageBox::warning(nullptr, "Неверный ключ", "Ключ должен быть больше нуля");
        return "";
    }
    if (_key == 1)
        return plaintext;
    _plaintext = filterStr(plaintext, isRuLetter);

    // Определение длин рядов
    QVector<QString> rows(_key);
    int period = 2 * (_key - 1);
    int periodsCount = _plaintext.length() / period;
    rows[0].reserve(periodsCount + 1);
    rows[0].resize(periodsCount);
    rows[_key - 1].reserve(periodsCount + 1);
    rows[_key - 1].resize(periodsCount);
    for (int i = 1; i < _key - 1; ++i) {
        rows[i].reserve(2 * periodsCount + 1);
        rows[i].resize(2 * periodsCount);
    }
    int lettersLeft = _plaintext.length() % period;
    int index;
    for (int i = 0; i < lettersLeft; ++i) {
        index = _key - 1 - qAbs(_key - 1 - i);
        rows[index].resize(rows[index].length() + 1);
    }

    // Заполнение рядов задом наперёд
    index = 0;
    for (auto & row : rows)
        for (int j = row.length() - 1; j >= 0; --j)
            row[j] = _plaintext[index++];

    // Создание шифротекста
    QString ciphertext;
    ciphertext.reserve(_plaintext.length());
    int mod;
    for (int i = 0; i < _plaintext.length(); ++i) {
        mod = i % period;
        index = _key - 1 - qAbs(_key - 1 - mod);
        ciphertext.push_back(rows[index].back());
        rows[index].resize(rows[index].length() - 1);
    }

    // Добавление недопустимых символов
    QString result = addInvalidChars(ciphertext, plaintext, isRuLetter);

    return result;
}