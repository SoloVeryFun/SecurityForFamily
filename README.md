# Smart Door Lock with Telegram Bot and One-Time Codes

This project is a smart door lock system controlled via a Telegram bot. It uses Arduino, ESP8266, and Python to provide secure, remote access using one-time codes. Ideal for temporary guest access or remote control scenarios.

## Features

- Unlock door remotely via Telegram bot
- One-time access codes for added security
- Simple Telegram interface for control
- ESP8266 handles Wi-Fi communication
- Arduino controls the physical locking mechanism
- Python backend processes codes and commands

## Tech Stack

**Hardware:**
- Arduino (e.g. Uno, Nano)
- ESP8266 (e.g. NodeMCU)
- Relay module or servo motor for lock actuation

**Software:**
- Python (Telegram Bot API, backend logic)
- Arduino sketch for lock control
- ESP8266 code for network communication

## How It Works

1. User sends a command (e.g. `/unlock 123456`) to the Telegram bot.
2. Python backend verifies the one-time code.
3. If valid, it sends a command to the ESP8266 via Wi-Fi.
4. ESP8266 communicates with Arduino to unlock the door.
5. The code is marked as used and cannot be reused.

## Security

- One-time codes are stored and invalidated after use
- Bot access can be limited to specific Telegram users
- Optional encryption between components
