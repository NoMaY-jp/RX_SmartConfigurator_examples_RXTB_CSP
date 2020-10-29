#ifndef CONFIG_EXT_H
#define CONFIG_EXT_H

#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || (defined(__cplusplus) && (__cplusplus >= 201103L))

#define Printf( serial, ... )\
    do\
    {\
        extern const uint16_t serial##_transmit_buff_size;\
        extern uint8_t serial##_transmit_buff[];\
        extern volatile bool serial##_transmit_end;\
        uint32_t len;\
        if ( _IEN( R_CONFIG_##serial##_TXINT ) == 0 )\
        {\
            R_Config_##serial##_Start();\
        }\
        len = snprintf( (char *)serial##_transmit_buff, serial##_transmit_buff_size, __VA_ARGS__ );\
        R_Config_##serial##_Serial_Send( serial##_transmit_buff, len );\
        do{}while (serial##_transmit_end == false); serial##_transmit_end = false;\
    }while (0)

#define R_CONFIG_SCI_SEND_IMPL( serial, size )\
    const uint16_t serial##_transmit_buff_size = size;\
    uint8_t serial##_transmit_buff[size];\
    volatile bool serial##_transmit_end

#define R_CONFIG_SCI_CALLBACK_TRANSMITEND( serial )\
    do{\
        extern volatile bool serial##_transmit_end;\
        serial##_transmit_end = true;\
        r_Config_##serial##_callback_transmitend();\
    }while(0)

#define R_CONFIG_SCI0_TXINT  _SCI0_TXI0
#define R_CONFIG_SCI1_TXINT  _SCI1_TXI1
#define R_CONFIG_SCI2_TXINT  _SCI2_TXI2
#define R_CONFIG_SCI3_TXINT  _SCI3_TXI3
#define R_CONFIG_SCI4_TXINT  _SCI4_TXI4
#define R_CONFIG_SCI5_TXINT  _SCI5_TXI5
#define R_CONFIG_SCI6_TXINT  _SCI6_TXI6
#define R_CONFIG_SCI7_TXINT  _SCI7_TXI7
#define R_CONFIG_SCI8_TXINT  _SCI8_TXI8
#define R_CONFIG_SCI9_TXINT  _SCI9_TXI9
#define R_CONFIG_SCI10_TXINT _SCI10_TXI10
#define R_CONFIG_SCI11_TXINT _SCI11_TXI11
#define R_CONFIG_SCI12_TXINT _SCI12_TXI12

#define R_CONFIG_SCI0_CALLBACK_TRANSMITEND()  R_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI0 )
#define R_CONFIG_SCI1_CALLBACK_TRANSMITEND()  R_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI1 )
#define R_CONFIG_SCI2_CALLBACK_TRANSMITEND()  R_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI2 )
#define R_CONFIG_SCI3_CALLBACK_TRANSMITEND()  R_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI3 )
#define R_CONFIG_SCI4_CALLBACK_TRANSMITEND()  R_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI4 )
#define R_CONFIG_SCI5_CALLBACK_TRANSMITEND()  R_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI5 )
#define R_CONFIG_SCI6_CALLBACK_TRANSMITEND()  R_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI6 )
#define R_CONFIG_SCI7_CALLBACK_TRANSMITEND()  R_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI7 )
#define R_CONFIG_SCI8_CALLBACK_TRANSMITEND()  R_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI8 )
#define R_CONFIG_SCI9_CALLBACK_TRANSMITEND()  R_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI9 )
#define R_CONFIG_SCI10_CALLBACK_TRANSMITEND() R_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI10 )
#define R_CONFIG_SCI11_CALLBACK_TRANSMITEND() R_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI11 )
#define R_CONFIG_SCI12_CALLBACK_TRANSMITEND() R_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI12 )

#define r_Config_SCI0_callback_transmitend( ... )    r_Config_SCI0_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI0_callback_transmitendXXXvoid()  r_Config_SCI0_callback_transmitend( void )
#define r_Config_SCI0_callback_transmitendXXX()      R_CONFIG_SCI0_CALLBACK_TRANSMITEND()

#define r_Config_SCI1_callback_transmitend( ... )    r_Config_SCI1_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI1_callback_transmitendXXXvoid()  r_Config_SCI1_callback_transmitend( void )
#define r_Config_SCI1_callback_transmitendXXX()      R_CONFIG_SCI1_CALLBACK_TRANSMITEND()

#define r_Config_SCI2_callback_transmitend( ... )    r_Config_SCI2_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI2_callback_transmitendXXXvoid()  r_Config_SCI2_callback_transmitend( void )
#define r_Config_SCI2_callback_transmitendXXX()      R_CONFIG_SCI2_CALLBACK_TRANSMITEND()

#define r_Config_SCI3_callback_transmitend( ... )    r_Config_SCI3_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI3_callback_transmitendXXXvoid()  r_Config_SCI3_callback_transmitend( void )
#define r_Config_SCI3_callback_transmitendXXX()      R_CONFIG_SCI3_CALLBACK_TRANSMITEND()

#define r_Config_SCI4_callback_transmitend( ... )    r_Config_SCI4_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI4_callback_transmitendXXXvoid()  r_Config_SCI4_callback_transmitend( void )
#define r_Config_SCI4_callback_transmitendXXX()      R_CONFIG_SCI4_CALLBACK_TRANSMITEND()

#define r_Config_SCI5_callback_transmitend( ... )    r_Config_SCI5_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI5_callback_transmitendXXXvoid()  r_Config_SCI5_callback_transmitend( void )
#define r_Config_SCI5_callback_transmitendXXX()      R_CONFIG_SCI5_CALLBACK_TRANSMITEND()

#define r_Config_SCI6_callback_transmitend( ... )    r_Config_SCI6_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI6_callback_transmitendXXXvoid()  r_Config_SCI6_callback_transmitend( void )
#define r_Config_SCI6_callback_transmitendXXX()      R_CONFIG_SCI6_CALLBACK_TRANSMITEND()

#define r_Config_SCI7_callback_transmitend( ... )    r_Config_SCI7_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI7_callback_transmitendXXXvoid()  r_Config_SCI7_callback_transmitend( void )
#define r_Config_SCI7_callback_transmitendXXX()      R_CONFIG_SCI7_CALLBACK_TRANSMITEND()

#define r_Config_SCI8_callback_transmitend( ... )    r_Config_SCI8_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI8_callback_transmitendXXXvoid()  r_Config_SCI8_callback_transmitend( void )
#define r_Config_SCI8_callback_transmitendXXX()      R_CONFIG_SCI8_CALLBACK_TRANSMITEND()

#define r_Config_SCI9_callback_transmitend( ... )    r_Config_SCI9_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI9_callback_transmitendXXXvoid()  r_Config_SCI9_callback_transmitend( void )
#define r_Config_SCI9_callback_transmitendXXX()      R_CONFIG_SCI9_CALLBACK_TRANSMITEND()

#define r_Config_SCI10_callback_transmitend( ... )   r_Config_SCI10_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI10_callback_transmitendXXXvoid() r_Config_SCI10_callback_transmitend( void )
#define r_Config_SCI10_callback_transmitendXXX()     R_CONFIG_SCI10_CALLBACK_TRANSMITEND()

#define r_Config_SCI11_callback_transmitend( ... )   r_Config_SCI11_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI11_callback_transmitendXXXvoid() r_Config_SCI11_callback_transmitend( void )
#define r_Config_SCI11_callback_transmitendXXX()     R_CONFIG_SCI11_CALLBACK_TRANSMITEND()

#define r_Config_SCI12_callback_transmitend( ... )   r_Config_SCI12_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI12_callback_transmitendXXXvoid() r_Config_SCI12_callback_transmitend( void )
#define r_Config_SCI12_callback_transmitendXXX()     R_CONFIG_SCI12_CALLBACK_TRANSMITEND()

#endif /* (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || (defined(__cplusplus) && (__cplusplus >= 201103L)) */

#endif
