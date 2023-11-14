#include<iostream>
#include<iomanip>
#include<conio.h>
#include<string>

using namespace std;
const int maxBooks = 100;

struct Book
{
    int bookID;
    string title;
    string author;
    string publisher;
    double cost;
    int stock;
};

void addBook(Book* inventory, int& bookCount) 
{
    if (bookCount < maxBooks)
    {
        cout << "Enter Book ID: ";
        cin >> inventory[bookCount].bookID;
        cin.ignore(); // Clear the newline character from the input buffer
        cout << "Enter Title: ";
        getline(cin, inventory[bookCount].title);
        cout << "Enter Author Name: ";
        getline(cin, inventory[bookCount].author);
        cout << "Enter Publisher's Name: ";
        getline( cin, inventory[bookCount].publisher);
        cout << "Enter Cost: ";
        cin >> inventory[bookCount].cost;
        cout << "Enter Stock: ";
        cin >> inventory[bookCount].stock;

        bookCount++; 
        cout << "Book added to the inventory." << endl;
    } 
    else 
    {
        cout << "Inventory is full. Cannot add more books." << endl;
    }
}

void updateBook(Book* inventory, int bookCount, int bookID) 
{
    for (int i = 0; i < bookCount; i++) 
    {
        if (inventory[i].bookID == bookID) 
        {
            cout << "Enter new Title: ";
            cin.ignore();
            getline( cin, inventory[i].title);
            cout << "Enter new Author Name: ";
            getline( cin, inventory[i].author);
            cout << "Enter new Cost: ";
            cin >> inventory[i].cost;
            cout << "Enter new Stock: ";
            cin >> inventory[i].stock;

            cout << "Book details updated." <<  endl;
            return; 
        }
    }
    cout << "Book not found in the inventory." <<  endl;
}

void removeBook(Book* inventory, int& bookCount, int bookID) 
{
    for (int i = 0; i < bookCount; i++) 
    {
        if (inventory[i].bookID == bookID) 
        {
            for (int j = i; j < bookCount - 1; j++) 
            {
                inventory[j] = inventory[j + 1];
            }
            bookCount--; 
            cout << "Book removed from the inventory." <<  endl;
            return; 
        }
    }
    cout << "Book not found in the inventory." <<  endl;
}

void displayBookDetails(Book* inventory, int bookCount, int bookID) 
{
    for (int i = 0; i < bookCount; i++) 
    {
        if (inventory[i].bookID == bookID) 
        {
            cout << "Book ID: " << inventory[i].bookID <<  endl;
            cout << "Title: " << inventory[i].title <<  endl;
            cout << "Author Name: " << inventory[i].author <<  endl;
            cout << "Publisher's Name: " << inventory[i].publisher <<  endl;
            cout << "Cost: " << inventory[i].cost <<  endl;
            cout << "Stock: " << inventory[i].stock <<  endl;
            return; 
        }
    }
    cout << "Book not found in the inventory." <<  endl;
}

void displayAllBooks(Book* inventory, int bookCount) 
{
    for (int i = 0; i < bookCount; i++) 
    {
        cout << "Book ID: " << inventory[i].bookID <<  endl;
        cout << "Title: " << inventory[i].title <<  endl;
        cout << "Author Name: " << inventory[i].author <<  endl;
        cout << "Publisher's Name: " << inventory[i].publisher <<  endl;
        cout << "Cost: " << inventory[i].cost <<  endl;
        cout << "Stock: " << inventory[i].stock <<  endl;
        cout << "-------------------------" <<  endl;
    }
}

void searchBooks(Book* inventory, int bookCount, int bookID) 
{
    for (int i = 0; i < bookCount; i++) 
    {
        if (inventory[i].bookID == bookID) 
        {
            displayBookDetails(inventory, bookCount, bookID);
            return;
        }
    }
    cout << "Book not found in the inventory." <<  endl;
}


void purchaseBook(Book* inventory, int bookCount, int bookID)               //I am reducing the stock as well as the bookcount
{
    for (int i = 0; i < bookCount; i++) 
    {
        if (inventory[i].bookID == bookID) 
        {
            if (inventory[i].stock > 0) 
            {
                inventory[i].stock--;
                cout << "Book purchased. Stock decreased." <<  endl;
            } 
            else 
            {
                cout << "Book is out of stock." <<  endl;
            }
            return; 
        }
    }
    cout << "Book not found in the inventory." <<  endl;
}

int main() 
{
    Book* bookInventory = new Book[maxBooks];
    int bookCount = 0;

    int choice;

    while (true) 
    {
        cout << "\nBookshop Inventory System" <<  endl;
        cout << "1. Add a Book" <<  endl;
        cout << "2. Update Book Details" <<  endl;
        cout << "3. Remove a Book" <<  endl;
        cout << "4. Display Book Details" <<  endl;
        cout << "5. Display All Books" <<  endl;
        cout << "6. Search for a Book by Book ID" <<  endl;
        cout << "7. Purchase a Book" <<  endl;
        cout << "8. Exit" <<  endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                addBook(bookInventory, bookCount);
                break;
            case 2:
                int updateID;
                cout << "Enter Book ID to update: ";
                cin >> updateID;
                updateBook(bookInventory, bookCount, updateID);
                break;
            case 3:
                int removeID;
                cout << "Enter Book ID to remove: ";
                cin >> removeID;
                removeBook(bookInventory, bookCount, removeID);
                break;
            case 4:
                int displayID;
                cout << "Enter Book ID to display: ";
                cin >> displayID;
                displayBookDetails(bookInventory, bookCount, displayID);
                break;
            case 5:
                displayAllBooks(bookInventory, bookCount);
                break;
            case 6:
                int searchID;
                cout << "Enter Book ID to search: ";
                cin >> searchID;
                searchBooks(bookInventory, bookCount, searchID);
                break;
            case 7:
                int purchaseID;
                cout << "Enter Book ID to purchase: ";
                cin >> purchaseID;
                purchaseBook(bookInventory, bookCount, purchaseID);
                break;
            case 8:
                delete[] bookInventory;                        // Exit the program
                return 0;
            default:
                cout << "Invalid choice. Please try again." <<  endl;
        }
    }
    return 0;
}
