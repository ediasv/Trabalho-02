#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trabalho2.h"
#include "wavfile.h"

void mudaGanho(double *dados, int n_amostras, double ganho); 
int contaSaturacoes(double *dados, int n_amostras); 
int hardClipping(double *dados, int n_amostras, double limite); 
void limitaSinal(double *dados, int n_amostras, int n_passos);
void geraOndaQuadrada(double *dados, int n_amostras, int taxa, double freq);

void mudaGanho(double *dados, int n_amostras, double ganho) {
  int i;
  // Para cada dado do vetor, multiplicar ele pelo ganho.
  for (i = 0; i < n_amostras; i++) {
    dados[i] = dados[i] * ganho;
  }
}

int contaSaturacoes(double *dados, int n_amostras) {
  int saturacoes, i;
  saturacoes = 0;
  // Pada cada dado do vetor, verificar se está além do limite. Em caso afirmativo, incrementa o número de saturações.
  for (i = 0; i < n_amostras; i++) {
    if (dados[i] > 1 || dados[i] < -1)
      saturacoes++;
  }
  return saturacoes;
}

int hardClipping(double *dados, int n_amostras, double limite) {
  int n_alterados, i;
  n_alterados = 0;
  // Para cada dado do vetor...
  for (i = 0; i < n_amostras; i++) {
    // Se o dado estiver acima do limite superior, "clipa".
    if (dados[i] > limite) {
      dados[i] = limite;
      n_alterados++;
    }
    // Se o dado estiver abaixo do limite inferior, "clipa".
    else if (dados[i] < -1 * limite) {
      dados[i] = -1 * limite;
      n_alterados++;
    }
  }
  return n_alterados;
}

void limitaSinal(double *dados, int n_amostras, int n_passos) {
  int i, j;
  float fator = 0;
  float incremento;
  for (i = 0; i < n_amostras; i++) {
    if (dados[i] > 1 || dados[i] < -1) {
      fator = 1 / dados[i];
      incremento = (1 - fator) / (n_passos + 1);
      dados[i] *= fator;
      fator += incremento;
      for (j = 1; j < n_passos; j++, fator += incremento) {
        if (i - j >= 0)
          dados[i - j] *= fator;
        if (i + j < n_amostras)
          dados[i + j] *= fator;
      }
    }
  }
}

void geraOndaQuadrada(double *dados, int n_amostras, int taxa, double freq)
{
  int i, sinal, n_ciclo;
  float meio_periodo;

  meio_periodo = taxa/(2*freq);
  sinal = 1;
  n_ciclo = 1;
  for (int i = 0; i < n_amostras; i++)
  {
    dados[i] = 1 * sinal;
    if (i == n_ciclo*meio_periodo)
    {
      sinal *= -1;
      n_ciclo++;
    }
  }
}
