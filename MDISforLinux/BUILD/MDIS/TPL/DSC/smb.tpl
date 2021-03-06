smb2_bus0 {

    # ------------------------------------------------------------------------
    #        general parameters (don't modify)
    # ------------------------------------------------------------------------
    DESC_TYPE = U_INT32 0x2
    HW_TYPE = STRING SMB2
    _WIZ_MODEL = STRING SCAN_SMBDRV
    _WIZ_BUSIF = STRING cpu,SCAN_SMBUSIF

    # ------------------------------------------------------------------------
    #           SMBus parameters
    # ------------------------------------------------------------------------
    SMB_BUSNBR = U_INT32 SCAN_SMBNR
SCAN_LIST_OF_SMB_DEVICES

    # ------------------------------------------------------------------------
    #        debug levels (optional)
    #        these keys have only effect on debug drivers
    # ------------------------------------------------------------------------
    DEBUG_LEVEL = U_INT32 0xc0008000
    DEBUG_LEVEL_BK = U_INT32 0xc0008000
    DEBUG_LEVEL_OSS = U_INT32 0xc0008000
    DEBUG_LEVEL_DESC = U_INT32 0xc0008000
}
