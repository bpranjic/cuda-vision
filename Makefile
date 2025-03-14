BUILD_DIR = _build

.PHONY: build
build:
	@mkdir -p $(BUILD_DIR)
	cmake -S . -B $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR)

.PHONY: run
run: build
	@$(BUILD_DIR)/app/main

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)
