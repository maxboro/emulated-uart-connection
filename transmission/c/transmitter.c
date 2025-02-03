#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "utils.h"

// Send end of transmission signal
void end_of_transmission(int serial_port) {
    char end_of_transmission_char = 3;
    char end_of_transmission_message[] = {end_of_transmission_char , '\0'};

    write(serial_port, end_of_transmission_message, strlen(end_of_transmission_message));
    printf("End of transmission signal is sent.\n");
    fflush(stdout);
}

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

    end_of_transmission(serial_port);
    close(serial_port);
    return 0;
}
