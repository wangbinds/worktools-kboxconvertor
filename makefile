TARGET=KeyboxConvertor
CFLAGS=-Wall -O -g

$(TARGET) : main.o keybox.o
	g++ main.o keybox.o -o $(TARGET)

main.o : main.cpp keybox.h
	g++ $(CFLAGS) -c main.cpp -o main.o

keybox.o : keybox.cpp keybox.h
	g++ $(CFLAGS) -c keybox.cpp -o keybox.o

clean:
	rm -rf *.o $(TARGET) *.csv
