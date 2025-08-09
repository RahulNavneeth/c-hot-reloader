CC      = clang
CFLAGS  = -Wall -O3 -Iinclude

BIN     = bin
SRC     = $(shell find src -name "*.c")
OBJ     = $(patsubst src/%.c, $(BIN)/%.o, $(SRC))
SRC_WO_R = $(filter-out src/main.c, $(SRC))

.PHONY: all clean dirs build watch run

all: dirs build

clean:
	rm -rf $(BIN)

dirs:
	mkdir -p $(BIN)

build: $(OBJ)
	$(CC) -o $(BIN)/main $^

$(BIN)/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build-watch: $(SRC_WO_R)
	$(CC) $(CFLAGS) -fPIC -shared $^ -o $(BIN)/watch.so

run:
	$(BIN)/main

watch:
	@$(MAKE) dirs
	@$(MAKE) build
	@$(MAKE) build-watch
	@trap 'kill 0' SIGINT; \
	 $(MAKE) run & \
	 echo "$(SRC_WO_R)" | tr " " "\n" | entr $(MAKE) build-watch & \
	 wait
