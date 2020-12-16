BASE_DIR     = ../..
SWIG         = swig
SYMBOLS      = -DUSE_LINUX
GCC          = g++
CPPFLAGS     = -shared -Wall -Wno-deprecated -pthread -fPIC
LIBS         = -L${BASE_DIR}/lib -lDragonfly
PY_VERSION   = 3.7
PYTHON       = /usr/bin/python${PY_VERSION}
PY_CONFIG    = python${PY_VERSION}-config
PY_INC      += $(shell ${PY_CONFIG} --includes)
PY_LD_FLAGS += $(shell ${PY_CONFIG} --ldflags)
INCLUDES     = -I${BASE_DIR}/include -I${BASE_DIR}/include/internal
CTYPESGEN    = /opt/git/ctypesgen

all:  _pydragonfly.so dragonfly_types.py

pydragonfly.py: pydragonfly.i
        ${SWIG} ${SYMBOLS} ${INCLUDES} -c++ -python pydragonfly.i

_pydragonfly.so:  pydragonfly.py
        ${GCC} ${CPPFLAGS} ${SYMBOLS} ${INCLUDES} -I${PY_INC} ${LIBS} ${PY_LD_FLAGS} pydragonfly_wrap.cxx -o _pydragonfly.so

dragonfly_types.py:
        ${PYTHON} ${CTYPESGEN}/run.py `pwd`/../../include/Dragonfly_types.h -o `pwd`/dragonfly_types.py

clean:
        rm -f *.so
        rm -f *.cxx
        rm -f pydragonfly.py
        rm -f *.pyc
        rm -f dragonfly_types.xml
        rm -f dragonfly_types.py