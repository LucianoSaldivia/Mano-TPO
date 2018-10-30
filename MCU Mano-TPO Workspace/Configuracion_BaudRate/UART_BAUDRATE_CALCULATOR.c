#include <stdio.h>


#define BAUDRATE    256000





#define MILLONES    *1000000
#define MIL         *1000
#define ERROR       100

void Estimar_Valores( int PCLK, int BaudRate, int *DLM, int *DLL, int *DivAddVal, int *MulVal );
float Calcular_BaudRate( int PCLK, int DLM, int DLL, int DivAddVal, int MulVal );
float Calcular_Error_Porcentual( int BaudRate, float Actual_BaudRate );
char TABLA_DAV( float FR_est_F );
char TABLA_MV( float FR_est_F, char DivAddValue );

int main()
{
    int BaudRate = BAUDRATE, PCLK;
    int DLM = 1, DLL = 0, DivAddVal = 0, MulVal = 1;
    float Error_Porcentual, Actual_BaudRate;

    PCLK = 12 MILLONES;
    Estimar_Valores( PCLK, BaudRate, &DLM, &DLL, &DivAddVal, &MulVal );
    Actual_BaudRate = Calcular_BaudRate( PCLK, DLM, DLL, DivAddVal, MulVal );
    Error_Porcentual = Calcular_Error_Porcentual( BaudRate, Actual_BaudRate );

    printf( "\n\n\n PCLK = %d", PCLK );
    printf( "\n BaudRate pedido = %d", BaudRate );
    printf( "\n BaudRate Conseguido = %f", (double) Actual_BaudRate );
    printf( "\n Error Porcentual = %f %%", (double) Error_Porcentual );
    printf( "\n DLM = %d", DLM );
    printf( "\n DLL = %d", DLL );
    printf( "\n DivAddVal = %d", DivAddVal );
    printf( "\n MulVal = %d", MulVal );



    PCLK = 6 MILLONES;
    Estimar_Valores( PCLK, BaudRate, &DLM, &DLL, &DivAddVal, &MulVal );
    Actual_BaudRate = Calcular_BaudRate( PCLK, DLM, DLL, DivAddVal, MulVal );
    Error_Porcentual = Calcular_Error_Porcentual( BaudRate, Actual_BaudRate );

    printf( "\n\n\n PCLK = %d", PCLK );
    printf( "\n BaudRate pedido = %d", BaudRate );
    printf( "\n BaudRate Conseguido = %f", (double) Actual_BaudRate );
    printf( "\n Error Porcentual = %f", (double) Error_Porcentual );
    printf( "\n DLM = %d", DLM );
    printf( "\n DLL = %d", DLL );
    printf( "\n DivAddVal = %d", DivAddVal );
    printf( "\n MulVal = %d", MulVal );



    PCLK = 3 MILLONES;
    Estimar_Valores( PCLK, BaudRate, &DLM, &DLL, &DivAddVal, &MulVal );
    Actual_BaudRate = Calcular_BaudRate( PCLK, DLM, DLL, DivAddVal, MulVal );
    Error_Porcentual = Calcular_Error_Porcentual( BaudRate, Actual_BaudRate );

    printf( "\n\n\n PCLK = %d", PCLK );
    printf( "\n BaudRate pedido = %d", BaudRate );
    printf( "\n BaudRate Conseguido = %f", (double) Actual_BaudRate );
    printf( "\n Error Porcentual = %f", (double) Error_Porcentual );
    printf( "\n DLM = %d", DLM );
    printf( "\n DLL = %d", DLL );
    printf( "\n DivAddVal = %d", DivAddVal );
    printf( "\n MulVal = %d", MulVal );



    PCLK = 1500 MIL;
    Estimar_Valores( PCLK, BaudRate, &DLM, &DLL, &DivAddVal, &MulVal );
    Actual_BaudRate = Calcular_BaudRate( PCLK, DLM, DLL, DivAddVal, MulVal );

    Error_Porcentual = Calcular_Error_Porcentual( BaudRate, Actual_BaudRate );

    printf( "\n\n\n PCLK = %d", PCLK );
    printf( "\n BaudRate pedido = %d", BaudRate );
    printf( "\n BaudRate Conseguido = %f", (double) Actual_BaudRate );
    printf( "\n Error Porcentual = %f", (double) Error_Porcentual );
    printf( "\n DLM = %d", DLM );
    printf( "\n DLL = %d", DLL );
    printf( "\n DivAddVal = %d", DivAddVal );
    printf( "\n MulVal = %d", MulVal );

    return 0;
}
/*                                                                                                                                                                                                  */
void Estimar_Valores( int PCLK, int BaudRate, int *DLM, int *DLL, int *DivAddVal, int *MulVal ){
    float FR_est = 0; // Fraccion estimada

    (*DivAddVal) = 0;
    (*MulVal) = 1;
    (*DLM) = PCLK / ( 16 * 256 * BaudRate );
    (*DLL) = ( PCLK / ( 16 * BaudRate ) ) - 256 * (*DLM);

    if( Calcular_Error_Porcentual( BaudRate, Calcular_BaudRate( PCLK, (*DLM), (*DLL), (*DivAddVal), (*MulVal) ) )  > 1.5 ){
        FR_est = (float) 1.0 * PCLK / ( (float) 16.0 * ( (*DLM) * 256 + (*DLL) ) * BaudRate );

        (*DivAddVal) = (int) TABLA_DAV(FR_est);
        (*MulVal) = (int) TABLA_MV(FR_est, (char) (*DivAddVal) );
    }
    else return;

}

