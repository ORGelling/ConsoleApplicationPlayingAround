/* 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <random>

using namespace std;

struct Card {
    string name;
    int value;
};

// Utility function that builds a deck and returns a dynamically allocated array
Card* generateDeck(int numDecks, int& outTotalCards) {
    const char* suits[] = { "H", "D", "C", "S" };
    const char* values[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
    int points[] = { 2,3,4,5,6,7,8,9,10,10,10,10,10 };

    outTotalCards = 52 * numDecks;
    Card* newDeck = new Card[outTotalCards];
    int index = 0;

    for (int d = 0; d < numDecks; ++d) {
        for (int s = 0; s < 4; ++s) {
            for (int v = 0; v < 13; ++v) {
                newDeck[index].name = string(values[v]) + suits[s];
                newDeck[index].value = points[v];
                ++index;
            }
        }
    }

    return newDeck;
}

class Deck {
private:
    Card* deck;
    int totalCards;
    int currentIndex;
    int cutPoint;
    int numDecks;
    mt19937 rng;

public:
    Deck(int numDecks = 6) {
        this->numDecks = numDecks;
        rng.seed(static_cast<unsigned int>(time(nullptr)));
        deck = generateDeck(numDecks, totalCards);
        shuffleDeck();
        burnCards();
    }

    ~Deck() {
        delete[] deck;
    }

    void shuffleDeck() {
        for (int i = totalCards - 1; i > 0; --i) {
            uniform_int_distribution<int> dist(0, i);
            int j = dist(rng);
            swap(deck[i], deck[j]);
        }
        currentIndex = 0;

        // Cut point between 70% - 80% for added realism
        uniform_int_distribution<int> cutDist(70, 80);
        int cutPercentage = cutDist(rng);
        cutPoint = totalCards * cutPercentage / 100;
    }

    void burnCards() {
        uniform_int_distribution<int> dist(1, 5);
        int burnCount = dist(rng);
        currentIndex += burnCount;
        // Burn cards are not shown to players in real casinos
    }

    Card drawCard() {
        if (currentIndex == cutPoint - 1) {
            cout << "[Dealer] Last hand before shuffle.\n";
        }

        if (currentIndex >= cutPoint) {
            cout << "[Casino] Cut card reached. Reshuffling...\n";
            delete[] deck;
            deck = generateDeck(numDecks, totalCards);
            shuffleDeck();
            burnCards();
        }

        return deck[currentIndex++];
    }

    int cardsLeft() const {
        return totalCards - currentIndex;
    }

    void printDeckState() const {
        cout << "[Deck] " << cardsLeft() << " cards left (cut point at " << cutPoint << ").\n";
    }
};

int main() {
    Deck deck(6); // 6-deck casino shoe

    for (int i = 0; i < 260; ++i) {
        Card c = deck.drawCard();
        cout << "Draw " << i + 1 << ": " << c.name << " (" << c.value << ")\n";
        if ((i + 1) % 52 == 0) deck.printDeckState();
    }

    return 0;
}
*/