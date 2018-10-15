# Key Sounds

**Key Sounds** is a simple background program for Windows that provides a typewriter sound whenever a key is pressed.
As well as being a novelty gimmick **Key Sounds** does actually have a functional use as an accessability tool for people who have limited fine motor control or very weak muscles. They get audible feedback to let them know they have pushed the keys correctly.

## Origin Story

Many years ago I used to use an instant messaging system called ICQ. The desktop program for ICQ back then included a novel feature to have a typewriter sound while you type messages. I liked that effect so in January of 2004 I decided to see if I could make it work for any program. **Key Sounds** is the result.

I named it **Key Sounds** to make it future proof. I planned to increase its functionality to allow for more sounds to be used. Alas life changes put **Key Sounds** on semi-permanent hold for many years! Today (the day this GitHub project was created) I decided I would release the code here. Maybe if there is interest I might be motivated to continue with the project.

## Usage

To use **Key Sounds** simply run the application! Your keyboard will now start producing that old classic typewriter sound whever keys are pressed! **Key Sounds** runs in the background with an icon showing in the taskbar notification area. Double clicking that icon will bring up the about box for the program and right clicking will bring up a prompt asking if you want to close the program.

## Version Changes

What follows is an almost direct copy from my old README.TXT file so it does not follow current conventions. It's easy enough to read though. The version changes do seem to take a long time but at the time I wrote it I was also a full time father to 3 very young children! It was a spare time only project.

### Beta Versions:

**Version 1.0 Beta - August 2004 (Current version)**
> This version is the first public release and has a very simple user interface.
> - Added notification area icon and its ability to respond to mouse clicks.
> - Added an about box to be displayed when the icon is double clicked.
> - Added icon right click function to ask user if they want the program closed.
> - Added code for closing program cleanly restoring existing keyboard hooks correctly. Very important to do that!

### Alpha Versions:
**Version 0.9 Alpha - June 2004**
> The first version to work without bugs. Unfortunately, the only way to close the program is using the stop command in the debugger or using Task Manager to kill the task!

**Version 0.6 Alpha - May 2004**
> First version to make the sounds system wide.
> - Made the keyboard hook routine hook in to the system's functions. Prior to this the hook was only local to the program.
> - Made the program run hidden in the background.

**Version 0.3 Alpha - February 2004**
> Let there be sound!
> - Added sound routines to the keyboard hook.

**Version 0.1 Alpha - January 2004**
> This is the bare bones start of the project.
> - Created an empty project that simply shows an empty window.
> - Added a keyboard hook that does nothing for now.

## Bugs

No known bugs!

## Future Features

These are all the features and changes I had planned for the project but never got round to.

### Issues:
1. **KeySounds** currently responds to all keys. It needs to ignore modifier keys Shift, Control and Alt.

### Planned Additions:
1. Use a different sound for RETURN/ENTER keys.
2. A pop up menu with options when you right click the notification area icon.
3. Include a selection of alternative sounds to the typewriter.
4. Include an option for a custom user supplied sound.
5. Include a enable/disable sounds option in the pop up menu so the program does not have to be closed to stop sounds.
6. Add an option to have the program run at startup.
