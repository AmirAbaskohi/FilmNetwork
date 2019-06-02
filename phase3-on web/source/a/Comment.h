#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include <vector>
#include <iostream>

class Comment
{
public:
	Comment(std :: string _content,int _id,int _commenter_id);
    int get_id();
    std :: string get_content();
    void show_replies();
    void add_reply(std :: string content);
    int get_commenter_id();
private:
    std :: vector < std :: string > replies;
    int id;
    int commenter_id;
    std :: string content;
};

#endif
