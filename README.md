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
