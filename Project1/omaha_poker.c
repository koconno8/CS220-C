#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "omaha_poker.h"

/* TODO: TASK 1 (1 point) : Define 2 global instances of struct player--one for each player */
struct player player1;
struct player player2;

/* Parse card from a 2 char input */
struct card parse(const char *card)
{
	return parse_ref(card); 
	/* TODO: TASK 2 (10 points): Implement this function. 
	 * The function accepts a 2-character array called card (e.g., 'AH')
	 * Create an instance of struct card and populate it with the correct enum values based on the input chars value and suit.
	 * return the card */
	/* Hint: Use a switch statement to get the value from card[0] and another switch statement to get suit from card[1] */
	struct card c;
    switch (card[0]) {
        case '2': c.val = TWO; break;
        case '3': c.val = THREE; break;
        case '4': c.val = FOUR; break;
        case '5': c.val = FIVE; break;
        case '6': c.val = SIX; break;
        case '7': c.val = SEVEN; break;
        case '8': c.val = EIGHT; break;
        case '9': c.val = NINE; break;
        case 'T': c.val = TEN; break;
        case 'J': c.val = JACK; break;
        case 'Q': c.val = QUEEN; break;
        case 'K': c.val = KING; break;
        case 'A': c.val = ACE; break;
        default: c.val = ONE; // Dummy value
	}
	switch (card[1]){
        case 'C': c.suit = CLUB; break;
        case 'D': c.suit = DIAMOND; break;
        case 'H': c.suit = HEART; break;
        case 'S': c.suit = SPADE; break;
        default: c.suit = CLUB; // Dummy suit
    }
}

			/* Count the number of occurrences of each card 2 through Ace */
			void count_cards(struct hand *h)
			{
				//return count_cards_ref(h); //
				/* TODO: TASK 3 (6 points): Implement this function
				* The function accepts a pointer to a hand that has its cards already setup.
				* This function must iterate through the cards in the hand and count the number of times
				* a card appears, and update the counter for that card */
				
				for (int i = 0; i < 5; i++) {
					h->card_count[h->cards[i].val - 1]++;
    			}
			}

			int is_flush(struct hand *h)
			{
				return is_flush_ref(h); 

				/* TODO: TASK 4 (6 points): Implement this function.
				* Return 1 if suits of all 5 cards in the hand are the same, else return 0 */
				for (int i = 1; i < 5; i++) {
					if (h->cards[i].suit != h->cards[0].suit) {
						return 0; // Not a flush
        			}
    			}
				return 1;
			}

			int is_straight(struct hand *h)
			{
				return is_straight_ref(h); 

				/* TODO: TASK 5 (10 points): Implement this function. 
				* Return 1 if the 5 cards in the hand form a sequence, else return 0
				NOTE: You must handle the exception for A2345, where A is not 1 but 13 */

				/* HINT: The card_count in the hand structure contains the number of times 
				* each card value appears in the hand. See if 5 consecutive cards have a card_count value of 1 */
				int consecutive = 0;

				// Check for A-2-3-4-5 straight
				if (h->card_count[ACE - 1] && h->card_count[TWO - 1] &&
					h->card_count[THREE - 1] && h->card_count[FOUR - 1] &&
					h->card_count[FIVE - 1]) {
					return 1;
				}

				// Check for other straights
				for (int i = 0; i < 13; i++) {
					if (h->card_count[i] > 0) {
						consecutive++;
						if (consecutive == 5) {
							return 1; // Found a straight
						}
					} 
					else 
					{
						consecutive = 0;
					}
				}

				return 0; // Not a straight
			}

			int is_straight_flush(struct hand *h)
			{
				return is_straight_flush_ref(h); 

				/* TODO: TASK 6 (1 point): Implement this function.
				* Return 1 if the hand is a straight and a flush, else return 0. 
				* HINT: Use the already implemented functions for flush and straight */
				if (is_flush(h) && is_straight(h)) {
					return 1; // Straight flush
				}
				return 0;
			}
					

			/* This function print's a hand. Useful in debugging */
			void print_hand(struct hand *h)
			{
				for(int i = 0; i < 5; i++) {
					printf("%d%d ", h->cards[i].val, h->cards[i].suit);
				}
			}


			/* This is the main function that converts the player's hand into weighted unsigned long number. 
			It is a 56bit vector as shown below (2 is the LSB and StraightFlush is the MSB) */
			/* 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K, A, 22, 33, 44, 55, 66, 77, 88, 99, TT, JJ, QQ, KK, AA,
			222, 333, 444, 555, 666, 777, 888, 999, TTT, JJJ, QQQ, KKK, AAA, Straight, Flush, FullHouse, 2222, 3333, 
			4444, 5555, 6666, 7777, 8888, 9999, TTTT, JJJJ, QQQQ, KKKK, AAAA, StraightFlush */
			/* The number of occurrences of each number in the hand is first calculated in count_cards. 
			Then, depending on the number of occurrences, the corresponding bit in the bit-vector is set. 
			In order to find the winner, a simple comparison of the bit vectors (i.e., unsigned long integers) will suffice! */
			void eval_strength(struct hand *h)
			{
				return eval_strength_ref(h); 
				/* TODO: TASK 7 (25 points): Implement this function.
				* Given a hand, iterate through the cards and use the BIT macros to set the appropriate bit in the hand vector */

				h->vector = 0;

				// Set bits based on the number of occurrences of each card value
				for (int i = 0; i < 13; i++) 
				{
					if (h->card_count[i] > 0) 
					{
						h->vector |= BIT(i);
					}
				}

				// Check for flush and straight
				if (is_straight_flush(h)) 
				{
					h->vector |= BIT(49); // StraightFlush
				} else if (is_flush(h)) 
				{
					h->vector |= BIT(48); // Flush
				} else if (is_straight(h)) 
				{
					h->vector |= BIT(47); // Straight
				}
			}


			void eval_players_best_hand(struct player *p)
			{
				return eval_players_best_hand_ref(p); 
				/* TODO: TASK 8 (10 points): Implement this function. 
				* For each possible hand the player can make, evaluate the strength of the hand (by calling eval_strength).
				* Then, set the best_hand vector for the player to point to the strongest hand.
				*/
				
				p->best_hand = &p->hands[0];
				for (int i = 1; i < MAX_COMBINATIONS; i++) 
				{
					if (p->hands[i].vector > p->best_hand->vector) 
					{
						p->best_hand = &p->hands[i];
					}
				}
			}

			void copy_card(struct card *dst, struct card *src)
			{
				return copy_card_ref(dst, src); 
				/* TODO: TASK 9 (3 points): Implement this function. 
				* copy the value and suit from the src card to the dst card. 
				*/
				dst->val = src->val;
				dst->suit = src->suit;
			}


			void initialize_player_omaha(struct player *p, struct card *player_cards, struct card *community_cards)
			{
				return initialize_player_omaha_ref(p, player_cards, community_cards);

				/* TODO: TASK 10 (25 points): Given the player cards and the community cards, initialize the array of hands in the player structure. 
				* There are a total of MAX_COMBINATIONS number of possible hands that the player can make.
				* Initialize each of the MAX_COMBINATIONS number of hands with different 5 card combinations. 
				* Use the copy_card function.
				*/
				/* HINT: Start by zeroing out the player instance. Then, copy each unique combination into a hand in the hands array. 
				* For example: P1 P2 C1 C2 C3 is one possible combination (i.e., first 2 cards of the player and first 3 cards from community cards). 
				* So, copy player_cards[0] into hands[0].cards[0], player_cards[1] into hands[0].cards[1], community_cards[0] into hands[0].cards[2], 
				* community_cards[1] into hands[0].cards[3] and community_cards[2] into hands[0].cards[4]. Repeat this process for each possible combination
				* such as P1 P2 C1 C2 C4, P3 P4 C1 C2 C3, etc. 
				* Implement helper functions as necessary. */
				int p1, p2, c1, c2, c3;
				int i = 0;

				// Zero out the player instance
				memset(p, 0, sizeof(struct player));

				// Initialize hands with different 5-card combinations
				for (p1 = 0; p1 < 4; p1++) {
					for (p2 = p1 + 1; p2 < 4; p2++) {
						for (c1 = 0; c1 < 5; c1++) {
							for (c2 = c1 + 1; c2 < 5; c2++) {
								for (c3 = c2 + 1; c3 < 5; c3++) {
									copy_card(&p->hands[i].cards[0], &player_cards[p1]);
									copy_card(&p->hands[i].cards[1], &player_cards[p2]);
									copy_card(&p->hands[i].cards[2], &community_cards[c1]);
									copy_card(&p->hands[i].cards[3], &community_cards[c2]);
									copy_card(&p->hands[i].cards[4], &community_cards[c3]);

									// Count cards in the hand
									count_cards(&p->hands[i]);

									// Evaluate hand strength
									eval_strength(&p->hands[i]);

									i++;
								}
							}
						}
					}
				}
			}

			/* Parse each hand in the input file, evaluate the strengths of hands and identify a winner by comparing the weighted vectors */
			void process_input_omaha(FILE *fp)
			{
				return process_input_omaha_ref(fp); 

				char p1[4][3];
				char p2[4][3];
				char comm[5][3];
				struct card p1_cards[4], p2_cards[4], community_cards[5];
				int i;

				while(fscanf(fp, "%s %s %s %s %s %s %s %s %s %s %s %s %s", 
					&p1[0][0], &p1[1][0], &p1[2][0], &p1[3][0], &p2[0][0], &p2[1][0], &p2[2][0], &p2[3][0], 
					&comm[0][0], &comm[1][0], &comm[2][0], &comm[3][0], &comm[4][0]) == 13) {

					memset(p1_cards, 0, sizeof(struct card) * 4);
					memset(p2_cards, 0, sizeof(struct card) * 4); 
					memset(community_cards, 0, sizeof(struct card) * 5);

					for(i = 0; i < 4; i++) {
						p1_cards[i] = parse(&p1[i][0]);
						p2_cards[i] = parse(&p2[i][0]);
					}

					for(i = 0; i < 5; i++) 
						community_cards[i] = parse(&comm[i][0]);

					/* TODO: TASK 11 (1 point): Initialize each player with p1_cards and community_cards by calling initialize_player_omaha */
					initialize_player_omaha(&player1, p1_cards, community_cards);

					/* TODO: TASK 12 (1 point): Evaluate the best hand for a player by calling eval_players_best_hand */
					initialize_player_omaha(&player2, p2_cards, community_cards);

					/* TODO: TASK 13 (1 point): Depending on who has the stronger hand, print the winner. 
					* If both have the same strong hand, print "No single winner" */
					eval_players_best_hand(&player1);
					eval_players_best_hand(&player2);
					if (player1.best_hand->vector > player2.best_hand->vector) \
					{
						printf("Player 1 wins\n");
					} 
					else if (player2.best_hand->vector > player1.best_hand->vector) 
					{
						printf("Player 2 wins\n");
					} 
					else 
					{
						printf("No single winner\n");
					}	

				}
			}

			int main(int argc, char *argv[])
			{
				FILE *fp;

				if(argc != 2 || (fp = fopen(argv[1], "r")) == NULL) {
					printf("Unable to open input file\n");
					exit(-1);
				}
				
				process_input_omaha(fp);

				return 0;
			}
	