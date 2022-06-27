#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

bool Locations[10][10] = {0};
string Authors[100] = {};
string Genres[100] = {};

// A book node for implementation of linked list
struct Book
{
    string Name = "";
    string Author = "Unknown";
    string Genre = "Unknown";
    int row = 0, shelf = 0;
    float Cost = 0;
    int Pages = 0;
    string Quote = "";
    Book *Next = nullptr;

    Book(string name, string author, string genre, float cost, int pages, string quote)
    {

        // Checks if there is free space on the shelfs
        bool bookStored = 0;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (!Locations[i][j])
                {
                    row = i + 1;
                    shelf = j + 1;
                    Locations[i][j] = 1;
                    bookStored = 1;
                    i = 10;
                    j = 10; // breaks both loops
                }
            }
        }
        if (!bookStored)
            cout << "\nWarning: Shelf is full. Please increase storage capacity.\n\n";

        // Adds author to Authors list if it doesn't already exist
        if (author.length())
        {
            Author = author;
            bool alreadyExists = 0;
            int i;
            for (i = 0; i < 100; i++)
            {
                string name = Authors[i];
                if (name == author)
                {
                    alreadyExists = 1;
                    break;
                }
                if (!name.length())
                    break;
            }
            if (!alreadyExists)
                Authors[i] = author;
        }

        // Adds genre to Genres list if it doesn't already exist
        if (genre.length())
        {
            Genre = genre;
            bool alreadyExists = 0;
            int i;
            for (i = 0; i < 100; i++)
            {
                string name = Genres[i];
                if (name == genre)
                {
                    alreadyExists = 1;
                    break;
                }
                if (!name.length())
                    break;
            }
            if (!alreadyExists)
                Genres[i] = genre;
        }

        Name = name;
        Cost = cost;
        Pages = pages;
        Quote = quote;
    }
};

// Inserting a node in linkedlist
void insert(Book *newBook, Book **ptrToHead)
{
    Book *indexPtr = *ptrToHead;
    newBook->Next = indexPtr;
    *ptrToHead = newBook;
}

// Ask user for information of new book and add book to library
void addBook(Book **ptrToHead)
{
    string name, author, genre, quote = "";
    int pages = 0;
    float cost = 0;
    cin.sync(); // Discards the input buffer
    cout << "\nEnter name of book >>> ";
    getline(cin, name);
    cout << "Enter name of author (Leave blank if not specified) >>> ";
    getline(cin, author);
    cout << "Enter genre of book (Leave blank if not specified) >>> ";
    getline(cin, genre);
    cout << "Enter famous quote in the book (Leave blank if not specified) >>> ";
    getline(cin, quote);
    cout << "Enter cost of book >>> ";
    cin >> cost;
    cout << "Enter no. of pages in book (0 if not specified)>>> ";
    cin >> pages;

    if (!genre.length())
        genre = "Unknown";
    Book *newBook = new Book(name, author, genre, cost, pages, quote);
    insert(newBook, ptrToHead);
    cin.sync();
    string temp;
    cout << "\nAdded Successfully. Press Enter to Continue...";
    getline(cin, temp);
    system("CLS");
}

// Remove a node from linked list
void pop(Book *ptrToBook, Book **ptrToHead)
{
    Book *indexPtr = *ptrToHead;
    while (indexPtr->Next != ptrToBook)
    {
        indexPtr = indexPtr->Next;
    }
    Book *ptrToCurrent = indexPtr->Next;
    indexPtr->Next = ptrToCurrent->Next;
    free(ptrToCurrent);
}

// Reverse the linked list
void reverse(Book **ptrToHead)
{
    Book *previous = nullptr;
    Book *indexPtr = *ptrToHead;
    Book *temp;
    while (indexPtr != nullptr)
    {
        temp = indexPtr->Next;
        indexPtr->Next = previous;
        previous = indexPtr;
        indexPtr = temp;
    }
    *ptrToHead = previous;
}

