// D032310401 MOHAMED SYAHMI BIN ABDUL SHUKOR
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>  
using namespace std;
// kenapa aku gay
// global variable
const int SIZE = 100;	   // set limit for user input in the array,, used in collecting order from customer, look in askOrder() function -
double salesRevenue = 0.0; // total sales revenue as global variable, updated each time after new customer done ordering
int order[SIZE], quantity[SIZE], totalOrder[SIZE], totalQuantity[SIZE];
int countSalesRevenue = 0;
int quantity100 = 0, quantity101 = 0, quantity102 = 0, quantity103 = 0, quantity104 = 0, quantity105 = 0, quantity106 = 0;
double price100 = 0.00, price101 = 0.00, price102 = 0.00, price103 = 0.00, price104 = 0.00, price105 = 0.00, price106 = 0.00;

// function prototype
void askOrder();
void menu();
void printTotalRevenue();
void printReceipt(int order[], int quantity[], int count, int payment, double cash);
int choosePayment(double &cash, int order[], int quantity[], int count);

// ############################################################################################################################################################################################################################################################################

// main function
int main()
{
	int userChoice;

while(userChoice != 3){
	cout << endl
		 << "\t\tMAIN MENU" << endl
		 << endl;
	cout << "1. New Customer" << endl
		 << "2. Sales Revenue" << endl
		 << "3. Exit" << endl;
	cout << "Please enter your choice : ";
	cin >> userChoice;

	while (userChoice != 1 && userChoice != 2 && userChoice != 3)
	{
		cin.clear(); // clearing non wanted user input
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout << endl
			 << "Invalid Choice! Please try again." << endl;
		cin >> userChoice;
	}

	switch (userChoice)
	{
	case 1:			// if user input 1 -
		askOrder(); // program go to askOrder() function -
		break;
	case 2:					 // user input 2 -
		printTotalRevenue(); // program go to printTotalRevenue() function -
		break;
	case 3: // user input 3 -
		cout << endl
			 << "Thank You...." << endl;
		exit(1); // program terminated
		break;

	}
}
	cout << endl;
	return 0;
}

// ############################################################################################################################################################################################################################################################################

// function for displaying food menu
void menu()
{
	cout << endl
		 << "\t\t CAFE MENU \t\t" << endl
		 << endl;
	cout << left << setw(10) << "CODE" << setw(20) << "NAME " << setw(15) << "PRICE (RM) " << endl;
	cout << left << setw(10) << 100 << setw(20) << "Black Coffee " << setw(15) << fixed << setprecision(2) << 4.00 << endl;
	cout << left << setw(10) << 101 << setw(20) << "Espresso " << setw(15) << fixed << setprecision(2) << 5.00 << endl;
	cout << left << setw(10) << 102 << setw(20) << "Latte " << setw(15) << fixed << setprecision(2) << 6.00 << endl;
	cout << left << setw(10) << 103 << setw(20) << "Americano " << setw(15) << fixed << setprecision(2) << 7.00 << endl;
	cout << left << setw(10) << 104 << setw(20) << "Cappucino" << setw(15) << fixed << setprecision(2) << 8.00 << endl;
	cout << left << setw(10) << 105 << setw(20) << "Macchiato" << setw(15) << fixed << setprecision(2) << 9.00 << endl;
	cout << left << setw(10) << 106 << setw(20) << "Chocolate Milkshake " << setw(15) << fixed << setprecision(2) << 10.00 << endl
		 << endl;
}

// ############################################################################################################################################################################################################################################################################

