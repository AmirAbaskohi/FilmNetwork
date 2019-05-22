#ifndef FILM_H
#define FILM_H

#include <string>
#include <vector>
#include <iostream>
#include "Comment.h"
#include "Exception.h"

class Film
{
public:
  Film(int _id,std :: string _name,int _year,int _length,int _price,std :: string _summary,std :: string _director);
  std :: string get_name();
  std :: string get_summary();
  std :: string get_director();
  int get_price();
  int get_year();
  int get_length();
  int get_id();
  void add_score(int score);
  float get_mean_rate();
  void add_comment(std :: string _content,int user_id);
  void edit(std :: string new_name,int new_year,int new_length,std :: string new_summary,std :: string new_director);
  void reply_comment(int comment_id,std :: string content);
  void delete_all_comments();
  int get_commenter_id(int comment_id);
  int get_size_comments();
  int get_id_comment(int index);
  void delete_comment(int index);
  std :: string get_content_comment(int index);
  std :: vector<Comment*>comments;
private:
  std :: string name;
  int year;
  int length;
  int price;
  std :: string summary;
  std :: string director;
  int id;
  std :: vector<int> scores;
};

#endif
