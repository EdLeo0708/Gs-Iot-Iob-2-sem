# Gs-Iot-Iob-2-sem

**Integrantes do Grupo:**

Gustavo Bezerra Assumção - RM 553076

Jó Sales - RM 552679

Miguel Garcez de Carvalho - RM 553768

Vinicius Souza e Silva - RM 552781

Edson Leonardo - RM 553737

## O Problema Espacial Resolvido
Em colônias espaciais (Lua ou Marte), o ambiente habitável depende de sistemas de suporte de vida que devem funcionar perfeitamente. Falhas na pressão atmosférica (vazamentos) ou na blindagem contra radiação cósmica podem ser fatais em questão de segundos.
A latência de comunicação com a Terra (que pode levar minutos dependendo da posição de Marte) torna impossível depender de servidores terrestres para tomar decisões críticas.
Este projeto implementa um sistema **Edge Computing** que coleta dados dos sensores e realiza a inferência de Machine Learning (TinyML) *localmente* no microcontrolador (ESP32), decidindo instantaneamente se o ambiente está Seguro, em Alerta ou em estado Crítico, e disponibilizando esse status aos astronautas via um Webserver local.

## Alinhamento com a ODS 11 (Cidades e Comunidades Sustentáveis)
Embora focado no espaço, o desenvolvimento de habitats autossuficientes e ultrasseguros gera tecnologias que podem ser aplicadas diretamente na Terra:
- Monitoramento de ambientes confinados (minas subterrâneas, plataformas de petróleo).
- Sistemas de alerta rápido para vazamentos de gases em áreas industriais.
- Criação de ecovilas resilientes em ambientes extremos no nosso próprio planeta.

## Arquitetura da Solução
- **Simulador Wokwi:** Plataforma utilizada para montar e testar o circuito IoT virtualmente.
- **Sensores:**
  - Potenciômetro: Simula o sensor de pressão interna do habitat.
  - LDR: Simula o sensor de nível de radiação.
- **Microcontrolador:** ESP32, atuando como o cérebro (Edge Device) e servidor web (IoT).
- **TinyML:** As regras do modelo de Machine Learning treinado foram abstraídas em lógicas condicionais (C++) para economizar memória e contornar a limitação de bibliotecas complexas no simulador Wokwi gratuito.

## Como Executar
1. Acesse o [Wokwi]([https://wokwi.com/](https://wokwi.com/projects/465766194729111553)).
2. Crie um novo projeto "ESP32".
3. Adicione um Potenciômetro (pino 34), um LDR (pino 35) e opcionalmente 3 LEDs (pinos 12, 14 e 27).
4. Cole o código `guardiao_habitat.ino` no arquivo `sketch.ino`.
5. Inicie a simulação e abra o Serial Monitor. O IP do servidor web aparecerá no terminal.
6. Copie o IP ou o endereço fornecido e abra em uma nova aba do navegador para ver o painel de status em tempo real. Movimente o Potenciômetro e o LDR para ver a inteligência artificial mudando o status na página.
