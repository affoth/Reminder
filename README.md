# Reminder
Popup reminder to check whether you're still working — or procrastinating. Popup is set to 30 min(can be changed)  Useful as a personal productivity tool, accountability prompt, or gentle motivator.

Features
-----------
- Popup message every **30 minutes** (configurable).
- Custom motivational text over multiple lines.
- Press **`y`** to dismiss the popup.
- Press **`ESC`** to exit the program completely.
- Ideal for background use during long work sessions.

Customize
---------------
- By changing #define you can customize
    - Popuptime
    - Popup size
    - Popup message
- go to src/reminder.c to make the changes

Requirements
---------------
- **Linux** system

Compilation
--------------
This program relies on the MiniLibX library, a library I do not have controll over: https://github.com/42Paris/minilibx-linux.git
It is cloned during the make process. The copyright belongs to Ecole 42.
(Copyright (c) 2021, Ecole 42)

make
to run program: ./Reminder

Autostart (Optional)
-----------------------
To make the program launch on login (no root required):

WARNING!
before you do, run the program as is, uncoment the debug statement in src/reminder.c -> main (all the way at the end of the file)
and run the program in the terminal. The program is an infinite loop, before you add it to autostart you should double check that
it closes correctly.

1. Place the compiled binary in a known location, e.g. `~/bin/Reminder`
2. Make sure Reminder (the compiled binary) is executable (ls -l), if not use chmod +x
3. Create a file named reminder.desktop in the folder ~/.config/autostart/
4. Enter the following lines in it:

```
[Desktop Entry]
Type=Application
Exec=/home/yourusername/bin/Reminder
Hidden=false
NoDisplay=false
X-GNOME-Autostart-enabled=true
Name=Reminder
Comment=Popup to keep me focused
```

Bugs
----------
If you find a bug or suggest an improvement you can contact me by email:
afoth@student.42berlin.de

License
----------
MIT — free to use, modify, and share.