// Check if the linked list is empty
bool isEmpty(Book *head)
{
    return head == nullptr;
}

// Print information of given book
void printBk(Book *book)
{
    cout << "\n****************************************************\n";

    cout << "Name:         " << book->Name << "\n";
    cout << "Author:       " << book->Author << "\n";
    cout << "Genre:        " << book->Genre << "\n";
    if (book->Cost)
        cout << "Cost:         " << book->Cost << "\n";
    if (book->Pages)
        cout << "Pages:        " << book->Pages << "\n";
    if ((book->Quote).length())
        cout << "Famous Quote: " << book->Quote << "\n";
    if (!book->row)
        cout << "Book is located beside row 10 as starage capacity is full.\nWarning: Please increase storage capacity.\n";
    else
        cout << "Book is located at row " << book->row << " shelf " << book->shelf << ".\n";
    cout << "****************************************************\n";
}

// List all the books in library
void printAll(Book *head)
{
    if (isEmpty(head))
        cout << "No books found.";
    while (head != nullptr)
    {
        printBk(head);
        head = head->Next;
    }
    cout << "----> End Of List <----\n\n\n";
    cin.sync();
    string temp;
    cout << "\nPress Enter to Continue...";
    getline(cin, temp);
    system("CLS");
}

// Search the library by name of a book
void searchByName(Book *head, string name)
{
    bool found = 0;
    while (head != nullptr)
    {
        if (head->Name == name)
        {
            printBk(head);
            found = 1;
        }
        head = head->Next;
    }
    if (!found)
        cout << "\nNo results found!!!\n";
    cin.sync();
    string temp;
    cout << "\nPress Enter to Continue...";
    getline(cin, temp);
    system("CLS");
}

// Search the library for books of specific author
void searchByAuthor(Book *head, string author)
{
    bool found = 0;
    while (head != nullptr)
    {
        if (head->Author == author)
        {
            printBk(head);
            found = 1;
        }
        head = head->Next;
    }
    if (!found)
        cout << "\nNo results found!!!\n";
    cin.sync();
    string temp;
    cout << "\nPress Enter to Continue...";
    getline(cin, temp);
    system("CLS");
}

// Search for books within specified price range
void searchByCost(Book *head, float costHigh, float costLow)
{
    bool found = 0;
    while (head != nullptr)
    {
        if (head->Cost <= costHigh && head->Cost >= costLow)
        {
            printBk(head);
            found = 1;
        }
        head = head->Next;
    }
    if (!found)
        cout << "\nNo results found!!!\n";
    cin.sync();
    string temp;
    cout << "\nPress Enter to Continue...";
    getline(cin, temp);
    system("CLS");
}

// Search for books within specified page range
void searchByPages(Book *head, int pagesHigh, int pagesLow)
{
    bool found = 0;
    while (head != nullptr)
    {
        if (head->Pages <= pagesHigh && head->Pages >= pagesLow)
        {
            printBk(head);
            found = 1;
        }
        head = head->Next;
    }
    if (!found)
        cout << "\nNo results found!!!\n";
    cin.sync();
    string temp;
    cout << "\nPress Enter to Continue...";
    getline(cin, temp);
    system("CLS");
}

// Search for books of a specific genre
void searchByGenre(Book *head, string genre)
{
    bool found = 0;
    while (head != nullptr)
    {
        if (head->Genre == genre)
        {
            printBk(head);
            found = 1;
        }
        head = head->Next;
    }
    if (!found)
        cout << "\nNo results found!!!\n";
    cin.sync();
    string temp;
    cout << "\nPress Enter to Continue...";
    getline(cin, temp);
    system("CLS");
}

// Search a specific row of books
void searchByRow(Book *head, int rowNo)
{
    bool found = 0;
    while (head != nullptr)
    {
        if (head->row == rowNo)
        {
            printBk(head);
            found = 1;
        }
        head = head->Next;
    }
    if (!found)
        cout << "\nNo results found!!!\n";
    cin.sync();
    string temp;
    cout << "\nPress Enter to Continue...";
    getline(cin, temp);
    system("CLS");
}

