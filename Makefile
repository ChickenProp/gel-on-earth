.PHONY: game clean

all: game

game:
	$(MAKE) -C src

clean:
	$(MAKE) clean -C src
