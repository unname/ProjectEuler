#include <stdlib.h>
#include <iostream>
#include "windows.h"
#include <ctime>

#include "euler_functions.h"


// In the game, Monopoly, the standard board is set up in the following way:
//
//      |  GO  |  A1  |  CC1 |  A2  |  T1  |  R1  |  B1  |  CH1 |  B2  |  B3  | JAIL |
//
//      |  H2  |                                                              |  C1  |
//
//      |  T2  |                                                              |  U1  |
//
//      |  H1  |                                                              |  C2  |
//
//      |  CH3 |                                                              |  C3  |
//
//      |  R4  |                                                              |  R2  |
//
//      |  G3  |                                                              |  D1  |
//
//      |  CC3 |                                                              |  CC2 |
//
//      |  G2  |                                                              |  D2  |
//
//      |  G1  |                                                              |  D3  |
//
//      |  G2J |  F3  |  U2  |  F2  |  F1  |  R3  |  E3  |  E2  |  CH2 |  E1  |  FP  |
//
// A player starts on the GO square and adds the scores on two 6 - sided dice to determine the number of squares they advance in a clockwise direction.
// Without any further rules we would expect to visit each square with equal probability: 2.5%.
// However, landing on G2J(Go To Jail), CC(community chest), and CH(chance) changes this distribution.
//
// In addition to G2J, and one card from each of CC and CH, that orders the player to go directly to jail,
// if a player rolls three consecutive doubles, they do not advance the result of their 3rd roll.Instead they proceed directly to jail.
//
// At the beginning of the game, the CC and CH cards are shuffled.When a player lands on CC or CH they take a card from the top of the respective pile and,
// after following the instructions, it is returned to the bottom of the pile.There are sixteen cards in each pile, but for the purpose of this problem
// we are only concerned with cards that order a movement; any instruction not concerned with movement will be ignored and the player will remain on the CC / CH square.
//
//  Community Chest(2 / 16 cards) :
//      1.  Advance to GO
//      2.  Go to JAIL
//  Chance(10 / 16 cards) :
//      1.  Advance to GO
//      2.  Go to JAIL
//      3.  Go to C1
//      4.  Go to E3
//      5.  Go to H2
//      6.  Go to R1
//      7.  Go to next R(railway company)
//      8.  Go to next R
//      9.  Go to next U(utility company)
//      10. Go back 3 squares.
//
// The heart of this problem concerns the likelihood of visiting a particular square.That is, the probability of finishing at that square after a roll.
// For this reason it should be clear that, with the exception of G2J for which the probability of finishing on it is zero, 
// the CH squares will have the lowest probabilities, as 5 / 8 request a movement to another square, and it is the final square that the player 
// finishes at on each roll that we are interested in.We shall make no distinction between "Just Visiting" and being sent to JAIL,
// and we shall also ignore the rule about requiring a double to "get out of jail", assuming that they pay to get out on their next turn.
//
// By starting at GO and numbering the squares sequentially from 00 to 39 we can concatenate these two - digit numbers to produce strings that correspond with sets of squares.
//
// Statistically it can be shown that the three most popular squares, in order, are JAIL(6.24%) = Square 10, E3(3.18%) = Square 24, and GO(3.09%) = Square 00.
// So these three most popular squares can be listed with the six - digit modal string : 102400.
//
// If, instead of using two 6 - sided dice, two 4 - sided dice are used, find the six - digit modal string.

#define SQUARES     squares
#define IT          it

#define CH_IT       ch_it
#define CC_IT       cc_it

#define MOVE_COUNT      move_count
#define DOUBLES_COUNT   doubles_count

#define PREVIOUS_ODDS   previous_odds

#define SQUARES_SIZE    40
#define CHEST_SIZE      16
#define CHANCE_SIZE     16

#define GO      0
#define A1      1
#define CC1     2
#define A2      3
#define T1      4
#define R1      5
#define B1      6
#define CH1     7
#define B2      8
#define B3      9
#define JAIL    10
#define C1      11
#define U1      12
#define C2      13
#define C3      14
#define R2      15
#define D1      16
#define CC2     17
#define D2      18
#define D3      19
#define FP      20
#define E1      21
#define CH2     22
#define E2      23
#define E3      24
#define R3      25
#define F1      26
#define F2      27
#define U2      28
#define F3      29
#define G2J     30
#define G1      31
#define G2      32
#define CC3     33
#define G3      34
#define R4      35
#define CH3     36
#define H1      37
#define T2      38
#define H2      39

#define GoTo(x)     { IT = (x) % SQUARES_SIZE; SQUARES[IT]++; }

#define GoToGO      { SQUARES[IT]--; GoTo(GO)   }
#define GoToJAIL    { SQUARES[IT]--; GoTo(JAIL) }
#define GoToC1      { SQUARES[IT]--; GoTo(C1)   }
#define GoToE3      { SQUARES[IT]--; GoTo(E3)   }
#define GoToH2      { SQUARES[IT]--; GoTo(H2)   }
#define GoToR1      { SQUARES[IT]--; GoTo(R1)   }

#define GoToNextR   { SQUARES[IT]--;           \
                    if (IT < R1) GoTo(R1) else \
                    if (IT < R2) GoTo(R2) else \
                    if (IT < R3) GoTo(R3) else \
                    if (IT < R4) GoTo(R4) else \
                        GoTo(R1);               }

