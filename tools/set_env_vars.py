import os
import pathlib

curr_dir = pathlib.Path(__file__).parent.absolute()

dragonfly_root = os.path.dirname(curr_dir)

try_again = False
python_root = ''
python_include = ''
python_lib = ''
while not os.path.isdir(python_root) or not os.path.isdir(python_include) or not os.path.isdir(python_lib):
    if try_again:
        print('That Anaconda or Python filepath is not valid. Please try again')
    try_again = True
    python_root = input('Enter the filepath of the Anaconda or Python directory (ex: C:\Anaconda3): ')
    python_include = os.path.join(python_root, 'include')
    python_lib = os.path.join(python_root, 'libs')

try_again = False
mingw_root = ''
mingw_bin = ''
while not os.path.isdir(mingw_root) or not os.path.exists(mingw_bin):
    if try_again:
        print('That MinGW filepath is not valid. Please try again')
    try_again = True
    mingw_root = input('Enter the filepath of the MinGW directory (ex: C:\MinGW): ')
    mingw_bin = os.path.join(mingw_root, 'bin')

try_again = False
swig_root = ''
while not os.path.isdir(swig_root):
    if try_again:
        print('That Swig filepath is not valid. Please try again')
    try_again = True
    swig_root = input('Enter the filepath of the Swig directory (ex: C:\swigwin-4.0.2): ')

try_again = False
ctypegen_root = ''
while not os.path.isdir(ctypegen_root):
    if try_again:
        print('That CTypeGen filepath is not valid. Please try again')
    try_again = True
    ctypegen_root = input('Enter the filepath of the CTypeGen directory (ex: C:\ctypesgen-ctypesgen-1-0-2): ')

os.system(f'setx DRAGONFLY {dragonfly_root}')
os.system(f'setx PYTHON_BASE {python_root}')
os.system(f'setx PYTHON_INCLUDE {python_include}')
os.system(f'setx PYTHON_LIB {python_lib}')
os.system(f'setx CTYPESGEN {ctypegen_root}')

curr_path = os.environ['PATH'] if os.environ.get('PATH') else ''
os.system(f'setx PATH "{mingw_bin};{swig_root};{curr_path}"')

python_path = os.environ['PYTHONPATH'] if os.environ.get('PYTHONPATH') else ''
pydragonfly = os.path.join(dragonfly_root, 'lang', 'python')
os.system(f'setx PYTHONPATH "{pydragonfly};{python_path}"')