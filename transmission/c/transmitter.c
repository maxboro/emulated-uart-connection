#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "utils.h"

int main() {
    struct ConnectionParams params = get_devices();
    printf("main PTY_T: %s\n", params.PTY_T);
    printf("main PTY_R: %s\n", params.PTY_R);

    float rand_val = get_random_float();
    printf("main rand_val: %f\n", rand_val);


    int serial_port = open(params.PTY_T, O_WRONLY);
    if (serial_port < 0){
        perror("Error opening serial port");
        return 1;
    }

    char message[] = "String send by C transmitter.\n";
    for (int n_msg = 0; n_msg < 10; n_msg++){
        sleep(1);
        write(serial_port, message, strlen(message));
        printf("Msg %d is sent.\n", n_msg);
        fflush(stdout);
    }
    
    close(serial_port);
    return 0;
}
