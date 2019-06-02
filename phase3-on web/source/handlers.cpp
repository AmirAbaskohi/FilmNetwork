#include "handlers.hpp"

using namespace std;

LoginHandler :: LoginHandler(Network* net)
{
	network = net;
}

SignUpHandler :: SignUpHandler(Network* net)
{
	network = net;
}

PublishedFilmListHandler :: PublishedFilmListHandler(Network* net)
{
	network = net;
}

PublishedFilterFilmListHandler :: PublishedFilterFilmListHandler(Network* net)
{
	network = net;
}

PublishFilmHandler :: PublishFilmHandler(Network *net)
{
	network = net;
}

BoughtFilmListHandler :: BoughtFilmListHandler(Network *net)
{
	network = net;
}

AllowedFilmListHandler :: AllowedFilmListHandler(Network *net)
{
	network = net;
}

DetailFilmHandler :: DetailFilmHandler(Network *net)
{
	network = net;
}

BuyFilmHandler :: BuyFilmHandler(Network *net)
{
	network = net;
}

ScoreFilmHandler :: ScoreFilmHandler(Network *net)
{
	network = net;
}

RateFilmHandler :: RateFilmHandler(Network *net)
{
	network = net;
}

AllowedFilterFilmListHandler :: AllowedFilterFilmListHandler(Network *net)
{
	network = net;
}

Response *LoginHandler::callback(Request *req) 
{
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  Response *res;
  if(network -> login(username,password))
  {
  	if(network->get_is_active_publisher())
  		res = Response::redirect("/publishershome");
  	else
  		res = Response::redirect("/customershome");
  }
  else
  	res = Response::redirect("/");
  return res;
}

Response *SignUpHandler::callback(Request *req) 
{
	bool is_publisher = false;
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  string repassword = req->getBodyParam("repassword");
  string email = req->getBodyParam("email");
  string age = req->getBodyParam("age");
  string publisher = req->getBodyParam("publisher");
  Response *res;
  if(publisher == "true")
  	is_publisher = true;
  if (password != repassword)
    throw Server::Exception("Passwords are not equal!");
	if(network -> signup(email,username,password,age,is_publisher))
  	{
  		cout << "Done" << endl;
  		if(network->get_is_active_publisher())
  			res = Response::redirect("/publishershome");
  		else
  			res = Response::redirect("/customershome");
  	}
  	else
  		res = Response::redirect("/signup");
  return res;
}

Response *PublishFilmHandler::callback(Request *req) 
{
  string name = req->getBodyParam("name");
  string price = req->getBodyParam("price");
  string director = req->getBodyParam("director");
  string length = req->getBodyParam("length");
  string year = req->getBodyParam("year");
  string summary = req->getBodyParam("summary");
  network -> release_film(name,stoi(year),stoi(length),stoi(price),summary,director);
  Response *res = Response::redirect("/publishershome");
  return res;
}

Response *DeleteFilm::callback(Request *req)
{
	string id = req->getQueryParam("film_id");
	network->delete_film(stoi(id));
	Response *res = Response::redirect("/publishershome");
	return res;
}

