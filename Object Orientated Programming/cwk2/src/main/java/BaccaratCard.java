// TODO: Implement the BaccaratCard class in this file


public class BaccaratCard extends Card {
    
    public BaccaratCard(Rank r, Suit s) {
        super(r, s);
    }

    @Override
    public int value() {
        int cardValue = super.value();

        if (cardValue == 10) {
            cardValue = 0;
        }

        return cardValue;
    }
}