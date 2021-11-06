/*
		Account management system can sort the account according to alphabetical order of username
		
		referrence:	1. delay() fucntion:
							https://www.geeksforgeeks.org/time-delay-c/
					2. using input.peek() to detect the ending of file:
							http://www.cplusplus.com/reference/istream/istream/peek/
					3. convert string type to numbers:
							http://www.cplusplus.com/reference/sstream/istringstream/istringstream/
					4. Red-Black Tree is refer to the pseudocode and algorithm in the book:
							Cormen T.H., Leiserson, C.E., Rivest, R.L. & Stein, C.
							(2009), Introduction to Algorithm (3rd Edition), London: MIT Press.
							Page 308 to Page 329.
					5. map container refers to the book:
							Book Name:	C++ Primer Eifth Edition
							Author:	Stanley B. Lippman ,	Josee Lajoie ,	Barbara E. Moo
							Publisher:	Pearson Education (US)
							page:	420 ~ 443
					6. get the data today:
							https://www.geeksforgeeks.org/time-h-localtime-function-in-c-with-examples/
							https://www.geeksforgeeks.org/time-h-header-file-in-c-with-examples/
							http://www.cplusplus.com/reference/ctime/tm/?kw=tm
					7.	Hash table refers to:
						The book: Cormen T.H., Leiserson, C.E., Rivest, R.L. & Stein, C. (2009), 
						Introduction to Algorithm (3rd Edition), London: MIT Press.
						Page 270 and Page 271.

						And the link:
						https://github.com/jamesroutley/write-a-hash-table
					8. The format of output was inspired by this video£º 
						https://www.youtube.com/watch?v=Hk5xWzlHUoo&t=949s

*/

#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include <tr1/functional>
#include <sstream> 
#include <iomanip>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;


/* Global Declaration*/
enum RBTColor {RED, BLACK};		// RED color is 0; BLACK color is 1; For Red-Black Tree. 	


struct Book		// store book's information
{
	string ID;
	string name;
	string author;
	string category;
	string publisher;
	double price;
	int quantity; // in store
};

struct LL_Node		// node of linked list
{
	struct Book book_data;
	struct LL_Node *next;
};

struct HT_Node		// node of Hash Table using chaining. It is doubly linked list
{
	struct Book book_data;
	struct HT_Node *next;
	struct HT_Node *prev;	
}; 

struct Database			// Books Database
{
	struct HT_Node **ID_hash_table;		// Hash Table
	struct LL_Node **category;		// store the book according to category
	vector<LL_Node*> author;		// store the boook according to author
	struct LL_Node *name;		// store the book according to book name
};

struct admin_staff		// store account username and password
{
	string username;
	string password;
};

struct Node		// The node of Red-Black tree
{
	struct Node *left;
	struct Node *right;
	struct Node *parent;
	struct admin_staff account;
	string key;		// the key used to sort
	RBTColor color;		// 0 is red, 1 is black;
};

struct Book_Sales		// store details of sales report
{
	string ID;
	int month_sales[12];		// the number of specific books sold in one month
	int total_sales; 		// Total number of specific books sold in one year
};

struct wish_list
{
	struct Book book;
	int quantity;		// How many books customer wants.
};




/* Global Declaration*/
struct Database book_database;		// Database, whiich contain all the books' information.
struct Node *T_NIL;		// Declare a sentinel, using repressent NULL; Used in Red-Black tree
map<string,Book_Sales> sales_database;		// sales_database contain details about sales information


// %%%%%%%%%%%%%%%% Red-Black Tree %%%%%%%%%%%%%%%%%%%% 
// Insert node
void New_Node(struct Node* newNode, string key);
void leftRotation(struct Node *&root, struct Node *&A);
void rightRotation(struct Node *&root, struct Node *&A);
struct Node *BSTinsertNode(struct Node *tree, struct Node *newNode);
void fixUp(struct Node *&tree, struct Node *&current);
void RB_insert(Node* &root, Node* newNode);
struct Node *insert(Node *tree, string username, string password);


// Delete node 
struct Node *findSmallest(struct Node *tree);
void RB_transplant(struct Node *&tree, struct Node *&node, struct Node *&replace);
void RB_delete(struct Node *&tree, struct Node *node);
struct Node* search(struct Node *tree, string key);
void deleteNode(struct Node *&tree, string key); 

// %%%%%%%%%%%%%%%%% End Red-Black Tree %%%%%%%%%%%%%%%%%%


// Menu 
void search_book();
void delay(int milliseconds);
void main_menu();
void administrator_menu();
void guest_menu();
void staff_menu();
void delete_book();
void update_book();
void sales_report();
void account_menu();
void Add_new_book_menu();


// Account Management System 
struct Node *admin_RB_tree();
void login_admin(struct Node *&adminaccounts);
struct Node *new_admin_list(struct Node *&admin_tree ,string username, string password);
void sign_up_admin(struct Node *&admin_RB_tree);
void delete_admin_account(struct Node *&admin_accounts);

struct Node *staff_RB_tree();
void login_staff(struct Node *&staff_accounts);
struct Node *new_staff_list(struct Node *&admin_accounts ,string username, string password);
void sign_up_staff(struct Node *&staff_accounts);
void delete_staff_account(struct Node *&staff_accounts);


// Operation of Database
struct Database new_database(struct Book newBook);
void database_add_book(struct Database &book_database, struct Book newBook);
void initialize_database(struct Database &book_database);


// Hash Table
struct HT_Node *new_HT_Node(struct Book book_data);
int hashing_function(string key);
void doubly_LL_insert(struct HT_Node *&head, struct HT_Node *newNode);
struct HT_Node *doubly_LL_search(struct HT_Node *head, string key);
void doubly_LL_delete(struct HT_Node *&head, struct HT_Node *deleted_node);
void hash_insert(struct Database &book_database, struct Book newBook);
struct HT_Node *hash_search(struct Database book_database, string key);
void hash_delete(struct Database &book_database, string key);


// operations by ID using hash table
void search_by_ID();
void printOut_book(struct Book book_data);
void deleteBook_byID(struct Database &book_database);
void updateBook_byID(struct Database &book_database);
void update_whole_details(struct Database &book_database);
void update_few_details(struct Database &book_database);


//operations by category, author and name using Singly Linked List
void singly_LL_insert(struct LL_Node *&head, struct LL_Node *newNode);
struct LL_Node *New_LL_Node(struct Book newBook);
void category_insert(struct Database &book_database, struct Book newBook);
void author_insert(struct Database &book_database, struct Book newBook);
void search_by_category(struct Database book_database);
void search_by_author(struct Database book_database);
void show_all_book(struct Database book_database);
void search_by_name(struct Database book_database);
void updateByName_whole_details(struct Database &book_database);
void updateByName_few_details(struct Database &book_database);
void deleteBook_byName(struct Database &book_database);
void updateBook_byName(struct Database &book_database);


// Merge sort according to
void divideList(struct LL_Node *&head1, struct LL_Node *&head2);
struct LL_Node* mergeList(struct LL_Node *head1, struct LL_Node *head2);
void recMergeSort(struct LL_Node *&head);


// Binary Search
struct LL_Node* find_middle(LL_Node* head, LL_Node* rear);
struct LL_Node* binarySearch(LL_Node *head, string key);


// check out
void check_out_menu();
void add_cart_byID(vector<wish_list> &cart, struct Database book_database);
void delete_cart_byID(vector<wish_list> &cart);
void show_cart(vector<wish_list> &cart);
void check_out(vector<wish_list> &cart, struct Database &book_database);


// Sales Report
void initialize_Book_Sales(map<string, Book_Sales> &sales_database);
void update_sales_database(map<string, Book_Sales> sales_database);
void display_sales_report(map<string, Book_Sales> sales_database);





int main()
{
	initialize_database(book_database);
	initialize_Book_Sales(sales_database);

	
	// Initialize T_NIL 
	T_NIL = new Node;		// T_NIL is sentinel, which is alreday declared;
	T_NIL->color = BLACK;		// All the leaf nodes(NIL) are BLACK;
	
	main_menu();

		
	return 0;
} 




// Do time delay
void delay(int milliseconds) 
{
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milliseconds); 
}



/*	%%%%%%%%%%%%%%%% Books Database %%%%%%%%%%%%%%%%%%%%
	____________________________________________________
*/	


// Initialize database to store books
struct Database new_database()
{
	// initialize database
	Database temp;
	temp.ID_hash_table = new HT_Node*[401];		// hash table using chaining to solve collision. And the number of slots is 401. which is prime integer and is not closed to 2^n. 
	temp.category = new LL_Node*[10];		// There are 10 kinds of categories. We set:
											//	index 0 is "History"; index 1 is "Adventure"; index 2 is "Classic";
											//	index 3 is "Detective"; index 4 is "Fairy Tale; index 5 is "Horror";
											//	index 6 is "Romance"; index 7 is "Textbook"; index 8 is "Poetry";
											//	index 9 is "Other"
	temp.name = NULL;
	
	// initialize Hash table
	for(int i = 0; i < 401; i++)
	{
		temp.ID_hash_table[i] = NULL;
	}
	
	for(int i = 0; i < 10; i++)
	{
		temp.category[i] = NULL;
	}
	
	return temp;
}

// Insert a new book into the books database 
void database_add_book(struct Database &book_database, struct Book newBook)
{
	
	// insert the book into hash table;
	hash_insert(book_database, newBook);
	
	
	// insert the book into the database sorted by category
	category_insert(book_database, newBook);
	
	// insert the book into the database sorted by author
	author_insert(book_database, newBook);
	
	// insert the book into linked list sorted by name
	singly_LL_insert(book_database.name, New_LL_Node(newBook));
}


// store all information of "book_database.txt" into "struct Database book_database"
void initialize_database(struct Database &book_database)
{
	// initialize the database
	book_database = new_database();
	
	struct Book newBook;
	
	ifstream input("book_database.txt");
	
	// Check the existence of file.
	if(input.fail())
	{
		cout << "\n\n\t\tError! The \"book_database.txt\" does not exist!\n\n\t\t";
		exit(1); 
	}
	if(input.peek() == EOF)
	{
		cout << "\n\n\t\tError! The \"book_database.txt\" does not include any data!\n\n\t\t";
		exit(1); 
	}
	
	// store one book's all information in "newBook"
	while(input.peek() != EOF)
	{
		string space;		// use to eliminate the effect brought by "\n" in the file.
		string price;		// get the price first. Then it will be converted to int type
		string quantity;
		
		getline(input, newBook.ID, ';');
		getline(input, newBook.name, ';');
		getline(input, newBook.author, ';');
		getline(input, newBook.category, ';');
		getline(input, newBook.publisher, ';');
		getline(input, price, ';');
		istringstream istr1(price);		// convert string type to double type;
		istr1 >> newBook.price;
		getline(input, quantity, ';');
		istringstream istr2(quantity);		// convert string type to int type;
		istr2 >> newBook.quantity;		
		getline(input, space);
		
		database_add_book(book_database, newBook);
	}
	
	input.close();		// End opening file
}


// %%%%%%%%%%%%% End Books Database %%%%%%%%%%%%%%%%% 





/* %%%%%%%%%%%%%%%%% Menu %%%%%%%%%%%%%%%%%%%%%%%%%
		
			* show various menus *
*/

// Main Menu
void main_menu()
{
	bool error = 0;		// check invalid input.
	int choice;
	
	// Show the main menu and detect failed cin command.
	do
	{
		error = 0;
		char title[] = "Main Menu";
		
		system("cls");
		cin.clear();
		
		// Display the menu 
		cout << "\n\n\n\n\t\t";
		for(int i = 0; i < 20; i++)
		{
			delay(30);
			printf("*");
		}
		cout << " ";
		for(int i = 0; i < 9; i++)
		{
			delay(30);
			printf("%c", title[i]);
		}
		cout << " ";
		for(int i = 0; i < 20; i++)
		{
			delay(30);
			printf("*");
		}
		delay(500);
		cout << "\n\n\t\t\t1. Administrator Login";
		delay(500);
		cout << "\n\n\t\t\t2. Staff Login";
		delay(500);
		cout << "\n\n\t\t\t3. Guest Login";
		delay(500);
		cout << "\n\n\t\t\t0. Exit\n\n\t\t";
		delay(500);
		for(int i = 0; i < 51; i++)
		{
			delay(10);
			printf("-");
		}
		cout << "\n\n\n\n\t\tPlease enter your choice: ";
		cin >> choice;
		
		// Detect failed cin command and invalid input.
		if(cin.fail() || choice > 3 || choice < 0)		// cin.fail() is used to check whether cin command failed
		{
			cout << "\n\n\t\tPlease enter valid choice." << endl;
			cin.clear();
			cin.ignore(80,'\n');
			error = 1;
		}
		cout << "\t\t";
		system("pause");
	}while(error == 1);		// end do-while
	
	switch(choice)
	{
		case 0: exit(0);
				break;
		case 1: {
					struct Node *admin_accounts = T_NIL;
					admin_accounts = admin_RB_tree();
					login_admin(admin_accounts);
					administrator_menu();			
					break;
				}
		case 2: {
					struct Node *staff_accounts = T_NIL;
					staff_accounts = staff_RB_tree();
					login_staff(staff_accounts);
					staff_menu();
					break;
				} 
				
		case 3: guest_menu();
				break;
	}
}

