#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <limits>

using namespace std;

string formatAmount(double amount) {
    string amountText = to_string(amount);
    int decimalPoint = amountText.find('.');
    return amountText.substr(0, decimalPoint + 3);
}

int main() {
    double grandTotalSales = 0;
    int totalCustomers = 0;
    char anotherCustomer = 'Y';

    while (anotherCustomer == 'Y') {
        string customerName;
        string orderDetails = "";
        string inventoryDetails = "";
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

            cout << endl;
            cout << "Drink Menu" << endl;
            cout << "A. Sprite - Small $2.50, Medium $3.50, Large $4.50" << endl;
            cout << "B. Powerade - Small $5.00, Medium $7.00, Large $9.00" << endl;
            cout << "C. Water - Small $1.50, Medium $3.00, Large $4.00" << endl;
            cout << "D. Pink Lemonade - Small $3.00, Medium $5.00, Large $7.50" << endl;
            cout << "E. Checkout" << endl;
            cout << "Choose a drink or checkout (A-E): ";
            cin >> menuChoice;

            if (menuChoice.length() == 1) {
                menuChoice[0] = static_cast<char>(toupper(menuChoice[0]));
            }

            if (menuChoice == "E") {
                if (orderDetails == "") {
                    cout << "Add at least one item before checkout." << endl;
                }
                else {
                    break;
                }
            }
            else if (menuChoice == "A") {
                drinkName = "Sprite";
                smallPrice = 2.50;
                mediumPrice = 3.50;
                largePrice = 4.50;
            }
            else if (menuChoice == "B") {
                drinkName = "Powerade";
                smallPrice = 5.00;
                mediumPrice = 7.00;
                largePrice = 9.00;
            }
            else if (menuChoice == "C") {
                drinkName = "Water";
                smallPrice = 1.50;
                mediumPrice = 3.00;
                largePrice = 4.00;
            }
            else if (menuChoice == "D") {
                drinkName = "Pink Lemonade";
                smallPrice = 3.00;
                mediumPrice = 5.00;
                largePrice = 7.50;
            }
            else if (menuChoice != "E") {
                cout << "That is not a menu choice. Please choose A-E." << endl;
            }

            if (menuChoice == "A" || menuChoice == "B" ||
                menuChoice == "C" || menuChoice == "D") {
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
                    else {
                        cout << "That is not a size choice. Please choose S, M, or L." << endl;
                    }
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

                orderDetails = orderDetails + drinkName + " - " + sizeName;
                orderDetails = orderDetails + " x " + to_string(quantity);
                orderDetails = orderDetails + " @ $" + formatAmount(unitPrice);
                orderDetails = orderDetails + " = $" + formatAmount(itemSubtotal) + "\n";

                inventoryDetails = inventoryDetails + "Item: " + drinkName + "\n";
                inventoryDetails = inventoryDetails + "Size: " + sizeName + "\n";
                inventoryDetails = inventoryDetails + "Quantity sold: " + to_string(quantity) + "\n";
            }
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
        cout << "Tip Selection" << setw(15) << "Amount" << endl;
        cout << left << setw(20) << "A. 15%" << "$" << tip15 << endl;
        cout << left << setw(20) << "B. 20%" << "$" << tip20 << endl;
        cout << left << setw(20) << "C. 25%" << "$" << tip25 << endl;
        cout << "D. Other Amount" << endl;

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

        cout << fixed << setprecision(2);
        cout << endl;
        cout << "Coffee Shop Receipt" << endl;
        cout << "Customer: " << customerName << endl;
        cout << "Items" << endl;
        cout << orderDetails;
        cout << "Subtotal: $" << subtotal << endl;
        cout << "Member discount: $" << discount << endl;
        cout << "Taxable subtotal: $" << taxableSubtotal << endl;
        cout << "Total tax: $" << totalTax << endl;
        cout << "Tip: $" << tipAmount << endl;
        cout << "Total: $" << total << endl;

        int loyaltyPoints = static_cast<int>(total / 3);
        cout << "Loyalty Points: ";
        for (int i = 0; i < loyaltyPoints; i++) {
            cout << "*";
        }
        cout << endl;

        cout << endl;
        cout << "Inventory Audit" << endl;
        cout << inventoryDetails;

        grandTotalSales = grandTotalSales + total;
        totalCustomers = totalCustomers + 1;

        while (true) {
            string anotherAnswer;
            cout << "Is there another customer? (Y/N): ";
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
    return 0;
}