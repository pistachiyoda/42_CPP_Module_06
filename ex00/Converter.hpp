#ifndef CONVERTER_H
#define CONVERTER_H

#include <iostream>
#include <sstream>
#include <limits>

class Converter
{
public:
    enum InputType
    {
        Char,
        Int,
        Float,
        Double,
        PositiveInfinite,
        NegativeInfinite,
        Nan,
        Other,
    };
    Converter();
    Converter(const std::string &input);
    Converter(const Converter &converter);
    Converter &operator=(const Converter &converter);
    ~Converter();
    void convert() const;
private:
    std::string input_;
    InputType inputType_;
    char inputChar_;
    int inputInt_;
    float inputFloat_;
    double inputDouble_;
    void parse();
    void setValues();
    InputType parseInputType() const;
    void convertToChar() const;
    void convertToInt() const;
    void convertToFloat() const;
    void convertToDouble() const;
    void printImpossible() const;
    void printNan() const;
    void printNanf() const;
    void printPositiveInf() const;
    void printPositiveInff() const;
    void printNegativeInf() const;
    void printNegativeInff() const;
    bool isDisplayable(const char &c) const;
    bool isInt() const;
    bool isFloat() const;
    bool isDouble() const;
};

#endif
