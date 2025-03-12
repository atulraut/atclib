p	= 1_ADT

all clean test::
	@ for p in $p; do \
	    if [ -d $$p -a -r $$p/makefile ]; then \
	      echo; echo make $@ in $$p; echo; \
	      (cd $$p && $(MAKE) $(MFLAGS) $@) \
	    fi; \
	  done

include make/Makefile.$(OSTYPE)
