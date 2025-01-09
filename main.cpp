#include "MotorControl.hpp"

int main()
{
   // Creating of few objects
   DC_Motor::Initialize test1(1, 1, "uno");

   // split of set_level func out of construct for safety reasons
   test1.set_Level(75);
   DC_Motor::Initialize test2(2, 1, "dos");
   test2.set_Level(-50);
   DC_Motor::Initialize test3(3, 0, "tres");
   test3.set_Level(24);
   DC_Motor::Initialize test4(4, 1, "cuatro");
   test4.set_Level(24);

   // get pin check
   std::cout << "pin" << test2.get_Pin() << std::endl;

   std::cout << test2.get_Level() << std::endl;
   std::cout << test2.read_PWR() << std::endl;

   // check all provided data
   printEngineData(test4);

   // preparation of data to transfer
   char data1[] = "[23,94,-89,-2,3]";
   // creation of vector that will contain valus on client side
   std::vector<int> vi;
   // encapsulating data from string to vector
   DC_Motor::stringToInt(data1, vi);
   std::cout << "data1: " << data1;

   // reading data from objects and preparing another data to send
   std::string senddata = stringFromLevels(test1, test2, test3, test4);
   std::vector<int> jinx;
   DC_Motor::stringToInt(senddata, jinx);

   std::cout << "senddata test: " << senddata << std::endl;

   // test of simple converter for microcontroller usage
   std::cout << DC_Motor::outputConvert(5.0, 99.0) << std::endl;

   std::cout << "test: " << std::endl;

   // comparison of values from different engines (hard to overload anything more to this project)
   bool x;
   x = test1 == test2;
   std::cout << "trueornot 1&2: " << x << std::endl;
   x = test3 == test4;
   std::cout << "trueornot 3&4: " << x << std::endl;
   return 0;
}
