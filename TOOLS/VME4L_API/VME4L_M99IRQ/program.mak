#***************************  M a k e f i l e  *******************************
#
#         Author: kp
#          $Date: 2003/12/15 15:02:35 $
#      $Revision: 1.1 $
#
#    Description: Makefile definitions for VME4L_M99IRQ
#
#---------------------------------[ History ]---------------------------------
#
#   $Log: program.mak,v $
#   Revision 1.1  2003/12/15 15:02:35  kp
#   Initial Revision
#
#-----------------------------------------------------------------------------
#   (c) Copyright 2003 by MEN mikro elektronik GmbH, Nuernberg, Germany
#*****************************************************************************

MAK_NAME=vme4l_m99irq

MAK_LIBS=$(LIB_PREFIX)$(MEN_LIB_DIR)/vme4l_api$(LIB_SUFFIX)


MAK_INCL=$(MEN_INC_DIR)/../../NATIVE/MEN/vme4l_api.h	\
	     $(MEN_INC_DIR)/../../NATIVE/MEN/vme4l.h

MAK_INP1=vme4l_m99irq$(INP_SUFFIX)

MAK_INP=$(MAK_INP1)
