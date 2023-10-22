default: VCPU
include VCPU.mk
CXXFLAGS += -MMD -O2 -std=c++14 -fno-exceptions -fPIE -Wno-unused-result
LDFLAGS += -O2 -rdynamic -fPIC
LIBS += -lreadline -ldl -pie -lSDL2
LINK := g++