Response *PublishedFilmListHandler::callback(Request *req)
{
	Response *res = new Response;
	vector<vector < string > > published_films = network->show_published("");
	res -> setHeader("Content-Type","text/html");
	string body;
	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<head>";
	body += "<style>";
	body += ".nav";
	body += "{";
	body += "  list-style-type: none;";
	body += "  margin: 0;";
	body += "  padding: 0;";
	body += "  overflow: hidden;";
	body += "  background-color: #333;";
	body += "  position: -webkit-sticky;";
	body += "  position: sticky;";
	body += "  top: 0;";
	body += "}";
	body += ".nav li";
	body += "{";
	body += "  float: left;";
	body += "  width:10%;";
	body += "}";
	body += ".nav li a";
	body += "{";
	body += "  display: block;";
	body += "  color: white;";
	body += "  text-align: center;";
	body += "  padding: 14px 16px;";
	body += "  text-decoration: none;";
	body += "	font-size: 14px;";
	body += "}";
	body += ".nav li a:hover";
	body += "{";
	body += "  background-color: #111;";
	body += "}";
	body += ".active";
	body += "{";
	body += "  background-color: #4CAF50;";
	body += "}";
	body += ".nav .exit";
	body += "{";
	body += "  background-color: #ff5050;";
	body += "  float: right;";
	body += "  width:12%;";
	body += "}";
	body += "#filmtable {";
	body += "border-collapse: collapse;";
	body += "width: 100%;";
	body += "}";
	body += "#filmtable th,#filmtable td {";
	body += "padding: 8px;";
	body += "text-align: left;";
	body += "border-bottom: 1px solid #ddd;";
	body += "}";
	body += "#filmtable tr:hover {background-color:#f5f5f5;}";
	body += ".deletebtn{";
	body += "padding: 12px 28px;";
	body += "background-color: #008CBA;";
	body += "border: none;";
	body += "border-radius: 9%;";
	body += "}";
	body += ".deletebtn:hover{";
	body +=	"background-color: #55CFF8;";
	body += "}";
	body += ".publishnewbtn a {";
	body += "background-color: red;";
  body += "box-shadow: 0 5px 0 darkred;";
  body += "color: white;";
 	body += "padding: 1em 1.5em;";
  body += "position: relative;";
 	body += "text-decoration: none;";
  body += "text-transform: uppercase;";
	body += "}";
	body += ".publishnewbtn a:hover {";
  body += "background-color: #ce0606;";
  body += "cursor: pointer;";
	body += "}";
	body += ".publishnewbtn a:active {";
  body += "box-shadow: none;";
  body += "top: 5px;";
	body +="}";
	body +=".publishnewbtn{";
  body +="margin-top: 3%;";
  body +="margin-left: 43%;";
	body +="}";
	body += ".filter {";
  body += "width: 190px;";
  body += "box-sizing: border-box;";
  body += "border: 2px solid #aaa;";
 	body += "border-radius: 4px;";
 	body += "font-size: 16px;";
 	body += "background-color: white;";
 	body += "background-position: 10px 10px; ";
 	body += "background-repeat: no-repeat;";
 	body += "padding: 12px 20px 12px 40px;";
  body += "transition: width 0.7s ease-in-out;";
  body += "color:black;";
	body += "}";
	body += ".filter:focus {";
 	body += " width: 30%;";
	body += "}";
	body += ".filterbtn{";
  body += "background-color:#19bc93;";
  body += "border-radius: 4px;";
  body += "border:none;";
  body += "padding: 12px 26px;";
	body += "}";
	body += "</style>";
	body += "</head>";
	body += "<body>";
	body += "<ul class='nav'>";
	body += "<li><a class='active' href='/publishershome'>Home</a></li>";
	body += "<li><a href='/profile'>Profile</a></li>";
	body += "<li><a href='/signup'>Signup</a></li>";
	body += "<li class='exit'><a href='/login'>Logout</a></li>";
	body += "</ul>";
	body += "<p>Search for film by id:</p>";
	body += "<form action='/detailoffilm' method = 'POST'>";
	body += "<input type='text' name='film_id' placeholder='Enter film id' class='filter'>";
	body += "<button type='submit' class='filterbtn'>Search</button>";
	body += "</form>";
	body += "<hr>";
	body += "<h2>Published films up to now:</h2>";
	body += "<form action='/publishershomefilter' method = 'POST'>";
	body += "<p>Filter by director name:</p><br>";
	body += "<input type='text' name='director' placeholder='Enter director' class='filter'>";
	body += "<button type='submit' class='filterbtn'>Filter</button>";
	body += "</form>";
	body += "<hr>";
	body += "<table id='filmtable'>";
	body += "<tr>";
  body += "<th>Name</th>";
  body += "<th>Length</th> ";
  body += "<th>Price</th>";
  body += "<th>Rate</th>";
  body += "<th>Year</th>";
  body += "<th>Director</th>";
  body += "<th>Delete Button</th>";
  body += "</tr>";
	for(unsigned int i = 0 ; i < published_films.size() ; i++)
	{
		body += "<tr>";
		for(int j = 0 ; j < 6 ; j++)
		{
			body += "<td>";
			body += published_films[i][j];
			body += "</td>";
		}
		body += "<td>";
		body += "<form method='POST' action='/publishershome'>";
		body += "<input type='hidden' name='film_id' value='";
		body += published_films[i][7];
		body += "'/>";
		body += "<button type='submit' class='deletebtn'>Delete</button>";
		body += "</form>";
		body += "</td>";
		body += "</tr>";
	}
	body += "</table>";
	body += "<div class='publishnewbtn'><a href='/publishnewfilm'>Publish new</a></div>";
	body += "</body>";
	body += "</html>";
	res -> setBody(body);
	return res;
}

