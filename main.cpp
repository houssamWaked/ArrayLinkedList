#include <iostream>
#include <string>
#include <limits>
#include "List.h"

using namespace std;

void printMenu() {
    cout << "\n=== ArrayBased Linked List Tester ===\n"
         << "1. Insert Front\n"
         << "2. Delete Front\n"
         << "3. Insert After\n"
         << "4. Delete After\n"
         << "5. Traverse List\n"
         << "6. Size\n"
         << "7. Find\n"
         << "8. Clear List\n"
         << "9. Insert Sorted\n"
         << "10. Remove by Value\n"
         << "11. Sort List\n"
         << "12. Remove Duplicates (Unique)\n"
         << "0. Exit\n"
         << "Choice: ";
}

int main() {
    List<string> lst;
    int choice;

    do {
        printMenu();
        if (!(cin >> choice)) break;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        try {
            switch (choice) {
                case 1: {
                    cout << "Enter value to insert at front: ";
                    string v; getline(cin, v);
                    lst.insertFront(v);
                    cout << lst;
                    break;
                }
                case 2:
                    lst.deleteFront();
                    cout << lst;
                    break;

                case 3: {
                    cout << "Enter position index: ";
                    int pos; cin >> pos;
                    cin.ignore();
                    cout << "Enter value to insert after " << pos << ": ";
                    string v; getline(cin, v);
                    lst.insertAfter(pos, v);
                    cout << lst;
                    break;
                }
                case 4: {
                    cout << "Enter position index to delete after: ";
                    int pos; cin >> pos;
                    cin.ignore();
                    lst.deleteAfter(pos);
                    cout << lst;
                    break;
                }
                case 5:
                    cout << lst;
                    break;

                case 6:
                    cout << "Size: " << lst.size() << "\n";
                    break;

                case 7: {
                    cout << "Enter value to find: ";
                    string v; getline(cin, v);
                    int idx = lst.find(v);
                    if (idx == List<string>::NULL_VALUE)
                        cout << "Value not found.\n";
                    else
                        cout << "Found at index: " << idx << "\n";
                    break;
                }
                case 8:
                    lst.clear();
                    cout << "List cleared.\n";
                    cout << lst;
                    break;

                case 9: {
                    cout << "Enter value to insert sorted: ";
                    string v; getline(cin, v);
                    lst.insertSorted(v);
                    cout << lst;
                    break;
                }
                case 10: {
                    cout << "Enter value to remove: ";
                    string v; getline(cin, v);
                    bool removed = lst.remove(v);
                    cout << (removed ? "Removed.\n" : "Not found.\n");
                    cout << lst;
                    break;
                }
                case 11:
                    lst.sortList();
                    cout << "List sorted.\n";
                    cout << lst;
                    break;

                case 12:
                    lst.unique();
                    cout << "Duplicates removed.\n";
                    cout << lst;
                    break;

                case 0:
                    cout << "Exiting.\n";
                    break;

                default:
                    cout << "Invalid choice.\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }

    } while (choice != 0);

    return 0;
}
