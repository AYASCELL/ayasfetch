# ayasfetch 🚀

A lightning-fast, ultra-modern system information fetch tool written in pure C.

`ayasfetch` takes the beloved concept of terminal fetch utilities (like neofetch or fastfetch) and gives it a highly customized, elegant visual touch featuring:
- Beautiful single-line rounded borders.
- Lightweight, zero-dependency C codebase for instant execution.
- Dynamic OS logo detection.

## 📸 Preview
<img width="1124" height="393" alt="image" src="https://github.com/user-attachments/assets/542682ac-f2f0-4e62-be35-051e9c8d3ec8" />

## 🧩 Dependencies
`ayasfetch` is incredibly lightweight, but relies on a few standards to look and work perfectly:
- **iproute2**: For fetching the local IP address (`ip` command).
- **make & gcc**: For compiling the source code.

## 🚀 Installation

There are two ways to install `ayasfetch`: using the pre-compiled binary (easiest) or compiling from source.

### Method 1: Pre-compiled Binary (Easy)
If you don't want to compile from source, you can simply download the standalone binary from the Releases page and install it directly:

```bash
# 1. Download the latest binary from GitHub Releases
wget https://github.com/AYASCELL/ayasfetch/releases/latest/download/ayasfetch-x86_64-linux

# 2. Move it to your local bin directory (Installs the app)
sudo mv ayasfetch-x86_64-linux /usr/local/bin/ayasfetch

# 3. Give it execution permissions
sudo chmod +x /usr/local/bin/ayasfetch
```
*That's it! You can now just type `ayasfetch` in your terminal.*

### Method 2: Compile from Source

To compile `ayasfetch` from source, all you need is a C compiler (like `gcc`) and `make`.

```bash
git clone https://github.com/ayascell/ayasfetch.git
cd ayasfetch
make
```

You can test it locally by running `./ayasfetch`.

## 📦 Installation

To install `ayasfetch` system-wide so you can run it from anywhere by just typing `ayasfetch`:

```bash
sudo make install
```

This will place the binary in `/usr/local/bin/`.

*(Note for Packagers: The Makefile fully supports `PREFIX` and `DESTDIR` variables, making it natively compatible with AUR PKGBUILDs and other package managers!)*

## 🗑️ Uninstallation

If you ever want to remove it:

```bash
sudo make uninstall
```

## ⚙️ Configuration
The design and ASCII arts are built directly into the C code for maximum performance. If you want to change colors or add new logos, simply edit `ayasfetch.c` and recompile!
