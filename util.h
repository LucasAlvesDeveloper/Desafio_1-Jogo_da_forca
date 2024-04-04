#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <wchar.h>

bool isLetterInWord(wchar_t letter, const wchar_t* word);
void putLetterInWord(wchar_t letter, const wchar_t* word, wchar_t* guessedWord);

#endif