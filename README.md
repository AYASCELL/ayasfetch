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

You can customize the accent and box border color either temporarily or permanently directly from your terminal, without needing to manually edit files!

### 1. Test Colors on the Fly (`-c, --color`)

Preview any color in your terminal without saving it:

```bash
# Try a built-in color
ayasfetch -c gold
ayasfetch -c purple
ayasfetch -c cyan

# Try any 24-bit TrueColor hex code (#RRGGBB or #RRGGBBAA)
ayasfetch -c '#fc0fc0'
ayasfetch -c '#38bdf8'

# List all built-in color names and formats
ayasfetch --list-colors
```

### 2. Make Your Favorite Color Permanent (`-s, --set-color`)

Found a color you love? Save it permanently with a single command from your terminal:

```bash
# Save a built-in color permanently
ayasfetch -s purple
ayasfetch --set-color gold

# Save a custom hex code permanently
ayasfetch -s '#fc0fc0'
```
This automatically writes your choice to `~/.config/ayasfetch/config`. Every subsequent `ayasfetch` run will now use your chosen theme.

### 3. Reverting to Default Distro Colors

Want to go back to the original distribution theme (e.g. Cyan for CachyOS/Arch, Gold for AYAS)?

```bash
# Set back to auto/default
ayasfetch -s auto

# Or reset and delete the configuration file
ayasfetch --reset-config
```

### 4. Manual Configuration File (`~/.config/ayasfetch/config`)

You can also create or edit the config file manually if you prefer:
```bash
ayasfetch --gen-config
nano ~/.config/ayasfetch/config
```

Example `~/.config/ayasfetch/config`:
```ini
color = purple
# or
color = #fc0fc0
# or default distro mode:
color = auto
```

> **Note:** The configuration file is stored safely in your user home directory (`~/.config/ayasfetch/config`), so updates or reinstallations will **never** overwrite or erase your custom settings!

