#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>

#include "hangmanParts.h"
#include "util.h"
#include "words.h"

int main(int argc, const char* argv[])
{
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    wprintf(L"JOGO DA FORCA!\n\n");

    sleep(3);

    wprintf(L"O objetivo do jogo é adivinhar a palavra secreta.\n");
    sleep(2);
    wprintf(L"Será que você consegue?\n\n");
    sleep(2);

    wprintf(L"P.S: Por favor não use teclas especiais como acentos, cedilha, etc. Caso a palavra tenha acentos, eles serão detectados automaticamente.\n\n");
    sleep(3);

    const wchar_t* word = words[rand() % (sizeof(words) / sizeof(words[0]))];
    wchar_t* guessedWord = calloc(wcslen(word), sizeof(wchar_t));

    wchar_t letter;
    int wrongGuesses = 0;
    wchar_t* usedLetters = calloc(26, sizeof(wchar_t)); // [a-z]

    bool guessWordMode = false;
    bool lostGame = false;
    bool wonGame = false;
    do
    {
        // Print hangman parts
        for (int i = wrongGuesses * 7; i < (wrongGuesses + 1) * 7; i++)
            wprintf(L"%s", hangmanParts[i]);

        wprintf(L"\n");

        wprintf(L"Número de tentativas restantes: %d\n\n", 6 - wrongGuesses);

        wprintf(L"Resposta: ");
        // Print guessed word
        for (int i = 0; i < wcslen(word); i++)
        {
            if (guessedWord[i] == 0)
                wprintf(L"_ ");
            else
                wprintf(L"%c ", guessedWord[i]);
        }
        wprintf(L"\n\n");

        wprintf(L"Letras usadas: %s\n\n", usedLetters);

        if (wcscmp(word, guessedWord) == 0)
            wonGame = true;

        if (wrongGuesses == 6)
            lostGame = true;

        // Get only valid character from user.
        if (!wonGame && !lostGame)
        {
            do
            {
                wprintf(L"Digite uma letra ou aperte enter para digitar a palavra: ");
                letter = fgetwc(stdin);
                if (letter == '\n')
                {
                    guessWordMode = true;
                    break;
                }
                fgetwc(stdin); // Consume newline (Enter)
            } while (letter == '\n' || isLetterInWord(letter, guessedWord) || wcschr(usedLetters, letter));
        }

        if (guessWordMode)
        {
            wprintf(L"Digite a palavra: ");
            wchar_t* answer = calloc(100, sizeof(wchar_t));
            fgetws(answer, 100, stdin);
            if (wcslen(answer) > 0)
                answer[wcslen(answer) - 1] = 0; // Remove newline character

            for (int i = 0; i < wcslen(answer); i++)
            {
                if (answer[i] == word[i])
                    continue;

                bool foundLetter = false;
                for (int j = 0; j < (sizeof(accents) / sizeof(accents[0])); j++)
                {
                    if (word[i] == *accents[j])
                    {
                        foundLetter = true;
                        break;
                    }
                }

                if (!foundLetter)
                {
                    lostGame = true;
                    break;
                }
            }

            if (!lostGame)
                wonGame = true;
            free(answer);
        }

        if (lostGame)
        {
            wprintf(L"\nVocê perdeu! A palavra correta era: %s\n", word);
            wprintf(L"Deseja jogar novamente? (s/n): ");
            wchar_t playAgain;
            do
            {
                playAgain = fgetwc(stdin);
                fgetc(stdin); // Consume newline (Enter)

                if (playAgain != L's' && playAgain != L'n')
                {
                    wprintf(L"Digite 's' para sim ou 'n' para não: ");
                    continue;
                }

                break;
            } while (true);

            if (playAgain == 's')
            {
                guessWordMode = false;
                lostGame = false;
                wonGame = false;
                wrongGuesses = 0;
                word = words[rand() % (sizeof(words) / sizeof(words[0]))];
                free(usedLetters);
                free(guessedWord);
                guessedWord = calloc(wcslen(word), sizeof(wchar_t));
                usedLetters = calloc(26, sizeof(wchar_t));
                wprintf(L"\n--------------------------------------------------------\n\n");
                continue;
            }

            break;
        }
        else if (wonGame)
        {
            wprintf(L"\nParabéns, você ganhou! A palavra correta era mesmo %s!\n", word);
            wprintf(L"Deseja jogar novamente? (s/n): ");
            wchar_t playAgain;
            do
            {
                playAgain = fgetwc(stdin);
                fgetc(stdin); // Consume newline (Enter)

                if (playAgain != L's' && playAgain != L'n')
                {
                    wprintf(L"Digite 's' para sim ou 'n' para não: ");
                    continue;
                }

                break;
            } while (true);

            if (playAgain == 's')
            {
                guessWordMode = false;
                lostGame = false;
                wonGame = false;
                wrongGuesses = 0;
                word = words[rand() % (sizeof(words) / sizeof(words[0]))];
                free(usedLetters);
                free(guessedWord);
                guessedWord = calloc(wcslen(word), sizeof(wchar_t));
                usedLetters = calloc(26, sizeof(wchar_t));
                wprintf(L"\n--------------------------------------------------------\n\n");
                continue;
            }

            break;
        }

        usedLetters[wcslen(usedLetters)] = letter;
        wprintf(L"\nA letra digitada foi: %c\n\n", letter);
        sleep(1);

        if (!isLetterInWord(letter, word))
        {
            wprintf(L"A letra %c não está na palavra!\n", letter);
            wrongGuesses++;
            sleep(1);
            wprintf(L"\n--------------------------------------------------------\n\n");
            continue;
        }

        wprintf(L"A letra %c está na palavra!\n", letter);
        putLetterInWord(letter, word, guessedWord);
        sleep(1);

        wprintf(L"\n--------------------------------------------------------\n\n");
    } while (true);

    free(guessedWord);

    wprintf(L"\nObrigado por jogar!!! \nPressione Enter para sair...");
    getchar();

    return 0;
}
