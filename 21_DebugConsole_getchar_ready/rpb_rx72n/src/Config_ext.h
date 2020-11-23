#ifndef CONFIG_EXT_H
#define CONFIG_EXT_H

#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || (defined(__cplusplus) && (__cplusplus >= 201103L))

#include <stdarg.h>

static inline bool is_putchar_busy( void )
{
    volatile R_BSP_EVENACCESS_SFR uint32_t * const p_dbg_stat = (volatile R_BSP_EVENACCESS_SFR uint32_t *)0x840C0;
    const uint32_t dbg_tx_busy = 0x00000100;

    return 0 != (*p_dbg_stat & dbg_tx_busy);
}

static inline bool is_getchar_ready( void )
{
    volatile R_BSP_EVENACCESS_SFR uint32_t * const p_dbg_stat = (volatile R_BSP_EVENACCESS_SFR uint32_t *)0x840C0;
    const uint32_t dbg_rx_ready = 0x00001000;

    return 0 != (*p_dbg_stat & dbg_rx_ready);
}

#define Printf( serial, ... ) U_Config_##serial##_Serial_Printf( __VA_ARGS__ )

#define U_CONFIG_UART_PRINTF_IMPL( serial, size )\
    static const uint16_t g_##serial##_tx_buffer_size = size;\
    static uint8_t g_##serial##_tx_buffer[size];\
    static volatile bool g_##serial##_tx_ready_flag = true;\
    extern void u_Config_##serial##_callback_transmitend( void );\
    extern void u_Config_##serial##_callback_transmitend( void )\
    {\
        g_##serial##_tx_ready_flag = true;\
    }\
    extern bool U_Config_##serial##_Serial_Is_Send_Busy( void )\
    {\
        return !g_##serial##_tx_ready_flag;\
    }\
    extern void U_Config_##serial##_Serial_Send( const uint8_t * const tx_buf, uint16_t tx_num )\
    {\
        g_##serial##_tx_ready_flag = false;\
        R_Config_##serial##_Serial_Send( (/* absolutely... const */ uint8_t *)tx_buf, tx_num );\
    }\
    extern void U_Config_##serial##_Serial_Send_UWT( const uint8_t * const tx_buf, uint16_t tx_num )\
    {\
        U_Config_##serial##_Serial_Send( tx_buf, tx_num );\
        do{}while (U_Config_##serial##_Serial_Is_Send_Busy());\
    }\
    extern void U_Config_##serial##_Serial_Printf( const char * const fmt, ... )\
    {\
        extern const uint16_t g_##serial##_tx_buffer_size;\
        extern uint8_t g_##serial##_tx_buffer[];\
        va_list args;\
        int len;\
        if (0 == _IEN( U_CONFIG_##serial##_TXINT ))\
        {\
            R_Config_##serial##_Start();\
        }\
        args = NULL;\
        va_start( args, fmt );\
        len = vsnprintf( (char *)g_##serial##_tx_buffer, g_##serial##_tx_buffer_size, fmt, args );\
        if (0 < len )\
        {\
            U_Config_##serial##_Serial_Send_UWT( g_##serial##_tx_buffer, len );\
        }\
    }\
    extern void u_Config_ext_header_file_Remove_Compiler_Warning( void )

#define U_CONFIG_UART_PRINTF_PROTO( serial )\
    extern bool U_Config_##serial##_Serial_Is_Send_Busy( void );\
    extern void U_Config_##serial##_Serial_Send( const uint8_t * const tx_buf, uint16_t tx_num );\
    extern void U_Config_##serial##_Serial_Send_UWT( const uint8_t * const tx_buf, uint16_t tx_num );\
    extern void U_Config_##serial##_Serial_Printf( const char * const fmt, ... )

U_CONFIG_UART_PRINTF_PROTO( SCI0  );
U_CONFIG_UART_PRINTF_PROTO( SCI1  );
U_CONFIG_UART_PRINTF_PROTO( SCI2  );
U_CONFIG_UART_PRINTF_PROTO( SCI3  );
U_CONFIG_UART_PRINTF_PROTO( SCI4  );
U_CONFIG_UART_PRINTF_PROTO( SCI5  );
U_CONFIG_UART_PRINTF_PROTO( SCI6  );
U_CONFIG_UART_PRINTF_PROTO( SCI7  );
U_CONFIG_UART_PRINTF_PROTO( SCI8  );
U_CONFIG_UART_PRINTF_PROTO( SCI9  );
U_CONFIG_UART_PRINTF_PROTO( SCI10 );
U_CONFIG_UART_PRINTF_PROTO( SCI11 );
U_CONFIG_UART_PRINTF_PROTO( SCI12 );

#define Getchar( serial ) U_Config_##serial##_UART_Getchar()
#define Is_Getchar_Ready( serial ) U_Config_##serial##_UART_Is_Getchar_Ready()

#define U_CONFIG_UART_GETCHAR_IMPL( serial, size )\
    static const uint16_t g_##serial##_rx_buffer_size = size;\
    static volatile uint8_t g_##serial##_rx_buffer[size];\
    static volatile uint8_t g_##serial##_rx_data;\
    static volatile uint8_t * volatile gp_##serial##_rx_buffer_data_put_address = g_##serial##_rx_buffer;\
    static volatile uint8_t * gp_##serial##_rx_buffer_data_get_address = g_##serial##_rx_buffer;\
    static volatile uint16_t  g_##serial##_rx_buffer_data_count = 0;\
    static bool g_##serial##_rx_is_operation_started = false;\
    static inline bool u_Config_##serial##_UART_rx_buffer_is_empty( void )\
    {\
        return 0 == g_##serial##_rx_buffer_data_count;\
    }\
    static inline bool u_Config_##serial##_UART_rx_buffer_is_full( void )\
    {\
        return g_##serial##_rx_buffer_size <= g_##serial##_rx_buffer_data_count;\
    }\
    static inline void u_Config_##serial##_UART_rx_buffer_get_data( uint8_t *pc )\
    {\
        *pc = *gp_##serial##_rx_buffer_data_get_address++;\
        if ( g_##serial##_rx_buffer + g_##serial##_rx_buffer_size <= gp_##serial##_rx_buffer_data_get_address)\
        {\
            gp_##serial##_rx_buffer_data_get_address = g_##serial##_rx_buffer;\
        }\
        g_##serial##_rx_buffer_data_count--;\
    }\
    static inline void u_Config_##serial##_UART_rx_buffer_put_data( uint8_t c )\
    {\
        *gp_##serial##_rx_buffer_data_put_address++ = c;\
        if ( g_##serial##_rx_buffer + g_##serial##_rx_buffer_size <= gp_##serial##_rx_buffer_data_put_address)\
        {\
            gp_##serial##_rx_buffer_data_put_address = g_##serial##_rx_buffer;\
        }\
        g_##serial##_rx_buffer_data_count++;\
    }\
    extern void u_Config_##serial##_callback_receiveend( void );\
    extern void u_Config_##serial##_callback_receiveend( void )\
    {\
        if (!u_Config_##serial##_UART_rx_buffer_is_full())\
        {\
            u_Config_##serial##_UART_rx_buffer_put_data( g_##serial##_rx_data );\
        }\
        R_Config_##serial##_Serial_Receive( (/* obviously... volatile */ uint8_t *)&g_##serial##_rx_data, 1 );\
    }\
    extern bool U_Config_##serial##_UART_Is_Getchar_Ready( void )\
    {\
        if (0 == _IEN( U_CONFIG_##serial##_RXINT ))\
        {\
            R_Config_##serial##_Start();\
        }\
        if (!g_##serial##_rx_is_operation_started)\
        {\
            R_Config_##serial##_Serial_Receive( (/* obviously... volatile */ uint8_t *)&g_##serial##_rx_data, 1 );\
            g_##serial##_rx_is_operation_started = true;\
        }\
        return !u_Config_##serial##_UART_rx_buffer_is_empty();\
    }\
    extern uint8_t U_Config_##serial##_UART_Getchar( void )\
    {\
        uint8_t c;\
        do{}while (!U_Config_##serial##_UART_Is_Getchar_Ready());\
        _IEN( U_CONFIG_##serial##_RXINT ) = 0;\
        {\
            u_Config_##serial##_UART_rx_buffer_get_data( &c );\
        }\
        _IEN( U_CONFIG_##serial##_RXINT ) = 1;\
        return c;\
    }\
    extern void u_Config_ext_header_file_Remove_Compiler_Warning( void )

#define U_CONFIG_UART_GETCHAR_PROTO( serial )\
    extern bool U_Config_##serial##_UART_Is_Getchar_Ready( void );\
    extern uint8_t U_Config_##serial##_UART_Getchar( void )

U_CONFIG_UART_GETCHAR_PROTO( SCI0  );
U_CONFIG_UART_GETCHAR_PROTO( SCI1  );
U_CONFIG_UART_GETCHAR_PROTO( SCI2  );
U_CONFIG_UART_GETCHAR_PROTO( SCI3  );
U_CONFIG_UART_GETCHAR_PROTO( SCI4  );
U_CONFIG_UART_GETCHAR_PROTO( SCI5  );
U_CONFIG_UART_GETCHAR_PROTO( SCI6  );
U_CONFIG_UART_GETCHAR_PROTO( SCI7  );
U_CONFIG_UART_GETCHAR_PROTO( SCI8  );
U_CONFIG_UART_GETCHAR_PROTO( SCI9  );
U_CONFIG_UART_GETCHAR_PROTO( SCI10 );
U_CONFIG_UART_GETCHAR_PROTO( SCI11 );
U_CONFIG_UART_GETCHAR_PROTO( SCI12 );

#define U_Config_I2C_Master_Start( serial ) R_Config_##serial##_Start();
#define U_Config_I2C_Master_Send_UWT( serial, adr7, tx_buf, tx_num ) U_Config_##serial##_I2C_Master_Send_UWT( adr7, tx_buf, tx_num )
#define U_Config_I2C_Master_Receive_UWT( serial, adr7, rx_buf, rx_num ) U_Config_##serial##_I2C_Master_Receive_UWT( adr7, rx_buf, rx_num )

#define U_CONFIG_I2C_MASTER_IMPL( serial )\
    static volatile bool g_##serial##_tx_ready_flag = true;\
    static volatile bool g_##serial##_rx_ready_flag = false;\
    extern void u_Config_##serial##_callback_transmitend( void );\
    extern void u_Config_##serial##_callback_transmitend( void )\
    {\
        g_##serial##_tx_ready_flag = true;\
    }\
    extern void u_Config_##serial##_callback_receiveend( void );\
    extern void u_Config_##serial##_callback_receiveend( void )\
    {\
        g_##serial##_rx_ready_flag = true;\
    }\
    extern bool U_Config_##serial##_I2C_Master_Is_Send_Busy( void )\
    {\
        return !g_##serial##_tx_ready_flag;\
    }\
    extern void U_Config_##serial##_I2C_Master_Send( uint8_t adr7, const uint8_t * const tx_buf, uint16_t tx_num )\
    {\
        g_##serial##_tx_ready_flag = false;\
        R_Config_##serial##_IIC_Master_Send( (adr7 << 1), (/* absolutely... const */ uint8_t *)tx_buf, tx_num );\
    }\
    extern void U_Config_##serial##_I2C_Master_Send_UWT( uint8_t adr7, const uint8_t * const tx_buf, uint16_t tx_num )\
    {\
        U_Config_##serial##_I2C_Master_Send( adr7, (uint8_t *)tx_buf, tx_num );\
        do{}while (U_Config_##serial##_I2C_Master_Is_Send_Busy());\
    }\
    extern bool U_Config_##serial##_I2C_Master_Is_Receive_Ready( void )\
    {\
        return g_##serial##_rx_ready_flag;\
    }\
    extern void U_Config_##serial##_I2C_Master_Receive( uint8_t adr7, volatile uint8_t * const rx_buf, uint16_t rx_num )\
    {\
        g_##serial##_rx_ready_flag = false;\
        R_Config_##serial##_IIC_Master_Receive( ((adr7 << 1) | 1), (/* obviously... volatile */ uint8_t *)rx_buf, rx_num );\
    }\
    extern void U_Config_##serial##_I2C_Master_Receive_UWT( uint8_t adr7, uint8_t * const rx_buf, uint16_t rx_num )\
    {\
        U_Config_##serial##_I2C_Master_Receive( adr7, rx_buf, rx_num );\
        do{}while (!U_Config_##serial##_I2C_Master_Is_Receive_Ready());\
    }\
    extern void u_Config_ext_header_file_Remove_Compiler_Warning( void )

#define U_CONFIG_I2C_MASTER_PROTO( serial )\
    extern bool U_Config_##serial##_I2C_Master_Is_Send_Busy( void );\
    extern void U_Config_##serial##_I2C_Master_Send( uint8_t adr7, const uint8_t * const tx_buf, uint16_t tx_num );\
    extern void U_Config_##serial##_I2C_Master_Send_UWT( uint8_t adr7, const uint8_t * const tx_buf, uint16_t tx_num );\
    extern bool U_Config_##serial##_I2C_Master_Is_Receive_Ready( void );\
    extern void U_Config_##serial##_I2C_Master_Receive( uint8_t adr7, volatile uint8_t * const rx_buf, uint16_t rx_num );\
    extern void U_Config_##serial##_I2C_Master_Receive_UWT( uint8_t adr7, uint8_t * const rx_buf, uint16_t rx_num )

U_CONFIG_I2C_MASTER_PROTO( SCI0  );
U_CONFIG_I2C_MASTER_PROTO( SCI1  );
U_CONFIG_I2C_MASTER_PROTO( SCI2  );
U_CONFIG_I2C_MASTER_PROTO( SCI3  );
U_CONFIG_I2C_MASTER_PROTO( SCI4  );
U_CONFIG_I2C_MASTER_PROTO( SCI5  );
U_CONFIG_I2C_MASTER_PROTO( SCI6  );
U_CONFIG_I2C_MASTER_PROTO( SCI7  );
U_CONFIG_I2C_MASTER_PROTO( SCI8  );
U_CONFIG_I2C_MASTER_PROTO( SCI9  );
U_CONFIG_I2C_MASTER_PROTO( SCI10 );
U_CONFIG_I2C_MASTER_PROTO( SCI11 );
U_CONFIG_I2C_MASTER_PROTO( SCI12 );

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
#define U_CONFIG_SCI0_RXINT  _SCI0_RXI0
#define U_CONFIG_SCI1_RXINT  _SCI1_RXI1
#define U_CONFIG_SCI2_RXINT  _SCI2_RXI2
#define U_CONFIG_SCI3_RXINT  _SCI3_RXI3
#define U_CONFIG_SCI4_RXINT  _SCI4_RXI4
#define U_CONFIG_SCI5_RXINT  _SCI5_RXI5
#define U_CONFIG_SCI6_RXINT  _SCI6_RXI6
#define U_CONFIG_SCI7_RXINT  _SCI7_RXI7
#define U_CONFIG_SCI8_RXINT  _SCI8_RXI8
#define U_CONFIG_SCI9_RXINT  _SCI9_RXI9
#define U_CONFIG_SCI10_RXINT _SCI10_RXI10
#define U_CONFIG_SCI11_RXINT _SCI11_RXI11
#define U_CONFIG_SCI12_RXINT _SCI12_RXI12

#define U_CONFIG_SCI_CALLBACK_TRANSMITEND( serial )\
    do{\
        extern void u_Config_##serial##_callback_transmitend( void );\
        u_Config_##serial##_callback_transmitend();\
        r_Config_##serial##_callback_transmitend();\
    }while (0)
#define U_CONFIG_SCI_CALLBACK_RECEIVEEND( serial )\
    do{\
        extern void u_Config_##serial##_callback_receiveend( void );\
        u_Config_##serial##_callback_receiveend();\
        r_Config_##serial##_callback_receiveend();\
    }while (0)

#define U_CONFIG_SCI0_CALLBACK_TRANSMITEND( ) U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI0  )
#define U_CONFIG_SCI1_CALLBACK_TRANSMITEND( ) U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI1  )
#define U_CONFIG_SCI2_CALLBACK_TRANSMITEND( ) U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI2  )
#define U_CONFIG_SCI3_CALLBACK_TRANSMITEND( ) U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI3  )
#define U_CONFIG_SCI4_CALLBACK_TRANSMITEND( ) U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI4  )
#define U_CONFIG_SCI5_CALLBACK_TRANSMITEND( ) U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI5  )
#define U_CONFIG_SCI6_CALLBACK_TRANSMITEND( ) U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI6  )
#define U_CONFIG_SCI7_CALLBACK_TRANSMITEND( ) U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI7  )
#define U_CONFIG_SCI8_CALLBACK_TRANSMITEND( ) U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI8  )
#define U_CONFIG_SCI9_CALLBACK_TRANSMITEND( ) U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI9  )
#define U_CONFIG_SCI10_CALLBACK_TRANSMITEND() U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI10 )
#define U_CONFIG_SCI11_CALLBACK_TRANSMITEND() U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI11 )
#define U_CONFIG_SCI12_CALLBACK_TRANSMITEND() U_CONFIG_SCI_CALLBACK_TRANSMITEND( SCI12 )
#define U_CONFIG_SCI0_CALLBACK_RECEIVEEND( )  U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI0  )
#define U_CONFIG_SCI1_CALLBACK_RECEIVEEND( )  U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI1  )
#define U_CONFIG_SCI2_CALLBACK_RECEIVEEND( )  U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI2  )
#define U_CONFIG_SCI3_CALLBACK_RECEIVEEND( )  U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI3  )
#define U_CONFIG_SCI4_CALLBACK_RECEIVEEND( )  U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI4  )
#define U_CONFIG_SCI5_CALLBACK_RECEIVEEND( )  U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI5  )
#define U_CONFIG_SCI6_CALLBACK_RECEIVEEND( )  U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI6  )
#define U_CONFIG_SCI7_CALLBACK_RECEIVEEND( )  U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI7  )
#define U_CONFIG_SCI8_CALLBACK_RECEIVEEND( )  U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI8  )
#define U_CONFIG_SCI9_CALLBACK_RECEIVEEND( )  U_CONFIG_SCI_CALLBACK_RECEIVEEND(  SCI9  )
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
