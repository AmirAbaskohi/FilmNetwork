#include "Film.h"

using namespace std;

Film :: Film(int _id,string _name,int _year,int _length,int _price,string _summary,string _director)
{
	id = _id;
	name = _name;
	year = _year;
	length = _length;
	price = _price;
	summary = _summary;
	director = _director;
}

string Film :: get_name()
{
	return name;
}
string Film :: get_summary()
{
	return summary;
}
string Film :: get_director()
{
	return director;
}
int Film :: get_price()
{
	return price;
}
int Film :: get_year()
{
	return year;
}
int Film :: get_length()
{
	return length;
}
int Film :: get_id()
{
	return id;
}

void Film :: delete_all_comments()
{
	for(int i = 0 ; i < comments.size() ; i++)
		delete comments[i];
	comments.clear();
}

void Film :: add_score(int score)
{
	scores.push_back(score);
}

float Film :: get_mean_rate()
{
	int sum = 0;
	int num_of_scores = 0;
	for(int i = 0; i < scores.size() ; i++)
	{
		sum = sum + scores[i];
		num_of_scores ++;
	}
	return sum/num_of_scores;
}

void Film :: add_comment(string _content,int user_id)
{
	int new_id = comments.size() + 1;
	comments.push_back(new Comment(_content,new_id,user_id));
}

void Film :: edit(string new_name,int new_year,int new_length,string new_summary,string new_director)
{
	if(new_name != "")
		name = new_name;
	if(new_summary != "")
		summary = new_summary;
	if(new_director != "")
		director = new_director;
	if(new_length != 0)
		length = new_length;
	if(new_year != 0)
		year = new_year;
}

void Film :: reply_comment(int comment_id,std :: string content)
{
	for(int i = 0 ; i < comments.size() ; i++)
		if(comments[i]->get_id() == comment_id)
		{
			comments[i]->add_reply(content);
			return;
		}
	throw NotFoundEx();
}

int Film :: get_commenter_id(int comment_id)
{
	for(int i = 0 ; i < comments.size() ; i++)
		if(comments[i]->get_id() == comment_id)
			return comments[i]->get_commenter_id();
}

int Film :: get_size_comments()
{
	return comments.size();
}

int Film :: get_id_comment(int index)
{
	return comments[index]->get_id();
}

void Film :: delete_comment(int index)
{
	delete comments[index];
	comments.erase(comments.begin()+index);
}

string Film :: get_content_comment(int index)
{
	return comments[index]->get_content();
}
