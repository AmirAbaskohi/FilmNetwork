#include <iostream>

#include "handlers.hpp"
#include "my_server.hpp"

using namespace std;

int main(int argc, char **argv) {
  Network network = Network();
  try
  {
    MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
    server.setNotFoundErrPage("static/404.html");
    server.get("/", new ShowPage("static/login.html"));
    server.post("/", new LoginHandler(&network));
    server.get("/signup", new ShowPage("static/signup.html"));
    server.post("/signup", new SignUpHandler(&network));
    server.get("/publishershome", new PublishedFilmListHandler(&network));
    server.get("/publishershomefilter", new PublishedFilterFilmListHandler(&network));
    server.get("/customershome", new AllowedFilmListHandler(&network));
    server.get("/customershomefilter", new AllowedFilterFilmListHandler(&network));
    server.get("/profile", new BoughtFilmListHandler(&network));
    server.get("/detailoffilm", new DetailFilmHandler(&network));
    server.get("/rate", new ScoreFilmHandler(&network));
    server.run();
  }
  catch (Server::Exception e)
  {
    cerr << e.getMessage() << endl;
  }
}
