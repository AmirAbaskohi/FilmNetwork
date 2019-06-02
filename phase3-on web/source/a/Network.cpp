#include "Network.h"

using namespace std;

Network :: Network()
{
  cactive_user = NULL;
  pactive_user = NULL;
  is_active_publisher = false;
  is_admin = false;
  all_money = 0;
  num_of_removed_films = 0;
}

bool Network :: get_is_active_publisher()
{
  return is_active_publisher;
}

bool Network :: signup(string email,string username,string password,string age,bool is_publisher)
{
  for(int i = 0 ; i < publishers.size() ; i++)
    if(publishers[i] -> get_username() == username)
      return false;
  for(int i = 0 ; i < customers.size() ; i++)
    if(customers[i] -> get_username() == username)
      return false;
  int new_id = customers.size() + publishers.size() + 1;
  if(is_publisher)
  {
    Publisher* new_user;
    new_user = new Publisher(new_id,email,username,sha256(password),stoi(age));
    publishers.push_back(new_user);
    is_active_publisher = true ;
    pactive_user = new_user;
    cactive_user = new_user;
    return true;
  }
  else
  {
    Customer* new_user;
    new_user = new Customer(new_id,email,username,sha256(password),stoi(age));
    customers.push_back(new_user);
    is_active_publisher = false;
    cactive_user = new_user;
    return true;
  }
}

bool Network :: login(string username,string password)
{
  if(cactive_user != NULL)

  for(int i = 0 ; i < publishers.size() ; i++)
    if(publishers[i] -> get_username() == username && sha256(publishers[i] -> get_password()) == sha256(password))
      {
        pactive_user = publishers[i];
        cactive_user = publishers[i];
        is_active_publisher = true;
        return true;
      }
  for(int i = 0 ; i < customers.size() ; i++)
    if(customers[i] -> get_username() == username && sha256(customers[i] -> get_password()) == sha256(password))
      {
        cactive_user = customers[i];
        is_active_publisher = false;
        if(customers[i]->get_username() == "admin" && customers[i]->get_password() == sha256(password))
          is_admin = true;
        return true;
      }
  return false;
}

void Network :: release_film(string _name,int _year,int _length,int _price,string _summary,string _director)
{
  int new_id = films.size() + num_of_removed_films + 1;
  films.push_back(pactive_user -> release_film(new_id,_name,_year,_length,_price,_summary,_director));
  for(int i = 0; i < pactive_user->customers.size() ; i++)
  {
    pactive_user->customers[i]->add_notification(
      "Publisher " + pactive_user->get_username() +
      " with id " + to_string(pactive_user->get_id()) +
      " register new film.");
  }
  update_graph();
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
}

void Network :: buy_film(int _id)
{
  for(int i = 0;i < publishers.size() ; i++)
    for(int j = 0 ; j < publishers[i]->get_size_publishedfilms() ; j++)
      if(publishers[i]->get_id_publishedfilm(j) == _id)
      {
        publishers[i]->increase_film_bought(j);
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
        all_money = all_money + (amount * (100-percent) / 100);
        publishers[i]->add_notification(
          "User "+cactive_user->get_username()+" with id "+
          to_string(cactive_user->get_id())+" buy your film "+
          publishers[i]->get_name_publishedfilm(j)+" with id "+
          to_string(publishers[i]->get_id_publishedfilm(j)));
        update_graph();
        return;
      }
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
  for(int i = 0 ; i < pactive_user->get_size_publishedfilms() ; i++)
    if(pactive_user->get_id_publishedfilm(i) == film_id)
    {
      for(int j = 0 ; j < pactive_user->get_size_publishedfilm_comments(i) ; j++)
        if(pactive_user->get_id_publishedfilm_comment(i,j) == comment_id)
        {
          pactive_user->delete_publishedfilm_comment(i,j);
          return;
        }
    }
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
  for(int i = 0 ; i < films.size() ; i++)
    if(films[i]->get_id() == film_id)
    {
      film_entity = true;
      break;
    }
  for(int i = 0 ; i < pactive_user->get_size_publishedfilms() ; i++)
    if(pactive_user->get_id_publishedfilm(i) == film_id)
    {
      num_of_removed_films++;
      remove_film_from_all(film_id);
      update_graph();
      return;
    }
}

vector< vector<string> > Network :: show_published(string director="")
{
  return pactive_user->get_published(director);
}

bool Network :: has_film(Film *film)
{
  for(int i = 0 ; i < cactive_user->get_size_films() ; i++)
    if(cactive_user->get_film(i) == film)
      return true;
  return false;
}

