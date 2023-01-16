all: BeaconFlood
main.o : main.cpp
BeaconFlood : main.o -ltins
	$(LINK.cc) $^  $(LDLIBS) -o $@

clean:
	rm -f BeaconFlood *.o