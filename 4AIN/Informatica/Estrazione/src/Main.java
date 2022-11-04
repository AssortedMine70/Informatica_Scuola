public class Main {
    public static void main(String[] args) {
        Pool estrattore = new Pool(10, 0, 10);
        System.out.println(estrattore);
        System.out.println(estrattore.estrai() + " " + estrattore.estrai());
        System.out.println(estrattore);
        System.out.println(estrattore.howManyOdds());
    }
}
