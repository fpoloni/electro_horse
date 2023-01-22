from enum import Enum, IntEnum, unique

@unique
class IdxParameterPDU(IntEnum):
    HEAD = 0
    OPERATION = 1
    LEN = 2
    PROGRAM = 3
    STATE  = 4
    DEVICE = 5
    PAYLOAD = 6
    CRC = 7
    TAIL = 8

@unique
class IdxParameterPayload(IntEnum):
    PWM = 6
    TEMP_MIN = 7
    TEMP_MAX = 8
    TEMP_CUR = 9
    TIME     = 10
    STATUS   = 11