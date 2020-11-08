#ifndef CONFIG_EXT_H
#define CONFIG_EXT_H

#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || (defined(__cplusplus) && (__cplusplus >= 201103L))

#define Printf( serial, ... )\
    do\
    {\
        extern const uint16_t g_##serial##_tx_buffer_size;\
        extern uint8_t g_##serial##_tx_buffer[];\
        extern volatile bool g_##serial##_tx_ready_flag;\
        uint32_t len;\
        if (_IEN( U_CONFIG_##serial##_TXINT ) == 0)\
        {\
            R_Config_##serial##_Start();\
        }\
        len = snprintf( (char *)g_##serial##_tx_buffer, g_##serial##_tx_buffer_size, __VA_ARGS__ );\
        g_##serial##_tx_ready_flag = false;\
        R_Config_##serial##_Serial_Send( g_##serial##_tx_buffer, len );\
        do{}while (g_##serial##_tx_ready_flag == false);\
    }while (0)

#define U_CONFIG_UART_PRINTF_IMPL( serial, size )\
    const uint16_t g_##serial##_tx_buffer_size = size;\
    uint8_t g_##serial##_tx_buffer[size];\
    volatile bool g_##serial##_tx_ready_flag = true

#define U_Config_I2C_Master_Start( serial ) R_Config_##serial##_Start();

#define U_Config_I2C_Master_Send_UWT( serial, adr, ... )\
    do\
    {\
        extern volatile bool g_##serial##_tx_ready_flag;\
        g_##serial##_tx_ready_flag = false;\
        R_Config_##serial##_IIC_Master_Send( ((adr) << 1), __VA_ARGS__ );\
        do{}while (g_##serial##_tx_ready_flag == false);\
    }while (0)

#define U_Config_I2C_Master_Receive_UWT( serial, adr, ... )\
    do\
    {\
        extern volatile bool g_##serial##_rx_ready_flag;\
        g_##serial##_rx_ready_flag = false;\
        R_Config_##serial##_IIC_Master_Receive( (((adr) << 1) | 1), __VA_ARGS__ );\
        do{}while (g_##serial##_rx_ready_flag == false);\
    }while (0)

#define U_CONFIG_I2C_MASTER_IMPL( serial )\
    volatile bool g_##serial##_tx_ready_flag = true;\
    volatile bool g_##serial##_rx_ready_flag = false

#define U_CONFIG_SCI_CALLBACK_TRANSMITEND( serial )\
    do{\
        extern volatile bool g_##serial##_tx_ready_flag;\
        g_##serial##_tx_ready_flag = true;\
        r_Config_##serial##_callback_transmitend();\
    }while(0)

#define U_CONFIG_SCI_CALLBACK_RECEIVEEND( serial )\
    do{\
        extern volatile bool g_##serial##_rx_ready_flag;\
        g_##serial##_rx_ready_flag = true;\
        r_Config_##serial##_callback_receiveend();\
    }while(0)

#define U_CONFIG_SCI0_TXINT  _SCI0_TXI0
#define U_CONFIG_SCI1_TXINT  _SCI1_TXI1
#define U_CONFIG_SCI2_TXINT  _SCI2_TXI2
#define U_CONFIG_SCI3_TXINT  _SCI3_TXI3
#define U_CONFIG_SCI4_TXINT  _SCI4_TXI4
#define U_CONFIG_SCI5_TXINT  _SCI5_TXI5
#define U_CONFIG_SCI6_TXINT  _SCI6_TXI6
#define U_CONFIG_SCI7_TXINT  _SCI7_TXI7
#define U_CONFIG_SCI8_TXINT  _SCI8_TXI8
#define U_CONFIG_SCI9_TXINT  _SCI9_TXI9
#define U_CONFIG_SCI10_TXINT _SCI10_TXI10
#define U_CONFIG_SCI11_TXINT _SCI11_TXI11
#define U_CONFIG_SCI12_TXINT _SCI12_TXI12

#define U_CONFIG_SCI0_CALLBACK_TRANSMITEND()  U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI0  )
#define U_CONFIG_SCI1_CALLBACK_TRANSMITEND()  U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI1  )
#define U_CONFIG_SCI2_CALLBACK_TRANSMITEND()  U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI2  )
#define U_CONFIG_SCI3_CALLBACK_TRANSMITEND()  U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI3  )
#define U_CONFIG_SCI4_CALLBACK_TRANSMITEND()  U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI4  )
#define U_CONFIG_SCI5_CALLBACK_TRANSMITEND()  U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI5  )
#define U_CONFIG_SCI6_CALLBACK_TRANSMITEND()  U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI6  )
#define U_CONFIG_SCI7_CALLBACK_TRANSMITEND()  U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI7  )
#define U_CONFIG_SCI8_CALLBACK_TRANSMITEND()  U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI8  )
#define U_CONFIG_SCI9_CALLBACK_TRANSMITEND()  U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI9  )
#define U_CONFIG_SCI10_CALLBACK_TRANSMITEND() U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI10 )
#define U_CONFIG_SCI11_CALLBACK_TRANSMITEND() U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI11 )
#define U_CONFIG_SCI12_CALLBACK_TRANSMITEND() U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI12 )
#define U_CONFIG_SCI0_CALLBACK_RECEIVEEND()   U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI0  )
#define U_CONFIG_SCI1_CALLBACK_RECEIVEEND()   U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI1  )
#define U_CONFIG_SCI2_CALLBACK_RECEIVEEND()   U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI2  )
#define U_CONFIG_SCI3_CALLBACK_RECEIVEEND()   U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI3  )
#define U_CONFIG_SCI4_CALLBACK_RECEIVEEND()   U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI4  )
#define U_CONFIG_SCI5_CALLBACK_RECEIVEEND()   U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI5  )
#define U_CONFIG_SCI6_CALLBACK_RECEIVEEND()   U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI6  )
#define U_CONFIG_SCI7_CALLBACK_RECEIVEEND()   U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI7  )
#define U_CONFIG_SCI8_CALLBACK_RECEIVEEND()   U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI8  )
#define U_CONFIG_SCI9_CALLBACK_RECEIVEEND()   U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI9  )
#define U_CONFIG_SCI10_CALLBACK_RECEIVEEND()  U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI10 )
#define U_CONFIG_SCI11_CALLBACK_RECEIVEEND()  U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI11 )
#define U_CONFIG_SCI12_CALLBACK_RECEIVEEND()  U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI12 )

#define r_Config_SCI0_callback_transmitend( ... )    r_Config_SCI0_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI0_callback_transmitendXXXvoid()  r_Config_SCI0_callback_transmitend( void )
#define r_Config_SCI0_callback_transmitendXXX()      U_CONFIG_SCI0_CALLBACK_TRANSMITEND()

#define r_Config_SCI1_callback_transmitend( ... )    r_Config_SCI1_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI1_callback_transmitendXXXvoid()  r_Config_SCI1_callback_transmitend( void )
#define r_Config_SCI1_callback_transmitendXXX()      U_CONFIG_SCI1_CALLBACK_TRANSMITEND()

#define r_Config_SCI2_callback_transmitend( ... )    r_Config_SCI2_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI2_callback_transmitendXXXvoid()  r_Config_SCI2_callback_transmitend( void )
#define r_Config_SCI2_callback_transmitendXXX()      U_CONFIG_SCI2_CALLBACK_TRANSMITEND()

#define r_Config_SCI3_callback_transmitend( ... )    r_Config_SCI3_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI3_callback_transmitendXXXvoid()  r_Config_SCI3_callback_transmitend( void )
#define r_Config_SCI3_callback_transmitendXXX()      U_CONFIG_SCI3_CALLBACK_TRANSMITEND()

#define r_Config_SCI4_callback_transmitend( ... )    r_Config_SCI4_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI4_callback_transmitendXXXvoid()  r_Config_SCI4_callback_transmitend( void )
#define r_Config_SCI4_callback_transmitendXXX()      U_CONFIG_SCI4_CALLBACK_TRANSMITEND()

#define r_Config_SCI5_callback_transmitend( ... )    r_Config_SCI5_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI5_callback_transmitendXXXvoid()  r_Config_SCI5_callback_transmitend( void )
#define r_Config_SCI5_callback_transmitendXXX()      U_CONFIG_SCI5_CALLBACK_TRANSMITEND()

#define r_Config_SCI6_callback_transmitend( ... )    r_Config_SCI6_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI6_callback_transmitendXXXvoid()  r_Config_SCI6_callback_transmitend( void )
#define r_Config_SCI6_callback_transmitendXXX()      U_CONFIG_SCI6_CALLBACK_TRANSMITEND()

#define r_Config_SCI7_callback_transmitend( ... )    r_Config_SCI7_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI7_callback_transmitendXXXvoid()  r_Config_SCI7_callback_transmitend( void )
#define r_Config_SCI7_callback_transmitendXXX()      U_CONFIG_SCI7_CALLBACK_TRANSMITEND()

#define r_Config_SCI8_callback_transmitend( ... )    r_Config_SCI8_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI8_callback_transmitendXXXvoid()  r_Config_SCI8_callback_transmitend( void )
#define r_Config_SCI8_callback_transmitendXXX()      U_CONFIG_SCI8_CALLBACK_TRANSMITEND()

#define r_Config_SCI9_callback_transmitend( ... )    r_Config_SCI9_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI9_callback_transmitendXXXvoid()  r_Config_SCI9_callback_transmitend( void )
#define r_Config_SCI9_callback_transmitendXXX()      U_CONFIG_SCI9_CALLBACK_TRANSMITEND()

#define r_Config_SCI10_callback_transmitend( ... )   r_Config_SCI10_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI10_callback_transmitendXXXvoid() r_Config_SCI10_callback_transmitend( void )
#define r_Config_SCI10_callback_transmitendXXX()     U_CONFIG_SCI10_CALLBACK_TRANSMITEND()

#define r_Config_SCI11_callback_transmitend( ... )   r_Config_SCI11_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI11_callback_transmitendXXXvoid() r_Config_SCI11_callback_transmitend( void )
#define r_Config_SCI11_callback_transmitendXXX()     U_CONFIG_SCI11_CALLBACK_TRANSMITEND()

#define r_Config_SCI12_callback_transmitend( ... )   r_Config_SCI12_callback_transmitendXXX##__VA_ARGS__()
#define r_Config_SCI12_callback_transmitendXXXvoid() r_Config_SCI12_callback_transmitend( void )
#define r_Config_SCI12_callback_transmitendXXX()     U_CONFIG_SCI12_CALLBACK_TRANSMITEND()

#define r_Config_SCI0_callback_receiveend( ... )     r_Config_SCI0_callback_receiveendXXX##__VA_ARGS__()
#define r_Config_SCI0_callback_receiveendXXXvoid()   r_Config_SCI0_callback_receiveend( void )
#define r_Config_SCI0_callback_receiveendXXX()       U_CONFIG_SCI0_CALLBACK_RECEIVEEND()

#define r_Config_SCI1_callback_receiveend( ... )     r_Config_SCI1_callback_receiveendXXX##__VA_ARGS__()
#define r_Config_SCI1_callback_receiveendXXXvoid()   r_Config_SCI1_callback_receiveend( void )
#define r_Config_SCI1_callback_receiveendXXX()       U_CONFIG_SCI1_CALLBACK_RECEIVEEND()

#define r_Config_SCI2_callback_receiveend( ... )     r_Config_SCI2_callback_receiveendXXX##__VA_ARGS__()
#define r_Config_SCI2_callback_receiveendXXXvoid()   r_Config_SCI2_callback_receiveend( void )
#define r_Config_SCI2_callback_receiveendXXX()       U_CONFIG_SCI2_CALLBACK_RECEIVEEND()

#define r_Config_SCI3_callback_receiveend( ... )     r_Config_SCI3_callback_receiveendXXX##__VA_ARGS__()
#define r_Config_SCI3_callback_receiveendXXXvoid()   r_Config_SCI3_callback_receiveend( void )
#define r_Config_SCI3_callback_receiveendXXX()       U_CONFIG_SCI3_CALLBACK_RECEIVEEND()

#define r_Config_SCI4_callback_receiveend( ... )     r_Config_SCI4_callback_receiveendXXX##__VA_ARGS__()
#define r_Config_SCI4_callback_receiveendXXXvoid()   r_Config_SCI4_callback_receiveend( void )
#define r_Config_SCI4_callback_receiveendXXX()       U_CONFIG_SCI4_CALLBACK_RECEIVEEND()

#define r_Config_SCI5_callback_receiveend( ... )     r_Config_SCI5_callback_receiveendXXX##__VA_ARGS__()
#define r_Config_SCI5_callback_receiveendXXXvoid()   r_Config_SCI5_callback_receiveend( void )
#define r_Config_SCI5_callback_receiveendXXX()       U_CONFIG_SCI5_CALLBACK_RECEIVEEND()

#define r_Config_SCI6_callback_receiveend( ... )     r_Config_SCI6_callback_receiveendXXX##__VA_ARGS__()
#define r_Config_SCI6_callback_receiveendXXXvoid()   r_Config_SCI6_callback_receiveend( void )
#define r_Config_SCI6_callback_receiveendXXX()       U_CONFIG_SCI6_CALLBACK_RECEIVEEND()

#define r_Config_SCI7_callback_receiveend( ... )     r_Config_SCI7_callback_receiveendXXX##__VA_ARGS__()
#define r_Config_SCI7_callback_receiveendXXXvoid()   r_Config_SCI7_callback_receiveend( void )
#define r_Config_SCI7_callback_receiveendXXX()       U_CONFIG_SCI7_CALLBACK_RECEIVEEND()

#define r_Config_SCI8_callback_receiveend( ... )     r_Config_SCI8_callback_receiveendXXX##__VA_ARGS__()
#define r_Config_SCI8_callback_receiveendXXXvoid()   r_Config_SCI8_callback_receiveend( void )
#define r_Config_SCI8_callback_receiveendXXX()       U_CONFIG_SCI8_CALLBACK_RECEIVEEND()

#define r_Config_SCI9_callback_receiveend( ... )     r_Config_SCI9_callback_receiveendXXX##__VA_ARGS__()
#define r_Config_SCI9_callback_receiveendXXXvoid()   r_Config_SCI9_callback_receiveend( void )
#define r_Config_SCI9_callback_receiveendXXX()       U_CONFIG_SCI9_CALLBACK_RECEIVEEND()

#define r_Config_SCI10_callback_receiveend( ... )    r_Config_SCI10_callback_receiveendXXX##__VA_ARGS__()
#define r_Config_SCI10_callback_receiveendXXXvoid()  r_Config_SCI10_callback_receiveend( void )
#define r_Config_SCI10_callback_receiveendXXX()      U_CONFIG_SCI10_CALLBACK_RECEIVEEND()

#define r_Config_SCI11_callback_receiveend( ... )    r_Config_SCI11_callback_receiveendXXX##__VA_ARGS__()
#define r_Config_SCI11_callback_receiveendXXXvoid()  r_Config_SCI11_callback_receiveend( void )
#define r_Config_SCI11_callback_receiveendXXX()      U_CONFIG_SCI11_CALLBACK_RECEIVEEND()

#define r_Config_SCI12_callback_receiveend( ... )    r_Config_SCI12_callback_receiveendXXX##__VA_ARGS__()
#define r_Config_SCI12_callback_receiveendXXXvoid()  r_Config_SCI12_callback_receiveend( void )
#define r_Config_SCI12_callback_receiveendXXX()      U_CONFIG_SCI12_CALLBACK_RECEIVEEND()

#endif /* (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || (defined(__cplusplus) && (__cplusplus >= 201103L)) */

#endif
