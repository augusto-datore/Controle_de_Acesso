# Protótipo acadêmico de controle de acesso

Trabalho acadêmico de eletricidade aplicada que documenta um protótipo didático de cancela automática para estacionamento. O repositório reúne o sketch Arduino (`codigo.ino`), a simulação do circuito no Wokwi (`diagrama.json`) e o relatório técnico em `.docx`, que descreve a montagem com Arduino UNO, sensor ultrassônico HC-SR04, servomotor SG90, LED RGB, buzzer passivo, botão e potenciômetro.

O repositório inclui o diagrama do circuito para simulação no Wokwi. O relatório técnico registra testes em bancada com Arduino conectado via USB e uma maquete; não há teste em uma instalação real documentado.

## Funcionamento descrito

- O HC-SR04 detecta a aproximação de um objeto; o potenciômetro ajusta o limite de 10 cm a 50 cm.
- O Arduino abre e fecha a cancela demonstrativa por meio do SG90.
- O LED RGB sinaliza estados e o buzzer indica movimentação.
- O botão alterna entre controle automático, manual aberto e manual fechado, com debounce.
- O código e o relatório utilizam sinais de TRIG/ECHO, controle de tempo com `millis()` na espera e os comportamentos de estado do protótipo.

## Arquivos do projeto

- `codigo.ino`: sketch Arduino com o código-fonte do protótipo.
- `diagrama.json`: topologia de componentes e conexões da simulação Wokwi.
- `Relatorio_Tecnico_Controle_de_Acesso.docx`: relatório acadêmico com a descrição, tabelas de pinagem e diagramas incorporados.

## Limites desta publicação

Este repositório reúne o sketch Arduino, a descrição da montagem/simulação e o relatório acadêmico; não contém arquivos CAD nem um esquema elétrico editável em formato dedicado. As descrições e resultados são os registrados no escopo acadêmico; não constituem certificação de segurança, validação para uma instalação real ou evidência de ensaios físicos.

Consulte `Relatorio_Tecnico_Controle_de_Acesso.docx` para a descrição integral, tabelas de pinagem e diagramas incorporados.
