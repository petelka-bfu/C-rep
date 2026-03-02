#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>
#include <clocale>
#include <cstring>

using namespace std;

wstring utf8_to_wstring(const string& utf8_str) {
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(utf8_str);
}


string wstring_to_utf8(const wstring& wstr) {
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}


bool isRussianLetter(wchar_t c) {
    return (c >= L'А' && c <= L'Я') ||
        (c >= L'а' && c <= L'я') ||
        c == L'Ё' || c == L'ё';
}


bool isEnglishLetter(wchar_t c) {
    return (c >= L'A' && c <= L'Z') || (c >= L'a' && c <= L'z');
}


bool isAnyLetter(wchar_t c) {
    return isRussianLetter(c) || isEnglishLetter(c);
}


bool isDigitChar(wchar_t c) {
    return c >= L'0' && c <= L'9';
}


bool isLetterOrDigit(wchar_t c) {
    return isAnyLetter(c) || isDigitChar(c);
}


bool isVowel(wchar_t c) {
    wchar_t lower = c;
    if (c >= L'A' && c <= L'Z') {
        lower = c + 32;
    }
    else if (c >= L'А' && c <= L'Я') {
        lower = c + 32;
    }
    else if (c == L'Ё') {
        lower = L'ё';
    }

    if (lower == L'а' || lower == L'е' || lower == L'ё' ||
        lower == L'и' || lower == L'о' || lower == L'у' ||
        lower == L'ы' || lower == L'э' || lower == L'ю' || lower == L'я') {
        return true;
    }

    if (lower == L'a' || lower == L'e' || lower == L'i' ||
        lower == L'o' || lower == L'u' || lower == L'y') {
        return true;
    }

    return false;
}

bool isConsonant(wchar_t c) {
    if (!isAnyLetter(c)) {
        return false;
    }
    return !isVowel(c);
}

void printCharTable() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wcout.imbue(locale("ru_RU.UTF-8"));

    wcout << L"=== Таблица символов ===\n";

    wcout << L"\nРусский алфавит (заглавные):\n";
    int count = 0;
    for (wchar_t c = L'А'; c <= L'Я'; ++c) {
        wcout << c << L"/" << (int)c << L" ";
        count++;
        if (count % 6 == 0) wcout << L"\n";
    }
    wcout << L"Ё/" << (int)L'Ё' << L"\n";

    wcout << L"\nРусский алфавит (строчные):\n";
    count = 0;
    for (wchar_t c = L'а'; c <= L'я'; ++c) {
        wcout << c << L"/" << (int)c << L" ";
        count++;
        if (count % 6 == 0) wcout << L"\n";
    }
    wcout << L"ё/" << (int)L'ё' << L"\n";

    wcout << L"\nАнглийский алфавит (заглавные):\n";
    count = 0;
    for (wchar_t c = L'A'; c <= L'Z'; ++c) {
        wcout << c << L"/" << (int)c << L" ";
        count++;
        if (count % 8 == 0) wcout << L"\n";
    }

    wcout << L"\n\nАнглийский алфавит (строчные):\n";
    count = 0;
    for (wchar_t c = L'a'; c <= L'z'; ++c) {
        wcout << c << L"/" << (int)c << L" ";
        count++;
        if (count % 8 == 0) wcout << L"\n";
    }

    wcout << L"\n\nЦифры:\n";
    for (wchar_t c = L'0'; c <= L'9'; ++c) {
        wcout << c << L"/" << (int)c << L" ";
    }


    wcout << L"\n\nЗнаки препинания:\n";
    const wchar_t* punct = L".,!?;:-()\"'";
    for (int i = 0; punct[i] != L'\0'; ++i) {
        wcout << punct[i] << L"/" << (int)punct[i] << L" ";
    }

    wcout << L"\n\n========================\n";
}

// Функция для чтения строки из файла
bool readLineFromFile(ifstream& file, char* buffer, int max_len) {
    if (!file) return false;

    int pos = 0;
    char ch;

    while (pos < max_len - 1 && file.get(ch)) {
        if (ch == '\n') {
            break;
        }
        buffer[pos++] = ch;
    }
    buffer[pos] = '\0';

    return pos > 0;
}

