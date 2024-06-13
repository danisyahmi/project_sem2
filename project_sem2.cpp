// include filestream output for print reciept
#include <iostream>
#include <iomanip>
#include <limits> // (numeric_limit<streamsize>::max(), '\n')
#include <cstring>
#include <fstream>

using namespace std;

const int ARR_SIZE = 10;
const int MENU_SIZE = 7;

void menu();
void receiveOrder(int customerCount, int countOrder[ARR_SIZE], char orderID[MENU_SIZE][6]);
void calculationTotalPrice(int customerCount, double priceList[ARR_SIZE], int countOrder[ARR_SIZE], char orderID[MENU_SIZE][6]);
void calculateRevenue(char orderID[MENU_SIZE][6], int customerCount, int countOrder[ARR_SIZE], int totalOrderID[MENU_SIZE]);
bool check(char orderID[MENU_SIZE][6], int customerCount, const char *order); // const * is a constant pointer parameter. allows for read-only access and only pointing on that specific member
void printReceipt(double cashReceive, int paymentMethod, int customerCount, char menuList[MENU_SIZE][20], char orderID[MENU_SIZE][6], int countOrder[ARR_SIZE], double pricelist[MENU_SIZE]);
int choosePayment(double &cashReceive, int customerCount);
void printReceiptFileOutput(double cashReceive, int paymentMethod, int customerCount, char menuList[MENU_SIZE][20], char orderID[MENU_SIZE][6], int countOrder[ARR_SIZE], double pricelist[MENU_SIZE]);

struct CUSTOMER
{
    char name[50];
    int tableNumber;
    char order[ARR_SIZE][6];
    int quantity[ARR_SIZE];
    double totalPayment;
};

CUSTOMER customer[ARR_SIZE];

int main()
{
    int userChoice, customerCount = 0, countOrder[ARR_SIZE] = {0}, totalOrderID[MENU_SIZE] = {0}, paymentMethod;
    char orderID[MENU_SIZE][6] = {"D100", "D101", "D102", "D103", "D104", "D105", "D106"};
    char menuList[MENU_SIZE][20] = {"Black Coffe", "Espresso", "Latte", "Americano", "Cappuchino", "Macchiato", "Chocolate Milkshake"};
    char printReceiptChoice;
    double priceList[MENU_SIZE] = {4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 10.00}, cashReceive;

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
            paymentMethod = choosePayment(cashReceive, customerCount);
            printReceipt(cashReceive, paymentMethod, customerCount, menuList, orderID, countOrder, priceList);
            cout << "Would you like to print the receipt? (Y/N) : ";
            cin >> printReceiptChoice;
            while(printReceiptChoice != 'N' && printReceiptChoice != 'n' && printReceiptChoice != 'Y' && printReceiptChoice != 'y'){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\tWrong input! Would you like to print the receipt? (Y/N) : ";
                cin >> printReceiptChoice;
            }
            if(printReceiptChoice == 'y' || printReceiptChoice == 'Y'){
                printReceiptFileOutput(cashReceive, paymentMethod, customerCount, menuList, orderID, countOrder, priceList);
            }else{
                cout << "Receipt are not printed" << endl;
            }
            customerCount++; // this increment should be done after all processes for one customer are done
            break;
        case 2: // user input 2 -
            // program go to printTotalRevenue() function -
            calculateRevenue(orderID, customerCount, countOrder, totalOrderID);
            break;
        case 3: // user input 3 -
            break;
        }
    }
    return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// this function will display an output on "receipt.txt", as an act of printing receipt 
