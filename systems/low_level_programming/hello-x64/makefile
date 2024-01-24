.PHONY: run
run: hello
	@./hello

hello: hello_mac.o
	@ld hello_mac.o \
		-o hello \
		-macosx_version_min 11.0 \
		-L /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib \
		-lSystem \
		-no_pie

hello_mac.o: hello_mac.asm
	@nasm -fmacho64 hello_mac.asm

.PHONY: disassemble
disassemble: hello_mac.o
	@objdump -d hello_mac.o