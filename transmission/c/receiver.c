#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "utils.h"

int main() {
    struct ConnectionParams params = get_devices();
    printf("main PTY_T: %s\n", params.PTY_T);
    printf("main PTY_R: %s\n", params.PTY_R);

    int serial_port = open(params.PTY_R, O_RDONLY);
    if (serial_port < 0) {
        perror("Error opening serial port");
        return 1;
    }

    char buffer[256];
    for (int n_msg = 0; n_msg < 10; n_msg++) {
        int bytes_read = read(serial_port, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            printf("Received: %s\n", buffer);
        }
    }

    close(serial_port);
    return 0;
}
