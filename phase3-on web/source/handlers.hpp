#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include <iostream>

#include "../server/server.hpp"
#include "Network.h"

class LoginHandler : public RequestHandler {
public:
	LoginHandler(Network* net);
  Response *callback(Request *);
private:
	Network *network;
};

class SignUpHandler : public RequestHandler {
public:
	SignUpHandler(Network* net);
  Response *callback(Request *);
private:
	Network *network;
};

class PublishFilmHandler : public RequestHandler{
public:
	PublishFilmHandler(Network *net);
	Response *callback(Request *);
private:
	Network *network;
};

class DeleteFilm : public RequestHandler{
public:
	Response *callback(Request *);
private:
	Network *network;
};

class FilmListHandler : public RequestHandler{
public:
	FilmListHandler(Network* net);
	Response *callback(Request *);
private:
	Network *network;
};

class BoughtFilmListHandler : public RequestHandler{
public:
	BoughtFilmListHandler(Network *net);
	Response *callback(Request *);
private:
	Network *network;
};

class DetailFilmHandler : public RequestHandler{
public:
	DetailFilmHandler(Network *net);
	Response *callback(Request *);
private:
	Network *network;
};

class BuyFilmHandler : public RequestHandler{
public:
	BuyFilmHandler(Network *net);
	Response *callback(Request *);
private:
	Network *network;
};

class ScoreFilmHandler : public RequestHandler{
public:
	ScoreFilmHandler(Network *net);
	Response *callback(Request *);
private:
	Network *network;
};

class RateFilmHandler : public RequestHandler{
public:
	RateFilmHandler(Network *net);
	Response *callback(Request *);
private:
	Network *network;
};

#endif
