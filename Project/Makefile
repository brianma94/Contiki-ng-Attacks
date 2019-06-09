CONTIKI_PROJECT = udp-client udp-server flood selector ids ids-detector
all: $(CONTIKI_PROJECT)
selector.sky: CFLAGS+= -DSELECT=1
selector.z1: CFLAGS+= -DSELECT=1
CONTIKI=../
include $(CONTIKI)/Makefile.include
