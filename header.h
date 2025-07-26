typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned short int u16;
typedef signed short int s16;


// DELAY
extern void delay_sec(unsigned int sec);
extern void delay_ms(unsigned int ms);

// LCD
extern void lcd_data(unsigned char data);
extern void lcd_cmd(unsigned char cmd);
extern void lcd_init(void);
extern void lcd_string(char *ptr);
extern void lcd_integer(int num);
extern void lcd_float(float f);
extern void lcd_cgram(void);
extern void lcd_ascii(int num);

// UART0
extern void uart0_init(unsigned int baud);
extern void uart0_tx(unsigned char data);
extern unsigned char uart0_rx(void);
extern void uart0_tx_string(s8 *ptr);
extern void uart0_rx_string(char *ptr,u8 len);
extern void uart0_hex(u8 temp);
extern int uart0_rx_int(void);
extern u8  my_strcmp(s8 *p,s8 *q);
extern void uart0_tx_integer(int num);
extern void uart0_tx_float(float num);
extern void uart0_tx_int(int);

// ADC
extern u32 adc_read(u8 ch_num);
extern void adc_init(void);

// EXTERNAL INTERRUPT
extern void EINT0_ISR(void)__irq;
extern void config_vic_for_eint0(void);
extern void config_eint0(void);

extern void config_vic_for_uart0(void);

extern char a[];


// home automation
extern u8 flag;
extern u8 temp;
//extern void config_eint0(void);
//extern void config_vic_for_eint0(void);
//extern void config_vic_for_uart0(void);


extern void config_vic_for_timer1(void);
extern void config_timer1(void);

// SPI0
extern void spi0_init(void);
extern u8 spi0(u8 data);
extern u16 mcp3204_read(u8 ch_num);

// I2C
extern void i2c_init(void);
extern void i2c_byte_write_frame(u8 sa,u8 mr,u8 data);
extern u8 i2c_byte_read_frame(u8 sa,u8 mr);


// digital clock
extern u8 flag1;
extern u8 flag2;
extern u8 flag3;
extern void config_vic_for_eint0(void);
extern void config_eint0(void);
extern void config_vic_for_eint2(void);
extern void config_eint2(void);
extern u8 hex_to_decimal(u8 num);
extern u8 decimal_to_hex(u8 num);

// CAN1

typedef struct CAN1_MSG
{
	u32 id;
	u32 byteA;
	u32 byteB;
	u8 rtr;
	u8 dlc;
}CAN1;

extern void can1_init(void);
extern void can1_tx(CAN1 v);

// CAN2
typedef struct CAN2_MSG
{
	u32 id;
	u32 byteA;
	u32 byteB;
	u8 rtr;
	u8 dlc;
}CAN2;

extern void can2_init(void);
extern void can2_tx(CAN2 v);
extern void can2_rx(CAN2 *ptr);

extern void config_vic_for_can2(void);
extern void config_int_can2(void);
//extern u8 flag1;
extern CAN2 v2;
extern CAN2 v1;
extern CAN2 r1;


// dashboard 

extern CAN2 v1;
extern CAN2 v2;
extern CAN2 v3;
extern CAN2 v4;
extern CAN2 v5;

extern u8 flag;
extern u8 flag1;
extern u8 flag2;
extern u8 flag3;

extern void config_vic_for_eint0(void);
extern void config_eint0(void);
extern void config_vic_for_eint1(void);
extern void config_eint1(void);
extern void config_vic_for_eint2(void);
extern void config_eint2(void);

extern void config_vic_for_can2(void);
extern void config_can2(void);

extern void head_light_cgram(void);
extern void left_indicator_cgram(void);
extern void right_indicator_cgram(void);

extern void head_light_cgram1(void);
extern void left_indicator_cgram1(void);
extern void right_indicator_cgram1(void);

extern void degree_cgram(void);


