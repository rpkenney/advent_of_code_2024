import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.lang.Math;
import java.util.ArrayList;

public class Part2 {

    @SuppressWarnings("unchecked")
    static boolean isSafe(ArrayList<Integer> list, boolean secondChance, int removeIdx) {
        if (secondChance) {
            list.remove(removeIdx);
        }

        int prev;
        if (list.size() > 0) {
            prev = list.get(0);
        } else {
            return true;
        }

        int ascendingCount = 0;
        int descendingCount = 0;

        for (int i = 1; i < list.size(); i++) {
            int curr = list.get(i);
            if (curr > prev) {
                ascendingCount++;
            } else if (prev > curr) {
                descendingCount++;
            }

            if (Math.min(ascendingCount, descendingCount) > 0 || Math.abs(curr - prev) > 3 || prev == curr) {
                if (!secondChance) {
                    return isSafe((ArrayList<Integer>) list.clone(), true, i)
                            || isSafe((ArrayList<Integer>) list.clone(), true, i - 1)
                            || (i == 2 && isSafe((ArrayList<Integer>) list.clone(), true, 0));
                } else {
                    return false;
                }
            } else {
                prev = curr;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        String fileName = "../inputs/day2.txt";
        try {
            File file = new File(fileName);
            Scanner fileScanner = new Scanner(file);

            int safe = 0;
            while (fileScanner.hasNextLine()) {
                String line = fileScanner.nextLine();

                Scanner lineScanner = new Scanner(line);

                ArrayList<Integer> list = new ArrayList<Integer>();

                while (lineScanner.hasNextInt()) {
                    list.add(lineScanner.nextInt());
                }

                if (isSafe(list, false, -1)) {
                    safe++;
                }
                lineScanner.close();
            }
            fileScanner.close();
            System.out.println(safe);
        } catch (FileNotFoundException e) {
            System.out.println("Error opening file: " + fileName);
        }
    }
}
