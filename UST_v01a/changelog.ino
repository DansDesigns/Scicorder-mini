/*
 * 
 * 
 * 
 *    06/02/2024
 *              - added sleep and wake function for EXT0 on pin35
 *              - added temporary Company Logo - need to put as boot logo..
 *              - 
 * 
 *     28/11/2023
 *               - updated system fonts
 *               - updated welcome screen
 *               - merged atm_gas to one sprite
 *               
 *               
 *     20-25/11/2023
 *                - updated ota_updater
 *                - updated Setup_AP to new Setup_AP
 *                - added wifi file access - NEED TO REDO LCARS INTERFACE TO MATCH SETUP_AP
 *                - changed from SPIFFS FS to LITTLEFS
 *                - added save wifi credentials to EEPROM
 *                
 *                
 *     19/11/2023     
 *                - added wifi menu and bluetooth menu
 *                
 *                
 *     17/11/2023          
 *                - added microSD save wifi credentials - WIP 
 *                  - might move to SPIFFS 
 *                  - possible issue with same spi bus as screen - screen errors could be amp related
 *                  
 *    16/11/2023      
 *               - Added OTA updates from GitHub
 *                  - Manual Update Tested & Working
 *                  - Auto Check on Boot needs testing
 *               - added Wifi Setup_AP
 *               - Updated ButtonTone to use DAC-ESP32 instead of Tones library
 *               
 *               
 *    14/11/2023        
 *               - updated TFT_eSPI library on linux, works with OG code now..
 *               - copied code from old TFT_eSPI_NEW-GUI > new UST_V0.1a.ino
 *               - updated fonts & moved non used Adafruit_GFX stuff to foler: GFX.old
 *               - updated UI Components to TFT_eSPI Sprites
 *               - tested shapes and colours with ATM/GAS.. issue with Altitude flashing during update
 *               - removed page names
 *               
 *               
 *    13/11/2023 
 *               - updated MPR121 buttson with proper page names
 *               -
 *               
 *
 *    12/11/2023
 *               - Created UST_V0.1a from old code
 *               - created statusbar including battery, wifi, bt, sdcard status & page name 
 *               - 
 *               
 *                
 *                
 *                
 *                
 *                
 *                
 *                
 *                
 *                
 *                
 */
