all: main
main.o : main.cpp
main : main.o -ltins
	$(LINK.cc) $^  $(LDLIBS) -o $@

clean:
	rm -f main *.o