// Explore library by different categories
void explore(Book *head)
{
    int choice;
    cout << "\n***Exploring The Library***\n";
    cout << "\n1. By Author\n2. By Genre\n3. By Cost\n4. By No. of Pages\n5. By Row\n\n";
    cout << "Enter Choice Here >>> ";
    cin >> choice;
    system("CLS");
    if (choice == 1)
    {
        int i = 0;
        cout << "\n***Explore by Author***\n\n";
        while (Authors[i].length())
        {
            cout << i + 1 << ". " << Authors[i] << "\n";
            i++;
        }
        cout << i + 1 << ". Unknown\n\n";
        cout << "Enter choice number here >>> ";
        int choice2;
        cin >> choice2;
        cout << "\n***Books by " << Authors[choice2 - 1] << "***\n";
        system("CLS");
        if (Authors[choice2 - 1].length())
            searchByAuthor(head, Authors[choice2 - 1]);
        else
            searchByAuthor(head, "Unknown");
    }
    else if (choice == 2)
    {
        int i = 0;
        cout << "\n***Explore by Genre***\n\n";
        while (Genres[i].length())
        {
            cout << i + 1 << ". " << Genres[i] << "\n";
            i++;
        }
        cout << i + 1 << ". Unknown\n\n";
        cout << "Enter choice number here >>> ";
        int choice2;
        cin >> choice2;
        system("CLS");
        cout << "\n***Books in Genre " << Genres[choice2 - 1] << "***\n";
        if (Genres[choice2 - 1].length())
            searchByGenre(head, Genres[choice2 - 1]);
        else
            searchByGenre(head, "Unknown");
    }
    else if (choice == 3)
    {
        cout << "\n***Explore by No. of Pages***\n\n";
        cout << "1. 0-100\n2.101-300\n3.301-500\n4.Above 500\n";
        cout << "Enter choice number here >>> ";
        int choice2;
        cin >> choice2;
        system("CLS");
        cout << "\n***Books by No. of Pages"
             << "***\n";
        if (choice2 == 1)
            searchByCost(head, 100, 0);
        else if (choice2 == 2)
            searchByCost(head, 300, 101);
        else if (choice2 == 3)
            searchByCost(head, 500, 301);
        else if (choice2 == 4)
            searchByCost(head, 99999, 501);
        else
            searchByCost(head, 99999, 0);
    }
    else if (choice == 4)
    {
        cout << "\n***Explore by Cost of Books***\n\n";
        cout << "1. 0-100\n2.101-300\n3.301-500\n4.Above 500\n";
        cout << "Enter choice number here >>> ";
        int choice2;
        cin >> choice2;
        system("CLS");
        cout << "\n***Books by Cost of Books"
             << "***\n";
        if (choice2 == 1)
            searchByPages(head, 100, 0);
        else if (choice2 == 2)
            searchByPages(head, 300, 101);
        else if (choice2 == 3)
            searchByPages(head, 500, 301);
        else if (choice2 == 4)
            searchByPages(head, 99999, 501);
        else
            searchByPages(head, 99999, 0);
    }
    else if (choice == 5)
    {
        cout << "\n***Explore by Rows*** "
             << "\n\n";
        cout << "Enter row number from 1-10 (0 for extras row) >>> ";
        int choice2;
        cin >> choice2;
        system("CLS");
        cout << "\n***Books in Row " << choice2 << "***\n";
        searchByRow(head, choice2);
    }
}

