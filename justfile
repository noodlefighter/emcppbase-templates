FW_OPENOCD_PATH := "~/sdk/MRS_Toolchain_Linux_x64_V1.80/OpenOCD"
FW_BUILD_DIR := "./build/fw"

default:
    @just --list

all: pc fw

init:
    # 在自建镜象站的时候，可以用 just mirror-pull 代替此条命令拉取子模块
    git submodule update --init --recursive




pc:
    mkdir -p build/pc
    cd build/pc && cmake -DCMAKE_BUILD_TYPE=Debug -GNinja ../../target/pc
    cd build/pc && ninja

fw debug="1":
    mkdir -p build/fw
    cd build/fw && cmake -DCMAKE_BUILD_TYPE={{ if debug != "0" {"Debug"} else {"Release"} }} -GNinja ../../target/fw
    cd build/fw && ninja

flash elf="app": (fw "1")
    {{ FW_OPENOCD_PATH }}/bin/openocd -f {{ FW_OPENOCD_PATH }}/bin/wch-riscv.cfg \
        -c init -c halt -c "flash erase_sector wch_riscv 0 last" \
        -c "program {{ FW_BUILD_DIR }}/{{ elf }}" \
        -c "flash protect wch_riscv 0 last off" \
        -c wlink_reset_resume -c exit

flash_app:
    just flash project-root/entrance/app

unlock:
    {{ FW_OPENOCD_PATH }}/bin/openocd -f {{ FW_OPENOCD_PATH }}/bin/wch-riscv.cfg \
    -c init -c halt -c "flash protect wch_riscv 0 last  off " -c exit

test: pc
    ./build/pc/test/test

clean:
    rm -rf build

# 子模块镜拉取/推送
MIRROR_NORMAL := "--site-ssh=\"ssh://git@your-mirror.com/{}.git\" --site-http=\"http://your-mirror.com/{}\""
mirror-pull:
    python3 ./scripts/git-mirror.py {{ MIRROR_NORMAL }} update
mirror-push:
    python3 ./scripts/git-mirror.py {{ MIRROR_NORMAL }} push
