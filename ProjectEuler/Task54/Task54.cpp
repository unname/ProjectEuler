#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"

// In the card game poker, a hand consists of five cards and are ranked, from lowest to highest, in the following way :
//
// High Card        : Highest value card.
// One Pair         : Two cards of the same value.
// Two Pairs        : Two different pairs.
// Three of a Kind  : Three cards of the same value.
// Straight         : All cards are consecutive values.
// Flush            : All cards of the same suit.
// Full House       : Three of a kind and a pair.
// Four of a Kind   : Four cards of the same value.
// Straight Flush   : All cards are consecutive values of same suit.
// Royal Flush      : Ten, Jack, Queen, King, Ace, in same suit.
//
// The cards are valued in the order :
// 2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.
//
// If two players have the same ranked hands then the rank made up of the highest value wins;
// for example, a pair of eights beats a pair of fives(see example 1 below).But if two ranks tie, for example,
// both players have a pair of queens, then highest cards in each hand are compared(see example 4 below);
// if the highest cards tie then the next highest cards are compared, and so on.
//
// Consider the following five hands dealt to two players :
//  Hand	 	Player 1	 	    Player 2	     Winner
//   1	 	5H 5C 6S 7S KD       2C 3S 8S 8D TD     Player 2
//           Pair of Fives       Pair of Eights
//
//   2	 	5D 8C 9S JS AC      2C 5C 7D 8S QH      Player 1
//         Highest card Ace    Highest card Queen
//
//   3	 	2D 9C AS AH AC      3D 6D 7D TD QD      Player 2
//           Three Aces       Flush with Diamonds
//
//   4	 	4D 6S 9H QH QC      3D 6D 7H QD QS      Player 1
//          Pair of Queens      Pair of Queens
//         Highest card Nine  Highest card Seven
//
//   5	 	2H 2D 4C 4D 4S      3C 3D 3S 9S 9D      Player 1
//            Full House          Full House
//          With Three Fours   With Three Threes
//
// The file, poker.txt, contains one-thousand random hands dealt to two players.
// Each line of the file contains ten cards(separated by a single space) : the first five are Player 1's cards and the last five are Player 2's cards.
// You can assume that all hands are valid(no invalid characters or repeated cards), each player's hand is in no specific order, and in each hand there is a clear winner.
//
// How many hands does Player 1 win ?

#define pair      1
#define two_pair  2
#define three     4
#define straight  8
#define flush     16
#define fullhouse 32
#define four      64
#define str_flush 128

#ifdef _WIN64
#define FILE_NAME "..\\..\\Task54\\p054_poker.txt"
#else
#define FILE_NAME "..\\Task54\\p054_poker.txt"
#endif
#define SEMICOLON ' '

