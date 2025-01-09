/**This library was made for purpose of comfortable using
and working with DC motors

    In order to add new engine simply create new object by example:
    DC_Motor::Control Engine_number(pin_number,"name");

    !!uncomment 26 line for flow direction pin usage!!
    !!DC_Motor::Control Engine_number(pin_number,flow_dir_pin_nr,"name");!!

Steiring is implemented in such way that;
    - providing a +value will result in engine rotating clockwise
    - providing a -value will result in engine rotating anticlockwise
    - providing a null will result stopping engine

Also library provides tools for converting specified outputs to easier transfer of data Via
network sockets
*/
#ifndef MOTORCONTROLL_HPP
#define MOTORCONTROLL_HPP

#pragma once
#include <iostream>
#include <string.h>
#include <vector>
#include <cctype>
#include <sstream>
#include <iterator>

#define FLOW_DIR_PIN 5 /// uncomment if using flow direction pin for rotating both clockwise & anticlockwise

namespace DC_Motor /// name DC_Motor namespace
{
    class Control
    {
    private:
        __INT16_TYPE__ m_level{};

    public:
        __INT16_TYPE__ get_Level() const;
        void set_Level(__INT16_TYPE__ val);

        bool operator==(const Control &other) const
        {
            return m_level == other.m_level;
        }

        Control();
        ~Control();
    };

    class Initialize : public Control
    {
    private:
        __UINT16_TYPE__ m_pin;
        std::string m_name;

#ifdef FLOW_DIR_PIN
        __UINT16_TYPE__ m_FLOW_DIR_PIN;
#endif

    public:
        __UINT16_TYPE__ pin{};
        std::string name{};

#ifdef FLOW_DIR_PIN
        //__UINT16_TYPE__ &flow_Dir_Pin =  m_FLOW_DIR_PIN;
        __UINT16_TYPE__ flow_Dir_Pin{};
        Initialize(__UINT16_TYPE__ pin, __UINT16_TYPE__ flow_direction_pin, std::string name);
#endif

        __INT16_TYPE__ read_PWR() const;
        __UINT16_TYPE__ get_Pin() const;
        void set_Name(std::string temp_name);
        std::string get_Name() const;

#ifndef FLOW_DIR_PIN
        Initialize(__UINT16_TYPE__ pin, std::string name);
#endif
        Initialize();
        ~Initialize();
    };

    void printEngineData(Initialize &x);
    float outputConvert(float refVoltage, float level);
    std::string stringFromLevels(Initialize &x);
    std::string stringFromLevels(Initialize &x, Initialize &y);
    std::string stringFromLevels(Initialize &x, Initialize &y, Initialize &z);
    std::string stringFromLevels(Initialize &x, Initialize &y, Initialize &z, Initialize &q);
    std::string inputToString();
    void stringToInt(char str[], std::vector<int> &vecOfInts);
    void stringToInt(std::string str, std::vector<int> &vecOfInts);

}
#endif