float Calcular_BaudRate( int PCLK, int DLM, int DLL, int DivAddVal, int MulVal ){
    float BaudRateCalculado;
    float Aux1, Aux2;

    /*
    Fórmula para el BAUDRATE dada por la hoja de datos del LPC_17xx
                                        PCLK
    BaudRate = ------------------------------------------------------
                16 * ( DLM * 256 + DLL ) * ( 1 + DivAddVal / MulVal )
    */

    Aux1 = DLL + DLM * (float) 256.0;
    Aux2 = (float) 1.0 + ( ( (float) 1.0 * DivAddVal ) / ( (float) 1.0 * MulVal ) );

    /*printf( "\n\n EN LA FUNCION" );
    printf( "\n\t\t Aux1 = %f", (double) Aux1 );
    printf( "\n\t\t Aux2 = %f", (double) Aux2 );*/

    BaudRateCalculado = PCLK / ( 16 * Aux1 * Aux2 );

    /*printf( "\n\t DLM = %d", DLM );
    printf( "\n\t DLL = %d", DLL );
    printf( "\n\t DivAddVal = %d", DivAddVal );
    printf( "\n\t MulVal = %d \n\n\n", MulVal );*/

    return BaudRateCalculado;
}

float Calcular_Error_Porcentual( int BaudRate, float Actual_BaudRate ){

    float Error_Porcentual;

    if( Actual_BaudRate > BaudRate ){
        Error_Porcentual = 100 * ( ( Actual_BaudRate - BaudRate ) / BaudRate );
    }else{
        Error_Porcentual = 100 * ( ( BaudRate - Actual_BaudRate ) / BaudRate );
    }

    return Error_Porcentual;
}

