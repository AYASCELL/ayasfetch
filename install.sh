#!/usr/bin/env bash
#
# ayasfetch - Automated Installer & Updater
# https://github.com/AYASCELL/ayasfetch
#
set -e

COLOR_CYAN="\033[36m"
COLOR_GREEN="\033[32m"
COLOR_RED="\033[31m"
COLOR_YELLOW="\033[33m"
COLOR_RESET="\033[0m"

echo -e "${COLOR_CYAN}==>${COLOR_RESET} \033[1mayasfetch Kurulum / Güncelleme Sihirbazı\033[0m"

# 1. Bağımlılık kontrolleri (C derleyicisi ve make)
if ! command -v gcc >/dev/null 2>&1 && ! command -v cc >/dev/null 2>&1 && ! command -v clang >/dev/null 2>&1; then
    echo -e "${COLOR_RED}Hata:${COLOR_RESET} Sisteminizde C derleyicisi (gcc / clang) bulunamadı."
    echo -e "Lütfen derleyiciyi kurup tekrar deneyin:"
    echo -e "  - Arch / CachyOS: ${COLOR_YELLOW}sudo pacman -S base-devel gcc${COLOR_RESET}"
    echo -e "  - Ubuntu / Debian: ${COLOR_YELLOW}sudo apt install build-essential${COLOR_RESET}"
    echo -e "  - Fedora: ${COLOR_YELLOW}sudo dnf groupinstall \"Development Tools\"${COLOR_RESET}"
    exit 1
fi

if ! command -v make >/dev/null 2>&1; then
    echo -e "${COLOR_RED}Hata:${COLOR_RESET} Sisteminizde 'make' aracı bulunamadı."
    exit 1
fi

# 2. Geçici çalışma dizini oluştur (Çıkışta otomatik silinir)
TMP_DIR=$(mktemp -d -t ayasfetch-install-XXXXXX)
trap 'rm -rf "$TMP_DIR"' EXIT INT TERM

echo -e "${COLOR_CYAN}==>${COLOR_RESET} En güncel kaynak kod indiriliyor..."

if command -v git >/dev/null 2>&1; then
    git clone --depth 1 https://github.com/AYASCELL/ayasfetch.git "$TMP_DIR/ayasfetch" --quiet
    cd "$TMP_DIR/ayasfetch"
else
    mkdir -p "$TMP_DIR/ayasfetch"
    curl -sSL https://github.com/AYASCELL/ayasfetch/archive/refs/heads/main.tar.gz | tar -xz -C "$TMP_DIR/ayasfetch" --strip-components=1
    cd "$TMP_DIR/ayasfetch"
fi

# 3. Kaynaktan derle
echo -e "${COLOR_CYAN}==>${COLOR_RESET} Sisteminiz için derleniyor..."
make clean >/dev/null 2>&1 || true
make

# 4. Kur / Güncelle (/usr/local/bin)
echo -e "${COLOR_CYAN}==>${COLOR_RESET} Kurulum yapılıyor (/usr/local/bin)..."
if [ "$(id -u)" -eq 0 ]; then
    make install
else
    sudo make install
fi

echo -e "\n${COLOR_GREEN}✔ ayasfetch başarıyla kuruldu / güncellendi!${COLOR_RESET}"
echo -e "Terminalinizde ${COLOR_CYAN}ayasfetch${COLOR_RESET} yazarak kullanmaya başlayabilirsiniz.\n"