void task1() {
    const int MAX_LEN = 101;

    setlocale(LC_ALL, "ru_RU.UTF-8");
    wcout.imbue(locale("ru_RU.UTF-8"));

    ifstream input_file("input.txt");
    if (!input_file) {
        wcerr << L"Ошибка: файл input.txt не найден\n";
        return;
    }

    char str_utf8[MAX_LEN];
    if (!readLineFromFile(input_file, str_utf8, MAX_LEN)) {
        wcerr << L"Ошибка чтения строки из файла\n";
        input_file.close();
        return;
    }

    wstring str = utf8_to_wstring(str_utf8);
    wcout << L"Строка из файла: " << str << endl;

    wstring result;
    for (wchar_t c : str) {
        if (!isConsonant(c)) {
            result += c;
        }
    }

    wcout << L"Результат после удаления согласных: " << result << L"\n\n";

    input_file.close();
}

struct WordInfo {
    wchar_t word[256];
    int length;
};

// Проверка на запр слово
bool containsLettersFrom(const wchar_t* word, const wchar_t* forbidden) {
    for (int i = 0; word[i] != L'\0'; ++i) {
        if (!isAnyLetter(word[i])) continue;

        wchar_t lower_word = word[i];
        if (word[i] >= L'A' && word[i] <= L'Z') {
            lower_word = word[i] + 32;
        }
        else if (word[i] >= L'А' && word[i] <= L'Я') {
            lower_word = word[i] + 32;
        }
        else if (word[i] == L'Ё') {
            lower_word = L'ё';
        }

        for (int j = 0; forbidden[j] != L'\0'; ++j) {
            if (!isAnyLetter(forbidden[j])) continue;

            wchar_t lower_forbidden = forbidden[j];
            if (forbidden[j] >= L'A' && forbidden[j] <= L'Z') {
                lower_forbidden = forbidden[j] + 32;
            }
            else if (forbidden[j] >= L'А' && forbidden[j] <= L'Я') {
                lower_forbidden = forbidden[j] + 32;
            }
            else if (forbidden[j] == L'Ё') {
                lower_forbidden = L'ё';
            }

            if (lower_forbidden == lower_word) {
                return true;
            }
        }
    }
    return false;
}

// Очистка по краям
void cleanWord(const wchar_t* src, wchar_t* dest) {
    int len = 0;
    while (src[len] != L'\0') {
        len++;
    }

    int start = 0, end = len - 1;

    while (start < len && !isAnyLetter(src[start]) && !isDigitChar(src[start])) {
        start++;
    }

    while (end >= start && !isAnyLetter(src[end])) {
        end--;
    }

    if (start > end) {
        dest[0] = L'\0';
        return;
    }

    int j = 0;
    for (int i = start; i <= end; ++i) {
        wchar_t c = src[i];

        if (c >= L'A' && c <= L'Z') {
            c = c + 32; //ангийские заглавыне
        }
        else if (c >= L'А' && c <= L'Я') {
            c = c + 32; // русские заглавные 
        }
        else if (c == L'Ё') {
            c = L'ё';
        }

        dest[j++] = c;
    }
    dest[j] = L'\0';
}

