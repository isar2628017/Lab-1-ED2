//Universidad del Valle de Guatemala
//Maria Isabel Rivera De Leon
//Electrónica Digital 2
//Laboratorio 1



#include <Arduino.h>
#include <driver/gpio.h>

#include <stdio.h>
#include <stdint.h>

//LEDS
#define L1 GPIO_NUM_23
#define L2 GPIO_NUM_22
#define L3 GPIO_NUM_21
#define L4 GPIO_NUM_19

//Botones
#define BOD GPIO_NUM_33     //Incrementa
#define BOU GPIO_NUM_25     //Decrementa
#define BM  GPIO_NUM_26     //Modo


uint8_t contador=0;
int modo=0;

void mostrarNumero(uint8_t numero)  {
    gpio_set_level(L1, numero & 1);
    gpio_set_level(L2, (numero >> 1) & 1);
    gpio_set_level(L3, (numero >> 2) & 1);
    gpio_set_level(L4, (numero >> 3) & 1);
}


void setup() {
  //LED's
  gpio_set_direction(L1, GPIO_MODE_OUTPUT);
  gpio_set_direction(L2, GPIO_MODE_OUTPUT);
  gpio_set_direction(L3, GPIO_MODE_OUTPUT);
  gpio_set_direction(L4, GPIO_MODE_OUTPUT);

  //Botones
  gpio_set_direction(GPIO_NUM_33, GPIO_MODE_INPUT);
  gpio_set_direction(GPIO_NUM_25, GPIO_MODE_INPUT);
  gpio_set_direction(GPIO_NUM_26, GPIO_MODE_INPUT);


  //Pull down o up
  gpio_set_pull_mode(BOD, GPIO_FLOATING);          
  gpio_set_pull_mode(BOU, GPIO_FLOATING);          
  gpio_set_pull_mode(BM, GPIO_PULLDOWN_ONLY);     

  
  mostrarNumero(contador);

}

void loop() {

  //Modo
  if (gpio_get_level(BM) == 1) {
    if (modo == 0)  {
      modo = 1;
    }
    else  {
      modo = 0;
    }

    contador = 0;
    mostrarNumero(contador);
    delay(250);
  }

  if (modo == 0)  {
    conDecadas();
  }
  else  {
    conBinario();
  }
  
  
}

void conDecadas() {
    // Incrementa
    if (gpio_get_level(BOD) == 1) {
        contador++;
        if (contador > 9) {
          contador = 0;
        }
        mostrarNumero(contador);
        delay(200);
    }

    // Decrementa
    if (gpio_get_level(BOU) == 0) {
        if (contador == 0)  {
          contador = 9;
        }
        else  {
            contador--;
        }
        mostrarNumero(contador);
        delay(200);
    }
}

void conBinario()  {
    // Incrementa
    if (gpio_get_level(BOD) == 1)
    {
        contador++;
        if (contador > 15)  {
          contador = 0;
        }
        mostrarNumero(contador);
        delay(200);
    }

    // Decrementa
    if (gpio_get_level(BOU) == 0) {
        if (contador == 0)  {
          contador = 15;
        }
        else  {
            contador--;
        }
        mostrarNumero(contador);
        delay(200);
    }
}