#define GoToNextU   { SQUARES[IT]--;           \
                    if (IT < U1) GoTo(U1) else \
                    if (IT < U2) GoTo(U2) else \
                         GoTo(U1);              }

#define GoBack(x)   { SQUARES[IT]--; if(IT >= x) GoTo(IT - x) else GoTo(SQUARES_SIZE - IT + x) }

#define DiceSides               4 
#define MAX_DOUBLES_COUNT       3

#define ThrowDice   rand() % DiceSides + 1

#define MakeMove    { size_t d1 = (size_t)ThrowDice; \
                      size_t d2 = (size_t)ThrowDice; \
                      if(d1 == d2) DOUBLES_COUNT++;  \
                        else DOUBLES_COUNT = 0;      \
                      GoTo(IT + d1 + d2);            \
                      MOVE_COUNT++;             }


static size_t ScreenOffset = 0;

void SetScreenOffset()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo = { 0 };
    GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);

    system("cls");

    ScreenOffset = 1;
}

void SetCarriege(size_t x, size_t y)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo = { 0 };
    GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);

    consoleInfo.dwCursorPosition.X = x;
    consoleInfo.dwCursorPosition.Y = ScreenOffset + y;

    SetConsoleCursorPosition(consoleHandle, consoleInfo.dwCursorPosition);
}

int main(int argc, char **argv)
{
    SetScreenOffset();

    srand(time(NULL));

    size_t MOVE_COUNT = 0;
    size_t DOUBLES_COUNT = 0;

    size_t IT = 0;
    size_t SQUARES[SQUARES_SIZE] = { 0 };
    size_t PREVIOUS_ODDS[SQUARES_SIZE] = { 0 };

    size_t CC_IT = 0;
    size_t CH_IT = 0;

    while (true)
    {
        MakeMove;

        if (DOUBLES_COUNT == MAX_DOUBLES_COUNT)
        {
            GoToJAIL;
            DOUBLES_COUNT = 0;
        }

        //CHANCE
        if (IT == CH1 || IT == CH2 || IT == CH3)
        {
            switch (CH_IT)
            {
            case 0:
                GoToGO;
                break;
            case 1:
                GoToJAIL
                    break;
            case 2:
                GoToC1;
                break;
            case 3:
                GoToE3;
                break;
            case 4:
                GoToH2;
                break;
            case 5:
                GoToR1;
                break;
            case 6:
                GoToNextR;
                break;
            case 7:
                GoToNextR;
                break;
            case 8:
                GoToNextU;
                break;
            case 9:
                GoBack(3);
                break;
            default:
                break;
            }

            CH_IT = (CH_IT + 1) % CHANCE_SIZE;
        }

        //COMMUNITY CHEST
        if (IT == CC1 || IT == CC2 || IT == CC3)
        {
            switch (CC_IT)
            {
            case 0:
                GoToGO;
                break;
            case 1:
                GoToJAIL;
                break;
            default:
                break;
            }

            CC_IT = (CC_IT + 1) % CHEST_SIZE;
        }

        //G2J
        if (IT == G2J)
            GoToJAIL;

        if (MOVE_COUNT && MOVE_COUNT % 1000 == 0)
        {
            SetCarriege(0, 0);

            printf("Move: %Iu * 1000\n\n", MOVE_COUNT / 1000);

            for (size_t i = 0; i < SQUARES_SIZE; ++i)
                printf("[ %Iu ] = %.2f\n", i, 100 * (float)SQUARES[i] / MOVE_COUNT);

            if (MOVE_COUNT > 1000)
            {
                bool stop = true;

                for (size_t i = 0; i < SQUARES_SIZE; ++i)
                    if (PREVIOUS_ODDS[i] != SQUARES[i] * 100 * 100 / MOVE_COUNT)
                        stop = false;

                if (stop)
                    break;

            }

            for (size_t i = 0; i < SQUARES_SIZE; ++i)
                PREVIOUS_ODDS[i] = SQUARES[i] * 100 * 100 / MOVE_COUNT;
        }
    }

    size_t max_value1 = 0;
    size_t max_value2 = 0;
    size_t max_value3 = 0;

    size_t max_index1 = 0;
    size_t max_index2 = 0;
    size_t max_index3 = 0;

    for (size_t i = 0; i < SQUARES_SIZE; ++i)
    {
        if (SQUARES[i] > max_value1)
        {
            max_value3 = max_value2;
            max_value2 = max_value1;
            max_value1 = SQUARES[i];

            max_index3 = max_index2;
            max_index2 = max_index1;
            max_index1 = i;
        }
        else
            if (SQUARES[i] > max_value2)
            {
                max_value3 = max_value2;
                max_value2 = SQUARES[i];

                max_index3 = max_index2;
                max_index2 = i;
            }
            else
                if (SQUARES[i] > max_value3)
                {
                    max_value3 = SQUARES[i];
                    max_index3 = i;
                }
    }

    printf("\nResult: ");

    if (max_index1)
        printf("%Iu", max_index1);
    else
        printf("00");

    if (max_index2)
        printf("%Iu", max_index2);
    else
        printf("00");

    if (max_index3)
        printf("%Iu", max_index3);
    else
        printf("00");

    printf("\n");

    return 0;
}