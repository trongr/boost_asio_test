CC = g++
CFLAGS = -g -Wall
INCLUDES = -I/Users/admin/boost_1_61_0
LFLAGS = -L/Users/admin/boost_1_61_0/stage/lib
LIBS = -lboost_system -lboost_thread
MAIN = main
DEPS =
SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp,obj/%.o,$(SRCS))
POST = install_name_tool -change libboost_system.dylib \
	~/boost_1_61_0/stage/lib/libboost_system.dylib $(MAIN)

$(MAIN): build $(OBJS) $(DEPS)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS)
	$(POST)

obj/%.o: src/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDES)

build:
	@mkdir -p obj

.PHONY: clean
clean:
	rm -rf $(MAIN) obj *~
