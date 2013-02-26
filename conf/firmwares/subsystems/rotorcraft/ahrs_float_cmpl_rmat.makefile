# Hey Emacs, this is a -*- makefile -*-
#
# AHRS_H_X
# AHRS_H_Y
# AHRS_H_Z
#

USE_MAGNETOMETER ?= 1

AHRS_CFLAGS  = -DUSE_AHRS
AHRS_CFLAGS += -DUSE_AHRS_ALIGNER

ifneq ($(USE_MAGNETOMETER),0)
  AHRS_CFLAGS += -DUSE_MAGNETOMETER
endif

ifneq ($(AHRS_ALIGNER_LED),none)
  AHRS_CFLAGS += -DAHRS_ALIGNER_LED=$(AHRS_ALIGNER_LED)
endif

AHRS_CFLAGS += -DAHRS_TYPE_H=\"subsystems/ahrs/ahrs_float_cmpl.h\"
AHRS_CFLAGS += -DAHRS_PROPAGATE_RMAT
AHRS_SRCS   += subsystems/ahrs.c
AHRS_SRCS   += subsystems/ahrs/ahrs_float_cmpl.c
AHRS_SRCS   += subsystems/ahrs/ahrs_aligner.c

ifdef AHRS_PROPAGATE_FREQUENCY
AHRS_CFLAGS += -DAHRS_PROPAGATE_FREQUENCY=$(AHRS_PROPAGATE_FREQUENCY)
endif

ifdef AHRS_CORRECT_FREQUENCY
AHRS_CFLAGS += -DAHRS_CORRECT_FREQUENCY=$(AHRS_CORRECT_FREQUENCY)
endif

ap.CFLAGS += $(AHRS_CFLAGS)
ap.srcs += $(AHRS_SRCS)

nps.CFLAGS += $(AHRS_CFLAGS)
nps.srcs += $(AHRS_SRCS)
