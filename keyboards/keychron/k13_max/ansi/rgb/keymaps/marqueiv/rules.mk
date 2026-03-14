COMMON_DIR = $(QMK_USERSPACE)/common
SRC += $(wildcard $(COMMON_DIR)/*.c)

SRC += hardware.c

TAP_DANCE_ENABLE = yes
MOUSEKEY_ENABLE = yes
VIA_ENABLE = yes
