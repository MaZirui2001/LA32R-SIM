default: VCPU
include VCPU.mk
CXXFLAGS += -O0 -std=c++14 -fno-exceptions -fPIE -Wno-unused-result -fPIC
LDFLAGS += -rdynamic -fPIC
LIBS += -ldl -pie -lSDL2
LINK := g++