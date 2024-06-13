#include "ConfigParseException.hpp"

ConfigParseException::ConfigParseException(const std::string &message)
  : m_Message(message) {}

const char *ConfigParseException::what() const noexcept {
    return m_Message.c_str();
}
