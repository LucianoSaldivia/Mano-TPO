#include <stdio.h>
#include <stdlib.h>

#define MILLONES                *1000000
#define MIL                     *1000
#define CCLK                    120 MILLONES
#define MI_TIPO_ERROR           100
#define ERROR_MAXIMO_ADMITIDO   1.0
#define CANT_VALORES_TABLA      72
#define CANT_VALORES_BAUDRATE   15

typedef struct{
    float BaudRate_Calculado;
    float Error_Porcentual;
    int BaudRate;
    int PCLK;
    int DLM;
    int DLL;
    char DivAddVal;
    char MulVal;
    char inutil1;       //  Para evitar warning: padding size of S_Config with bytes to alignment boundary
    char inutil2;       //  Para evitar warning: padding size of S_Config with bytes to alignment boundary
}S_Config;

void MostrarTodo( int BaudRate );
void Estimar_Valores( S_Config *Config_Final );
void Actualizar_BaudRate( S_Config *Config_Final );
void Actualizar_Error_Porcentual( S_Config *Config_Final );
char Index_DAV_MV_by_FR( float FR, S_Config *Config_Final );
char DAV_by_Index( char I );
char MV_by_Index( char I );

static float Valores_FR_Tabla[CANT_VALORES_TABLA] =
{ (float) 1.000, (float) 1.067, (float) 1.071, (float) 1.077, (float) 1.083,
  (float) 1.091, (float) 1.100, (float) 1.111, (float) 1.125, (float) 1.133,
  (float) 1.143, (float) 1.154, (float) 1.167, (float) 1.182, (float) 1.200,
  (float) 1.214, (float) 1.222, (float) 1.231, (float) 1.250, (float) 1.267,
  (float) 1.273, (float) 1.286, (float) 1.300, (float) 1.308, (float) 1.333,
  (float) 1.357, (float) 1.364, (float) 1.375, (float) 1.385, (float) 1.400,
  (float) 1.417, (float) 1.429, (float) 1.444, (float) 1.455, (float) 1.462,
  (float) 1.467, (float) 1.500, (float) 1.533, (float) 1.538, (float) 1.545,
  (float) 1.556, (float) 1.571, (float) 1.583, (float) 1.600, (float) 1.615,
  (float) 1.625, (float) 1.636, (float) 1.643, (float) 1.667, (float) 1.692,
  (float) 1.700, (float) 1.714, (float) 1.727, (float) 1.733, (float) 1.750,
  (float) 1.769, (float) 1.778, (float) 1.786, (float) 1.800, (float) 1.818,
  (float) 1.833, (float) 1.846, (float) 1.857, (float) 1.867, (float) 1.875,
  (float) 1.889, (float) 1.900, (float) 1.909, (float) 1.917, (float) 1.923,
  (float) 1.929, (float) 1.933};

static int Valores_BaudRate_A_Testear[CANT_VALORES_BAUDRATE] =
{ (int) 600, (int) 1200, (int) 2400, (int) 4800, (int) 9600,
  (int) 14400, (int) 19200, (int) 28800, (int) 38400, (int) 56000,
  (int) 57600, (int) 115200, (int) 128000, (int) 230400, (int) 256000};

int main( void ){

    int Index;

    printf( "\nPedido\tPCLK\t\tObtenido\tError %%\t\tDLM  \tDLL  DivAddVal  MulVal\n\n" );

    for( Index = 0 ; Index < CANT_VALORES_BAUDRATE ; Index++ ){
        MostrarTodo( Valores_BaudRate_A_Testear[ Index ] );
    }
}

