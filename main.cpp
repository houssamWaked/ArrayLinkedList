#include <iostream>
#include <string>
#include <limits>
#include "List.h"

void printMenu() {
    std::cout << "\n=== Array‑Based Linked List Tester ===\n"
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
              << "0. Exit\n"
              << "Choice: ";
}

void printList(const List<std::string>& lst) {
    std::cout << "List contents: ";
    lst.traverse([](const std::string& s){
        std::cout << s << " ";
    });
    std::cout << "\nFree‑list head index: "
              << lst.getFreeListHead()
              << "\n";
}

int main() {
    List<std::string> lst;
    int choice;

    do {
        printMenu();
        if (!(std::cin >> choice)) break;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        try {
            switch (choice) {
                case 1: {
                    std::cout << "Enter value to insert at front: ";
                    std::string v; std::getline(std::cin, v);
                    lst.insertFront(v);
                    printList(lst);
                    break;
                }
                case 2:
                    lst.deleteFront();
                    printList(lst);
                    break;

                case 3: {
                    std::cout << "Enter position index: ";
                    int pos; std::cin >> pos;
                    std::cin.ignore();
                    std::cout << "Enter value to insert after " << pos << ": ";
                    std::string v; std::getline(std::cin, v);
                    lst.insertAfter(pos, v);
                    printList(lst);
                    break;
                }
                case 4: {
                    std::cout << "Enter position index to delete after: ";
                    int pos; std::cin >> pos;
                    std::cin.ignore();
                    lst.deleteAfter(pos);
                    printList(lst);
                    break;
                }
                case 5:
                    printList(lst);
                    break;

                case 6:
                    std::cout << "Size: " << lst.size() << "\n";
                    break;

                case 7: {
                    std::cout << "Enter value to find: ";
                    std::string v; std::getline(std::cin, v);
                    int idx = lst.find(v);
                    if (idx == List<std::string>::NULL_VALUE)
                        std::cout << "Value not found.\n";
                    else
                        std::cout << "Found at index: " << idx << "\n";
                    break;
                }
                case 8:
                    lst.clear();
                    printList(lst);
                    break;

                case 9: {
                    std::cout << "Enter value to insert sorted: ";
                    std::string v; std::getline(std::cin, v);
                    lst.insertSorted(v);
                    printList(lst);
                    break;
                }
                case 10: {
                    std::cout << "Enter value to remove: ";
                    std::string v; std::getline(std::cin, v);
                    bool removed = lst.remove(v);
                    std::cout << (removed ? "Removed.\n" : "Not found.\n");
                    printList(lst);
                    break;
                }
                case 0:
                    std::cout << "Exiting.\n";
                    break;
                default:
                    std::cout << "Invalid choice.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    } while (choice != 0);

    return 0;
}
