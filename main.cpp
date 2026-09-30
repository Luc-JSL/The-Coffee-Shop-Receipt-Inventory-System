#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

int main() {
    string drinkName;
    string sizeName;
    char drinkChoice;
    char sizeChoice;
    char memberAnswer;
    int quantity;

    double smallPrice = 0;
    double mediumPrice = 0;
    double largePrice = 0;
    double unitPrice = 0;

    cout << "Drink Menu" << endl;
    cout << "A. Sprite - Small $2.50, Medium $3.50, Large $4.50" << endl;
    cout << "B. Powerade - Small $5.00, Medium $7.00, Large $9.00" << endl;
    cout << "C. Water - Small $1.50, Medium $3.00, Large $4.00" << endl;
    cout << "D. Pink Lemonade - Small $3.00, Medium $5.00, Large $7.50" << endl;

    cout << "Choose a drink (A-D): ";
    cin >> drinkChoice;
    drinkChoice = toupper(drinkChoice);

    switch (drinkChoice) {
        case 'A':
            drinkName = "Sprite";
            smallPrice = 2.50;
            mediumPrice = 3.50;
            largePrice = 4.50;
            break;
        case 'B':
            drinkName = "Powerade";
            smallPrice = 5.00;
            mediumPrice = 7.00;
            largePrice = 9.00;
            break;
        case 'C':
            drinkName = "Water";
            smallPrice = 1.50;
            mediumPrice = 3.00;
            largePrice = 4.00;
            break;
        case 'D':
            drinkName = "Pink Lemonade";
            smallPrice = 3.00;
            mediumPrice = 5.00;
            largePrice = 7.50;
            break;
        default:
            cout << "That is not a drink choice." << endl;
            return 0;
    }

    cout << "Choose a size (S, M, or L): ";
    cin >> sizeChoice;
    sizeChoice = toupper(sizeChoice);

    if (sizeChoice == 'S') {
        sizeName = "Small";
        unitPrice = smallPrice;
    } else if (sizeChoice == 'M') {
        sizeName = "Medium";
        unitPrice = mediumPrice;
    } else if (sizeChoice == 'L') {
        sizeName = "Large";
        unitPrice = largePrice;
    } else {
        cout << "That is not a size choice." << endl;
        return 0;
    }

    cout << "How many would you like? ";
    cin >> quantity;

    cout << "Are you a member? (Y/N): ";
    cin >> memberAnswer;

    double subtotal = unitPrice * quantity;
    double discount = 0;

    if (memberAnswer == 'Y' || memberAnswer == 'y') {
        discount = subtotal * 0.10;
    }

    double taxableSubtotal = subtotal - discount;
    double stateTax = taxableSubtotal * 0.65;
    double countyTax = taxableSubtotal * 0.05;
    double municipalTax = taxableSubtotal * 0.2125;
    double totalTax = stateTax + countyTax + municipalTax;

    double tip15 = taxableSubtotal * 0.15;
    double tip20 = taxableSubtotal * 0.20;
    double tip25 = taxableSubtotal * 0.25;
    double tipAmount = 0;
    char tipChoice;

    cout << fixed << setprecision(2);
    cout << endl;
    cout << "Coffee Shop Receipt" << endl;
    cout << "Drink: " << drinkName << endl;
    cout << "Size: " << sizeName << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Price: $" << unitPrice << endl;
    cout << "Subtotal: $" << subtotal << endl;
    cout << "Member discount: $" << discount << endl;
    cout << "Taxable subtotal: $" << taxableSubtotal << endl;

    cout << endl;
    cout << "Sales Taxes" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << left << setw(25) << "Tax Name"
         << setw(12) << "Rate"
         << "Tax Amount" << endl;
    cout << left << setw(25) << "Arkansas State Tax"
         << setw(12) << "6.5%"
         << "$" << stateTax << endl;
    cout << left << setw(25) << "Faulkner County Tax"
         << setw(12) << "0.5%"
         << "$" << countyTax << endl;
    cout << left << setw(25) << "Conway Municipal Tax"
         << setw(12) << "2.125%"
         << "$" << municipalTax << endl;
    cout << "Total tax: $" << totalTax << endl;

    cout << endl;
    cout << "Tip Selection" << setw(15) << "Amount" << endl;
    cout << left << setw(20) << "A. 15%" << "$" << tip15 << endl;
    cout << left << setw(20) << "B. 20%" << "$" << tip20 << endl;
    cout << left << setw(20) << "C. 25%" << "$" << tip25 << endl;
    cout << "D. Other Amount" << endl;
    cout << "Choose a tip (A-D): ";
    cin >> tipChoice;
    tipChoice = toupper(tipChoice);

    if (tipChoice == 'A') {
        tipAmount = tip15;
    } else if (tipChoice == 'B') {
        tipAmount = tip20;
    } else if (tipChoice == 'C') {
        tipAmount = tip25;
    } else if (tipChoice == 'D') {
        cout << "Enter your tip amount: $";
        cin >> tipAmount;
        if (tipAmount < 0) {
            cout << "The tip cannot be negative." << endl;
            return 0;
        }
    } else {
        cout << "That is not a tip choice." << endl;
        return 0;
    }

    double total = taxableSubtotal + totalTax + tipAmount;
    cout << "Tip: $" << tipAmount << endl;
    cout << "Total: $" << total << endl;

    cout << endl;
    cout << "Inventory Audit" << endl;
    cout << "Item: " << drinkName << endl;
    cout << "Size: " << sizeName << endl;
    cout << "Quantity sold: " << quantity << endl;

    return 0;
}