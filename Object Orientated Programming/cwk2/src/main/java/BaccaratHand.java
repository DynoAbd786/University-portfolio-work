// TODO: Implement the BaccaratHand class in the file

public class BaccaratHand extends CardCollection {

    public BaccaratHand() {
        super();
    }
    
    public String toString() {
        String cardsString = "";
        int cardCounter = 0;
        for (Card card : cards) {
            String cardName = card.toString();

            if (cardCounter == 0) {
                cardsString = cardName;
            }
            else if (cardCounter < cards.size()) {
                cardsString = cardsString + " " + cardName;
            }

            cardCounter++;
        }

        return cardsString;
    }

    @Override
    public int value() {
        return (super.value() % 10);
    }

    public Boolean isNatural() {
        int cardValueTotal = this.value();       

        if ((cardValueTotal == 8 || cardValueTotal == 9) && this.size() == 2) {
            return true;
        }

        return false;
    }
}
