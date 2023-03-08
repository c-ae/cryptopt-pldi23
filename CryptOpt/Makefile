ROOT           := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

NODE_DIR       := $(ROOT)/bins/node
NODE           := $(ROOT)/bins/node/bin/node
NODE_VERSION   := 18.14.2

PATH           := $(NODE_DIR)/bin:$(PATH)

BUILT_CRYPTOPT := $(ROOT)/dist/CryptOpt.js

.PHONY: all build check clean deepclean

all: clean $(BUILT_CRYPTOPT)
build: $(BUILT_CRYPTOPT)

$(NODE):
	mkdir -p ./bins
	curl -L https://nodejs.org/dist/v$(NODE_VERSION)/node-v$(NODE_VERSION)-linux-x64.tar.xz | tar --extract --xz --directory ./bins
	mv -f ./bins/node-v$(NODE_VERSION)-linux-x64 "$(NODE_DIR)"

node_modules: 
	@echo "Installing dependencies"
	@CFLAGS="-I$(NODE_DIR)/include" PATH=$(PATH) npm $$(test -e ./package-lock.json && echo 'clean-install' || echo "install")

$(BUILT_CRYPTOPT): $(NODE) node_modules $(shell find ./src -type f -name '*ts')
	@echo "Building CryptOpt"
	@PATH=$(PATH) npm run bundle
	@test -e "$(@)" && touch $(@) && echo "Successfully built CryptOpt. :)"

check: $(BUILT_CRYPTOPT)
	PATH=$(PATH) npm run test-no-watch

clean:
	@rm -rf ./dist ./coverage ./bundle.tar.gz ./bundle.zip

deepclean: clean
	rm -rf ./bins ./node_modules package-lock.json

install-zsh:
	install -v $(ROOT)/completion/_cryptopt /usr/local/share/zsh/site-functions && echo -e "Installed successfully\nRestart your shell to enjoy\n"

BUNDLE_FILES:=$(shell find . -type f ! -path './bundle*' -a ! -path '*node_modules*' -a ! -path '*results*' -a ! -path '*.git*' -a ! -path './bins/*' -a ! -path '*dist*')

dist: bundle.tar.gz bundle.zip

bundle.tar.gz: $(BUNDLE_FILES)
	tar czvf ${@} $(^)

bundle.zip: $(BUNDLE_FILES)
	zip ${@} $(^)