Response *PublishedFilterFilmListHandler::callback(Request *req)
{
	Response *res = new Response;
	vector<vector < string > > published_films = network->show_published(req->getQueryParam("director"));
	res -> setHeader("Content-Type","text/html");
	string body;
	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<head>";
	body += "<style>";
	body += ".nav";
	body += "{";
	body += "  list-style-type: none;";
	body += "  margin: 0;";
	body += "  padding: 0;";
	body += "  overflow: hidden;";
	body += "  background-color: #333;";
	body += "  position: -webkit-sticky;";
	body += "  position: sticky;";
	body += "  top: 0;";
	body += "}";
	body += ".nav li";
	body += "{";
	body += "  float: left;";
	body += "  width:10%;";
	body += "}";
	body += ".nav li a";
	body += "{";
	body += "  display: block;";
	body += "  color: white;";
	body += "  text-align: center;";
	body += "  padding: 14px 16px;";
	body += "  text-decoration: none;";
	body += "	font-size: 14px;";
	body += "}";
	body += ".nav li a:hover";
	body += "{";
	body += "  background-color: #111;";
	body += "}";
	body += ".active";
	body += "{";
	body += "  background-color: #4CAF50;";
	body += "}";
	body += ".nav .exit";
	body += "{";
	body += "  background-color: #ff5050;";
	body += "  float: right;";
	body += " width:12%;";
	body += "}";
	body += "#filmtable {";
	body += "border-collapse: collapse;";
	body += "width: 100%;";
	body += "}";
	body += "#filmtable th,#filmtable td {";
	body += "padding: 8px;";
	body += "text-align: left;";
	body += "border-bottom: 1px solid #ddd;";
	body += "}";
	body += "#filmtable tr:hover {background-color:#f5f5f5;}";
	body += ".deletebtn{";
	body += "padding: 12px 28px;";
	body += "background-color: #008CBA;";
	body += "border: none;";
	body += "border-radius: 9%;";
	body += "}";
	body += ".deletebtn:hover{";
	body +=	"background-color: #55CFF8;";
	body += "}";
	body += ".publishnewbtn a {";
	body += "background-color: red;";
  body += "box-shadow: 0 5px 0 darkred;";
  body += "color: white;";
 	body += "padding: 1em 1.5em;";
  body += "position: relative;";
 	body += "text-decoration: none;";
  body += "text-transform: uppercase;";
	body += "}";
	body += ".publishnewbtn a:hover {";
  body += "background-color: #ce0606;";
  body += "cursor: pointer;";
	body += "}";
	body += ".publishnewbtn a:active {";
  body += "box-shadow: none;";
  body += "top: 5px;";
	body +="}";
	body +=".publishnewbtn{";
  body +="margin-top: 3%;";
  body +="margin-left: 43%;";
	body +="}";
	body += ".filter {";
  body += "width: 190px;";
  body += "box-sizing: border-box;";
  body += "border: 2px solid #aaa;";
 	body += "border-radius: 4px;";
 	body += "font-size: 16px;";
 	body += "background-color: white;";
 	body += "background-position: 10px 10px; ";
 	body += "background-repeat: no-repeat;";
 	body += "padding: 12px 20px 12px 40px;";
  body += "transition: width 0.7s ease-in-out;";
  body += "color:black;";
	body += "}";
	body += ".filter:focus {";
 	body += " width: 30%;";
	body += "}";
	body += ".filterbtn{";
  body += "background-color:#19bc93;";
  body += "border-radius: 4px;";
  body += "border:none;";
  body += "padding: 12px 26px;";
	body += "}";
	body += "</style>";
	body += "</head>";
	body += "<body>";
	body += "<ul class='nav'>";
	body += "<li><a class='active' href='/publishershomefilter'>Home</a></li>";
	body += "<li><a href='/profile'>Profile</a></li>";
	body += "<li><a href='/signup'>Signup</a></li>";
	body += "<li class='exit'><a href='/login'>Logout</a></li>";
	body += "</ul>";
	body += "<p>Search for film by id:</p>";
	body += "<form action='/detailoffilm' method = 'POST'>";
	body += "<input type='text' name='film_id' placeholder='Enter film id' class='filter'>";
	body += "<button type='submit' class='filterbtn'>Search</button>";
	body += "</form>";
	body += "<hr>";
	body += "<h2>Published films up to now:</h2>";
	body += "<form action='/publishershomefilter' method = 'POST'>";
	body += "<p>Filter by director name:</p><br>";
	body += "<input type='text' name='director' placeholder='Enter director' class='filter'>";
	body += "<button type='submit' class='filterbtn'>Filter</button>";
	body += "</form>";
	body += "<hr>";
	body += "<table id='filmtable'>";
	body += "<tr>";
  body += "<th>Name</th>";
  body += "<th>Length</th> ";
  body += "<th>Price</th>";
  body += "<th>Rate</th>";
  body += "<th>Year</th>";
  body += "<th>Director</th>";
  body += "<th>Delete Button</th>";
  body += "</tr>";
	for(unsigned int i = 0 ; i < published_films.size() ; i++)
	{
		body += "<tr>";
		for(int j = 0 ; j < 6 ; j++)
		{
			body += "<td>";
			body += published_films[i][j];
			body += "</td>";
		}
		body += "<td>";
		body += "<form method='POST' action='/publishershome'>";
		body += "<input type='hidden' name='film_id' value='";
		body += published_films[i][7];
		body += "'/>";
		body += "<button type='submit' class='deletebtn'>Delete</button>";
		body += "</form>";
		body += "</td>";
		body += "</tr>";
	}
	body += "</table>";
	body += "<div class='publishnewbtn'><a href='/publishnewfilm'>Publish new</a></div>";
	body += "</body>";
	body += "</html>";
	res -> setBody(body);
	return res;
}

