/**
 * Represents a Open Rx Scan Mode message, it is used to put the ANT radio into open rx scan mode
 */
class OpenRxScanMode : public AntRequest {
public:
    OpenRxScanMode();
    void setSynchronousChannelPacketsOnly(bool synchronousOnly);
    bool getSynchronousChannelPacketsOnly();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif // NATIVE_API_AVAILABLE
private:
    bool _synchronousChannelPacketsOnly;
};