vector<vector<string> > Network :: recomm_film(int index)
{
  int counter = 1;
  bool is_all_checked;
  int rates[films_graph.size()];
  int* temp_index;
  vector<string> one_film_inf;
  vector<vector<string> >all_films_inf;
  for(int i = 0 ; i < films_graph.size() ; i++)
    rates[i] = films_graph[index][i];
  rates[index] = -1;
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
    temp_index = max_element(rates,rates+films_graph.size());
    for(int i = 0 ; i < films.size() ; i++)
      if(temp_index == rates+i)
      {
        if(!has_film(films[i]))
        {
          one_film_inf.push_back(films[i]->get_name());
          one_film_inf.push_back(to_string(films[i]->get_length()));
          one_film_inf.push_back(films[i]->get_director());
          one_film_inf.push_back(to_string(films[i]->get_id()));
          all_films_inf.push_back(one_film_inf);
          one_film_inf.clear();
          counter ++;
        }
        rates[i] = -1;
      }
  }
  return all_films_inf;
}

vector< string > Network :: show_dateils_of_movie(int film_id)
{
  vector<string>details_and_recomms;
  vector<vector < string > > recomms;
  for(int i = 0 ; i < films.size() ; i++)
    if(films[i]->get_id() == film_id)
    {
      details_and_recomms.push_back(films[i]->get_name());
      details_and_recomms.push_back(films[i]->get_length());
      details_and_recomms.push_back(films[i]->get_director());
      details_and_recomms.push_back(films[i]->get_price());
      details_and_recomms.push_back(films[i]->get_mean_rate());
      details_and_recomms.push_back(films[i]->get_year());
      details_and_recomms.push_back(films[i]->get_summary());
      recomms = recomm_film(i);
      for(int i = 0 ; i<recomms.size() ; i++)
        for(int j = 0 ; j < 4 ; j++)
          details_and_recomms.push_back(recomms[i][j]);
      return details_and_recomms;
    }
}

void Network :: get_films(string name,int min_rate,int min_year,int price,int max_year,string director)
{
  int counter = 1;
  cout << "#. Film Id | Film Name | Film Length | Film Price | Rate | Production Year | Film Director" << endl;
  for(int i = 0 ; i < films.size() ; i++)
    if((films[i]->get_name() == name || name == "") &&
      (films[i]->get_director() == director || director == "") &&
      (films[i]->get_price() == price || price == 0) &&
      (films[i]->get_year() >= min_year || min_year == 0) &&
      (films[i]->get_year() <= max_year || max_year == 0) &&
      (films[i]->get_mean_rate() >= min_rate || min_rate == 0)
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

vector<vector < string > > Network :: get_purchased()
{
  vector<vector < string > >all_films_inf;
  vector<string>one_film_inf;
  for(int i = 0 ; i < cactive_user -> get_size_films() ; i++)
  {
        one_film_inf.push_back(cactive_user -> get_name_film(i));
        one_film_inf.push_back(to_string(cactive_user -> get_length_film(i)));
        one_film_inf.push_back(to_string(cactive_user -> get_price_film(i)));
        one_film_inf.push_back(to_string(cactive_user -> get_mean_rate_film(i)));
        one_film_inf.push_back(to_string(cactive_user -> get_year_film(i)));
        one_film_inf.push_back(cactive_user -> get_director_film(i));
        all_films_inf.push_back(one_film_inf);
        one_film_inf.clear();
  }
  return all_films_inf;
}

vector < vector < string > > Network :: get_allowed_films(string director)
{
  vector<vector < string > >all_films_inf;
  vector<string>one_film_inf;
  for(int i = 0 ; i < films.size() ; i++)
  {
    if(cactive_user->get_all_money() >= films[i]->get_price())
      if(films[i]->get_director() == director || director="")
      {
        one_film_inf.push_back(films[i] -> get_name());
        one_film_inf.push_back(films[i] -> get_length());
        one_film_inf.push_back(films[i] -> get_price());
        one_film_inf.push_back(films[i] -> get_mean_rate());
        one_film_inf.push_back(films[i] -> get_year());
        one_film_inf.push_back(films[i] -> get_director()));
        all_films_inf.push_back(one_film_inf);
        one_film_inf.clear();
      }
  }
  return all_films_inf;
}


int get_all_money_of_current_user()
{
  return cactive_user->get_all_money();
}
void change_all_money_of_current_user(int amount)
{
  cactive_user->charge(amount);
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
}

int Network :: get_all_money_in_network()
{
  return all_money;
}

void Network :: update_graph()
{
  int num_of_rows_and_col = films.size();
  for(int i = 0 ; i < films_graph.size() ; i++)
    films_graph[i].clear();
  films_graph.clear();
  vector<vector< int > > new_graph(num_of_rows_and_col,vector<int>(num_of_rows_and_col,0));
  for(int i = 0 ; i < num_of_rows_and_col ; i++)
    for(int j = i ; j < num_of_rows_and_col ; j++)
    {
      if(i == j)
        continue;
      films_graph[i][j] = films[i]->get_num_of_bought() + films[j]->get_num_of_bought();
      films_graph[j][i] = films_graph[i][j];
    }
  films_graph = new_graph;
}
