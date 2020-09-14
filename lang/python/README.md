# PyDragonfly
Dragonfly support for Python 3

## Installing

### Windows
1. Install Python 3 (64 bit Python 3.7 is recommended)
2. Build Dragonfly following the README file in the root directory
3. Download [SWIG](http://www.swig.org/download.html) and save it to a safe spot
4. Create a `SWIG` [environment variable](https://docs.oracle.com/en/database/oracle/r-enterprise/1.5.1/oread/creating-and-modifying-environment-variables-on-windows.html#GUID-DD6F9982-60D5-48F6-8270-A27EC53807D0) for the SWIG root directory
5. Build the PyDragonfly solution found in the `lang/Python` directory using Visual Studio (Visual Studio 2019 is recommended). The build configuration and platform must match the Dragonfly build configuration in step 2 and the Python version. (`Release x64` for the 64 bit Python 3.7 is recommended)
6. Add the `lang/Python` directory to the `PYTHONPATH` environment variable 

## Build Message Definitions
1. Download [CTypesGen](https://github.com/davidjamesca/ctypesgen) and save it to a safe spot
2. Create a `CTYPESGEN` environment variable for the CTypesGen root directory
3. Download and install [MinGW](http://www.mingw.org/) (mingw32-gcc-bin package)
4. Add the MinGW `bin` directory to your path. `gcc` should be recognized as a command in the Command Prompt
5. Create message definitions python file by using `build_python_message_defs.py` in `/tools` directory.
```
python build_python_message_defs.py MESSAGE_DEFINITIONS_HEADER_FILE.h
```
6. Add the the message definitions directory to the `PYTHONPATH` environment variable 


## Migrating from Python 2.7
Programs migrating from Python 2.7 to Python 3 will need to change all references to PyDragonfly to pydragonfly (all lowercase), such as
```python
import pydragonfly

mod = pydragonfly.Dragonfly_Module()
```
All other code should work the same. You will get a deprecation warning telling you to move to the new `DragonflyModule` class. `Dragonfly_Module` 
will be removed in a future version.