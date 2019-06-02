CC = g++ --std=c++11
all : filmnetwork.out

filmnetwork.out:main.o Comment.o Customer.o Exception.o Film.o Network.o Publisher.o Sha256.o
	${CC} main.o Comment.o Customer.o Exception.o Film.o Network.o Publisher.o Sha256.o -o filmnetwork.out

main.o: Exception.h	Network.h main.cpp
	${CC} -c main.cpp -o main.o

Comment.o:Comment.h Comment.cpp
	${CC} -c Comment.cpp -o Comment.o

Customer.o:Film.h Customer.h Customer.cpp
	${CC} -c Customer.cpp -o Customer.o

Exception.o:Exception.h Exception.cpp
	${CC} -c Exception.cpp -o Exception.o

Film.o:Film.h Comment.h Exception.h Film.cpp
	${CC} -c Film.cpp -o Film.o

Network.o:Network.h Publisher.h Customer.h Exception.h Sha256.h Film.h Network.cpp
	${CC} -c Network.cpp -o Network.o

Publisher.o:Publisher.h Customer.h Publisher.cpp
	${CC} -c Publisher.cpp -o Publisher.o

Sha256.o:Sha256.h Sha256.cpp
	${CC} -c Sha256.cpp -o Sha256.o

.PHONY: clean
clean:
	rm *.o
	rm filmnetwork.out