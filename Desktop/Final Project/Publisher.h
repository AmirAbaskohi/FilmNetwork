#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "Customer.h"

class Publisher : public Customer
{
public:
	Publisher(int _id,std :: string _email,std :: string _username , std :: string _password , int _age);
	Film* release_film(int _id,std :: string _name,int _year,int _length,int _price,std :: string _summary,std :: string _director);
  void accumulate(int amount);
  void get_money_from_network();
  void get_published(std :: string name,int min_rate,int min_year,int price,int max_year,std :: string director);
  void show_followers();
  void add_customer(Customer* customer);
  int get_id_publishedfilm(int index);
  std :: string get_name_publishedfilm(int index);
  int get_mean_rate_publishedfilm(int index);
  int get_price_publishedfilm(int index);
  void add_comment_publishedfilm(int index,std :: string content,int user_id);
  int get_size_publishedfilms();
  int get_size_publishedfilm_comments(int index);
  int get_id_publishedfilm_comment(int findex,int cindex);
  void delete_publishedfilm_comment(int findex,int cindex);
  void add_score_to_published(int index,int score);
  void remove_from_pubfilms(int index);
  int min_index(int i);
  void sort_followers(int i);
  void romove_from_pubfilms(int index);
  void increase_film_bought(int index);
  std :: vector<Customer*>customers;
  std :: vector<Film*>published_films;
protected:
  std :: vector <int> accumulateds;
};

#endif
