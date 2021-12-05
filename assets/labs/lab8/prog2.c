#include <unistd.h>

int main() {
  return unlink("/boot/kernel.img");
}
