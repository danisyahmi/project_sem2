#include <iostream>
#include <iomanip>
#include <string>
#include <limits> // (numeric_limit<streamsize>::max(), '\n')
#include <cstring>

using namespace std;

const int ARR_SIZE = 10;
const int MENU_SIZE = 7;
void menu();
void receiveOrder(int customerCount, int countOrder[ARR_SIZE], int tableNumber[ARR_SIZE], string customer[ARR_SIZE], string order[ARR_SIZE], int quantity[ARR_SIZE]);
void calculationTotalPrice(int &customerCount, int countOrder[ARR_SIZE], string order[ARR_SIZE], int quantity[ARR_SIZE], double totalPrice[ARR_SIZE]);

int main()
{
    int userChoice, customerCount = 0, countOrder[ARR_SIZE] = {0}, tableNumber[ARR_SIZE], quantity[ARR_SIZE];
    double totalPrice[ARR_SIZE];
    string customer[ARR_SIZE];
    string order[ARR_SIZE];

    while (userChoice != 3)
    {
        cout << endl
             << "\t\tMAIN MENU" << endl
             << endl
             << "1. New Customer" << endl
             << "2. Sales Revenue" << endl
             << "3. Exit" << endl
             << "Please enter your choice : ";
        cin >> userChoice;

        while (userChoice != 1 && userChoice != 2 && userChoice != 3)
        {
            cin.clear(); // clearing non wanted user input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl
                 << "Invalid Choice! Please try again." << endl;
            cin >> userChoice;
        }

        switch (userChoice)
        {
        case 1: // if user input 1 -
            receiveOrder(customerCount, countOrder, tableNumber, customer, order, quantity);
            calculationTotalPrice(customerCount, countOrder, order, quantity, totalPrice);
            break;
        case 2: // user input 2 -
                // program go to printTotalRevenue() function -
            break;
        case 3: // user input 3 -
            break;
        }
    }
    return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

void calculationTotalPrice(int &customerCount, int countOrder[ARR_SIZE], string order[ARR_SIZE], int quantity[ARR_SIZE], double totalPrice[ARR_SIZE])
{
    string orderID[MENU_SIZE] = {"D100", "D101", "D102", "D103", "D104", "D105", "D106"};
    double priceList[MENU_SIZE] = {4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 10.00};
    totalPrice[ARR_SIZE] = {0};

    for (int k = 0; k < countOrder[customerCount]; k++)
    {
        int ID = 0;
        // please kemaskan loop dibawah ini ya dani
        while (ID < MENU_SIZE)
        {
            int IDlenght = sizeof(orderID[ID]), orderLenght = sizeof(order[k]);
            char charOrderID[IDlenght], charOrder[orderLenght];
            strcpy(charOrderID, orderID[ID].c_str());
            strcpy(charOrder, order[k].c_str());

            if (strcmp(charOrder, charOrderID) == 0)
            {
                totalPrice[customerCount] = totalPrice[customerCount] + (quantity[k] * priceList[ID]);
                break;
            }
            ID++;
        }
    }
    cout << endl
         << "the total price is " << totalPrice[customerCount] << endl;
    customerCount++; // this increment should be done after all processes for one customer are done
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

// Function focusing on getting data for each customer input for result calculation
void receiveOrder(int customerCount, int countOrder[ARR_SIZE], int tableNumber[ARR_SIZE], string customer[ARR_SIZE], string order[ARR_SIZE], int quantity[ARR_SIZE])
{
    int paymentMethod;
    char choice;

    cout << "\n\n\t\t NEW CUSTOMER\n\n";
    cout << "Please enter customer name : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, customer[customerCount]);

    cout << "Please enter customer table number (1 -> 40) : ";
    cin >> tableNumber[customerCount];

    for (int j = 0; j < ARR_SIZE; j++)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        menu();
        cout << "please enter food code: ";
        getline(cin, order[j]);

        cout << "please enter quantity: ";
        cin >> quantity[j];

        cout << "do you want to add on ? (y/n): ";
        cin >> choice;
        countOrder[customerCount]++;
        if (choice == 'n')
        {
            break;
        }
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// DANI 
void menu()
{
    cout << endl
         << "\t\t CAFE MENU \t\t" << endl
         << endl;
    cout << left << setw(10) << "CODE" << setw(20) << "NAME " << setw(15) << "PRICE (RM) " << endl;
    cout << left << setw(10) << "D100" << setw(20) << "Black Coffee " << setw(15) << fixed << setprecision(2) << 4.00 << endl;
    cout << left << setw(10) << "D101" << setw(20) << "Espresso " << setw(15) << fixed << setprecision(2) << 5.00 << endl;
    cout << left << setw(10) << "D102" << setw(20) << "Latte " << setw(15) << fixed << setprecision(2) << 6.00 << endl;
    cout << left << setw(10) << "D103" << setw(20) << "Americano " << setw(15) << fixed << setprecision(2) << 7.00 << endl;
    cout << left << setw(10) << "D104" << setw(20) << "Cappucino" << setw(15) << fixed << setprecision(2) << 8.00 << endl;
    cout << left << setw(10) << "D105" << setw(20) << "Macchiato" << setw(15) << fixed << setprecision(2) << 9.00 << endl;
    cout << left << setw(10) << "D106" << setw(20) << "Chocolate Milkshake " << setw(15) << fixed << setprecision(2) << 10.00 << endl
         << endl;
}
