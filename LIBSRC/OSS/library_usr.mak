#***************************  M a k e f i l e  *******************************
#
#         Author: christian.schuster@men.de
#          $Date: 2007/07/16 09:55:10 $
#      $Revision: 2.4 $
#
#    Description: makefile for Linux OSS lib for user space
#
#---------------------------------[ History ]---------------------------------
#
#   $Log: library_usr.mak,v $
#   Revision 2.4  2007/07/16 09:55:10  cs
#   added: use specific ident file for user space lib
#
#   Revision 2.3  2007/07/13 17:44:32  cs
#   added:
#     + pciutils header files to dependancies
#
#   Revision 2.2  2005/07/08 16:49:08  cs
#   removed pciutils linking from oss_usr linking
#
#   Revision 2.1  2005/07/08 11:32:51  cs
#   Initial Revision
#
#
#-----------------------------------------------------------------------------
# (c) Copyright 2005 by MEN Mikro Elektronik GmbH, Nuremberg, Germany
#*****************************************************************************
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

MAK_NAME=oss_usr

MAK_SWITCH= $(SW_PREFIX)MAC_USERSPACE \
			$(SW_PREFIX)OSS_CONFIG_PCI \
			$(SW_PREFIX)OSS_CONFIG_VME \
			$(SW_PREFIX)DBG \

MAK_INCL=$(MEN_INC_DIR)/men_typs.h    \
         $(MEN_INC_DIR)/../../NATIVE/MEN/vme4l.h       \
         $(MEN_INC_DIR)/../../NATIVE/MEN/vme4l_api.h   \
         $(MEN_INC_DIR)/oss.h         \
         $(MEN_INC_DIR)/mdis_err.h    \
         $(MEN_MOD_DIR)/oss_intern.h  \
         $(MEN_MOD_DIR)/../pciutils/lib/pci.h  \
         $(MEN_MOD_DIR)/../pciutils/lib/config.h  \
         $(MEN_MOD_DIR)/../pciutils/lib/header.h  \
	 $(MEN_INC_DIR)/../../NATIVE/MEN/oss_os.h

MAK_INP1=ossu$(INP_SUFFIX)
MAK_INP2=oss_clib$(INP_SUFFIX)
MAK_INP3=ossu_mem$(INP_SUFFIX)
MAK_INP4=ossu_time$(INP_SUFFIX)
MAK_INP5=ossu_resource$(INP_SUFFIX)
MAK_INP6=ossu_map$(INP_SUFFIX)
MAK_INP7=oss_swap$(INP_SUFFIX)
MAK_INP8=oss_dl_list$(INP_SUFFIX)
MAK_INP9=ossu_bustoaddr$(INP_SUFFIX)
MAK_INP10=ossu_task$(INP_SUFFIX)
MAK_INP11=ossu_sem$(INP_SUFFIX)

MAK_INP12=ossu_ident$(INP_SUFFIX)

MAK_INP=$(MAK_INP1) \
        $(MAK_INP2) \
        $(MAK_INP3) \
        $(MAK_INP4) \
        $(MAK_INP5) \
        $(MAK_INP6) \
        $(MAK_INP7) \
        $(MAK_INP8) \
        $(MAK_INP9) \
        $(MAK_INP10) \
        $(MAK_INP11) \
        $(MAK_INP12) \
        $(MAK_INP13) \
