#include "Converter.hpp"

Converter::Converter()
{
    throw std::runtime_error("invalid constructor call");
}

Converter::Converter(const std::string &input) : input_(input)
{
    parse();
}

Converter::Converter(const Converter &converter)
{
    *this = converter;
}

Converter &Converter::operator=(const Converter &converter)
{
    if (this == &converter)
        return *this;
    input_ = converter.input_;
    parse();
    return *this;
}

Converter::~Converter()
{
}

void Converter::parse()
{
    inputChar_ = 0;
    inputInt_ = 0;
    inputFloat_ = 0.0f;
    inputDouble_ = 0.0;
    inputType_ = parseInputType();
    setValues();
}

Converter::InputType Converter::parseInputType() const{
    if (input_ == "nan" || input_ == "nanf")
        return Nan;
    if (input_ == "inf" || input_ == "inff" || input_ == "+inf" || input_ == "+inff")
        return PositiveInfinite;
    if (input_ == "-inf" || input_ == "-inff")
        return NegativeInfinite;
    if (input_.length() == 1 && !std::isdigit(input_[0]))
        return Char;
    if (isInt())
        return Int;
    if (isFloat())
        return Float;
    if (isDouble())
        return Double;
    return Other;
}

bool Converter::isInt() const
{
    for (size_t i = 0; i < input_.length(); i++)
    {
        if (i == 0 && (input_[i] == '-' || input_[i] == '+'))
            continue;
        if (!std::isdigit(input_[i]))
            return false;
    }
    return true;
}

bool Converter::isFloat() const
{
    bool hasDot = false;
    for (size_t i = 0; i < input_.length() - 1; i++)
    {
        if (i == 0 && (input_[i] == '-' || input_[i] == '+'))
            continue;
        if (input_[i] == '.')
        {
            if (hasDot)
                return false;
            hasDot = true;
            continue;
        }
        if (!std::isdigit(input_[i]))
            return false;
    }
    return input_[input_.length() - 1] == 'f' ? true : false;
}

bool Converter::isDouble() const
{
    bool hasDot = false;
    for (size_t i = 0; i < input_.length(); i++)
    {
        if (i == 0 && (input_[i] == '-' || input_[i] == '+'))
            continue;
        if (input_[i] == '.')
        {
            if (hasDot)
                return false;
            hasDot = true;
            continue;
        }
        if (!std::isdigit(input_[i]))
            return false;
    }
    return true;
}

void Converter::setValues()
{
    if (input_[input_.length() - 1] == 'f')
        input_ = input_.erase(input_.length() - 1, 1);
    
    std::stringstream ss;
    ss << input_;

    switch (inputType_)
    {
        case Char:
            inputChar_ = input_[0];
            break;
        case Int:
            ss >> inputInt_;
            break;
        case Float:
            ss >> inputFloat_;
            break;
        case Double:
            ss >> inputDouble_;
            break;
        default:
            break;
    }
    if (ss.fail())
        inputType_ = Other;
}

void Converter::convert() const
{
    convertToChar();
    convertToInt();
    convertToFloat();
    convertToDouble();
}

/**
 * 0~31, 127はnon displayable表示
 * 32~126はそのまま対応するcharのリテラルを表示
 * それ以外の値はimpossible
 */
void Converter::convertToChar() const
{
    char val;
    std::cout << "char: ";
    switch (inputType_)
    {
    case Char:
        val = inputChar_;
        break;
    case Int:
        if (inputInt_ > std::numeric_limits<char>::max() || inputInt_ < std::numeric_limits<char>::min())
            return printImpossible();
        val = static_cast<char>(inputInt_);
        break;
    case Float:
        if (inputFloat_ > std::numeric_limits<char>::max() || inputFloat_ < std::numeric_limits<char>::min())
            return printImpossible();
        val = static_cast<char>(inputFloat_);
        break;
    case Double:
        if (inputDouble_ > std::numeric_limits<char>::max() || inputDouble_ < std::numeric_limits<char>::min())
            return printImpossible();
        val = static_cast<char>(inputDouble_);
        break;
    default:
        return printImpossible();
    }
    if (isDisplayable(val))
        std::cout << "'" << val << "'" << std::endl;
    else
        std::cout << "Non displayable" << std::endl;
}

void Converter::convertToInt() const
{
    int val;
    std::cout << "int: ";
    switch (inputType_)
    {
    case Char:
        val = static_cast<int>(inputChar_);
        break;
    case Int:
        val = inputInt_;
        break;
    case Float:
        if (inputFloat_ > std::numeric_limits<int>::max() || inputFloat_ < std::numeric_limits<int>::min())
            return printImpossible();
        val = static_cast<int>(inputFloat_);
        break;
    case Double:
        if (inputDouble_ > std::numeric_limits<int>::max() || inputDouble_ < std::numeric_limits<int>::min())
            return printImpossible();
        val = static_cast<int>(inputDouble_);
        break;
    default:
        return printImpossible();
    }
    std::cout << val << std::endl;
}

void Converter::convertToFloat() const
{
    float val;
    std::cout << "float: ";
    switch (inputType_)
    {
    case Char:
        val = static_cast<float>(inputChar_);
        break;
    case Int:
        val = static_cast<float>(inputInt_);
        break;
    case Float:
        val = inputFloat_;
        break;
    case Double:
        if (inputDouble_ > std::numeric_limits<float>::max() || inputDouble_ < std::numeric_limits<float>::max() * -1)
            return printImpossible();
        val = static_cast<float>(inputDouble_);
        break;
    case Nan:
        return printNanf();
    case PositiveInfinite:
        return printPositiveInff();
    case NegativeInfinite:
        return printNegativeInff();
    default:
        return printImpossible();
    }
    std::cout << val;
    std::stringstream floatstr;
    floatstr << val;
    if (floatstr.str().find('.') == std::string::npos)
        std::cout << ".0";
    std::cout << "f" << std::endl;
}

void Converter::convertToDouble() const
{
    double val;
    std::cout << "double: ";
    switch (inputType_)
    {
    case Char:
        val = static_cast<double>(inputChar_);
        break;
    case Int:
        val = static_cast<double>(inputInt_);
        break;
    case Float:
        val = static_cast<double>(inputFloat_);
        break;
    case Double:
        val = inputDouble_;
        break;
    case Nan:
        return printNan();
    case PositiveInfinite:
        return printPositiveInf();
    case NegativeInfinite:
        return printNegativeInf();
    default:
        return printImpossible();
    }
    std::cout << val;
    std::stringstream doublestr;
    doublestr << val;
    if (doublestr.str().find('.') == std::string::npos)
        std::cout << ".0";
    std::cout << std::endl;
}

void Converter::printImpossible() const
{
    std::cout << "impossible" << std::endl;
}

bool Converter::isDisplayable(const char &c) const
{
    if (c <= 31 || c >= 127)
        return false;
    return true;
}

void Converter::printNan() const
{
    std::cout << "nan" << std::endl;
}

void Converter::printNanf() const
{
    std::cout << "nanf" << std::endl;
}

void Converter::printPositiveInf() const
{
    std::cout << "inf" << std::endl;
}

void Converter::printPositiveInff() const
{
    std::cout << "inff" << std::endl;
}

void Converter::printNegativeInf() const
{
    std::cout << "-inf" << std::endl;
}

void Converter::printNegativeInff() const
{
    std::cout << "-inff" << std::endl;
}