/***********************  I n c l u d e  -  F i l e  ************************/
/*!
 *        \file  men_chameleon.h
 *
 *      \author  ub/kp
 *        $Date: 2007/10/24 14:12:42 $
 *    $Revision: 1.9 $
 *
 *       \brief  Linux header file for MEN Chameleon FPGA support
 *
 *     Switches: -
 */
/*-------------------------------[ History ]---------------------------------
 *
 * $Log: men_chameleon.h,v $
 * Revision 1.9  2007/10/24 14:12:42  ts
 * removed define CHAMELEON_MAX_UNITS, nr. of IP cores per FPGA is unlimited now
 * changed CHAMELEON_CFGTABLE_SZ to be depending on h->numUnits (# of cores)
 *
 * Revision 1.8  2007/10/08 14:39:50  ts
 * added seamless V2 support (changes by GL)
 *
 * Revision 1.7  2007/03/28 17:02:14  ts
 * Bugfix: struct for V0 Chameleon tabes wasnt necessary here
 *
 * Revision 1.6  2007/03/01 10:05:05  ts
 * struct CHAMELEON_UNIT (V0/V1 Units) moved here from men_chameleon.c
 *
 * Revision 1.5  2006/09/01 11:05:09  ts
 * Corrected wrong MOD_CODE_END for V0 tables to 0x3f
 *
 * Revision 1.4  2004/12/16 09:05:38  ub
 * changed include path for chameleon.h
 *
 * Revision 1.3  2004/04/08 08:31:04  kp
 * added proto for men_chameleon_init
 *
 * Revision 1.2  2004/02/06 08:42:43  kp
 * take module codes from common chameleon.h
 *
 * Revision 1.1  2004/01/28 13:02:56  kp
 * Added men_chameleon.h
 *
 *---------------------------------------------------------------------------
 * (c) Copyright 2003 by MEN mikro elektronik GmbH, Nuernberg, Germany
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 ****************************************************************************/
#ifndef _MEN_CHAMELEON_H
#define _MEN_CHAMELEON_H

#include <MEN/men_typs.h>
#include <linux/pci.h>
#include <linux/list.h>

/* #define CHAMELEON_CODES_ONLY */
#include <MEN/chameleon.h>

/*--------------------------------------+
|   DEFINES & CONSTS                    |
+--------------------------------------*/
#define CHAMELEON_MODCODE_END 0x3f /* end of CHAMELEON_DRIVER_T.modCodeArr */
#define CHAMELEONV2_DEVID_END 0x0000 /* end of CHAMELEONV2_DRIVER_T.devIdArr */

#define CHAMELEON_CFGTABLE_SZ ((h->numUnits+1)*8)


/*--------------------------------------+
|   TYPEDEFS                            |
+--------------------------------------*/

/** This structure describes a chameleon unit
 */
typedef struct {
    u16 modCode;            /**< chameleon unit module code */
    u16 revision;           /**< revision of that module */
    int instance;           /**< unit instance number 0..n (within this FPGA)*/
    int irq;                /**< Linux interrupt number assigned for unit */
    int bar;                /**< unit's address space is in BARx (0..3) */
    u32 offset;             /**< unit's address space offset to BARx */
    void *phys;             /**< physical CPU address of unit regs */   

    /* for pnp access routines only! */
    int chamNum;            /**< nth chameleon fpga in system  */
    struct pci_dev *pdev;   /**< the pci device handling this unit 
                                 (NULL for early access routines) */
    void *driver_data;      /**< data private to driver  */
    struct CHAMELEON_DRIVER_T *driver; /**< attached driver (NULL if none) */

} CHAMELEON_UNIT_T;

/** This structure describes a chameleon driver
 */
typedef struct CHAMELEON_DRIVER_T {
    struct list_head node;  /**< list of all registered drivers  */
    const char *name;       /**< driver name */
    const u16 *modCodeArr;  /**< array of chameleon module codes handled,
                               terminated by 0xffff */
    /** called when module code matches. must return >=0 on success */
    int (*probe)( CHAMELEON_UNIT_T *unit );
    /** called when driver unregisters. may be NULL */
    int (*remove)( CHAMELEON_UNIT_T *unit ); 
} CHAMELEON_DRIVER_T;


/** This structure describes a chameleon V2 driver unit 
 */
typedef struct {
    CHAMELEONV2_UNIT unitFpga;           /**< unit data in FPGA */
    /* for pnp access routines only! */
    int chamNum;                         /**< nth chameleon fpga in system  */
    struct pci_dev *pdev;                /**< the pci device handling this unit 
                                             (NULL for early access routines) */
    void *driver_data;                   /**< data private to driver  */
    struct CHAMELEONV2_DRIVER_T *driver; /**< attached driver (NULL if none) */
} CHAMELEONV2_UNIT_T;

/** This structure describes a chameleon V2 driver
 */
typedef struct CHAMELEONV2_DRIVER_T {
    struct list_head node;  /**< list of all registered drivers  */
    const char *name;       /**< driver name */
    const u16 *devIdArr;    /**< array of chameleon device ids handled,
                               terminated by 0xffff */
    /** called when module code matches. must return >=0 on success */
    int (*probe)( CHAMELEONV2_UNIT_T *unit );
    /** called when driver unregisters. may be NULL */
    int (*remove)( CHAMELEONV2_UNIT_T *unit ); 
} CHAMELEONV2_DRIVER_T;

/*--------------------------------------+
|   PROTOTYPES                          |
+--------------------------------------*/
/* early access interface */
#ifdef _ASM_PCI_BRIDGE_H
int men_chameleon_early_init( struct pci_controller *hose, int devNo);
#endif

int men_chameleon_early_unit_ident( int idx, CHAMELEON_UNIT_T *info );
int men_chameleon_early_unit_find( int modCode, int instance, 
                                   CHAMELEON_UNIT_T *info);

/* Plug&Play interface */

extern int men_chameleon_init(void);
int men_chameleon_register_driver( CHAMELEON_DRIVER_T *drv );
void men_chameleon_unregister_driver( CHAMELEON_DRIVER_T *drv );

/* Non-Plug&Play interface */
int men_chameleon_unit_find(int modCode, int idx, CHAMELEON_UNIT_T *unit);

int men_chameleonV2_register_driver( CHAMELEONV2_DRIVER_T *drv );
void men_chameleonV2_unregister_driver( CHAMELEONV2_DRIVER_T *drv );

/* Non-Plug&Play interface */
int men_chameleonV2_unit_find(int devId, int idx, CHAMELEONV2_UNIT_T *unit);

#endif  /* _MEN_CHAMELEON_H */

