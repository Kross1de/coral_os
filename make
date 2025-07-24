git submodule update --init
(cd limine && make > /dev/null 2>&1)

clear

rm -rf build/* && mkdir -p build/iso

C="clang -include std.h"
LD="ld.lld"

CFLAGS="-O2 -march=x86-64 -mtune=generic -m64 -ffreestanding -nostdlib -fno-builtin -fno-stack-protector -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -mno-3dnow"
LDFLAGS="-nostdlib -static -no-dynamic-linker"

${C} -c kernel/init.c -o build/init.o ${CFLAGS} || exit 1;
${C} -c kernel/terminal.c -o build/terminal.o ${CFLAGS} || exit 1;
${C} -c kernel/mem.c -o build/mem.o ${CFLAGS} || exit 1;
${C} -c kernel/data.c -o build/data.o ${CFLAGS} || exit 1;
${C} -c kernel/page.c -o build/page.o ${CFLAGS} || exit 1;
${LD} build/init.o build/terminal.o build/mem.o build/data.o build/page.o -o build/kernel -T tools/linker.kernel ${LDFLAGS}

cp build/kernel tools/limine.cfg limine/limine-bios.sys limine/limine-bios-cd.bin limine/limine-uefi-cd.bin build/iso

gzip build/iso/kernel

xorriso -as mkisofs -b limine-bios-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table --efi-boot limine-uefi-cd.bin -efi-boot-part --efi-boot-image --protective-msdos-label build/iso -o build/coral_os.iso > /dev/null 2>&1

limine/limine bios-install build/coral_os.iso > /dev/null 2>&1