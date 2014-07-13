/*******************************************************************************
 * File:  main.c
 * Author: Will Flores waflores@ncsu.edu
 * Usage: Implements Project 3. For Device M30620FCP
 * Description: This file contains the main function which allows the user
 *              to press buttons on the QSK board and have the LCD display
 *              words as per button presses.
 * Environment: Windows 7, x64 build
 *              Built in HEW with MC16 Series Compiler V.5.44 Release 00
 * Notes:       The Timers are cut in half as far as duration is concerned
 * Revisions:   0.0, Initial Release
 *              1.0, Better documented main function
 *              2.0, Project 2a + Homework 5 improvements
 *              2.5, Project 2b
 *              2.9, Homework 8 Functionality
 *              3.0, Project 3 works :)
 *              3.1, Homework 9 Functionanity
 * 
 * Created on March 26, 2012
 ******************************************************************************/

#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"
#include "serial.h"
#include "ports.h"
#include "helperfuncs.h"
#include "shapes.h"
#include "movement.h"
#include "IR.h"
#include "gps.h"
#include "menus.h"

/*******************************************************************************
 * Purpose: This function allows the user to press a button which gives us menus.
 * Arguments: No arguments passed.
 * Returned: No values returned.
 * Author: Will Flores waflores@ncsu.edu
 *******************************************************************************/
void main(void) {
    /* Watchdog timer would go here */
    int buttonCount = CLEAR_INDEX;
    /* Initialize the ports */
    init_ports();
	
    /* Initialize the System clock */
    system_clock_init();
    
    /* Initialize the display */
    InitDisplay("HW9");
	clearScreen();
    
    /* Initialize the interrupts */
    BNSPrintf(LCD, "\tStart\nInterrupts");
	DisplayDelay(DISPLAY_DELAY1);
	init_interrupts();
    clearScreen();
	
    /* Initialize the System timers */
    BNSPrintf(LCD, "\tStart\nTimers");
	DisplayDelay(DISPLAY_DELAY1);
    TimerInit();
	clearScreen();
    
    /* Initialize Serial ports */
    BNSPrintf(LCD, "\tStart\nSerial");
	DisplayDelay(DISPLAY_DELAY1);
    InitUART();
	clearScreen();
    
    /* Initialize AD converter */
    BNSPrintf(LCD, "\tStart\nADCs");
	DisplayDelay(DISPLAY_DELAY1);
    ADInit();
    clearScreen();
    
    while(FOREVER) {
        if (buttonPressed) {
            /* indicate that we've been pressing menu buttons */
            if (buttonCount != CLEAR_INDEX) ++buttonCount;
            switch (buttonPressed) {
                case SW1_PRESSED:
                    /* Clear the bit */
                    buttonPressed &= ~(SW1_PRESSED);
                    /* Clear the screen */
                    clearScreen();
                    resistorMenu();
                    break;
                case SW2_PRESSED:
                    /* Clear the bit */
                    buttonPressed &= ~(SW2_PRESSED);
                    clearScreen();
                    shapeMenu();
                    break;
                case SW3_PRESSED:
                    /* Clear the bit */
                    buttonPressed &= ~(SW3_PRESSED);
                    clearScreen();
                    fightSongMenu();
                    break;
                default: // any 2+ Btn combo to terminate 
                    buttonCount = CLEAR_INDEX;
                    buttonPressed = CLEAR_INDEX;
                    break;
            } /* End Switch */
        }
        else {
            if (buttonCount == CLEAR_INDEX) {
                clearScreen();
                BNSPrintf(LCD, "\twaflores\n     HW9");
                DisplayDelay(DISPLAY_DELAY);
            }
        }
    }
}
