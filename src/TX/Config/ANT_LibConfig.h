#ifndef ANT_LIBCONFIG_h
#define ANT_LIBCONFIG_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a Lib Config message, it is used to
 * configure extended responses from the radio
 */
class LibConfig : public AntRequest {
public:
    LibConfig();
    LibConfig(uint8_t config);
    void setConfig(uint8_t config);
    uint8_t getConfig();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _config;
};

#endif // ANT_LIBCONFIG_h