// Admin Menu
void administrator_menu()
{
	bool error = 0;		// check invalid input.
	int choice;
	
	// Show the Admin menu and detect failed cin command.
	do
	{
		error = 0;
		char title[] = "Administrator Menu";
		
		system("cls");
		cin.clear();
		
		// Display the menu 
		cout << "\n\n\n\t\t";
		for(int i = 0; i < 20; i++)
		{
			delay(30);
			printf("#");
		}
		cout << " ";
		for(int i = 0; i < 18; i++)
		{
			delay(30);
			printf("%c", title[i]);
		}
		cout << " ";
		for(int i = 0; i < 20; i++)
		{
			delay(30);
			printf("#");
		}
		delay(300);
		cout << "\n\n\t\t\t1. Add New Books";
		delay(300);
		cout << "\n\n\t\t\t2. Display All Books";
		delay(300);
		cout << "\n\n\t\t\t3. Search Books";
		delay(300);
		cout << "\n\n\t\t\t4. Delete Books";
		delay(300);
		cout << "\n\n\t\t\t5. Update Books";
		delay(300);
		cout << "\n\n\t\t\t6. View Sales Report";
		delay(300);
		cout << "\n\n\t\t\t7. Manage Administrator and Staff Account";
		delay(300);
		cout << "\n\n\t\t\t0. Return to Main Menu\n\n\t\t";
		delay(300);
		for(int i = 0; i < 60; i++)
		{
			delay(10);
			printf("-");
		}
		cout << "\n\n\n\t\tPlease enter your choice: ";
		cin >> choice;
		
		// Detect failed cin command and invalid input.
		if(cin.fail() || choice > 7 || choice < 0)		// cin.fail() is used to check whether cin command failed
		{
			cout << "\n\n\t\tPlease enter valid choice." << endl;
			cin.clear();
			cin.ignore(80,'\n');
			error = 1;
		}
		cout << "\t\t";
		system("pause");
	}while(error == 1);		// end do-while
	
	switch(choice)
	{
		case 0: main_menu();
				break;
		case 1: Add_new_book_menu();
				break;
		case 2: show_all_book(book_database);
				break;
		case 3: search_book();
				break;
		case 4: delete_book();
				break;
		case 5: update_book(); 
				break;
		case 6: sales_report();
				break;
		case 7: account_menu();
				break;
	}
}

// Staff Menu
void staff_menu()
{
	bool error = 0;		// check invalid input.
	int choice;
	
	// Show the staff menu and detect failed cin command.
	do
	{
		error = 0;
		char title[] = "Staff Menu";
		
		system("cls");
		cin.clear();
		
		// Display the menu 
		cout << "\n\n\n\n\t\t";
		for(int i = 0; i < 20; i++)
		{
			delay(30);
			printf("*");
		}
		cout << " ";
		for(int i = 0; i < 10; i++)
		{
			delay(30);
			printf("%c", title[i]);
		}
		cout << " ";
		for(int i = 0; i < 20; i++)
		{
			delay(30);
			printf("*");
		}
		delay(300);
		cout << "\n\n\t\t\t1. Display All Books";
		delay(300);
		cout << "\n\n\t\t\t2. Search Books";
		delay(300);
		cout << "\n\n\t\t\t3. Check Out";
		delay(300);
		cout << "\n\n\t\t\t0. Return to Main Menu\n\n\t\t";
		delay(300);
		for(int i = 0; i < 52; i++)
		{
			delay(10);
			printf("-");
		}
		cout << "\n\n\n\n\t\tPlease enter your choice: ";
		cin >> choice;
		
		// Detect failed cin command and invalid input.
		if(cin.fail() || choice > 3 || choice < 0)		// cin.fail() is used to check whether cin command failed
		{
			cout << "\n\n\t\tPlease enter valid choice." << endl;
			cin.clear();
			cin.ignore(80,'\n');
			error = 1;
		}
		cout << "\t\t";
		system("pause");
	}while(error == 1);		// end do-while
	
	switch(choice)
	{
		case 0: main_menu();
				break;
		case 1: show_all_book(book_database);
				break;
		case 2: search_book();
				break;
		case 3: check_out_menu();
				break;
	}
}

// Guest Menu
void guest_menu()
{
	bool error = 0;		// check invalid input.
	int choice;
	
	// Show the guest menu and detect failed cin command.
	do
	{
		error = 0;
		char title[] = "Guest Menu";
		
		system("cls");
		cin.clear();
		
		// Display the menu 
		cout << "\n\n\n\n\t\t";
		for(int i = 0; i < 20; i++)
		{
			delay(30);
			printf("*");
		}
		cout << " ";
		for(int i = 0; i < 10; i++)
		{
			delay(30);
			printf("%c", title[i]);
		}
		cout << " ";
		for(int i = 0; i < 20; i++)
		{
			delay(30);
			printf("*");
		}
		delay(300);
		cout << "\n\n\t\t\t1. Display All Books";
		delay(300);
		cout << "\n\n\t\t\t2. Search Books";
		delay(300);
		cout << "\n\n\t\t\t0. Return to Main Menu\n\n\t\t";
		delay(300);
		
		for(int i = 0; i < 52; i++)
		{
			delay(10);
			printf("-");
		}
		cout << "\n\n\n\n\t\tPlease enter your choice: ";
		cin >> choice;
		
		// Detect failed cin command and invalid input.
		if(cin.fail() || choice > 2 || choice < 0)		// cin.fail() is used to check whether cin command failed
		{
			cout << "\n\n\t\tPlease enter valid choice." << endl;
			cin.clear();
			cin.ignore(80,'\n');
			error = 1;
		}
		cout << "\t\t";
		system("pause");
	}while(error == 1);		// end do-while
	
	switch(choice)
	{
		case 0: main_menu();
				break;
		case 1: show_all_book(book_database);
				break;
		case 2: search_book();
				break;
	}
}

// Menu for choosing Searching type
void search_book()
{
	bool error = 0;		// check invalid input.
	int choice;
	
	// Show the searching menu and detect failed cin command.
	do
	{
		error = 0;
		char title[] = "Searching Menu";
		
		system("cls");
		cin.clear();
		
		// Display the menu 
		cout << "\n\n\n\n\t\t";
		for(int i = 0; i < 20; i++)
		{
			delay(30);
			printf("*");
		}
		cout << " ";
		for(int i = 0; i < 14; i++)
		{
			delay(30);
			printf("%c", title[i]);
		}
		cout << " ";
		for(int i = 0; i < 20; i++)
		{
			delay(30);
			printf("*");
		}
		delay(300);
		cout << "\n\n\t\t\t1. Search Books by ID";
		delay(300);
		cout << "\n\n\t\t\t2. Search Books by Category";
		delay(300);
		cout << "\n\n\t\t\t3. Search Books by Book Name";
		delay(300);
		cout << "\n\n\t\t\t4. Search Books by Author";
		delay(300);
		cout << "\n\n\t\t\t0. Return to Main Menu\n\n\t\t";
		delay(300);
		
		for(int i = 0; i < 54; i++)
		{
			delay(10);
			printf("-");
		}
		cout << "\n\n\n\n\t\tPlease enter your choice: ";
		cin >> choice;
		
		// Detect failed cin command and invalid input.
		if(cin.fail() || choice > 4 || choice < 0)		// cin.fail() is used to check whether cin command failed
		{
			cout << "\n\n\t\tPlease enter valid choice." << endl;
			cin.clear();
			cin.ignore(80,'\n');
			error = 1;
		}
		cout << "\t\t";
		system("pause");
	}while(error == 1);		// end do-while
	
	switch(choice)
	{
		case 0: main_menu();
				break;
		case 1: search_by_ID();
				search_book();
				break;
		case 2: search_by_category(book_database);
				cout << "\n\n\t\tPlease enter any key to return to Searching Menu.\n\n\t\t";
				search_book();
				break;
		case 3: search_by_name(book_database);
				search_book();
				break;
		case 4: search_by_author(book_database);
				cout << "\n\n\t\tPlease enter any key to return to Searching Menu.\n\n\t\t";
				search_book();
				break;
	}
}

// Menu for deleting Books
void delete_book()
{
	bool error = 0;		// check invalid input.
	int choice;
	
	// Show the Deleting menu and detect failed cin command.
	do
	{
		error = 0;
		char title[] = "Delete Books";
		
		system("cls");
		cin.clear();
		
		// Display the menu 
		cout << "\n\n\n\n\t\t";
		for(int i = 0; i < 20; i++)
		{
			delay(30);
			printf("*");
		}
		cout << " ";
		for(int i = 0; i < 12; i++)
		{
			delay(30);
			printf("%c", title[i]);
		}
		cout << " ";
		for(int i = 0; i < 20; i++)
		{
			delay(30);
			printf("*");
		}
		delay(300);
		cout << "\n\n\t\t\t1. Search and Delete by ID";
		delay(300);
		cout << "\n\n\t\t\t2. Search and Delete by Category";
		delay(300);
		cout << "\n\n\t\t\t3. Search and Delete by Book Name";
		delay(300);
		cout << "\n\n\t\t\t4. Search and Delete by Author";
		delay(300);
		cout << "\n\n\t\t\t0. Return to Administrator Menu\n\n\t\t";
		delay(300);
		
		for(int i = 0; i < 54; i++)
		{
			delay(10);
			printf("-");
		}
		cout << "\n\n\n\t\tPlease enter your choice to find"
				" \n\t\tthe book you will delete: ";
		cin >> choice;
		
		// Detect failed cin command and invalid input.
		if(cin.fail() || choice > 4 || choice < 0)		// cin.fail() is used to check whether cin command failed
		{
			cout << "\n\n\t\tPlease enter valid choice." << endl;
			cin.clear();
			cin.ignore(80,'\n');
			error = 1;
		}
		cout << "\t\t";
		system("pause");
	}while(error == 1);		// end do-while
	
	switch(choice)
	{
		case 0: administrator_menu();
				break;
		case 1: deleteBook_byID(book_database);
				break;
		case 2: search_by_category(book_database);
				cout << "\n\n\t\tPlease, remember the booke ID to be deleted.\n\n\t\t";
				system("pause");
				deleteBook_byID(book_database);
				break;
		case 3: deleteBook_byName(book_database);
				break;
		case 4: search_by_author(book_database);
				cout << "\n\n\t\tPlease, remember the booke ID to be deleted.\n\n\t\t";
				system("pause");
				deleteBook_byID(book_database);
				break;
	}
}

// Update the books
void update_book()
{
	bool error = 0;		// check invalid input.
	int choice;
	
	// Show the Update menu and detect failed cin command.
	do
	{
		error = 0;
		char title[] = "Update Books";
		
		system("cls");
		cin.clear();
		
		// Display the menu 
		cout << "\n\n\n\n\t\t";
		for(int i = 0; i < 20; i++)
		{
			delay(30);
			printf("*");
		}
		cout << " ";
		for(int i = 0; i < 12; i++)
		{
			delay(30);
			printf("%c", title[i]);
		}
		cout << " ";
		for(int i = 0; i < 20; i++)
		{
			delay(30);
			printf("*");
		}
		delay(300);
		cout << "\n\n\t\t\t1. Search and Update by ID";
		delay(300);
		cout << "\n\n\t\t\t2. Search and Update by Book Name";
		delay(300);
		cout << "\n\n\t\t\t0. Return to Administrator Menu\n\n\t\t";
		delay(300);
		
		for(int i = 0; i < 54; i++)
		{
			delay(10);
			printf("-");
		}
		cout << "\n\n\n\t\tPlease enter your choice to find"
				" \n\t\tthe book you will update: ";
		cin >> choice;
		
		// Detect failed cin command and invalid input.
		if(cin.fail() || choice > 2 || choice < 0)		// cin.fail() is used to check whether cin command failed
		{
			cout << "\n\n\t\tPlease enter valid choice." << endl;
			cin.clear();
			cin.ignore(80,'\n');
			error = 1;
		}
		cout << "\t\t";
		system("pause");
	}while(error == 1);		// end do-while
	
	switch(choice)
	{
		case 0: administrator_menu();
				break;
		case 1: updateBook_byID(book_database);
				break;
		case 2: updateBook_byName(book_database);
				break;
	}
}

// menu for sales report
void sales_report()
{
	bool error = 0;		// check invalid input.
	int choice;
	
	// Show the menu for sales report and detect failed cin command.
	do
	{
		error = 0;
		char title[] = "Sales Report";
		
		system("cls");
		cin.clear();
		
		// Display the menu 
		cout << "\n\n\n\n\t\t";
		for(int i = 0; i < 20; i++)
		{
			delay(30);
			printf("*");
		}
		cout << " ";
		for(int i = 0; i < 12; i++)
		{
			delay(30);
			printf("%c", title[i]);
		}
		cout << " ";
		for(int i = 0; i < 20; i++)
		{
			delay(30);
			printf("*");
		}
		delay(300);
		cout << "\n\n\t\t\t1. Annual Sales Report";
		delay(300);
		cout << "\n\n\t\t\t0. Return to Administrator Menu\n\n\t\t";
		delay(300);
		
		for(int i = 0; i < 54; i++)
		{
			delay(10);
			printf("-");
		}
		cout << "\n\n\n\t\tPlease enter your choice: ";
		cin >> choice;
		
		// Detect failed cin command and invalid input.
		if(cin.fail() || choice > 2 || choice < 0)		// cin.fail() is used to check whether cin command failed
		{
			cout << "\n\n\t\tPlease enter valid choice." << endl;
			cin.clear();
			cin.ignore(80,'\n');
			error = 1;
		}
		cout << "\t\t";
		system("pause");
	}while(error == 1);		// end do-while
	
	switch(choice)
	{
		case 0: administrator_menu();
				break;
		case 1: display_sales_report(sales_database);
				cout << "\n\n\t\tPlease, enter any key to return to administrator.\n\n\t\t";
				system("pause");
				administrator_menu();
				break;
	}
}

