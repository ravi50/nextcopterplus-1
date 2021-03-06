/*********************************************************************
 * menu_ext.h
 ********************************************************************/

//***********************************************************
//* Externals
//***********************************************************

// Display-only screens
extern void Display_status(void);
extern void Display_balance(void);
extern void Display_sensors(void);
extern void Display_rcinput(void);
extern void Display_sticks(void);
extern void idle_screen(void);

// Menus
extern void menu_main(void);
extern void menu_battery(void);
extern void menu_rc_setup(uint8_t i);
extern void menu_mixer(uint8_t i);
extern void	menu_camstab(void);
extern void menu_servo_setup(uint8_t section);
extern void menu_flight(uint8_t i);
extern void Wait_BUTTON1(void);
extern void Wait_BUTTON4(void);
extern void menu_log(void);
extern void add_log(uint8_t error);

extern  uint8_t button;

// Menu frames, items
extern void print_menu_frame(uint8_t style);
//extern void print_menu_items(uint16_t top, uint16_t start, int8_t values[], const unsigned char* menu_ranges, uint8_t rangetype, uint16_t MenuOffsets, const unsigned char* text_link, uint16_t cursor);
extern void print_menu_items(uint16_t top, uint16_t start, int8_t values[], const unsigned char* menu_ranges, uint8_t rangetype, uint16_t MenuOffsets, const uint16_t* text_link, uint16_t cursor);

// Misc subroutines
extern uint8_t poll_buttons(bool acceleration);
extern void menu_beep(uint8_t beeps);
extern void print_cursor(uint8_t line);

// Menu management
extern void update_menu(uint16_t items, uint16_t start, uint16_t offset, uint8_t button, uint16_t* cursor, uint16_t* top, uint16_t* temp);
extern void do_menu_item(uint16_t menuitem, int8_t *values, uint8_t mult, menu_range_t range, int8_t offset, uint16_t text_link, bool servo_enable, int16_t servo_number);

// Special print routine - prints either numeric or text
extern void print_menu_text(int16_t values, uint8_t style, uint16_t text_link, uint8_t x, uint8_t y);
extern menu_range_t get_menu_range (const unsigned char* menu_ranges, uint8_t menuitem);

// Externs
extern const char *text_menu[]; 

// Menu defines
#define ITEMOFFSET 10	// Left edge of menu text
#define CURSOROFFSET 3	// Left edge of cursor
#define PREVLINE 2		// When cursor has been asked to move up off screen
#define LINE0 3			// Top line of menu
#define LINE1 15		// Top line of menu
#define LINE2 27		// Middle line of menu
#define LINE3 39		// Bottom line of menu
#define NEXTLINE 40		// When cursor has been asked to move down off screen
#define BACK	0x70 	// S1 pressed
#define UP		0xb0 	// S2 pressed
#define DOWN	0xd0 	// S3 pressed
#define ENTER	0xe0 	// S4 pressed
#define NONE	0xf0 	// No button pressed
#define ABORT	0xa0 	// Abort button pressed

// Global menu variables
extern uint16_t cursor;
extern uint16_t menu_temp;
extern const uint8_t lines[4];
extern uint8_t menu_flag;
extern uint16_t sub_top;


