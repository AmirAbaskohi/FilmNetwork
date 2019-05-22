#include "Network.h"

using namespace std;

Network :: Network()
{
  cactive_user = NULL;
  pactive_user = NULL;
  is_active_publisher = false;
}

void Network :: get_user_command()
{
  string user_input;
  string word;
  vector < string > words_in_line;
  getline(cin,user_input);
  istringstream iss(user_input);
  while(iss >> word)
  {
    words_in_line.push_back(word);
    word.clear();
  }
  int size = words_in_line.size();
  if(size == 6 && (words_in_line[0] != GET ||
     words_in_line[1] != "notifications" ||
     words_in_line[2] != "read" || words_in_line[3] != "?" ||
      words_in_line[4] != "limit"))
      throw NotFoundEx();
  if(size > 2 && (words_in_line[2] != "?" || size % 2 != 1))
    throw NotFoundEx();
  if(size == 2 && !(words_in_line[1] == GET || words_in_line[1] == POST))
    throw NotFoundEx();
  if(words_in_line[0] == POST)
    handle_post_commands(words_in_line);
  else if(words_in_line [0] == PUT)
    handle_put_commands(words_in_line);
  else if(words_in_line [0] == GET)
    handle_get_commands(words_in_line);
  else if(words_in_line [0] == DELETE)
    handle_delete_commands(words_in_line);
  else
    throw NotFoundEx();
}

void Network :: handle_post_commands(vector < string > words)
{
  if(words[1] == "signup")
  {
    if(words[3] != "email" || words[5] != "username" ||
      words[7] != "password" || words[9] != "age")
     throw NotFoundEx();
    else if(words.size() == 13 && words[11] != "publisher")
      throw NotFoundEx();
    else
    {
      if(words.size() == 13 )
      {
        if(words[11] != "publisher" || !(words[12] == "true" || words[12] == "false"))
          throw NotFoundEx();
        else
          signup(words[4],words[6],words[8],words[10],true);
      }
      else
        signup(words[4],words[6],words[8],words[10],false);
      cout << "OK" << endl;
    }
  }
  else if(words[1] == "login")
  {
    if(words[3] != "username" || words[5] != "password")
      throw NotFoundEx();
    else
      login(words[4],words[6]);
    cout << "OK" << endl;
  }
  else if(words[1] == "films")
  {
    if(words[3] != "name" || words[5] != "year" ||
      words[7] != "length" || words[9] != "price" ||
      words[11] != "summary" || words[13] != "director")
       throw NotFoundEx();
    else
    {
      if(pactive_user == NULL || is_active_publisher == false)
        throw PermissionEx();
      else
        release_film(words[4],stoi(words[6]),stoi(words[8]),stoi(words[10]),words[12],words[14]);
      cout << "OK" << endl;
    }
  }
  else if(words[1] ==  "money")
  {
    if(words.size() == 2)
    {
      if(pactive_user == NULL || is_active_publisher == false)
        throw PermissionEx();
      pactive_user -> get_money_from_network();
      cout << "OK" << endl;
    }
    else if(words.size() == 5)
    {
      if(words[3] != "amount")
        throw NotFoundEx();
      if(cactive_user == NULL)
        throw PermissionEx();
      cactive_user -> charge(stoi(words[4]));
    }
    else
      throw NotFoundEx();
  }
  else if(words[1] == "followers")
  {
    if(words[3] != "user_id")
      throw NotFoundEx();
    else
    {
      if(cactive_user == NULL)
        throw PermissionEx();
      else
        follow_a_publisher(stoi(words[4]));
      cout << "OK" << endl;
    }
  }
  else if(words[1] == "replies")
  {
    if(words[3] != "film_id" || words[5] != "comment_id" || words[7] == "content")
      throw NotFoundEx();
    else
      reply_to_comment(stoi(words[4]),stoi(words[6]),words[8]);
    cout << "OK" << endl;
  }
  else if(words[1] == "buy")
  {
    if(words[3] != "film_id")
      throw NotFoundEx();
    else
    {
      if(pactive_user == NULL)
        throw PermissionEx();
      buy_film(stoi(words[4]));
      cout << "OK" << endl;
    }
  }
  else if(words[1] == "rate")
  {
    if(words[3] != "film_id" || words[5] != "content")
      throw NotFoundEx();
    else
    {
      if(cactive_user == NULL)
        throw PermissionEx();
      rate_a_film(stoi(words[4]),stoi(words[6]));
      cout << "OK" << endl;
    }
  }
  else if(words[1] == "comments")
  {
    if(words[3] != "film_id" || words[5] != "content")
      throw NotFoundEx();
    else
      comment_film(stoi(words[4]),words[6],cactive_user->get_id());
    cout << "OK" << endl;
  }
  else
    throw NotFoundEx();
}

