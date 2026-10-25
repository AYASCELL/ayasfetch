# ayasfetch 🚀

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A lightning-fast, ultra-modern system information fetch tool written in pure C.

`ayasfetch` takes the beloved concept of terminal fetch utilities (like neofetch or fastfetch) and gives it a highly customized, elegant visual touch featuring:
- Beautiful double-line Unicode borders with full box-drawing aesthetics.
- Lightweight, zero-dependency C codebase for instant execution.
- Dynamic OS logo detection (including Arch/CachyOS derivatives).
- 24-bit TrueColor customization with persistent configuration.

## 📸 Preview
<img width="1139" height="432" alt="Ekran Görüntüsü_20260720_133055" src="https://github.com/user-attachments/assets/8112d774-746c-4932-97b8-453b60e2531c" />

## 🧩 Dependencies
`ayasfetch` is incredibly lightweight, but relies on a few standards to look and work perfectly:
- **iproute2**: For fetching the local IP address (`ip` command).
- **make & gcc**: For compiling the source code.

## 🚀 Installation & Update

### Method 1: Automatic One-Liner (Recommended ⚡)

The fastest and easiest way to install or update `ayasfetch` directly from the latest source code:

```bash
curl -sSL https://raw.githubusercontent.com/AYASCELL/ayasfetch/main/install.sh | bash
```

> **Tip:** Whenever you want to **update** to the newest version in the future, simply re-run this exact same command! It will automatically fetch the latest code, compile it for your system, and update `ayasfetch`.

---

### Method 2: Manual Compile from Source (🛠️)

If you prefer to clone and build manually:

```bash
# 1. Clone the repository
git clone https://github.com/AYASCELL/ayasfetch.git
cd ayasfetch

# 2. Compile and install
make
sudo make install
```

To update in the future:
```bash
cd ayasfetch
git pull
make
sudo make install
```

*(Note for Packagers: The Makefile fully supports `PREFIX` and `DESTDIR` variables, making it natively compatible with AUR PKGBUILDs and other package managers!)*

---

### Method 3: Standalone Pre-compiled Binary (📦)

If you don't want to compile from source, you can download the standalone binary from the Releases page:

```bash
# 1. Download the latest binary from GitHub Releases
wget https://github.com/AYASCELL/ayasfetch/releases/latest/download/ayasfetch-x86_64-linux

# 2. Move it to your local bin directory
sudo mv ayasfetch-x86_64-linux /usr/local/bin/ayasfetch

# 3. Give it execution permissions
sudo chmod +x /usr/local/bin/ayasfetch
```

## 📖 Post-Installation & Usage Guide

Once installed, simply run:
```bash
ayasfetch
```

### 💡 Run Automatically on Terminal Launch
Want `ayasfetch` to automatically greet you every time you open a new terminal window? Add it to your shell configuration file:

- **Bash** (`~/.bashrc`):
  ```bash
  echo "ayasfetch" >> ~/.bashrc
  ```
- **Zsh** (`~/.zshrc`):
  ```bash
  echo "ayasfetch" >> ~/.zshrc
  ```
- **Fish** (`~/.config/fish/config.fish`):
  ```bash
  echo "ayasfetch" >> ~/.config/fish/config.fish
  ```

---

## 🎨 Complete Theme & Color Customization Guide

You can customize the accent and box border color **directly from your terminal** without touching any configuration files.

### 1. Test Colors on the Fly (`-c, --color`)
Preview how different themes look in your terminal before saving:
```bash
# Try built-in color themes
ayasfetch -c gold          # AYAS OS gold
ayasfetch -c purple        # Elegant purple
ayasfetch -c cyan          # Arch / Cachy cyan
ayasfetch -c red           # Debian / Ubuntu red
ayasfetch -c green         # Emerald green

# Try any custom 24-bit TrueColor HEX code (#RRGGBB or #RRGGBBAA)
ayasfetch -c '#fc0fc0'
ayasfetch -c '#38bdf8'
```

### 2. Make Your Favorite Color Permanent (`-s, --set-color`)
Found a theme or HEX color you love? Save it permanently with one command:
```bash
# Save a built-in color permanently
ayasfetch -s purple
ayasfetch --set-color gold

# Save any custom hex code permanently
ayasfetch -s '#fc0fc0'
```
> **How it works:** This command automatically saves your choice to `~/.config/ayasfetch/config`. Every subsequent `ayasfetch` execution will use this theme. Your preferences are stored in your home directory and will **never be lost or overwritten during updates!**

### 3. Revert to Default Distro Theme
Want to return to the original system distribution theme (e.g., Cyan for CachyOS/Arch, Gold for AYAS)?
```bash
# Set back to default automatic mode
ayasfetch -s auto

# Or delete the config file entirely and reset to defaults
ayasfetch --reset-config
```

### 4. Interactive Help & Color Palette
```bash
# List all built-in color names and formatting rules
ayasfetch --list-colors

# View all available CLI options and examples
ayasfetch --help
```

### 5. Manual Configuration File (`~/.config/ayasfetch/config`)
If you prefer to edit files manually:
```bash
# Generate default config if it doesn't exist
ayasfetch --gen-config

# Open in your favorite text editor
nano ~/.config/ayasfetch/config
```

Example file content:
```ini
# ayasfetch Configuration File
# Options: auto, cyan, gold, yellow, red, green, blue, purple, magenta, pink, orange, white, gray
# Or any TrueColor hex code: #fc0fc0, #1793d1, #daa520
color = purple
```

---

## ⚡ CLI Cheatsheet & Command Reference

| Command | Shortcut | Description |
|---|---|---|
| `ayasfetch` | | Displays system specs with current active theme |
| `ayasfetch -c <color>` | `--color` | Temporarily tests a color theme or HEX code |
| `ayasfetch -s <color>` | `--set-color` | **Permanently** saves color to `~/.config/ayasfetch/config` |
| `ayasfetch -s auto` | `--set-color auto` | Reverts permanent color back to default distro theme |
| `ayasfetch --reset-config` | `--reset` | Deletes the config file and resets everything to defaults |
| `ayasfetch --list-colors` | `--colors` | Prints list of available color names & palette preview |
| `ayasfetch --gen-config` | | Generates `~/.config/ayasfetch/config` file |
| `ayasfetch -h` | `--help` | Shows detailed help screen and usage examples |
| `ayasfetch -v` | `--version` | Shows version information |

---

## 🗑️ Uninstallation

If you installed via the pre-compiled binary:
```bash
sudo rm /usr/local/bin/ayasfetch
```

If you installed from source:
```bash
sudo make uninstall
```

---

## 📜 License

This project is open-source and licensed under the [MIT License](LICENSE).  
Copyright (c) 2026 AYASCELL



