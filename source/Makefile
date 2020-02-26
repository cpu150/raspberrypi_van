CC					:= g++ --std=c++11
CCFLAGS			:= -Wall
LDFLAGS 		:= -lbcm2835
DEBUGFLAGS	:= -DDEBUG

TARGETS	:= main
MAINS		:= $(addsuffix .o, $(TARGETS) )
OBJ			:= raspberrypi_gpio/Gpio.o Van.o $(MAINS)
DEPS		:=

.PHONY: all clean install uninstall

all: $(TARGETS)

debug: CCFLAGS += $(DEBUGFLAGS)
debug: $(TARGETS)

clean:
	rm -f $(TARGETS) $(OBJ)

install:
	sudo cp main /usr/local/bin/van
	sudo cp ../init.d/van /etc/init.d/
	sudo chmod 755 /etc/init.d/van
	sudo update-rc.d van defaults
	echo "To start the service manually: sudo /etc/init.d/van start"

uninstall:
	sudo /etc/init.d/van stop
	sudo rm /usr/local/bin/van
	sudo rm /etc/init.d/van
	sudo update-rc.d -f van remove

$(OBJ): %.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGETS): % : $(filter-out $(MAINS), $(OBJ)) %.o
	$(CC) -o $@ $^ $(CCFLAGS) $(LDFLAGS)
