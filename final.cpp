#include "final.h"
#include <iostream>



final::final(EndingOption option, char win_mes[10], char loose_mes[10])
{
    gameEndType = option;
    strcopy(winMessage, win_mes);
    strcopy(looseMessage, loose_mes);
}

final::final()
{
    gameEndType = WinGame;
    strcopy(winMessage, "You WIN!");
    strcopy(looseMessage, "You Loose");
}

final::~final()
{
}


int final::changeType(EndingOption option)
{
    gameEndType = option;
    return 0;
}

int final::outputFinal()
{
    if (gameEndType == WinGame)
        std::cout << '\n' << winMessage << '\n' << std::endl;
    if (gameEndType == LooseGame)
        std::cout << '\n' << looseMessage << '\n' << std::endl;
    return 0;
}
