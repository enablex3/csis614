import java.util.Scanner;

class FibonacciGen {

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		System.out.println("How many fibonacci numbers would you like?");
		String input = scanner.nextLine();
		int value = Integer.parseInt(input.trim());
	}
}