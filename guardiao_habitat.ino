#include <WiFi.h>
#include <WebServer.h>

// Configurações da rede Wi-Fi simulada do Wokwi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Inicialização do Servidor Web na porta 80
WebServer server(80);

// Pinos dos Sensores
const int PIN_PRESSAO = 34; // Potenciômetro
const int PIN_RADIACAO = 35; // LDR

// Pinos de Atuação Visual (Opcional - LEDs de Status no Wokwi)
const int LED_SEGURO = 12;
const int LED_ALERTA = 14;
const int LED_CRITICO = 27;

// Variáveis Globais
int valorPressao = 0;
int valorRadiacao = 0;
String statusClassificacao = "Inicializando...";

// Função contendo as regras extraídas da árvore de decisão do TinyML
void executarInferenciaTinyML(int pressao, int radiacao) {
  // Tradução exata das fronteiras de decisão calculadas no Edge Impulse
  if (pressao < 1200 || radiacao > 2800) {
    statusClassificacao = "CRÍTICO";
    digitalWrite(LED_SEGURO, LOW);
    digitalWrite(LED_ALERTA, LOW);
    digitalWrite(LED_CRITICO, HIGH); // Alarme ativo
  } 
  else if ((pressao >= 1200 && pressao < 2000) || (radiacao > 1500 && radiacao <= 2800)) {
    statusClassificacao = "EM ALERTA";
    digitalWrite(LED_SEGURO, LOW);
    digitalWrite(LED_ALERTA, HIGH);
    digitalWrite(LED_CRITICO, LOW);
  } 
  else {
    statusClassificacao = "SEGURO";
    digitalWrite(LED_SEGURO, HIGH);
    digitalWrite(LED_ALERTA, LOW);
    digitalWrite(LED_CRITICO, LOW);
  }
}

// Handler da Página Web (com HTML e CSS)
void handleRoot() {
  String corStatus = "#10b981"; // Verde para Seguro
  if (statusClassificacao == "EM ALERTA") corStatus = "#f59e0b"; // Amarelo
  if (statusClassificacao == "CRÍTICO") corStatus = "#ef4444"; // Vermelho

  String html = "<!DOCTYPE html><html lang='pt-BR'><head>";
  html += "<meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>Space Connect - Guardiao de Habitat</title>";
  html += "<style>";
  html += "body { font-family: 'Segoe UI', Arial, sans-serif; background-color: #0f172a; color: #f8fafc; margin: 0; padding: 20px; display: flex; justify-content: center; align-items: center; min-height: 100vh; }";
  html += ".container { background-color: #1e293b; padding: 30px; border-radius: 12px; box-shadow: 0 10px 15px -3px rgba(0,0,0,0.5); width: 100%; max-width: 450px; text-align: center; border: 1px solid #334155; }";
  html += "h1 { font-size: 20px; margin-bottom: 5px; text-transform: uppercase; color: #3b82f6; letter-spacing: 1px; }";
  html += ".subtitle { font-size: 12px; color: #94a3b8; margin-bottom: 25px; }";
  html += ".status-box { background-color: " + corStatus + "; color: #ffffff; padding: 15px; border-radius: 8px; font-size: 24px; font-weight: bold; margin-bottom: 25px; letter-spacing: 1px; box-shadow: 0 4px 6px -1px rgba(0,0,0,0.2); }";
  html += ".data-item { display: flex; justify-content: space-between; padding: 12px; background-color: #0f172a; margin-bottom: 10px; border-radius: 6px; font-size: 14px; border: 1px solid #334155; }";
  html += ".data-label { color: #94a3b8; }";
  html += ".data-value { font-weight: bold; color: #e2e8f0; }";
  html += ".footer { font-size: 10px; color: #64748b; margin-top: 25px; }";
  html += "</style>";
  html += "<script>setInterval(function(){ window.location.reload(); }, 2000);</script>"; // Auto-refresh a cada 2s
  html += "</head><body>";
  html += "<div class='container'>";
  html += "<h1>Guardi&atilde;o de Habitat</h1>";
  html += "<div class='subtitle'>M&Oacute;DULO ATMOSF&Eacute;RICO LUNAR - ODS 11</div>";
  html += "<div class='status-box'>" + statusClassificacao + "</div>";
  html += "<div class='data-item'><span class='data-label'>Press&atilde;o Atmosf&eacute;rica:</span><span class='data-value'>" + String(valorPressao) + " N/m&sup2;</span></div>";
  html += "<div class='data-item'><span class='data-label'>N&iacute;vel de Radia&ccedil;&atilde;o:</span><span class='data-value'>" + String(valorRadiacao) + " µSv/h</span></div>";
  html += "<div class='footer'>Sistemas de Borda IoT & IoB — FIAP 2026</div>";
  html += "</div></body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  
  // Configuração dos Pinos
  pinMode(PIN_PRESSAO, INPUT);
  pinMode(PIN_RADIACAO, INPUT);
  pinMode(LED_SEGURO, OUTPUT);
  pinMode(LED_ALERTA, OUTPUT);
  pinMode(LED_CRITICO, OUTPUT);

  // Inicialização de conexão Wi-Fi
  Serial.print("Conectando ao ecossistema Wi-Fi do Habitat");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi Conectado com sucesso!");
  Serial.print("IP do Webserver do Setor: ");
  Serial.println(WiFi.localIP());

  // Rotas do Servidor
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Servidor HTTP iniciado.");
}

void loop() {
  // Leitura analógica dos sensores simulados
  valorPressao = analogRead(PIN_PRESSAO);
  valorRadiacao = analogRead(PIN_RADIACAO);

  // Executa o motor de classificação TinyML por aproximação lógica
  executarInferenciaTinyML(valorPressao, valorRadiacao);

  // Mantém o servidor web ouvindo requisições dos astronautas
  server.handleClient();
  
  delay(100); // Estabilidade do loop
}
