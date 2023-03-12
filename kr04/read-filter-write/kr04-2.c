#include <stdio.h>
#include <unistd.h>

int separate(int fd_in, int fd_out_even, int fd_out_odd) {
    int x, num;
    while (1) {
        x = read(fd_in, &num, sizeof(num));
        if (x <= 0) {
            break;
        }
        if (x != sizeof(num)) {
            return -1;
        }
        if (num % 2 == 0) {
            if (write(fd_out_even, &num, sizeof(num)) != sizeof(num)) {
                return -1;
            }
        } else {
            if (write(fd_out_odd, &num, sizeof(num)) != sizeof(num)) {
                return -1;
            }
        }
    }
    if (x < 0) {
        return -1;
    }
    return 0;
}