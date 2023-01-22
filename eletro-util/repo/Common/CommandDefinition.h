#ifndef MEDICALHORSE_COMMAND_HANDLER_DEFINITION_H_
#define MEDICALHORSE_COMMAND_HANDLER_DEFINITION_H_

namespace medicalhorse::util::definition
{
    namespace program
    {
        enum name : int8_t
        {
            CRYOTHERAPY = 0,
            THERMOTHERAPY,
            NONE
        };
    } // namespace program

    namespace operation
    {
        enum name : int8_t
        {
            WRITE = 0,
            READ,
            ALL
        };
    } // namespace operation

    namespace device
    {
        enum name : int8_t
        {
            MOTOR = 0,
            SENSOR,
            TIME,
            HBRIDGE,
            ALL
        };
    } // namespace device

    namespace state
    {
        enum name : int8_t
        {
            START = 0,
            STOP,
            CANCEL
        };
    } // namespace state

    namespace status
    {
        enum name : int8_t
        {
            RUN = 0,
            PREPARE,
            NONE
        };
    } // namespace status

} // namespace medicalhorse::command::definition

#endif // MEDICALHORSE_COMMAND_LINE_INTERFACE_H_