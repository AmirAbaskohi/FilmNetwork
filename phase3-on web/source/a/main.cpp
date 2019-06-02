#include <exception>
#include "Network.h"
#include "Exception.h"

using namespace std;

int main()
{
	Network network = Network();
	network.signup("admin@admin.admin","admin","admin","0",false);
	network.logout();
	while(true)
	{
		try{
			network.get_user_command();
		}
		catch(exception &ex)
		{
			cerr << ex.what() << endl;
		}
	}
}