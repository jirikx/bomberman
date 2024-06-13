#include <stdexcept>
#include <string>

/**
 * @brief Exception which is thrown after some parsing error
 *
 */
class ConfigParseException : public std::exception {
public:
    /**
     * @brief Constructor
     *
     * @param message describing the exception
     */
    explicit ConfigParseException(const std::string &message);

    /**
     * @brief Returns the exception description
     *
     * @return exception description
     */
    const char* what() const noexcept override;

private:
    std::string m_Message;
};