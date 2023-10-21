#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trabalho2.h"
#include "wavfile.h"

void mudaGanho(double *dados, int n_amostras, double ganho) {
  int i;
  for (i = 0; i < n_amostras; i++) {
    dados[i] = dados[i] * ganho;
  }
}

int contaSaturacoes(double *dados, int n_amostras) {
  int saturacoes = 0;
  for (int i = 0; i < n_amostras; i++) {
    if (dados[i] > 1 || dados[i] < -1)
      saturacoes++;
  }
  return saturacoes;
}

int hardClipping(double *dados, int n_amostras, double limite) {
  int n_alterados = 0;
  for (int i = 0; i < n_amostras; i++) {
    if (dados[i] > limite) {
      dados[i] = limite;
      n_alterados++;
    }
    else if (dados[i] < -1 * limite) {
      dados[i] = -1 * limite;
      n_alterados++;
    }
  }
  return n_alterados;
}

void limitaSinal(double *dados, int n_amostras, int n_passos);

void geraOndaQuadrada(double *dados, int n_amostras, int taxa, double freq);