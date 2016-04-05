#
# windows power shell script to create matlab and python message definition files from C header file
#
# by: Max Novelli
#     max.novelli@pitt.edu
#     2016/03/28
#

# get header file from command line
$HFILE=$args[0]
Write-Host Dragonfly Messages file : $HFILE

# function to retrieve the location of the running script
# https://blogs.msdn.microsoft.com/powershell/2007/06/19/get-scriptdirectory-to-the-rescue/
function Get-ScriptDirectory {
	$invocation = (Get-Variable MyInvocation -Scope 1).Value
	Split-Path $Invocation.MyCommand.Path
}

# get current folder
$TOOLS_DIR = (Get-ScriptDirectory)
Write-Host Dragonfly Tools folder : $TOOLS_DIR

# get base installation of dragonfly
$DRAGONFLY = (get-item $TOOLS_DIR).parent.parent
Write-Host Dragonfly base installation : $DRAGONFLY

# generate python message defs
Write-Host "Generating Python module..."
Try {
	& python ${TOOLS_DIR}/build_python_message_defs.py ${HFILE}
	Write-Host "===> SUCCESS"
}
Catch {
	Write-Host Error
	Write-Host - Message  : $_.Exception.Message
	Write-Host - Location : $_.Exception.ItemName
	Write-Host "===> FAILED"
}
Write-Host "...Done"

# generate matlab message defs
Write-Host "Generating Matlab file..."
Try {
	& $env:MATLAB_EXE -nodesktop -nosplash -nojvm -r "addpath('${TOOLS_DIR}'); build_matlab_message_defs('${HFILE}'); exit;"
	Write-Host "===> SUCCESS"
}
Catch {
	Write-Host "===> FAILED"
}
Write-Host "...Done"