// Search Library for books
void searchBooks(Book *head)
{
    cout << "\n***Search for Books***\n";
    int choice;
    cout << "\n1. By Name\n2. By Author\n3. By Genre\n\n";
    cout << "Enter Choice Here >>> ";
    cin >> choice;
    system("CLS");
    if (choice == 1)
    {
        cout << "***Search By Name***\n\n";
        cout << "Enter Book Name Here >>> ";
        string name;
        cin.sync();
        getline(cin, name);
        system("CLS");
        cout << "***Search Results for \"" << name << "\":\n";
        searchByName(head, name);
    }
    else if (choice == 2)
    {
        cout << "***Search By Author***\n\n";
        cout << "Enter Author Name Here >>> ";
        string name;
        cin.sync();
        getline(cin, name);
        system("CLS");
        cout << "***Search Results for Author \"" << name << "\":\n";
        searchByAuthor(head, name);
    }
    else if (choice == 3)
    {
        cout << "***Search By Genre***\n\n";
        cout << "Enter Genre Here >>> ";
        string name;
        cin.sync();
        getline(cin, name);
        system("CLS");
        cout << "***Search Results for Genre \"" << name << "\":\n";
        searchByGenre(head, name);
    }
}

// Welcome message
void greetings()
{
    cout << "\n";
    cout << "****************************************\n";
    cout << "*                                      *\n";
    cout << "*                                      *\n";
    cout << "*     ----------------------------     *\n";
    cout << "*      WELCOME TO STUDENT LIBRARY      *\n";
    cout << "*     ----------------------------     *\n";
    cout << "*                                      *\n";
    cout << "*                                      *\n";
    cout << "*                                      *\n";
    cout << "*                                      *\n";
    cout << "*       Pune, Maharashtra, India       *\n";
    cout << "*     Email: studentlib@gmail.com      *\n";
    cout << "*   Contact: 8800991010, 8800992020    *\n";
    cout << "*                                      *\n";
    cout << "****************************************\n";
    cin.sync();
    string temp;
    cout << "\nPress Enter to Continue...";
    getline(cin, temp);
    system("CLS");
}

int main()
{
    Book *head = nullptr;
    greetings();

    Book *newBook;
    newBook = new Book("Name1", "Author1", "Genre", 101, 201, "Quote1");
    insert(newBook, &head);
    newBook = new Book("Name2", "Author2", "Genre", 102, 202, "Quote2");
    insert(newBook, &head);
    newBook = new Book("Name3", "Author3", "Genre", 103, 203, "Quote3");
    insert(newBook, &head);
    newBook = new Book("Name4", "Author4", "Genre5", 104, 204, "Quote4");
    insert(newBook, &head);
    newBook = new Book("Name5", "Author5", "Genre5", 105, 205, "Quote5");
    insert(newBook, &head);
    newBook = new Book("Name6", "Author6", "Genre", 106, 206, "Quote6");
    insert(newBook, &head);
    newBook = new Book("Name7", "Author7", "Genre", 107, 207, "Quote7");
    insert(newBook, &head);
    newBook = new Book("Name8", "Author8", "Genre", 108, 208, "Quote8");
    insert(newBook, &head);
    newBook = new Book("Name9", "Author9", "Genre", 109, 209, "Quote9");
    insert(newBook, &head);
    newBook = new Book("Name10", "Author10", "Genre", 110, 210, "Quote10");
    insert(newBook, &head);

    while (1)
    {
        cout << "Please select any option below:\n\n";
        cout << "1. Search For a Book\n2. Explore The Library\n3. List All Books\n4. Add a New Book\n5. Exit\n\n";
        cout << "Enter Choice Here >>> ";
        int choice;
        cin >> choice;
        system("CLS");
        if (choice == 1)
        {
            searchBooks(head);
        }
        else if (choice == 2)
        {
            explore(head);
        }
        else if (choice == 3)
        {
            cout << "***List of All Available Books***\n";
            printAll(head);
        }
        else if (choice == 4)
        {
            cout << "***Add a New Book***\n";
            addBook(&head);
        }
        else if (choice == 5)
        {
            break;
        }
        else
        {
            cout << "\nPlease Enter Correct Choice Number (1-4).\n";
            cout << "Press enter to continue...";
            cin.sync();
            string temp;
            getline(cin, temp);
            system("CLS");
        }
    }
    return 0;
}