// function for receive user order -
void askOrder()
{
	// array order[size] used to store user order in each index,,, example - index 0 = code 101, index 1= code 102
	int paymentMethod, tableNumber, count = 0; // declaring array order[SIZE], quantity[SIZE] and counter variable-
	double cash, totalOrder = 0.0;			   // total order price set as 0.0 -
	char choice;
	string customerName;

	cout << "\n\n\t\t NEW CUSTOMER\n\n";
	cout << "Please enter customer name : ";
	cin.ignore(numeric_limits<streamsize>::max(),'\n');; // need to use cin.ignore() to clear '\n' in the buffer from previous input
	getline(cin, customerName);
	cout << "Please enter customer table number (1 -> 40) : ";
	cin >> tableNumber;

	// input validation, any non number input for table number OR table number > 40 OR <= 0 will not be accepted
	while (!cin >> tableNumber || tableNumber > 40 || tableNumber <= 0)
	{
		cin.clear(); // clearing non wanted user input
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout << "Wrong input, try again \n";
		cout << "Please enter customer table number (1 -> 40) : ";
		cin >> tableNumber;
	}

	// using for loop to keep increase the array index -
	for (int index = 0; index < SIZE; index++) // index = 0; if index < SIZE; index + 1 -
	{
		menu();
		cout << "Please enter your food code : ";
		cin >> order[index]; // i = index, index will be updated each time loop happened -

		// input validation, non number will not be accepted -
		while (!cin >> order[index] || order[index] < 100 || order[index] > 106) // if cin >> order[i] == false  OR order[index] < 100 OR order[index] > 109 -
		{
			cin.clear();				   // clearing non wanted user input -
			cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignore input up to numeric limit until found '\n' -
			cout << "\nwrong input..... please try again \n";
			cout << "Please enter your food code : ";
			cin >> order[index];
		}
		cout << "please enter quantity : ";
		cin >> quantity[index]; // i = index, index will be updated each time loop happened -

		// input validation, non number will not be accepted -
		while (!cin >> quantity[index]) // if cin >> order[i] == false -
		{
			cin.clear();				   // clearing non wanted user input -
			cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignore input up to 1000 until found '\n' -
			cout << "\nWrong input..... please try again \n";
			cout << "Please enter quantity : ";
			cin >> quantity[index];
		}

		count++; // counter for counting array index or how many index user inserted -

		cout << "Do you want to add on? (y/n) \n";
		cin >> choice;

		// input validation
		while (choice != 'n' && choice != 'y')
		{
			cin.clear();				   // clearing non wanted user input
			cin.ignore(numeric_limits<streamsize>::max(),'\n'); // ignore input up to 1000 until found '\n' -
			cout << "\nWrong input..... please try again \n";
			cout << "Do you want to add on? (y/n) \n";
			cin >> choice;
		}

		// user stop inserting order, program go to printReceipt function -
		if (choice == 'n') // if user want to stop ordering -
		{
			paymentMethod = choosePayment(cash, order, quantity, count);
			printReceipt(order, quantity, count, paymentMethod, cash);
			break; // stop for loop -
		}
	}
}

// ############################################################################################################################################################################################################################################################################

// choose 1 out of three payment method
int choosePayment(double &cash, int order[], int quantity[], int count)
{
	int paymentMethod;
	double totalPricePerOrder, cashbalance;
	cash = 0.0; // cash initialize as zero -
	totalPricePerOrder = 0.00;
	// user needed to insert an amount of cash
	for (int i = 0; i < count; i++)
	{
		switch (order[i])
		{ // check the value in each index in order[] array -
		case 100:
			totalPricePerOrder = totalPricePerOrder + (quantity[i] * 4.00); // total price for the order will be updated after cheking food code (using switch) -
			break;
		case 101:
			totalPricePerOrder = totalPricePerOrder + (quantity[i] * 5.00); // total price for the order will be updated after cheking food code (using switch) -
			break;
		case 102:
			totalPricePerOrder = totalPricePerOrder + (quantity[i] * 6.00); // total price for the order will be updated after cheking food code (using switch) -
			break;
		case 103:
			totalPricePerOrder = totalPricePerOrder + (quantity[i] * 7.00); // total price for the order will be updated after cheking food code (using switch) -
			break;
		case 104:
			totalPricePerOrder = totalPricePerOrder + (quantity[i] * 8.00); // total price for the order will be updated after cheking food code (using switch) -
			break;
		case 105:
			totalPricePerOrder = totalPricePerOrder + (quantity[i] * 9.00); // total price for the order will be updated after cheking food code (using switch) -
			break;
		case 106:
			totalPricePerOrder = totalPricePerOrder + (quantity[i] * 10.00); // total price for the order will be updated after cheking food code (using switch) -
			break;
		}
	}
	salesRevenue = salesRevenue + totalPricePerOrder; // after total price for the order is confirmed, sales revenue will be updated by adding with total price of each order -

	cout << "PAYMENT METHOD" << endl;
	cout << "1) E Wallet" << endl;
	cout << "2) Online Banking " << endl;
	cout << "3) Cash" << endl;
	cout << endl
		 << endl
		 << "Total (RM) :" << totalPricePerOrder << endl
		 << endl;
	cout << "Please enter payment method : ";
	cin >> paymentMethod;

	// input validation, only 1, 2, 3 choices are accepted
	while (paymentMethod != 1 && paymentMethod != 2 && paymentMethod != 3)
	{
		cin.clear(); // clearing non wanted user input
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout << endl
			 << "Wrong input, please try again." << endl;
		cout << "Please enter payment method : ";
		cin >> paymentMethod;
	}

	// is user choose to pay with cash
	if (paymentMethod == 3)
	{
		cout << "Please Enter the amount of cash : ";
		cin >> cash;
		while (cash < totalPricePerOrder)
		{
			cout << "Your money is insufficient! Please enter RM " << totalPricePerOrder - cash << " more : ";
			cin >> cashbalance;
			cash = cash + cashbalance;
		}
	}
	// if user choose not to pay with cash
	else
	{
		cash = 0.0; // cash set as 0.0 again
	}
	return paymentMethod;
}

