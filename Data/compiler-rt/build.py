import os
import subprocess

def compile():
    files = []

    if not os.path.isdir('Build'):
        os.mkdir('Build')
    
    for folder in ['Source', 'Source/arm']:
        for filename in os.listdir(folder):
            f = os.path.join(folder, filename)
            if not filename.endswith('.h') and not filename.endswith(".inc") and not os.path.isdir(f):
                if filename.endswith('.S'):
                    subprocess.run(["clang", "-target", "armv6k-none-eabi", "-mtune=mpcore", "-mfloat-abi=hard", "-mtp=soft", "-mfpu=vfpv2", f"-isystem {os.path.abspath('../musl/include')}", f"-isystem {os.path.abspath('../musl/arch/arm')}", f"-isystem {os.path.abspath('../musl/arch/generic')}", f"-isystem {os.path.abspath('../musl/include')}", f"-isystem {os.path.abspath('../musl/obj/include')}", "-x", "assembler-with-cpp", "-c", f, "-o", f'Build/{filename}.o'])
                else:
                    subprocess.run(["clang", "-target", "armv6k-none-eabi", "-mtune=mpcore", "-mfloat-abi=hard", "-mtp=soft", "-mfpu=vfpv2", f"-isystem {os.path.abspath('../musl/include')}", f"-isystem {os.path.abspath('../musl/arch/arm')}", f"-isystem {os.path.abspath('../musl/arch/generic')}", f"-isystem {os.path.abspath('../musl/include')}", f"-isystem {os.path.abspath('../musl/obj/include')}", "-c", f, "-o", f'Build/{filename}.o'])
                files.append(filename)
    
    
    for filename in files:
        subprocess.run(["llvm-ar", "q", "Build/builtins.a", os.path.join('Build', f'{filename}.o')])