Response *AllowedFilmListHandler::callback(Request *req)
{
	Response *res = new Response;
	vector<vector < string > > allowedfilms = network->get_allowed_films("");
	res -> setHeader("Content-Type","text/html");
	string body;
	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<head>";
	body += "<style>";
	body += ".nav";
	body += "{";
	body += "  list-style-type: none;";
	body += "  margin: 0;";
	body += "  padding: 0;";
	body += "  overflow: hidden;";
	body += "  background-color: #333;";
	body += "  position: -webkit-sticky;";
	body += "  position: sticky;";
	body += "  top: 0;";
	body += "}";
	body += ".nav li";
	body += "{";
	body += "  float: left;";
	body += "  width:10%;";
	body += "}";
	body += ".nav li a";
	body += "{";
	body += "  display: block;";
	body += "  color: white;";
	body += "  text-align: center;";
	body += "  padding: 14px 16px;";
	body += "  text-decoration: none;";
	body += "	font-size: 14px;";
	body += "}";
	body += ".nav li a:hover";
	body += "{";
	body += "  background-color: #111;";
	body += "}";
	body += ".active";
	body += "{";
	body += "  background-color: #4CAF50;";
	body += "}";
	body += ".nav .exit";
	body += "{";
	body += "  background-color: #ff5050;";
	body += "  float: right;";
	body += "  width:12%;";
	body += "}";
	body += "#filmtable {";
	body += "border-collapse: collapse;";
	body += "width: 100%;";
	body += "}";
	body += "#filmtable th,#filmtable td {";
	body += "padding: 8px;";
	body += "text-align: left;";
	body += "border-bottom: 1px solid #ddd;";
	body += "}";
	body += "#filmtable tr:hover {background-color:#f5f5f5;}";
	body += ".filter {";
  body += "width: 190px;";
  body += "box-sizing: border-box;";
  body += "border: 2px solid #aaa;";
 	body += "border-radius: 4px;";
 	body += "font-size: 16px;";
 	body += "background-color: white;";
 	body += "background-position: 10px 10px; ";
 	body += "background-repeat: no-repeat;";
 	body += "padding: 12px 20px 12px 40px;";
  body += "transition: width 0.7s ease-in-out;";
  body += "color:black;";
	body += "}";
	body += ".filter:focus {";
 	body += " width: 30%;";
	body += "}";
	body += ".filterbtn{";
  body += "background-color:#19bc93;";
  body += "border-radius: 4px;";
  body += "border:none;";
  body += "padding: 12px 26px;";
	body += "}";
	body += "</style>";
	body += "</head>";
	body += "<body>";
	body += "<ul class='nav'>";
	body += "<li><a class='active' href='/customershome'>Home</a></li>";
	body += "<li><a href='/profile'>Profile</a></li>";
	body += "<li><a href='/signup'>Signup</a></li>";
	body += "<li class='exit'><a href='/login'>Logout</a></li>";
	body += "</ul>";
	body += "<h2>You can buy these films:</h2>";
	body += "<form action='/customershomefilter' method='POST'>";
	body += "<h2>Filter by director name:</h2><br>";
	body += "<input type='text' name='director' placeholder='Enter director' class='filter'>";
	body += "<button type='submit'class='filterbtn'>Filter</button>";
	body += "</form>";
	body += "<hr>";
	body += "<table id='filmtable'>";
	body += "<tr>";
  body += "<th>Name</th>";
  body += "<th>Length</th> ";
  body += "<th>Price</th>";
  body += "<th>Rate</th>";
  body += "<th>Year</th>";
  body += "<th>Director</th>";
  body += "</tr>";
	for(unsigned int i = 0 ; i < allowedfilms.size() ; i++)
	{
		body += "<tr>";
		for(int j = 0 ; j < 6 ; j++)
		{
			body += "<td>";
			body += allowedfilms[i][j];
			body += "</td>";
		}
		body += "</tr>";
	}
	body += "</table>";
	body += "</body>";
	body += "</html>";
	res -> setBody(body);
	return res;
}

