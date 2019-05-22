#include <exception>
#include "Network.h"
#include "Exception.h"

using namespace std;

int main()
{
	Network network = Network();
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