void Network :: handle_get_commands(vector < string > words)
{
  if(words[1] == "published")
  {  
    for(int i = 3;i < words.size() ; i++)
      if(i % 2 == 1 && !(words[i] != "name" ||
        words[i] != "min_rate" || words[i] != "min_year" ||
        words[i] != "price" || words[i] != "max_year" ||
        words[i] != "director"))
        throw NotFoundEx();
    if(pactive_user == NULL || is_active_publisher == false)
      throw PermissionEx();
    show_published(words);
  }
  else if(words[1] == "films" && words.size() == 5 && words[3] == "film_id")
  {
    if(cactive_user == NULL)
      throw PermissionEx();
    show_dateils_of_movie(stoi(words[4]));
  }
  else if(words[1] == "films")
  {
    for(int i = 3;i < words.size() ; i++)
      if(i % 2 == 1 && !(words[i] != "name" ||
        words[i] != "min_rate" || words[i] != "director" ||
        words[i] != "price" || words[i] != "max_year" || words[i] != "min_year"))
        throw NotFoundEx();
    if(cactive_user == NULL)
      throw PermissionEx();
    search_film(words);
  }
  else if(words[1] == "purchased")
  {
    for(int i = 3;i < words.size() ; i++)
      if(i % 2 == 1 && !(words[i] != "name" ||
        words[i] != "min_year" || words[i] != "director" ||
        words[i] != "price" || words[i] != "max_year" ))
        throw NotFoundEx();
    show_purchased(words);
  }
  else if(words[1] == "notifications")
  {
    if(words.size() == 2)
    {
      if(cactive_user == NULL)
        throw PermissionEx();
      cactive_user -> show_unread_notifications();
    }
    else if(words.size() == 6 && words[2] == "read" &&
     words[3] == "?" && words[4] == "limit")
    {
      if(cactive_user == NULL)
        throw PermissionEx();
      cactive_user -> show_read_notifications(stoi(words[5]));
    }
    else
      throw NotFoundEx();
  }
  else if(words[1] == "followers")
  {
    if(words.size() != 2)
      throw NotFoundEx();
    else
    {
      if(pactive_user == NULL || is_active_publisher == false)
        throw PermissionEx();
      pactive_user -> show_followers();
    }
  }
}

void Network :: handle_put_commands(vector < string > words)
{
  if(words[1] == "films")
  {
    if(words.size() < 5 || words.size() > 15)
      throw NotFoundEx();
    if(words[2] != "?" || words[3] != "film_id")
      throw NotFoundEx();
    else
    {
      for(int i = 3;i < words.size() ; i++)
        if(i % 2 == 1 && !(words[i] != "name" ||
          words[i] != "year" || words[i] != "length" ||
          words[i] != "director" || words[i] != "summary" ))
          throw NotFoundEx();
      if(cactive_user == NULL)
        throw PermissionEx();
     edit_film(words,stoi(words[4]));
     cout << "OK" << endl;
    }
  }
  else
    throw NotFoundEx();
}

