BASE_DIR   = ../..
SWIG       = swig
SYMBOLS    = -DUSE_LINUX
GCC        = g++
CPPFLAGS   = -shared -Wall -Wno-deprecated -pthread -fPIC
LIBS       = -L${BASE_DIR}/lib -lDragonfly
PY_VERSION = 3.8
PY_INC     = /usr/include/python${PY_VERSION}
PYTHON     = /usr/bin/python${PY_VERSION}
INCLUDES   = -I${BASE_DIR}/include -I${BASE_DIR}/include/internal

all:  _pydragonfly.so dragonfly_types.py

pydragonfly.py: pydragonfly.i
	${SWIG} ${SYMBOLS} ${INCLUDES} -c++ -python pydragonfly.i

_pydragonfly.so:  pydragonfly.py
	${GCC} ${CPPFLAGS} ${INCLUDES} ${SYMBOLS} -I${PY_INC} ${LIBS} pydragonfly_wrap.cxx -o _pydragonfly.so -lpython${PY_VERSION} -lDragonfly

dragonfly_types.py:
	${PYTHON} ${CTYPESGEN}/run.py `pwd`/../../include/Dragonfly_types.h -o `pwd`/dragonfly_types.py

clean:
	rm -f *.so
	rm -f *.cxx
	rm -f PyDragonfly.py
	rm -f *.pyc
	rm -f Dragonfly_types.xml
	rm -f Dragonfly_types.py

