//A programme of the Joint Cafe!!
#include<iostream>
#include<string>
#include<iomanip>
#include<cstring>
#include<fstream>
#include<conio.h>//to allow the ch=_getch() function

using namespace std;//are going to use classes or functions(if any) so no need to explicitly call the namespace to accedd them


struct menuitem //defintion of a struct to store data about resturant
{
       string menulist; 
       double price;
};
menuitem menu[10]; //Instance of a struct to store data of 7 resturant items
void calcIncome(double jumlah, double jwp);//prototype of a function to calculate the total income in admin
void readData(string& date,string& name,double &dee);//prototype of a function that read the customer's information
void input(char& status,string& time,string& name,string& email,string& date,int& pax);//prototype of a function to get the customer's information
void getdata(); //prototype of a function to loads data about the items in struct
void showdata(); // prototype of a function show the loaded data
void selectItems(); //prototype of a function  to select the items
void cal(string& name,string& email,double& due,char& status, double &dee); //prototype of a function to calculate the bill
void writeData(double &dee, double &ttl, double jumlah);//prototype of a function to keep the customer's amount due to a file
void Data1(string& date,string& name,double &dee);//prototype of a function to keep the customer's information to a file
int c[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; 

int main()
{

	long userId; //for user id of administrator  
	char ch;                                                                                                                                                                                                                                                                                                                                                                                                                 string pwd="wordpass";  //password
	string pass="";//the password is hidden.....
	int intro;//for user to choose the next step
	double ttl, jumlah, jwp;//for calcualation of income
	string date, name;	
	double dee;
	system("COLOR 3");//to make all the outputs become blue in colour
	cout << "-------------------------------------------------------------------------"<< endl;
	cout << "-------------------------------------------------------------------------"<< endl << endl;
	cout << "\t \t Welcome to Joint cafe!" << endl;
	cout << "\n-------------------------------------------------------------------------";
	cout << "\n-------------------------------------------------------------------------"<< endl << endl;
	
	cout << "\t 1. \t Administration Section" << endl;
	cout << "\t 2. \t Customer Section" << endl;
	cout << "\t 3. \t Exit" << endl;
	cout << "Please enter your choice: ";
	cin >> intro;//for user to choose either they are the admin, customer or just exit.
	
	system ("CLS");//to make the screen clear directly
	if (intro==1)//as the user is an admin
	{
	cout << "-------------------------------------------------------------------------"<< endl << endl;
	cout << "\t\tJoint cafe Administration Section" << endl;
	cout << "\n-------------------------------------------------------------------------"<< endl << endl;
	system ("CLS");//to make the screen clear directly
	cout<<"\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t---------------------";
	cout<<"\n\t\t\t\t\t\t\tEnter Login Id = ";
	cin>>userId;//for user to enter the right Id
	cout<<"\t\t\t\t\t\t\t---------------------";
	
	if(userId==3005)//If the Id entered is true 
	{

	cout<<"\n\n\n\t\t\t\t\t\t\tHello Admin,\n";
	cout<<"\n\n\n\t\t\t\t\t\t\tPassword = "; 
	ch=_getch();//reads the keystroke, saves it to the ch but does not display it on the console
	while(ch!=13){//to continue reading keystrokes from the screen until the user press Enter
	pass.push_back(ch);//to puts the character specified as parameter at the end of the string
	cout<<'*'; //for printing * instead for password
	ch=_getch();//read another keystroke to continue reading keystrokes from the user
	}
    if(pass==pwd)//If the password is true
    {
    cout<<"\n\n\t\t\tAccess Granted. Welcome to our system\n\n\n";
    system("PAUSE");//to make the screen wait for a key press
    system("CLS");//to make the screen clear directly
	calcIncome(jumlah,jwp);//to direct to the function for calculating total income
	readData(date, name, dee);//to direct to the function that read the customer's information
    system("PAUSE");//to make the screen wait for a key press
	return 0;
}
else 
cout<<"\nAcess aborted.\nSorry, but you not an Admin since you get the password wrong."<<endl;	
    system("PAUSE");//to make the screen wait for a key press
    system("CLS");//to make the screen clear directly
cout<<"\n\n\t\t\t Goodbye!"<<endl;
cout << "\t\t\tHave a nice day!" << endl;
}
else
cout<<"\nSorry, but you not an Admin since you not know the ID."<<endl;
    system("PAUSE");//to make the screen wait for a key press
    system("CLS");//to make the screen clear directly
cout<<"\n\n\t\t\t Goodbye!"<<endl;
cout << "\t\t\tHave a nice day!" << endl;
}	

	else if (intro==2)//as the user is a customer
	{
	   string name, email, date, num,time;//as the input to get the customer's information
	   char status;//as an input to get either the customer wants to dine-in or take away
	   double t, due, dee;//as the input to get the amount due
	   int pax;//as the input to get the customer's pax
	   cout<<endl;
	   cout << "\t\t\t\t\t\tWelcome to Joint Cafe!" << endl;
	   cout << "\tWE HAVE SUCH A GREAT PROMOTION FOR YOU!!!!!"<<endl;
	   cout << "FOR EVERY RM50 AND ABOVE, YOU WILL GET RM10 DISCOUNT!!!" << endl;
	   cout << "\t\tBUT MOST IMPORTANTLY....."<<endl;
	   cout << "RM20 DISCOUNT FOR THOSE WHO SPEND MORE THAN RM100 IN OUR CAFE!!!!!!!!"<<endl;
	   cout << "SO, WHAT ARE YOU WAITING FOR? HURRY UP MAKE A CHOOSE!!!"<<endl;
       input (status, time, name, email, date,pax);//calling of a function to get the customer's information 
       getdata(); //calling of a function to get load the data
       showdata();//calling of a function to display data
       selectItems(); //calling of a function select the items from the menu
       cal(name, email, due,status,dee); //calling of a function to calculate the bill
	   writeData(dee, ttl, jumlah);//calling of a function to keep the customer's amount due to a file
	   Data1(date, name, dee);//calling a function to keep the customer's information to a file
    
       //system("pause");
       return 0;

}
}


void input(char& status,string& time,string& name,string& email,string& date,int&pax)//a function to get the customer's information
{
	
	int table=5;//to start with the table only have 5
	int chair=20;//to start with the chair only have 20
	string num,street,city,postcode,state;//as the input to get the customer phone number and address
    cout<<endl;
	cout<<"Take away(T) or Dine-in (D) ? : "<<endl <<endl;
	cout<<"#Take away means delivery"<<endl;
	cout<<"#Deliverycharge is only RM7!"<<endl<< endl;
	cout<<"Please enter your choose ";
	cin>>status;//for user to enter either they want to take away or dine-in
	cout<<endl;
	system("cls");//to make the screen clear directly
	if(status=='T')//as the customer wants to take away
	{
	cout<<"[Take-away]"<<endl<<endl;
	cout<<"Enter first name: ";
	cin>>name;//for user to enter the name
	cout<<endl;
	cout<<"Enter your number phone: ";
	cin>>num;//for user to enter the phone number
	cout<<endl;
	cout<<"Enter your address: "<<endl;
	cout<<"Street address : ";
    cin>>street;//for user to enter the street
	cout<<"city : ";
	cin>>city;//for user to enter the city
	cout<<"State : ";
	cin>>state;//for user to enter the state
	cout<<"Postcode : ";
	cin>>postcode;//for user to enter the postcode
	cout<<endl;
	cout<<"Enter email: ";
	cin>>email;//for user to enter the email
	}
	
	else if (status=='D')//as the customer wants to dine in
	{
	cout<<"[Dine-in]"<<endl<<endl;
	cout<<"Enter first name: ";
	cin>>name;//for user to enter the name
	cout<<endl;
	cout<<"Enter date(dd/mm):";
	cin>>date;//for user to enter the date that they want to dine in
	cout<<endl;
	cout<<"Enter your number phone: ";
	cin>>num;//for user to enter the phone number
	cout<<endl;
	cout<<"Enter email: ";
	cin>>email;//for user to enter the email
	cout<<endl;
	cout<<"What time you would like to come?(in 24 hours) :";
	cin>>time;//for user to enter the time
	cout<<endl;
	cout<<"Number of pax = ";
	cin>>pax;//for user to enter the pax of customer
	{
		if(pax<=4){//if pax less than or equal to 4
		cout<<"Your table is number 1"<<endl;
		--table;//to reduce the amount table that left
		chair=chair-pax;//to reduce the amount chair that left
	}
	else if(pax>=5){//if pax more than or equal to 5
		if(pax%4==0){//if the pax entered was even
			if(pax==8)//if pax is equal to 8
			cout<<"Your table are table 1 and table 2"<<endl;//the customer will provided with 2 tables
			else if (pax==12)//if pax is equal to 12
			cout<<"Your table are table 1, table 2 and table 3"<<endl;//the customer will provided with 3 tables
			else if (pax==16)//if pax is equal to 16
			cout<<"Your table are table 1, table 2, table 3 and table 4"<<endl;//the customer will provided with 4 tables
			else if (pax==20)//if pax is equal to 20
			cout<<"Your table are table 1, table 2, table 3, table 3, table 4 and table 5"<<endl;//the customer will provided with 5 tables
	
			table=table-(pax/4);//to reduce the amount table that left
			chair=chair-pax;}//to reduce the amount chair that left
		else if(pax%4!=0){//if the pax entered was odd
			if(pax>4&&pax<=8)//if pax is equal to 8
			cout<<"Your table are table 1 and table 2"<<endl;
			else if (pax>8&&pax<=12)//if pax is equal to 12
			cout<<"Your table are table 1, table 2 and table 3"<<endl;
			else if (pax>12&&pax<=16)//if pax is equal to 16
			cout<<"Your table are table 1, table 2, table 3 and table 4"<<endl;
			else if (pax>16&&pax<=20)//if pax is equal to 20
			cout<<"Your table are table 1, table 2, table 3, table 3, table 4 and table 5"<<endl;
			
			table=table-(pax/4)-1;//to reduce the amount table that left
			chair=chair-pax;//to reduce the amount chair that left
		}
	}
	}
}

	
	cout<<"Number of Table available:\t"<<table<<"\n"<<"Number of Chair available:\t"<<chair<<endl;
	
	if(table<=0)
	{
	cout<<"Table full" << endl;
	system("PAUSE");//to make the screen wait for a key press
	}
	
	cout<<endl;
	cout<<endl;
}
	
void getdata() //a function to get load the data

{	
       menu[1].menulist = "Nasi Lemak";//first menu
       menu[1].price = 4.00;//first menu's price
       menu[2].menulist = "White Rice and Butter Chicken";//second menu
       menu[2].price = 6.00;//secone menu's price
       menu[3].menulist = "White Rice and Soy Chicken";//third menu
       menu[3].price = 6.00;//third menu's price
       menu[4].menulist = "White Rice and Sweet & Sour Fish";//fourth menu
       menu[4].price = 6.00;//fourth menu's price
       menu[5].menulist = "Chicken Chop";//fifth menu
       menu[5].price = 7.00;//fifth menu's price
       menu[6].menulist = "Chicken Fried Rice";//sixth menu
       menu[6].price = 6.00;//sixth menu's price
       menu[7].menulist = "Mushroom Swiss Beef";//seventh menu
       menu[7].price = 7.00;//seventh menu's price
       menu[8].menulist = "Sky Juice";//first drink
       menu[8].price = 1.00;//first drink's price
       menu[9].menulist = "Coke";//second drink
       menu[9].price = 2.00;//second drink's price


}
void showdata() //a function to display menu
{

       cout << "Items offered by the restaurant are: " << endl;
       cout << 1 << "\t" << menu[1].menulist << setw(29) << "RM " << menu[1].price << endl;//to display the first menu with price
       cout << 2 << "\t" << menu[2].menulist << setw(10) << "RM " << menu[2].price << endl;//to display the second menu with price
       cout << 3 << "\t" << menu[3].menulist << setw(13) << "RM " << menu[3].price << endl;//to display the third menu with price 
       cout << 4 << "\t" << menu[4].menulist << setw(7) << "RM " << menu[4].price << endl;//to display the fourth menu with price
       cout << 5 << "\t" << menu[5].menulist << setw(27) << "RM " << menu[5].price << endl;//to display the fifth menu with price
       cout << 6 << "\t" << menu[6].menulist << setw(21) << "RM " << menu[6].price << endl;//to display the sixth menu with price
       cout << 7 << "\t" << menu[7].menulist << setw(20) << "RM " << menu[7].price << endl;//to display the seventh menu with price
       cout << 8 << "\t" << menu[8].menulist << setw(30) << "RM " << menu[8].price << endl;//to display the first drink with price
       cout << 9 << "\t" << menu[9].menulist << setw(35) << "RM " << menu[9].price << endl;//to display the second drink with price
       cout << endl;


}
void selectItems() //function select the items from the menu
{
       int ch,quantity;//as the input to get the choice and its amount from customer
       char con;//as the input for the customer to make more order or not
       do{
              cout << "Enter your choice :";
              cin >> ch; //takes the choice from the user to select the item
              cout << "Enter the Quantity :";
              cin >> quantity;//to get the amount of selected item
              switch (ch)//to separate the menu in the loop
              {
              case 1://as if the customer wants the first menu
              {
                     c[1] = c[1] + quantity;
                     cout << "You have Selected :" << menu[1].menulist << endl;

                     break;//to terminate the loop
              }
              case 2://as if the customer wants the second menu
              {
                     c[2] = c[2] + quantity;
                     cout << "You have Selected :" << menu[2].menulist << endl;

                     break;//to terminate the loop
              }
              case 3://as if the customer wants the third menu
              {
                     c[3] = c[3] + quantity;
                     cout << "You have Selected :" << menu[3].menulist << endl;

                     break;//to terminate the loop
              }
              case 4://as if the customer wants the fourth menu
              {
                     c[4] = c[4] + quantity;
                     cout << "You have Selected :" << menu[4].menulist << endl;

                     break;//to terminate the loop
              }
              case 5://as if the customer wants the fifth menu
              {
                     c[5] = c[5] + quantity;
                     cout << "You have Selected :" << menu[5].menulist << endl;

                     break;//to terminate the loop
              }
              case 6://as if the customer wants the sixth menu
              {
                     c[6] = c[6] + quantity;
                     cout << "You have Selected :" << menu[6].menulist << endl;

                     break;//to terminate the loop
              }
              case 7://as if the customer wants the seventh menu
              {
                     c[7] = c[7] + quantity;
                     cout << "You have Selected :" << menu[7].menulist << endl;


                     break;//to terminate the loop
              }
              case 8://as if the customer wants the first drink
              {
                     c[8] = c[8] + quantity;
                     cout << "You have Selected :" << menu[8].menulist << endl;

                     break;//to terminate the loop
              }
              case 9://as if the customer wants the second drink
              {
                     c[9] = c[9] + quantity;
                     cout << "You have Selected :" << menu[9].menulist << endl;


                     break;//to terminate the loop
              }
              default://if the user input wrong number
                     cout << "Invalid input" << endl;
              }
              //break jumps here
              cout << endl;
              cout << "To select more items, press Y (Yes) or N (No): ";
              cin >> con;//for the customer to choose to get more order or not


       } while (con != 'N');//as if the customer want more order, the switch loop repeated.
       cout << endl;
       system ("CLS");//to make the screen clear directly
}

	
void cal(string& name,string& email,double& due,char& status,double &dee)//a function to calculate the bill
{

    double total = 0, tax,due1;//as the input to get the bills
	int time;//as the input to get the time from user
	
       
       cout << "------Welcome to Joint Cafe!-----" << endl;
       for (int i = 1; i < 10; i++)
       {
              if (c[i] > 0)
              {
                     cout <<menu[i].menulist << setw (5) << "   RM " << menu[i].price <<"X"<<c[i] <<endl;
                     total = total + (menu[i].price*c[i]);
              }

       }
       
       if(status=='D')//as the user wants to dine-in
       {
       tax = total*0.06; //calculate the tax on the total price
       due = total + tax; //calculate the price after adding tax
       if (due>=100){//if spend more than RM100
    	cout<<"PROMOTION : Discount of RM20 is deducted from bill";
       	due1=due-20;//calculate the price after discount
       	cout << endl;
       cout << "        Tax " << "\t" << "RM " << tax << endl;
       	cout <<"        Total : " << " RM" << due<<endl;
       cout << "-----------------------------------------------" << endl;
       dee=due1;//to make all the output(amount due) in the same name
       cout << "Amount due      RM " << dee<< endl;
       cout << "-----------------------------------------------" << endl;
	   }
	   
	   else if (due >=50){//if spend more than RM50 until RM99.99
	   	cout<<"PROMOTION: Discount of RM10 is deducted from bill";
       	due1=due-10;//calculate the price after discount
       	cout << endl;
       cout << "        Tax " << "\t" << "RM " << tax << endl;
       	cout <<"        Total : " << " RM" << due<<endl;
       cout << "-----------------------------------------------" << endl;
       dee=due1;//to make all the output(amount due) in the same name
       cout << "Amount due      RM " << dee<< endl;
       cout << "-----------------------------------------------" << endl;
	   	
	   }
	   
	   else if (due<=50){//if spend less than RM50
	   	
       cout << endl;
       cout << "        Tax " << "\t" << "RM " << tax << endl;
       	cout <<"        Total : " << " RM" <<due<<endl;
       cout << "-----------------------------------------------" << endl;
       dee=due;//to make all the output(amount due) in the same name
       cout << "Amount due      RM " << dee<< endl;
       cout << "-----------------------------------------------" << endl;
	   }
   	   }
   	   
   	   else if(status=='T')//as the user wants to take away
   	   {
		tax = total*0.06; //calculate the tax on the total price
        due = total + tax + 7; //calculate the price after adding tax and delivery
        if (due>=100){//if spend more than RM100
     	cout<<"PROMOTION : Discount of RM20 is deducted from bill";
       	due1=due-20;//calculate the price after discount
       	cout << endl;
		cout << "        Tax " << "\t" << "RM " << tax << endl;
		cout << "        Delivery Charge"<<"\t"<<"RM"<<7<<endl;
       	cout <<"        Total : " << " RM" << due<<endl;
       cout << "-----------------------------------------------" << endl;
       dee=due1;//to make all the output(amount due) in the same name
       cout << "Amount due      RM " << dee<< endl;
       cout << "-----------------------------------------------" << endl;
	   }
	   
	   else if (due >=50){//if spend more than RM50 until RM99.99
	   	cout<<"PROMOTION: Discount of RM10 is deducted from bill";
       	due1=due-10;//calculate the price after discount
       	cout << endl;
       cout << "        Tax " << "\t" << "RM " << tax << endl;
       	cout << "       Delivery Charge"<<"\t"<<"RM"<<7<<endl;
       	cout <<"        Total : " << " RM" << due<<endl;
       cout << "-----------------------------------------------" << endl;
       dee=due1;//to make all the output(amount due) in the same name
       cout << "Amount due      RM " << dee<< endl;
       cout << "-----------------------------------------------" << endl;
	   	
	   }
	   
	   else if (due<=50){//if spend less than RM50
	   	
       cout << endl;
       cout << "        Tax " << "\t" << "RM " << tax << endl;
   		cout << "        Delivery Charge"<<"\t"<<"RM"<<7<<endl;
       	cout <<"        Total : " << " RM" << due<<endl;
       cout << "-----------------------------------------------" << endl;
       dee=due;//to make all the output(amount due) in the same name
       cout << "Amount due      RM " << dee<< endl;
       cout << "-----------------------------------------------" << endl;
	   }
		}
		cout << endl<<endl;
		cout << "Thank you for choosing us Mr/Miss " << name << endl;//to thanks the user for choosing our cafe
		cout << "Your order detail has been sent to: " << email << endl;//to reminds the customer that the detail order has been sent to their email
		cout << "Total is: " << " RM" << dee;//to portrait the total amount that customer needs to pay
	
}


void writeData(double &dee, double &ttl, double jumlah)//a function to keep the customer's amount due to a file
{
	ofstream output;//to declare object
	
	output.open("total.txt",ios::app);//to create a file
	ttl += dee;//to sum up all the amount dee from customer
	jumlah = ttl/2;//to gain the incomes,We are taking 100% profits,which means our modal is half of the exact menu price.
	output << jumlah << endl;//to put in the data in the file
	output.close();//to close file
}

void Data1(string& date,string& name,double &dee)//a function to keep the customer's information to a file
{
	ofstream output;//to declare object
	
	output.open("desc.txt",ios::app);//to create a file
	output << date << "\t "<<  name << "\t " << dee << endl;//to put in the data in the file
	output.close();//to close file
}

void calcIncome(double jumlah,double jwp)//a function to calculate the total income
{
	ifstream input;//to declare object
	
	input.open("total.txt", ios::in);//to open the file	
    string line;//as the input to get the line in the file
	int counter=0;//as the input to get the amount of line in the file
	
	ifstream file("total.txt");//to read the input(line) in the file
		while(getline(file, line))//to create a loop to get the amount of line in the file
		{
				++counter;//to get the total line in the file
		}
	
	for(int i=0; i<counter;i++)//to create a loop to get the income
	{
	input >> jumlah;//to take out the data in the file
	jwp += jumlah;//to sum up all the profits from every customer amount due
}
	cout << endl;
	cout << "Total income" << " RM" << jwp << endl << endl;//to print out the total income
	cout << "We are taking 100% profits,which means our modal is half of the exact menu price";

	input.close();//to close the file
}

void readData(string& date,string& name,double &dee)
{
	string lines;
	ifstream input;
	cout << endl << endl;
	cout << "Customer History Bills" << endl << endl;
	cout << "Date \t Name \t Amount Due" << endl;
	input.open("desc.txt");
	if (input.is_open())
	{
		while ( getline (input, lines))
		{
			cout << lines << endl;
		}
	}
	
	input.close();
}

