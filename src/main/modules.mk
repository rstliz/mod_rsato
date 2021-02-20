
SRC=mod_rsato controller renderer

mod_rsato.la: $(addsuffix .slo,$(SRC))
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  $(addsuffix .lo,$(SRC)) $(LIBS)

#include <stdio.h>
DISTCLEAN_TARGETS = modules.mk
shared =  mod_rsato.la
