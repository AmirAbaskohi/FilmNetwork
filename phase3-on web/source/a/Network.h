#ifndef NETWORK_H
#define NETWORK_H

#include <sstream>
#include <algorithm>
#include <iostream>
#include "Film.h"
#include "Publisher.h"
#include "Customer.h"
#include "Exception.h"
#include "Sha256.h"

#define POST "POST"
#define GET "GET"

class Network
{
public:
  Network();
  bool signup(std :: string email,std :: string username,std :: string password,std :: string age,bool is_publisher);
  bool login(std :: string username,std :: string password);
  void release_film(std :: string _name,int _year,int _length,int _price,std :: string _summary,std :: string _director);
  void follow_a_publisher(int _id);
  void rate_a_film(int _id,int score);
  void buy_film(int _id);
  void comment_film(int _id,std :: string _content,int user_id);
  void edit_film(std :: vector <std :: string> words,int film_id);
  void delete_comment(int film_id , int comment_id);
  void delete_film(int film_id);
  std :: vector< std :: vector<std :: string> > show_published(std :: string director="");
  bool has_film(Film *film);
  std :: vector<std :: vector<std :: string> > recomm_film(int index);
  std :: vector<std :: string> show_dateils_of_movie(int film_id);
  std :: vector < std :: vector < std :: string > > get_purchased(std :: string director="");
  void reply_to_comment(int film_id,int comment_id,std :: string content);
  void remove_film_from_all(int film_id);
  void logout();
  int get_all_money_in_network();
  void update_graph();
  bool get_is_active_publisher();
  int get_all_money_of_current_user();
  void change_all_money_of_current_user(int amount);
  std :: vector < std :: vector < std :: string > > get_allowed_films(std :: string director = "");
protected:
  std :: vector <Film*>films;
  std :: vector <Customer*>customers;
  std :: vector <Publisher*>publishers;
  std :: vector<std :: vector <int> > films_graph;
  Customer* cactive_user;
  Publisher* pactive_user;
  bool is_active_publisher;
  bool is_admin;
  int num_of_removed_films;
  int all_money;
};

#endif
