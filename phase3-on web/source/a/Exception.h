#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

class NotFoundEx : public std :: exception
{
public:
	const char* what() const throw();
};
class PermissionEx : public std :: exception
{
public:
	const char* what() const throw();
};
class BadRequestEx : public std :: exception
{
public:
	const char* what() const throw();
};

#endif