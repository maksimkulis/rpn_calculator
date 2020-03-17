#include <iostream>
#include <stack>
#include <sstream>
#include <stdexcept>

enum class SIGNS {
    PLUS,
    MINUS,
    MUL,
    DIV
};

class Error: public std::runtime_error
{
public:
    Error(const char* message): std::runtime_error(message) {}
};

bool is_value(const std::string& str)
{
    if (str[0] == '.') return false;

    bool flag = false;
    for (auto c: str) {
        if (!(isdigit(c) || c == '.') || ((c == '.') && flag)) {
            return false;
        }
        if (c == '.') flag = true;
    }
    return true;
}

bool is_sign(const std::string& str)
{
    if (str.size() == 1) {
        switch (str[0]) {
        case '+':
        case '-':
        case '*':
        case '/':
            return true;
        default:
            return false;
        }

    } else {
        return false;
    }
}

SIGNS str_to_sign(char sign)
{
    switch(sign){
    case '+':
        return SIGNS::PLUS;
    case '-':
        return SIGNS::MINUS;
    case '*':
        return SIGNS::MUL;
    case '/':
        return SIGNS::DIV;
    }
}

double calculate(std::istream& stream)
{
    std::stack<double> values;
    std::string str;
    while (stream >> str) {
        if (is_value(str)) {
            values.push(atof(str.c_str()));
        } else if (is_sign(str)) {
            if (values.size() < 2) {
                throw Error("Bad usage: Binary operation
                            for less then 2 arguments\n");
            }
            double first_value, second_value;
            second_value = values.top();
            values.pop();
            first_value = values.top();
            values.pop();

            switch(str_to_sign(str[0])){
            case SIGNS::PLUS:
                values.push(first_value + second_value);
                break;
            case SIGNS::MINUS:
                values.push(first_value - second_value);
                break;
            case SIGNS::MUL:
                values.push(first_value * second_value);
                break;
            case SIGNS::DIV:
                if (second_value == 0) {
                    throw Error("Zero division!\n");
                } else {
                    values.push(first_value / second_value);
                    break;
                }
            }
        }
    }

    if (values.size() != 1) {
        throw Error("Wrong usage\n");
    } else {
        return values.top();
    }
}


int main(int argc, char** argv)
{
    try {
        if (argc == 1) {
            std::cout << calculate(std::cin);
        } else if (argc == 2) {
            std::stringstream strstream {argv[1]};
            std::cout << calculate(strstream) << std::endl;
        } else {
            std::cout << "Usage: ./prog \"[expression]\"\n"
                      << "For example: ./prog \"2 2 +\"\n";
            return -1;
        }
    } catch (const Error &e) {
        std::cout << e.what();
        return -1;
    }
    return 0;
}
