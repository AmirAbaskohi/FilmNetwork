#include "Customer.h"

using namespace std;

Customer :: Customer(int _id, string _email, string _username , string _password , int _age)
{
	id = _id;
	email = _email;
	username = _username;
	password = _password;
	age = _age;
	all_money = 0;
}

void Customer :: follow_publisher(Customer* publisher)
{
	publishers.push_back(publisher);
}

void Customer :: charge(int amount)
{
	all_money = all_money + amount;
}

void Customer :: buy(int amount)
{
	all_money = all_money - amount;
}

int Customer :: get_id()
{
	return id;
}

string Customer :: get_username()
{
	return username;
}

void Customer :: show_unread_notifications()
{
	cout << "#. Notification Message" << endl ;
	for(int i = unread_notifications.size()-1 ; i >= 0 ; i--)
		cout << unread_notifications.size()-i << ". "<<unread_notifications[i] << endl;
	for(int i = 0 ; i < unread_notifications.size() ; i++)
		read_notifications.push_back(unread_notifications[i]);
	unread_notifications.clear();
}

void Customer :: show_read_notifications(int limit)
{
	cout << "#. Notification Message" << endl ;
	for(int i = 0 ; i < limit ; i++)
		cout << i+1 << ". "<<read_notifications[read_notifications.size() - i -1] << endl;
}

void Customer :: add_notification(std :: string content)
{
	unread_notifications.push_back(content);
}

void Customer :: add_publisher(Customer* customer)
{
	publishers.push_back(customer);
}

void Customer :: romove_from_films(int index)
{
	films.erase(films.begin() + index);
}

int Customer :: get_id_film(int index)
{
	return films[index]->get_id();
}

int Customer :: get_size_films()
{
	return films.size();
}

Film* Customer :: get_film(int index)
{
	return films[index];
}

string Customer :: get_name_film(int index)
{
	return films[index]->get_name();
}
string Customer :: get_director_film(int index)
{
	return films[index]->get_director();
}
int Customer :: get_price_film(int index)
{
	return films[index]->get_price();
}
int Customer :: get_year_film(int index)
{
	return films[index]->get_year();
}
int Customer :: get_length_film(int index)
{
	return films[index]->get_length();
}
int Customer :: get_mean_rate_film(int index)
{
	return films[index]->get_mean_rate();
}

string Customer :: get_password()
{
	return password;
}

string Customer :: get_email()
{
	return email;
}