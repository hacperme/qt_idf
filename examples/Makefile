build_dirs += shell
build_dirs += opus_demo
build_dirs += linksdk_demo
build_dirs += mcu_hex
all: $(build_dirs)

$(build_dirs):
	make -C $@

.PHONY: $(build_dirs)

