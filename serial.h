#define SBUFSIZE 256
typedef struct {
	volatile unsigned head;
	volatile unsigned tail;
	volatile int count;
	char buffer[SBUFSIZE+1];
} SerialBuffer;

void initUART(void);
void UART_baud(int baudrate);
void putBuf(SerialBuffer *sbuf, char c);
char getBuf(SerialBuffer *sbuf);
int rx_count(void);
int tx_count(void);
char egetc(void);
void eputc(char c);
void printString(char *s);
void printInteger(unsigned int Number);
void printShort(unsigned int Number);
void printByte(unsigned int Number);