// ############################################################################################################################################################################################################################################################################

// printing output
void printReceipt(int order[], int quantity[], int count, int payment, double cash) // loop go through array -
{
	double totalPricePerOrder = 0.0;

	cout << endl
		 << left << setw(10) << "CODE" << setw(20) << "NAME " << setw(10) << "QUANTITY" << setw(10) << "PRICE(RM) " << endl
		 << endl;

	// go through each index in the array, order[] and quantity[] -
	for (int index = 0; index < count; index++) // using "for" loop to move into each index in order[] and quantity[] array simultaneously
	{
		switch (order[index]) // check the value in each index in order[] array -
		{
		case 100:
			cout << left << setw(10) << fixed << setprecision(2) << 100 << setw(20) << "Black Coffee " << setw(15) << quantity[index] << setw(15) << 4.00 << endl;
			totalPricePerOrder = totalPricePerOrder + (quantity[index] * 4.00); // total price for the order will be updated after cheking food code (using switch) -
			quantity100 = quantity100 + quantity[index];
			price100 = price100 + (quantity[index] * 4.00);
			countSalesRevenue++;
			break;
		case 101:
			cout << left << setw(10) << fixed << setprecision(2) << 101 << setw(20) << "Espresso " << setw(15) << quantity[index] << setw(15) << 5.00 << endl;
			totalPricePerOrder = totalPricePerOrder + (quantity[index] * 5.00); // total price for the order will be updated after cheking food code (using switch) -
			quantity101 = quantity101 + quantity[index];
			price101 = price101 + (quantity[index] * 5.00);
			countSalesRevenue++;
			break;
		case 102:
			cout << left << setw(10) << fixed << setprecision(2) << 102 << setw(20) << "Latte " << setw(15) << quantity[index] << setw(15) << 6.00 << endl;
			totalPricePerOrder = totalPricePerOrder + (quantity[index] * 6.00); // total price for the order will be updated after cheking food code (using switch) -
			quantity102 = quantity102 + quantity[index];
			price102 = price102 + (quantity[index] * 6.00);
			countSalesRevenue++;
			break;
		case 103:
			cout << left << setw(10) << fixed << setprecision(2) << 103 << setw(20) << "Americano " << setw(15) << quantity[index] << setw(15) << 7.00 << endl;
			totalPricePerOrder = totalPricePerOrder + (quantity[index] * 7.00); // total price for the order will be updated after cheking food code (using switch) -
			quantity103 = quantity103 + quantity[index];
			price103 = price103 + (quantity[index] * 7.00);
			countSalesRevenue++;

			break;
		case 104:
			cout << left << setw(10) << fixed << setprecision(2) << 104 << setw(20) << "Cappucino " << setw(15) << quantity[index] << setw(15) << 8.00 << endl;
			totalPricePerOrder = totalPricePerOrder + (quantity[index] * 8.00); // total price for the order will be updated after cheking food code (using switch) -
			quantity104 = quantity104 + quantity[index];
			price104 = price104 + (quantity[index] * 8.00);

			break;
		case 105:
			cout << left << setw(10) << fixed << setprecision(2) << 105 << setw(20) << "Macchiato" << setw(15) << quantity[index] << setw(15) << 9.00 << endl;
			totalPricePerOrder = totalPricePerOrder + (quantity[index] * 9.00); // total price for the order will be updated after cheking food code (using switch) -
			quantity105 = quantity105 + quantity[index];
			price105 = price105 + (quantity[index] * 9.00);
			countSalesRevenue++;
			break;
		case 106:
			cout << left << setw(10) << fixed << setprecision(2) << 106 << setw(20) << "Chocolate Milkshake " << setw(15) << quantity[index] << setw(15) << 10.00 << endl;
			totalPricePerOrder = totalPricePerOrder + (quantity[index] * 10.00); // total price for the order will be updated after cheking food code (using switch) -
			quantity106 = quantity106 + quantity[index];
			price106 = price106 + (quantity[index] * 10.00);
			countSalesRevenue++;
			break;
		}
	}
	cout << endl
		 << "TOTAL PRICE (RM) :" << right << setw(31) << totalPricePerOrder << endl;
	switch (payment)
	{
	case 1:
		cout << endl
			 << "PAYMENT METHOD :" << right << setw(33) << "E Wallet" << endl
			 << endl
			 << endl;
		cout << "PAID (RM): " << right << setw(38) << fixed << setprecision(2) << totalPricePerOrder << endl;
		cout << "CHANGE (RM) : " << right << setw(35) << fixed << setprecision(2) << 0.00 << endl
			 << endl;
		break;
	case 2:
		cout << endl
			 << "PAYMENT METHOD :" << right << setw(33) << "Online Banking" << endl
			 << endl
			 << endl;
		cout << "PAID (RM): " << right << setw(38) << fixed << setprecision(2) << totalPricePerOrder << endl;
		cout << "CHANGE (RM) : " << right << setw(35) << fixed << setprecision(2) << 0.00 << endl
			 << endl;
		break;
	case 3:
		// if cash input are valid
		cout << endl
			 << "PAYMENT METHOD :" << right << setw(33) << "Cash" << endl
			 << endl
			 << endl;
		cout << "PAID (RM) : " << right << setw(38) << fixed << setprecision(2) << cash << endl;
		cout << "CHANGE (RM) : " << right << setw(35) << fixed << setprecision(2) << cash - totalPricePerOrder << endl
			 << endl;
		break;
	}
}

