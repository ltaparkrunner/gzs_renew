#ifndef CLIBINC_H
#define CLIBINC_H
extern "C" {
    #include "sio.h"
    #include "i7k.h"
    #include "i87000_lnx.h"
}

const int RBUF_SIZE = 80;
const int TBUF_SIZE = 20;

struct axil_arrs{
    DWORD _87017_TX[TBUF_SIZE]; // = {0};
    float _87017_RX[RBUF_SIZE]; //  = {0};
    DWORD _87024_TX[TBUF_SIZE]; // = {0};
    float _87024_RX[RBUF_SIZE]; // = {0};
    DWORD _87024_2_TX[TBUF_SIZE]; // = {0};
    float _87024_2_RX[RBUF_SIZE];   // = {0};
    DWORD _87063_TX[TBUF_SIZE]; // = {0};
    float _87063_RX[RBUF_SIZE]; // = {0};
    char szSend[RBUF_SIZE], szReceive[RBUF_SIZE];
};

extern struct axil_arrs ar;
#endif // CLIBINC_H
