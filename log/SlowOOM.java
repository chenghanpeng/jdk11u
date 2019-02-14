import java.util.LinkedList;

public class SlowOOM {
    private static final LinkedList<String> strings = new LinkedList<>();
    public static void main(String[] args) throws Exception {
        int iteration = 0;
        while (true) {
            for (int i = 0; i < 100; i++) {
                for (int j = 0; j < 10; j++) {
                    strings.add(new String("String " + j));
                }
            }
            Thread.sleep(100);
        }
    }
}