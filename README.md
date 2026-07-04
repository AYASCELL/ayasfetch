# ayasfetch 🚀

A lightning-fast, ultra-modern system information fetch tool written in pure C.

`ayasfetch` takes the beloved concept of terminal fetch utilities (like neofetch or fastfetch) and gives it a highly customized, elegant visual touch featuring:
- Beautiful single-line rounded borders.
- Perfect terminal alignment supporting Emojis and Nerd Font Icons.
- Lightweight, zero-dependency C codebase for instant execution.
- Dynamic OS logo detection.

## 📸 Preview
*(When you upload to GitHub, take a screenshot of your terminal and put it here!)*

## 🧩 Dependencies
`ayasfetch` is incredibly lightweight, but relies on a few standards to look and work perfectly:
- **Nerd Fonts**: Required for the beautiful hardware icons (CPU, GPU, Network, etc.) to render correctly. Make sure your terminal font is set to a Nerd Font (e.g., FiraCode Nerd Font, MesloLGS NF).
- **iproute2**: For fetching the local IP address (`ip` command).
- **make & gcc**: For compiling the source code.

## 🛠️ Compilation

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

---
**Created by [AYASCELL]** 💻
