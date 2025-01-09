
output: main.o MotorControl.o
	g++ main.o MotorControl.o -o output

main.o: main.cpp
	g++ -c main.cpp

MotorControl.o: MotorControl.cpp MotorControl.hpp
	g++ -c  MotorControl.cpp

clean:
	rm *.o output