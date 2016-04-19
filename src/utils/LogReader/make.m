function make()
    % make
    %
    % Builds mex file for reading binary message logs.

    base_dir = '../../..'

    options = '-D_MEX_FILE_ ';
    if( ispc)
         % nothing to do
    elseif( isunix)
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
                gccver = '4.8';
            else
                gccver = '4.7';
            end
            if isempty(gcc)
                disp('No viable gcc compiler')
                return
            end
            % find correct libstdc library
            %[res, libstdc] = system(['locate libstdc++.so | grep gcc | grep ' gccver]);
            %options = [options '-DUSE_LINUX -DC++11 -v CPPLIB_DIR=''' libstdc(1:end-1)  ''' -v GCC=''' gcc(1:end-1) ''' '];
            options = [options '-DUSE_LINUX -DCpp11 -v GCC=''' gcc(1:end-1) ''' '];
        end %if
    end %if

    options = [options ' -I' base_dir '/src/core' ' -I' base_dir '/include' ' -I' base_dir '/include/internal'];
    options = [options ' -I../../modules/QuickLogger' ' -I' base_dir '/lang/matlab'];

    additional_source_files = [base_dir '/src/core/MyCException.cpp ' base_dir '/src/core/MyCString.cpp'];

    cmd = ['mex ' options ' LogReader.cpp ' additional_source_files]
    eval( cmd);

end %function
