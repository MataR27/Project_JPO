#include "MotorControl.hpp"
namespace DC_Motor
{
    /** \brief Fuctionality to set working value of engine
     *
     *  Functions reads the provided short int value and
     *  sets it to the coresponding engine
     *  @param val short int value
     *  @return functions does not return anything type: void
     */
    void Control::set_Level(__INT16_TYPE__ val = {})
    {
        m_level = val; //
    }
    /** \brief Fuctionality to get working value of engine
     *
     *  Functions reads the value of coresponding engine
     * and returns it
     *  @param  NULL none
     *  @return functions returns the value of type: short int
     */
    __INT16_TYPE__ Control::get_Level() const
    {
        return m_level;
    }

    Control::Control() {}
    Control::~Control() {}

    /** \brief Fuctionality to get binded pin of engine
     *
     *  Functions reads the pin number of engine
     * and returns it
     *  @param  NULL none
     *  @return functions returns the value of type: short int
     */
    __UINT16_TYPE__ Initialize::get_Pin() const
    {
        return m_pin;
    }

    /** \brief Fuctionality to set/reset the name of the engine
     *
     *  Functions reads the provided string and
     *  sets it as a name to the coresponding engine
     *  @param temp_name std::string
     *  @return functions does not return anything type: void
     */
    void Initialize::set_Name(std::string temp_name)
    {
        m_name = temp_name;
    }

    /** \brief Fuctionality to get the name of the engine
     *
     *  Functions reads the name of an engine
     * and returns it
     *  @param  NULL none
     *  @return functions returns the string of type: std::string
     */
    std::string Initialize::get_Name() const
    {
        return m_name;
    }
#ifdef FLOW_DIR_PIN

    /** \brief Fuctionality to read the value the engine based on direction flag
     *
     *  Functions reads the current power of an engine, then based on
     * value of the flag it returns the corresponding "-" or "+"" value
     * and returns it
     *  @param  NULL none
     *  @return functions returns the signed value type: short int
     */
    __INT16_TYPE__ Initialize::read_PWR() const
    {
        __INT16_TYPE__ val = Control::get_Level();
        if (Initialize::m_FLOW_DIR_PIN == 0)
        {
            return (val);
        }
        if (Initialize::m_FLOW_DIR_PIN == 1)
        {
            return (-val);
        }
        else
        {
            return 0;
        }
    }

    /** \brief Parametrized constructor of Initialize class with pin flag
     *
     *  Construcor when created is setting the listed things:
     *  @param  pin Pin that engines works at type: short int
     *  @param  flow_direction_pin Pin flag that is set for purpouse of relay control type: short int
     *  @param  name Set the name of engine type: std::string
     * @return  Prints "Initializing Engine: " message with corresponding engine name to stdout
     */
    Initialize::Initialize(__UINT16_TYPE__ pin, __UINT16_TYPE__ flow_direction_pin, std::string name) : m_pin(pin), m_FLOW_DIR_PIN(flow_direction_pin), m_name(name)
    {
        std::cout << "Initializing Engine: " << get_Name() << std::endl;
        std::cout << "Call set_Level() method to run the engine: " << std::endl;
    }
#endif
#ifndef FLOW_DIR_PIN
    /** \brief Parametrized constructor of Initialize class
     *
     *  Construcor when created is setting the listed things:
     *  @param  pin Pin that engines works at type: short int
     *  @param  name Set the name of engine type: std::string
     */
    Initialize::Initialize(__UINT16_TYPE__ pin, std::string name) : m_pin(pin), m_name(name)
    {
        std::cout << "Initializing Engine: " << get_Name() << std::endl;
    }
#endif
     /** \brief Constructor of Initialize class
     *
     *  Constructor of Initialize class:
     *  @param  NULL Does not take any parameters
     *  @return Prints "Created empty engine: "to stdout
     */
    Initialize::Initialize()
    {
        std::cout << "Created empty engine" << std::endl;
    }
    /** \brief Destructor of Initialize class
     *
     *  Destructor of Initialize class:
     *  @param  NULL Does not take any parameters
     *  @return Prints "Clearing Engine: " message with corresponding engine name to stdout
     */
    Initialize::~Initialize()
    {
        std::cout << "Clearing Engine: " << get_Name() << std::endl;
    }

