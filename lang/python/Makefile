BASE_DIR     = ../..
SWIG         = swig
SYMBOLS      = -DUSE_LINUX
GCC          = g++
CPPFLAGS     = -shared -Wall -Wno-deprecated -pthread -fPIC
LIBS         = -L${BASE_DIR}/lib -lDragonfly
PY_VERSION   = 3
PYTHON       = /usr/bin/python${PY_VERSION}
PY_CONFIG    = python${PY_VERSION}-config
PY_INC      += $(shell ${PY_CONFIG} --includes)
PY_LD_FLAGS += $(shell ${PY_CONFIG} --ldflags)
INCLUDES     = -I${BASE_DIR}/include -I${BASE_DIR}/include/internal

all:  _pydragonfly.so

pydragonfly.py: pydragonfly.i
	${SWIG} ${SYMBOLS} ${INCLUDES} -c++ -python pydragonfly.i

_pydragonfly.so:  pydragonfly.py
	${GCC} ${CPPFLAGS} ${SYMBOLS} ${INCLUDES} -I${PY_INC} ${LIBS} ${PY_LD_FLAGS} pydragonfly_wrap.cxx -o _pydragonfly.so

clean:
	rm -f *.so
	rm -f *.cxx
	rm -f pydragonfly.py
	rm -f *.pyc
