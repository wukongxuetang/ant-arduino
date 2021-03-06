#include <MainClasses/ANT_Ant.h>
#include <ANT_private_defines.h>

Ant::Ant() : BaseAnt() {
    _pos = 0;
    _checksumTotal = 0;
    getResponse().setFrameData(_responseFrameData);

    // Contributed by Paul Stoffregen for Teensy support
#if defined(__AVR_ATmega32U4__) || defined(__MK20DX128__)
    _serial = &Serial1;
#else
    _serial = &Serial;
#endif
}

void Ant::resetResponse() {
    _pos = 0;
    _checksumTotal = 0;
    getResponse().reset();
}

void Ant::begin(Stream &serial) {
    _serial = &serial;
}

void Ant::setSerial(Stream &serial) {
    _serial = &serial;
}

bool Ant::available() {
    return _serial->available();
}

uint8_t Ant::read() {
    return _serial->read();
}

void Ant::write(uint8_t val) {
    _serial->write(val);
}

void Ant::readPacket() {
    // reset previous response
    if (getResponse().isAvailable() || getResponse().isError()) {
        // discard previous packet and start over
        resetResponse();
    }

    while (available()) {

        b = read();

        // checksum includes all bytes including the sync
        _checksumTotal ^= b;

        switch(_pos) {
            case 0:
                if (b == ANT_START_BYTE) {
                    _pos++;
                }

                break;
            case 1:
                // length msb
                getResponse().setLength(b);
                _pos++;

                break;
            case 2:
                getResponse().setMsgId(b);
                _pos++;

                break;
            default:
                // starts at fourth byte

                if (_pos > ANT_MAX_MSG_DATA_SIZE) {
                    // exceed max size.  should never occur
                    getResponse().setErrorCode(PACKET_EXCEEDS_BYTE_ARRAY_LENGTH);
                    return;
                }

                // check if we're at the end of the packet
                if (_pos == (getResponse().getLength() + 3)) {
                    // verify checksum
                    // if the last byte is the checksum
                    // then XOR it with itself should be 0

                    if (_checksumTotal == 0) {
                        getResponse().setChecksum(b);
                        getResponse().setAvailable(true);

                        getResponse().setErrorCode(NO_ERROR);
                    } else {
                        // checksum failed
                        getResponse().setErrorCode(CHECKSUM_FAILURE);
                    }

                    // reset state vars
                    _pos = 0;

                    return;
                } else {
                    // add to packet array, starting with the fourth byte of the msgId
                    getResponse().getFrameData()[_pos - ANT_MSG_FRONT_OVERHEAD] = b;
                    _pos++;
                }
        }
    }
}

void Ant::send(AntRequest &request) {
    // checksum is XOR of all bytes
    uint8_t checksum = 0;

    // the new new deal
    checksum ^= ANT_START_BYTE;
    write(ANT_START_BYTE);

    // send length
    uint8_t len = (request.getDataLength());
    checksum ^= len;
    write(len);

    // Msg id
    write(request.getMsgId());
    checksum ^= request.getMsgId();

    for (int i = 0; i < request.getDataLength(); i++) {
        write(request.getData(i));
        checksum ^= request.getData(i);
    }

    // send checksum
    write(checksum);
}