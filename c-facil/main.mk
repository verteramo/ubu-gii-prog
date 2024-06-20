path := $(dir $(abspath $(firstword $(MAKEFILE_LIST))))/..
packages := "vim gcc cpp make indent man manpages manpages-dev manpages-es"


include $(path)/make/cpa.mk

uninstall:
	./uninstall.sh
