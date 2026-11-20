# Protótipo acadêmico de controle de acesso

Trabalho acadêmico de eletricidade aplicada que documenta um protótipo didático de cancela automática para estacionamento. O relatório descreve a montagem com Arduino UNO, sensor ultrassônico HC-SR04, servomotor SG90, LED RGB, buzzer passivo, botão e potenciômetro.

## Funcionamento descrito

- O HC-SR04 detecta a aproximação de um objeto; o potenciômetro ajusta o limite de 10 cm a 50 cm.
- O Arduino abre e fecha a cancela demonstrativa por meio do SG90.
- O LED RGB sinaliza estados e o buzzer indica movimentação.
- O botão alterna entre controle automático, manual aberto e manual fechado, com debounce.
- O relatório descreve os sinais de TRIG/ECHO, uso de `millis()` na espera e o comportamento esperado do protótipo.

## Limites desta publicação

Este repositório contém o relatório acadêmico fornecido, não o sketch Arduino, arquivos CAD nem um esquema elétrico editável. As descrições e resultados são os registrados no relatório; não constituem certificação de segurança, validação para uma instalação real ou evidência de ensaios além do escopo acadêmico.

Consulte `Relatorio_Tecnico_Controle_de_Acesso.docx` para a descrição integral, tabelas de pinagem e diagramas incorporados.
