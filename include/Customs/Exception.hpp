/**
    @file Exception.cpp
    @brief Class representing an exception.
    @copyright LGPL. MIT License.
*/
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

using std::string;

class Exception {
public:
    Exception(const string& message)
        : m_message(message) {

        }

    string message() const {
        return m_message;
    }

private:
    string m_message;
};

#endif
