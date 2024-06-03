# SPDX-License-Identifier: MIT
# Copyright (c) 2019-2023 The Pybricks Authors

# ensure micropython submodule is checked out for building mpy-cross
ifeq ("$(wildcard micropython/README.md)","")
$(info GIT cloning micropython submodule)
$(info $(shell git submodule update --init micropython))
ifeq ("$(wildcard micropython/README.md)","")
$(error failed)
endif
endif

ifeq ("$(OS)","Windows_NT")
$(error Use Linux please)
else
HOST_OS = $(shell uname -s)
endif

primehub: .depend
	@$(MAKE) -C bricks/primehub
	
clean: .clean-mpy-cross
	@$(MAKE) -C bricks/primehub clean
	
.depend:
	@$(MAKE) -C micropython/mpy-cross CROSS_COMPILE=$(HOST_CROSS_COMPILE)
	
.clean-mpy-cross:
	@$(MAKE) -C micropython/mpy-cross clean CROSS_COMPILE=$(HOST_CROSS_COMPILE)
	
help:
	@echo "Use 'make primehub' to build a brick."
