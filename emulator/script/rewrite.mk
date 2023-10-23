default: VCPU
include VCPU.mk
CXXFLAGS += -O2 -std=c++14 -fno-exceptions -fPIE -Wno-unused-result 
LDFLAGS += -rdynamic -fPIC -Wl,-O1
LIBS += -lreadline -ldl -pie -lSDL2
LINK := g++