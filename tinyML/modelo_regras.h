/*
 * Este arquivo substitui a biblioteca pesada gerada pelo Edge Impulse.
 * Em vez de incluir um arquivo .zip grande contendo o motor TensorFlow Lite Micro,
 * utilizamos as regras extraídas do Classificador de Árvore de Decisão gerado no Edge Impulse.
 * 
 * Regras geradas pelo modelo treinado:
 * 1. SE pressao < 1200 OU radiacao > 2800 -> ESTADO CRÍTICO
 * 2. SE (pressao >= 1200 E pressao < 2000) OU (radiacao > 1500 E radiacao <= 2800) -> ESTADO DE ALERTA
 * 3. CASO CONTRÁRIO -> ESTADO SEGURO
 * 
 * Motivação: O simulador Wokwi (versão gratuita) possui limitações no upload de bibliotecas externas complexas e grandes.
 * Esta abordagem de "Hardcoded ML" prova o conceito de Edge Computing com recursos restritos.
 */
