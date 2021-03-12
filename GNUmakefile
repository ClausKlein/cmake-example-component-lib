#

#XXX GENERATOR?="Unix Makefiles"
GENERATOR?=Ninja

STAGE_DIR?=$(CURDIR)/stage
BUILD_TYPE?=Debug
CMAKE_PRESET:=-G "$(GENERATOR)" -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
 -DCMAKE_PREFIX_PATH=$(STAGE_DIR) -DCMAKE_CXX_STANDARD=20 -DBUILD_SHARED_LIBS=1
# Note: not needed -DCMAKE_CXX_COMPILER_LAUNCHER=ccache

# export CXX=/usr/local/bin/g++-10
# export GCOV=/usr/local/bin/gcov-10
## export CXX=clang++
## export GCOV=llvm-cov
export CXX=g++
export GCOV=gcov

export CPM_USE_LOCAL_PACKAGES=0
export CPM_SOURCE_CACHE=${HOME}/.cache/CPM

MACHINE:=$(shell uname -m)
PROJECT_NAME:=$(shell basename $(CURDIR))
BUILD_DIR?=./build-$(PROJECT_NAME)-$(MACHINE)-$(BUILD_TYPE)

.PHONY: update format all test standalone gcov tidy doc modernize clean distclean

# the default target does just all, but neither standalone nor doc
test: gcov

clean:
	rm -rf $(BUILD_DIR) reports/gcov/*.* build build-*

distclean: clean
	rm -rf $(STAGE_DIR)

# update CPM.cmake
update:
	pip3 install jinja2 Pygments gcovr cmake_format==0.6.13 pyyaml
	wget -q -O cmake/CPM.cmake https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/get_cpm.cmake
	wget -q -O cmake/ProjectWarningsAsErrors.cmake https://raw.githubusercontent.com/approvals/ApprovalTests.cpp/master/CMake/WarningsAsErrors.cmake

# install the library to stagedir
install:
	cmake -S . -B $(BUILD_DIR)/$@ ${CMAKE_PRESET} -DCMAKE_INSTALL_PREFIX=$(STAGE_DIR)
	cmake --build $(BUILD_DIR)/$@ --target $@
	perl -i.bak -p -e 's#-W[-\w]+\b##g;' -e 's#-I($$CPM_SOURCE_CACHE)#-isystem $$1#g;' $(BUILD_DIR)/$@/compile_commands.json
	run-clang-tidy.py -p $(BUILD_DIR)/$@ -quiet -header-filter='$(CURDIR)/.*' source # Note: only local sources! CK

# test the library
test: install
	rm -rf $(BUILD_DIR)
	cmake -S $@ -B $(BUILD_DIR)/$@ ${CMAKE_PRESET} -DTEST_INSTALLED_VERSION=1
	perl -i.bak -p -e 's#-W[-\w]+\b##g;' -e 's#-I($$CPM_SOURCE_CACHE)#-isystem $$1#g;' $(BUILD_DIR)/$@/compile_commands.json
	cmake --build $(BUILD_DIR)/$@
	cmake --build $(BUILD_DIR)/$@ --target $@
	run-clang-tidy.py -p $(BUILD_DIR)/$@ -quiet -header-filter='$(CURDIR)/.*' test/source # Note: only local sources! CK

# all together
all:
	cmake -S $@ -B $(BUILD_DIR)/$@ ${CMAKE_PRESET} -DENABLE_TEST_COVERAGE=1    # NO! -DUSE_STATIC_ANALYZER=clang-tidy CK
	cmake --build $(BUILD_DIR)/$@
	cmake --build $(BUILD_DIR)/$@ --target test
	perl -i.bak -p -e 's#-W[-\w]+\b##g;' -e 's#-I($$CPM_SOURCE_CACHE)#-isystem $$1#g;' $(BUILD_DIR)/$@/compile_commands.json
	gcovr --root . #XXX --verbose

tidy: all
	run-clang-tidy.py -p $(BUILD_DIR)/all -quiet -header-filter='$(CURDIR)/.*' $(CURDIR)   # Note: only local sources! CK

gcov: all
	gcovr -r . --html-title $(PROJECT_NAME) --html-detail $(CURDIR)/reports/gcov/index.html
	perl -i.bak -pe 's#class="headerValue">./<#class="headerValue">$(PROJECT_NAME)<#g;' $(CURDIR)/reports/gcov/index.html

# GenerateDocs
doc:
	cmake -S documentation -B $(BUILD_DIR)/documentation ${CMAKE_PRESET}
	cmake --build $(BUILD_DIR)/documentation --target GenerateDocs

format: distclean
	find . -name CMakeLists.txt | xargs cmake-format -i
	find . -type f -name '*.cmake' | xargs cmake-format -i
	find . -name '*.cxx' | xargs clang-format -i
	find . -name '*.h' | xargs clang-format -i

standalone:
	cmake -S $@ -B $(BUILD_DIR)/$@ ${CMAKE_PRESET}
	perl -i.bak -p -e 's#-W[-\w]+\b##g;' -e 's#-I($$CPM_SOURCE_CACHE)#-isystem $$1#g;' $(BUILD_DIR)/$@/compile_commands.json
	cmake --build $(BUILD_DIR)/$@

# modernize the library sources
modernize: standalone
	run-clang-tidy.py -p $(BUILD_DIR)/standalone -quiet -header-filter='$(CURDIR)/.*' \
	 -checks='-*,modernize-*' -j1 -fix $(CURDIR) # Note: only local sources! CK
