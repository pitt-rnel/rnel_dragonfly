import os
import sys
import subprocess as sp
from argparse import ArgumentParser

if __name__ == '__main__':

    description = 'Converts C header files to python files'
    parser = ArgumentParser(description = description)
    parser.add_argument(type=str, dest='input_file')
    args = parser.parse_args()
    print('Processing %s ...' % (args.input_file))

    input_file = os.path.abspath(args.input_file)
    base_dir, filename = os.path.split(input_file)
    filename_root, filename_ext = os.path.splitext(filename)

    ctypesgen = os.getenv('CTYPESGEN')
    if ctypesgen:
        ctypesgen_path = os.path.join(ctypesgen, 'run.py')
        output_file = os.path.join(base_dir, filename_root) + '.py'

        print('%s')

        python_exe = sys.executable
        include_path = os.path.join('..', 'include')
        proc = sp.call([python_exe, ctypesgen_path, 
                       '--includedir="%s"' % (include_path), 
                       '-a', '-o', output_file, input_file])
    else:
        print('Error: CTYPESGEN environment variable must be set')
