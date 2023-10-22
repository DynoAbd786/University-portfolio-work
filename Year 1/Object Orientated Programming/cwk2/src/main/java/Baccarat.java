import java.util.Scanner;

public class Baccarat {
    private static int roundCounter = 0;
    private static int playerWins = 0;
    private static int bankerWins = 0;
    private static int ties = 0;

    private static final Scanner scanner = new Scanner(System.in);
    private static final int MIN_REQUIRED_SHOE_SIZE = 6;

    // TODO: Implement your Baccarat simulation program here
    public static void main(String[] args) {
        boolean interactive = false;
        if ((args.length == 1)) {
            if (args[0].equals("-i") || args[0].equals("--interactive")) {
                interactive = true;
            }
        }

        Shoe shoe = null;
        try {
            shoe = new Shoe(6);
        } catch (CardException e) {
            System.err.println("incorrect number of decks");
        }

        shoe.shuffle();

        while (shoe.size() >= MIN_REQUIRED_SHOE_SIZE) {
            System.out.println("Round " + (roundCounter + 1));
            roundCounter++;

            BaccaratHand banker = new BaccaratHand();
            BaccaratHand player = new BaccaratHand();

            for (int i = 0; i < 2; i++) {
                try {
                    banker.add(shoe.deal());
                } catch (CardException e) {
                    System.err.println("No more cards to deal");
                }

                try {
                    player.add(shoe.deal());
                } catch (CardException e) {
                    System.err.println("No more cards to deal");
                }
            }

            System.out.println("Player: " + player.toString() + " = " + player.value());
            System.out.println("Banker: " + banker.toString() + " = " + banker.value());

            if (player.isNatural() && banker.isNatural()) {
                System.out.println("Tie");
                ties++;
                System.out.println();
                if (interactive && !shouldContinue()) {
                    break;
                }
                continue;
            } else if (banker.isNatural()) {
                System.out.println("Banker has a Natural");
                System.out.println("Banker win!");
                bankerWins++;
                System.out.println();
                if (interactive && !shouldContinue()) {
                    break;
                }
                continue;
            } else if (player.isNatural()) {
                System.out.println("Player has a Natural");
                System.out.println("Player win!");
                playerWins++;
                System.out.println();
                if (interactive && !shouldContinue()) {
                    break;
                }
                continue;
            }

            Boolean thirdCardFlagPlayer = false;
            Card thirdCard = null;

            if (!(player.value() == 6 || player.value() == 7)) {
                System.out.println("Dealing third card to player...");

                try {
                    thirdCard = shoe.deal();
                } catch (CardException e) {
                    System.err.println("No more cards to deal");
                }
                player.add(thirdCard);
                System.out.println("Player: " + player.toString() + " = " + player.value());

                thirdCardFlagPlayer = true;
            }

            if (!(banker.value() == 6 || banker.value() == 7) && thirdCardFlagPlayer == false) {
                System.out.println("Dealing third card to banker...");
                banker.add(shoe.deal());
            } else if (thirdCardFlagPlayer == true && banker.value() != 7) {
                if (banker.value() >= 0 && banker.value() <= 2) {
                    System.out.println("Dealing third card to banker...");
                    banker.add(shoe.deal());
                } else if (banker.value() == 3 && thirdCard.value() == 8) {
                    System.out.println("Dealing third card to banker...");
                    banker.add(shoe.deal());
                } else if ((banker.value() == 4) && (thirdCard.value() >= 2 && thirdCard.value() <= 7)) {
                    System.out.println("Dealing third card to banker...");
                    banker.add(shoe.deal());
                } else if ((banker.value() == 5) && (thirdCard.value() >= 4 && thirdCard.value() <= 7)) {
                    System.out.println("Dealing third card to banker...");
                    banker.add(shoe.deal());
                } else if ((banker.value() == 6) && (thirdCard.value() >= 6 && thirdCard.value() <= 7)) {
                    System.out.println("Dealing third card to banker...");
                    banker.add(shoe.deal());
                }
            }

            System.out.println("Banker: " + banker.toString() + " = " + banker.value());

            if (banker.value() < player.value()) {
                System.out.println("Player win!");
                playerWins++;
            } else if (banker.value() > player.value()) {
                System.out.println("Banker win!");
                bankerWins++;
            } else {
                System.out.println("Tie");
                ties++;
            }

            System.out.println();

            if (interactive && !shouldContinue()) {
                break;
            }
        }

        System.out.println(roundCounter + " rounds played");
        System.out.println(playerWins + " player wins");
        System.out.println(bankerWins + " banker wins");
        System.out.println(ties + " ties");
    }

    public static Boolean shouldContinue() {
        System.out.print("Another round? (y/n): ");
        String input = scanner.nextLine().trim();
        System.out.println();
        if (input.length() > 0 && (input.charAt(0) == 'y' || input.charAt(0) == 'Y')) {
            return true;
        }
        return false;
    }
}