void MostrarTodo( int BaudRate ){
    S_Config *Config;

    Config = (S_Config *) malloc( sizeof( S_Config ) );

    Config->BaudRate = BaudRate;
    Config->PCLK = CCLK;
    Config->BaudRate_Calculado = 0.0;
    Config->Error_Porcentual= 0.0;
    Config->DLM = 0;
    Config->DLL = 1;
    Config->DivAddVal = 1;
    Config->MulVal = 1;

    Estimar_Valores( Config );
    Actualizar_BaudRate( Config );
    Actualizar_Error_Porcentual( Config );

    printf( "\n%d", Config->BaudRate );
    printf( "\t%d", Config->PCLK );
    printf( "\t%f", (double) Config->BaudRate_Calculado );
    printf( "\t%f %%", (double) Config->Error_Porcentual );
    printf( "\t%d", Config->DLM );
    printf( "\t%d", Config->DLL );
    printf( "\t%d", Config->DivAddVal );
    printf( "\t%d", Config->MulVal );



    Config->BaudRate = BaudRate;
    Config->PCLK = CCLK / 2;
    Config->BaudRate_Calculado = 0.0;
    Config->Error_Porcentual= 0.0;
    Config->DLM = 0;
    Config->DLL = 1;
    Config->DivAddVal = 1;
    Config->MulVal = 1;

    Estimar_Valores( Config );
    Actualizar_BaudRate( Config );
    Actualizar_Error_Porcentual( Config );

    printf( "\n\t %d", Config->PCLK );
    printf( "\t%f", (double) Config->BaudRate_Calculado );
    printf( "\t%f %%", (double) Config->Error_Porcentual );
    printf( "\t%d", Config->DLM );
    printf( "\t%d", Config->DLL );
    printf( "\t%d", Config->DivAddVal );
    printf( "\t%d", Config->MulVal );




    Config->BaudRate = BaudRate;
    Config->PCLK = CCLK / 4;
    Config->BaudRate_Calculado = 0.0;
    Config->Error_Porcentual= 0.0;
    Config->DLM = 0;
    Config->DLL = 1;
    Config->DivAddVal = 1;
    Config->MulVal = 1;

    Estimar_Valores( Config );
    Actualizar_BaudRate( Config );
    Actualizar_Error_Porcentual( Config );

    printf( "\n\t %d", Config->PCLK );
    printf( "\t%f", (double) Config->BaudRate_Calculado );
    printf( "\t%f %%", (double) Config->Error_Porcentual );
    printf( "\t%d", Config->DLM );
    printf( "\t%d", Config->DLL );
    printf( "\t%d", Config->DivAddVal );
    printf( "\t%d", Config->MulVal );




    Config->BaudRate = BaudRate;
    Config->PCLK = CCLK / 8;
    Config->BaudRate_Calculado = 0.0;
    Config->Error_Porcentual= 0.0;
    Config->DLM = 0;
    Config->DLL = 1;
    Config->DivAddVal = 1;
    Config->MulVal = 1;

    Estimar_Valores( Config );
    Actualizar_BaudRate( Config );
    Actualizar_Error_Porcentual( Config );

    printf( "\n\t %d", Config->PCLK );
    printf( "\t%f", (double) Config->BaudRate_Calculado );
    printf( "\t%f %%", (double) Config->Error_Porcentual );
    printf( "\t%d", Config->DLM );
    printf( "\t%d", Config->DLL );
    printf( "\t%d", Config->DivAddVal );
    printf( "\t%d\n\n", Config->MulVal );
}

