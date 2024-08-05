#ifndef C0_I2C_H
#define C0_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#define I2C_CR1 ((volatile I2C_CR1_TypeDef *) 0x40005400)
#define I2C_CR2 ((volatile I2C_CR2_TypeDef *) 0x40005404)
#define I2C_CCR ((volatile I2C_CCR_TypeDef *) 0x4000541C)
#define I2C_DR *((volatile unsigned char *) 0x40005410)
#define I2C_TRISE ((volatile I2C_TRISE_TypeDef *) 0x40005420)
#define I2C_SR1 ((volatile struct I2C_SR1_TypeDef *) 0x40005414)
#define I2C_SR2 ((volatile struct I2C_SR2_TypeDef *) 0x40005418)

typedef struct I2C_CCR_TypeDef {
    unsigned short CCR: 12;
    unsigned char : 2;
    unsigned char F_S: 1;
} I2C_CCR_TypeDef;

typedef struct I2C_TRISE_TypeDef {
    unsigned long TRISE: 6,
                       : 9;
} I2C_TRISE_TypeDef;

typedef union I2C_CR1_TypeDef {
    struct {
        unsigned long PE: 1,
                      SMBUS: 1,
                      : 1,
                      SMBTYPE: 1,
                      ENARP: 1,
                      ENPEC: 1,
                      ENGC: 1,
                      NO_STRETCH: 1,
                      START: 1,
                      STOP: 1,
                      ACK: 1,
                      POS: 1,
                      PEC: 1,
                      ALERT: 1,
                      : 1,
                      SWREST: 1;
    };
    unsigned long value;
} I2C_CR1_TypeDef;

typedef struct I2C_CR2_TypeDef {
    unsigned char FREQ: 6;
    unsigned char : 2;
    unsigned char ITERREN: 1;
    unsigned char TEVTEN: 1;
    unsigned char ITBUFEN: 1;
    unsigned char DMAEN: 1;
    unsigned char LAST: 1;
} I2C_CR2_TypeDef;

typedef struct I2C_SR1_TypeDef {
    unsigned char SB: 1;
    unsigned char ADDR: 1;
    unsigned char BTF: 1;
    unsigned char ADD10: 1;
    unsigned char STOPF: 1;
    unsigned char : 1;
    unsigned char RxNE: 1;
    unsigned char TxE: 1;
    unsigned char BERR: 1;
    unsigned char ARLO: 1;
    unsigned char AF: 1;
    unsigned char OVR: 1;
    unsigned char PECERR: 1;
    unsigned char : 1;
    unsigned char TIMEOUT: 1;
    unsigned char SMBALERT: 1;
} I2C_SR1_TypeDef;

typedef struct I2C_SR2_TypeDef {
    unsigned char MSL: 1;
    unsigned char BUSY: 1;
    unsigned char TRA: 1;
    unsigned char : 1;
    unsigned char GENCALL: 1;
    unsigned char SMBDEFAULT: 1;
    unsigned char SMBHOST: 1;
    unsigned char DUALF: 1;
    unsigned char PEC: 8;
} I2C_SR2_TypeDef;

void I2C_Init();
void I2C_Start(char address);
void I2C_Start_Raw(char address);
void I2C_Read(char address);
void I2C_Send(char data);
void I2C_End();
void I2C_Send_Byte(char address, char data);
void I2C_Send_2_Bytes(char address, short data);

#ifdef __cplusplus
}
#endif
#endif //C0_I2C_H