char TABLA_DAV( float FR_est_F ){
    if( FR_est_F >= (float) 1.000 && FR_est_F < (float) 1.0335 ){               // 0/1
        return 0;
    }
    if( ( FR_est_F >= (float) 1.0335 && FR_est_F < (float) 1.129 ) ||           // [ 1/15 ; 1/8 ]
            ( FR_est_F >= (float) 1.138 && FR_est_F < (float) 1.1485 ) ||       // 1/7
            ( FR_est_F >= (float) 1.1605 && FR_est_F < (float) 1.1745 ) ||      // 1/6
            ( FR_est_F >= (float) 1.191 && FR_est_F < (float) 1.207 ) ||        // 1/5
            ( FR_est_F >= (float) 1.2405 && FR_est_F < (float) 1.2585 ) ||      // 1/4
            ( FR_est_F >= (float) 1.3205 && FR_est_F < (float) 1.345 ) ||       // 1/3
            ( FR_est_F >= (float) 1.4835 && FR_est_F < (float) 1.5165 ) ){      // 1/2
        return 1;
    }
    if( ( FR_est_F >= (float) 1.129 && FR_est_F < (float) 1.138 ) ||            // 2/15
            ( FR_est_F >= (float) 1.1485 && FR_est_F < (float) 1.1605 ) ||      // 2/13
            ( FR_est_F >= (float) 1.1745 && FR_est_F < (float) 1.191 ) ||       // 2/11
            ( FR_est_F >= (float) 1.218 && FR_est_F < (float) 1.2265 ) ||       // 2/9
            ( FR_est_F >= (float) 1.2795 && FR_est_F < (float) 1.293 ) ||       // 2/7
            ( FR_est_F >= (float) 1.3925 && FR_est_F < (float) 1.4085 ) ||      // 2/5
            ( FR_est_F >= (float) 1.655 && FR_est_F < (float) 1.6795 ) ){       // 2/3
        return 2;
    }
    if( ( FR_est_F >= (float) 1.207 && FR_est_F < (float) 1.218 ) ||            // 3/14
            ( FR_est_F >= (float) 1.2265 && FR_est_F < (float)  1.2405 ) ||     // 3/13
            ( FR_est_F >= (float) 1.27 && FR_est_F < (float) 1.2795 ) ||        // 3/11
            ( FR_est_F >= (float) 1.293 && FR_est_F < (float) 1.304 ) ||        // 3/10
            ( FR_est_F >= (float) 1.3695 && FR_est_F < (float) 1.38 ) ||        // 3/8
            ( FR_est_F >= (float) 1.423 && FR_est_F < (float) 1.4365 ) ||       // 3/7
            ( FR_est_F >= (float) 1.5915 && FR_est_F < (float) 1.6075 ) ||      // 3/5
            ( FR_est_F >= (float) 1.7415 && FR_est_F < (float) 1.7595 ) ){      // 3/4
        return 3;
    }
    if( ( FR_est_F >= (float) 1.2585 && FR_est_F < (float) 1.27 ) ||            // 4/15
            ( FR_est_F >= (float) 1.304 && FR_est_F < (float)  1.3205 ) ||      // 4/13
            ( FR_est_F >= (float) 1.3605 && FR_est_F < (float) 1.3695 ) ||      // 4/11
            ( FR_est_F >= (float) 1.4365 && FR_est_F < (float) 1.4495 ) ||      // 4/9
            ( FR_est_F >= (float) 1.5635 && FR_est_F < (float) 1.5545 ) ||      // 4/7
            ( FR_est_F >= (float) 1.793 && FR_est_F < (float) 1.809 ) ){        // 4/5
        return 4;
    }
    if( ( FR_est_F >= (float) 1.345 && FR_est_F < (float) 1.3605 ) ||           // 5/14
            ( FR_est_F >= (float) 1.38 && FR_est_F < (float)  1.3205 ) ||       // 5/13
            ( FR_est_F >= (float) 1.4085 && FR_est_F < (float) 1.423 ) ||       // 5/12
            ( FR_est_F >= (float) 1.4495 && FR_est_F < (float) 1.4585 ) ||      // 5/11
            ( FR_est_F >= (float) 1.5505 && FR_est_F < (float) 1.5635 ) ||      // 5/9
            ( FR_est_F >= (float) 1.62 && FR_est_F < (float) 1.6305 ) ||        // 5/8
            ( FR_est_F >= (float) 1.707 && FR_est_F < (float) 1.7205 ) ||       // 5/7
            ( FR_est_F >= (float) 1.8255 && FR_est_F < (float) 1.8395 ) ){      // 5/6
        return 5;
    }
    if( ( FR_est_F >= (float) 1.4585 && FR_est_F < (float) 1.4645 ) ||          // 6/13
            ( FR_est_F >= (float) 1.5415 && FR_est_F < (float) 1.5505 ) ||      // 6/11
            ( FR_est_F >= (float) 1.8515 && FR_est_F < (float) 1.862 ) ){       // 6/7
        return 6;
    }
    if( ( FR_est_F >= (float) 1.4645 && FR_est_F < (float) 1.5 ) ||             // 7/15
            ( FR_est_F >= (float) 1.5355 && FR_est_F < (float)  1.5415 ) ||     // 7/13
            ( FR_est_F >= (float) 1.5545 && FR_est_F < (float) 1.5915 ) ||      // 7/12
            ( FR_est_F >= (float) 1.6305 && FR_est_F < (float) 1.6395 ) ||      // 7/11
            ( FR_est_F >= (float) 1.696 && FR_est_F < (float) 1.707 ) ||        // 7/10
            ( FR_est_F >= (float) 1.7735 && FR_est_F < (float) 1.782 ) ||       // 7/9
            ( FR_est_F >= (float) 1.871 && FR_est_F < (float) 1.882 ) ){        // 7/8
        return 7;
    }
    if( ( FR_est_F >= (float) 1.5165 && FR_est_F < (float) 1.5355 ) ||          // 8/15
            ( FR_est_F >= (float) 1.6075 && FR_est_F < (float)  1.62 ) ||       // 8/13
            ( FR_est_F >= (float) 1.7205 && FR_est_F < (float) 1.73 ) ||        // 8/11
            ( FR_est_F >= (float) 1.882 && FR_est_F < (float) 1.8945 ) ){       // 8/9
        return 8;
    }
    if( ( FR_est_F >= (float) 1.6395 && FR_est_F < (float) 1.655 ) ||           // 9/14
            ( FR_est_F >= (float) 1.6795 && FR_est_F < (float)  1.696 ) ||      // 9/13
            ( FR_est_F >= (float) 1.809 && FR_est_F < (float) 1.8255 ) ||       // 9/11
            ( FR_est_F >= (float) 1.8945 && FR_est_F < (float) 1.9045 ) ){      // 9/10
        return 9;
    }
    if( ( FR_est_F >= (float) 1.7595 && FR_est_F < (float) 1.7735 ) ||          // 10/13
            ( FR_est_F >= (float) 1.9045 && FR_est_F < (float) 1.913 ) ){       // 10/11
        return 10;
     }
    if( ( FR_est_F >= (float) 1.73 && FR_est_F < (float) 1.7415 ) ||            // 11/15
            ( FR_est_F >= (float) 1.782 && FR_est_F < (float)  1.793 ) ||       // 11/14
            ( FR_est_F >= (float) 1.8395 && FR_est_F < (float) 1.8515 ) ||      // 11/13
            ( FR_est_F >= (float) 1.913 && FR_est_F < (float) 1.92 ) ){         // 11/12
        return 11;
    }
    if( ( FR_est_F >= (float) 1.92 && FR_est_F < (float) 1.926 )  ){            // 12/13
        return 12;
    }
    if( ( FR_est_F >= (float) 1.862 && FR_est_F < (float) 1.871 ) ||            // 13/15
            ( FR_est_F >= (float) 1.926 && FR_est_F < (float) 1.931 ) ){        // 13/14
        return 13;
    }
    if( ( FR_est_F >= (float) 1.931 && FR_est_F <= (float) 1.934 ) ){           // 14/15
        return 14;
    }
    return ERROR;
}


