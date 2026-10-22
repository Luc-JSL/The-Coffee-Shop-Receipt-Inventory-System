// Coffee Shop Receipt and Inventory System (Lab 8 - Functions)
// Reads the drink menu from Menu.txt, takes orders for any number of
// customers, prints each receipt to the screen and to receipt.txt, and
// writes an end-of-day summary and inventory report to log.txt.

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <limits>

using namespace std;

// Rates used to price an order. These are constants, so it is safe for
// every function to see them.
const double MEMBER_DISCOUNT_RATE = 0.10;
const double STATE_TAX_RATE = 0.065;
const double COUNTY_TAX_RATE = 0.005;
const double MUNICIPAL_TAX_RATE = 0.02125;
const double DOLLARS_PER_LOYALTY_POINT = 3.0;

// Stops the program cleanly if the keyboard input runs out (for example,
// when input is piped from a file). Without this, input loops would spin
// forever once cin reaches the end of the input.
void exitIfInputEnded() {
    if (cin.eof()) {
        cout << endl << "Input ended. Closing program." << endl;
        exit(1);
    }
}

// Throws away everything left on the current input line, so leftover
// characters cannot be read as the answer to the next prompt.
void clearRestOfLine() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Shows a prompt and reads one letter from the user.
// Parameters: prompt - the text to show before reading
// Returns: the first non-space character typed, converted to uppercase
char getLetter(string prompt) {
    char letter;
    cout << prompt;
    if (!(cin >> letter)) {
        exitIfInputEnded();
    }
    clearRestOfLine();
    return toupper(letter);
}

// Asks a yes/no question until the user answers Y or N.
// Parameters: prompt - the question to show
// Returns: true for Y, false for N
bool getYesNo(string prompt) {
    while (true) {
        char answer = getLetter(prompt);
        if (answer == 'Y') {
            return true;
        }
        if (answer == 'N') {
            return false;
        }
        cout << "Please enter Y or N." << endl;
    }
}

// Formats a dollar amount with exactly two decimal places.
// Parameters: amount - the value to format
// Returns: the amount as text, rounded to the cent (for example "4.50")
string formatAmount(double amount) {
    stringstream amountText;
    amountText << fixed << setprecision(2) << amount;
    return amountText.str();
}

// Writes the same text to the screen and to an output file, so receipts
// and reports only have to be built once.
// Parameters: outputFile - the open file to write to
//             text - the text to write
void printToBoth(ofstream& outputFile, string text) {
    cout << text;
    outputFile << text;
}

// Reads the next non-blank line from the menu file.
// Parameters: menuFile - the open menu file
// Returns: the line without a trailing '\r' (from Windows files),
//          or "" if the end of the file is reached
string readMenuLine(ifstream& menuFile) {
    string line;
    while (getline(menuFile, line)) {
        // Files saved on Windows end lines with "\r\n"; drop the '\r'.
        if (!line.empty() && line[line.length() - 1] == '\r') {
            line = line.substr(0, line.length() - 1);
        }
        if (line != "") {
            return line;
        }
    }
    return "";
}

