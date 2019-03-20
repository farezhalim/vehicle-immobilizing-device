#!/usr/bin/expect -f

set prompt "#"

spawn sudo bluetoothctl -a
expect -re $prompt

send "power on\r"
sleep 1

send "discoverable on\r"
sleep 1

send "agent -NoInputNoOutput"

sleep 5

expect eof
