CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lpthread -lgtest

USER=User.cpp UserManage.cpp
MEETING=Meeting.cpp MeetingManage.cpp
DATE=Date.cpp
FILE=FileManage.cpp
AGENDA=AgendaService.cpp AgendaController.cpp Agenda.cpp
CODE=Encode.cpp

SOURCES=$(USER) $(MEETING) $(DATE) $(FILE) $(AGENDA) $(CODE)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=a.out

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
