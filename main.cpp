#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

int main() {
    string foodName;
    char itemCode;
    int quantity;
    double unitPrice;
    char memberAnswer;
    string cashierNotes;

    cout << "Enter food name: ";
    getline(cin, foodName);

    cout << "Enter item code: ";
    cin >> itemCode;

    cout << "Enter quantity: ";
    cin >> quantity;

    cout << "Enter unit price: ";
    cin >> unitPrice;

    cout << "Member? (y/n): ";
    cin >> memberAnswer;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Cashier notes: ";
    getline(cin, cashierNotes);

    const double subtotal = quantity * unitPrice;
    const bool isMember = memberAnswer == 'y' || memberAnswer == 'Y';
    const double discount = isMember ? subtotal * 0.10 : 0.0;
    const double taxableSubtotal = subtotal - discount;
    const double tax = taxableSubtotal * 0.06;
    const double total = taxableSubtotal + tax;

    cout << "\n========================================\n";
    cout << "              COFFEE SHOP\n";
    cout << "========================================\n";
    cout << "Food Name: " << foodName << '\n';
    cout << "Item Code: " << itemCode << '\n';
    cout << "Quantity: " << quantity << '\n';
    cout << fixed << setprecision(2);
    cout << "Unit Price: " << unitPrice << '\n';
    cout << "Member: " << (isMember ? "Yes" : "No") << '\n';
        cout << "Cashier Notes: " << cashierNotes << '\n';
    cout << "----------------------------------------\n";
        cout << "Subtotal: " << subtotal << '\n';
        cout << "Member Discount: " << discount << '\n';
        cout << "Tax: " << tax << '\n';
        cout << "Total: " << total << '\n';
        cout << "\nInventory Audit\n";
        cout << left << setw(20) << "Food Name"
            << setw(12) << "Item Code"
            << right << setw(10) << "Quantity"
            << setw(14) << "Unit Price" << '\n';
        cout << left << setw(20) << foodName
            << setw(12) << itemCode
            << right << setw(10) << quantity
            << setw(14) << unitPrice << '\n';
    cout << "========================================\n";

    return 0;
}