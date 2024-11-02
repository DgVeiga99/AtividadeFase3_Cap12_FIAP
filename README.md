# AtividadeFase3_Cap12_FIAP

## Objetivo do Projeto
Este projeto tem como objetivo desenvolver um sistema inteligente de monitoramento climático e controle automatizado para ambientes agrícolas, utilizando o microcontrolador ESP32 e quatro sensores. O sistema abrange o monitoramento de condições climáticas, controle do nível de água no tanque de irrigação, detecção de presença de operadores ou animais na plantação, além de ajuste automatizado da irrigação com base na temperatura, umidade e luminosidade do ambiente. Essa solução visa otimizar o uso de recursos e melhorar a eficiência no manejo agrícola.

## Desenho do Circuito Completo
![image](https://github.com/user-attachments/assets/19ca8870-b61d-40ef-812d-475dd31c77e6)
O circuito foi montado no Wokwi.com que inclui os componentes:
- **Componentes**: ESP32, DHT22, HC-SR04, PIR e LDR.
- **Acessórios**:  Led vermelho e buzzer para sinalização de presença, Led azul para verificação do funcionamento do ultrassom

## Descrição do papel de cada sensor no sistema
- **DHT22**: Monitora temperatura e umidade. Caso a temperatura seja superior a 30°C ou a umidade seja baixa, o sistema emite um alerta para aumentar a irrigação.
- **HC-SR04**: Mede a distância, utilizado para monitorar o nível de água no tanque. Se a distância até o topo do tanque for grande, significa que o nível de água está baixo, gerando um alerta.
- **PIR**: Detecta movimento para monitoramento de atividades em áreas sensíveis, como plantações. Aciona um LED e um buzzer em caso de presença detectada.
- **LDR**: Monitora o nível de luz ambiente para identificar condições de luminosidade (dia ensolarado, nublado, etc.). Isso pode ajudar no controle de sistemas de iluminação ou sombreamento.

## Como Configurar e Rodar o Projeto no Wokwi e ESP32
Para conseguir realizar a configuração do projeto, basta acessar o link abaixo:
[https://wokwi.com/projects/413281322205761537](https://wokwi.com/projects/413281322205761537)

Assim será possível ter acesso ao diagrama confeccionado e configurado

## Instruções de instalação e dependências
Instale as bibliotecas abaixo para que o projeto tenha a operação conforme esperado
  - DHT22
  - HC-SR04
  - PIR
  - DHT sensor library for ESPx
  - DHT sensor library

## Testes realizados, com prints do Monitor Serial com mensagens de funcionamento.
Para validar o funcionamento do sistema, foram realizados testes em cada sensor individualmente e integrados ao ESP32.

#### Sensor DHT22 - Umidade e Temperatura
- **Expectativa**: O sistema deve ler e exibir os valores de temperatura e umidade no Monitor Serial.
- **Critério de Sucesso**: 
  - O sistema deve emitir um alerta para "Aumentar irrigação" se a temperatura estiver acima de 30°C ou a umidade abaixo de 50%.
  - O sistema deve emitir um alerta para "Reduzir irrigação" se a umidade estiver acima de 85%.
  
#### Sensor HC-SR04 - Distância (Nível de Água)
- **Expectativa**: A distância até o nível de água deve ser exibida em centímetros no Monitor Serial, com um alerta se o nível estiver baixo.
- **Critério de Sucesso**: 
- O sistema deve exibir "Abastecer tanque de água!" se a distância até o topo do tanque for inferior a 50 cm.

#### Sensor PIR - Detecção de Movimento
- **Expectativa**: O sistema deve detectar a presença de movimento e acionar o LED e o buzzer, além de exibir o status no Monitor Serial.
- **Critério de Sucesso**: 
- O sistema deve exibir "Movimento detectado na colheita!" ao detectar movimento e "Colheita normal" quando não há presença detectada.

#### Sensor LDR - Iluminação (Nível de Luz)
- **Expectativa**: O sistema deve medir a quantidade de luz ambiente e exibir o nível de luminosidade em lux no Monitor Serial.
- **Critério de Sucesso**: 
- O sistema deve alertar "Dia ensolarado!" para valores acima de 10.000 lux e "Dia nublado!" para valores abaixo de 1.000 lux.

Como resultado no monitor serial obtivemos:
1. Sistema operando normalmente:
 ![image](https://github.com/user-attachments/assets/c48a333c-2281-49ce-ae77-84837d595a9d)

2. Sistema operando com ajustes conforme situação:
![image](https://github.com/user-attachments/assets/dd12d0d7-fc69-442b-813c-125ef7619374)


Esses testes comprovam o funcionamento adequado dos sensores e da lógica implementada no sistema, garantindo a resposta correta a diferentes condições ambientais.