void Network :: handle_delete_commands(vector < string > words)
{
  if(words[1] == "film")
  {
    if(words.size() != 5 || words[3] != "film_id")
      throw NotFoundEx();
    else
    {
      if(pactive_user == NULL || is_active_publisher == false)
        throw PermissionEx();
      delete_film(stoi(words[4]));
      cout << "OK" << endl;
    }
  }
  if(words[1] == "comment")
  {
    if(words.size() != 7 || words[3] != "film_id" || words[5] != "comment_id")
      throw NotFoundEx();
    else
    {
      if(pactive_user == NULL || is_active_publisher == false)
        throw PermissionEx();
      delete_comment(stoi(words[4]) ,stoi(words[6]));
      cout << "OK" << endl;
    }
  }
}

void Network :: signup(string email,string username,string password,string age,bool is_publisher)
{
  for(int i = 0 ; i < publishers.size() ; i++)
    if(publishers[i] -> get_username() == username)
      throw BadRequestEx();
  for(int i = 0 ; i < customers.size() ; i++)
    if(customers[i] -> get_username() == username)
      throw BadRequestEx();
  int new_id = customers.size() + publishers.size() + 1;
  if(is_publisher)
  {
    Publisher* new_user;
    new_user = new Publisher(new_id,email,username,password,stoi(age));
    publishers.push_back(new_user);
    is_active_publisher = true ;
    pactive_user = new_user;
    cactive_user = new_user;
  }
  else
  {
    Customer* new_user;
    new_user = new Customer(new_id,email,username,password,stoi(age));
    customers.push_back(new_user);
    is_active_publisher = false;
    cactive_user = new_user;
  }
}

void Network :: login(string username,string password)
{
  for(int i = 0 ; i < publishers.size() ; i++)
    if(publishers[i] -> get_username() == username && publishers[i] -> get_password() == password)
      {
        pactive_user = publishers[i];
        cactive_user = publishers[i];
        is_active_publisher = true;
        return ;
      }
  for(int i = 0 ; i < customers.size() ; i++)
    if(customers[i] -> get_username() == username && customers[i] -> get_password() == password)
      {
        cactive_user = customers[i];
        is_active_publisher = false;
        return ;
      }
  throw BadRequestEx();
}

void Network :: release_film(string _name,int _year,int _length,int _price,string _summary,string _director)
{
  int new_id = films.size() + 1;
  films.push_back(pactive_user -> release_film(new_id,_name,_year,_length,_price,_summary,_director));
  for(int i = 0; i < pactive_user->customers.size() ; i++)
  {
    pactive_user->customers[i]->add_notification(
      "Publisher " + pactive_user->get_username() +  
      " with id " + to_string(pactive_user->get_id()) +
      " register new film.");
  }
}

void Network :: follow_a_publisher(int _id)
{
  for(int i = 0 ; i < publishers.size() ; i++)
    if(publishers[i]->get_id() == _id)
    {
      cactive_user -> follow_publisher(publishers[i]);
      publishers[i] -> add_customer(cactive_user);
      cactive_user -> add_publisher(publishers[i]);
      publishers[i] -> add_notification(
        "User " + cactive_user->get_username() + " with id " +
         to_string(cactive_user->get_id()) + " follow you.");
      return ;
    }
  throw NotFoundEx();
}

void Network :: rate_a_film(int _id,int score)
{
  for(int i = 0;i < publishers.size() ; i++)
    for(int j = 0 ; j < publishers[i]->get_size_publishedfilms() ; j++)
      if(publishers[i]->get_id_publishedfilm(j) == _id)
      {
        publishers[i] -> add_score_to_published(j,score);
        publishers[i]-> add_notification(
          "User "+cactive_user->get_username()+" with id "+
          to_string(cactive_user->get_id())+" rate your film "+
          publishers[i]->get_name_publishedfilm(j)+" with id "+
          to_string(publishers[i]->get_id_publishedfilm(j)));
        return;
      }
  throw NotFoundEx();
}

