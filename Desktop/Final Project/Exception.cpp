#include "Exception.h"

using namespace std;

const char* NotFoundEx::what() const throw()
{
	return "Not Found";
}

const char* PermissionEx::what() const throw()
{
	return "Permission Denied";
}

const char* BadRequestEx::what() const throw()
{
	return "Bad Request";
}