void printReceiptFileOutput(double cashReceive, int paymentMethod, int customerCount, char menuList[MENU_SIZE][20], char orderID[MENU_SIZE][6], int countOrder[ARR_SIZE], double pricelist[MENU_SIZE])
{
    ofstream fileout;
    fileout.open("receipt.txt");
//------------------------------------------------------------------------------------------------------------------------------------------------------
    fileout << endl
         << "-----------------------------------------" << endl;
    fileout << setw(21) << left << "RECEIPT";
    fileout << setw(18) << right << "TABLE NO : " << setw(2) << right << customer[customerCount].tableNumber;
    fileout << endl
         << "-----------------------------------------" << endl;
    fileout << setw(5) << left << "ITEM" << setw(20) << "DESCRIPTION" << setw(10) << "QUANTITY" << setw(6) << right << "PRICE" << endl;
    for (int h = 0; h < countOrder[customerCount]; h++)
    {
        fileout << setw(5) << left << customer[customerCount].order[h];
        int orderNameQuery = 0;
        while (strcmp(customer[customerCount].order[h], orderID[orderNameQuery]) != 0)
        {
            orderNameQuery++;
        }
        fileout << setw(20) << left << menuList[orderNameQuery];
        fileout << setw(5) << right << customer[customerCount].quantity[h];
        fileout << setw(11) << right << fixed << setprecision(2) << pricelist[orderNameQuery] << endl;
    }
    fileout << endl
         << "-----------------------------------------" << endl;
    fileout << setw(31) << left << "TOTAL :" << setw(10) << right << fixed << setprecision(2) << customer[customerCount].totalPayment << endl;

    switch (paymentMethod)
    {
    case 1:
        fileout << endl
             << setw(31) << left << "PAYMENT METHOD :" << right << setw(10) << "E Wallet" << endl
             << endl;
        fileout << setw(31) << left << "PAID (RM): " << right << setw(10) << fixed << setprecision(2) << customer[customerCount].totalPayment << endl;
        fileout << setw(31) << left << "CHANGE (RM) : " << right << setw(10) << fixed << setprecision(2) << 0.00 << endl
             << endl;
        break;
    case 2:
        fileout << endl
             << setw(31) << left << "PAYMENT METHOD :" << right << setw(10) << "Online Banking" << endl
             << endl;
        fileout << setw(31) << left << "PAID (RM): " << right << setw(10) << fixed << setprecision(2) << customer[customerCount].totalPayment << endl;
        fileout << setw(31) << left << "CHANGE (RM) : " << right << setw(10) << fixed << setprecision(2) << 0.00 << endl
             << endl;
        break;
    case 3:
        // if cash input are valid
        fileout << endl
             << setw(31) << left << "PAYMENT METHOD :" << right << setw(10) << "Cash" << endl
             << endl;
        fileout << setw(31) << left << "PAID (RM) : " << right << setw(10) << fixed << setprecision(2) << cashReceive << endl;
        fileout << setw(31) << left << "CHANGE (RM) : " << right << setw(10) << fixed << setprecision(2) << cashReceive - customer[customerCount].totalPayment << endl
             << endl;
        break;
    }
    fileout << "-----------------------------------------" << endl
         << endl;
//------------------------------------------------------------------------------------------------------------------------------------------------------
    fileout.close();
    cout << "Receipt printed" << endl;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
void calculateRevenue(char orderID[MENU_SIZE][6], int customerCount, int countOrder[ARR_SIZE], int totalOrderID[MENU_SIZE])
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
                char charOrderID[IDlenght], customerID[orderLenght];
                strcpy(customerID, customer[r].order[c]);
                // problems with calculating total revenue of each order, please help me future
                if (strcmp(orderID[ID], customerID) == 0)
                {
                    totalRevenue[r][ID] += customer[r].quantity[c];
                }
                ID++;
            }
        }
    }
    for (int i = 0; i < MENU_SIZE; i++)
    {
        totalOrderID[i] = 0;
        for (int j = 0; j < customerCount; j++)
        {
            totalOrderID[i] += totalRevenue[j][i];
        }
    }

    cout << endl
         << endl;
    // printing the total revenue
    cout << "SALES REVENUE" << endl << endl;
    cout << setw(9) << left << "NAME" << '|' << setw(6) << "TABLE" << '|' << setw(5) << "D100" << setw(5) << "D101" << setw(5) << "D102" << setw(5) << "D103" << setw(5) << "D104" << setw(5) << "D105" << setw(5) << "D106" << setw(5) << endl;
    
    for (int r = 0; r < customerCount; r++)
    {
        cout << "---------------------------------------------------" << endl;
        cout << setw(9) << left << customer[r].name << '|' << setw(6) << left << customer[r].tableNumber << '|';
        for (int c = 0; c < MENU_SIZE; c++)
        {
            cout << setw(5) << totalRevenue[r][c];
        }
    }
    cout << endl << "---------------------------------------------------" << endl;
    cout << setw(16) << left << "TOTAL (UNIT) :" << '|';
    for (int h = 0; h < MENU_SIZE; h++)
    {
        cout << setw(5) << totalOrderID[h];
    }
    cout << endl
         << "---------------------------------------------------" << endl
         << endl;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
void calculationTotalPrice(int customerCount, double priceList[ARR_SIZE], int countOrder[ARR_SIZE], char orderID[MENU_SIZE][6])
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
         << endl
         << "TOTAL PRICE : " << customer[customerCount].totalPayment << endl
         << endl;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
void receiveOrder(int customerCount, int countOrder[ARR_SIZE], char orderID[MENU_SIZE][6])
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
    while (customer[customerCount].tableNumber < 1 || customer[customerCount].tableNumber > 40 || cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\tWrong input! Please enter customer table number (1 -> 40) : ";
        cin >> customer[customerCount].tableNumber;
    }

    for (int j = 0; j < ARR_SIZE; j++)
    {
        menu();
        cout << "Please enter food code: ";
        cin >> customer[customerCount].order[j];
        input = check(orderID, customerCount, customer[customerCount].order[j]);
        while (input == false)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\tWrong input! Please enter food code : ";
            cin >> customer[customerCount].order[j];
            input = check(orderID, customerCount, customer[customerCount].order[j]);
        }

        cout << "Please enter quantity: ";
        cin >> customer[customerCount].quantity[j];
        while (cin.fail())
        {
            cin.clear();
            cout << "\tWrong input! Please enter quantity : ";
            cin >> customer[customerCount].quantity[j];
        }

        cout << "Do you want to add on? (Y/N): ";
        cin >> choice;
        while(choice != 'N' && choice != 'n' && choice != 'Y' && choice != 'y'){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\tWrong input, Do you want to add on? (Y/N) : ";
                cin >> choice;
            }
        countOrder[customerCount]++;
        if (choice == 'n' || choice == 'N')
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
    cout << left << setw(10) << "D106" << setw(20) << "Chocolate Milkshake" << setw(15) << fixed << setprecision(2) << 10.00 << endl
         << endl;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