void copyWString(wchar_t* dest, const wchar_t* src) {
    int i = 0;
    while (src[i] != L'\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = L'\0';
}

bool areWStringsEqual(const wchar_t* str1, const wchar_t* str2) {
    int i = 0;
    while (str1[i] != L'\0' && str2[i] != L'\0') {
        if (str1[i] != str2[i]) {
            return false;
        }
        i++;
    }
    return str1[i] == L'\0' && str2[i] == L'\0';
}

void task2() {
    const int MAX_WORDS = 500;        
    const int MAX_WORD_LEN = 128;      
    const int MAX_TEXT_LEN = 10000;    

    setlocale(LC_ALL, "ru_RU.UTF-8");
    wcout.imbue(locale("ru_RU.UTF-8"));

    // Открываем input.txt
    ifstream input_file("input.txt");
    if (!input_file) {
        wcerr << L"Ошибка: файл input.txt не найден\n";
        return;
    }

    // Пропускаем первую строку 
    char dummy_utf8[256];
    readLineFromFile(input_file, dummy_utf8, 256);

    readLineFromFile(input_file, dummy_utf8, 256);

    // Читаем N
    int N;
    input_file >> N;
    input_file.ignore();

    readLineFromFile(input_file, dummy_utf8, 256);

    // Читаем запрещенное слово
    char forbidden_utf8[256];
    if (!readLineFromFile(input_file, forbidden_utf8, 256)) {
        wcerr << L"Ошибка чтения запрещенного слова\n";
        input_file.close();
        return;
    }
    input_file.close();

    wstring forbidden_temp = utf8_to_wstring(forbidden_utf8);
    wchar_t forbidden_word[MAX_WORD_LEN];
    copyWString(forbidden_word, forbidden_temp.c_str());

    wcout << L"Задача 2: N = " << N << L", запрещенное слово = '" << forbidden_word << L"'\n";

    // Открываем text.txt
    ifstream text_file("text.txt");
    if (!text_file) {
        wcerr << L"Ошибка: файл text.txt не найден\n";
        return;
    }

    WordInfo words_array[MAX_WORDS];
    int word_count = 0;

    wchar_t current_word[MAX_WORD_LEN];
    int word_pos = 0;

    char ch_utf8;
    string utf8_buffer;

    while (text_file.get(ch_utf8)) {
        utf8_buffer += ch_utf8;
        try {
            wstring wch = utf8_to_wstring(utf8_buffer);
            if (wch.length() == 1) {
                wchar_t c = wch[0];

                if (isAnyLetter(c) || isDigitChar(c) || c == L'-' || c == L'\'') {
                    if (word_pos < MAX_WORD_LEN - 1) {
                        current_word[word_pos++] = c;
                    }
                }
                else {
                    if (word_pos > 0) {
                        current_word[word_pos] = L'\0';

                        wchar_t cleaned[MAX_WORD_LEN];
                        cleanWord(current_word, cleaned);

                        if (cleaned[0] != L'\0' && !containsLettersFrom(cleaned, forbidden_word)) {
                            // Проверяем уникальность
                            bool found = false;
                            for (int i = 0; i < word_count; ++i) {
                                if (areWStringsEqual(words_array[i].word, cleaned)) {
                                    found = true;
                                    break;
                                }
                            }

                            if (!found && word_count < MAX_WORDS) {
                                copyWString(words_array[word_count].word, cleaned);

                                int len = 0;
                                while (cleaned[len] != L'\0') {
                                    len++;
                                }
                                words_array[word_count].length = len;
                                word_count++;
                            }
                        }
                        word_pos = 0;
                    }
                }
                utf8_buffer.clear();
            }
        }
        catch (...) {
        }
    }

    if (word_pos > 0) {
        current_word[word_pos] = L'\0';

        wchar_t cleaned[MAX_WORD_LEN];
        cleanWord(current_word, cleaned);

        if (cleaned[0] != L'\0' && !containsLettersFrom(cleaned, forbidden_word)) {
            bool found = false;
            for (int i = 0; i < word_count; ++i) {
                if (areWStringsEqual(words_array[i].word, cleaned)) {
                    found = true;
                    break;
                }
            }

            if (!found && word_count < MAX_WORDS) {
                copyWString(words_array[word_count].word, cleaned);

                int len = 0;
                while (cleaned[len] != L'\0') {
                    len++;
                }
                words_array[word_count].length = len;
                word_count++;
            }
        }
    }

    text_file.close();

    wcout << L"Найдено уникальных слов без запрещенных букв: " << word_count << L"\n";

    // Сортировка пузырьком по убыванию длины
    for (int i = 0; i < word_count - 1; ++i) {
        for (int j = 0; j < word_count - i - 1; ++j) {
            if (words_array[j].length < words_array[j + 1].length) {
                WordInfo temp = words_array[j];
                words_array[j] = words_array[j + 1];
                words_array[j + 1] = temp;
            }
        }
    }

    // Запись результата
    ofstream result_file("result.txt");
    if (!result_file) {
        wcerr << L"Ошибка создания result.txt\n";
        return;
    }

    int limit = (N < word_count) ? N : word_count;
    for (int i = 0; i < limit; ++i) {
        wstring wword = words_array[i].word;
        string utf8_word = wstring_to_utf8(wword);
        result_file << utf8_word << "\n";
    }
    result_file.close();

    wcout << L"Результат записан в result.txt. Записано слов: " << limit << L"\n";

    // Вывод для отладки
    wcout << L"\nПервые " << limit << L" слов:\n";
    for (int i = 0; i < limit && i < 10; ++i) {
        wcout << L"  " << words_array[i].word << L" (длина: " << words_array[i].length << L")\n";
    }
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wcout.imbue(locale("ru_RU.UTF-8"));
    wcerr.imbue(locale("ru_RU.UTF-8"));
    printCharTable();
    task1();
    task2();

    return 0;
}