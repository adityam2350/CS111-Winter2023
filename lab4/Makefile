ifeq ($(shell uname -s),Darwin)
	CFLAGS = -std=gnu17 -pthread -Wall -O0 -pipe -fno-plt -fPIC
	LDFLAGS =
else
	CFLAGS = -std=gnu17 -pthread -Wall -O0 -pipe -fno-plt -fPIC
	LDFLAGS = -lrt -pthread -Wl,-O1,--sort-common,--as-needed,-z,relro,-z,now
endif

FILENAME=README.md
UID = $(shell cat ${FILENAME} | grep '## UID'| grep -oe '\([0-9.]*\)')
SUBMISSION_FILES = ext2-create.c README.md
.PHONY: all
all: ext2-create

ext2-create: ext2-create.o

tar:
	@tar -cf ${UID}-lab4-submission.tar ${SUBMISSION_FILES}
.PHONY: clean
clean:
	rm -f ext2-create.o ext2-create
	rm -f *.img
	rm -f ${UID}-lab4-submission.tar
