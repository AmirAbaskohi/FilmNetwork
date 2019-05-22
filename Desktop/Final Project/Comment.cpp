#include "Comment.h"

using namespace std;

Comment :: Comment(string _content,int _id,int _commenter_id)
{
	id = _id;
	content = _content;
	commenter_id = _commenter_id;
}

int Comment :: get_id()
{
	return id;
}

string Comment :: get_content()
{
	return content;
}

void Comment :: show_replies()
{
	for(int i = 0 ; i < replies.size() ; i++)
		cout << id << "." << i+1 << ". " << replies[i] << endl;
}

void Comment :: add_reply(string content)
{
	replies.push_back(content);
}

int Comment :: get_commenter_id()
{
	return commenter_id;
}