// ############################################################################################################################################################################################################################################################################

// printing total sales revenue
void printTotalRevenue()
{
	cout << endl
		 << "\t\tCAFE" << endl
		 << endl;
	cout << "TOTAL SALES" << endl
		 << endl;
	cout << left << setw(10) << "CODE" << setw(20) << "NAME " << setw(15) << "QUANTITY" << setw(15) << "SALES (RM) " << endl;
	cout << left << setw(10) << 100 << setw(20) << "Black Coffee " << right << setw(5) << quantity100 << setw(15) << fixed << setprecision(2) << price100 << endl;
	cout << left << setw(10) << 101 << setw(20) << "Espresso " << right << setw(5) << quantity101 << setw(15) << fixed << setprecision(2) << price101 << endl;
	cout << left << setw(10) << 102 << setw(20) << "Latte " << right << setw(5) << quantity102 << setw(15) << fixed << setprecision(2) << price102 << endl;
	cout << left << setw(10) << 103 << setw(20) << "Americano " << right << setw(5) << quantity103 << setw(15) << fixed << setprecision(2) << price103 << endl;
	cout << left << setw(10) << 104 << setw(20) << "Cappucino" << right << setw(5) << quantity104 << setw(15) << fixed << setprecision(2) << price104 << endl;
	cout << left << setw(10) << 105 << setw(20) << "Macchiato" << right << setw(5) << quantity105 << setw(15) << fixed << setprecision(2) << price105 << endl;
	cout << left << setw(10) << 106 << setw(20) << "Chocolate Milkshake " << right << setw(5) << quantity106 << setw(15) << fixed << setprecision(2) << price106 << endl
		 << endl;
	cout << "TOTAL SALES REVENUE (RM) : " << right << setw(23) << salesRevenue << endl
		 << endl;
}
