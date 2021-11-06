#include<iostream>
#include<string>
#include <iomanip>
#include<cstring>

using namespace std;


struct menuitem //defintion of a struct to store data about resturant
{
       string menulist;
       double price;
};
menuitem menu[10]; //Instance of a struct to store data of 7 resturant items
void input(char& status,int& time,string& name,string& email,string& date);
void getdata(); //prototype of a function to loads data about the items in struct
void showdata(); // prototype of a function show the loaded data
void selectItems(); //prototype of a function  to select the items
void cal(string& name,string& email,double& due); //prototype of a function to calculate the bill
int c[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

int main()
{
	   string name, email, date, num;
	   char status;
	   int time;
	   double t, due;
	   cout << "Welcome to Joint Cafe!" << endl;
       input (status, time, name, email, date);
       getdata(); //calling of a function to get load the data
       showdata();//calling of a function to display data
       selectItems(); //calling of a function select the items from the menu
       cal(name, email, due); //calling of a function to calculate the bill
    
       //system("pause");
       return 0;

}

void input(char& status,int& time,string& name,string& email,string& date)
{
	string num;
    string add;
	cout<<"Take away(T) or Dine-in (D) ? : ";
	cin>>status;
	cout<<endl;
	
	if(status=='T')
	{
	cout<<"Enter name: ";
	cin>>name;
	cout<<endl;
	cout<<"Enter your number phone: ";
	cin>>num;	
	cout<<endl;
	cout<<"Enter your address: ";
	cin>>add;
	cout<<endl;
	cout<<"Enter email: ";
	cin>>email;
	}
	
	else if (status=='D')
	{
	cout<<"Enter first name: ";
	cin>>name;
	cout<<endl;
	cout<<"Enter date(dd/mm):";
	cin>>date;
	cout<<endl;
	cout<<"Enter your number phone: ";
	cin>>num;
	cout<<endl;
	cout<<"Enter email: ";
	cin>>email;
	cout<<endl;
	cout<<"What time you would like to pick up your order?(in 24 hours) :";
	cin>>time;
	cout<<endl;
	cout<<endl;
	}
	
}

	
void getdata() //a function to get load the data

{
       menu[1].menulist = "Nasi Lemak";
       menu[1].price = 4.00;
       menu[2].menulist = "White Rice and Butter Chicken";
       menu[2].price = 6.00;
       menu[3].menulist = "White Rice and Soy Chicken";
       menu[3].price = 6.00;
       menu[4].menulist = "White Rice and Sweet & Sour Fish";
       menu[4].price = 6.00;
       menu[5].menulist = "Chicken Chop";
       menu[5].price = 7.00;
       menu[6].menulist = "Chicken Fried Rice";
       menu[6].price = 6.00;
       menu[7].menulist = "Mushroom Swiss Beef";
       menu[7].price = 7.00;
       menu[8].menulist = "Sky Juice";
       menu[8].price = 1.00;
       menu[9].menulist = "Coke";
       menu[9].price = 2.00;


}
void showdata() //a function to display menu
{
       cout << "Items offered by the restaurant are: " << endl;
       cout << 1 << "\t" << menu[1].menulist << setw(29) << "RM " << menu[1].price << endl;
       cout << 2 << "\t" << menu[2].menulist << setw(10) << "RM " << menu[2].price << endl;
       cout << 3 << "\t" << menu[3].menulist << setw(13) << "RM " << menu[3].price << endl;
       cout << 4 << "\t" << menu[4].menulist << setw(7) << "RM " << menu[4].price << endl;
       cout << 5 << "\t" << menu[5].menulist << setw(27) << "RM " << menu[5].price << endl;
       cout << 6 << "\t" << menu[6].menulist << setw(21) << "RM " << menu[6].price << endl;
       cout << 7 << "\t" << menu[7].menulist << setw(20) << "RM " << menu[7].price << endl;
       cout << 8 << "\t" << menu[8].menulist << setw(30) << "RM " << menu[8].price << endl;
       cout << 9 << "\t" << menu[9].menulist << setw(35) << "RM " << menu[9].price << endl;
       cout << endl;


}
void selectItems() //function select the items from the menu
{
       int ch,quantity;
       char con;
       do{
              cout << "Enter your choice :";
              cin >> ch; //takes the choice from the user to select the item
              cout << "Enter the Quantity :";
              cin >> quantity;
              switch (ch)
              {
              case 1:
              {
                     c[1] = c[1] + quantity;
                     cout << "You have Selected :" << menu[1].menulist << endl;

                     break;
              }
              case 2:
              {
                     c[2] = c[2] + quantity;
                     cout << "You have Selected :" << menu[2].menulist << endl;

                     break;
              }
              case 3:
              {
                     c[3] = c[3] + quantity;
                     cout << "You have Selected :" << menu[3].menulist << endl;

                     break;
              }
              case 4:
              {
                     c[4] = c[4] + quantity;
                     cout << "You have Selected :" << menu[4].menulist << endl;

                     break;
              }
              case 5:
              {
                     c[5] = c[5] + quantity;
                     cout << "You have Selected :" << menu[5].menulist << endl;

                     break;
              }
              case 6:
              {
                     c[6] = c[6] + quantity;
                     cout << "You have Selected :" << menu[6].menulist << endl;

                     break;
              }
              case 7:
              {
                     c[7] = c[7] + quantity;
                     cout << "You have Selected :" << menu[7].menulist << endl;


                     break;
              }
              case 8:
              {
                     c[8] = c[8] + quantity;
                     cout << "You have Selected :" << menu[8].menulist << endl;

                     break;
              }
              case 9:
              {
                     c[9] = c[9] + quantity;
                     cout << "You have Selected :" << menu[9].menulist << endl;


                     break;
              }
              default:
                     cout << "Invalid input" << endl;
              }
              cout << endl;
              cout << "To select more items, press Y (Yes) or N (No): ";
              cin >> con;


       } while (con != 'N');
       cout << endl;
}

	
void cal(string& name,string& email,double& due)
{
    double total = 0, tax,due1;
	int time;
	
       
       cout << "------Welcome to Joint Cafe!-----" << endl;
       for (int i = 1; i < 10; i++)
       {
              if (c[i] > 0)
              {
                     cout << c[i] << "\t" << menu[i].menulist << setw (5) << "   RM " << menu[i].price << endl;
                     total = total + (menu[i].price*c[i]);
              }

       }
       tax = total*0.06; //calculate the tax on the total price
       due = total + tax; //calculate the price after adding tax
       if (due>=100){
    	cout<<"PROMOTION : Discount of RM20 is deducted from bill";
       	due1=due-20;
       	cout << endl;
       cout << "        Tax " << "\t" << "RM " << tax << endl;
       	cout <<"        Total : " << " RM" << due<<endl;
       cout << "-----------------------------------------------" << endl;
       cout << "Amount due      RM " << due1<< endl;
       cout << "-----------------------------------------------" << endl;
	   }
	   
	   else if (due >=50){
	   	cout<<"PROMOTION: Discount of RM10 is deducted from bill";
       	due1=due-10;
       	cout << endl;
       cout << "        Tax " << "\t" << "RM " << tax << endl;
       	cout <<"        Total : " << " RM" << endl<<due;
       cout << "-----------------------------------------------" << endl;
       cout << "Amount due      RM " << due1<< endl;
       cout << "-----------------------------------------------" << endl;
	   	
	   }
	   
	   else if (due<=50){
	   	
       cout << endl;
       cout << "        Tax " << "\t" << "RM " << tax << endl;
       	cout <<"        Total : " << " RM" << endl<<due;
       cout << "-----------------------------------------------" << endl;
       cout << "Amount due      RM " << due<< endl;
       cout << "-----------------------------------------------" << endl;
	   }
 
       

	
	
		cout << endl<<endl;
		cout << "Thank you for choosing us Mr/Miss " << name << endl;
		cout << "Your order detail has been sent to: " << email << endl;
	
	
       
       
    
}


	
	