Response *AllowedFilterFilmListHandler::callback(Request *req)
{
	Response *res = new Response;
	vector<vector < string > > allowedfilms = network->get_allowed_films(req->getQueryParam("director"));
	res -> setHeader("Content-Type","text/html");
	string body;
	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<head>";
	body += "<style>";
	body += ".nav";
	body += "{";
	body += "  list-style-type: none;";
	body += "  margin: 0;";
	body += "  padding: 0;";
	body += "  overflow: hidden;";
	body += "  background-color: #333;";
	body += "  position: -webkit-sticky;";
	body += "  position: sticky;";
	body += "  top: 0;";
	body += "}";
	body += ".nav li";
	body += "{";
	body += "  float: left;";
	body += "  width:10%;";
	body += "}";
	body += ".nav li a";
	body += "{";
	body += "  display: block;";
	body += "  color: white;";
	body += "  text-align: center;";
	body += "  padding: 14px 16px;";
	body += "  text-decoration: none;";
	body += "	font-size: 14px;";
	body += "}";
	body += ".nav li a:hover";
	body += "{";
	body += "  background-color: #111;";
	body += "}";
	body += ".active";
	body += "{";
	body += "  background-color: #4CAF50;";
	body += "}";
	body += ".nav .exit";
	body += "{";
	body += "  background-color: #ff5050;";
	body += "  float: right;";
	body += "  width:12%;";
	body += "}";
	body += "#filmtable {";
	body += "border-collapse: collapse;";
	body += "width: 100%;";
	body += "}";
	body += "#filmtable th,#filmtable td {";
	body += "padding: 8px;";
	body += "text-align: left;";
	body += "border-bottom: 1px solid #ddd;";
	body += "}";
	body += "#filmtable tr:hover {background-color:#f5f5f5;}";
	body += ".filter {";
  body += "width: 190px;";
  body += "box-sizing: border-box;";
  body += "border: 2px solid #aaa;";
 	body += "border-radius: 4px;";
 	body += "font-size: 16px;";
 	body += "background-color: white;";
 	body += "background-position: 10px 10px; ";
 	body += "background-repeat: no-repeat;";
 	body += "padding: 12px 20px 12px 40px;";
  body += "transition: width 0.7s ease-in-out;";
  body += "color:black;";
	body += "}";
	body += ".filter:focus {";
 	body += " width: 30%;";
	body += "}";
	body += ".filterbtn{";
  body += "background-color:#19bc93;";
  body += "border-radius: 4px;";
  body += "border:none;";
  body += "padding: 12px 26px;";
	body += "}";
	body += "</style>";
	body += "</head>";
	body += "<body>";
	body += "<ul class='nav'>";
	body += "<li><a class='active' href='/customershomefilter'>Home</a></li>";
	body += "<li><a href='/profile'>Profile</a></li>";
	body += "<li><a href='/signup'>Signup</a></li>";
	body += "<li class='exit'><a href='/login'>Logout</a></li>";
	body += "</ul>";
	body += "<h2>You can buy these films:</h2>";
	body += "<form action='/customershomefilter' method='POST'>";
	body += "<h2>Filter by director name:</h2><br>";
	body += "<input type='text' name='director' placeholder='Enter director' class='filter'>";
	body += "<button type='submit'class='filterbtn'>Filter</button>";
	body += "</form>";
	body += "<hr>";
	body += "<table id='filmtable'>";
	body += "<tr>";
  body += "<th>Name</th>";
  body += "<th>Length</th> ";
  body += "<th>Price</th>";
  body += "<th>Rate</th>";
  body += "<th>Year</th>";
  body += "<th>Director</th>";
  body += "</tr>";
	for(unsigned int i = 0 ; i < allowedfilms.size() ; i++)
	{
		body += "<tr>";
		for(int j = 0 ; j < 6 ; j++)
		{
			body += "<td>";
			body += allowedfilms[i][j];
			body += "</td>";
		}
		body += "</tr>";
	}
	body += "</table>";
	body += "</body>";
	body += "</html>";
	res -> setBody(body);
	return res;
}