int main(int argc, char **argv)
{
    // Читаем данные из файла
    size_t file_size = 0;

    read_file(FILE_NAME, NULL, &file_size);
    char* file_data = (char*)malloc(sizeof(char) * (file_size + 1));
    read_file(FILE_NAME, file_data, &file_size);
    file_data[file_size] = '\0';

    // Считаем количество элементов в файле
    size_t size = 0;
    for (size_t i = 0; i < file_size; ++i)
        if (file_data[i] == SEMICOLON || file_data[i] == '\n')
            size++;
    if (size)
        size++;

#ifdef _DEBUG
    printf("\nTotal cards: %Iu\n", size);
#endif

    //Помещаем элементы в массив
    size_t offset = 0;

    char** cards = (char**)malloc(sizeof(char*) * size);

    for (size_t i = 0; i < size; ++i)
    {
        cards[i] = (char*)malloc(sizeof(char) * 3);
        cards[i][0] = file_data[0 + offset];
        cards[i][1] = file_data[1 + offset];;
        cards[i][2] = '\0';
        
        offset += 3;
    }

    free(file_data);
    
    bool* wins = (bool*)malloc(sizeof(bool) * (size / 10));

    for (size_t hand = 0; hand < size / 10; ++hand)
    {
        const size_t max_cards = 13;
        
        size_t hands[max_cards][2] = { 0 };
        size_t player       = 0;
        
        unsigned char  combo[2];
        combo[0] = flush;
        combo[1] = flush;

        size_t top_cards[3][2] = { 0 };

        // Заполняем информацию о картах в текущей раздаче
        for(size_t i = 0; i < 10; ++i)
        {
            if (i % 10 > 4)
                player = 1;

            size_t card_value = cards[hand * 10 + i][0] - '0' - 2;

            switch (cards[hand * 10 + i][0])
            {
            case 'T':
                card_value = 8;
                break;
            case 'J':
                card_value = 9;
                break;
            case 'Q':
                card_value = 10;
                break;
            case 'K':
                card_value = 11;
                break;
            case 'A':
                card_value = 12;
                break;
            }

            hands[card_value][player]++;

            if (i)
                if (cards[i][1] != cards[i - 1][1])
                    combo[player] &= 0xFF - flush;
        }

        //Вычисляем комбинации
        for (player = 0; player < 2; ++player)
        {
            for (size_t c = 0; c < max_cards; ++c)
            {
                //Проверяем стрит (стрит флеш)
                if ((c < 9) && !(combo[player] & straight))
                {
                    for (size_t str = 0; str < 5; ++str)
                    {
                        combo[player] |= straight;

                        if (hands[c + str][player] != 1)
                        {
                            combo[player] &= 0xFF - straight;
                            break;
                        }
                    }

                    if (combo[player] & straight && combo[player]  & flush)
                        combo[player] |= str_flush;
                }

                switch (hands[c][player])
                {
                case 4:
                    combo[player] |= four;
                    top_cards[0][player] = c;
                    break;
                case 3:
                    combo[player] |= three;
                    top_cards[0][player] = c;

                    if (combo[player] & pair)
                    {
                        combo[player] |= fullhouse;
                    }

                    break;
                case 2:
                    if (combo[player] & pair)
                    {
                        combo[player] |= two_pair;
                        
                        if (c > top_cards[1][player])
                            top_cards[0][player] = c;
                        else
                        {
                            top_cards[0][player] = top_cards[1][player];
                            top_cards[1][player] = c;
                        }
                    }
                    else
                    {
                        combo[player] |= pair;
                        top_cards[1][player] = c;
                    }

                    if (combo[player] & three)
                    {
                        combo[player] |= fullhouse;
                    }

                    break;
                case 1:
                    if (c > top_cards[2][player])
                        top_cards[2][player] = c;
                    break;
                default:
                    break;
                }
            }
        }

        //Определяем победителя
        if (combo[0] == combo[1])
        {
            for (size_t val = 0; val < 3; ++val)
            {
                if (top_cards[val][0] > top_cards[val][1])
                {
                    wins[hand] = true;
                    break;
                }

                if (top_cards[val][0] < top_cards[val][1])
                {
                    wins[hand] = false;
                    break;
                }
            }
        }

        if (combo[0] > combo[1])
            wins[hand] = true;

        if (combo[0] < combo[1])
            wins[hand] = false;
    }

#ifdef _DEBUG
    printf("\n     Hand              Player1           Player2         Winner\n");

    for (size_t i = 0; i < size; ++i)
    {
        if (i % 10 == 0)
        {
            printf("\nCombination[%Iu]:", i / 10 + 1);

            for (size_t s = 0; s < get_digitsize(size / 10) - get_digitsize(i / 10 + 1); ++s)
                printf(" ");
        }

        printf(" %s", cards[i]);

        if (i % 10 == 4)
            printf("   ");

        if (i % 10 == 9)
            printf("        P%s", wins[i / 10] ? "1" : "2");
    }
    printf("\n");
#endif

    size_t result = 0;

    for (size_t i = 0; i < size / 10; ++i)
    {
        if (wins[i])
            result++;
    }

    printf("\nResult: %Iu\n", result);

    // Освобождение памяти
    free(wins);

    for (size_t i = 0; i < size; ++i)
    {
        free(cards[i]);
    }
    free(cards);

    return 0;
}
