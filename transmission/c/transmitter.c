#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "utils.h"

int main() {
    struct ConnectionParams params = get_devices();
    printf("main PTY_T: %s\n", params.PTY_T);
    printf("main PTY_R: %s\n", params.PTY_R);

    int serial_port = open(params.PTY_T, O_WRONLY);
    if (serial_port < 0){
        perror("Error opening serial port");
        return 1;
    }

    for (int n_msg = 0; n_msg < 10; n_msg++) {
        char message[40];
        sprintf(message, "String send by C transmitter #%d.", n_msg);
        write(serial_port, message, strlen(message));
        printf("Msg %d is sent.\n", n_msg);
        fflush(stdout);
        sleep(1);
    }
    
    close(serial_port);
    return 0;
}
