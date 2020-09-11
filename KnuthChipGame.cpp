// KnuthChipGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>

/*
2 players
starting pot at 1000 $ (N)

playerA starts, playerB follows
First player cannot take all chips in the first turn
otherwise the players can take up-to 2 times the amount that the other player took on the previous turn
player must take at least one chip
player who takes the last chip wins the game
*/

//PlayerA has turn at even numbers, playerB has turn at uneven
size_t playerTurnCounter = 0;
size_t chips = 1000;
size_t limitingBid = 999;


void makeMove()
{
    using namespace std;
    static bool firstRound = true;
    size_t taken = 0;
    if (firstRound)
    {
        firstRound = false;
        taken = (floor(1 / 3.0 * chips));
        limitingBid = 2 * taken;
        chips -= taken;
        cout << "player " << playerTurnCounter << " took " << taken << " amount of chips, ";
        cout << "limitingBid was valued at " << limitingBid << " , remaining pot is valued at " << chips << endl;
    }
    else
    {

        for (size_t proposal = limitingBid;; proposal--)
        {
            if(proposal >= chips)
            {
                taken = chips;
                limitingBid = chips;
                chips = 0;
                cout << "player " << playerTurnCounter << " took " << limitingBid << " amount of chips, ";
                cout << "limitingBid was valued at " << limitingBid << " , remaining pot is valued at " << chips << endl;

                return;
            }
            else if( chips - proposal > (2*proposal) )
            {
                //seems to work, but check also for getting the final win by taking all chips in one turn
                taken = proposal;
                limitingBid = 2 * taken;
                chips -= taken;
                cout << "player " << playerTurnCounter << " took " << taken << " amount of chips, ";
                cout << "limitingBid was valued at " << limitingBid << " , remaining pot is valued at " << chips << endl;

                return;
            }
        }
    }
}


int main()
{
    using namespace std;
    cout << "Hello World! Welcome to Donald Knuth chipgame\n";

    for (; chips > 0;) 
    {
        if (playerTurnCounter == 0)
        {
            makeMove();
            playerTurnCounter++;
        }
        else
        {
            size_t humantake = 50000;
            while(humantake > limitingBid)
            {
                cout << "make your choice human!: ";
                cin >> humantake;
            }
            chips -= humantake;
            limitingBid = 2 * humantake;
            cout << endl << "you took " << humantake << " chips from the pot, there remains "
                << chips << " amount of chips in the pot, limitingBid is valued at " << limitingBid << endl;
            playerTurnCounter--;
        }  
    }
}