void Estimar_Valores( S_Config *Config_Final ){

    S_Config *C_Mejor, *C_Pos;
    float FR = 0.0;

    C_Mejor = (S_Config *) malloc( sizeof( S_Config ) );

    //  Inicializamos por seguridad
    (*C_Mejor) = (*Config_Final);
    C_Mejor->BaudRate_Calculado = 0.0;
    C_Mejor->Error_Porcentual= 0.0;
    C_Mejor->DLM = 0;
    C_Mejor->DLL = 1;
    C_Mejor->DivAddVal = 0;
    C_Mejor->MulVal = 1;

    //  Algoritmo
    C_Mejor->DLM = C_Mejor->PCLK / ( 16 * 256 * C_Mejor->BaudRate );    // Truco DLM
    C_Mejor->DLL = ( C_Mejor->PCLK / ( 16 * C_Mejor->BaudRate ) ) - 256 * C_Mejor->DLM; // Trunco DLL

    if( C_Mejor->DLM == 0 && C_Mejor->DLL == 0 ){   // Si ambos son 0, DLL = 1
        C_Mejor->DLL = 1;
        (*Config_Final) = (*C_Mejor);
        return;
    }
    Actualizar_BaudRate( C_Mejor );
    Actualizar_Error_Porcentual( C_Mejor );

    /*
    Ya tenemos una base (C_Mejor) con DLM y DLL, ahora queremos mas precisión usando DAV y MV
    Pasos según mi algoritmo:
     1º Calcular DLM con DLL = 0, DAV = 1 y MV = 0
     2º Calcular DLL con el DLM calculado en el 1º paso, y con DAV = 1, MV = 0
     3º Calcular DAV y MV con los últimos DLL y DLM obtenidos
     4º if( es la primera vez ) guardamos el error actual como MEJOR_ERROR, y guardamos nuestros valores actuales
        else if( nuestro error actual < MEJOR_ERROR ) sobreescribimos MEJOR_ERROR y guardamos nuestros valores actuales
     5º Volvemos al paso 3, haciendo DLL(nuevo) = DLL(anterior) - 1, siempre que ( DLL > 0 ) o ( DLL = 0  &&  DLM > 0 )
     6º Volvemos al paso 2, haciendo DLM(nuevo) = DLM(anterior) - 1, siempre que DLM >= 0

     7º En MEJOR_ERROR tenemos el Error más bajo posible habiendo probado con todos los DLM, DLL, DAV y MV más cercanos.
     Y en donde los guardamos, tenemos los valores que generan ese error

    */

    C_Pos = (S_Config *) malloc( sizeof( S_Config ) );
    (*C_Pos) = (*C_Mejor);

    if( C_Pos->DLM >= 1 && C_Pos->DLL == 0 ){   //
            C_Pos->DLM --;
            C_Pos->DLL = ( C_Pos->PCLK / ( 16 * C_Pos->BaudRate ) ) - 256 * C_Pos->DLM;
    }

    if( C_Pos->DLM == 0 ){
        while ( C_Pos->DLL > 0 ){
            FR = (float) 1.0 * C_Pos->PCLK / ( (float) 16.0 * ( C_Pos->DLM * 256 + C_Pos->DLL ) * C_Pos->BaudRate );

            Index_DAV_MV_by_FR( FR, C_Pos );    // También actualiza BR y Err %

            if( C_Pos->Error_Porcentual < C_Mejor->Error_Porcentual ){
                (*C_Mejor)= (*C_Pos);
            }

            C_Pos->DLL -- ;
        }

        (*Config_Final) = (*C_Mejor);
        Actualizar_BaudRate( Config_Final );
        Actualizar_Error_Porcentual( Config_Final );

        return;
    }

    else{
        while( C_Pos->DLM >= 0 ){

            C_Pos->DLL = ( C_Pos->PCLK / ( 16 * C_Pos->BaudRate ) ) - 256 * C_Pos->DLM;

            while ( C_Pos->DLL > 0 || ( C_Pos->DLL == 0 && C_Pos->DLM > 0 ) ){

                FR = (float) 1.0 * C_Pos->PCLK / ( (float) 16.0 * ( C_Pos->DLM * 256 + C_Pos->DLL ) * C_Pos->BaudRate );

                Index_DAV_MV_by_FR( FR, C_Pos );

                Actualizar_BaudRate( C_Pos );
                Actualizar_Error_Porcentual( C_Pos );

                if( C_Pos->Error_Porcentual < C_Mejor->Error_Porcentual ){
                    (*C_Mejor)= (*C_Pos);
                }

                C_Pos->DLL -- ;
            }

            C_Pos->DLM -- ;
        }

        (*Config_Final) = (*C_Mejor);
        Actualizar_BaudRate( Config_Final );
        Actualizar_Error_Porcentual( Config_Final );
        return;
    }
}

void Actualizar_BaudRate( S_Config *Config_Final ){
    float Aux1, Aux2;

    /*
    Fórmula para el BAUDRATE dada por la hoja de datos del LPC_17xx
                                        PCLK
    BaudRate = ------------------------------------------------------
                16 * ( DLM * 256 + DLL ) * ( 1 + DivAddVal / MulVal )
    */

    Aux1 = Config_Final->DLL + Config_Final->DLM * (float) 256.0;
    Aux2 = (float) 1.0 + ( ( (float) 1.0 * Config_Final->DivAddVal ) / ( (float) 1.0 * Config_Final->MulVal ) );

    Config_Final->BaudRate_Calculado = Config_Final->PCLK / ( 16 * Aux1 * Aux2 );
}

void Actualizar_Error_Porcentual( S_Config *Config_Final ){

    if( Config_Final->BaudRate > Config_Final->BaudRate_Calculado ){
        Config_Final->Error_Porcentual = 100 * ( ( Config_Final->BaudRate - Config_Final->BaudRate_Calculado ) / Config_Final->BaudRate );
    }else{
        Config_Final->Error_Porcentual = 100 * ( ( Config_Final->BaudRate_Calculado - Config_Final->BaudRate ) / Config_Final->BaudRate );
    }
}

