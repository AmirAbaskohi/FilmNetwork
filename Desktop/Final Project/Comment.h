#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include <iostream>
#include "Film.h"

class Customer
{
public:
    Customer(int _id,std :: string _email,std :: string _username , std :: string _password , int _age);
    void follow_publisher(Customer* publisher);
    void charge(int amount);
    void buy(int amount);
    std :: string get_username();
    int get_id();
    void show_unread_notifications();
    void show_read_notifications(int limit);
    void add_notification(std :: string content);
    void add_publisher(Customer* customer);
    void romove_from_films(int index);
    int get_id_film(int index);
    int get_size_films();
    Film* get_film(int index);
    std :: string get_name_film(int index);
    std :: string get_director_film(int index);
    std :: string get_password();
    int get_price_film(int index);
    int get_year_film(int index);
    int get_length_film(int index);
    int get_mean_rate_film(int index);
    std :: string get_email();
    int get_all_money();
protected:
    std :: string email;
    std :: string username;
    std :: string password;
    int age;
    int all_money;
    int id;
    std :: vector<Film*>films;
    std :: vector<Customer*>publishers;
    std :: vector<std :: string>unread_notifications;
    std :: vector<std :: string>read_notifications;
};

#endif
