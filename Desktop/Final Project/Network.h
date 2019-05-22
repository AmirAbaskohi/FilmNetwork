#ifndef NETWORK_H
#define NETWORK_H

#include <sstream>
#include <algorithm>
#include <iostream>
#include "Film.h"
#include "Publisher.h"
#include "Customer.h"
#include "Exception.h"

#define POST "POST"
#define GET "GET"
#define PUT "PUT"
#define DELETE "DELETE"

class Network
{
public:
  Network();
  void get_user_command();
  void handle_put_commands(std :: vector < std :: string >words);
  void handle_delete_commands(std :: vector < std :: string >words);
  void handle_get_commands(std :: vector < std :: string >words);
  void handle_post_commands(std :: vector < std :: string >words);
  void signup(std :: string email,std :: string username,std :: string password,std :: string age,bool is_publisher);
  void login(std :: string username,std :: string password);
  void release_film(std :: string _name,int _year,int _length,int _price,std :: string _summary,std :: string _director);
  void follow_a_publisher(int _id);
  void rate_a_film(int _id,int score);
  void buy_film(int _id);
  void comment_film(int _id,std :: string _content,int user_id);
  void edit_film(std :: vector <std :: string> words,int film_id);
  void delete_comment(int film_id , int comment_id);
  void delete_film(int film_id);
  void show_published(std :: vector <std :: string> words);
  void show_comments(Film* film);
  bool has_film(Film *film);
  void recomm_film();
  void show_dateils_of_movie(int film_id);
  void get_films(std :: string name,int min_rate,int min_year,int price,int max_year,std :: string director);
  void search_film(std :: vector<std :: string>words);
  void get_purchased(std :: string name,int min_year,int price,int max_year,std :: string director);
  void show_purchased(std :: vector < std :: string > words);
  void reply_to_comment(int film_id,int comment_id,std :: string content);
  void remove_film_from_all(int film_id);
protected:
  std :: vector <Film*>films;
  std :: vector <Customer*>customers;
  std :: vector <Publisher*>publishers;
  Customer* cactive_user;
  Publisher* pactive_user;
  bool is_active_publisher;
};

#endif
