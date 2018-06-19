_release_dir := release$(if $(asserts),+asserts)

objects = $$(patsubst src/%.c,obj/$(_release_dir)/%.o,$$(patsubst src/%.cc,obj/$(_release_dir)/%.o,$$(sort $(1))))
debug_objects = $$(patsubst src/%.c,obj/debug/%.o,$$(patsubst src/%.cc,obj/debug/%.o,$$(sort $(1))))

obj/$(_release_dir)/%.o: CPPFLAGS += $(RELEASE_CPPFLAGS) $(if $(asserts),$(ASSERTS_CPPFLAGS),$(NOASSERTS_CPPFLAGS))
obj/$(_release_dir)/%.o: CXXFLAGS += $(RELEASE_CXXFLAGS) $(if $(warnings),$(WARNINGS_CXXFLAGS),$(NOWARNINGS_CXXFLAGS))
obj/$(_release_dir)/%.o: CFLAGS += $(RELEASE_CFLAGS) $(if $(warnings),$(WARNINGS_CFLAGS),$(NOWARNINGS_CFLAGS))
obj/$(_release_dir)/%.o: src/%.cc
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
obj/$(_release_dir)/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

obj/debug/%.o: CPPFLAGS += $(DEBUG_CPPFLAGS) $(ASSERTS_CPPFLAGS)
obj/debug/%.o: CXXFLAGS += $(DEBUG_CXXFLAGS) $(WARNINGS_CXXFLAGS)
obj/debug/%.o: CFLAGS += $(DEBUG_CFLAGS) $(WARNINGS_CFLAGS)
obj/debug/%.o: src/%.cc
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
obj/debug/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

obj/$(_release_dir)/%.d: src/%.cc src/%.c
obj/debug/%.d: src/%.cc src/%.c
include $(shell [[ -e obj/ ]] && find obj/ -type f -name "*.d")
