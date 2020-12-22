#include <stdio.h>
#include "deck.h"
#include "card.h"
#include "player.h"


// Shuffle the deck of 52 cards
int shuffle() {
    fprintf(stdout, "Shuffling deck... \n");
    resetDeck();

    // Shuffle the deck by swapping cards. The cards will swap with random indices
    for (int n=0; n<52; n++) {
        int index = rand() % 52;
        swapCard(&(deck_instance.list[n]), &(deck_instance.list[index]));
    }

    // Make the top card of the deck the first card
    deck_instance.top_card = 0;

    return 0;
}


// Deal the cards out to each player
int deal_player_cards(struct player* target) {

    // Hand out the top 7 cards to each player
    for (int n=0; n<7; n++) {
        add_card(target, next_card());
    }

    return 0;
}


// Instances of the cards and their espective ranks and suits
struct card* next_card( ) {
    struct card* c = (struct card*)malloc(sizeof(struct card));

    c->suit = deck_instance.list[deck_instance.top_card].suit;

    c->rank[0] = deck_instance.list[deck_instance.top_card].rank[0];
    c->rank[1] = deck_instance.list[deck_instance.top_card].rank[1];

    deck_instance.top_card++;

    return c;
}


// Total size of the deck
size_t deck_size( ) {
    // Total number of cards - top card = new deck size
    size_t decksize = 52 - deck_instance.top_card;

    return decksize;
}


// Reset the deck with 52 cards, 13 cards in each of the 4 suits
void resetDeck() {
    int n;
    int x=0;

    // Put the 13 cards of each suit in numerical/alphabetical order

    // Hearts (H)
    for (n=0; n<13; n++) {
        deck_instance.list[x].suit = 'H';

        deck_instance.list[x].rank[0] = getRank(n);
        deck_instance.list[x].rank[1] = '\0';

        x++;
    }

    // Diamonds (D) 
    for (n=0; n<13; n++) {
        deck_instance.list[x].suit = 'D';

        deck_instance.list[x].rank[0] = getRank(n);
        deck_instance.list[x].rank[1] = '\0';

        x++;
    }

    // Spades (S)
    for (n=0; n<13; n++) {
        deck_instance.list[x].suit = 'S';

        deck_instance.list[x].rank[0] = getRank(n);
        deck_instance.list[x].rank[1] = '\0';

        x++;
    }

    // Clubs (C)
    for (n=0; n<13; n++) {
        deck_instance.list[x].suit = 'C';

        deck_instance.list[x].rank[0] = getRank(n);
        deck_instance.list[x].rank[1] = '\0';

        x++;
    }
}


// Rank of each card.  Count will start at 0
char getRank(int count) {
    if (count == 0) {
        return 'A';
    } 
    else if (count == 1) {
        return '2';
    } 
    else if (count == 2) {
        return '3';
    } 
    else if (count == 3) {
        return '4';
    } 
    else if (count == 4) {
        return '5';
    } 
    else if (count == 5) {
        return '6';
    } 
    else if (count == 6) {
        return '7';
    } 
    else if (count == 7) {
        return '8';
    } 
    else if (count == 8) {
        return '9';
    } 
    else if (count == 9) {
        return 'T';
    } 
    else if (count == 10) {
        return 'J';
    } 
    else if (count == 11) {
        return 'Q';
    } 
    else {
        return 'K';
    }
}


// Swap the cards to shuffle
void swapCard(struct card *a,struct card *b) {
    struct card temp = *a;
    *a = *b;
    *b = temp;
}


// Print the deck
void printDeck() {
    for (int n=0; n<52; n++) {
        struct card c = deck_instance.list[n];

        fprintf(stdout, "card number %i ", n+1);
        fprintf(stdout, ": suit %c ", c.suit);
        fprintf(stdout, ": rank %c%c \n", c.rank[0], c.rank[1]);
    }
}