    /** \brief Prints parameteres of specific engine
     *
     *  Prints parameteres in a Box listed here:
     *      Engine name: [name]
     *      Working pin: [value]
     *      Current level: [level]
     *      Memory value: [value]
     *  @param  x Enter the object name here
     *  @return  Prints Box with basic parameters od specific object/engine
     */
    void printEngineData(Initialize &x)
    {
        std::cout << "/---------------------------\\" << std::endl;
        std::cout << "|Engine name: " << x.get_Name() << std::endl;
        std::cout << "|Working pin: " << x.get_Pin() << std::endl;
        std::cout << "|Current level: " << x.get_Level() << std::endl;
        std::cout << "|Memory value: " << &x << std::endl;
        std::cout << "\\---------------------------/" << std::endl;
    }

    /** \brief Function to convert the value based on reference voltage
     *
     *  Function return the value based on reference voltage
     *  @param  refVoltage set reference Voltage
     *  @param  level set working level from range 0 : 100
     *  @return converted value type: float
     */
    float outputConvert(float refVoltage, float level)
    {
        if (level < 0 || level > 100)
        {
            throw std::invalid_argument("level was not from correct range");
            return 0;
        }
        else
        {
            return (refVoltage / 100) * level;
        }
    }

    /** \brief Function to convert level of engine to formated string[1/4]
     *
     *  Implementation up to 4 engines.
     *  Function to convert level of engine [1] to formated string
     *  @param  x place for 1st object/engine
     *  @return converted string formated: [level] type: std::string
     */
    std::string stringFromLevels(Initialize &x)
    {

        std::ostringstream oss;
        std::vector<__INT64_TYPE__> vecObjc(1, 0);
        vecObjc[0] = x.get_Level();
        std::copy(vecObjc.begin(), vecObjc.end() - 1, std::ostream_iterator<int>(oss, ","));
        oss << vecObjc.back();
        std::string str = "[" + oss.str() + "]";
        std::cout << "from in " << str << std::endl;
        return str;
    }

    /** \brief Function to convert level of engine to formated string[2/4]
     *
     *  Implementation up to 4 engines.
     *  Function to convert level of engine [2] to formated string
     *  @param  x place for 1st object/engine
     *  @param  y place for 2nd object/engine
     *  @return converted string formated: [level1,level2] type: std::string
     */
    std::string stringFromLevels(Initialize &x, Initialize &y)
    {

        std::ostringstream oss;
        std::vector<__INT64_TYPE__> vecObjc(2, 0);
        vecObjc[0] = x.get_Level();
        vecObjc[1] = y.get_Level();
        std::copy(vecObjc.begin(), vecObjc.end() - 1, std::ostream_iterator<int>(oss, ","));
        oss << vecObjc.back();
        std::string str = "[" + oss.str() + "]";
        std::cout << "from in " << str << std::endl;
        return str;
    }

    /** \brief Function to convert level of engine to formated string[3/4]
     *
     *  Implementation up to 4 engines.
     *  Function to convert level of engine [3] to formated string
     *  @param  x place for 1st object/engine
     *  @param  y place for 2nd object/engine
     *  @param  z place for 3rd object/engine
     *  @return converted string formated: [level1,level2,level3] type: std::string
     */
    std::string stringFromLevels(Initialize &x, Initialize &y, Initialize &z)
    {

        std::ostringstream oss;
        std::vector<__INT64_TYPE__> vecObjc(3, 0);
        vecObjc[0] = x.get_Level();
        vecObjc[1] = y.get_Level();
        vecObjc[2] = z.get_Level();
        std::copy(vecObjc.begin(), vecObjc.end() - 1, std::ostream_iterator<int>(oss, ","));
        oss << vecObjc.back();
        std::string str = "[" + oss.str() + "]";
        std::cout << "from in " << str << std::endl;
        return str;
    }