// Loads the drink names and prices from Menu.txt (or a file named Menu).
// Each drink takes two lines: its name, then its small, medium, and large
// prices separated by spaces.
// Parameters: itemNames, smallPrices, mediumPrices, largePrices - arrays
//             filled in with the menu data
//             itemCount - how many drinks to read
// Returns: true if every drink was read, false if the file is missing
//          or not in the right format
bool loadMenu(string itemNames[], double smallPrices[],
    double mediumPrices[], double largePrices[], int itemCount) {
    ifstream menuFile("Menu.txt");
    if (!menuFile) {
        // Some editors save the file without the .txt extension.
        menuFile.clear();
        menuFile.open("Menu");
    }
    if (!menuFile) {
        return false;
    }

    for (int i = 0; i < itemCount; i++) {
        itemNames[i] = readMenuLine(menuFile);
        if (itemNames[i] == "") {
            return false;
        }

        if (!(menuFile >> smallPrices[i] >> mediumPrices[i] >> largePrices[i])) {
            return false;
        }
        // Skip the end of the price line before reading the next name.
        menuFile.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return true;
}

// Shows the drink menu with a letter for each drink, plus a checkout option.
// Parameters: itemNames, smallPrices, mediumPrices, largePrices - menu data
//             itemCount - number of drinks on the menu
void displayMenu(string itemNames[], double smallPrices[],
    double mediumPrices[], double largePrices[], int itemCount) {
    cout << endl << "Drink Menu" << endl;
    for (int i = 0; i < itemCount; i++) {
        cout << char('A' + i) << ". " << itemNames[i]
            << " - Small $" << formatAmount(smallPrices[i])
            << ", Medium $" << formatAmount(mediumPrices[i])
            << ", Large $" << formatAmount(largePrices[i]) << endl;
    }
    // The letter right after the last drink is checkout.
    cout << char('A' + itemCount) << ". Checkout" << endl;
}

// Asks the customer to pick a drink or checkout until they enter a valid letter.
// Parameters: itemCount - number of drinks on the menu
// Returns: the index of the chosen drink (0 for A, 1 for B, ...),
//          or -1 if the customer chose checkout
int getMenuChoice(int itemCount) {
    char lastLetter = char('A' + itemCount);
    string prompt = "Choose a drink or checkout (A-";
    prompt = prompt + lastLetter + "): ";

    while (true) {
        char choice = getLetter(prompt);
        if (choice == lastLetter) {
            return -1;
        }
        if (choice >= 'A' && choice < lastLetter) {
            return choice - 'A';
        }
        cout << "That is not a menu choice. Please choose A-"
            << lastLetter << "." << endl;
    }
}

// Asks for a drink size until the customer enters S, M, or L.
// Returns: 'S', 'M', or 'L'
char getSize() {
    while (true) {
        char sizeChoice = getLetter("Choose a size (S, M, or L): ");
        if (sizeChoice == 'S' || sizeChoice == 'M' || sizeChoice == 'L') {
            return sizeChoice;
        }
        cout << "That is not a size choice. Please choose S, M, or L." << endl;
    }
}

// Asks how many drinks the customer wants, without going over what is in stock.
// Parameters: inStock - how many of this drink are left
// Returns: a whole number from 1 to inStock
int getQuantity(int inStock) {
    int quantity;
    while (true) {
        cout << "How many would you like? (" << inStock << " left): ";
        if (cin >> quantity && quantity > 0 && quantity <= inStock) {
            clearRestOfLine();
            return quantity;
        }
        exitIfInputEnded();
        cout << "Enter a whole number from 1 to " << inStock << "." << endl;
        // Reset cin in case a non-number was typed, then drop the bad line.
        cin.clear();
        clearRestOfLine();
    }
}

// Collects the size and quantity for one drink, adds a line for it to the
// order, and records the sale for the inventory report.
// Parameters: itemNumber - index of the chosen drink
//             itemNames, smallPrices, mediumPrices, largePrices - menu data
//             quantitiesSold - drinks sold so far today (updated)
//             inStock - how many of this drink are left
//             orderDetails - the receipt's item lines (a line is added)
// Returns: the cost of this line (price x quantity)
double collectMenuItem(int itemNumber, string itemNames[],
    double smallPrices[], double mediumPrices[],
    double largePrices[], int quantitiesSold[], int inStock,
    string& orderDetails) {
    char sizeChoice = getSize();
    string sizeName;
    double itemPrice;

    // Look up the name and price for the chosen size.
    if (sizeChoice == 'S') {
        sizeName = "Small";
        itemPrice = smallPrices[itemNumber];
    }
    else if (sizeChoice == 'M') {
        sizeName = "Medium";
        itemPrice = mediumPrices[itemNumber];
    }
    else {
        sizeName = "Large";
        itemPrice = largePrices[itemNumber];
    }

    int quantity = getQuantity(inStock);
    double itemTotal = itemPrice * quantity;
    quantitiesSold[itemNumber] = quantitiesSold[itemNumber] + quantity;

    // Example line: "  Latte (Medium) x 2 @ $4.25 = $8.50"
    orderDetails = orderDetails + "  " + itemNames[itemNumber];
    orderDetails = orderDetails + " (" + sizeName + ") x ";
    orderDetails = orderDetails + to_string(quantity);
    orderDetails = orderDetails + " @ $" + formatAmount(itemPrice);
    orderDetails = orderDetails + " = $" + formatAmount(itemTotal) + "\n";

    return itemTotal;
}

// Takes one customer's whole order: shows the menu and adds drinks until
// the customer checks out with at least one item.
// Parameters: itemNames, smallPrices, mediumPrices, largePrices - menu data
//             quantitiesSold - drinks sold so far today (updated)
//             itemCount - number of drinks on the menu
//             startingInventory - how many of each drink the shop starts with
//             orderDetails - the receipt's item lines (filled in)
// Returns: the order subtotal before discount, tax, and tip
double takeOrder(string itemNames[], double smallPrices[],
    double mediumPrices[], double largePrices[],
    int quantitiesSold[], int itemCount, int startingInventory,
    string& orderDetails) {
    double subtotal = 0;

    while (true) {
        displayMenu(itemNames, smallPrices, mediumPrices, largePrices, itemCount);
        int choice = getMenuChoice(itemCount);

        if (choice == -1) {
            // Do not allow checkout with an empty order.
            if (orderDetails == "") {
                cout << "Add at least one item before checkout." << endl;
            }
            else {
                return subtotal;
            }
        }
        else {
            int inStock = startingInventory - quantitiesSold[choice];
            if (inStock <= 0) {
                cout << "Sorry, " << itemNames[choice] << " is sold out." << endl;
            }
            else {
                subtotal = subtotal + collectMenuItem(
                    choice, itemNames, smallPrices, mediumPrices, largePrices,
                    quantitiesSold, inStock, orderDetails);
            }
        }
    }
}

// Asks for the customer's name until something other than a blank line is typed.
// Returns: the customer's name
string getCustomerName() {
    string customerName;
    while (true) {
        cout << "Customer name: ";
        if (!getline(cin, customerName)) {
            exitIfInputEnded();
        }
        if (customerName != "") {
            return customerName;
        }
        cout << "Please enter a name." << endl;
    }
}

// Works out the member discount for an order.
// Parameters: subtotal - the order total before discount
//             member - true if the customer is a member
// Returns: the discount amount (10% for members, 0 otherwise)
double calculateDiscount(double subtotal, bool member) {
    if (member) {
        return subtotal * MEMBER_DISCOUNT_RATE;
    }
    return 0;
}

// Asks for a custom tip amount until a non-negative number is entered.
// Returns: the tip amount in dollars
double getCustomTip() {
    double tipAmount;
    while (true) {
        cout << "Enter your tip amount: $";
        if (cin >> tipAmount && tipAmount >= 0) {
            clearRestOfLine();
            return tipAmount;
        }
        exitIfInputEnded();
        cout << "Enter a valid non-negative tip amount." << endl;
        cin.clear();
        clearRestOfLine();
    }
}

// Shows the 15%, 20%, and 25% tip options and lets the customer pick one
// or enter their own amount.
// Parameters: taxableSubtotal - the amount the tip percentages are based on
// Returns: the tip amount in dollars
double getTip(double taxableSubtotal) {
    double tip15 = taxableSubtotal * 0.15;
    double tip20 = taxableSubtotal * 0.20;
    double tip25 = taxableSubtotal * 0.25;

    cout << endl;
    cout << left << setw(20) << "Tip Selection" << "Amount" << endl;
    cout << left << setw(20) << "A. 15%" << "$" << formatAmount(tip15) << endl;
    cout << left << setw(20) << "B. 20%" << "$" << formatAmount(tip20) << endl;
    cout << left << setw(20) << "C. 25%" << "$" << formatAmount(tip25) << endl;
    cout << "D. Other Amount" << endl;
    // Put alignment back to the default for later output.
    cout << right;

    while (true) {
        char choice = getLetter("Choose a tip (A-D): ");
        if (choice == 'A') {
            return tip15;
        }
        if (choice == 'B') {
            return tip20;
        }
        if (choice == 'C') {
            return tip25;
        }
        if (choice == 'D') {
            return getCustomTip();
        }
        cout << "That is not a tip choice. Please choose A-D." << endl;
    }
}

// Works out the tax, final total, and loyalty points for an order.
// Parameters: taxableSubtotal - the subtotal after the member discount
//             tip - the tip amount
//             totalTax - set to the state + county + municipal tax
//             total - set to the taxable subtotal + tax + tip
//             loyaltyPoints - set to one point for every $3 of the total
void calculateReceipt(double taxableSubtotal, double tip,
    double& totalTax, double& total, int& loyaltyPoints) {
    double stateTax = taxableSubtotal * STATE_TAX_RATE;
    double countyTax = taxableSubtotal * COUNTY_TAX_RATE;
    double municipalTax = taxableSubtotal * MUNICIPAL_TAX_RATE;
    totalTax = stateTax + countyTax + municipalTax;
    total = taxableSubtotal + totalTax + tip;
    // Converting to int drops any partial point.
    loyaltyPoints = int(total / DOLLARS_PER_LOYALTY_POINT);
}

// Builds one customer's receipt and prints it to the screen and receipt file.
// Parameters: receiptFile - the open receipt.txt file
//             customerName - name shown in the receipt header
//             orderDetails - the item lines for the order
//             subtotal, discount, taxableSubtotal, totalTax, tip, total -
//             the dollar amounts shown on the receipt
//             loyaltyPoints - number of stars to show
void printReceipt(ofstream& receiptFile, string customerName,
    string orderDetails, double subtotal, double discount,
    double taxableSubtotal, double totalTax, double tip,
    double total, int loyaltyPoints) {
    string receipt = "\n";
    receipt = receipt + "************* Receipt for " + customerName + " *************\n";
    receipt = receipt + "Coffee Shop Receipt\n";
    receipt = receipt + "Items:\n";
    receipt = receipt + orderDetails;
    receipt = receipt + "Subtotal:          $" + formatAmount(subtotal) + "\n";
    receipt = receipt + "Member discount:  -$" + formatAmount(discount) + "\n";
    receipt = receipt + "Taxable subtotal:  $" + formatAmount(taxableSubtotal) + "\n";
    receipt = receipt + "Total tax:         $" + formatAmount(totalTax) + "\n";
    receipt = receipt + "Tip:               $" + formatAmount(tip) + "\n";
    receipt = receipt + "Total:             $" + formatAmount(total) + "\n";

    // One star for each loyalty point earned.
    receipt = receipt + "Loyalty Points: " + string(loyaltyPoints, '*') + "\n";
    receipt = receipt + "**************************************************\n";

    printToBoth(receiptFile, receipt);
}

// Prints the number of customers and total sales for the day to the
// screen and the log file.
// Parameters: logFile - the open log.txt file
//             totalCustomers - how many customers were served
//             grandTotalSales - the sum of every customer's total
void printEndOfDaySummary(ofstream& logFile, int totalCustomers,
    double grandTotalSales) {
    string summary = "\nEnd of Day Summary\n";
    summary = summary + "Total customers: " + to_string(totalCustomers) + "\n";
    summary = summary + "Total sales: $" + formatAmount(grandTotalSales) + "\n";
    printToBoth(logFile, summary);
}

// Builds one row of the inventory table with lined-up columns.
// Parameters: itemName - text for the first column
//             start, change, end - text for the number columns
// Returns: the formatted row, ending in a newline
string formatInventoryRow(string itemName, string start,
    string change, string end) {
    stringstream row;
    row << left << setw(25) << itemName << right
        << setw(8) << start << setw(8) << change << setw(8) << end << "\n";
    return row.str();
}

// Prints how many of each drink the shop started with, sold, and has left,
// to the screen and the log file.
// Parameters: logFile - the open log.txt file
//             itemNames - drink names
//             quantitiesSold - how many of each drink were sold today
//             itemCount - number of drinks on the menu
//             startingInventory - how many of each drink the shop started with
void printInventory(ofstream& logFile, string itemNames[],
    int quantitiesSold[], int itemCount, int startingInventory) {
    string report = "\nDaily Inventory\n";
    report = report + formatInventoryRow("Item", "Start", "Change", "End");

    for (int i = 0; i < itemCount; i++) {
        report = report + formatInventoryRow(itemNames[i],
            to_string(startingInventory),
            to_string(-quantitiesSold[i]),
            to_string(startingInventory - quantitiesSold[i]));
    }
    printToBoth(logFile, report);
}

int main() {
    const int itemCount = 4;
    const int startingInventory = 50;
    string itemNames[itemCount];
    double smallPrices[itemCount];
    double mediumPrices[itemCount];
    double largePrices[itemCount];
    int quantitiesSold[itemCount] = { 0, 0, 0, 0 };

    if (!loadMenu(itemNames, smallPrices, mediumPrices, largePrices, itemCount)) {
        cout << "Could not open or read Menu.txt or Menu. Check the menu file." << endl;
        return 1;
    }

    ofstream receiptFile("receipt.txt");
    ofstream logFile("log.txt");
    if (!receiptFile || !logFile) {
        cout << "Could not open receipt.txt or log.txt for writing." << endl;
        return 1;
    }

    double grandTotalSales = 0;
    int totalCustomers = 0;
    bool anotherCustomer = true;

    // Serve customers until the cashier says there are no more.
    while (anotherCustomer) {
        string customerName = getCustomerName();
        string orderDetails = "";

        double subtotal = takeOrder(itemNames, smallPrices, mediumPrices,
            largePrices, quantitiesSold, itemCount, startingInventory,
            orderDetails);
        bool member = getYesNo("Are you a member? (Y/N): ");
        double discount = calculateDiscount(subtotal, member);
        double taxableSubtotal = subtotal - discount;
        double tip = getTip(taxableSubtotal);
        double totalTax;
        double total;
        int loyaltyPoints;

        calculateReceipt(taxableSubtotal, tip, totalTax, total, loyaltyPoints);
        printReceipt(receiptFile, customerName, orderDetails, subtotal, discount,
            taxableSubtotal, totalTax, tip, total, loyaltyPoints);

        grandTotalSales = grandTotalSales + total;
        totalCustomers = totalCustomers + 1;
        cout << endl;
        anotherCustomer = getYesNo("Is there another customer? (Y/N): ");
    }

    printEndOfDaySummary(logFile, totalCustomers, grandTotalSales);
    printInventory(logFile, itemNames, quantitiesSold, itemCount, startingInventory);
    return 0;
}
