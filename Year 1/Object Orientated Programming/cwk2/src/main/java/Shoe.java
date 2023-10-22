// TODO: Implement the Shoe class in this file

import java.util.Collections;

public class Shoe extends CardCollection {

    public Shoe(int decks) throws CardException {
        if (decks != 6 && decks != 8) {
            throw new CardException("Invalid number of decks provided");
        }
        
        for (int deckNo = 0; deckNo < decks; deckNo++) {
            for (Card.Suit suit : Card.Suit.values()) {
                for (Card.Rank rank : Card.Rank.values()) {
                    this.add(new BaccaratCard(rank, suit));
                }
            }
        }
    } 


    public void shuffle() {
        Collections.shuffle(cards);
    }

    public Card deal() throws CardException {
        if (isEmpty()) {
            throw new CardException("Shoe is empty");
        }

        Card cardToDeal = cards.get(0);
        cards.remove(0);
        return cardToDeal;
    }
}