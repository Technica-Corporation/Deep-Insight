# g++ -std=c++11  -I snap-core/ -I glib-core/ -pthread -o CDeepWalk DeepWalk.cpp
CC =g++
CFLAGS = $(CC) -std=c++11  -I snap-core/ -I glib-core/ -pthread

CDeepWalk : DeepWalk.o TestDWC.o word2vec.o
	$(CFLAGS) DeepWalk.o TestDWC.o  snap-core/Snap.o word2vec.o -o CdeepWalk

TestDWC.o:TestDWC.cpp
	$(CFLAGS) -c TestDWC.cpp -o TestDWC.o

word2vec.o: word2vec.cpp word2vec.h
	$(CFLAGS) -c word2vec.cpp -o word2vec.o

DeepWalk.o: DeepWalk.cpp
	$(CFLAGS) -c DeepWalk.cpp -o DeepWalk.o

clean:
	rm *.o CdeepWalk