void Network :: buy_film(int _id)
{
  for(int i = 0;i < publishers.size() ; i++)
    for(int j = 0 ; j < publishers[i]->get_size_publishedfilms() ; j++)
      if(publishers[i]->get_id_publishedfilm(j) == _id)
      {
        int amount = publishers[i]->get_price_publishedfilm(j);
        int mean_rate = publishers[i]->get_mean_rate_publishedfilm(j);
        int percent;
        if(mean_rate < 5)
          percent = 80;
        else if(mean_rate >= 5 && mean_rate < 8)
          percent = 90;
        else
          percent = 95;
        cactive_user -> buy(amount);
        publishers[i] -> accumulate(amount * percent / 100);
        publishers[i]->add_notification(
          "User "+cactive_user->get_username()+" with id "+
          to_string(cactive_user->get_id())+" buy your film "+
          publishers[i]->get_name_publishedfilm(j)+" with id "+
          to_string(publishers[i]->get_id_publishedfilm(j)));
        return;
      }
  throw NotFoundEx();
}

void Network :: comment_film(int _id,string _content,int user_id)
{
  for(int i = 0;i < publishers.size() ; i++)
    for(int j = 0 ; j < publishers[i]->get_size_publishedfilms() ; j++)
    if(publishers[i]->get_id_publishedfilm(j) == _id)
    {
      publishers[i] -> add_comment_publishedfilm(j,_content,user_id);
      publishers[i]->add_notification(
          "User "+cactive_user->get_username()+" with id "+
          to_string(cactive_user->get_id())+" comment on your film "+
          publishers[i]->get_name_publishedfilm(j)+" with id "+
          to_string(publishers[i]->get_id_publishedfilm(j)));
      return;
    }
  throw NotFoundEx();
}

void Network :: edit_film(vector<string>words,int film_id)
{
  string name = "";
  string summary = "";
  string director = "";
  int year = 0;
  int length = 0;
  for(int i = 5 ; i < words.size() ; i = i+2)
  {
    if(words[i] == "name")
      name = words[i+1];
    else if(words[i] == "year")
      year = stoi(words[i+1]);
    else if(words[i] == "length")
      length = stoi(words[i+1]);
    else if(words[i] == "summary")
      summary = words[i+1];
    else if(words[i] == "director")
      director = words[i+1];
  }
  for(int i = 0 ; i < films.size() ; i++)
    if(films[i] -> get_id() == film_id)
    {
      films[i]->edit(name,year,length,summary,director);
      return;
    }
  throw NotFoundEx();
}

void Network :: delete_comment(int film_id,int comment_id)
{
  bool film_entity = false;
  for(int i = 0 ; i < films.size() ; i++)
    if(films[i]->get_id() == film_id)
    {
      film_entity = true;
      break;
    }
  if(! film_entity)
    throw NotFoundEx();
  for(int i = 0 ; i < pactive_user->get_size_publishedfilms() ; i++)
    if(pactive_user->get_id_publishedfilm(i) == film_id)
    {
      for(int j = 0 ; j < pactive_user->get_size_publishedfilm_comments(i) ; j++)
        if(pactive_user->get_id_publishedfilm_comment(i,j) == comment_id)
        {
          pactive_user->delete_publishedfilm_comment(i,j);
          return;
        }
      throw NotFoundEx();
    }
  throw PermissionEx();
}

void Network :: remove_film_from_all(int film_id)
{
  for(int i = 0 ; i < films.size() ; i++)
    if(films[i] -> get_id() == film_id)
    {
      films[i]->delete_all_comments();
      delete films[i];
      films.erase(films.begin() + i);
      break;
    }
  for(int i = 0 ; i < pactive_user->get_size_publishedfilms() ; i++)
    if(pactive_user->get_id_publishedfilm(i) == film_id)
    {
      pactive_user->published_films.erase(pactive_user->published_films.begin()+i);
      break;
    }
  for(int i = 0 ; i < publishers.size() ; i++)
    for(int j = 0 ; j < publishers[i]->get_size_films(); j++)
      if(publishers[i] -> get_id_film(j) == film_id)
      {
        publishers[i] ->romove_from_films(j);
        break;
      }
  for(int i = 0 ; i < customers.size() ; i++)
    for(int j = 0 ; j < customers[i]->get_size_films() ; j++)
      if(customers[i] -> get_id_film(j)== film_id)
      {
        customers[i] -> romove_from_films(j);
        break;
      }
}

