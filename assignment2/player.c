#include <stdio.h>
#include "player.h"


// Add a card to the player's hand
int add_card(struct player* target, struct card* new_card) {
    struct hand* thisHand = (struct hand*)malloc(sizeof(struct hand));

    if (thisHand == NULL) { 
    	return -1; 
    }

    // New hand with the newly added card
    thisHand->top = *new_card;
    thisHand->next = target->card_list;

    target->card_list = thisHand;

    check_add_book(target);

    return 0;
}


// Remove a card from the player's hand
int remove_card(struct player* target, struct card* old_card) {
    struct hand* front = target->card_list;
    struct hand* iterator = front;
    struct hand* previous = NULL;

    if (iterator == NULL) { 
    	return 1; 
    }

    // Check if the card was found
    while ((iterator->top.suit != old_card->suit) || (iterator->top.rank != old_card->rank))
    { 
        previous = iterator;              // Store point in last item
        iterator = iterator->next;        // Look at next item
        if (iterator == NULL)             // Check for end of
            return 1;                     // Did not find the item
    }

    // If card is found
    if (previous != NULL) {
      previous->next = iterator->next;  // Remove item
    }
    else {
      front = iterator->next;           // Set new item where the old one was
      target->card_list = front;
    }

    // Free the memory
    free(iterator);

    return 0;
}


// Check player's hand if their hand has multiple cards of the same rank for a book
char check_add_book(struct player* target) {
    struct hand* iterator = target->card_list;
    char curRank = '\0';
    int rankMatch = 0;
    while (iterator != NULL) {
        curRank = iterator->top.rank[0];
        rankMatch = checkNumRankMatching(target, curRank);

        // Cards with the same rank are removed
        if (rankMatch == 4) {
            int chkRank = 0;
            while (chkRank == 0) {
                struct card* matching = getMatchingRankCard(target, curRank);
                if (matching != NULL)
                    chkRank = remove_card(target, matching);
				else
    				chkRank = 1;
            }
            break;  // Break when done removing matching rank cards
        }
        iterator = iterator->next;
    }
    
    // Add the new rank to the book
    if (rankMatch == 4) {
    	addToBook(target, curRank);
		return curRank;
    }
    return '\0';
}


int search(struct player* target, char rank) {
    struct hand* front = target->card_list;
    struct hand* iterator = front;

    // List is empty
    if (iterator == NULL) { 
    	return 0; 
	} 

	// Check if card was found
    while (iterator->top.rank[0] != rank)
    {
        iterator = iterator->next;        // Look at next item
        if (iterator == NULL)             // Check if this is the end of the list
            return 0;                     // Did not find an item
    }
    return 1; // Card was found
}


// Transfer cards between the players
int transfer_cards(struct player* src, struct player* dest, char rank) {
    struct hand* iterator = src->card_list;
    int transfered = 0;
    while (iterator != NULL) {
        if (iterator->top.rank[0] == rank) {
            struct card* c = (struct card*)malloc(sizeof(struct card));  // Copy of source card next to pointer

            c->suit = iterator->top.suit;

            c->rank[0] = iterator->top.rank[0];
            c->rank[1] = iterator->top.rank[1];

            struct hand* copyNext = iterator->next;

            remove_card(src, &iterator->top);  // Add source card to destination once removed
            add_card(dest, c);
            iterator = copyNext;
            transferred++;
        } 
        else {
            iterator = iterator->next;
        }
    }
    return transferred;
}


// Game is over once a player has 7 books
int game_over(struct player* target) {
    int numBooks = numOfBooks(target);

    if (numBooks == 7) {
        return 1;
    }
    return 0;
}


// Reset the players books and hand
int reset_player(struct player* target) {
    while ( target->card_list != NULL) {
        remove_card( target, &target->card_list->top );
    }

    // Remove the player's books by setting them to null
    for (int n=0; n<7; n++) {
        target->book[n] = '\0';
    }
    return 0;
}


// Computer Player 2's Turn
char computer_play(struct player* target) {
    fprintf(stdout, "\nPlayer 2's turn, enter a Rank: %c ", target->card_list->top.rank[0]);
    return target->card_list->top.rank[0];
}

// User Player 1's Turn
char user_play(struct player* target) {
    char iRank;
    char inter = 'x';

    while (inter == 'x') {
        fprintf(stdout, "\nPlayer 1's turn, enter a Rank : ");
        scanf(" %c", &iRank);
        int output = search(target, iRank);

        if (output == 1) {
            inter = 'y';
        } else {
            fprintf(stdout, "\nError - must have at least one card from rank to play");
        }
    }
    return iRank;
}


// Print the player's hand
void printHand(struct player* target) {
    struct hand* iterator = target->card_list;

    while (iterator != NULL) {
        fprintf(stdout, "%c%c ", iterator->top.rank[0], iterator->top.suit);

        iterator = iterator->next;
    }
}


// Number of books a player has
int numOfBooks(struct player* target) {
    int numBooks = 0;

    for (int n=0; n<7; n++) {
        if (target->book[n] != '\0')  {
            numBooks++;
        }
    }
    return numBooks;
}


// Print the books
void printBooks(struct player* target) {
    for (int n=0; n<7; n++) {
        if (target->book[n] != '\0') {
            fprintf(stdout, " %c", target->book[n]);
        }
    }
}


// Add a book to the player's books
void addToBook(struct player* target, char rank) {
    for (int n=0; n<7; n++) {
        if (target->book[n] == '\0')  {
            target->book[n] = rank;
        	return;
        }
    }
}


// Check the rank matches
int checkNumRankMatching(struct player* target, char rank) {
    struct hand* iterator = target->card_list;
    int x = 0;

    while (iterator != NULL)
    {
        if (iterator->top.rank[0] == rank) {
            x++;
        }
        iterator = iterator->next;
    }
    return x;
}


// Get the matching card that is matching matching the rank
struct card* getMatchingRankCard(struct player* target, char rank) {
    struct hand* iterator = target->card_list;

    while (iterator != NULL)
    {
        if (iterator->top.rank[0] == rank) {
            return &iterator->top;
        }
        iterator = iterator->next; 
    }
    return NULL;
}