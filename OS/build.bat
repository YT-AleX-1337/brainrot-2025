::Requirements: nasm, x86_64-elf gcc toolchain (see below), python 3.11+, bin2hex.exe (downloaded from http://tomeko.net/bin/bin2hex/bin2hex.exe)
::Open command prompt and run "pip install pillow" and "pip install mido"

::Custom toolchain built with Cygwin
::gcc 10.2.0
::binutils 2.35.2
::mtools 4.0.42
::Followed this tutorial by nanobyte: http://youtube.com/watch?v=TgIdFVOV_0U
::(watch the full video or you might miss some important stuff)
::IMPORTANT: at 9:04, set TARGET to x86_64-elf, not i686-elf!

del bin\* /q

cd src\Bootloader

nasm Bootloader.asm -f bin -o ..\..\bin\Bootloader.bin

cd ..\Utils

ResGenerator.py

cd ..\Kernel

nasm Kernel.asm -f elf64 -o ..\..\bin\KernelASM.o
x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c -pipe -Wno-int-to-pointer-cast -Wno-write-strings Kernel.cpp -o ..\..\bin\Kernel.o
x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c -pipe -Wno-int-to-pointer-cast -Wno-write-strings HAL.cpp -o ..\..\bin\HAL.o
x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c -pipe -Wno-int-to-pointer-cast -Wno-write-strings HAL\IDT.cpp -o ..\..\bin\HAL_IDT.o
x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c -pipe -Wno-int-to-pointer-cast -Wno-write-strings HAL\ISR.cpp -o ..\..\bin\HAL_ISR.o
x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c -pipe -Wno-int-to-pointer-cast -Wno-write-strings HAL\IRQ.cpp -o ..\..\bin\HAL_IRQ.o
x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c -pipe -Wno-int-to-pointer-cast -Wno-write-strings HAL\Memory.cpp -o ..\..\bin\HAL_Memory.o
x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c -pipe -Wno-int-to-pointer-cast -Wno-write-strings HAL\PIC.cpp -o ..\..\bin\HAL_PIC.o
x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c -pipe -Wno-int-to-pointer-cast -Wno-write-strings Keyboard.cpp -o ..\..\bin\Keyboard.o
x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c -pipe -Wno-int-to-pointer-cast -Wno-write-strings Math.cpp -o ..\..\bin\Math.o
x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c -pipe -Wno-int-to-pointer-cast -Wno-write-strings Scenes.cpp -o ..\..\bin\Scenes.o  
x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c -pipe -Wno-int-to-pointer-cast -Wno-write-strings Sound.cpp -o ..\..\bin\Sound.o    
x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c -pipe -Wno-int-to-pointer-cast -Wno-write-strings String.cpp -o ..\..\bin\String.o
x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c -pipe -Wno-int-to-pointer-cast -Wno-write-strings Time.cpp -o ..\..\bin\Time.o
x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c -pipe -Wno-int-to-pointer-cast -Wno-write-strings UI.cpp -o ..\..\bin\UI.o
x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c -pipe -Wno-int-to-pointer-cast -Wno-write-strings Video.cpp -o ..\..\bin\Video.o
x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c -pipe -Wno-int-to-pointer-cast -Wno-write-strings Resources.cpp -o ..\..\bin\Resources.o

cd ..\..\bin

x86_64-elf-ld KernelASM.o Kernel.o HAL.o HAL_IDT.o HAL_ISR.o HAL_IRQ.o HAL_Memory.o HAL_PIC.o Keyboard.o Math.o Scenes.o Sound.o String.o Time.o UI.o Video.o Resources.o -T ..\Linker.ld --oformat binary -o Kernel.bin
copy /b Bootloader.bin+Kernel.bin OS.bin
for /f "usebackq" %%s in ('OS.bin') do set size=%%~zs
echo.times (1 + 127 * 3) * 512 - 4 - %size% db 0 >> Dummy.asm
echo.db ".END" >> Dummy.asm
nasm Dummy.asm -f bin -o Dummy.bin
copy /b OS.bin+Dummy.bin OS.img

cd ..

bin2hex --i bin\OS.img --o OS.dat --s ", "

pause
test