void Network :: delete_film(int film_id)
{
  bool film_entity = false;
  for(int i = 0 ; i < films.size() ; i++)
    if(films[i]->get_id() == film_id)
    {
      film_entity = true;
      break;
    }
  if(! film_entity)
    throw NotFoundEx();
  for(int i = 0 ; i < pactive_user->get_size_publishedfilms() ; i++)
    if(pactive_user->get_id_publishedfilm(i) == film_id)
      remove_film_from_all(film_id);
  throw PermissionEx();
}

void Network :: show_published(vector <string> words)
{
  string name = "";
  string summary = "";
  string director = "";
  int min_year = 0;
  int max_year = 0;
  int price = 0;
  int min_rate = 0;
  for(int i = 5 ; i < words.size() ; i = i+2)
  {
    if(words[i] == "name")
      name = words[i+1];
    else if(words[i] == "min_year")
      min_year = stoi(words[i+1]);
    else if(words[i] == "max_year")
      max_year = stoi(words[i+1]);
    else if(words[i] == "price")
      price = stoi(words[i+1]);
    else if(words[i] == "min_rate")
      min_rate = stoi(words[i+1]);
    else if(words[i] == "director")
      director = words[i+1];
  }
  pactive_user->get_published(name,min_rate,min_year,price,max_year,director);
}

void Network :: show_comments(Film* film)
{
  cout << "Comments" <<endl;
  for(int i = 0 ; i < film->get_size_comments() ; i++)
  {
    cout << film->get_id_comment(i) << ". " << film->get_content_comment(i) << endl;
    film->comments[i]->show_replies();
  }
  cout << "\n\n";
}

bool Network :: has_film(Film *film)
{
  for(int i = 0 ; i < cactive_user->get_size_films() ; i++)
    if(cactive_user->get_film(i) == film)
      return true;
  return false;
}

void Network :: recomm_film()
{
  cout << "Recommendation Film" << endl;
  cout << "#. Film Id | Film Name | Film Length | Film Director" << endl;
  int counter = 1;
  bool is_all_checked;
  int rates[films.size()];
  int* temp_index;
  for(int i = 0 ; i < films.size() ; i++)
    rates[i] = (films[i]->get_mean_rate());
  while(counter < 5)
  {
    for(int i = 0 ; films.size() ; i++)
      if(rates[i] != -1)
      {
        is_all_checked = false;
        break;
      }
    if(is_all_checked)
      break;
    temp_index = max_element(rates,rates+films.size());
    for(int i = 0 ; i < films.size() ; i++)
      if(temp_index == rates+i)
      {
        if(!has_film(films[i]))
        {
          cout << counter << ". " << films[i]->get_id() << " | " <<
            films[i]->get_name() << " | " <<
            films[i]->get_length() << " | " <<
            films[i]->get_director() << " | " <<endl;
            counter ++;
        }
        rates[i] = -1;
      }
  }
}

void Network :: show_dateils_of_movie(int film_id)
{
  for(int i = 0 ; i < films.size() ; i++)
    if(films[i]->get_id() == film_id)
    {
      cout << "Details of Film "<<films[i]->get_name() <<"\n" <<
        "Id "<<films[i]->get_id() <<"\n" <<
        "Director "<<films[i]->get_director() <<"\n" <<
        "Length "<<films[i]->get_length() <<"\n" <<
        "Year "<<films[i]->get_name() <<"\n" <<
        "Summary "<<films[i]->get_name() <<"\n" <<
        "Rate "<<films[i]->get_name() <<"\n" <<
        "Price "<<films[i]->get_name() <<"\n\n\n";
      show_comments(films[i]);
      recomm_film();
      return;
    }
  throw NotFoundEx();
}

