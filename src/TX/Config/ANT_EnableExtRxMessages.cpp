#include <TX/Config/ANT_EnableExtRxMessages.h>

#include <ANT_private_defines.h>

EnableExtRxMessages::EnableExtRxMessages() : AntRequest(ENABLE_EXT_RX_MESSAGES) {

}

EnableExtRxMessages::EnableExtRxMessages(uint8_t enable) : AntRequest(ENABLE_EXT_RX_MESSAGES) {
    setEnable(enable);
}

void EnableExtRxMessages::setEnable(uint8_t enable) {
    _enable = enable;
}

uint8_t EnableExtRxMessages::getEnable() {
    return _enable;
}

uint8_t EnableExtRxMessages::getData(uint8_t pos) {
    if (pos == 0) {
        return 0;
    } else {
        return _enable;
    }
}

uint8_t EnableExtRxMessages::getDataLength() {
    return ENABLE_EXT_RX_MESSAGES_LENGTH;
}


#ifdef NATIVE_API_AVAILABLE

uint8_t EnableExtRxMessages::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE