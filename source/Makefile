CC              := g++ --std=c++11
CCFLAGS         := -Wall
LDFLAGS         := -lbcm2835
DEBUGFLAGS      := -DDEBUG

TARGETS         := main
MAINS           := $(addsuffix .o, $(TARGETS) )
OBJ             := raspberrypi_gpio/Gpio.o Van.o $(MAINS)
DEPS            :=

INSTALL_BIN     := van
INSTALL_PATH    := /usr/local/bin/$(INSTALL_BIN)
LOG_OUT         := /var/log/van.log
LOG_ERR         := /var/log/van_err.log
CRONJOB         := @reboot /usr/local/bin/van >>$(LOG_OUT) 2>>$(LOG_ERR)

.PHONY: all clean install uninstall

all: $(TARGETS)

debug: CCFLAGS += $(DEBUGFLAGS)
debug: $(TARGETS)

clean:
	rm -f $(TARGETS) $(OBJ)

install:
	sudo cp $(TARGETS) $(INSTALL_PATH)
	sudo touch $(LOG_OUT) ; sudo touch $(LOG_ERR)
	sudo crontab -l | { cat; echo "$(CRONJOB)"; } | sudo crontab -
	echo "Reboot required"

uninstall:
	sudo killall $(INSTALL_BIN)
	sudo rm $(INSTALL_PATH)
	sudo crontab -l | grep -v -F "$(CRONJOB)" | sudo crontab -

$(OBJ): %.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGETS): % : $(filter-out $(MAINS), $(OBJ)) %.o
	$(CC) -o $@ $^ $(CCFLAGS) $(LDFLAGS)
