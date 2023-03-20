

//======Variáveis globais=======
unsigned int semente,               //guarda valor para srand
             nivel = 3,            //nível atual
             flag[2] = {1 , 1},   //flag[x] == 1-> player não errou,flag[x] == 0-> player errou
             modo,               //modo de jogo, se modo for 0, sigleplayer, se for 1 multiplayer
             cont = 0,          //variável para contagem dos botões pressionados
             sequencia[5],     //guarda sequencia de leds para serem acesos
             i = 0,           //variável de controle geral de laços for
             fim = 0,        //indica o fim do jogo
             estouros = 0;  //conta os estouros do timer 1
             
char char_nivel[10];      //guarda o nível num vetor de char
             


bit vez;               //se for 0, vez do player 1, se for 1 vez do player 2
// ======Mapeamento de HARDWARE=======

#define led1 RD0_bit             //pino do led vermelho
#define led2 RD1_bit             //pino do led amarelo
#define led3 RD2_bit             //pino do led verde
#define led4 RD3_bit             //pino do led azul
#define jog1 RD4_bit             //pino onde está o led indicador da vez do jogador 1
#define jog2 RD5_bit             //pino onde está o led indicador da vez do jogador 2

#define but1 RB2_bit             //botão para led vermelho (led1)
#define but2 RB3_bit             //botão para led amarelo  (led2)
#define but3 RB4_bit             //botão para led azul     (led3)
#define but4 RB5_bit             //botão para led verde    (led4)

#define chave RB6_bit            //se chave fechada, singleplayer, se abertar, multiplayer(função players)


//======definições gerais=======
#define MAXN 4              //define o nível máximo

//Configura Pinos do LCD.
sbit LCD_RS at RD6_bit;
sbit LCD_EN at RD7_bit;
sbit LCD_D7 at RA0_bit;
sbit LCD_D6 at RA1_bit;
sbit LCD_D5 at RA2_bit;
sbit LCD_D4 at RA3_bit;
//Configura a direção dos pinos do LCD.
sbit LCD_RS_Direction at TRISD6_bit;
sbit LCD_EN_Direction at TRISD7_bit;
sbit LCD_D7_Direction at TRISA0_bit;
sbit LCD_D6_Direction at TRISA1_bit;
sbit LCD_D5_Direction at TRISA2_bit;
sbit LCD_D4_Direction at TRISA3_bit;

//======Funções usadas=======
#include "genius.h"         //inclui bibliotecas com funções

//======Função principal=======
void main() {

     setup();                      //configura microcontrolador
     Lcd_Init();                   //inicializa módulo LCD
     Lcd_Cmd(_LCD_CURSOR_OFF);     //desliga o cursor
     players();                    //seleciona modo de jogo;
     
     sementee();      //gera uma semente entre 0 e 255 para srand
     srand(semente);  //insere semente me srand

    for(i = 0; i<MAXN; i++){         //gera vetor com sequencia aleatoria

      sequencia[i] =  1 + rand()%4;  //gera numeros na faixa entre 1 e 4

    }

    while(nivel <= MAXN){ // enquanto o jogador não tiver zerado o último nível...

         InttoStr(nivel, char_nivel);    //converte o int nível para um string char_nivel
         
         Lcd_Cmd(_LCD_CLEAR);            //limpa display
         Lcd_Out(1, 7, "Nivel");         //mostra o nível
         Lcd_Out(2, 4, char_nivel);
         delay_ms(1500);                 //espera um pouco
         
         Lcd_Cmd(_LCD_CLEAR);            //limpa display
         Lcd_Out(1, 5, "Atencao");       //alerta o jogador da sequencia
         delay_ms(1500);                 //espera um pouco

        for(i = 0; i<nivel; i++){        //pisca leds da sequência nivel vezes

          switch(sequencia[i]){          //escolhe qual led vai piscar

             case 1: output1(); break;   //se o sequencia[i] for 1 pisca led 1
             case 2: output2(); break;   //se o sequencia[i] for 2 pisca led 2
             case 3: output3(); break;   //se o sequencia[i] for 3 pisca led 3
             case 4: output4(); break;   //se o sequencia[i] for 4 pisca led 4

          }
        }

        for(i = 0; i<= modo; i++){      // singleplayer execulta 1 vez, multiplayer execulta duas vezes

          led_jogadores();              //acende um dos leds dos jogadores
          lerbotao();                   //lê a resposta do jogador
          led_jogadores();              //apaga o led que foi aceso

          if(modo == 1){                //se o modo for multiplayer...

             vez = ~vez;                //passa a vez pro próximo jogador

          }

        }

        resultado();                   //se houve vitória de um jogador ou empate
        if(fim){

           break;                       //acaba o jogo

        }

     }
     
     if(nivel > MAXN){                 //se o/os jogador/es foi até o último nível...

        zerar();                       //pisca os leds numa sequência para indicar vitória

     }

}
