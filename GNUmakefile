.DEFAULT_GOAL := opt

MAIN_SRCS = **.cpp

EMU_CORE_ROOT = EmuCore/

COMPILER = g++
WARNINGS =
STD = -std=c++20
EXTRA_LIBS = -lstdc++fs
SIMD = -mavx2 -mfma
INSTRUCTION_SETS = $(SIMD)
COMMON_COMPILER_ARGS = $(WARNINGS) $(STD) $(INSTRUCTION_SETS) $(EXTRA_LIBS)
SOURCES = $(MAIN_SRCS) $(EMU_CORE_SRCS)
OUTPUT_BASE = ./build/emu_math_tests

# Want to delete these flags at a later point, just to tidy up during changes-for-linux branch
TMP_FLAGS = 

OPT_OUT = $(OUTPUT_BASE)
DBG_OUT = $(OUTPUT_BASE)_dbg

COMMON_COMPILE = $(COMPILER) $(COMMON_COMPILER_ARGS) ${TMP_FLAGS}
DBG_COMPILE = $(COMMON_COMPILE) -o $(DBG_OUT)
FULL_OPT_COMPILE = $(COMMON_COMPILE) -O3 -o $(OPT_OUT)

clean_opt:
	rm -rf $(OPT_OUT)

clean_dbg:
	rm -rf $(DBG_OUT)

clean:
	rm -rf ./build
	mkdir ./build

opt:
	$(FULL_OPT_COMPILE) $(SOURCES)

opt_rebuild: clean_opt opt


dbg:
	$(DBG_COMPILE) $(SOURCES)

dbg_rebuild: clean_dbg dbg
	