Response *BoughtFilmListHandler::callback(Request *req)
{
	Response *res = new Response;
	vector<vector < string > > boughtfilms = network->get_purchased(req->getQueryParam("director"));
	res -> setHeader("Content-Type","text/html");
	string body;
	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<head>";
	body += "<style>";
	body += ".nav";
	body += "{";
	body += "  list-style-type: none;";
	body +="   margin: 0;";
	body +="   padding: 0;";
	body +="   overflow: hidden;";
	body +="   background-color: #333;";
	body += "  position: -webkit-sticky;";
	body +="   position: sticky;";
	body +="   top: 0;";
	body += "}";
	body += ".nav li";
	body += "{";
	body +="   float: left;";
	body +="   width:10%;";
	body += "}";
	body += ".nav li a";
	body += "{";
	body +="   display: block;";
	body +="  color: white;";
	body +="   text-align: center;";
	body +="   padding: 14px 16px;";
	body +="   text-decoration: none;";
	body +=" 	font-size: 14px;";
	body += "}";
	body += ".nav li a:hover";
	body += "{";
	body +="   background-color: #111;";
	body += "}";
	body += ".active";
	body += "{";
	body +="   background-color: #4CAF50;";
	body += "}";
	body += ".nav .exit";
	body += "{";
	body +="   background-color: #ff5050;";
	body +="   float: right;";
	body +="   width:12%;";
	body += "}";
	body += "#filmtable {";
	body += "border-collapse: collapse;";
	body += "width: 100%;";
	body += "}";
	body += "#filmtable th,#filmtable td {";
	body += "padding: 8px;";
	body += "text-align: left;";
	body += "border-bottom: 1px solid #ddd;";
	body += "}";
	body += "#filmtable tr:hover {background-color:#f5f5f5;}";
	body += ".charge {";
  body += "width: 190px;";
  body += "box-sizing: border-box;";
  body += "border: 2px solid #aaa;";
 	body += "border-radius: 4px;";
 	body += "font-size: 16px;";
 	body += "background-color: white;";
 	body += "background-position: 10px 10px; ";
 	body += "background-repeat: no-repeat;";
 	body += "padding: 12px 20px 12px 40px;";
  body += "transition: width 0.7s ease-in-out;";
  body += "color:black;";
	body += "}";
	body += ".charge:focus {";
 	body += " width: 30%;";
	body += "}";
	body += ".chargebtn{";
  body += "background-color:#19bc93;";
  body += "border-radius: 4px;";
  body += "border:none;";
  body += "padding: 12px 26px;";
	body += "}";
	body += "</style>";
	body += "</head>";
	body += "<body>";
	body += "<ul class='nav'>";
	body += "<li><a class='active' href='";
	if(network->get_is_active_publisher())
		body += "/publishershome'>Home</a></li>";
	else
		body += "/customershome'>Home</a></li>";
	body += "<li><a href='/profile'>Profile</a></li>";
	body += "<li><a href='/signup'>Signup</a></li>";
	body += "<li class='exit'><a href='/login'>Logout</a></li>";
	body += "</ul>";
	body += "<h2>You can buy these films:</h2>";
	body += "<hr>";
	body += "<table id='filmtable'>";
	body += "<tr>";
  body += "<th>Name</th>";
  body += "<th>Length</th> ";
  body += "<th>Price</th>";
  body += "<th>Rate</th>";
  body += "<th>Year</th>";
  body += "<th>Director</th>";
  body += "</tr>";
	for(unsigned int i = 0 ; i < boughtfilms.size() ; i++)
	{
		body += "<tr>";
		for(int j = 0 ; j < 6 ; j++)
		{
			body += "<td>";
			body += boughtfilms[i][j];
			body += "</td>";
		}
		body += "</tr>";
	}
	body += "</table>";
	body += "<hr>";
	body += "<p>Your money in network is: <b>";
	body += to_string(network->get_all_money_of_current_user());
	body += "</b></p><hr>";
	body += "<form action='/profile' method='POST'>";
	body += "<h2>Do you want to charge your account?</h2><br>";
	body += "<input type='text' name='money' placeholder='Enter amount of money' class='charge'>";
	body += "<button type='submit' class='chargebtn'>Charge</button>";
	body += "<hr>";
	body += "</form>";
	body += "</body>";
	body += "</html>";
	res -> setBody(body);
	return res;
}

