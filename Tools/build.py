import multiprocessing
import os
import sys
import shutil
from colorama import Fore, Style
import subprocess
import distutils.spawn

buildPath = 'Build'
projectName = os.path.basename(os.getcwd())

if not os.path.isdir('Tools/ExheaderCli/Build') or not os.path.isdir('Data/musl'):
    print("Run setup.py before building");
    exit(1)

def status(msg: str):
    print(Style.BRIGHT + Fore.CYAN + msg + Fore.RESET + Style.RESET_ALL)


if len(sys.argv) >= 2 and sys.argv[1] == 'clean':
    shutil.rmtree(buildPath)

if not os.path.exists(buildPath):
    os.mkdir(buildPath)
    os.chdir(buildPath)
    subprocess.run("cmake ..", shell=True)
    os.chdir('..')

status("Generating Linker Script")
os.system("find Symbols -type f -name '*.sym' -exec cat {} + >" + f"{buildPath}/Symbols.ld")

os.chdir(buildPath)

verbose = ''
if len(sys.argv) >= 2 and sys.argv[1] == 'verbose':
    verbose = 'VERBOSE=1'
result = subprocess.run(f'make -j {multiprocessing.cpu_count()} {verbose}', shell=True)
if result.returncode != 0:
    exit()

os.chdir('..')

status("Generating Binary")
subprocess.run(f"llvm-objcopy -O binary {buildPath}/{projectName}.axf {buildPath}/{projectName}.bin", shell=True)

status("Inserting new code")

code_offset = int(subprocess.check_output(["Tools/ExheaderCli/Build/ExheaderCli", "printCodeOffset=true", "Data/exheader.bin"]), 16)
new_size = os.stat(f"{buildPath}/{projectName}.bin").st_size + 32

subprocess.run(["Tools/ExheaderCli/Build/ExheaderCli", "patchCode=true", "inFileExh=Data/exheader.bin", f"inFileNewCode=Build/{projectName}.bin", f"out={buildPath}/code.bin", f"inFileMap={buildPath}/{projectName}.map", "Data/code.bin"])

flips = distutils.spawn.find_executable("flips")
if (flips is not None):
    status("Generating code.bps patch")
    subprocess.run([flips, "Data/code.bin", "Build/code.bin", "Build/code.bps"])
else:
    status("Warning: flips not found. Not generating code.bps")

status("Generating exheader.bin")

subprocess.run(["Tools/ExheaderCli/Build/ExheaderCli", f"newSize={new_size}", f"out={buildPath}/exheader.bin", "Data/exheader.bin"])
