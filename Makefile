PREFIX = /opt/mine

BUILD ?= build

default: all

CFLAGS := -Wall -Wextra -g3 -fvisibility=default -fPIC `pkg-config --cflags elementary` -I.

LDFLAGS := -L$(BUILD) -lnotifiz `pkg-config --libs elementary`

all: $(BUILD)/libnotifiz.so $(BUILD)/example

$(BUILD)/libnotifiz.so: $(BUILD)/notifiz.o
	gcc -shared -o $@ $^

$(BUILD)/notifiz.o: notifiz.c
	@mkdir -p $(@D)
	gcc -c $^ $(CFLAGS) -o $@

$(BUILD)/example: $(BUILD)/example.o
	gcc $^ -o $@ $(LDFLAGS)

$(BUILD)/example.o: example.c $(BUILD)/libnotifiz.so
	gcc -c $< -o $@ $(CFLAGS)

clean:
	rm -rf $(BUILD)/notifiz.o $(BUILD)/libnotifiz.so $(BUILD)/example.o $(BUILD)/example