Response* DetailFilmHandler :: callback(Request *req)
{
	vector<string> details_and_recomms = network->show_dateils_of_movie(stoi(req->getQueryParam("film_id")));
	Response *res = new Response;
	res -> setHeader("Content-Type","text/html");
	string body;
	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<head>";
	body += "<style>";
	body += ".nav";
	body += "{";
	body += "  list-style-type: none;";
	body += "  margin: 0;";
	body += "  padding: 0;";
	body += "  overflow: hidden;";
	body += "  background-color: #333;";
	body += "  position: -webkit-sticky;";
	body += "  position: sticky;";
	body += "  top: 0;";
	body += "}";
	body += ".nav li";
	body += "{";
	body += "  float: left;";
	body += "  width:10%;";
	body += "}";
	body += ".nav li a";
	body += "{";
	body += "  display: block;";
	body += "  color: white;";
	body += "  text-align: center;";
	body += "  padding: 14px 16px;";
	body += "  text-decoration: none;";
	body += "	font-size: 14px;";
	body += "}";
	body += ".nav li a:hover";
	body += "{";
	body += "  background-color: #111;";
	body += "}";
	body += ".active";
	body += "{";
	body += "  background-color: #4CAF50;";
	body += "}";
	body += ".nav .exit";
	body += "{";
	body += "  background-color: #ff5050;";
	body += "  float: right;";
	body += "  width:12%;";
	body += "}";
	body += ".filmtable {";
	body += "border-collapse: collapse;";
	body += "width: 100%;";
	body += "}";
	body += ".filmtable th,.filmtable td {";
	body += "padding: 8px;";
	body += "text-align: left;";
	body += "border-bottom: 1px solid #ddd;";
	body += "}";
	body += ".filmtable tr:hover {background-color:#f5f5f5;}";
	body += ".btn{";
	body += "padding: 12px 28px;";
	body += "background-color: #008CBA;";
	body += "border: none;";
	body += "border-radius: 9%;";
	body += "}";
	body += ".btn:hover{";
	body +=	"background-color: #55CFF8;";
	body += "}";
	body += "</style>";
	body += "</head>";
	body += "<body>";
	body += "<ul class='nav'>";
	body += "<li><a class='active' href='";
	if(network->get_is_active_publisher())
		body += "/publishershome'>Home</a></li>";
	else
		body += "/customershome'>Home</a></li>";
	body += "<li><a href='/profile'>Profile</a></li>";
	body += "<li><a href='/signup'>Signup</a></li>";
	body += "<li class='exit'><a href='/login'>Logout</a></li>";
	body += "</ul>";
	body += "<h2>You can buy these films:</h2>";
	body += "<hr>";
	body += "<table class='filmtable'>";
	body += "<tr>";
  body += "<th>Name</th>";
  body += "<th>Length</th> ";
  body += "<th>Director</th>";
  body += "<th>Price</th>";
  body += "<th>Rate</th>";
  body += "<th>Yaer</th>";
  body += "<th>Summary</th>";
  body += "</tr>";
  body += "<tr>";
	for(int i = 0 ; i < 7 ; i++)
	{
		body += "<td>";
		body += details_and_recomms[i];
		body += "</td>";
	}
	body += "</tr></table><hr>";
	body += "<h2>We recommand these films to you:</h2>";
	body += "<table class='filmtable'>";
	body += "<tr>";
  body += "<th>Name</th>";
  body += "<th>Length</th> ";
  body += "<th>Director</th>";
  body += "<th>Details</th>";
  body += "<th>Buy</th>";
  body += "</tr>";
	for(unsigned int i = 7 ; i < details_and_recomms.size() ; i = i + 4)
	{
		body += "<tr>";
		body += "<td>";
		body += details_and_recomms[i];
		body += "</td>";
		body += "<td>";
		body += details_and_recomms[i+1];
		body += "</td>";
		body += "<td>";
		body += details_and_recomms[i+2];
		body += "</td>";
		body += "<td>";
		body += "<form method='POST' action='/detailoffilm'>";
		body += "<input type='hidden' name='film_id' value='";
		body += details_and_recomms[i+3];
		body += "'/>";
		body += "<button type='submit' class = 'btn'>Details</button>";
		body += "</form>";
		body += "</td>";
		body += "<td>";
		body += "<form method='POST' action='/rate'>";
		body += "<input type='hidden' name='film_id' value='";
		body += details_and_recomms[i+3];
		body += "'/>";
		body += "<button type='submit' class = 'btn'>Buy</button>";
		body += "</form>";
		body += "</td>";
		body += "</tr>";
	}
	body += "</table>";
	body += "<hr>";
	body += "</body>";
	body += "</html>";
	res -> setBody(body);
	return res;

}

