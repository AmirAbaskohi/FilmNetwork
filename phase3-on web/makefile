CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: source/handlers.cpp source/Network.h server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c source/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: source/my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c source/my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: source/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c source/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/Comment.o: source/Comment.h source/Comment.cpp
	$(CC) $(CF) -c source/Comment.cpp -o $(BUILD_DIR)/Comment.o

$(BUILD_DIR)/Customer.o: source/Film.h source/Customer.h source/Customer.cpp
	$(CC) $(CF) -c source/Customer.cpp -o $(BUILD_DIR)/Customer.o

$(BUILD_DIR)/Exception.o: source/Exception.h source/Exception.cpp
	$(CC) $(CF) -c source/Exception.cpp -o $(BUILD_DIR)/Exception.o

$(BUILD_DIR)/Film.o: source/Film.h source/Comment.h source/Exception.h source/Film.cpp
	$(CC) $(CF) -c source/Film.cpp -o $(BUILD_DIR)/Film.o

$(BUILD_DIR)/Sha256.o: source/Sha256.h source/Sha256.cpp
	$(CC) $(CF) -c source/Sha256.cpp -o $(BUILD_DIR)/Sha256.o

$(BUILD_DIR)/Publisher.o: source/Publisher.h source/Customer.h source/Publisher.cpp
	$(CC) $(CF) -c source/Publisher.cpp -o $(BUILD_DIR)/Publisher.o

$(BUILD_DIR)/Network.o: source/Network.h source/Publisher.h source/Customer.h source/Exception.h source/Sha256.h source/Film.h source/Network.cpp
	$(CC) $(CF) -c source/Network.cpp -o $(BUILD_DIR)/Network.o

myserver.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/Comment.o $(BUILD_DIR)/Customer.o $(BUILD_DIR)/Exception.o $(BUILD_DIR)/Film.o $(BUILD_DIR)/Network.o $(BUILD_DIR)/Publisher.o $(BUILD_DIR)/Sha256.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o  $(BUILD_DIR)/Comment.o $(BUILD_DIR)/Customer.o $(BUILD_DIR)/Exception.o $(BUILD_DIR)/Film.o $(BUILD_DIR)/Network.o $(BUILD_DIR)/Publisher.o $(BUILD_DIR)/Sha256.o -o myserver.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
