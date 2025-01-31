#!/bin/bash

# Cleanup function
cleanup() {
    echo -e "\nCleaning up..."
    kill "$SOCAT_PID" 2>/dev/null
    rm -f socat_output.txt connection_params.txt
    echo "Cleanup complete!"
}

# Run cleanup when the script exits (Ctrl+C or termination)
trap cleanup EXIT

# Start socat in the background
socat -d -d pty,raw,echo=0 pty,raw,echo=0 2>&1 | tee socat_output.txt &
SOCAT_PID=$!

# Wait until both PTYs appear in the log
PTY_T=""
PTY_R=""
while [[ -z "$PTY_T" || -z "$PTY_R" ]]; do
    sleep 0.5  # Small delay to allow socat to print output
    readarray -t PTYS < <(awk '/PTY is/ {print $NF}' socat_output.txt)
    PTY_T=${PTYS[0]:-}
    PTY_R=${PTYS[1]:-}
done

# Print and save results
echo "UART Emulator Started!"
echo "Transmitter PTY: $PTY_T"
echo "Receiver PTY: $PTY_R"

echo "PTY_T=$PTY_T" > connection_params.txt
echo "PTY_R=$PTY_R" >> connection_params.txt

# Wait indefinitely until user presses Ctrl+C
echo "Press Ctrl+C to stop the UART emulation..."
while true; do sleep 1; done  # Keeps script running
