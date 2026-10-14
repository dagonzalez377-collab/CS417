#include <iostream>
#include <string>
#include <limits>
#include "Tree.h"
#include "Card.h"

using namespace std;

int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Please enter a number." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    Tree<Card> deck;
    int choice = 0;

    cout << "=== Index Card Deck ===" << endl;

    while (choice != 7) {
        cout << endl
             << "1. Add a card" << endl
             << "2. Search for a card" << endl
             << "3. Delete a card" << endl
             << "4. Print deck (inorder)" << endl
             << "5. Print deck (preorder)" << endl
             << "6. Print deck (postorder)" << endl
             << "7. Quit" << endl;
        choice = readInt("Choice: ");

        if (choice == 1) {
            int idx = readInt("Index number: ");
            if (deck.find(Card(idx)).index != -1) {
                cout << "A card with index " << idx << " already exists." << endl;
                continue;
            }
            string keyword, note;
            cout << "Keyword: ";
            getline(cin, keyword);
            cout << "Note: ";
            getline(cin, note);
            deck.insert(Card(idx, keyword, note));
            cout << "Card added." << endl;
        } else if (choice == 2) {
            int idx = readInt("Index number to find: ");
            Card c = deck.find(Card(idx));
            if (c.index == -1)
                cout << "Card " << idx << " not found." << endl;
            else
                cout << "Found: " << c << endl;
        } else if (choice == 3) {
            int idx = readInt("Index number to delete: ");
            if (deck.find(Card(idx)).index == -1) {
                cout << "Card " << idx << " not found." << endl;
            } else {
                deck.remove(Card(idx));
                cout << "Card " << idx << " deleted." << endl;
            }
        } else if (choice == 4) {
            cout << "-- Inorder --" << endl;
            deck.inorder();
        } else if (choice == 5) {
            cout << "-- Preorder --" << endl;
            deck.preorder();
        } else if (choice == 6) {
            cout << "-- Postorder --" << endl;
            deck.postorder();
        } else if (choice != 7) {
            cout << "Invalid choice." << endl;
        }
    }

    cout << "Goodbye!" << endl;
    return 0;
}
