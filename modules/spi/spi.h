#ifndef C0_SPI_H
#define C0_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#define SPI1     ( (volatile SPI_Base_TypeDef*)       0x40013000)
#define SPI2     ( (volatile SPI_Base_TypeDef*)       0x40013800)

typedef struct SPI_CR1 {
    unsigned long   CPHA:1,
                    CPOL: 1,
                    MSTR: 1,
                    BR: 3,
                    SPE: 1,
                    LSBFIRST: 1,
                    SSI: 1,
                    SSM: 1,
                    RXONLY: 1,
                    DFF:1,
                    CRCNEXT:1,
                    CRCEN:1,
                    BIDIOE: 1,
                    BIDIMODE: 1,
                    :16;
} SPI_CR1_TypeDef;

typedef struct SPI_SR {
    unsigned long   RXNE: 1,
                    TXE: 1,
                    CHSIDE: 1,
                    UDR: 1,
                    CRCERR: 1,
                    MODF: 1,
                    OVR: 1,
                    BSY: 1,
                    : 8 + 16;
} SPI_SR_TypeDef;

typedef struct SPI_Base {
    SPI_CR1_TypeDef CR1;
    unsigned long: 32;
    SPI_SR_TypeDef  SR;
    unsigned long DR: 16;
} SPI_Base_TypeDef;

void SPI_Transmit_Byte(volatile SPI_Base_TypeDef * SPI, char data);
void SPI_Transmit_Bytes(volatile SPI_Base_TypeDef * SPI, char * data, int size);

#ifdef __cplusplus
}
#endif
#endif //C0_SPI_H
