// BlackJack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
using namespace std;

class BlackJackGameSim {
public:
    std::vector<int> hand;
    std::vector<int> house;
    std::vector<int> Deck;
    bool noDrawHand = false, noDrawHouse = false, gameEnd = false;
    int handwin, housewin,draw, ace = 1;
    void CreateDeck() 
    {
        for (int o = 0; o <= 4; o++) // build without aces 
        {
            int cardNumber = 2;
            for (int i = 0; i <= 11; i++)
            {
                if (cardNumber > 10)
                {
                    cardNumber = 10;
                }
                Deck.push_back(cardNumber);
                cardNumber++;
            }
        }

        for (int e = 0; e <= 4; e++)
        {
            Deck.push_back(11); // add aces as 11
        }
    }

    void ShuffleDeck() {
        srand(time(NULL));
        std::random_shuffle(Deck.begin(), Deck.end());
    }

    void resetValues() {
        noDrawHand = false;
        noDrawHouse = false;
        gameEnd = false;
        hand.clear();
        house.clear();
        Deck.clear();
    }

    void PlayGame() {
        resetValues();
        CreateDeck();
        ShuffleDeck();
        DealFirstCards();
        
        while (gameEnd == false)
        {
            shouldIdraw();
        }
        printResults();
    }
    
    void DealFirstCards() {
        house.push_back(AddtoHandAndRemoveFromDeck());

        hand.push_back(AddtoHandAndRemoveFromDeck());

        house.push_back(AddtoHandAndRemoveFromDeck());

        hand.push_back(AddtoHandAndRemoveFromDeck());
    }

    int AddtoHandAndRemoveFromDeck() {
        int deckLastCard = Deck.back();
        Deck.pop_back();
        return deckLastCard;
    }

    int aceCheckHand(int total) {
        if (std::count(hand.begin(), hand.end(), ace)) {
            if (total + 10 < 21)
            {
                total += 10;
            }
        }
        return total;
    }

    int aceCheckHouse(int total) {
        if (std::count(house.begin(), house.end(), ace)) {
            if (total + 10 < 21)
            {
                total += 10;
            }
        }
        return total;
    }

    void shouldIdraw() {
        int totalinHand = 0;
        int totalinHouse = 0;
        int ace = 1;

        
        for (size_t i = 0; i < hand.size(); i++)
        {
            totalinHand += hand.at(i);
        }
        for (size_t h = 0; h < house.size(); h++)
        {
            totalinHouse += house.at(h);
        }

        aceCheckHand(totalinHand);
        if (totalinHand < 17 && totalinHand != 10)
        {
            HandDraw();
            totalinHand = 0;
            for (size_t x = 0; x < hand.size(); x++)
            {
                totalinHand += hand.at(x);
            }

        }
        else
        {
            noDrawHand = true;
        }

        aceCheckHouse(totalinHouse);
        if (totalinHouse < 17)
        {
            HouseDraw();
            totalinHouse = 0;
            for (size_t y = 0; y < house.size(); y++)
            {
                totalinHouse += house.at(y);
            }
        }
        else
        {
            noDrawHouse = true;
        }



        if (totalinHand == 21 && totalinHouse != 21)
        {
            handwin++;
            gameEnd = true;     //hand win 21
            return;
        }
        else if (totalinHand != 21 && totalinHouse == 21)
        {
            handwin++;
            gameEnd = true;     //house win 21
            return;
        }
        if (totalinHand != 21 && totalinHouse != 21)
        {
            if (totalinHand > totalinHouse && totalinHand <21)
            {
                handwin++;
                gameEnd = true; // hand win !=21
                return;
            }
            else if((totalinHand < totalinHouse && totalinHouse < 21))
            {
                housewin++;
                gameEnd = true; // house win !=21
                return;
            }
        }

        
        if (totalinHand == totalinHouse || totalinHand >21 && totalinHouse >21)//draw
        {
            draw++;
            gameEnd = true;
            return;
        }
        else if (totalinHand > 21 )// lose bust
        {
            housewin++;
            gameEnd = true;
            return;
        }
        else if (totalinHouse > 21)// lose bust
        {
            handwin++;
            gameEnd = true;
            return;
        }
    }

    void HandDraw() {
        hand.push_back(AddtoHandAndRemoveFromDeck());
    }
    
    void HouseDraw() {
        house.push_back(AddtoHandAndRemoveFromDeck());
    }

    void CheckWin() {
        int totalinHand = 0;
        int totalinHouse = 0;

        for (size_t i = 0; i < hand.size(); i++)
        {
            totalinHand += hand.at(i);
        }
        for (size_t h = 0; h < house.size(); h++)
        {
            totalinHouse += hand.at(h);
        }
    }

    void printResults() {
        system("cls");
        cout << "Win/Loss/Draw from player"; 
        std::cout << endl;
        cout << handwin;
        std::cout << "/";
        cout << housewin;
        std::cout << "/";
        cout << draw;
    }
};
int main()
{
    BlackJackGameSim bj;
    for (int i = 0; i < 100; i++)
    {
        bj.PlayGame();
    }
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
