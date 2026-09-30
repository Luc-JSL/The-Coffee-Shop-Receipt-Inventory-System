#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

int main() {
    string foodName;
    string sizeName;
    char drinkChoice;
    char sizeChoice;
    int quantity;
    double unitPrice;
    char memberAnswer;

    cout << fixed << setprecision(2);
    cout << "\n================ DRINK MENU ================\n";
    cout << left << setw(22) << "Drink"
         << right << setw(14) << "Small (s)"
         << setw(14) << "Medium (m)"
         << setw(14) << "Large (l)" << '\n';
    cout << left << setw(22) << "A. Sprite"
         << right << setw(14) << "$2.50"
         << setw(14) << "$3.50"
         << setw(14) << "$4.50" << '\n';
    cout << left << setw(22) << "B. Powerade"
         << right << setw(14) << "$5.00"
         << setw(14) << "$7.00"
         << setw(14) << "$9.00" << '\n';
    cout << left << setw(22) << "C. Water"
         << right << setw(14) << "$1.50"
         << setw(14) << "$3.00"
         << setw(14) << "$4.00" << '\n';
    cout << left << setw(22) << "D. Pink Lemonade"
         << right << setw(14) << "$3.00"
         << setw(14) << "$5.00"
         << setw(14) << "$7.50" << '\n';

    while (true) {
        cout << "Select a drink (A-D): ";
        cin >> drinkChoice;
        drinkChoice = static_cast<char>(toupper(static_cast<unsigned char>(drinkChoice)));
        if (drinkChoice >= 'A' && drinkChoice <= 'D') {
            break;
        }
        cout << "Invalid selection. Choose A, B, C, or D.\n";
    }

    while (true) {
        cout << "Select a size (S/M/L): ";
        cin >> sizeChoice;
        sizeChoice = static_cast<char>(toupper(static_cast<unsigned char>(sizeChoice)));
        if (sizeChoice == 'S' || sizeChoice == 'M' || sizeChoice == 'L') {
            break;
        }
        cout << "Invalid size. Choose S, M, or L.\n";
    }

    switch (drinkChoice) {
        case 'A':
            foodName = "Sprite";
            switch (sizeChoice) {
                case 'S': unitPrice = 2.50; break;
                case 'M': unitPrice = 3.50; break;
                case 'L': unitPrice = 4.50; break;
            }
            break;
        case 'B':
            foodName = "Powerade";
            switch (sizeChoice) {
                case 'S': unitPrice = 5.00; break;
                case 'M': unitPrice = 7.00; break;
                case 'L': unitPrice = 9.00; break;
            }
            break;
        case 'C':
            foodName = "Water";
            switch (sizeChoice) {
                case 'S': unitPrice = 1.50; break;
                case 'M': unitPrice = 3.00; break;
                case 'L': unitPrice = 4.00; break;
            }
            break;
        case 'D':
            foodName = "Pink Lemonade";
            switch (sizeChoice) {
                case 'S': unitPrice = 3.00; break;
                case 'M': unitPrice = 5.00; break;
                case 'L': unitPrice = 7.50; break;
            }
            break;
    }

    switch (sizeChoice) {
        case 'S': sizeName = "Small"; break;
        case 'M': sizeName = "Medium"; break;
        case 'L': sizeName = "Large"; break;
    }

    cout << "Enter quantity: ";
    cin >> quantity;

    cout << "Member? (y/n): ";
    cin >> memberAnswer;

    const double subtotal = quantity * unitPrice;
    const bool isMember = memberAnswer == 'y' || memberAnswer == 'Y';
    const double discount = isMember ? subtotal * 0.10 : 0.0;
    const double taxableSubtotal = subtotal - discount;
    const double tax = taxableSubtotal * 0.06;
    const double total = taxableSubtotal + tax;

    cout << "\n========================================\n";
    cout << "              COFFEE SHOP\n";
    cout << "========================================\n";
    cout << "Item: " << foodName << '\n';
    cout << "Size: " << sizeName << '\n';
    cout << "Quantity: " << quantity << '\n';
    cout << "Unit Price: $" << unitPrice << '\n';
    cout << "Member: " << (isMember ? "Yes" : "No") << '\n';
    cout << "----------------------------------------\n";
    cout << "Subtotal: $" << subtotal << '\n';
    cout << "Member Discount: $" << discount << '\n';
    cout << "Tax: $" << tax << '\n';
    cout << "Total: $" << total << '\n';
    cout << "\nInventory Audit\n";
    cout << left << setw(20) << "Item"
         << setw(12) << "Size"
         << right << setw(10) << "Quantity"
         << setw(14) << "Unit Price" << '\n';
    cout << left << setw(20) << foodName
         << setw(12) << sizeName
         << right << setw(10) << quantity
         << setw(13) << "$" << unitPrice << '\n';
    cout << "========================================\n";

    return 0;
}