// Account management Menu
void account_menu()
{
	bool error = 0;		// check invalid input.
	int choice;
	
	struct Node *admin_accounts = admin_RB_tree();		// Store all the data of account in a RB_tree.
	struct Node *staff_accounts = staff_RB_tree();		// Store all the data of account in a RB_tree.
	
	// Show the Account Management Menu and detect failed cin command.
	do
	{
		error = 0;
		char title[] = "Account Management Menu";
		
		system("cls");
		cin.clear();
		
		// Display the menu 
		cout << "\n\n\n\n\t\t";
		for(int i = 0; i < 20; i++)
		{
			delay(30);
			printf("*");
		}
		cout << " ";
		for(int i = 0; i < 23; i++)
		{
			delay(30);
			printf("%c", title[i]);
		}
		cout << " ";
		for(int i = 0; i < 20; i++)
		{
			delay(30);
			printf("*");
		}
		delay(300);
		cout << "\n\n\t\t\t1. Sign Up a New Staff Account";
		delay(300);
		cout << "\n\n\t\t\t2. Sign Up a New Administrator Account";
		delay(300);
		cout << "\n\n\t\t\t3. Delete a Staff Account";
		delay(300);
		cout << "\n\n\t\t\t4. Delete a Administrator Account";
		delay(300);
		cout << "\n\n\t\t\t0. Return to Administrator Menu\n\n\t\t";
		delay(300);
		for(int i = 0; i < 62; i++)
		{
			delay(10);
			printf("-");
		}
		cout << "\n\n\n\n\t\tPlease enter your choice: ";
		cin >> choice;
		
		// Detect failed cin command and invalid input.
		if(cin.fail() || choice > 4 || choice < 0)		// cin.fail() is used to check whether cin command failed
		{
			cout << "\n\n\t\tPlease enter valid choice." << endl;
			cin.clear();
			cin.ignore(80,'\n');
			error = 1;
		}
		cout << "\t\t";
		system("pause");
	}while(error == 1);		// end do-while
	
	switch(choice)
	{
		case 0: administrator_menu();
				break;
		case 1: sign_up_staff(staff_accounts);
				break;
		case 2: sign_up_admin(admin_accounts);
				break;
		case 3: delete_staff_account(staff_accounts);
				break;
		case 4: delete_admin_account(admin_accounts);
				break;
	}
}


// Add new book in "book_database.txt". Make sure the book ID unique.
void Add_new_book_menu()
{
	system("cls");
	cin.ignore(80,'\n');
	struct Book book_data;
	
	
	cout << "\n\n\t\t%%%%%%%%%%%%%%%%%%%% Book Addition System %%%%%%%%%%%%%%%%%%%%";
	cout << "\n\n\t\tPlease enter the new details"
	     << "\n\t\t1. Book ID: ";
	getline(cin, book_data.ID);
	cout << "\n\t\t2. Booke Name: ";
	getline(cin, book_data.name);
	cout << "\n\t\t3. Author: ";
	getline(cin, book_data.author);
	cout << "\n\t\t4. Category: ";
	getline(cin, book_data.category);
	cout << "\n\t\t5. Publisher: ";
	getline(cin, book_data.publisher);
	cout << "\n\t\t6. Price: ";
	cin >> book_data.price;
	cout << "\n\t\t7. Quantity: ";
	cin >> book_data.quantity;
	
	
	// find the object book
	struct HT_Node *found_book = hash_search(book_database, book_data.ID);
	
	// Make sure the book ID unique.
	if (found_book == NULL)
    {
    	// insert the book into book_database
    	hash_insert(book_database, book_data);
    	
    	ofstream output("book_database.txt");		// Open the file
		// store all the information into "book_database.txt"
		for(int i = 0; i < 401; i++)
		{
			struct HT_Node *current = book_database.ID_hash_table[i]; 
			while( current != NULL)
			{
				output << current->book_data.ID << ";"
					   << current->book_data.name << ";"
					   << current->book_data.author << ";"
					   << current->book_data.category << ";"
					   << current->book_data.publisher << ";"
					   << fixed << setprecision(2) << current->book_data.price << ";"
					   << current->book_data.quantity << ";" << "\n";
				
				current = current->next;
			}
		}
		
		output.close();
		
		initialize_database(book_database);		// read the file again after deleting;
	}
	else
	{
		cout << "\n\n\t\tError!! Book ID has existed!!.\n\t\t";
		cout << "--------------------------------------------------------\n\t\t";
		system("pause");
		administrator_menu();
	}
	
	cout << "\n\n\t\tInsertion has done successfully\n\t\t";
	cout << "--------------------------------------------------------\n\t\t";
	system("pause");
	administrator_menu();
}

// ######################### End Menu ########################




/*  %%%%%%%%%%%%%% Account Management System %%%%%%%%%%%%%%%
		-- login
		-- sign up
		-- delete account
*/

struct Node *admin_RB_tree()
{
	Node *RB_tree = T_NIL;		// T_NIL is a global declaration which has shown in the top of source code.
	
	ifstream input("admin_list.txt");		// Open the file
	
	// Check the existence of file.
	if(input.fail() || input.peek() == EOF)
	{
		ofstream output("admin_list.txt");
		output << "Admin" << ";" << "123456" << ";" << "\n";
		output.close();
	}
	
	// Check whether username matches password
	while(input.peek() != EOF)
	{
		string space;		// use to eliminate the effect brought by "\n" in the file.
		string username;
		string password;
		getline(input, username, ';');
		getline(input, password, ';');
		getline(input, space);
		
		RB_tree = insert(RB_tree, username, password);		// Store the (username and password in this tree)
	}
	
	input.close();		// End opening file
	
	return RB_tree;
}



// Login function for administrators
void login_admin(struct Node *&admin_accounts)
{
	system("cls");
	cin.ignore(80,'\n');		// clear '\n', because the '\n' enter in main_menu() will influence this function.
	
	int exist = 0;		// if esxit == 1, the username matches password.
	string username, password, correct_name, correct_pass;
	
	cout << "\n\n\n\t\t%%%%%%%%%%%%%%%%%%%% Admin Login System %%%%%%%%%%%%%%%%%%%%";
	cout << "\n\n\t\tPlease enter the admin username: ";
	getline(cin, username);
	cout << "\n\t\tPlease enter the password: ";
	getline(cin, password);
	
	// Check whether username matches password
	struct Node *account_searched = search(admin_accounts, username);
	if (account_searched != T_NIL)
    {
    	if(account_searched->account.username == username 
			&& account_searched->account.password == password)
		{
			exist = 1;
		}
    	
	}
	
	if(exist == 1)		// The password matches username.
	{
		cout << "\n\n\t\tHello " << username << ", \n\t\tYou have been entitled to" 
				" access administrative interface\n\t\t";
		for(int i = 0; i < 6; i++)
		{
			delay(500);
			cout << ".";
		}
	}
	else
	{
		cout << "\n\n\t\tLogin error! Please enter correct username and password.\n\t\t"
				"------------------------------------------------------------\n\t\t";
		system("pause");
		main_menu();
	}
}

struct Node *staff_RB_tree()
{
	Node *RB_tree = T_NIL;		// T_NIL is a global declaration which has shown in the top of source code.
	
	ifstream input("staff_list.txt");		// Open the file
	
	// Check the existence of file.
	if(input.fail() || input.peek() == EOF)
	{
		ofstream output("staff_list.txt");
		output << "Admin" << ";" << "123456" << ";" << "\n";
		output.close();
	}
	
	// Check whether username matches password
	while(input.peek() != EOF)
	{
		string space;		// use to eliminate the effect brought by "\n" in the file.
		string username;
		string password;
		getline(input, username, ';');
		getline(input, password, ';');
		getline(input, space);
		
		RB_tree = insert(RB_tree, username, password);		// Store the (username and password in this tree)
	}
	
	input.close();		// End opening file
	
	return RB_tree;
}

// Login function for staff
void login_staff(struct Node *&staff_accounts)
{
	system("cls");
	cin.ignore(80,'\n');		// clear '\n', because the '\n' enter in main_menu() will influence this function.
	
	int exist = 0;		// if esxit == 1, the username and password are in admin_list.txt.
	string username, password, correct_name, correct_pass;
	
	cout << "\n\n\n\t\t%%%%%%%%%%%%%%%%%%%% Staff Login System %%%%%%%%%%%%%%%%%%%%";
	cout << "\n\n\t\tPlease enter the staff username: ";
	getline(cin, username);
	cout << "\n\t\tPlease enter the password: ";
	getline(cin, password);
	
	ifstream input("staff_list.txt");		// Open the file
	
	// Check whether username matches password
	struct Node *account_searched = search(staff_accounts, username);
	
	if (account_searched != T_NIL)
    {
    	if(account_searched->account.username == username 
			&& account_searched->account.password == password)
		{
			exist = 1;
		}
    	
	}
	
	if(exist == 1)		// The password matches username.
	{
		cout << "\n\n\t\tHello " << username << ", \n\t\tYou have been entitled to" 
				" access staff interface\n\t\t";
		for(int i = 0; i < 6; i++)
		{
			delay(500);
			cout << ".";
		}
	}
	else
	{
		cout << "\n\n\t\tLogin error! Please enter correct username and password.\n\t\t"
				"------------------------------------------------------------\n\t\t";
		system("pause");
		main_menu();
	}
}

// Add a new admin account in admin_list.txt according to alphabetical order of username.
struct Node *new_admin_list(struct Node *&admin_accounts ,string username, string password)
{
	admin_accounts = insert(admin_accounts, username, password);		// admin_accounts is a RB_tree
	ofstream output("admin_list.txt");		// Open the file
	
	struct Node *smallest;
	// do the loop until the RB_tree is empty 
	while(admin_accounts != T_NIL)
	{
		smallest= findSmallest(admin_accounts);
		output << smallest->account.username << ";" 
			   << smallest->account.password << ";"
			   << "\n";
		RB_delete(admin_accounts, smallest);
	}
	output.close();
} 

// Sign up an admin account
void sign_up_admin(struct Node *&admin_accounts)
{
	system("cls");
	cin.ignore(80,'\n');		// clear '\n';
	
	string username, password;
	cout << "\n\n\t\t%%%%%%%%%%%%%%%%%%%% Sign Up System %%%%%%%%%%%%%%%%%%%%";
	cout << "\n\n\t\tPlease enter the username: ";
	getline(cin, username);
	cout << "\n\t\tPlease enter the password: ";
	getline(cin, password);
	
	new_admin_list(admin_accounts, username, password);
	
	cout << "\n\n\t\tRegistration is successful\n\t\t";
	cout << "--------------------------------------------------------\n\t\t";
	system("pause");
	account_menu();
}

// Add a new staff account in admin_list.txt according to alphabetical order of username.
struct Node *new_staff_list(struct Node *&admin_accounts ,string username, string password)
{
	admin_accounts = insert(admin_accounts, username, password);		// admin_accounts is a RB_tree
	ofstream output("staff_list.txt");		// Open the file
	
	struct Node *smallest;
	// do the loop until the RB_tree is empty 
	while(admin_accounts != T_NIL)
	{
		smallest= findSmallest(admin_accounts);
		output << smallest->account.username << ";" 
			   << smallest->account.password << ";"
			   << "\n";
	
		RB_delete(admin_accounts, smallest);
	}
	output.close();
}

// Sign up an staff account
void sign_up_staff(struct Node *&staff_accounts)
{
	system("cls");
	cin.ignore(80,'\n');		// clear '\n';
	
	string username, password;
	cout << "\n\n\t\t%%%%%%%%%%%%%%%%%%%% Sign Up System %%%%%%%%%%%%%%%%%%%%";
	cout << "\n\n\t\tPlease enter the username: ";
	getline(cin, username);
	cout << "\n\t\tPlease enter the password: ";
	getline(cin, password);
	
	new_staff_list(staff_accounts, username, password);
	
	cout << "\n\n\t\tRegistration is successful\n\t\t";
	cout << "--------------------------------------------------------\n\t\t";
	system("pause");
	account_menu();
}

// Delete the specified staff account from staff_list.txt
void delete_staff_account(struct Node *&staff_accounts)
{
	system("cls");
	cin.ignore(80,'\n');
	string username, password;
	cout << "\n\n\t\t%%%%%%%%%%%%%%%%%%%% Account Deletion System %%%%%%%%%%%%%%%%%%%%";
	cout << "\n\n\t\tPlease enter the staff username to be deleted: ";
	getline(cin, username);
	cout << "\n\t\tPlease enter the password for this username: ";
	getline(cin, password);
	
	// find the object account
	struct Node *account_searched = search(staff_accounts, username);
	
	// Check whether username matches password, then delete account and update staff_list.txt
	if (account_searched != T_NIL && account_searched->account.password == password)
    {
    	RB_delete(staff_accounts, account_searched);		// Delete this account
    	
    	// update staff_list.txt.
		ofstream output("staff_list.txt");		// Open the file
		
		struct Node *smallest;
		// do the loop until the RB_tree is empty 
		while(staff_accounts != T_NIL)
		{
			smallest= findSmallest(staff_accounts);
			output << smallest->account.username << ";" 
				   << smallest->account.password << ";"
				   << "\n";
		
			RB_delete(staff_accounts, smallest);
		}
		output.close();
	}
	else
	{
		cout << "\n\n\t\tError!! You enter a wrong username or password\n\t\t";
		cout << "--------------------------------------------------------\n\t\t";
		system("pause");
		account_menu();
	}
	
	cout << "\n\n\t\tDeletion has done successfully\n\t\t";
	cout << "--------------------------------------------------------\n\t\t";
	system("pause");
	account_menu();
}