char Index_DAV_MV_by_FR( float FR, S_Config *Config_Final ){

    S_Config *C_MAX, *C_MIN;
    int Index = 0;

    C_MAX = (S_Config *) malloc( sizeof( S_Config ) );  //  Inicializo ambas configuraciones
    C_MIN = (S_Config *) malloc( sizeof( S_Config ) );

    (*C_MAX) = (*Config_Final);
    (*C_MIN) = (*Config_Final);

    for( Index = 0; Index < CANT_VALORES_TABLA && FR > Valores_FR_Tabla[Index]; Index ++);

    FR = Valores_FR_Tabla[ Index ];       // MAX
    C_MAX->DivAddVal = DAV_by_Index( (char) Index );
    C_MAX->MulVal = MV_by_Index( (char) Index );
    Actualizar_BaudRate( C_MAX );
    Actualizar_Error_Porcentual( C_MAX );

    FR = Valores_FR_Tabla[ Index - 1 ];   // MIN
    C_MIN->DivAddVal = DAV_by_Index( (char) Index - 1 );
    C_MIN->MulVal = MV_by_Index( (char) Index - 1 );
    Actualizar_BaudRate( C_MIN );
    Actualizar_Error_Porcentual( C_MIN );


    if( C_MIN->Error_Porcentual < C_MAX->Error_Porcentual ){
        (*Config_Final) = (*C_MIN);
        return (char) Index - 1;
    }
    else{
        (*Config_Final) = (*C_MAX);
        return (char) Index;
    }
}

char DAV_by_Index( char I ){

    if( I == 0 ) return 0;
    if( I <= 9  || I == 10 || I == 12 || I == 14 || I == 18 || I == 24 || I == 36 ) return 1;
    if( I == 9  || I == 11 || I == 13 || I == 16 || I == 21 || I == 29 || I == 48 ) return 2;
    if( I == 15 || I == 17 || I == 20 || I == 22 || I == 27 || I == 31 || I == 43 || I == 54 ) return 3;
    if( I == 19 || I == 23 || I == 26 || I == 32 || I == 41 || I == 58 ) return 4;
    if( I == 25 || I == 28 || I == 30 || I == 33 || I == 40 || I == 45 || I == 51 || I == 60 ) return 5;
    if( I == 34 || I == 39 || I == 62 ) return 6;
    if( I == 35 || I == 38 || I == 42 || I == 46 || I == 50 || I == 56 || I == 64 ) return 7;
    if( I == 37 || I == 44 || I == 52 || I == 65 ) return 8;
    if( I == 47 || I == 49 || I == 59 || I == 66 ) return 9;
    if( I == 55 || I == 67 ) return 10;
    if( I == 53 || I == 57 || I == 61 || I == 68 ) return 11;
    if( I == 69 ) return 12;
    if( I == 63 || I == 70 ) return 13;
    if( I == 71 ) return 14;
    return MI_TIPO_ERROR;
}

char MV_by_Index( char I ){
    if( I == 0 ) return 1;
    if( I == 1  || I == 9  || I == 19 || I == 35 || I == 37 || I == 67 || I == 53 || I == 63 || I == 71 ) return 15;
    if( I == 2  || I == 15 || I == 25 || I == 47 || I == 57 || I == 70 ) return 14;
    if( I == 3  || I == 11 || I == 17 || I == 23 || I == 28 || I == 34 || I == 38 || I == 44 || I == 49 || I == 55 || I == 61 || I == 69 ) return 13;
    if( I == 4  || I == 30 || I == 42 || I == 68 ) return 12;
    if( I == 5  || I == 13 || I == 20 || I == 26 || I == 33 || I == 39 || I == 46 || I == 52 || I == 59 || I == 66 ) return 11;
    if( I == 6  || I == 22 || I == 50 || I == 66 ) return 10;
    if( I == 7  || I == 16 || I == 32 || I == 40 || I == 56 || I == 65 ) return 9;
    if( I == 8  || I == 27 || I == 45 || I == 64 ) return 8;
    if( I == 10 || I == 21 || I == 31 || I == 41 || I == 51 || I == 62 ) return 7;
    if( I == 12 || I == 60 ) return 6;
    if( I == 14 || I == 29 || I == 43 || I == 58 ) return 5;
    if( I == 18 || I == 54 ) return 4;
    if( I == 24 || I == 48 ) return 3;
    if( I == 36 ) return 2;
    return MI_TIPO_ERROR;
}






