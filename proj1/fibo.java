import java.util.ArrayList;
import java.util.Scanner;

class FibonacciGen {

	private static ArrayList<Integer> sequence = new ArrayList<>();
	private static ArrayList<Integer> n_values = new ArrayList<>();

	public static void main(String[] args) {
		// create Scanner object
		Scanner scanner = new Scanner(System.in);
		System.out.println("How many fibonacci numbers would you like?");

		// get value from user
		String input = scanner.nextLine();
		scanner.close();

		// we know 0 and 1 start the fibonacci seqeunce
		sequence.add(0);
		sequence.add(1);

		// determine what to display to the user
		if (input.equals("1")) {
			showOneValue();
		}
		else if (input.equals("2")) {
			showTwoValues();
		}
		else {
			// generate list of values for n
			generateReferenceList(Integer.parseInt(input.trim()));
			Thread thread = new Thread(new MyRunnable(), "child");
			thread.start();
			try {
				thread.join();
			}
			catch (InterruptedException e) {
				System.out.println(e);
			}
			System.out.println(sequence);
		}
	}

	public static void showOneValue() {
		System.out.println(sequence.get(0));
	}

	public static void showTwoValues() {
		System.out.println(sequence.get(0).toString() + ", " + sequence.get(1).toString());
	}

	public static void generateReferenceList(int value) {
		int i = 3; // start at 3 
		while (i < value + 1) {
			n_values.add(i);
			i++;
		}
	}

	static class MyRunnable implements Runnable {
		public void run() {
			for (int i = 0; i < n_values.size(); i++) {
				int n = n_values.get(i) - 1;
				sequence.add((sequence.get(n - 1) + sequence.get(n -  2)));
			}
		}
	}
}