// Delete the specified admin account from staff_list.txt
void delete_admin_account(struct Node *&admin_accounts)
{
	system("cls");
	cin.ignore(80,'\n');
	string username, password;
	cout << "\n\n\t\t%%%%%%%%%%%%%%%%%%%% Account Deletion System %%%%%%%%%%%%%%%%%%%%";
	cout << "\n\n\t\tPlease enter the admin username to be deleted: ";
	getline(cin, username);
	cout << "\n\t\tPlease enter the password for this username: ";
	getline(cin, password);
	
	// find the object account
	struct Node *account_searched = search(admin_accounts, username);
	
	// Check whether username matches password, then delete account and update admin_list.txt
	if (account_searched != T_NIL && account_searched->account.password == password)
    {
    	RB_delete(admin_accounts, account_searched);		// Delete this account
    	
    	// update admin_list.txt.
		ofstream output("admin_list.txt");		// Open the file
		
		struct Node *smallest;
		// do the loop until the RB_tree is empty 
		while(admin_accounts != T_NIL)
		{
			smallest= findSmallest(admin_accounts);
			output << smallest->account.username << ";" 
				   << smallest->account.password << ";"
				   << "\n";
		
			RB_delete(admin_accounts, smallest);
		}
		output.close();
	}
	else
	{
		cout << "\n\n\t\tError!! You enter a wrong username or password\n\t\t";
		cout << "--------------------------------------------------------\n\t\t";
		system("pause");
		account_menu();
	}
	
	cout << "\n\n\t\tDeletion has done successfully\n\t\t";
	cout << "--------------------------------------------------------\n\t\t";
	system("pause");
	account_menu();
}

// ################### End account management system ########################## 





/* %%%%%%%%%%%%%%%%%%%% Searching Book by ID %%%%%%%%%%%%%%%%%%%%%%%%%
	- searching book by ID
*/

