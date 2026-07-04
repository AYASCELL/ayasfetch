# Maintainer: Ayascell <your-email@example.com>

pkgname=ayasfetch-git
pkgver=r1.0.0
pkgrel=1
pkgdesc="A lightning-fast, ultra-modern system information fetch tool written in pure C."
arch=('x86_64')
url="https://github.com/ayascell/ayasfetch"
license=('GPL')
depends=('glibc')
makedepends=('git' 'make' 'gcc')
source=("git+https://github.com/ayascell/ayasfetch.git")
md5sums=('SKIP')

pkgver() {
  cd "$srcdir/ayasfetch"
  # Generate git version (e.g., r12.a1b2c3d)
  printf "r%s.%s" "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
}

build() {
  cd "$srcdir/ayasfetch"
  make
}

package() {
  cd "$srcdir/ayasfetch"
  make DESTDIR="$pkgdir/" PREFIX=/usr install
}
