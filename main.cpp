#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <fstream>
#include <limits>

using namespace std;

string formatAmount(double amount) {
    string amountText = to_string(amount);
    int decimalPoint = amountText.find('.');
    return amountText.substr(0, decimalPoint + 3);
}

// Reads the next line that is not blank, so blank lines in the menu are skipped
string readMenuLine(ifstream& menuFile) {
    string line;
    while (getline(menuFile, line)) {
        if (!line.empty() && line[line.length() - 1] == '\r') {
            line = line.substr(0, line.length() - 1);
        }
        if (line != "") {
            return line;
        }
    }
    return "";
}

int main() {
    // Phase 2: variables for the menu, filled in from the file
    string food1, food2, food3, food4;
    double food1Sm, food1Med, food1Lg;
    double food2Sm, food2Med, food2Lg;
    double food3Sm, food3Med, food3Lg;
    double food4Sm, food4Med, food4Lg;

    // The menu file goes in the same folder as the .cpp file
    ifstream menuFile("Menu.txt");
    if (!menuFile) {
        menuFile.clear();
        menuFile.open("Menu");
    }
    if (!menuFile) {
        cout << "Could not open Menu.txt. Put it in the same folder as your .cpp file." << endl;
        return 1;
    }

    food1 = readMenuLine(menuFile);
    food1Sm = stod(readMenuLine(menuFile));
    food1Med = stod(readMenuLine(menuFile));
    food1Lg = stod(readMenuLine(menuFile));

    food2 = readMenuLine(menuFile);
    food2Sm = stod(readMenuLine(menuFile));
    food2Med = stod(readMenuLine(menuFile));
    food2Lg = stod(readMenuLine(menuFile));

    food3 = readMenuLine(menuFile);
    food3Sm = stod(readMenuLine(menuFile));
    food3Med = stod(readMenuLine(menuFile));
    food3Lg = stod(readMenuLine(menuFile));

    food4 = readMenuLine(menuFile);
    food4Sm = stod(readMenuLine(menuFile));
    food4Med = stod(readMenuLine(menuFile));
    food4Lg = stod(readMenuLine(menuFile));

    menuFile.close();

    // Phase 3: output files for the receipt and the inventory log
    ofstream receipt_fout("receipt.txt");
    ofstream log_fout("log.txt");
    if (!receipt_fout || !log_fout) {
        cout << "Could not open receipt.txt or log.txt for writing." << endl;
        return 1;
    }

    // Small, medium and large each count as one of that item
    int startingInventory = 50;
    int food1Sold = 0, food2Sold = 0, food3Sold = 0, food4Sold = 0;

    double grandTotalSales = 0;
    int totalCustomers = 0;
    char anotherCustomer = 'Y';

    while (anotherCustomer == 'Y') {
        string customerName;
        string orderDetails = "";
        double subtotal = 0;

        cout << "Customer name: ";
        getline(cin, customerName);

        while (true) {
            string menuChoice;
            string drinkName;
            string sizeName;
            double smallPrice = 0;
            double mediumPrice = 0;
            double largePrice = 0;
            int foodNumber = 0;

            cout << endl;
            cout << "Drink Menu" << endl;
            cout << fixed << setprecision(2);
            cout << "A. " << food1 << " - Small $" << food1Sm
                 << ", Medium $" << food1Med << ", Large $" << food1Lg << endl;
            cout << "B. " << food2 << " - Small $" << food2Sm
                 << ", Medium $" << food2Med << ", Large $" << food2Lg << endl;
            cout << "C. " << food3 << " - Small $" << food3Sm
                 << ", Medium $" << food3Med << ", Large $" << food3Lg << endl;
            cout << "D. " << food4 << " - Small $" << food4Sm
                 << ", Medium $" << food4Med << ", Large $" << food4Lg << endl;
            cout << "E. Checkout" << endl;
            cout << "Choose a drink or checkout (A-E): ";
            cin >> menuChoice;

            if (menuChoice.length() == 1) {
                menuChoice[0] = static_cast<char>(toupper(menuChoice[0]));
            }

            if (menuChoice == "E") {
                if (orderDetails == "") {
                    cout << "Add at least one item before checkout." << endl;
                    continue;
                }
                break;
            }
            else if (menuChoice == "A") {
                foodNumber = 1;
                drinkName = food1;
                smallPrice = food1Sm;
                mediumPrice = food1Med;
                largePrice = food1Lg;
            }
            else if (menuChoice == "B") {
                foodNumber = 2;
                drinkName = food2;
                smallPrice = food2Sm;
                mediumPrice = food2Med;
                largePrice = food2Lg;
            }
            else if (menuChoice == "C") {
                foodNumber = 3;
                drinkName = food3;
                smallPrice = food3Sm;
                mediumPrice = food3Med;
                largePrice = food3Lg;
            }
            else if (menuChoice == "D") {
                foodNumber = 4;
                drinkName = food4;
                smallPrice = food4Sm;
                mediumPrice = food4Med;
                largePrice = food4Lg;
            }
            else {
                cout << "That is not a menu choice. Please choose A-E." << endl;
                continue;
            }

            string sizeChoice;
            double unitPrice = 0;
            while (true) {
                cout << "Choose a size (S, M, or L): ";
                cin >> sizeChoice;
                if (sizeChoice.length() == 1) {
                    sizeChoice[0] = static_cast<char>(toupper(sizeChoice[0]));
                }

                if (sizeChoice == "S") {
                    sizeName = "Small";
                    unitPrice = smallPrice;
                    break;
                }
                else if (sizeChoice == "M") {
                    sizeName = "Medium";
                    unitPrice = mediumPrice;
                    break;
                }
                else if (sizeChoice == "L") {
                    sizeName = "Large";
                    unitPrice = largePrice;
                    break;
                }
                cout << "That is not a size choice. Please choose S, M, or L." << endl;
            }

            int quantity;
            while (true) {
                cout << "How many would you like? ";
                if (cin >> quantity && quantity > 0) {
                    break;
                }
                cout << "Enter a whole number greater than zero." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            double itemSubtotal = unitPrice * quantity;
            subtotal = subtotal + itemSubtotal;

            if (foodNumber == 1) {
                food1Sold = food1Sold + quantity;
            }
            else if (foodNumber == 2) {
                food2Sold = food2Sold + quantity;
            }
            else if (foodNumber == 3) {
                food3Sold = food3Sold + quantity;
            }
            else {
                food4Sold = food4Sold + quantity;
            }

            orderDetails = orderDetails + "  " + drinkName + " (" + sizeName + ")";
            orderDetails = orderDetails + " x " + to_string(quantity);
            orderDetails = orderDetails + " @ $" + formatAmount(unitPrice);
            orderDetails = orderDetails + " = $" + formatAmount(itemSubtotal) + "\n";
        }

        char memberAnswer;
        while (true) {
            cout << "Are you a member? (Y/N): ";
            cin >> memberAnswer;
            memberAnswer = static_cast<char>(toupper(memberAnswer));
            if (memberAnswer == 'Y' || memberAnswer == 'N') {
                break;
            }
            cout << "Please enter Y or N." << endl;
        }

        double discount = 0;
        if (memberAnswer == 'Y') {
            discount = subtotal * 0.10;
        }

        double taxableSubtotal = subtotal - discount;
        double stateTax = taxableSubtotal * 0.065;
        double countyTax = taxableSubtotal * 0.005;
        double municipalTax = taxableSubtotal * 0.02125;
        double totalTax = stateTax + countyTax + municipalTax;

        double tip15 = taxableSubtotal * 0.15;
        double tip20 = taxableSubtotal * 0.20;
        double tip25 = taxableSubtotal * 0.25;
        double tipAmount = 0;
        char tipChoice;

        cout << endl;
        cout << left << setw(20) << "Tip Selection" << "Amount" << endl;
        cout << left << setw(20) << "A. 15%" << "$" << tip15 << endl;
        cout << left << setw(20) << "B. 20%" << "$" << tip20 << endl;
        cout << left << setw(20) << "C. 25%" << "$" << tip25 << endl;
        cout << "D. Other Amount" << endl;
        cout << right;

        while (true) {
            cout << "Choose a tip (A-D): ";
            cin >> tipChoice;
            tipChoice = static_cast<char>(toupper(tipChoice));

            if (tipChoice == 'A') {
                tipAmount = tip15;
                break;
            }
            else if (tipChoice == 'B') {
                tipAmount = tip20;
                break;
            }
            else if (tipChoice == 'C') {
                tipAmount = tip25;
                break;
            }
            else if (tipChoice == 'D') {
                cout << "Enter your tip amount: $";
                if (cin >> tipAmount && tipAmount >= 0) {
                    break;
                }
                cout << "Enter a valid non-negative tip amount." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                cout << "That is not a tip choice. Please choose A-D." << endl;
            }
        }

        double total = taxableSubtotal + totalTax + tipAmount;
        int loyaltyPoints = static_cast<int>(total / 3);

        // Receipt: every line goes to the console and to receipt.txt
        cout << fixed << setprecision(2);
        receipt_fout << fixed << setprecision(2);

        cout << endl;
        receipt_fout << endl;
        cout << "************* Receipt for " << customerName << " *************" << endl;
        receipt_fout << "************* Receipt for " << customerName << " *************" << endl;
        cout << "Coffee Shop Receipt" << endl;
        receipt_fout << "Coffee Shop Receipt" << endl;
        cout << "Items:" << endl;
        receipt_fout << "Items:" << endl;
        cout << orderDetails;
        receipt_fout << orderDetails;
        cout << "Subtotal:          $" << subtotal << endl;
        receipt_fout << "Subtotal:          $" << subtotal << endl;
        cout << "Member discount:  -$" << discount << endl;
        receipt_fout << "Member discount:  -$" << discount << endl;
        cout << "Taxable subtotal:  $" << taxableSubtotal << endl;
        receipt_fout << "Taxable subtotal:  $" << taxableSubtotal << endl;
        cout << "Total tax:         $" << totalTax << endl;
        receipt_fout << "Total tax:         $" << totalTax << endl;
        cout << "Tip:               $" << tipAmount << endl;
        receipt_fout << "Tip:               $" << tipAmount << endl;
        cout << "Total:             $" << total << endl;
        receipt_fout << "Total:             $" << total << endl;

        cout << "Loyalty Points: ";
        receipt_fout << "Loyalty Points: ";
        for (int i = 0; i < loyaltyPoints; i++) {
            cout << "*";
            receipt_fout << "*";
        }
        cout << endl;
        receipt_fout << endl;
        cout << "**************************************************" << endl;
        receipt_fout << "**************************************************" << endl;

        grandTotalSales = grandTotalSales + total;
        totalCustomers = totalCustomers + 1;

        while (true) {
            string anotherAnswer;
            cout << endl << "Is there another customer? (Y/N): ";
            cin >> anotherAnswer;
            if (anotherAnswer.length() == 1) {
                anotherAnswer[0] = static_cast<char>(toupper(anotherAnswer[0]));
            }
            if (anotherAnswer == "Y" || anotherAnswer == "N") {
                anotherCustomer = anotherAnswer[0];
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            cout << "Please enter Y or N." << endl;
        }
    }

    cout << endl;
    cout << "End of Day Summary" << endl;
    cout << "Total customers: " << totalCustomers << endl;
    cout << "Total sales: $" << fixed << setprecision(2) << grandTotalSales << endl;

    // Log: updated inventory goes to the console and to log.txt
    cout << endl;
    log_fout << "Daily Inventory" << endl;
    cout << "Daily Inventory" << endl;

    cout << left << setw(25) << "Item" << right << setw(8) << "Start"
         << setw(8) << "Change" << setw(8) << "End" << endl;
    log_fout << left << setw(25) << "Item" << right << setw(8) << "Start"
             << setw(8) << "Change" << setw(8) << "End" << endl;

    cout << left << setw(25) << food1 << right << setw(8) << startingInventory
         << setw(8) << -food1Sold << setw(8) << startingInventory - food1Sold << endl;
    log_fout << left << setw(25) << food1 << right << setw(8) << startingInventory
             << setw(8) << -food1Sold << setw(8) << startingInventory - food1Sold << endl;

    cout << left << setw(25) << food2 << right << setw(8) << startingInventory
         << setw(8) << -food2Sold << setw(8) << startingInventory - food2Sold << endl;
    log_fout << left << setw(25) << food2 << right << setw(8) << startingInventory
             << setw(8) << -food2Sold << setw(8) << startingInventory - food2Sold << endl;

    cout << left << setw(25) << food3 << right << setw(8) << startingInventory
         << setw(8) << -food3Sold << setw(8) << startingInventory - food3Sold << endl;
    log_fout << left << setw(25) << food3 << right << setw(8) << startingInventory
             << setw(8) << -food3Sold << setw(8) << startingInventory - food3Sold << endl;

    cout << left << setw(25) << food4 << right << setw(8) << startingInventory
         << setw(8) << -food4Sold << setw(8) << startingInventory - food4Sold << endl;
    log_fout << left << setw(25) << food4 << right << setw(8) << startingInventory
             << setw(8) << -food4Sold << setw(8) << startingInventory - food4Sold << endl;

    receipt_fout.close();
    log_fout.close();
    return 0;
}