void Network :: get_films(string name,int min_rate,int min_year,int price,int max_year,string director)
{
  int counter = 1;
  cout << "#. Film Id | Film Name | Film Length | Film Price | Rate | Production Year | Film Director" << endl;
  for(int i = 0 ; i < films.size() ; i++)
    if(films[i]->get_name() == name &&
      films[i]->get_director() == director &&
      films[i]->get_price() == price &&
      films[i]->get_year() >= min_year &&
      films[i]->get_year() <= max_year &&
      films[i]->get_mean_rate() >= min_rate
      )
    {
      cout << counter << ". " << films[i]->get_id() << "| "<<
        films[i]->get_name() << "| "<<
        films[i]->get_length() << "| "<<
        films[i]->get_price() << "| "<<
        films[i]->get_mean_rate() << "| "<<
        films[i]->get_year() << "| "<<
        films[i]->get_director() << "| "<<endl;
      counter++;
    }
}

void Network :: search_film(vector<string>words)
{
  string name = "";
  string summary = "";
  string director = "";
  int min_year = 0;
  int max_year = 0;
  int price = 0;
  int min_rate = 0;
  for(int i = 5 ; i < words.size() ; i = i+2)
  {
    if(words[i] == "name")
      name = words[i+1];
    else if(words[i] == "min_year")
      min_year = stoi(words[i+1]);
    else if(words[i] == "max_year")
      max_year = stoi(words[i+1]);
    else if(words[i] == "price")
      price = stoi(words[i+1]);
    else if(words[i] == "min_rate")
      min_rate = stoi(words[i+1]);
    else if(words[i] == "director")
      director = words[i+1];
  }
  get_films(name,min_rate,min_year,price,max_year,director);
}

void Network :: get_purchased(string name,int min_year,int price,int max_year,string director)
{
  int counter = 1;
  cout << "#. Film Id | Film Name | Film Length | Film Price | Rate | Production Year | Film Director" << endl;
  for(int i = 0 ; i < cactive_user -> get_size_films() ; i++)
    if(cactive_user -> get_name_film(i) == name &&
      cactive_user -> get_director_film(i) == director &&
      cactive_user -> get_price_film(i) == price &&
      cactive_user -> get_year_film(i) >= min_year &&
      cactive_user -> get_year_film(i) <= max_year
      )
    {
      cout << counter << ". " << cactive_user -> get_id_film(i) << "| "<<
        cactive_user -> get_name_film(i) << "| "<<
        cactive_user -> get_length_film(i) << "| "<<
        cactive_user -> get_price_film(i) << "| "<<
        cactive_user -> get_mean_rate_film(i) << "| "<<
        cactive_user -> get_year_film(i) << "| "<<
        cactive_user -> get_director_film(i) << "| "<<endl;
      counter++;
    }
}

void Network :: show_purchased(vector < string > words)
{
  string name = "";
  string summary = "";
  string director = "";
  int min_year = 0;
  int max_year = 0;
  int price = 0;
  int min_rate = 0;
  for(int i = 5 ; i < words.size() ; i = i+2)
  {
    if(words[i] == "name")
      name = words[i+1];
    else if(words[i] == "min_year")
      min_year = stoi(words[i+1]);
    else if(words[i] == "max_year")
      max_year = stoi(words[i+1]);
    else if(words[i] == "price")
      price = stoi(words[i+1]);
    else if(words[i] == "director")
      director = words[i+1];
  }
  get_purchased(name,min_year,price,max_year,director);
}

void Network :: reply_to_comment(int film_id,int comment_id,string content)
{
  for(int i = 0 ; i < films.size() ; i++)
    if(films[i] -> get_id() == film_id)
    {
      films[i] -> reply_comment(comment_id,content);
      int commenter_id = films[i] -> get_commenter_id(comment_id);
      for(int j = 0 ; j < customers.size() ; j++)
        if(commenter_id = customers[j]->get_id())
        {
          customers[j]->add_notification("Publisher " +
           cactive_user->get_username() + " with id " +
            to_string(cactive_user->get_id()) + "reply to your comment.");
          return;
        }
      for(int j = 0 ; j < publishers.size() ; j++)
      if(commenter_id = publishers[j]->get_id())
      {
        publishers[j]->add_notification("Publisher " +
          cactive_user->get_username() + " with id " +
          to_string(cactive_user->get_id()) + "reply to your comment.");
        return;
      }
    }
  throw NotFoundEx();
}
