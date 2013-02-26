#
# Mikrokopter v2 Actuators
#
# see actuators_mkk for more information
#
#  max command = 2047

include $(CFG_SHARED)/subsystems/shared/actuators_mkk.makefile

ap.CFLAGS += -DACTUATORS_MKK_V2_PROTOCOL