%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% make.m - Builds the matlab wrapper for the Dragonfly interface. Note that this script
%          re-compiles everything from source rather than using the pre-compiled
%          Dragonfly lib or dll file. This is necessary because it malloc and new 
%          calls need to be wrapped to use the Matlab memory manager (see mex_malloc.c and mex_malloc.cpp in src/core)
%
% MV 4/25/2011

if( ~ispc && ~isunix)
    error( 'Unsupported platform');
end

base_dir = '../..';
core_dir = [base_dir '/src/core'];
pipelib_dir = [core_dir '/PipeLib'];

core_sources = [core_dir '/Dragonfly.cpp ' core_dir '/MyCException.cpp ' core_dir '/MyCString.cpp ' core_dir '/mex_hack.cpp '];
pipelib_sources = [pipelib_dir '/UPipe.cpp ' pipelib_dir '/SocketPipe.cpp ' pipelib_dir '/Timing.cpp '];
mbg_sources = [base_dir '/include/mbglib/src/mbgdevio_import.c '];


sources = ['MatlabDragonfly.cpp ' core_sources pipelib_sources];
options = ['-v -D_MEX_FILE_ '];


% initialize include_dirs and libs
include_dirs = ['-I' base_dir '/include ' '-I' base_dir '/include/internal '];
libs = ['']

if (ispc)
    sources = [sources mbg_sources];
    include_dirs = [include_dirs '-I' base_dir '/include/mbglib/include '];
    libs = [base_dir '/include/mbglib/lib64/msc/mbgdevio.lib ' 'ws2_32.lib '];
elseif (isunix)
    if isempty(strfind(version, '2015b'))
        % we are not using version r2015b
        options = [options '-DUSE_LINUX '];
    else
        % we are using version 2015b
        % check which version of gcc is installed
        gcc = '';
        [res, gcc] = system('which gcc-4.7');
        if isempty(gcc)
            [res, gcc] = system('which gcc-4.8');
        end
        if isempty(gcc)
            disp('No viable gcc compiler')
            return
        end
        options = [ ...
            options ....
            '-DUSE_LINUX -DCpp11 -v CPPLIB_DIR=''/usr/lib/gcc/x86_64-linux-gnu/4.7/libstdc++.so'' -v GCC=''' gcc(1:end-1) ''' '];
    end %if
end %if

cmd = ['mex ' options include_dirs sources libs]
disp(cmd);
eval( cmd);
