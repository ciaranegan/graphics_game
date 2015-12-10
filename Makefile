EXECUTABLE = run_game
CC = g++
CFLAGS = `pkg-config glfw3 --cflags` `pkg-config glew --cflags` -I ./include -g
LDFLAGS= `pkg-config glfw3 --static --libs` `pkg-config glew --libs`
SOURCES = arrow.cpp game_project.cpp obj_parser.cpp mesh.cpp ball.cpp level.cpp bomb.cpp game.cpp level_loader.cpp text.cpp hud.cpp

OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)

${EXECUTABLE}: ${OBJECTS}
	${CC} ${OBJECTS} -o $@ ${LDFLAGS}

.cpp.o:
	${CC} ${CFLAGS} -c $< -o $@