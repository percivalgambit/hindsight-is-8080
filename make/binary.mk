define cc_binary =
all: $(1)
CLEAN_ITEMS += $$(filter-out obj/%,$(1))
$(1): LDFLAGS += $$(RELEASE_LDFLAGS)
$(1): $$(call objects,$(2))
	@mkdir -p $$(@D)
	$$(CXX) $$(LDFLAGS) $$^ -o $$@ $$(LOADLIBES) $$(LDLIBS)
endef

define cc_debug_binary =
CLEAN_ITEMS += $$(filter-out obj/%,$(1))
$(1): LDFLAGS += $$(DEBUG_LDFLAGS)
$(1): $$(call debug_objects,$(2))
	@mkdir -p $$(@D)
	$$(CXX) $$(LDFLAGS) $$^ -o $$@ $$(LOADLIBES) $$(LDLIBS)
endef

define c_binary =
all: $(1)
CLEAN_ITEMS += $$(filter-out obj/%,$(1))
$(1): LDFLAGS += $$(RELEASE_LDFLAGS)
$(1): $$(call objects,$(2))
	@mkdir -p $$(@D)
	$$(CC) $$(LDFLAGS) $$^ -o $$@ $$(LOADLIBES) $$(LDLIBS)
endef

define c_debug_binary =
CLEAN_ITEMS += $$(filter-out obj/%,$(1))
$(1): LDFLAGS += $$(DEBUG_LDFLAGS)
$(1): $$(call debug_objects,$(2))
	@mkdir -p $$(@D)
	$$(CC) $$(LDFLAGS) $$^ -o $$@ $$(LOADLIBES) $$(LDLIBS)
endef
