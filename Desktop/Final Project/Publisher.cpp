#include "Publisher.h"

using namespace std;

Publisher :: Publisher(int _id, string _email, string _username , string _password , int _age)
	:Customer(_id,_email,_username,_password,_age)
{
}

Film *Publisher :: release_film(int _id,string _name,int _year,int _length,int _price,string _summary,string _director)
{
	Film* new_film = new Film(_id,_name,_year,_length,_price,_summary,_director);
	published_films.push_back(new_film);
	return new_film;
}

void Publisher :: accumulate(int amount)
{
	accumulateds.push_back(amount);
}

void Publisher :: get_money_from_network()
{
	for(int i = 0 ; i < accumulateds.size() ; i++)
		all_money = all_money + accumulateds[i];
	accumulateds.clear();
}

void Publisher :: get_published(string name,int min_rate,int min_year,int price,int max_year,string director)
{
	int counter = 1;
	cout << "#. Film Id | Film Name | Film Length | Film Price | Rate | Production Year | Film Director" << endl;
	for(int i = 0 ; i < published_films.size() ; i++)
		if((published_films[i]->get_name() == name || name == "") &&
			(published_films[i]->get_director() == director || director == "") &&
			(published_films[i]->get_price() == price || price == 0) &&
			(published_films[i]->get_year() >= min_year || min_year == 0) &&
		 	(published_films[i]->get_year() <= max_year || max_year == 0) &&
			(published_films[i]->get_mean_rate() >= min_rate || min_rate == 0)
			)
		{
			cout << counter << ". " << published_films[i]->get_id() << "| "<<
				published_films[i]->get_name() << "| "<<
				published_films[i]->get_length() << "| "<<
				published_films[i]->get_price() << "| "<<
				published_films[i]->get_mean_rate() << "| "<<
				published_films[i]->get_year() << "| "<<
				published_films[i]->get_director() << "| "<<endl;
			counter++;
		}
}

int Publisher :: min_index(int i)
{
    if (i == customers.size() - 1)
        return i;
    int min_idx_rest = min_index(i + 1);
    if (customers[i]->get_id() < customers[min_idx_rest]->get_id())
        return i;
    else
        return min_idx_rest;
}

void Publisher :: sort_followers(int i)
{
    if (i == customers.size())
        return;
    int j = min_index(i);
    Customer* temp = customers[i];
    customers[i] = customers[j];
    customers[j] = temp;
    sort_followers(i + 1);    
}

void Publisher :: show_followers()
{
	sort_followers(0);
	cout << "List of Followes\n#. User Id | User Username | User Email" << endl;
	for(int i = 0 ; i < customers.size() ; i++)
	{
		cout << i+1 << ". " << customers[i]->get_id() << " | " <<
			customers[i]->get_username() << " | " <<
			customers[i]->get_email() << " | " << endl;
	}
}

void Publisher :: add_customer(Customer* customer)
{
	customers.push_back(customer);
}

int Publisher :: get_id_publishedfilm(int index)
{
	return published_films[index] -> get_id();
}

string Publisher :: get_name_publishedfilm(int index)
{
	return published_films[index] -> get_name();
}

int Publisher :: get_size_publishedfilms()
{
	return published_films.size();
}

int Publisher :: get_mean_rate_publishedfilm(int index)
{
	return published_films[index]->get_mean_rate();
}

int Publisher :: get_price_publishedfilm(int index)
{
	return published_films[index]->get_price();
}

void Publisher :: add_comment_publishedfilm(int index,std :: string content,int user_id)
{
	published_films[index]->add_comment(content,user_id);
}

int Publisher :: get_size_publishedfilm_comments(int index)
{
	return published_films[index]->get_size_comments();
}

int Publisher :: get_id_publishedfilm_comment(int findex,int cindex)
{
	return published_films[findex]->get_id_comment(cindex);
}

void Publisher :: delete_publishedfilm_comment(int findex,int cindex)
{
	published_films[findex]->delete_comment(cindex);
}

void Publisher :: add_score_to_published(int index,int score)
{
	published_films[index]->add_score(score);
}

void Publisher :: romove_from_pubfilms(int index)
{
	published_films.erase(published_films.begin() + index);
}
