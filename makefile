CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC

INC_DIR = include
DIST_DIR = src/distribution
FIO_DIR = src/file_io

INCLUDES = -I$(INC_DIR) -I$(DIST_DIR) -I$(FIO_DIR)

BUILD ?= release

ifeq ($(BUILD), release)
    CXXFLAGS += -O3
else ifeq ($(BUILD), debug)
    CXXFLAGS += -g -O0
else ifeq ($(BUILD), minsize)
    CXXFLAGS += -Os
else ifeq ($(BUILD), relwithdebinfo)
    CXXFLAGS += -O2 -g
endif


TARGET   = cargo_app
LIB_DIST = $(DIST_DIR)/libdistribution.a
LIB_FIO  = $(FIO_DIR)/libfile_io.so

all: $(TARGET)

$(DIST_DIR)/distribution.o: $(DIST_DIR)/distribution.cpp $(DIST_DIR)/distribution.h $(INC_DIR)/types.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(FIO_DIR)/file_io.o: $(FIO_DIR)/file_io.cpp $(FIO_DIR)/file_io.h $(INC_DIR)/types.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@



$(LIB_DIST): $(DIST_DIR)/distribution.o
	ar rcs $@ $<

$(LIB_FIO): $(FIO_DIR)/file_io.o
	$(CXX) -shared $< -o $@


$(TARGET): $(LIB_DIST) $(LIB_FIO) src/main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) src/main.cpp \
		-L$(DIST_DIR) -ldistribution \
		-L$(FIO_DIR) -lfile_io \
		-Wl,-rpath,./$(FIO_DIR) \
		-o $@


clean:
	rm -f $(TARGET) \
		$(DIST_DIR)/*.o $(DIST_DIR)/*.a \
		$(FIO_DIR)/*.o  $(FIO_DIR)/*.so
