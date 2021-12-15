#ifndef BLE_GATT_SERVER_H_
#define BLE_GATT_SERVER_H_	1

/* Attributes State Machine */
enum
{
    // Service Declaration
    IDX_SVC,
    // Characteristic Declaration
    IDX_CHAR_A,
    // Characteristic Value
    IDX_CHAR_VAL_A,
    // Client Characteristic Configuration Descriptor
    IDX_CHAR_CFG_A,
    // Characteristic Declaration
    IDX_CHAR_B,
    // Characteristic Value
    IDX_CHAR_VAL_B,
    // Characteristic Declaration
    IDX_CHAR_C,
    // Characteristic Value
    IDX_CHAR_VAL_C,

    HRS_IDX_NB,
};

void bleGattServerInit();

#endif
