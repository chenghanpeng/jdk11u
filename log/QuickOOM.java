import java.util.LinkedList;

public class QuickOOM {
    private static final LinkedList<String> strings = new LinkedList<>();
    private static final LinkedList<int[]>  intArrayList = new LinkedList<>();
    private static int[] mediumObjBuffer;
    private static int[] mediumObjBufferInArray;
    private static int mediumObjSize = 1024 * 512 ; // 2MB
    private static int mediumObjSizeInArray = 1024 * 256 ; // 1MB
    private static int[] largeObjBuffer;
    private static int largeObjSize = 1024 * 1024 * 2 ; // 8MB
    
    public static void main(String[] args) throws Exception {
        int iteration = 0;
        
        while (true) {
            //small object, strong root
            for (int i = 0; i < 1000; i++) {
                   for (int j = 0; j < 100; j++) {
                            strings.add(new String("String " + i*1000+j));
                   }
             }
            //medium object, grabage
            for (int i = 0; i < 8; i++) {
                  for (int j = 0; j < 5; j++) {
                           mediumObjBuffer = new int[mediumObjSize];
                           mediumObjBufferInArray = new int[mediumObjSizeInArray];
                           intArrayList.add(mediumObjBufferInArray);
                  }
            }
                                                                                                                                             
            //large object, strong root
            for (int i = 0; i < 10; i++) {
                  for (int j = 0; j < 10; j++) {
                           largeObjBuffer = new int[largeObjSize];
                  }
            System.gc();
            Thread.sleep(100);
        }
    }
}
