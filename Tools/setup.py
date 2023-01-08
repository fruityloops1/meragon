import os
import subprocess
import tarfile
import multiprocessing
import importlib.util

def tryCompileExheaderCli():
    print("Compiling ExheaderCli")

    os.mkdir('Tools/ExheaderCli/Build')
    os.chdir('Tools/ExheaderCli/Build')
    subprocess.run(['cmake', '..'])
    subprocess.run(['make'])
    os.chdir('../../..')

musl_ver = 'musl-1.2.3'
musl_source_tar_name = musl_ver + '.tar.gz'
musl_source = "https://musl.libc.org/releases/" + musl_source_tar_name

libunwind_ver = "libunwind-1.6.2"
libunwind_source_tar_name = libunwind_ver + ".tar.gz"
libunwind_source = "https://download.savannah.nongnu.org/releases/libunwind/" + libunwind_source_tar_name

def tryGetAndCompileMusl():
    print(f"Downloading musl")

    os.chdir('Data')
    subprocess.run(['curl', '-O', musl_source])

    print(f"Extracting musl")

    src_tar = tarfile.open(musl_source_tar_name)
    src_tar.extractall('.')
    src_tar.close()

    os.remove(musl_source_tar_name)

    print(f"Building musl")

    os.rename(musl_ver, 'musl')
    os.chdir('musl')

    env = os.environ.copy()
    env["CC"] = "clang"
    env["AR"] = "llvm-ar"
    env["RANLIB"] = "llvm-ranlib"
    env["LIBCC"] = " "
    env["CFLAGS"] = "-target armv6k-none-eabi -mtune=mpcore -mfloat-abi=hard -mtp=soft -mfpu=vfpv2"
    env["LDFLAGS"] = "-Wl,--unresolved-symbols=ignore-all"

    subprocess.run(["./configure", "--target=armv6k-none-eabi"], env=env)

    subprocess.run(["make", f"-j {multiprocessing.cpu_count()}"])

    os.chdir("../..")

def tryCompileCompilerRtBuiltins():
    print(f"Compiling compiler-rt")

    os.chdir('Data/compiler-rt')
    spec = importlib.util.spec_from_file_location("build", "build.py")
    build = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(build)

    build.compile()
    

if (not os.path.isdir('Tools/ExheaderCli/Build')):
    tryCompileExheaderCli()
if (not os.path.isdir('Data/musl')):
    tryGetAndCompileMusl()
if (not os.path.isdir('Data/compiler-rt/Build')):
    tryCompileCompilerRtBuiltins()