Response* BuyFilmHandler :: callback(Request *req)
{
	string id = req->getQueryParam("film_id");
	network->buy_film(stoi(id));
	Response* res = Response::redirect("/rate");
	return res;
}

Response* ScoreFilmHandler :: callback(Request *req)
{
	Response *res = new Response;
	res -> setHeader("Content-Type","text/html");
	string body;
	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<head>";
	body += "<style>";
	body += ".nav";
	body += "{";
	body += "  list-style-type: none;";
	body += "  margin: 0;";
	body += "  padding: 0;";
	body += "  overflow: hidden;";
	body += "  background-color: #333;";
	body += "  position: -webkit-sticky;";
	body += "  position: sticky;";
	body += "  top: 0;";
	body += "}";
	body += ".nav li";
	body += "{";
	body += "  float: left;";
	body += "  width:10%;";
	body += "}";
	body += ".nav li a";
	body += "{";
	body += "  display: block;";
	body += "  color: white;";
	body += "  text-align: center;";
	body += "  padding: 14px 16px;";
	body += "  text-decoration: none;";
	body += "	font-size: 14px;";
	body += "}";
	body += ".nav li a:hover";
	body += "{";
	body += "  background-color: #111;";
	body += "}";
	body += ".active";
	body += "{";
	body += "  background-color: #4CAF50;";
	body += "}";
	body += ".nav .exit";
	body += "{";
	body += "  background-color: #ff5050;";
	body += "  float: right;";
	body += "  width:12%;";
	body += "}";
	body += ".btn{";
	body += "padding: 12px 28px;";
	body += "background-color: #008CBA;";
	body += "border: none;";
	body += "border-radius: 9%;";
	body += "}";
	body += ".btn:hover{";
	body +=	"background-color: #55CFF8;";
	body += "}";
	body += "</style>";
	body += "</head>";
	body += "<body>";
	body += "<ul class='nav'>";
	body += "<li><a class='active' href='";
	if(network->get_is_active_publisher())
		body += "/publishershome'>Home</a></li>";
	else
		body += "/customershome'>Home</a></li>";
	body += "<li><a href='/profile'>Profile</a></li>";
	body += "<li><a href='/signup'>Signup</a></li>";
	body += "<li class='exit'><a href='/login'>Logout</a></li>";
	body += "</ul>";
	body += "<p>Rate this film: </p><hr>";
	body += "<form action='/rate'>";
	body += "<input type='hidden' name='film_id' value='";
	body += req->getQueryParam("film_id");
	body += "'>";
	body += "<input type='text' name='rate' placeholder='Enter score'>";
	body += "<button type='submit' class='btn'>Charge</button>";
	body += "</form>";
	body += "</body>";
	body += "</html>";
	res -> setBody(body);
	return res;
}

Response* RateFilmHandler :: callback(Request *req)
{
	Response *res = new Response;
	string rate = req->getQueryParam("rate");
	string id = req ->getQueryParam("film_id");
	network -> rate_a_film(stoi(rate),stoi(id));
	if(network -> get_is_active_publisher())
		res = Response :: redirect("/publishershome");
	else
		res = Response :: redirect("/customershome");
	return res;
}