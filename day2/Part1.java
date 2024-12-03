import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.lang.Math;

public class Part1 {
    public static void main(String[] args) {
        String fileName = "../inputs/day2.txt";
        try {
            File file = new File(fileName);
            Scanner fileScanner = new Scanner(file);

            int safe = 0;
            while (fileScanner.hasNextLine()) {
                boolean descending = false;

                String line = fileScanner.nextLine();

                Scanner lineScanner = new Scanner(line);

                int prev;
                if (lineScanner.hasNextInt()) {
                    prev = lineScanner.nextInt();
                    safe++;
                } else {
                    continue;
                }

                int curr;
                if (lineScanner.hasNextInt()) {
                    curr = lineScanner.nextInt();
                } else {
                    continue;
                }
                if (Math.abs(curr - prev) > 3 || curr == prev) {
                    safe--;
                    continue;
                }

                descending = curr < prev;
                while (lineScanner.hasNextInt()) {
                    prev = curr;
                    curr = lineScanner.nextInt();
                    if (descending && curr > prev) {
                        safe--;
                        break;
                    } else if (!descending && prev > curr) {
                        safe--;
                        break;
                    } else if (Math.abs(curr - prev) > 3 || prev == curr) {
                        safe--;
                        break;
                    }
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
