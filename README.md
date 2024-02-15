## Bootloader UART Based with Interactive TFT Screen.

## System Overview
At the outset of the bootloader application's launch, it takes a brief pause to inspect for any incoming updates via UART. Shortly thereafter, the TFT screen provides a visual indication of the availability of updates. The system then smoothly transitions to a selection menu, enabling users to pick between Application 1 and Application 2 by utilizing dedicated push buttons. Within each application, users have the flexibility to revert to the bootloader through a pre-configured push button. This functionality facilitates the reception of new updates or a seamless transition to another application.

## System Behavior Sequence
1)  #### During the initial boot, the bootloader application pauses for a few seconds.
2)  #### It checks for new updates received through UART.
3)  #### The TFT screen displays whether updates are available.
4)  #### it transitions to a selection menu.
5)  #### Users can choose between Application 1 or Application 2 using two push buttons.
6)  #### Within each application, there's an option to return to the bootloader.
7)  #### This return is facilitated through a configured push button.
8)  #### It allows for the reception of new updates or the transition to another application.

## [Project Video on Linkedin ](https://www.linkedin.com/posts/mahmoud-korayem-8b1947162_bootloader-applicationupdates-userexperience-activity-7146479831998791680-Kipx?utm_source=share&utm_medium=member_desktop)
## This is the MEMORY MAP :
1)  #### Bootloader APPlication:
     ADDRESS RANGE :0x0800 0000 - 0x0800 3C00 
    flash size :15K
3)  #### Application 1:
     ADDRESS RANGE :0x0800 3C00 - 0x800 8C00
    flash size :20K
5)  #### Application 2:
    ADDRESS RANGE : 0x800 8C00 - 0x0800 F00
    flash size:25K
7)  #### the new updated Application 1:
    ADDRESS RANGE : x0800 3C00 - 0x800 8C00
    flash size:25K

## Drivers Used in This Project
1)  ### MCAL--->(GPIO, Systick , NVIC , SCB , RCC , UART , FPEC )
2)  ### HAL---->(TFT Screen , push button)

## hardware components
1)  #### stm32f103 bluepill
2)  #### TFT screen
3)  #### 3 push buttons
4)  #### RGB led 