bool check(char orderID[MENU_SIZE][6], int customerCount, const char *order)
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
void printReceipt(double cashReceive, int paymentMethod, int customerCount, char menuList[MENU_SIZE][20], char orderID[MENU_SIZE][6], int countOrder[ARR_SIZE], double pricelist[MENU_SIZE])
{
    // include table number on receipt
    cout << endl
         << "-----------------------------------------" << endl;
    cout << setw(21) << left << "RECEIPT";
    cout << setw(18) << right << "TABLE NO : " << setw(2) << right << customer[customerCount].tableNumber;
    cout << endl
         << "-----------------------------------------" << endl;
    cout << setw(5) << left << "ITEM" << setw(20) << "DESCRIPTION" << setw(10) << "QUANTITY" << setw(6) << right << "PRICE" << endl;
    for (int h = 0; h < countOrder[customerCount]; h++)
    {
        cout << setw(5) << left << customer[customerCount].order[h];
        int orderNameQuery = 0;
        while (strcmp(customer[customerCount].order[h], orderID[orderNameQuery]) != 0)
        {
            orderNameQuery++;
        }
        cout << setw(20) << left << menuList[orderNameQuery];
        cout << setw(5) << right << customer[customerCount].quantity[h];
        cout << setw(11) << right << fixed << setprecision(2) << pricelist[orderNameQuery] << endl;
    }
    cout << endl
         << "-----------------------------------------" << endl;
    cout << setw(31) << left << "TOTAL :" << setw(10) << right << fixed << setprecision(2) << customer[customerCount].totalPayment << endl;

    switch (paymentMethod)
    {
    case 1:
        cout << endl
             << setw(31) << left << "PAYMENT METHOD :" << right << setw(10) << "E Wallet" << endl
             << endl;
        cout << setw(31) << left << "PAID (RM): " << right << setw(10) << fixed << setprecision(2) << customer[customerCount].totalPayment << endl;
        cout << setw(31) << left << "CHANGE (RM) : " << right << setw(10) << fixed << setprecision(2) << 0.00 << endl
             << endl;
        break;
    case 2:
        cout << endl
             << setw(31) << left << "PAYMENT METHOD :" << right << setw(10) << "Online Banking" << endl
             << endl;
        cout << setw(31) << left << "PAID (RM): " << right << setw(10) << fixed << setprecision(2) << customer[customerCount].totalPayment << endl;
        cout << setw(31) << left << "CHANGE (RM) : " << right << setw(10) << fixed << setprecision(2) << 0.00 << endl
             << endl;
        break;
    case 3:
        // if cash input are valid
        cout << endl
             << setw(31) << left << "PAYMENT METHOD :" << right << setw(10) << "Cash" << endl
             << endl;
        cout << setw(31) << left << "PAID (RM) : " << right << setw(10) << fixed << setprecision(2) << cashReceive << endl;
        cout << setw(31) << left << "CHANGE (RM) : " << right << setw(10) << fixed << setprecision(2) << cashReceive - customer[customerCount].totalPayment << endl
             << endl;
        break;
    }
    cout << "-----------------------------------------" << endl
         << endl;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
int choosePayment(double &cashReceive, int customerCount)
{
    int paymentMethod;
    double cashBalance;
    cout << "PAYMENT METHOD" << endl;
    cout << "1) E Wallet" << endl;
    cout << "2) Online Banking " << endl;
    cout << "3) Cash" << endl;
    cout << endl
         << endl
         << "Total (RM) :" << customer[customerCount].totalPayment << endl
         << endl;
    cout << "Please enter payment method : ";
    cin >> paymentMethod;
    while (paymentMethod != 1 && paymentMethod != 2 && paymentMethod != 3)
    {
        cin.clear(); // clearing non wanted user input
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl
             << "\t!Wrong input, Please enter payment method : ";
        cin >> paymentMethod;
    }
    if (paymentMethod == 3)
    {
        cout << "Please Enter the amount of cash : ";
        cin >> cashReceive;
        while(cin.fail()){
             cin.clear();
            cout << "\tWrong input! Please enter the amount of cash : ";
            cin >> cashReceive;
        }
        while (cashReceive < customer[customerCount].totalPayment)
        {
            cout << "Your money is insufficient! Please enter RM " << customer[customerCount].totalPayment - cashReceive << " more : ";
            cin >> cashBalance;
            while(cin.fail()){
            cin.clear();
            cout << "\tWrong input! Please enter RM " << customer[customerCount].totalPayment - cashReceive << " more : ";
            cin >> cashReceive;
        }
            cashReceive = cashReceive + cashBalance;
        }
    }
    else
    {
        cashReceive = 0.0;
    }

    return paymentMethod;
}