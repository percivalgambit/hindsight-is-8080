objects = $$(patsubst src/%.c,obj/release/%.o,$$(patsubst src/%.cc,obj/release/%.o,$$(sort $(1))))
debug_objects = $$(patsubst src/%.c,obj/debug/%.o,$$(patsubst src/%.cc,obj/debug/%.o,$$(sort $(1))))

obj/release/%.o: CPPFLAGS += $(RELEASE_CPPFLAGS)
obj/release/%.o: CXXFLAGS += $(RELEASE_CXXFLAGS)
obj/release/%.o: CFLAGS += $(RELEASE_CFLAGS)
obj/release/%.o: src/%.cc
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
obj/release/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

obj/debug/%.o: CPPFLAGS += $(DEBUG_CPPFLAGS)
obj/debug/%.o: CXXFLAGS += $(DEBUG_CXXFLAGS)
obj/debug/%.o: CFLAGS += $(DEBUG_CFLAGS)
obj/debug/%.o: src/%.cc
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
obj/debug/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

obj/release/%.dd: src/%.cc
obj/debug/%.dd: src/%.cc
obj/release/%.dd: src/%.c
obj/debug/%.dd: src/%.c
include $(shell [[ -e obj/ ]] && find obj/ -type f -name "*.dd")
include $(shell [[ -e obj/ ]] && find obj/ -type f -name "*.d")