    /** \brief Function to convert level of engine to formated string[4/4]
     *
     *  Function to convert level of engine [4] to formated string
     *  @param  x place for 1st object/engine
     *  @param  y place for 2nd object/engine
     *  @param  z place for 3rd object/engine
     *  @param  q place for 4th object/engine
     *  @return converted string formated: [level1,level2,level3,level4] type: std::string
     */
    std::string stringFromLevels(Initialize &x, Initialize &y, Initialize &z, Initialize &q)
    {

        std::ostringstream oss;
        std::vector<__INT64_TYPE__> vecObjc(4, 0);
        vecObjc[0] = x.get_Level();
        vecObjc[1] = y.get_Level();
        vecObjc[2] = z.get_Level();
        vecObjc[3] = q.get_Level();
        std::copy(vecObjc.begin(), vecObjc.end() - 1, std::ostream_iterator<int>(oss, ","));
        oss << vecObjc.back();
        std::string str = "[" + oss.str() + "]";
        std::cout << "from in " << str << std::endl;
        return str;
    }

    /** \brief Function converts from stdin to string
     *
     *  Function converts from stdin to string
     *  Provide engine control levels in format: [LEVEL1,LEVEL2]
     *  For compatibility with stringToInt() function
     *  @param  NULL none
     *  @return resturns string from stdin type: std::string
     */
    std::string inputToString()
    {
        std::cout << "" << std::endl;
        std::string str;
        getline(std::cin, str);
        return str;
    }

    /** \brief Function converts from char tab to vector of intigers
     *
     *  Function converts from char tab to vector of intigers
     *  It reads char tab formated: [num1,num2,...,numX]
     *  and converts numbers one by one to vector
     *  @param[in] str char tab
     *  @param[out] vecOfInts vector of intigers
     *  @return Nothing overload of vecOfInts @param
     */
    void stringToInt(char str[], std::vector<int> &vecOfInts)
    {
        int size = strlen(str);
        int tempNum = 0;
        bool isNegative = false;

        for (int i = 0; i < size; i++)
        {
            if (str[i] == '[' || str[i] == ']')
            {
                continue;
            }
            if (str[i] == '-')
            {
                isNegative = true;
                continue;
            }
            if (str[i] >= '0' && str[i] <= '9')
            {
                tempNum = tempNum * 10 + (str[i] - '0'); /// ASCII generating
            }
            if (str[i] == ',')
            {
                vecOfInts.push_back(isNegative ? -tempNum : tempNum);
                tempNum = 0;
                isNegative = false;
            }
        }

        vecOfInts.push_back(isNegative ? -tempNum : tempNum);

        for (int i = 0; i < vecOfInts.size(); ++i)
        {
            std::cout << vecOfInts[i] << " ";
        }
        std::cout << std::endl;
    }

    /** \brief Function converts from string to vector of intigers
     *
     *  Function converts from string to vector of intigers
     *  It reads char tab formated: [num1,num2,...,numX]
     *  and converts numbers one by one to vector
     *  @param[in] str string
     *  @param[out] vecOfInts vector of intigers
     *  @return Nothing overload of vecOfInts @param
     */
    void stringToInt(std::string str, std::vector<int> &vecOfInts)
    {
        int size = str.size();
        int tempNum = 0;
        bool isNegative = false;

        for (int i = 0; i < size; i++)
        {
            if (str[i] == '[' || str[i] == ']')
            {
                continue;
            }
            if (str[i] == '-')
            {
                isNegative = true;
                continue;
            }
            if (str[i] >= '0' && str[i] <= '9')
            {
                tempNum = tempNum * 10 + (str[i] - '0');
            }
            if (str[i] == ',')
            {
                vecOfInts.push_back(isNegative ? -tempNum : tempNum);
                tempNum = 0;
                isNegative = false;
            }
        }

        vecOfInts.push_back(isNegative ? -tempNum : tempNum);

        for (int i = 0; i < vecOfInts.size(); ++i)
        {
            std::cout << vecOfInts[i] << " ";
        }
    }
}