char TABLA_MV( float FR_est_F, char DivAddValue ){
    switch( DivAddValue ){
        case 0:
            return 1;

        case 1:
            if( FR_est_F >= (float) 1.0335 && FR_est_F < (float) 1.069 )    return 15;
            if( FR_est_F >= (float) 1.069 && FR_est_F < (float) 1.074 )     return 14;
            if( FR_est_F >= (float) 1.074 && FR_est_F < (float) 1.08 )      return 13;
            if( FR_est_F >= (float) 1.08 && FR_est_F < (float) 1.087 )      return 12;
            if( FR_est_F >= (float) 1.087 && FR_est_F < (float) 1.0955 )    return 11;
            if( FR_est_F >= (float) 1.0955 && FR_est_F < (float) 1.1055 )   return 10;
            if( FR_est_F >= (float) 1.1055 && FR_est_F < (float) 1.118 )    return 9;
            if( FR_est_F >= (float) 1.118 && FR_est_F < (float) 1.129 )     return 8;
            if( FR_est_F >= (float) 1.138 && FR_est_F < (float) 1.1485 )    return 7;
            if( FR_est_F >= (float) 1.1605 && FR_est_F < (float) 1.1745 )   return 6;
            if( FR_est_F >= (float) 1.191 && FR_est_F < (float) 1.207 )     return 5;
            if( FR_est_F >= (float) 1.2405 && FR_est_F < (float) 1.2585 )   return 4;
            if( FR_est_F >= (float) 1.3205 && FR_est_F < (float) 1.345 )    return 3;
            if( FR_est_F >= (float) 1.4835 && FR_est_F < (float) 1.5165 )   return 2;

            break;

        case 2:
            if ( FR_est_F >= (float) 1.129 && FR_est_F < (float) 1.138 )    return 15;
            if ( FR_est_F >= (float) 1.1485 && FR_est_F < (float) 1.1605 )  return 13;
            if ( FR_est_F >= (float) 1.1745 && FR_est_F < (float) 1.191 )   return 11;
            if ( FR_est_F >= (float) 1.218 && FR_est_F < (float) 1.2265 )   return 9;
            if ( FR_est_F >= (float) 1.2795 && FR_est_F < (float) 1.293 )   return 7;
            if ( FR_est_F >= (float) 1.3925 && FR_est_F < (float) 1.4085 )  return 5;
            if ( FR_est_F >= (float) 1.655 && FR_est_F < (float) 1.6795 )   return 3;
            break;

        case 3:
            if ( FR_est_F >= (float) 1.207 && FR_est_F < (float) 1.218 )    return 14;
            if ( FR_est_F >= (float) 1.2265 && FR_est_F < (float)  1.2405 ) return 13;
            if ( FR_est_F >= (float) 1.27 && FR_est_F < (float) 1.2795 )    return 11;
            if ( FR_est_F >= (float) 1.293 && FR_est_F < (float) 1.304 )    return 10;
            if ( FR_est_F >= (float) 1.3695 && FR_est_F < (float) 1.38 )    return 8;
            if ( FR_est_F >= (float) 1.423 && FR_est_F < (float) 1.4365 )   return 7;
            if ( FR_est_F >= (float) 1.5915 && FR_est_F < (float) 1.6075 )  return 5;
            if ( FR_est_F >= (float) 1.7415 && FR_est_F < (float) 1.7595 )  return 4;
            break;

        case 4:
            if ( FR_est_F >= (float) 1.2585 && FR_est_F < (float) 1.27 )    return 15;
            if ( FR_est_F >= (float) 1.304 && FR_est_F < (float)  1.3205 )  return 13;
            if ( FR_est_F >= (float) 1.3605 && FR_est_F < (float) 1.3695 )  return 11;
            if ( FR_est_F >= (float) 1.4365 && FR_est_F < (float) 1.4495 )  return 9;
            if ( FR_est_F >= (float) 1.5635 && FR_est_F < (float) 1.5545 )  return 7;
            if ( FR_est_F >= (float) 1.793 && FR_est_F < (float) 1.809 )    return 5;
            break;

        case 5:
            if ( FR_est_F >= (float) 1.345 && FR_est_F < (float) 1.3605 )   return 14;
            if ( FR_est_F >= (float) 1.38 && FR_est_F < (float)  1.3205 )   return 13;
            if ( FR_est_F >= (float) 1.4085 && FR_est_F < (float) 1.423 )   return 2;
            if ( FR_est_F >= (float) 1.4495 && FR_est_F < (float) 1.4585 )  return 11;
            if ( FR_est_F >= (float) 1.5505 && FR_est_F < (float) 1.5635 )  return 9;
            if ( FR_est_F >= (float) 1.62 && FR_est_F < (float) 1.6305 )    return 8;
            if ( FR_est_F >= (float) 1.707 && FR_est_F < (float) 1.7205 )   return 7;
            if ( FR_est_F >= (float) 1.8255 && FR_est_F < (float) 1.8395 )  return 6;
            break;

        case 6:
            if ( FR_est_F >= (float) 1.4585 && FR_est_F < (float) 1.4645 )  return 13;
            if ( FR_est_F >= (float) 1.5415 && FR_est_F < (float) 1.5505 )  return 11;
            if ( FR_est_F >= (float) 1.8515 && FR_est_F < (float) 1.862 )   return 7;
            break;

        case 7:
            if ( FR_est_F >= (float) 1.4645 && FR_est_F < (float) 1.5 )     return 15;
            if ( FR_est_F >= (float) 1.5355 && FR_est_F < (float)  1.5415 ) return 13;
            if ( FR_est_F >= (float) 1.5545 && FR_est_F < (float) 1.5915 )  return 12;
            if ( FR_est_F >= (float) 1.6305 && FR_est_F < (float) 1.6395 )  return 11;
            if ( FR_est_F >= (float) 1.696 && FR_est_F < (float) 1.707 )    return 10;
            if ( FR_est_F >= (float) 1.7735 && FR_est_F < (float) 1.782 )   return 9;
            if ( FR_est_F >= (float) 1.871 && FR_est_F < (float) 1.882 )    return 8;
            break;

        case 8:
            if ( FR_est_F >= (float) 1.5165 && FR_est_F < (float) 1.5355 )  return 15;
            if ( FR_est_F >= (float) 1.6075 && FR_est_F < (float)  1.62 )   return 13;
            if ( FR_est_F >= (float) 1.7205 && FR_est_F < (float) 1.73 )    return 11;
            if ( FR_est_F >= (float) 1.882 && FR_est_F < (float) 1.8945 )   return 9;
            break;

        case 9:
            if ( FR_est_F >= (float) 1.6395 && FR_est_F < (float) 1.655 )   return 14;
            if ( FR_est_F >= (float) 1.6795 && FR_est_F < (float)  1.696 )  return 13;
            if ( FR_est_F >= (float) 1.809 && FR_est_F < (float) 1.8255 )   return 11;
            if ( FR_est_F >= (float) 1.8945 && FR_est_F < (float) 1.9045 )  return 10;
            break;

        case 10:
            if ( FR_est_F >= (float) 1.7595 && FR_est_F < (float) 1.7735 )  return 13;
            if ( FR_est_F >= (float) 1.9045 && FR_est_F < (float) 1.913 )   return 11;
            break;

        case 11:
            if ( FR_est_F >= (float) 1.73 && FR_est_F < (float) 1.7415 )    return 15;
            if ( FR_est_F >= (float) 1.782 && FR_est_F < (float)  1.793 )   return 14;
            if ( FR_est_F >= (float) 1.8395 && FR_est_F < (float) 1.8515 )  return 13;
            if ( FR_est_F >= (float) 1.913 && FR_est_F < (float) 1.92 )     return 12;
            break;

        case 12:
            return 13;

        case 13:
            if ( FR_est_F >= (float) 1.862 && FR_est_F < (float) 1.871 )    return 15;
            if ( FR_est_F >= (float) 1.926 && FR_est_F < (float) 1.931 )    return 14;
            break;

        case 14:
            if ( FR_est_F >= (float) 1.931 && FR_est_F <= (float) 1.934 ) return 15;
            break;
        default:
            return ERROR;
    }
    return ERROR;
}








