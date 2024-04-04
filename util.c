#include "util.h"

#include "words.h"

bool isLetterInWord(wchar_t letter, const wchar_t* word)
{
    if (wcschr(word, letter))
        return true;

    switch (letter)
    {
    case L'a':
        for (int j = 0; j < (sizeof(accentsWithA) / sizeof(accentsWithA[0])); j++)
            if (wcschr(word, *accentsWithA[j]))
                return true;
        break;
    case L'e':
        for (int j = 0; j < (sizeof(accentsWithE) / sizeof(accentsWithE[0])); j++)
            if (wcschr(word, *accentsWithE[j]))
                return true;
        break;
    case L'i':
        for (int j = 0; j < (sizeof(accentsWithI) / sizeof(accentsWithI[0])); j++)
            if (wcschr(word, *accentsWithI[j]))
                return true;
        break;
    case L'o':
        for (int j = 0; j < (sizeof(accentsWithO) / sizeof(accentsWithO[0])); j++)
            if (wcschr(word, *accentsWithO[j]))
                return true;
        break;
    case L'u':
        for (int j = 0; j < (sizeof(accentsWithU) / sizeof(accentsWithU[0])); j++)
            if (wcschr(word, *accentsWithU[j]))
                return true;
        break;
    case L'c':
        for (int j = 0; j < (sizeof(accentsWithC) / sizeof(accentsWithC[0])); j++)
            if (wcschr(word, *accentsWithC[j]))
                return true;
        break;
    default:
        break;
    }

    return false;
}

void putLetterInWord(wchar_t letter, const wchar_t* word, wchar_t* guessedWord)
{
    for (int i = 0; i < wcslen(word); i++)
    {
        if (word[i] == letter)
        {
            guessedWord[i] = letter;
            continue;
        }

        switch (letter)
        {
        case L'a':
            for (int j = 0; j < (sizeof(accentsWithA) / sizeof(accentsWithA[0])); j++)
            {
                if (word[i] == *accentsWithA[j])
                {
                    guessedWord[i] = word[i];
                    break;
                }
            }
            break;

        case L'e':
            for (int j = 0; j < (sizeof(accentsWithE) / sizeof(accentsWithE[0])); j++)
            {
                if (word[i] == *accentsWithE[j])
                {
                    guessedWord[i] = word[i];
                    break;
                }
            }
            break;
        case L'i':
            for (int j = 0; j < (sizeof(accentsWithI) / sizeof(accentsWithI[0])); j++)
            {
                if (word[i] == *accentsWithI[j])
                {
                    guessedWord[i] = word[i];
                    break;
                }
            }
            break;
        case L'o':
            for (int j = 0; j < (sizeof(accentsWithO) / sizeof(accentsWithO[0])); j++)
            {
                if (word[i] == *accentsWithO[j])
                {
                    guessedWord[i] = word[i];
                    break;
                }
            }
            break;
        case L'u':
            for (int j = 0; j < (sizeof(accentsWithU) / sizeof(accentsWithU[0])); j++)
            {
                if (word[i] == *accentsWithU[j])
                {
                    guessedWord[i] = word[i];
                    break;
                }
            }
            break;
        case L'c':
            for (int j = 0; j < (sizeof(accentsWithC) / sizeof(accentsWithC[0])); j++)
            {
                if (word[i] == *accentsWithC[j])
                {
                    guessedWord[i] = word[i];
                    break;
                }
            }
            break;
        default:
            break;
        }
    }
}