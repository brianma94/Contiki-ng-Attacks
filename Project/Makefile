CONTIKI_PROJECT = udp-client udp-server udp-flood udp-selector
all: $(CONTIKI_PROJECT)
udp-selector.sky: CFLAGS+= -DSELECT=1
udp-selector.z1: CFLAGS+= -DSELECT=1
CONTIKI=../
include $(CONTIKI)/Makefile.include
