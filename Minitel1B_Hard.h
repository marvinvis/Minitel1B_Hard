////////////////////////////////////////////////////////////////////////
/*
   Minitel1B_Hard - Header file - Version of March 5, 2023 at 9:27 PM
   Copyright 2016-2023 - Eric Sérandour
   https://entropie.org/3615/
   
   Thanks to:
   BorisFR, iodeo
   
   Documentation used:
   Technical Specifications for Minitel 1B Use
   http://543210.free.fr/TV/stum1b.pdf
   
////////////////////////////////////////////////////////////////////////
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
////////////////////////////////////////////////////////////////////////

#ifndef MINITEL1B_H  // If the MINITEL1B_H constant is not
#define MINITEL1B_H  // defined, we define it.

// Depending on the Arduino version
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif  // End If (ARDUINO)

////////////////////////////////////////////////////////////////////////

// The Teletel standard

// Chapter 2: The screen

// 1 Videotex Mode

// 1.2.3 Encoding of displayable characters
// G0 Set => alphanumeric (see p.100)
// G1 Set => semi-graphic (see p.101 and 102)
// G2 Set => complement to G0 (see p.103)
// Characters from the G2 set are obtained if preceded by the SS2 code (0x19).
// They can be displayed directly using printSpecialChar(byte b):
#define LIVRE              0x23 // POUND
#define DOLLAR             0x24 // DOLLAR
#define DIESE              0x26 // HASH
#define PARAGRAPHE         0x27 // PARAGRAPH
#define FLECHE_GAUCHE      0x2C // LEFT_ARROW
#define FLECHE_HAUT        0x2D // UP_ARROW
#define FLECHE_DROITE      0x2E // RIGHT_ARROW
#define FLECHE_BAS         0x2F // DOWN_ARROW
#define DEGRE              0x30 // DEGREE
#define PLUS_OU_MOINS      0x31 // PLUS_OR_MINUS
#define DIVISION           0x38 // DIVISION
#define UN_QUART           0x3C // ONE_QUARTER
#define UN_DEMI            0x3D // ONE_HALF
#define TROIS_QUART        0x3E // THREE_QUARTERS
#define OE_MAJUSCULE       0x6A // OE_UPPERCASE
#define OE_MINUSCULE       0x7A // OE_LOWERCASE
#define BETA               0x7B // BETA
// Diacritics cannot be displayed alone.
// printSpecialChar(byte b) will therefore have no effect here.
#define ACCENT_GRAVE       0x41 // GRAVE_ACCENT
#define ACCENT_AIGU        0x42 // ACUTE_ACCENT
#define ACCENT_CIRCONFLEXE 0x43 // CIRCUMFLEX_ACCENT
#define TREMA              0x48 // DIAERESIS
#define CEDILLE            0x4B // CEDILLA


// 1.2.4 Encoding of display attributes (see p.91)
// These functions are obtained if preceded by the ESC code (0x1B).
// We then have access to the C1 grid. It can be accessed directly
// by using attributs(byte attribut).
// Character color
#define CARACTERE_NOIR    0x40 // BLACK_CHARACTER
#define CARACTERE_ROUGE   0x41 // RED_CHARACTER
#define CARACTERE_VERT    0x42 // GREEN_CHARACTER
#define CARACTERE_JAUNE   0x43 // YELLOW_CHARACTER
#define CARACTERE_BLEU    0x44 // BLUE_CHARACTER
#define CARACTERE_MAGENTA 0x45 // MAGENTA_CHARACTER
#define CARACTERE_CYAN    0x46 // CYAN_CHARACTER
#define CARACTERE_BLANC   0x47 // WHITE_CHARACTER
// Background color              // In text mode, the space (0x20) is the trigger for background color change (see p.93). This change is valid until the end of a row.
#define FOND_NOIR         0x50  // To avoid having this space on the screen, another solution (in this case the character will be black) is to implement inverse background.
#define FOND_ROUGE        0x51  // For example:
#define FOND_VERT         0x52  // minitel.attributs(GREEN_CHARACTER);
#define FOND_JAUNE        0x53  // minitel.attributs(INVERT_BACKGROUND);
#define FOND_BLEU         0x54  // minitel.print("I WRITE MY TEXT HERE");
#define FOND_MAGENTA      0x55  // minitel.attributs(NORMAL_BACKGROUND);
#define FOND_CYAN         0x56
#define FOND_BLANC        0x57
// Size
#define GRANDEUR_NORMALE  0x4C  // Normal size - Not usable in graphic mode
#define DOUBLE_HAUTEUR    0x4D  // Double height - Not usable in graphic mode
#define DOUBLE_LARGEUR    0x4E  // Double width - Not usable in graphic mode
#define DOUBLE_GRANDEUR   0x4F  // Double size - Not usable in graphic mode
// Blinking or steady
#define CLIGNOTEMENT      0x48 // BLINKING
#define FIXE              0x49 // STEADY
// Start and end of masking
#define MASQUAGE          0x58 // MASKING
#define DEMASQUAGE        0x5F // UNMASKING
// Start or end of underlining
#define FIN_LIGNAGE       0x59 // END_UNDERLINING
#define DEBUT_LIGNAGE     0x5A  // START_UNDERLINING - In text mode, the space (0x20) marks the beginning of an underlining area. It is the trigger element (see p.93).
// Inverted or normal background
#define FOND_NORMAL       0x5C  // NORMAL_BACKGROUND - Not usable in graphic mode
#define INVERSION_FOND    0x5D  // INVERT_BACKGROUND - Not usable in graphic mode
// Escape to ISO 6429 standard
#define CSI               0x1B5B


// 1.2.5 Page layout functions (see p.94)
#define BS   0x08  // BackSpace: Move cursor one character position to the left.
#define HT   0x09  // Horizontal Tab: Move cursor one character position to the right.
#define LF   0x0A  // Line Feed: Move cursor one character position down.
#define VT   0x0B  // Vertical Tab: Move cursor one character position up.
#define CR   0x0D  // Carriage Return: Return cursor to the beginning of the current row.
// CSI type functions are developed within the Minitel class (further down).
#define RS   0x1E  // Record Separator: Return cursor to the first position of row 01. This code is an explicit record separator.
#define FF   0x0C  // Form Feed: Return cursor to the first position of row 01 with complete screen clear.
#define US   0x1F  // Unit Separator: Sub-record separator.
#define CAN  0x18  // Cancel: Fill from the current cursor position to the end of the row with spaces from the current set having the current attribute state. The current cursor position is not moved.


// 1.2.6 Other functions (see p.98)
// 1.2.6.1 Various functions:
#define REP  0x12  // Repetition: Allows repeating the last displayed character with the current attributes of the active writing position.
#define NUL  0x00  // Null:
#define SP   0x20  // Space:
#define DEL  0x7F  // Delete:
#define BEL  0x07  // Bell: Triggers an audible signal
// 1.2.6.2 Cursor position request
//...
// 1.2.6.3 Code extension functions
#define SO   0x0E  // Shift Out: Access to G1 set. => Semi-graphic mode
#define SI   0x0F  // Shift In: Access to G0 set.  => Alphanumeric mode
#define SS2  0x19  // Single Shift 2: Call a single character from the G2 set.
#define ESC  0x1B  // Escape: Escape and access to C1 grid.
// 1.2.6.4 Cursor display
#define CON  0x11  // Display of the active cursor position (active cursor).
#define COFF 0x14  // Stop display of the active position (inactive cursor).


// 1.2.7 Specific filtering (see p.99)
//...


// 1.2.8 Error handling and resynchronization behavior (see p.99)
// ...




// Chapter 3: The keyboard

// 6 Sequences emitted by function keys in Videotex or Mixed mode (see p.123)
#define ENVOI          0x1341 // SEND
#define RETOUR         0x1342 // RETURN
#define REPETITION     0x1343 // REPEAT
#define GUIDE          0x1344 // GUIDE
#define ANNULATION     0x1345 // CANCEL
#define SOMMAIRE       0x1346 // SUMMARY
#define CORRECTION     0x1347 // CORRECTION
#define SUITE          0x1348 // NEXT
#define CONNEXION_FIN  0x1359  // CONNECTION_END - Not documented

// 7 Codes and sequences emitted by cursor management and editing keys in Videotex or Mixed mode (see p.124)
#define TOUCHE_FLECHE_HAUT         0x1B5B41 // UP_ARROW_KEY
#define SUPPRESSION_LIGNE          0x1B5B4D // LINE_DELETION
#define TOUCHE_FLECHE_BAS          0x1B5B42 // DOWN_ARROW_KEY
#define INSERTION_LIGNE            0x1B5B4C // LINE_INSERTION
#define TOUCHE_FLECHE_DROITE       0x1B5B43 // RIGHT_ARROW_KEY
#define DEBUT_INSERTION_CARACTERE  0x1B5B3468 // START_CHARACTER_INSERTION
#define FIN_INSERTION_CARACTERE    0x1B5B346C // END_CHARACTER_INSERTION
#define TOUCHE_FLECHE_GAUCHE       0x1B5B44 // LEFT_ARROW_KEY
#define SUPRESSION_CARACTERE       0x1B5B50 // CHARACTER_DELETION
// #define DEL                        0x7F  // Already defined above (1.2.6.1)
// #define CR                         0x0D  // Already defined above (1.2.5)
#define HOME                       0x1B5B4B // HOME
#define EFFACEMENT_PAGE            0x1B5B324A // PAGE_CLEAR




// Chapter 6: The Protocol (see p.134)

// 1 General (see p.134)
#define CODE_EMISSION_ECRAN        0x50 // SCREEN_EMISSION_CODE
#define CODE_EMISSION_CLAVIER      0x51 // KEYBOARD_EMISSION_CODE
#define CODE_EMISSION_MODEM        0x52 // MODEM_EMISSION_CODE
#define CODE_EMISSION_PRISE        0x53 // SOCKET_EMISSION_CODE
#define CODE_RECEPTION_ECRAN       0x58 // SCREEN_RECEPTION_CODE
#define CODE_RECEPTION_CLAVIER     0x59 // KEYBOARD_RECEPTION_CODE
#define CODE_RECEPTION_MODEM       0x5A // MODEM_RECEPTION_CODE
#define CODE_RECEPTION_PRISE       0x5B // SOCKET_RECEPTION_CODE

// 3 Switching and module blocking commands (see p.134)
// 3.2 Command format (see p.135)
#define AIGUILLAGE_OFF             0x60 // SWITCHING_OFF
#define AIGUILLAGE_ON              0x61 // SWITCHING_ON
// 3.4 Module switching status request (see p.136)
#define TO                         0x62 // TO
#define FROM                       0x63 // FROM

// 6 Identification and cursor position requests (see p.139)
// 6.1 Minitel identification request (see p.139)
#define ENQROM                     0x7B // ENQROM

// 7 Modem related commands (see p.139)
#define CONNEXION                  0x68 // CONNECTION
#define DECONNEXION                0x67 // DISCONNECTION

// 8 Socket related commands (see p.141)
#define PROG                       0x6B // PROG
#define STATUS_VITESSE             0x74 // SPEED_STATUS

// 9 Keyboard related commands (see p.141)
#define ETEN                       0x41  // Extended keyboard mode

// 10 Screen related commands (see p.142)
#define ROULEAU                    0x43  // Scroll mode screen

// 11 Commands related to multiple modules (see p.143)
#define START                      0x69 // START
#define STOP                       0x6A // STOP
#define MINUSCULES                 0x45  // Lowercase / uppercase keyboard mode

// 12 Protocol Commands related to standard change (see p.144)
#define MIXTE1                     0x327D // MIXED1
#define MIXTE2                     0x327E // MIXED2
#define TELINFO                    0x317D // TELINFO

// 13 Initial state of the minitel
// 13.2 Upon receipt of a reset command
#define RESET                      0x7F // RESET




// Personal constants for hline and vline
#define CENTER  0
#define TOP     1
#define BOTTOM  2
#define LEFT    3
#define RIGHT   4
#define UP      5
#define DOWN    6




////////////////////////////////////////////////////////////////////////

class Minitel
{
public:
  Minitel(HardwareSerial& serial);
  
  #if defined(ESP32) || defined(ARDUINO_ARCH_ESP32)
  Minitel(HardwareSerial& serial, int8_t rxPin, int8_t txPin);
  #endif
  
  // Write one byte, one word or a code of maximum 4 bytes / Read one byte
  void writeByte(byte b);
  void writeWord(word w);
  void writeCode(unsigned long code);  // 4 bytes maximum
  byte readByte();
  
  // Identification of Minitel type
  unsigned long identifyDevice();
  
  // Serial link speed
  // When the Minitel is powered on, the exchange speed between
  // the Minitel and the peripheral is 1200 bauds by default.
  // The Minitel user can program the exchange speed with the
  // peripheral via the keyboard, regardless of the terminal's state,
  // using the following commands:
  // Fnct P + 3: 300 bauds
  // Fnct P + 1: 1200 bauds
  // Fnct P + 4: 4800 bauds
  // Fnct P + 9: 9600 bauds (for Minitel 2 only)
  // Warning! If the Minitel and the peripheral do not communicate
  // at the same speed, the connection is lost.
  int changeSpeed(int bauds);  // At any time, a peripheral can modify the exchange speeds of the socket (possible speeds: 300, 1200, 4800 bauds; also 9600 bauds for Minitel 2).
  int currentSpeed();  // To know the current exchange speed, the Minitel and the peripheral exchanging at the same speed.
  int searchSpeed();  // To know the Minitel's speed, the Minitel and the peripheral not necessarily exchanging at the same speed.
  
  // Separators
  void newScreen();  // Warning! newScreen resets the display attributes.
  void newXY(int x, int y);  // Warning! newXY resets the display attributes.
  
  // Cursor
  void cursor();  // Visible cursor
  void noCursor();  // Invisible cursor
  void moveCursorXY(int x, int y);  // Direct cursor addressing in column x and row y.
  void moveCursorLeft(int n);  // Cursor left by n columns. Stops at the left edge of the screen.
  void moveCursorRight(int n);  // Cursor right by n columns. Stops at the right edge of the screen.
  void moveCursorDown(int n);  // Cursor down by n rows. Stops at the bottom of the screen.
  void moveCursorUp(int n);  // Cursor up by n rows. Stops at the top of the screen.
  void moveCursorReturn(int n);  // Return cursor to the beginning of the current row then cursor down by n rows. Stops at the bottom of the screen.
  int getCursorX();  // Column where the cursor is located
  int getCursorY();  // Row where the cursor is located
  
  // Erasing, Deleting, Inserting
  void cancel();  // Fill from the current cursor position to the end of the row with spaces from the current set having the current attribute state. The current cursor position is not moved.
  void clearScreenFromCursor();  // Clear from the cursor inclusive to the end of the screen.
  void clearScreenToCursor();  // Clear from the beginning of the screen to the cursor inclusive.
  void clearScreen();  // Clear the entire screen (cursor position is not modified).
  void clearLineFromCursor();  // Clear from the cursor inclusive to the end of the row.
  void clearLineToCursor();  // Clear from the beginning of the row to the cursor inclusive.
  void clearLine();  // Full clear of the row where the cursor is.
  void deleteChars(int n);  // Delete n characters starting at the cursor position inclusive.
  void insertChars(int n);  // Insert n characters starting at the cursor position inclusive (RTIC model only, not MATRA or TELIC).
  void startInsert();  // Start character insertion mode.
  void stopInsert();  // End character insertion mode.
  void deleteLines(int n);  // Delete n rows starting from the one where the cursor is.
  void insertLines(int n);  // Insert n rows starting from the one where the cursor is.
  
  // Teletel standard modes
  void textMode();      // Access to G0 set - Videotex 40-column mode (default when Minitel is powered on)
  void graphicMode();   // Access to G1 set - Videotex 40-column mode
  byte pageMode();      // Page mode
  byte scrollMode();    // Scroll mode
  byte modeMixte();     // Videotex mode => Mixed 80-column mode (No semi-graphic characters (G1 set) are displayable)
  byte modeVideotex();  // Mixed mode => Videotex 40-column mode

  // Standards
  byte standardTeleinformatique();  // Teletel standard => Teleinformatic standard 80 columns (Less extended programming possibilities)
  byte standardTeletel();           // Teleinformatic standard => Teletel standard (includes Videotex and Mixed modes)

  // Content
  void attributs(byte attribut); // attributes
  void print(String chaine);  // UTF-8 => Minitel codes
  void println(String chaine);
  void println();
  void printChar(char caractere);  // G0 set character except those coded 0x60, 0x7E, 0x7F.
  // void printDiacriticChar(unsigned char caractere);  // Character with accent, diaeresis or cedilla.  // Obsolete since 26/02/2023
  void printSpecialChar(byte b);  // G2 set character. See above, at 1.2.3, the possible constants.
  byte getCharByte(char caractere);
  String getString(unsigned long code);  // Unicode => UTF-8
  int getNbBytes(unsigned long code);  // To be used in conjunction with getString(unsigned long code) just above.
  void graphic(byte b, int x, int y);  // G1 set. See page 101. In the form 0b000000 to 0b111111 from the top-left corner to the bottom-right corner. In column x and row y.
  void graphic(byte b);  // See the line above.
  void repeat(int n);  // Allows repeating the last displayed character with the current attributes of the active writing position.
  void bip();  // Audible beep
  
  // Geometry
  void rect(int x1, int y1, int x2, int y2);  // Rectangle defined by 2 points.
  void hLine(int x1, int y, int x2, int position);  // Horizontal line. position = TOP, CENTER or BOTTOM.
  void vLine(int x, int y1, int y2, int position, int sens);  // Vertical line. position = LEFT, CENTER or RIGHT. sens = DOWN or UP.
  
  // Keyboard
  unsigned long getKeyCode(bool unicode = true);  // Minitel codes => Unicode by default (if false: no conversion)
  byte smallMode();  // Lowercase keyboard mode
  byte capitalMode();  // Uppercase keyboard mode
  byte extendedKeyboard();  // Extended keyboard
  byte standardKeyboard();  // Standard keyboard
  byte echo(boolean commande);  // Activates or deactivates the on-screen echo of what is typed on the keyboard
  
  // Protocol
  byte aiguillage(boolean commande, byte emetteur, byte recepteur); // switching
  byte statusAiguillage(byte module); // switching status
  byte connexion(boolean commande); // connection
  byte reset(); // reset
  
private: 
  HardwareSerial& mySerial; 
  
  byte currentSize = GRANDEUR_NORMALE; // NORMAL_SIZE
  boolean isValidChar(byte index);
  // boolean isDiacritic(unsigned char caractere);  // Obsolete since 26/02/2023
  boolean isVisualisable(unsigned long code); // is displayable
  void writeBytesP(int n);  // Pn, Pr, Pc
  
  // Protocol
  void writeBytesPRO(int n);  // PRO1, PRO2 or PRO3
  unsigned long identificationBytes();
  int workingSpeed();
  byte workingStandard(unsigned long sequence);
  byte workingMode();
  byte workingKeyboard();
  byte workingAiguillage(byte module);
  byte workingModem();
  
  unsigned long getCursorXY();
};

////////////////////////////////////////////////////////////////////////

#endif // End If (MINITEL1B_H)
