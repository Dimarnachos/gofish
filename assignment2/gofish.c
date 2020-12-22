#include <stdio.h>
#include "deck.h"
#include "player.h"
#include "gofish.h"

int main(int args, char* argv[])
{
    char keepGoing = 'y';

    while (keepGoing == 'y' || keepGoing == 'Y') {
        // Clean up linklists for the players
        reset_player(&user);
        reset_player(&computer);

        // Shuffle the cards randomly after filling the deck
        shuffle();

        // Deal users the cards
        if (deal_player_cards(&user) != 0) {
            fprintf(stdout, "Error in dealing card to player1\n");
            return 1;
        }

        // Check booking for user
        check_add_book(&user);

        // Deal Player 2 cards
        if (deal_player_cards(&computer) != 0) {
            fprintf(stdout, "Error in dealing card to player2\n");
            return 1;
        }

        // Start the Turn
        char repeatTurn = 'y';

        while (repeatTurn == 'y') {
        
            // Player 1 Turn
            while (doPlayerOneTurn() == 1){};

            if ( game_over(&user) == 1) {
                fprintf(stdout, "\nPlayer 1 won the game!!!!");
                break;
            }

            // Player 2 Turn
            while (doPlayerTwoTurn() == 1){};

            if ( game_over(&computer) == 1) {
                fprintf(stdout, "\nPlayer 2 won the game!!!!");
                break;
            }
        }

        fprintf(stdout, "\n\nPlay another game ? : ");
        scanf(" %c", &keepGoing);
    }
    fprintf(stdout, "\nExiting\n");
}


// Player 1's Turn
int doPlayerOneTurn() {
        fprintf(stdout, "\nPlayer 1's hand :");
        printHand(&user);

        fprintf(stdout, "\nPlayer 1's book : ");
        printBooks(&user);
        	
        fprintf(stdout, "\nPlayer 2's book : ");
        printBooks(&computer);

        // Player 1's Turn
        char userRank = user_play(&user);

        // Check if Player 2 has the Player 1 rank
        int chkRank = search(&computer, userRank);
        if (chkRank != 1) {
            fprintf(stdout, "\n  -Player 2 has no %c's", userRank);

            // Add the next card in the deck to Player 1's Hand
            struct card* nextCard = next_card( );
            add_card(&user, nextCard);
            fprintf(stdout, "\n  -Go Fish, Player 1 draws %c%c", nextCard->rank[0], nextCard->suit);
	    fprintf(stdout, "\n  -Player 2's turn\n");

            return 0;
        } 
        else {
            // Give Player 2's cards to Player 1
            transfer_cards(&computer, &user, userRank);
            fprintf(stdout, "\n  -Player 1 gets another turn");

            return 1;
        }
}


// Player 2's Turn
int doPlayerTwoTurn() {
        fprintf(stdout, "\nPlayer 1's hand :");
        printHand(&user);

        fprintf(stdout, "\nPlayer 1's book : ");
        printBooks(&user);
        	
        fprintf(stdout, "\nPlayer 2's book : ");
        printBooks(&computer);

        // Player's 2 Turn
        char compRank = computer_play(&computer);

        // Check if the Player 1 has the Player 2 rank
        int chkRank = search(&user, compRank);
        if (chkRank != 1) {
            fprintf(stdout, "\n  -Player 1 has no %c", compRank);

            // Give Player 2 the next card in the deck
            struct card* nextCard = next_card( );
            add_card(&computer, nextCard);
            fprintf(stdout, "\n  -Go Fish, Player 2 draws %c%c", nextCard->rank[0], nextCard->suit);
            fprintf(stdout, "\n  -Player 1's turn\n");

            return 0;
        } 
        else {
            // transfer cards from player1 to player2
            transfer_cards(&user, &computer, compRank);

            return 1;
        }
}