define cc_binary =
all: $(1)
CLEAN_ITEMS += $$(filter-out obj/%,$(1) $(1:%=%-debug))

$(1): LDFLAGS += $$(RELEASE_LDFLAGS)
$(1): $$(call objects,$(2))
	@mkdir -p $$(@D)
	$$(CXX) $$(LDFLAGS) $$^ -o $$@ $$(LOADLIBES) $$(LDLIBS)

debug: $(1:%=%-debug)
$(1:%=%-debug): LDFLAGS += $$(DEBUG_LDFLAGS)
$(1:%=%-debug): $$(call debug_objects,$(2))
	@mkdir -p $$(@D)
	$$(CXX) $$(LDFLAGS) $$^ -o $$@ $$(LOADLIBES) $$(LDLIBS)
endef

define c_binary =
all: $(1)
CLEAN_ITEMS += $$(filter-out obj/%,$(1) $(1:%=%-debug))

$(1): LDFLAGS += $$(RELEASE_LDFLAGS)
$(1): $$(call objects,$(2))
	@mkdir -p $$(@D)
	$$(CC) $$(LDFLAGS) $$^ -o $$@ $$(LOADLIBES) $$(LDLIBS)

debug: $(1:%=%-debug)
$(1:%=%-debug): LDFLAGS += $$(DEBUG_LDFLAGS)
$(1:%=%-debug): $$(call debug_objects,$(2))
	@mkdir -p $$(@D)
	$$(CC) $$(LDFLAGS) $$^ -o $$@ $$(LOADLIBES) $$(LDLIBS)
endef