// Menu for searching by ID
void search_by_ID()
{
	char choice = 'Y';
	
	do
	{
		system("cls");
		cin.clear();
		cin.ignore(80,'\n');		// clear '\n', because the '\n' enter in main_menu() will influence this function.
		
		string key_ID;		// The ID users want to look for.
		
		cout << "\n\n\n\t\t%%%%%%%%%%%%%%%%%%%%%%%% Search by ID %%%%%%%%%%%%%%%%%%%%%%%%";
		cout << "\n\n\t\tPlease enter the ID of the book you want to search for: ";
		getline(cin, key_ID);
		
		struct HT_Node *found_book = hash_search(book_database, key_ID);
		
		if(found_book == NULL)
		{
			cout << "\n\n\t\tSorry, the book does not exist.\n\n\t\t"
				 << "\n\n\t\tDo you want to search other book? (Y/N):";
			cin >> choice;
		}
		else
		{
			printOut_book(found_book->book_data);
			cout << "\n\n\t\tDo you want to search other book? (Y/N):";
			cin >> choice;
		}
		// Detect failed cin command and invalid input.
		while(cin.fail() || (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y'))		// cin.fail() is used to check whether cin command failed
		{
			cin.clear();
			cin.ignore(80,'\n');
			cout << "\n\n\t\tPlease enter a valid choice (Y/N): ";
			cin >> choice;
			
		}
		cout << "\n\t\t";
		system("pause");
	}while(choice == 'Y' || choice == 'y');		// end do-while
}

void printOut_book(struct Book book_data)
{
	cout << "\n\n\t\t====================================================="
		 << left << setw(20) << "\n\t\tThe details of the book:"
		 << left << setw(20) << "\n\t\t-----------------------------------------------------"
		 << left << setw(20) << "\n\t\tBook ID: " << right << setw(36) << book_data.ID
		 << left << setw(20) << "\n\t\tBook Name: " << right << setw(36) << book_data.name
		 << left << setw(20) << "\n\t\tBook Category: " << right << setw(36) << book_data.category
		 << left << setw(20) << "\n\t\tBook Author: " << right << setw(36) << book_data.author
		 << left << setw(20) << "\n\t\tBook Publisher:" << right << setw(36) << book_data.publisher
		 << left << setw(20) << "\n\t\tBook Price: " << fixed << setprecision(2) << right << setw(36) << book_data.price
		 << left << setw(20) << "\n\t\tBook Quntity: " << right << setw(36) << book_data.quantity;
}



// delete the book by ID
void deleteBook_byID(struct Database &book_database)
{
	system("cls");
	cin.clear();
	cin.ignore(80,'\n');
	
	string key_ID;
	cout << "\n\n\t\t%%%%%%%%%%%%%%%%%%%% Book Deletion System %%%%%%%%%%%%%%%%%%%%";
	cout << "\n\n\t\tPlease enter the ID of book to be deleted: ";
	getline(cin, key_ID);

	
	// find the object book
	struct HT_Node *found_book = hash_search(book_database, key_ID);
	
	// Check whether the book ID is correct
	if (found_book != NULL)
    {
    	char choice;
    	printOut_book(found_book->book_data);		// show the details of the book
    	
    	cout << "\n\n\t\tAre you sure to delete this book? (Y/N)£» ";
    	cin >> choice;
    	
    	while(cin.fail() || (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y'))		// cin.fail() is used to check whether cin command failed
		{
			cin.clear();
			cin.ignore(80,'\n');
			cout << "\n\n\t\tPlease enter a valid choice (Y/N): ";
			cin >> choice;
			
		}
		if(choice == 'Y' || choice == 'y') 
    		hash_delete(book_database, key_ID);		// Delete this account
    	else
    		delete_book();		// go to the delete book menu.
    	
    	// update sales_database, remove book whose ID is key_ID
    	sales_database.erase(key_ID);
    	update_sales_database(sales_database);
    	
		// update book_database.txt.
		ofstream output("book_database.txt");		// Open the file
		
		// store all the new information into "book_database.txt"
		for(int i = 0; i < 401; i++)
		{
			struct HT_Node *current = book_database.ID_hash_table[i]; 
			while( current != NULL)
			{
				output << current->book_data.ID << ";"
					   << current->book_data.name << ";"
					   << current->book_data.author << ";"
					   << current->book_data.category << ";"
					   << current->book_data.publisher << ";"
					   << fixed << setprecision(2) << current->book_data.price << ";"
					   << current->book_data.quantity << ";" << "\n";
				
				current = current->next;
			}
		}
		
		output.close();
		
		initialize_database(book_database);		// read the new file again after deleting;
	}
	else
	{
		cout << "\n\n\t\tError!! You enter a wrong book ID.\n\t\t";
		cout << "--------------------------------------------------------\n\t\t";
		system("pause");
		delete_book();
	}
	
	cout << "\n\n\t\tDeletion has done successfully\n\t\t";
	cout << "--------------------------------------------------------\n\t\t";
	system("pause");
	delete_book();
}


// update the book by ID
void updateBook_byID(struct Database &book_database)
{
	int choice;
	int error = 0;		// check invalid input.
	
	// Show the update choice and detect failed cin command.
	do
	{
		error = 0;
		
		system("cls");
		cin.clear();
		
		cout << "\n\n\t\t%%%%%%%%%%%%%%%%%%%% Book Update System %%%%%%%%%%%%%%%%%%%%"
			 << "\n\n\t\t1. Uptade whole the details"
			 << "\n\n\t\t2. Uptade one or few details"
			 << "\n\n\t\t0. Return to Administrator Menu";

		cout << "\n\n\n\t\tPlease enter your choice: ";
		cin >> choice;
		
		// Detect failed cin command and invalid input.
		if(cin.fail() || choice > 2 || choice < 0)		// cin.fail() is used to check whether cin command failed
		{
			cout << "\n\n\t\tPlease enter valid choice." << endl;
			cin.clear();
			cin.ignore(80,'\n');
			error = 1;
		}
		cout << "\t\t";
		system("pause");
	}while(error == 1);		// end do-while
	
	switch(choice)
	{
		case 0: administrator_menu();
				break;
		case 1: update_whole_details(book_database);
				break;
		case 2: update_few_details(book_database);
				break;
	}
}

// retype all the details of the book
void update_whole_details(struct Database &book_database)
{
	system("cls");
	cin.ignore(80,'\n');
	string key_ID;		// the key for searching.
	string ID_entered;		// using to detect uniqueness of  ID.
	
	cout << "\n\n\t\t%%%%%%%%%%%%%%%%%%%% Book Update System %%%%%%%%%%%%%%%%%%%%";
	cout << "\n\n\t\tPlease enter the ID of book to be update: ";
	getline(cin, key_ID);

	
	// find the object book
	struct HT_Node *found_book = hash_search(book_database, key_ID);
	
	// Check whether the book ID is correct
	if (found_book != NULL)
    {
    	printOut_book(found_book->book_data);		// show the details of the book
    	
    	
    	cout << "\n\n\t\tPlease enter the new details"
    		 << "\n\t\t1. Book ID: ";
    	getline(cin, ID_entered);
    	
		// Make sure ID_entered does not exist in database. 
    	if(hash_search(book_database, ID_entered) != NULL)
		{
			cout << "\n\n\t\tError! The ID has existed!\n\n\t\t";
			system("pause");
			main_menu(); 
		}
		else
		{
			found_book->book_data.ID = ID_entered;					
		}
    	cout << "\n\t\t2. Booke Name: ";
    	getline(cin, found_book->book_data.name);
    	cout << "\n\t\t3. Author: ";
    	getline(cin, found_book->book_data.author);
    	cout << "\n\t\t4. Category: ";
    	getline(cin, found_book->book_data.category);
    	cout << "\n\t\t5. Publisher: ";
    	getline(cin, found_book->book_data.publisher);
    	cout << "\n\t\t6. Price: ";
    	cin >> found_book->book_data.price;
    	cout << "\n\t\t7. Quantity: ";
    	cin >> found_book->book_data.quantity;
    	
    	// update book_database
    	ofstream output("book_database.txt");		// Open the file
		// store all the information into "book_database.txt"
		for(int i = 0; i < 401; i++)
		{
			struct HT_Node *current = book_database.ID_hash_table[i]; 
			while( current != NULL)
			{
				output << current->book_data.ID << ";"
					   << current->book_data.name << ";"
					   << current->book_data.author << ";"
					   << current->book_data.category << ";"
					   << current->book_data.publisher << ";"
					   << fixed << setprecision(2) << current->book_data.price << ";"
					   << current->book_data.quantity << ";" << "\n";
				
				current = current->next;
			}
		}
		
		output.close();
		
		initialize_database(book_database);		// read the file again after deleting;
		
		//Update the sales_database
		map<string,Book_Sales>::iterator mapItr= sales_database.find(key_ID);
		if (mapItr != sales_database.end())
		{
			(mapItr->second).ID = ID_entered;
			update_sales_database(sales_database);
			sales_database.clear();
			initialize_Book_Sales(sales_database);
		}
	}
	else
	{
		cout << "\n\n\t\tError!! You enter a wrong book ID.\n\t\t";
		cout << "--------------------------------------------------------\n\t\t";
		system("pause");
		updateBook_byID(book_database);
	}
	
	cout << "\n\n\t\tUpdating operation has done successfully\n\t\t";
	cout << "--------------------------------------------------------\n\t\t";
	system("pause");
	update_book();
}

// Choose the detail want to update
void update_few_details(struct Database &book_database)
{
	system("cls");
	cin.ignore(80,'\n');
	string key_ID;
	string ID_entered;		// using to detect uniqueness of  ID.
	cout << "\n\n\t\t%%%%%%%%%%%%%%%%%%%% Book Update System %%%%%%%%%%%%%%%%%%%%";
	cout << "\n\n\t\tPlease enter the ID of book to be update: ";
	getline(cin, key_ID);

	// find the object book
	struct HT_Node *found_book = hash_search(book_database, key_ID);
	
	// Check whether the book ID is correct
	if (found_book != NULL)
    {
				// show the details of the book
    	int choice;
    	int error = 0;		// check invalid input.
	    
		do		// repeat loop until choice == 7
		{
			do		// repeat loop when enter a wrong input
			{
				error = 0;
				
				system("cls");
				cin.clear();
				
				cout << "\n\n\t\t%%%%%%%%%%%%%%%%%%%% Book Update System %%%%%%%%%%%%%%%%%%%%";
				printOut_book(found_book->book_data);
			
				
				cout << "\n\n\t\tPlease choose the detail you want to update."
		    		 << "\n\t\t1. Book ID: "
		    		 << "\n\t\t2. Booke Name: "
			    	 << "\n\t\t3. Author: "
				     << "\n\t\t4. Category: "
		    	 	 << "\n\t\t5. Publisher: "
		    	 	 << "\n\t\t6. Price: "
			    	 << "\n\t\t7. Quantity: "
			    	 << "\n\t\t0. Finished";
		    	
		
				cout << "\n\n\n\t\tPlease enter your choice: ";
				cin >> choice;
				
				// Detect failed cin command and invalid input.
				if(cin.fail() || choice > 7 || choice < 0)		// cin.fail() is used to check whether cin command failed
				{
					cout << "\n\n\t\tPlease enter valid choice." << endl;
					cin.clear();
					cin.ignore(80,'\n');
					error = 1;
				}	
			}while(error == 1);		// end do-while
			
			cin.ignore(80,'\n');
			switch(choice)
			{
				case 0: break;
				case 1: cout << "\n\n\t\tEnter new ID: ";
						getline(cin, ID_entered);
						if(hash_search(book_database, ID_entered) != NULL)
						{
							cout << "\n\n\t\tError! The ID has existed!\n\n\t\t";
							system("pause");
							main_menu(); 
						}
						else
						{
							found_book->book_data.ID = ID_entered;
						}	
						break;
				case 2: cout << "\n\n\t\tEnter new name: ";
						getline(cin, found_book->book_data.name);
						break;
				case 3:	cout << "\n\n\t\tEnter new author: ";
						getline(cin, found_book->book_data.author);
						break;
				case 4: cout << "\n\n\t\tEnter new category: ";
						getline(cin, found_book->book_data.category);
						break;
				case 5: cout << "\n\n\t\tEnter new publisher: ";
						getline(cin, found_book->book_data.publisher);
						break;
				case 6: cout << "\n\n\t\tEnter new price: ";
						cin >> found_book->book_data.price;
						break;
				case 7: cout << "\n\n\t\tEnter new quantity: ";
						cin >> found_book->book_data.quantity;
						break;
			}	// end swtich
			
		}while(choice != 0);	// end do-while
    	
    	// store all the information into "book_database.txt"
    	ofstream output("book_database.txt");		// Open the file
		for(int i = 0; i < 401; i++)
		{
			struct HT_Node *current = book_database.ID_hash_table[i]; 
			while( current != NULL)
			{
				output << current->book_data.ID << ";"
					   << current->book_data.name << ";"
					   << current->book_data.author << ";"
					   << current->book_data.category << ";"
					   << current->book_data.publisher << ";"
					   << fixed << setprecision(2) << current->book_data.price << ";"
					   << current->book_data.quantity << ";" << "\n";
				
				current = current->next;
			}
		}
		output.close();
		
		initialize_database(book_database);		// read the file again after deleting;
		
		//Update the sales_database
		map<string,Book_Sales>::iterator mapItr= sales_database.find(key_ID);
		if (mapItr != sales_database.end())
		{
			(mapItr->second).ID = ID_entered;
			update_sales_database(sales_database);
			sales_database.clear();
			initialize_Book_Sales(sales_database);
		}
	}
	else
	{
		cout << "\n\n\t\tError!! You enter a wrong book ID.\n\t\t";
		cout << "--------------------------------------------------------\n\t\t";
		system("pause");
		updateBook_byID(book_database);
	}
	
	cout << "\n\n\t\tUpdating operation has done successfully\n\t\t";
	cout << "--------------------------------------------------------\n\t\t";
	system("pause");
	update_book();
}



// %%%%%%%%%%%%%%%%%%%%% End Searching Book by ID %%%%%%%%%%%%%%%%%%%%%%%%





/*	%%%%%%%%%%%%%% Red-Black Tree %%%%%%%%%%%%%%%

		Store the username and password.
		Sort the data using RED-BLACK TREE.
	______________________________________________
*/


// ------------------- Red-Black Tree insertion --------------------

// create a new node
void New_Node(struct Node* newNode, string username, string password)
{
	struct admin_staff account;
	account.password = password;
	account.username = username;
	newNode->account = account;
	newNode->key = account.username;
	newNode->left = newNode->right = newNode->parent = T_NIL; 
    newNode->color = RED;
}


void leftRotation(struct Node *&root, struct Node *&A)
{
	struct Node *B = A->right;
	
	struct Node *T2 = B->left;
	A->right = T2;
	
	if(T2 != T_NIL) 
		T2->parent = A;
	
	//build the relation between B and B's grandparent
	B->parent = A->parent;
	if(A->parent == T_NIL)
		root = B;
	else if(A == A->parent->left)
		A->parent->left = B;
	else
		A->parent->right = B;
	
	B->left = A;
	A->parent = B; 
}

void rightRotation(struct Node *&root, struct Node *&A)
{
	struct Node *B = A->left;
	A->left = B->right;
	
	if(B->right != T_NIL)
		B->right->parent = A;
	
	B->parent = A->parent;
	if(A->parent == T_NIL)
		root = B;
	else if(A == A->parent->left)
		A->parent->left = B;
	else
		A->parent->right = B;
	
	B->right = A;
	A->parent = B;
}

// Fix up the Binary Search Tree and make it become Red-Black Tree 
void fixUp(struct Node *&tree, struct Node *&current)
{
	struct Node *grandparent = T_NIL;
	struct Node *parent = T_NIL;
	
	while(current->parent->color == RED)
	{
		grandparent = current->parent->parent;
		parent = current->parent;
		if(parent == grandparent->left)
		{
			struct Node *uncle = grandparent->right;
			
			// case1:
			if(uncle->color == RED)
			{
				grandparent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				current = grandparent;
			}
			else
			{
				// case 2: LR
				if(current == parent->right)
				{
					leftRotation(tree, parent);
					current = parent;
					parent = current->parent;
					grandparent = current->parent->parent;
				}
				
				// case 3: LL
				parent->color = BLACK;
				grandparent->color = RED;
				rightRotation(tree, grandparent);
			}
		}
		else
		{
			struct Node *uncle = grandparent->left;
			
			// case1:
			if(uncle->color == RED)
			{
				grandparent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				current = grandparent;
			}
			else
			{
				// case 2: RL
				if(current == parent->left)
				{
					rightRotation(tree, parent);
					current = parent;
					parent = current->parent;
					grandparent = current->parent->parent;
				}
				
				// case 3: RR
				parent->color = BLACK;
				grandparent->color = RED;
				leftRotation(tree, grandparent);
			}
		}		
	}		//END while
	
	tree->color = BLACK;
}

// Insert a new node in to Tree and call fixUp() to fix up such a tree.
void RB_insert(Node* &root, Node* newNode)
{
    Node *parent = T_NIL;
    Node *place = root;

    // 1. View red-black tree as a binary search tree, and insert new node into this binary search tree
    while (place != T_NIL)
    {
        parent = place;
        if (newNode->key < place->key)
            place = place->left;
        else
            place = place->right;
    }

    newNode->parent = parent;
    
    if (parent == T_NIL)		// newNode is root;
    {
    	root = newNode;
	}
	else if(newNode->key < parent->key)
	{
		parent->left = newNode; 
	}
	else
	{
		parent->right = newNode;
	}


    // 2. Set new node's color as red;
    newNode->color = RED;
	newNode->left = T_NIL;
	newNode->right = T_NIL;
	
    // 3. Fix up the binary search tree so that it will become red-black tree;
    fixUp(root, newNode);
}

// Insert data inputed from users.
struct Node *insert(Node *tree, string username, string password)
{
	Node *newNode = new Node;
	New_Node(newNode, username, password);
	RB_insert(tree, newNode);
	return tree;
}

// Search the account accounding to username
struct Node* search(struct Node *tree, string key)
{
	if (tree == T_NIL || tree->key == key)
		return tree;

	if (key < tree->key)
		return search(tree->left, key);
	else
		return search(tree->right, key);
}



//------------------ Red-Black Tree DELETION  ------------------------

// return the smallest red_black tree node
struct Node *findSmallest(struct Node *tree)
{
	if(tree == T_NIL || tree->left == T_NIL)
		return tree;
	else
		return findSmallest(tree->left);
}


void RB_Delete_Fixup(struct Node *&tree, struct Node *fixNode)
{
	struct Node *sibling;
	
	while(fixNode != tree && fixNode->color == BLACK)
	{
		if(fixNode == fixNode->parent->left)		// fixNode is the left child of its parent.
		{
			// the sibling of fixNode
			sibling = fixNode->parent->right;
			
			// Case 1: fixNode's sibling is RED;
			if(sibling->color == RED)
			{
				// exchange the color between fixNode's parent and sibling.
				sibling->color = BLACK;
				fixNode->parent->color = RED;
				
				leftRotation(tree, fixNode->parent);
				
				// iterate at a new place.
				sibling = fixNode->parent->right; 
			}
			
			// Case 2: fixNode's sibling is BLACK. And both children of sibling are BLACK;
			if(sibling->left->color == BLACK && sibling->right->color == BLACK )
			{
				sibling->color = RED;
				fixNode = fixNode->parent;		// If original fixNode's parent is RED, the balance operation will be ended ;
			}
			else
			{
				// Case 3: sibling is the right side of its parent, and sibling's left child is RED, and sibling's right child is BLACK; (R-L)
				if(sibling->right->color == BLACK)
				{
					sibling->color = RED;
					sibling->left->color = BLACK;
					rightRotation(tree, sibling);
					sibling = fixNode->parent->right; 
				}
				// Case 4: sibling is the right side of its parent, and sibling's right child is RED, and sibling's left child is random color; (R-R)
				sibling->color = fixNode->parent->color;
				fixNode->parent->color = BLACK;
				sibling->right->color = BLACK;
				leftRotation(tree, fixNode->parent);
				fixNode =tree;
			}
		}
		else		//// fixNode is the right child of its parent.
		{
			// the sibling of fixNode
			sibling = fixNode->parent->left;
			
			// Case 1: fixNode's sibling is RED;
			if(sibling->color == RED)
			{
				// exchange the color between fixNode's parent and sibling.
				sibling->color = BLACK;
				fixNode->parent->color = RED;
				
				rightRotation(tree, fixNode->parent);
				
				// iterate at a new place.
				sibling = fixNode->parent->left; 
			}
			
			// Case 2: fixNode's sibling is BLACK. And both children of sibling are BLACK;
			if(sibling->right->color == BLACK && sibling->left->color == BLACK)
			{
				sibling->color = RED;
				fixNode = fixNode->parent;		// If original fixNode's parent is RED, the balance operation will be ended ;
			}
			else
			{
				// Case 3: sibling is the left side of its parent, and sibling's right child is RED, and sibling's left child is BLACK; (L-R)
				if(sibling->left->color == BLACK)
				{
					sibling->color = RED;
					sibling->right->color = BLACK;
					leftRotation(tree, sibling);
					sibling = fixNode->parent->left; 
				}
				// Case 4: sibling is the left side of its parent, and sibling's left child is RED, and sibling's right child is random color; (L-L)
				sibling->color = fixNode->parent->color;
				fixNode->parent->color = BLACK;
				sibling->left->color = BLACK;
				rightRotation(tree, fixNode->parent);
				fixNode =tree;
			}
		}
	}
	

	fixNode->color = BLACK;		// If fixNode is RED or fixNode is tree make it become BLACK.
}


void RB_transplant(struct Node *&tree, struct Node *&node, struct Node *&replace)
{
	if(node->parent == T_NIL)
		tree = replace;
	else if(node == node->parent->left)
		node->parent->left = replace;
	else
		node->parent->right = replace;
	
	replace->parent = node->parent;
}


void RB_delete(struct Node *&tree, struct Node *node)
{
	
	struct Node *fixNode;		// The child of "replace node", which will be the beginning node of fixing up.
	struct Node *replace = node;		// The successor, which is to be used to replace the deleted node;
	RBTColor color = replace->color;		// Save the original color of "replace node"
	
	if(node->left == T_NIL)
	{
		fixNode = node->right;
		RB_transplant(tree, node, node->right); 
	}
	else if(node->right == T_NIL)
	{
		fixNode = node->left;
		RB_transplant(tree, node, node->left);
	}
	else
	{
		// Find in-order successor
		replace = findSmallest(node->right);
		color = replace->color;
		fixNode = replace->right;
		
		if(replace->parent == node)
		{
			fixNode->parent = replace;		// In the RB_Delect_Fixup function, we need to know fixNode's parent, although it is NIL.
		}
		else
		{
			RB_transplant(tree, replace, replace->right);		// In the RB_Delect_Fixup function, we need to know fixNode's parent, although it is NIL.
			// Now, the "replace node" has been separated from tree, and prepare for substituting for the "node";
			replace->right = node->right;
			replace->right->parent = replace;
		}
		RB_transplant(tree, node, replace);
		replace->left = node->left;
		replace->left->parent = replace;
		replace->color = node->color; 
	}
	
	if(color == BLACK)
		RB_Delete_Fixup(tree, fixNode);
}


void deleteNode(struct Node *&tree, string key)
{
    struct Node *node;
	
    // Find the node which contains data equal to key. If it exists, delete it.
    if ((node = search(tree, key)) != T_NIL)
        RB_delete(tree, node);
}

// %%%%%%%%%%%%%%%%%%%%%% END Red-Black Tree %%%%%%%%%%%%%%%%%%%%%%%%%%%% 



/*	%%%%%%%%%%%%%%%%%%%% Hash Table %%%%%%%%%%%%%%%%%%%%%%%%%%%
		
		- Search book by ID
		- Delete book by ID
		- Add book by ID 
*/


struct HT_Node *new_HT_Node(struct Book book_data)
{
	struct HT_Node *temp = new HT_Node;
	temp->book_data = book_data;
	temp->next = NULL;
	temp->prev = NULL;
	
	return temp;
}

int hashing_function(string key)
{
	// convert string to a key value
	tr1::hash<string> key_value;
	
	int index = key_value(key) % 401;
	
	return index;		// return value of hashing function
}


void doubly_LL_insert(struct HT_Node *&head, struct HT_Node *newNode)
{
	newNode->next = head;
	if(head != NULL)
		head->prev = newNode;
	head = newNode;
	newNode->prev = NULL;
}

// Search the book according to book ID
struct HT_Node *doubly_LL_search(struct HT_Node *head, string key)
{
	HT_Node *current = head;
	
	// search the key.
	while(current != NULL && current->book_data.ID != key)
	{
		current = current->next;
	}
	
	return current;
}

// delete the given node.
void doubly_LL_delete(struct HT_Node *&head, struct HT_Node *deleted_node) 
{	
	// Delete the key node.
	if(deleted_node->prev != NULL)
	{
		deleted_node->prev->next = deleted_node->next;
	}
	else
	{
		head = deleted_node->next;
	}
	if(deleted_node->next != NULL)
	{
		deleted_node->next->prev = deleted_node->prev;
	}
}


// insert the node into the hash table. and function will prevent the isertion of the same ID.
void hash_insert(struct Database &book_database, struct Book newBook)
{
	// Check for duplicate book ID.
	if(hash_search(book_database, newBook.ID) != NULL)
	{
		cout << "\n\n\t\tError! This ID has already existed.\n\n\t\t";
		system("pause");
		main_menu();		// return to main menu
	}
	// store the book in a new hash table node
	struct HT_Node *newNode = new_HT_Node(newBook);
	
	int index = hashing_function(newNode->book_data.ID);
	doubly_LL_insert(book_database.ID_hash_table[index], newNode);
}

// Search the book accrding to ID using hash table;
struct HT_Node *hash_search(struct Database book_database, string key)
{
	int index = hashing_function(key);
	struct HT_Node *found_book = doubly_LL_search(book_database.ID_hash_table[index], key);
	
	return found_book;
}

// Delete the node according to ID
void hash_delete(struct Database &book_database, string key)
{
	int index = hashing_function(key);
	
	struct HT_Node *found_book = doubly_LL_search(book_database.ID_hash_table[index], key);
	 
	if(found_book != NULL)
		doubly_LL_delete(book_database.ID_hash_table[index], found_book);
}

// %%%%%%%%%%%%%%%%%%%%%% END Hash Table %%%%%%%%%%%%%%%%%%%%%%%%%%%%% 



/*	%%%%%%%%%%%%%%%%%%%%%%%%%% Singly Linked List %%%%%%%%%%%%%%%%%%%%%%%%%%%
	- store according to category (the number of categories is determined)
	- store according to author (the number of various author is unknown)
	- store according to the alphabetical order of book name
	__________________________________________________________________
*/

// Insert a new node at the beginning of the single linked list.
void singly_LL_insert(struct LL_Node *&head, struct LL_Node *newNode)
{
	newNode->next = head;
	head = newNode;
}

// initialize a signly linked list node
struct LL_Node *New_LL_Node(struct Book newBook)
{
	struct LL_Node *newNode = new LL_Node;
	newNode->book_data = newBook;
	newNode->next = NULL;
	
	return newNode;
} 

// sort and store the books according to category
void category_insert(struct Database &book_database, struct Book newBook)
{
	struct LL_Node *newNode = New_LL_Node(newBook);
	
	if(newBook.category == "History")
		singly_LL_insert(book_database.category[0], newNode);
	else if(newBook.category == "Adventure")
		singly_LL_insert(book_database.category[1], newNode);
	else if(newBook.category == "Classic")
		singly_LL_insert(book_database.category[2], newNode);
	else if(newBook.category == "Detective")
		singly_LL_insert(book_database.category[3], newNode);
	else if(newBook.category == "Fairy Tale")
		singly_LL_insert(book_database.category[4], newNode);
	else if(newBook.category == "Horror")
		singly_LL_insert(book_database.category[5], newNode);
	else if(newBook.category == "Romance")
		singly_LL_insert(book_database.category[6], newNode);
	else if(newBook.category == "Textbook")
		singly_LL_insert(book_database.category[7], newNode);
	else if(newBook.category == "Poetry")
		singly_LL_insert(book_database.category[8], newNode);
	else	// Other type 
		singly_LL_insert(book_database.category[9], newNode);

}


void author_insert(struct Database &book_database, struct Book newBook)
{
	struct LL_Node *newNode = New_LL_Node(newBook);
	
	vector<LL_Node*>::iterator index = book_database.author.begin();
	while(index != book_database.author.end() && (*index)->book_data.author != newNode->book_data.author)
	{
		++index;
	}
	
	// The author does not exist in vector.
	if(book_database.author.empty() || index == book_database.author.end())
	{
		book_database.author.push_back(newNode);
	}
	else		// the author have exist
	{
		singly_LL_insert(*index, newNode);
	}
}

// Search the book by category
void search_by_category(struct Database book_database)
{
	bool error = 0;		// check invalid input.
	int choice;
	
	do
	{
		system("cls");
		cin.clear();
		
		error = 0;
		cout << "\n\n\t\t%%%%%%%%%%%%%%%%%%%% Search by Category %%%%%%%%%%%%%%%%%%%%"
			 << "\n\n\t\t\t1. History"
			 << "\n\t\t\t2. Adventure"
			 << "\n\t\t\t3. Classic"
			 << "\n\t\t\t4. Detective"
			 << "\n\t\t\t5. Fairy Tale"
			 << "\n\t\t\t6. Horror"
			 << "\n\t\t\t7. Romance"
			 << "\n\t\t\t8. Textbook"
			 << "\n\t\t\t9. Classic"
			 << "\n\t\t\t10. Other\n\n\t\t"
			 << "\n\t\t\t0. Return to Searching Menu";
		cout << "\n\n\n\t\tPlease enter your choice: ";
		cin >> choice;
		
		// Detect failed cin command and invalid input.
		if(cin.fail() || choice > 10 || choice < 0)		// cin.fail() is used to check whether cin command failed
		{
			cout << "\n\n\t\tPlease enter valid choice." << endl;
			cin.clear();
			cin.ignore(80,'\n');
			error = 1;
		}
	}while(error == 1);		// end do-while
	
	// make sure the category contain books, or return to searching menu 
	if(book_database.category[choice-1] == NULL)
	{
		cout << "\n\n\t\tSorry, there are no book in this category\n\n\t\t";
		system("pause");
		return;
	}
	
	switch(choice)
	{
		case 0: search_book();
				break;
		default: 	system("cls");
				 	
					
					cout << "\n\n\t\t%%%%%%%%%%%%%%%%%%%%%%% "; 
					if(choice == 10)
						cout << "Other";
					else 
						cout << book_database.category[choice-1]->book_data.category;
				 	
					cout << " %%%%%%%%%%%%%%%%%%%%%%%";
					// sort the linked list using merge sorting
					recMergeSort(book_database.category[choice-1]);
				 	struct LL_Node *current = book_database.category[choice-1];
					while(current != NULL)
					{
						printOut_book(current->book_data);
						current = current->next;
					}
					cout << "\n\n\t\t";
					system("pause");
					return;
					break;
	}		// End switch
}

// Search book by author,
void search_by_author(struct Database book_database)
{
	string author_name;
	
	system("cls");
	cin.clear();
		
	cout << "\n\n\t\t%%%%%%%%%%%%%%%%%%%% Search by Author %%%%%%%%%%%%%%%%%%%%"
		 << "\n\n\t\tPlease enter author's name you want to search: ";
	cin.ignore(80,'\n');
	getline(cin, author_name);
	
	// Linear Searching
	vector<LL_Node*>::iterator vecItr = book_database.author.begin();
	while(vecItr != book_database.author.end() && (*vecItr)->book_data.author != author_name)
	{
		++vecItr;
	}
	
	// The books doesn't exist	
	if(book_database.author.empty() || vecItr == book_database.author.end())
	{
		cout << "\n\n\t\tSorry, we do not have book written by " << author_name << "\n\n\t\t";
		system("pause");
		return;
	}
	
	cout << "\n\n\t\t%%%%%%%%%%%%%%%%%%%%%%% " << author_name << " %%%%%%%%%%%%%%%%%%%%%%%%%%";
	
	struct LL_Node *current = *vecItr;
	// sort the linked list using merge sorting
	recMergeSort(current);
	
	// Print out all related book
	while(current!= NULL)
	{
		printOut_book(current->book_data);
		
		current = current->next;
	}
	cout << "\n\n\t\t";
	system("pause");
	return; 
}


// display all the book according to the alphabetical order of book name
void show_all_book(struct Database book_database)
{
	system("cls");
	cin.clear();
	
	// sort the linked list using merge sorting
	recMergeSort(book_database.name);
	
	cout << "\n\n\t\t%%%%%%%%%%%%%%%%%%%%%%% All the Book %%%%%%%%%%%%%%%%%%%%%%%%%%\n\n"
		 << "\n\n\t\tDisplay the Book Accouding to Alphabetical Order of Name";
	
	struct LL_Node *current = book_database.name;
	while(current != NULL)
	{
		printOut_book(current->book_data);
		
		current = current->next;
	}
	
	cout << "\n\n\n\t\tPlease enter any key to return to Main Menu\n\n\t\t";
	system("pause");
	main_menu(); 
}

// search the book according to name
void search_by_name(struct Database book_database)
{
	char choice = 'Y';
	
	do
	{
		system("cls");
		cin.clear();
		cin.ignore(80,'\n');		// clear '\n', because the '\n' enter in main_menu() will influence this function.
		
		string key_name;		// The ID users want to look for.
		
		cout << "\n\n\n\t\t%%%%%%%%%%%%%%%%%%%%%%%% Search by Name %%%%%%%%%%%%%%%%%%%%%%%%";
		cout << "\n\n\t\tPlease enter the name of book you want to search for: ";
		getline(cin, key_name);
		
		// sort the linked list using merge sorting
		recMergeSort(book_database.name);
		// search the book using binary search.
		struct LL_Node *found_book = binarySearch(book_database.name, key_name);
		
		if(found_book == NULL)
		{
			cout << "\n\n\t\tSorry, the book does not exist.\n\n\t\t"
				 << "\n\n\t\tDo you want to search other book? (Y/N):";
			cin >> choice;
		}
		else
		{
			printOut_book(found_book->book_data);
			cout << "\n\n\t\tDo you want to search other book? (Y/N):";
			cin >> choice;
		}
		// Detect failed cin command and invalid input.
		while(cin.fail() || (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y'))		// cin.fail() is used to check whether cin command failed
		{
			cin.clear();
			cin.ignore(80,'\n');
			cout << "\n\n\t\tPlease enter a valid choice (Y/N): ";
			cin >> choice;
			
		}
		cout << "\n\t\t";
		system("pause");
	}while(choice == 'Y' || choice == 'y');		// end do-while
}


// retype all the details of the book
void updateByName_whole_details(struct Database &book_database)
{
	system("cls");
	cin.ignore(80,'\n');
	string key_name;		// the key for searching.
	string ID_entered;		// using to detect uniqueness of  ID.
	
	cout << "\n\n\t\t%%%%%%%%%%%%%%%%%%%% Book Update System %%%%%%%%%%%%%%%%%%%%";
	cout << "\n\n\t\tPlease enter the name of book to be update: ";
	getline(cin, key_name);

	
	// sort the linked list using merge sorting
	recMergeSort(book_database.name);
	
	// find the book needed to deleted by binary search.
	struct LL_Node *found_LL_book = binarySearch(book_database.name, key_name);
	
	// find the object book
	struct HT_Node *found_book = hash_search(book_database, found_LL_book->book_data.ID);
	string key_ID = found_book->book_data.ID;		// store book ID for updating sales_database
	
	// Check whether the book ID is correct
	if (found_book != NULL)
    {
    	printOut_book(found_book->book_data);		// show the details of the book
    	
    	
    	cout << "\n\n\t\tPlease enter the new details"
    		 << "\n\t\t1. Book ID: ";
    	getline(cin, ID_entered);
    	
		// Make sure ID_entered does not exist in database. 
    	if(hash_search(book_database, ID_entered) != NULL)
		{
			cout << "\n\n\t\tError! The ID has existed!\n\n\t\t";
			system("pause");
			main_menu(); 
		}
		else
		{
			found_book->book_data.ID = ID_entered;					
		}
    	cout << "\n\t\t2. Booke Name: ";
    	getline(cin, found_book->book_data.name);
    	cout << "\n\t\t3. Author: ";
    	getline(cin, found_book->book_data.author);
    	cout << "\n\t\t4. Category: ";
    	getline(cin, found_book->book_data.category);
    	cout << "\n\t\t5. Publisher: ";
    	getline(cin, found_book->book_data.publisher);
    	cout << "\n\t\t6. Price: ";
    	cin >> found_book->book_data.price;
    	cout << "\n\t\t7. Quantity: ";
    	cin >> found_book->book_data.quantity;
    	
    	ofstream output("book_database.txt");		// Open the file
		// store all the information into "book_database.txt"
		for(int i = 0; i < 401; i++)
		{
			struct HT_Node *current = book_database.ID_hash_table[i]; 
			while( current != NULL)
			{
				output << current->book_data.ID << ";"
					   << current->book_data.name << ";"
					   << current->book_data.author << ";"
					   << current->book_data.category << ";"
					   << current->book_data.publisher << ";"
					   << fixed << setprecision(2) << current->book_data.price << ";"
					   << current->book_data.quantity << ";" << "\n";
				
				current = current->next;
			}
		}
		
		output.close();
		
		initialize_database(book_database);		// read the file again after deleting;
		
		
		//Update the sales_database
		map<string,Book_Sales>::iterator mapItr= sales_database.find(key_ID);
		if (mapItr != sales_database.end())
		{
			(mapItr->second).ID = ID_entered;
			update_sales_database(sales_database);
			sales_database.clear();
			initialize_Book_Sales(sales_database);
		}
	}
	else
	{
		cout << "\n\n\t\tError!! You enter a wrong book ID.\n\t\t";
		cout << "--------------------------------------------------------\n\t\t";
		system("pause");
		updateBook_byID(book_database);
	}
	
	cout << "\n\n\t\tUpdating operation has done successfully\n\t\t";
	cout << "--------------------------------------------------------\n\t\t";
	system("pause");
	update_book();
}

// Choose the detail want to update
void updateByName_few_details(struct Database &book_database)
{
	system("cls");
	cin.ignore(80,'\n');
	string key_name;
	string ID_entered;		// using to detect uniqueness of  ID.
	cout << "\n\n\t\t%%%%%%%%%%%%%%%%%%%% Book Update System %%%%%%%%%%%%%%%%%%%%";
	cout << "\n\n\t\tPlease enter the name of book to be update: ";
	getline(cin, key_name);

	// sort the linked list using merge sorting
	recMergeSort(book_database.name);
	
	// find the book needed to deleted by binary search.
	struct LL_Node *found_LL_book = binarySearch(book_database.name, key_name);
	
	// find the object book
	struct HT_Node *found_book = hash_search(book_database, found_LL_book->book_data.ID);
	string key_ID = found_book->book_data.ID;		// store ID for updating sales_database 
	// Check whether the book ID is correct
	if (found_book != NULL)
    {
				// show the details of the book
    	int choice;
    	int error = 0;		// check invalid input.
	    
		do		// repeat loop until choice == 7
		{
			do		// repeat loop when enter a wrong input
			{
				error = 0;
				
				system("cls");
				cin.clear();
				
				cout << "\n\n\t\t%%%%%%%%%%%%%%%%%%%% Book Update System %%%%%%%%%%%%%%%%%%%%";
				printOut_book(found_book->book_data);
			
				
				cout << "\n\n\t\tPlease choose the detail you want to update."
		    		 << "\n\t\t1. Book ID: "
		    		 << "\n\t\t2. Booke Name: "
			    	 << "\n\t\t3. Author: "
				     << "\n\t\t4. Category: "
		    	 	 << "\n\t\t5. Publisher: "
		    	 	 << "\n\t\t6. Price: "
			    	 << "\n\t\t7. Quantity: "
			    	 << "\n\t\t0. Finished";
		    	
		
				cout << "\n\n\n\t\tPlease enter your choice: ";
				cin >> choice;
				
				// Detect failed cin command and invalid input.
				if(cin.fail() || choice > 7 || choice < 0)		// cin.fail() is used to check whether cin command failed
				{
					cout << "\n\n\t\tPlease enter valid choice." << endl;
					cin.clear();
					cin.ignore(80,'\n');
					error = 1;
				}	
			}while(error == 1);		// end do-while
			
			cin.ignore(80,'\n');
			switch(choice)
			{
				case 0: break;
				case 1: cout << "\n\n\t\tEnter new ID: ";
						getline(cin, ID_entered);
						if(hash_search(book_database, ID_entered) != NULL)
						{
							cout << "\n\n\t\tError! The ID has existed!\n\n\t\t";
							system("pause");
							main_menu(); 
						}
						else
						{
							// udpate book ID
							found_book->book_data.ID = ID_entered;
						}
							
						break;
				case 2: cout << "\n\n\t\tEnter new name: ";
						getline(cin, found_book->book_data.name);
						break;
				case 3:	cout << "\n\n\t\tEnter new author: ";
						getline(cin, found_book->book_data.author);
						break;
				case 4: cout << "\n\n\t\tEnter new category: ";
						getline(cin, found_book->book_data.category);
						break;
				case 5: cout << "\n\n\t\tEnter new publisher: ";
						getline(cin, found_book->book_data.publisher);
						break;
				case 6: cout << "\n\n\t\tEnter new price: ";
						cin >> found_book->book_data.price;
						break;
				case 7: cout << "\n\n\t\tEnter new quantity: ";
						cin >> found_book->book_data.quantity;
						break;
			}	// end swtich
			
		}while(choice != 0);	// end do-while
    	
    	
    	ofstream output("book_database.txt");		// Open the file
		// store all the information into "book_database.txt"
		for(int i = 0; i < 401; i++)
		{
			struct HT_Node *current = book_database.ID_hash_table[i]; 
			while( current != NULL)
			{
				output << current->book_data.ID << ";"
					   << current->book_data.name << ";"
					   << current->book_data.author << ";"
					   << current->book_data.category << ";"
					   << current->book_data.publisher << ";"
					   << fixed << setprecision(2) << current->book_data.price << ";"
					   << current->book_data.quantity << ";" << "\n";
				
				current = current->next;
			}
		}
		
		output.close();
		
		initialize_database(book_database);		// read the file again after deleting;
		
		//Update the sales_database
		map<string,Book_Sales>::iterator mapItr= sales_database.find(key_ID);
		if (mapItr != sales_database.end())
		{
			(mapItr->second).ID = ID_entered;
			update_sales_database(sales_database);
			sales_database.clear();
			initialize_Book_Sales(sales_database);
		}
	}
	else
	{
		cout << "\n\n\t\tError!! You enter a wrong book ID.\n\t\t";
		cout << "--------------------------------------------------------\n\t\t";
		system("pause");
		updateBook_byID(book_database);
	}
	
	cout << "\n\n\t\tUpdating operation has done successfully\n\t\t";
	cout << "--------------------------------------------------------\n\t\t";
	system("pause");
	update_book();
}


// delete the book according to name
void deleteBook_byName(struct Database &book_database)
{
	system("cls");
	cin.clear();

	string key_name;
	cout << "\n\n\t\t%%%%%%%%%%%%%%%%%%%% Book Deletion System %%%%%%%%%%%%%%%%%%%%";
	cout << "\n\n\t\tPlease enter the name of book to be deleted: ";
	
	cin.ignore(80,'\n');
	getline(cin, key_name);

	// sort the linked list using merge sorting
	recMergeSort(book_database.name);
	
	// find the book needed to deleted by binary search.
	struct LL_Node *found_book = binarySearch(book_database.name, key_name);
	
	
	// Check whether the book ID is correct
	if (found_book != NULL)
    {
    	char choice;
    	printOut_book(found_book->book_data);		// show the details of the book
    	
    	cout << "\n\n\t\tAre you sure to delete this book? (Y/N): ";
    	cin >> choice;
    	
    	while(cin.fail() || (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y'))		// cin.fail() is used to check whether cin command failed
		{
			cin.clear();
			cin.ignore(80,'\n');
			cout << "\n\n\t\tPlease enter a valid choice (Y/N): ";
			cin >> choice;
			
		}
		
		string key_ID = found_book->book_data.ID;
		
		if(choice == 'Y' || choice == 'y') 
    		hash_delete(book_database, key_ID);		// Delete this account
    	else
    		delete_book();		// return to the delete book menu.
    	
    	
    	// update sales_database, remove book whose ID is key_ID
    	sales_database.erase(key_ID);
    	update_sales_database(sales_database);
    	
		// update book_database.txt.
		ofstream output("book_database.txt");		// Open the file
		
		// store all the new information into "book_database.txt"
		for(int i = 0; i < 401; i++)
		{
			struct HT_Node *current = book_database.ID_hash_table[i]; 
			while( current != NULL)
			{
				output << current->book_data.ID << ";"
					   << current->book_data.name << ";"
					   << current->book_data.author << ";"
					   << current->book_data.category << ";"
					   << current->book_data.publisher << ";"
					   << fixed << setprecision(2) << current->book_data.price << ";"
					   << current->book_data.quantity << ";" << "\n";
				
				current = current->next;
			}
		}
		
		output.close();
		
		initialize_database(book_database);		// read the new file again after deleting;
	}
	else
	{
		cout << "\n\n\t\tError!! You enter a wrong book name.\n\t\t";
		cout << "--------------------------------------------------------\n\t\t";
		system("pause");
		delete_book();
	}
	
	cout << "\n\n\t\tDeletion has done successfully\n\t\t";
	cout << "--------------------------------------------------------\n\t\t";
	system("pause");
	delete_book();
}

// update the book by name
void updateBook_byName(struct Database &book_database)
{
	int choice;
	int error = 0;		// check invalid input.
	
	// Show the update choice and detect failed cin command.
	do
	{
		error = 0;
		
		system("cls");
		cin.clear();
		
		cout << "\n\n\t\t%%%%%%%%%%%%%%%%%%%% Book Update System %%%%%%%%%%%%%%%%%%%%"
			 << "\n\n\t\t1. Uptade whole the details"
			 << "\n\n\t\t2. Uptade one or few details"
			 << "\n\n\t\t0. Return to Administrator Menu";

		cout << "\n\n\n\t\tPlease enter your choice: ";
		cin >> choice;
		
		// Detect failed cin command and invalid input.
		if(cin.fail() || choice > 2 || choice < 0)		// cin.fail() is used to check whether cin command failed
		{
			cout << "\n\n\t\tPlease enter valid choice." << endl;
			cin.clear();
			cin.ignore(80,'\n');
			error = 1;
		}
		cout << "\t\t";
		system("pause");
	}while(error == 1);		// end do-while
	
	switch(choice)
	{
		case 0: administrator_menu();
				break;
		case 1: updateByName_whole_details(book_database);
				break;
		case 2: updateByName_few_details(book_database);
				break;
	}
}

// %%%%%%%%%%%%%%%%%%%%%%%%%% End Singly Linked List %%%%%%%%%%%%%%%%%%%%%%%%%%%


/* %%%%%%%%%%%%%%%%%%%%%% Merge Sort %%%%%%%%%%%%%%%%%%%%%%%%%
		Sort the singly linked list according to 
		the alphabetical order of book name
	__________________________________________________________
*/

void divideList(struct LL_Node *&head1, struct LL_Node *&head2)
{
	struct LL_Node *middle;
	struct LL_Node *current;
	
	if(head1 == NULL)		// List is empty
		head2 = NULL;
	else if(head1->next == NULL)		// List has only one node
		head2 = NULL;
	else
	{
		middle = head1;
		current = head1->next;
		if(current != NULL)
			current = current->next;
		while(current != NULL)
		{
			middle = middle->next;
			current = current->next;
			if(current != NULL)
				current = current->next;
		}
		head2 = middle->next;
		middle->next = NULL;
	}
}

struct LL_Node* mergeList(struct LL_Node *head1, struct LL_Node *head2)
{
	struct LL_Node *lastMerged;		// pointer to the last node of merged list
	struct LL_Node *newHead;
	if(head1 == NULL)		// The first sublist is empty
		return head2;
	else if(head2 == NULL)
		return head1;
	else
	{
		if(head1->book_data.name < head2->book_data.name)
		{
			newHead = head1;
			head1 = head1->next;
			lastMerged = newHead;
		}
		else
		{
			newHead = head2;
			head2 = head2->next;
			lastMerged = newHead;
		}
		while(head1 != NULL && head2 != NULL)
		{
			if(head1->book_data.name < head2->book_data.name)
			{
				lastMerged->next = head1;
				lastMerged = lastMerged->next;
				head1 = head1->next;
			}
			else
			{
				lastMerged->next = head2;
				lastMerged = lastMerged->next;
				head2 = head2->next;
			}
		}
		if(head1 == NULL)
			lastMerged->next = head2;
		else
			lastMerged->next = head1;
		return newHead;
	}
}

// recursive
void recMergeSort(struct LL_Node *&head)
{
	struct LL_Node *otherHead;
	if(head != NULL)
	{
		if(head->next != NULL)
		{
			divideList(head, otherHead);
			recMergeSort(head);
			recMergeSort(otherHead);
			head = mergeList(head, otherHead);
		}
	}
}

// %%%%%%%%%%%%%%%%%%%% End Merge Sort %%%%%%%%%%%%%%%%%%%%%%



/*	%%%%%%%%%%%%%%%%%%% Binary Search %%%%%%%%%%%%%%%%%%%%%%%
		implement binary search in singly linked list
	_________________________________________________________	
*/

// function to find out middle element 
struct LL_Node* find_middle(LL_Node* head, LL_Node* rear) 
{ 
    if (head == NULL) 
        return NULL; 
  
    struct LL_Node* slow = head; 
    struct LL_Node* fast = head->next; 
  	
  	// "fast" moves one more time than "slow"
    while (fast != rear) 
    { 
        fast = fast->next; 
        if (fast != rear) 
        { 
            slow = slow->next; 
            fast = fast->next; 
        } 
    } 
  
    return slow; 
} 
  
// implementing the Binary Search on singly linked list. search the book according to book name
struct LL_Node* binarySearch(LL_Node *head, string key) 
{ 
    struct LL_Node* start = head; 
    struct LL_Node* last = NULL; 
  
    do
    { 
        // Find middle 
        LL_Node* mid = find_middle(start, last); 
  
        if (mid == NULL)		// whether middle is empty
            return NULL; 
  
        if (mid->book_data.name == key)		// whether value is at middle
            return mid; 
        else if (mid->book_data.name < key) 		// value is more than middle
            start = mid->next; 
        else		// the value is less than middle.
            last = mid; 
  
    } while (last == NULL || start != last); 
  
    // key does not exist 
    return NULL; 
}

// %%%%%%%%%%%%%%%%% End Binary Search %%%%%%%%%%%%%%%%%%%%%



/*	%%%%%%%%%%%%%%%%%%%%%%% Sales Report %%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/


void initialize_Book_Sales(map<string, Book_Sales> &sales_database)
{
	struct Book_Sales temp;		//Temporary storage of information of sales report
	string space;		// get '\n' to avoid mistake;
	string monthSales;		// store monthe_sales temporarily
	
	ifstream input("sales_database.txt");		// Open the file
	
	// Check the existence of file. If it does not exist, create a new one.
	if(input.fail())
	{
		ofstream output("sales_database.txt");
		output.close();
	}
	
	// store all the data into sales_database 
	while(input.peek() != EOF)
	{
		int total = 0;		// Total number of specific books sold in one year
		
		getline(input, temp.ID, ';');
		// the number of sold book each month
		for(int i = 0; i < 12; i++)
		{
			getline(input, monthSales, ';');
			istringstream istr1(monthSales);		// convert string type to int type;
			istr1 >> temp.month_sales[i];
			
			total +=  temp.month_sales[i];		// Calculate total number of specific books sold in one year
		}
		getline(input, space);		// avoid '\n' influncing the input.
		temp.total_sales = total;
		
		sales_database.insert(make_pair(temp.ID, temp));		// push the sales details of this book into sales database
	}
	
	input.close();
}

// output new sales database into sales_database.txt
void update_sales_database(map<string, Book_Sales> sales_database)
{
	ofstream output("sales_database.txt");
	
	map<string, Book_Sales>::iterator mapItr = sales_database.begin();
	while(mapItr != sales_database.end())
	{
		output << (mapItr->second).ID << ";";
		// the number of sold book each month
		for(int i = 0; i < 12; i++)
		{
			output << (mapItr->second).month_sales[i] << ";";
		}
		output << "\n";
		++mapItr;
	}
	
	output.close();
}

void display_sales_report(map<string, Book_Sales> sales_database)
{
	double total_sales_amount = 0.0;
	
	system("cls");
	cout << "\n\n\n\t\t%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Sales Report %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
	cout<< "\n\n\t\tThe Monthly Sales Volume and Annual Sales Volume are shown below";
	cout << "\n\n\t\t-------------------------------------------------------------------------------------------------------------";
	cout << "\n\n\t\t" << left << setw(15) << "Book ID" << setw(7) << "Jan." << setw(7) << "Feb."
			 << setw(7) << "Mar." << setw(7) << "Apr." << setw(7) << "May" << setw(7) << "Jun."
			 << setw(7) << "Jul." << setw(7) << "Aug." << setw(7) << "Sept." << setw(7) << "Oct."
			 << setw(7) << "Nov." << setw(7) << "Dec." << setw(10) << "Annual";
	
	map<string, Book_Sales>::iterator mapItr = sales_database.begin();
	while(mapItr != sales_database.end())
	{
		
		
		int annual = 0;
		cout << "\n\n\t\t" << left << setw(15) << (mapItr->second).ID;
		for(int i = 0; i < 12; i++)
		{
			cout << setw(7) << (mapItr->second).month_sales[i];
			annual += (mapItr->second).month_sales[i];
		}
		cout << setw(10) << annual;
		
		// search the book to get unit price and book name;
		double unit_price = hash_search(book_database, (mapItr->second).ID)->book_data.price;
		
		// calculate total annual sales amount
		total_sales_amount += (annual * unit_price);
		mapItr++;
	}
	cout << "\n\n\t\t-------------------------------------------------------------------------------------------------------------";
	cout << "\n\n\t\tToTal Annual Sales Amount:  RM " << fixed << setprecision(2)  << total_sales_amount;
} 

//	%%%%%%%%%%%%%%%%%%%%%%% End Sales Report %%%%%%%%%%%%%%%%%%%%%%%%%%%%


/*	%%%%%%%%%%%%%%%%%%%%%%% Check Out %%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

void check_out_menu()
{
	bool error = 0;		// check invalid input.
	int choice;
	vector<wish_list> cart;		// create a shopping cart
	
	repeatCheckOut:		// goto loop's label
	
	// Show the Admin menu and detect failed cin command.
	do
	{
		error = 0;
		char title[] = "Check Out Menu";
		
		system("cls");
		cin.clear();
		
		// Display the menu 
		cout << "\n\n\n\t\t";
		for(int i = 0; i < 20; i++)
		{
			delay(30);
			printf("#");
		}
		cout << " ";
		for(int i = 0; i < 14; i++)
		{
			delay(30);
			printf("%c", title[i]);
		}
		cout << " ";
		for(int i = 0; i < 20; i++)
		{
			delay(30);
			printf("#");
		}
		delay(300);
		cout << "\n\n\t\t\t1. Enter the ID to add the book";
		delay(300);
		cout << "\n\n\t\t\t2. Delete the book from cart";
		delay(300);
		cout << "\n\n\t\t\t3. Show the shopping cart";
		delay(300);
		cout << "\n\n\t\t\t4. Check out";
		delay(300);
		cout << "\n\n\t\t\t0. Return to Main Menu";
		delay(300);
		cout << "\n\n\t\t";
		for(int i = 0; i < 60; i++)
		{
			delay(10);
			printf("-");
		}
		cout << "\n\n\n\t\tPlease enter your choice: ";
		cin >> choice;
		
		// Detect failed cin command and invalid input.
		if(cin.fail() || choice > 4 || choice < 0)		// cin.fail() is used to check whether cin command failed
		{
			cout << "\n\n\t\tPlease enter valid choice." << endl;
			cin.clear();
			cin.ignore(80,'\n');
			error = 1;
		}
		cout << "\t\t";
		system("pause");
	}while(error == 1);		// end do-while
	
	switch(choice)
	{
		case 0: main_menu();
				break;
		case 1: {
					add_cart_byID(cart, book_database);
					cout << "\n\n\t\tPlease enter any key to return to Check Out Menue\n\n\t\t";
					system("pause");
					goto repeatCheckOut;
					break;	
				}
			
		case 2: {
					delete_cart_byID(cart);
					cout << "\n\n\t\tPlease enter any key to return to Check Out Menue\n\n\t\t";
					system("pause");
					goto repeatCheckOut;
					break;	
				}
		case 3: {
					show_cart(cart);
					cout << "\n\n\t\tPlease enter any key to return to Check Out Menue\n\n\t\t";
					system("pause");
					goto repeatCheckOut;
					break;
				}
		case 4: {
					check_out(cart,book_database);
					cout << "\n\n\t\tPlease enter any key to return to Check Out Menue\n\n\t\t";
					system("pause");
					goto repeatCheckOut;
					break;
				}
	}
} 

// Add the book into shopping cart searching by ID.
void add_cart_byID(vector<wish_list> &cart, struct Database book_database)
{
	char choice = 'Y';
	char option = 'Y';
	int number = 0;			// the number of books customer wants.
	
	do
	{
		system("cls");
		cin.clear();
		cin.ignore(80,'\n');		// clear '\n', because the '\n' will influence this function.
		
		string key_ID;		// The ID users want to look for.
		
		cout << "\n\n\n\t\t%%%%%%%%%%%%%%%%%%%%%%%% Search by ID %%%%%%%%%%%%%%%%%%%%%%%%";
		cout << "\n\n\t\tPlease enter the ID of the book you want to search for: ";
		getline(cin, key_ID);
		
		struct HT_Node *found_book = hash_search(book_database, key_ID);
		
		if(found_book == NULL)
		{
			cout << "\n\n\t\tSorry, the book does not exist.\n\n\t\t"
				 << "\n\n\t\tDo you want to search other book? (Y/N):";
			cin >> choice;
		}
		else
		{
			printOut_book(found_book->book_data);		// show the details of the book
			cout << "\n\n\t\tDo you want to add this book into shopping cart? (Y/N):";
			cin >> option;
			if(option == 'Y' || option == 'y')
			{
				cout << "\n\n\t\tHow many books do you want: ";
				cin >> number;
				
				if(number > found_book->book_data.quantity)
				{
					cout << "\n\n\t\tSorry! The stock of this book is insufficient.";
					system("pause");
					return;
				}
				
				// create a wishi_list
				struct wish_list newitem;
				newitem.quantity = number;
				newitem.book = found_book->book_data;
				
				// Check if the book has been in the cart
				vector<wish_list>::iterator vecItr = cart.begin();
				while(vecItr != cart.end() && (*vecItr).book.ID != key_ID)
				{
					++vecItr;
				}
				if(vecItr == cart.end())
					cart.push_back(newitem);		// add into cart
				else
				{
					if( ((*vecItr).quantity + number) > found_book->book_data.quantity)
					{
						cout << "\n\n\t\tSorry! The stock of this book is insufficient.";
						system("pause");
						return;
					}
					(*vecItr).quantity += number; 
				}
				cout << "\n\n\t\tThe book have add into cart successfully!";
			}
			else
				return;
			
			cout << "\n\n\t\tDo you want to add other book by ID? (Y/N):";
			cin >> choice;
		}
		// Detect failed cin command and invalid input.
		while(cin.fail() || (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y'))		// cin.fail() is used to check whether cin command failed
		{
			cin.clear();
			cin.ignore(80,'\n');
			cout << "\n\n\t\tPlease enter a valid choice (Y/N): ";
			cin >> choice;
			
		}
	}while(choice == 'Y' || choice == 'y');		// end do-while
}

// delete the book into shopping cart searching by ID.
void delete_cart_byID(vector<wish_list> &cart)
{
	char choice = 'Y';
	char option = 'Y';
	
	do
	{
		system("cls");
		cin.clear();
		cin.ignore(80,'\n');		// clear '\n', because the '\n' will influence this function.
		
		string key_ID;		// The ID users want to look for.
		
		
		cout << "\n\n\n\t\t%%%%%%%%%%%%%%%%%%%%%%%% Search by ID %%%%%%%%%%%%%%%%%%%%%%%%";
		
		if(cart.empty())		// the cart is empty;
		{
			cout << "\n\n\t\tThe shopping cart is empty";
			return;
		}
		cout << "\n\n\t\tPlease enter the ID of the book you want to search for: ";
		getline(cin, key_ID);
		
		
		vector<wish_list>::iterator vecItr = cart.begin();
		while(vecItr != cart.end() && (*vecItr).book.ID != key_ID)
		{
			++vecItr;
		}
		
		if(vecItr == cart.end())
		{
			cout << "\n\n\t\tSorry, the book does not exist.\n\n\t\t"
				 << "\n\n\t\tDo you want to search other book? (Y/N):";
			cin >> choice;
		}
		else
		{
			printOut_book((*vecItr).book);
			cout << "\n\n\t\tDo you want to delete this book from shopping cart? (Y/N):";
			cin >> option;
			if(option == 'Y' || option == 'y')
			{
				cart.erase(vecItr);
				
				cout << "\n\n\t\tThe book have delete from cart successfully!";
			}
			else
				return;
			
			cout << "\n\n\t\tDo you want to delete other book by ID? (Y/N):";
			cin >> choice;
		}
		// Detect failed cin command and invalid input.
		while(cin.fail() || (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y'))		// cin.fail() is used to check whether cin command failed
		{
			cin.clear();
			cin.ignore(80,'\n');
			cout << "\n\n\t\tPlease enter a valid choice (Y/N): ";
			cin >> choice;
			
		}
	}while(choice == 'Y' || choice == 'y');		// end do-while
}


void show_cart(vector<wish_list> &cart)
{
	system("cls");
	cin.clear();
	cout << "\n\n\t\t%%%%%%%%%%%%%%%%%%%%%%%% Shopping Cart %%%%%%%%%%%%%%%%%%%%%%%%";
	
	if(cart.empty())
	{
		cout << "\n\n\t\tThe shopping cart is empty";
		return;
	}
		
	vector<wish_list>::iterator vecItr = cart.begin();
	while(vecItr != cart.end())
	{
		cout << "\n\n\t\t====================================================="
		 << left << setw(30) << "\n\t\tThe details of the book:"
		 << left << setw(30) << "\n\t\t-----------------------------------------------------"
		 << left << setw(30) << "\n\t\tBook ID: " << right << setw(26) << (*vecItr).book.ID 
		 << left << setw(30) << "\n\t\tBook Name: " << right << setw(26) << (*vecItr).book.name
		 << left << setw(30) << "\n\t\tQuntity you want: " << right << setw(26) << (*vecItr).quantity;
		++vecItr;
	}
}



void check_out(vector<wish_list> &cart, struct Database &book_database)
{
	system("cls");
	cin.clear();
	
	double total;		// The total price of all the book user wants
	double cash;		// the money recieved from customer
	
	// display receipt
	cout << "\n\n\t\t%%%%%%%%%%%%%%%%%%%%%%%% Check Out %%%%%%%%%%%%%%%%%%%%%%%%";
	if(cart.empty())		// Check if the shopping cart is empty
	{
		cout << "\n\n\t\tThe shopping cart is empty";
		return;
	}
	cout << "\n\n\t\t" << left << setw(5) << "QTY" << setw(40) << "DESCRIPTION" 
		 << setw(15) << "UNIT PRICE" << setw(15) << "AMOUNT";	 
	cout << "\n\t\t---------------------------------------------------------------------------";
	
	vector<wish_list>::iterator vecItr = cart.begin();
	while(vecItr != cart.end())
	{
		double sum = ((*vecItr).book.price) * ((*vecItr).quantity);		// The sum price of all this books.
		cout << "\n\t\t" << setw(5) << (*vecItr).quantity << setw(40) << (*vecItr).book.name
			 << fixed << setprecision(2) << setw(15) << (*vecItr).book.price  << setw(15) << sum;
		total += sum;		// calculate total amount 
		
		vecItr++;
	}
	cout << "\n\t\t---------------------------------------------------------------------------";
	cout << "\n\n\t\t" << right << setw(55) << "TOTAL:\t" << "RM " 
		 << fixed << setprecision(2) << left << setw(12) << total;
	
	
	cout << "\n\t\t" << right << setw(55) << "Please Enter the Cash:\t" << "RM ";
	cin >> cash;
	
	// the cash should greater than total
	while(cash < total)
	{
		cout << "\n\t\t" << right << setw(55) << "Please Enter the right Cash:\t" << "RM ";
		cin >> cash;
	}
	
	cout << "\n\t\t" << right << setw(55) << "Change:\t" << "RM "
		 << fixed << setprecision(2) << left << setw(12) << (cash - total);
	cout << "\n\t\t---------------------------------------------------------------------------";
	cout << "\n\n\t\tPay successfully!\n\n\t\t";
	
	// Updata the quantity of book in database after payment.
	while(!cart.empty())
	{
		// subtract the number of books which was sold.
		( hash_search(book_database, cart.back().book.ID) )->book_data.quantity -= cart.back().quantity;
	
		// Get data; 
		time_t now = time(0);		// get current time
		struct tm *Itm = localtime(&now);		// get local time
		int q_mon = Itm -> tm_mon;		// get What month it is now. 
		
		// Update the sales volume of this book. 
		map<string,Book_Sales>::iterator mapItr= sales_database.find(cart.back().book.ID);
		// If this book exist in sales database, we just modify it.
		if(mapItr != sales_database.end())
			(mapItr->second).month_sales[Itm->tm_mon] += cart.back().quantity;
		// If this book does not exist in sales database, we create a new item, initialize it, and then insert it into sales database.
		else
		{
			struct Book_Sales temp;
			temp.ID = cart.back().book.ID;
			// the number of sold book each month
			for(int i = 0; i < 12; i++)
			{
				temp.month_sales[i] = 0;
				
				temp.total_sales +=  temp.month_sales[i];		// Calculate total number of specific books sold in one year
			}
			temp.month_sales[Itm->tm_mon] += cart.back().quantity;
			sales_database.insert(make_pair(temp.ID, temp));
		}
		
		// delete the wish_list from cart after updating the database
		cart.pop_back();
	}
	
	// output new sales database into sales_database.txt
	update_sales_database(sales_database);
	
	
	// updata all the information into "book_database.txt" after checking out
	ofstream output("book_database.txt");		// Open the file
	for(int i = 0; i < 401; i++)
	{
		struct HT_Node *current = book_database.ID_hash_table[i]; 
		while( current != NULL)
		{
			output << current->book_data.ID << ";"
				   << current->book_data.name << ";"
				   << current->book_data.author << ";"
				   << current->book_data.category << ";"
				   << current->book_data.publisher << ";"
				   << fixed << setprecision(2) << current->book_data.price << ";"
				   << current->book_data.quantity << ";" << "\n";
			
			current = current->next;
		}
	}
	output.close();
}



//	%%%%%%%%%%%%%%%%%%%%%%%% End Check Out %%%%%%%%%%%%%%%%%%%%%%%%%%






