References: Hoodloader (https://github.com/NicoHood/HoodLoader2)
    - This was done 1 time to reprogram the 16u2 controller on the Uno. 
    - Some of the instructions are not very clear, but one I found that isn't necessary is about switching modes between USB/Bootloader for programing. Follow the instructions below for uploading code instead.


USBController (16u2):
   GamePad implementation, adapted from: https://github.com/NicoHood/HID. To update:
   1. Select the "Hoodloader2 16u2" board. This is important as now there are two boards you can program.
   2. Upload the code. This may fail if you are in the "wrong" mode because the COM port will change. However, as long as you have the right board selected, simply change to the new port and repeat upload.

ButtonIO:
   Handles buttons, passes to USBController via serial.. To update:
   1. Select the "Hoodloader2 Uno" board, again, important you do this. If you have the 16u2 board selected you will upload your code to the wrong controller.
   2. Upload the code. This may fail if you are in the "wrong" mode because the COM port will change. However, as long as you have the right board selected, simply change to the new port and repeat upload.
   3. At this point, your board will be in "Arduino IO" mode and your hid controller will not be recognized. To fix it, you could connect the two "reset" posts, but I found it easier just to re-download the USBController code.