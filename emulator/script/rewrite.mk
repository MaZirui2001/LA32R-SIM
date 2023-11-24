default: VCPU
include VCPU.mk
CXX 		= clang++
CXXFLAGS 	+= -Ofast -fno-exceptions -fPIE -Wno-unused-result -fPIC -pipe
LDFLAGS 	+= -rdynamic -fPIC
LIBS 		+= -ldl -pie -lSDL2
LINK 		= clang++