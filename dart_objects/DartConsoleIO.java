package dart_objects;

public class DartConsoleIO {
    private DartConsoleIO() {}

    public static void print(DartObject object) {
        System.out.println(object);
    }
}