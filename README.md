# Protótipo acadêmico de controle de acesso

Trabalho acadêmico de eletricidade aplicada que documenta um protótipo didático de cancela automática para estacionamento. O repositório reúne o sketch Arduino (`.ino`), a simulação/circuito no Wokwi (`diagram.json`) e o relatório técnico em `.docx` descrevendo a montagem com Arduino UNO, sensor ultrassônico HC-SR04, servomotor SG90, LED RGB, buzzer passivo, botão e potenciômetro.

## Funcionamento descrito

- O HC-SR04 detecta a aproximação de um objeto; o potenciômetro ajusta o limite de 10 cm a 50 cm.
- O Arduino abre e fecha a cancela demonstrativa por meio do SG90.
- O LED RGB sinaliza estados e o buzzer indica movimentação.
- O botão alterna entre controle automático, manual aberto e manual fechado, com debounce.
- O código e o relatório utilizam sinais de TRIG/ECHO, controle de tempo com `millis()` na espera e os comportamentos de estado do protótipo.

## Arquivos do projeto

- Sketch Arduino (`.ino`) com o código-fonte do protótipo (adicionado ao repositório).
- `diagram.json` com a topologia de componentes e conexões da simulação.
- `Relatorio_Tecnico_Controle_de_Acesso.docx` com a descrição integral, tabelas de pinagem e diagramas incorporados.

## Limites desta publicação

Este repositório reúne o sketch Arduino, a descrição da montagem/simulação e o relatório acadêmico do projeto; não contém arquivos CAD nem um esquema elétrico editável em formato dedicado. As descrições e resultados são os registrados no escopo acadêmico; não constituem certificação de segurança, validação para uma instalação real ou evidência de ensaios além do escopo acadêmico.

Consulte `Relatorio_Tecnico_Controle_de_Acesso.docx` para a descrição integral, tabelas de pinagem e diagramas incorporados.
