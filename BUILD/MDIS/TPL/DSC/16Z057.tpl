uart_SCAN_MDIS_INSTANCE {

    # ------------------------------------------------------------------------
    #        general parameters (don't modify)
    # ------------------------------------------------------------------------
    DESC_TYPE = U_INT32 0x1
    HW_TYPE = STRING FRODO_SERIAL
    _WIZ_MODEL = STRING 16Z025_UART

    # ------------------------------------------------------------------------
    #        reference to base board
    # ------------------------------------------------------------------------
    BOARD_NAME = STRING SCAN_BBIS_NAMEUSCORESCAN_BBIS_INSTANCE
    DEVICE_SLOT = U_INT32 SCAN_DEV_SLOT

    # ------------------------------------------------------------------------
    #        device parameters
    # ------------------------------------------------------------------------
}
