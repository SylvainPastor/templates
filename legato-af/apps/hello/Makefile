
TARGETS := wp85 localhost

.PHONY: all $(TARGETS)
all: $(TARGETS)

$(TARGETS):
	mkapp -t $@ \
		hello.adef

install:
	app install hello.wp85.update 192.168.2.2

clean:
	rm -rf _build_* *.update
