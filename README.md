# ayasfetch 🚀

A lightning-fast, ultra-modern system information fetch tool written in pure C.

`ayasfetch` takes the beloved concept of terminal fetch utilities (like neofetch or fastfetch) and gives it a highly customized, elegant visual touch featuring:
- Beautiful single-line rounded borders.
- Lightweight, zero-dependency C codebase for instant execution.
- Dynamic OS logo detection.

## 📸 Preview
<img width="1139" height="432" alt="Ekran Görüntüsü_20260720_133055" src="https://github.com/user-attachments/assets/8112d774-746c-4932-97b8-453b60e2531c" />

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

If you installed via the pre-compiled binary:
```bash
sudo rm /usr/local/bin/ayasfetch
```

If you installed from source:
```bash
sudo make uninstall
```

## 🎨 Custom Colors & Configuration

### Command Line Options

You can easily change the color theme on the fly using the `-c` or `--color` flag:

```bash
# Use a built-in color
ayasfetch -c gold
ayasfetch -c purple
ayasfetch -c cyan

# Use any custom 24-bit TrueColor hex code
ayasfetch -c '#fc0fc0'
ayasfetch --color '#38bdf8'

# List all available colors and format instructions
ayasfetch --list-colors
# or
ayasfetch --color list
```

### Configuration File (`~/.config/ayasfetch/config`)

To make your preferred color permanent across terminal sessions and updates:

1. Generate a configuration file:
   ```bash
   ayasfetch --gen-config
   ```
2. Edit `~/.config/ayasfetch/config` and set your desired color or hex code:
   ```ini
   color = purple
   # or
   color = #fc0fc0
   ```
*(Note: Your config file is stored in your user directory and will never be overwritten or lost during updates!)*
