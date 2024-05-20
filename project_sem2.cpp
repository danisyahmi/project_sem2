#include <iostream>
#include <iomanip>
#include <limits> // (numeric_limit<streamsize>::max(), '\n')
#include <cstring>

using namespace std;

const int ARR_SIZE = 10;
const int MENU_SIZE = 7;

void menu();
void receiveOrder(int customerCount, int countOrder[ARR_SIZE], char orderID[6][MENU_SIZE]);
void calculationTotalPrice(int customerCount, double priceList[ARR_SIZE], int countOrder[ARR_SIZE], char orderID[6][MENU_SIZE]);
void calculateRevenue(char orderID[6][MENU_SIZE], int customerCount, int countOrder[ARR_SIZE]);
bool check(char orderID[6][MENU_SIZE], int customerCount, const char *order); // const * is a constant pointer parameter. allows for read-only access 
void printReceipt(int customerCount, char orderID[6][MENU_SIZE], int countOrder[ARR_SIZE], double pricelist[MENU_SIZE]);

struct CUSTOMER
{
    char name[50];
    int tableNumber;
    char order[6][ARR_SIZE];
    int quantity[ARR_SIZE];
    double totalPayment;
};

CUSTOMER customer[ARR_SIZE];

int main()
{
    int userChoice, customerCount = 0, countOrder[ARR_SIZE] = {0};
    char orderID[7][MENU_SIZE] = {"D100", "D101", "D102", "D103", "D104", "D105", "D106"};
    double priceList[MENU_SIZE] = {4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 10.00};

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
            receiveOrder(customerCount, countOrder, orderID);
            calculationTotalPrice(customerCount, priceList, countOrder, orderID);
            printReceipt(customerCount, orderID, countOrder, priceList);
            customerCount++; // this increment should be done after all processes for one customer are done
            break;
        case 2: // user input 2 -
            // program go to printTotalRevenue() function -
            calculateRevenue(orderID, customerCount, countOrder);
            break;
        case 3: // user input 3 -
            break;
        }
    }
    return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
void calculateRevenue(char orderID[6][MENU_SIZE], int customerCount, int countOrder[ARR_SIZE])
{
    int totalRevenue[customerCount][MENU_SIZE] = {0};
    for (int r = 0; r < customerCount; r++)
    {
        for (int c = 0; c < countOrder[r]; c++)
        {
            int ID = 0;
            while (ID < MENU_SIZE)
            {
                int IDlenght = strlen(orderID[ID]), orderLenght = strlen(customer[customerCount].order[c]);
                char charOrderID[IDlenght], charOrder[orderLenght];
                strcpy(charOrderID, orderID[ID]);
                strcpy(charOrder, customer[r].order[c]);

                if (strcmp(charOrder, charOrderID) == 0)
                {
                    totalRevenue[r][ID] += customer[r].quantity[c];
                }
                ID++;
            }
        }
    }

    for (int r = 0; r < customerCount; r++)
    {
        for (int c = 0; c < MENU_SIZE; c++)
        {
            cout << totalRevenue[r][c] << '\t';
        }
        cout << endl;
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
void calculationTotalPrice(int customerCount, double priceList[ARR_SIZE], int countOrder[ARR_SIZE], char orderID[6][MENU_SIZE])
{
    customer[customerCount].totalPayment = 0;
    for (int k = 0; k < countOrder[customerCount]; k++)
    {
        int ID = 0;
        while (ID < MENU_SIZE)
        {
            // agak unnecessary, but nak gunakan strcpy()
            int IDlenght = strlen(orderID[ID]), orderLenght = strlen(customer[customerCount].order[k]);
            char charOrderID[IDlenght], charOrder[orderLenght];
            strcpy(charOrderID, orderID[ID]);
            strcpy(charOrder, customer[customerCount].order[k]);

            if (strcmp(charOrder, charOrderID) == 0)
            {
                customer[customerCount].totalPayment = customer[customerCount].totalPayment + (customer[customerCount].quantity[k] * priceList[ID]);
                break;
            }
            ID++;
        }
    }
    cout << endl
         << "the total price is " << customer[customerCount].totalPayment << endl;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

// Function focusing on getting data for each customer input for result calculation
void receiveOrder(int customerCount, int countOrder[ARR_SIZE], char orderID[6][MENU_SIZE])
{
    int paymentMethod;
    char choice;
    bool input = false;

    cout << "\n\n\t\t NEW CUSTOMER\n\n";
    cout << "Please enter customer name : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> customer[customerCount].name;

    cout << "Please enter customer table number (1 -> 40) : ";
    cin >> customer[customerCount].tableNumber;
    while(customer[customerCount].tableNumber < 1 || customer[customerCount].tableNumber > 40 ){
        cout << "Please enter customer table number (1 -> 40) : ";
        cin >> customer[customerCount].tableNumber;
    }

    for (int j = 0; j < ARR_SIZE; j++)
    {
        menu();
        cout << "please enter food code: ";
        cin >> customer[customerCount].order[j];
        input = check(orderID, customerCount, customer[customerCount].order[j]);
        while (input == false)
        {
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cin >> customer[customerCount].order[j];
            input = check(orderID, customerCount, customer[customerCount].order[j]);
        }

        cout << "please enter quantity: ";
        cin >> customer[customerCount].quantity[j];
        while (cin.fail())
        {
            cout << "wrong input please try again : ";
            cin >> customer[customerCount].quantity[j];
        }

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

//------------------------------------------------------------------------------------------------------------------------------------------------------
bool check(char orderID[6][MENU_SIZE], int customerCount, const char *order)
{
    int k = 0;
    while (k < MENU_SIZE)
    {
        if (strcmp(order, orderID[k]) == 0)
        {
            return true;
            break;
        }
        k++;
    }
    return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
void printReceipt(int customerCount, char orderID[6][MENU_SIZE], int countOrder[ARR_SIZE], double pricelist[MENU_SIZE])
{
    int idUsed[ARR_SIZE];
    int i = 0;
    cout << endl << "----------------------------------------" << endl;
    cout << setw(20) << right <<"RECEIPT";
    cout << endl << "----------------------------------------" << endl;
    cout << setw(20) << left << "ITEM" << setw(10) << "QUANTITY" << setw(10) << right << "PRICE" << endl;
    for(int h = 0; h < countOrder[customerCount]; h++){
        cout << setw(24) << left << customer[customerCount].order[h] << setw(6) << customer[customerCount].quantity[h];
        int i = 0;
        while (i < MENU_SIZE){
            if (strcmp(customer[customerCount].order[h], orderID[i]) == 0){
                cout << setw(10) << right << fixed << setprecision(2) << pricelist[i] << endl;
            }
            i++;
        }
    }
    cout << endl << setw(30) << "TOTAL :" << setw(10) << right << fixed << setprecision(2) << customer[customerCount].totalPayment <<endl;
    cout << "----------------------------------------" << endl;
}