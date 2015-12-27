.PHONY all elrond clean

all: elrond

clean:
	$(MAKE) clean -C src
	
elrond:
	$(MAKE) -C src