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

    const double total = quantity * unitPrice;
    const bool isMember = memberAnswer == 'y' || memberAnswer == 'Y';

    cout << "\n========================================\n";
    cout << "              COFFEE SHOP\n";
    cout << "========================================\n";
    cout << "Food Name: " << foodName << '\n';
    cout << "Item Code: " << itemCode << '\n';
    cout << "Quantity: " << quantity << '\n';
    cout << fixed << setprecision(2);
    cout << "Unit Price: " << unitPrice << '\n';
    cout << "Member: " << (isMember ? "Yes" : "No") << '\n';
    cout << "----------------------------------------\n";
    cout << "Total: " << total << '\n';
    cout << "========================================\n";

    return 0;
}