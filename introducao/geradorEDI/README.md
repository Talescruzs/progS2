# 01 Exercício de Implementação: Gerador de Arquivos em Formato EDI

Você foi contratado por uma empresa para desenvolver um programa que gere notas de venda ou compra no formato EDI (Electronic Data Interchange). Sua tarefa é implementar um programa que recebe as informações de uma transação de venda ou compra e as formata conforme o padrão EDI especificado pela empresa.

Considere a seguinte estrutura simplificada de um documento EDI para os dois tipos (cada # representa uma linha diferente):

### #1: formato = ST*códigoEstrutura*códigoTipoNota
- códigoEstruta: 850 (sempre a mesma)
- códigoTipo precisa ser perguntado ao usuário
-- se for nota de Venda, códigoTipo: 5400
-- se for nota de Compra códigoTipo: 5700

### #2: formato = BG*numeroNotaFiscal*data
- numeroNotaFiscal precisa ser perguntado ao usuário
- data precisa ser perguntado ao usuário

### #3: formato: N1*nome*endereco*cidade*telefone*cpf/CNPJ
- N1 representa os dados de quem está emitindo a nota de venda ou de compra. A princípio, são dados que o próprio sistema já conhece, dessa forma, não precisa ser perguntado ao usuário.

### #4: formato: N2*nome*endereco*cidade*telefone*cpf/CNPJ
- N2 representa os dados para quem estãos emitindo a nota de venda ou de compra. Dessa forma, o usuário precisa ser perguntado sobre cada um dos dados.

### #5 a #?: formato: POX*quantidade*descrição*valorUnitario*total
- Não há limite de linhas. Pode haver quantas linhas forem necessárias para inserir todos os elementos da nota. Cada linha precisa ser numerada em sequência, iniciando em PO1, PO2, PO3...
- O usário informa quantidade, descrição e valorUnitario; o total é calculado pelo programa

### #X: penúltima linha do EDI. formato: CTT*numeroItens*valorTotalNota
- numeroItens deve apresentar a soma de todos os itens de cada linha acima
- valorTotalNota deve apresentar a soma de todos os valores de cada linha acima

### #X: última linha do EDI. formato: SE*numeroNotaFiscal
- numeroNotaFiscal já foi informado pelo usuário e deve apenas ser repetido aqui.

O arquivo EDI gerado precisa ser exibido na tela ou gravado em um arquivo .txt. O programa pode ser realizado em duplas e pode ser desenvolvido em qualquer linguagem. Enviar códigos e o necessário para rodar o mesmo.

Exemplo de EDI para uma nota de Venda:

ST*850*5400<br/>
BG*1201*06042024<br/>
N1*EMPRESA SYSTEMPA*RUA VENÂNCIO AIRES 1233. BAIRRO CENTRO*SANTA MARIA - RS*5533334444*001010100-0001<br/>
N2*LOJA DA ESQUINA*RUA DO ACAMPAMENTO. BAIRRO CENTRO*SANTA MARIA - RS*5522221111*021010202-0001<br/>
PO1*10*SACOS DE LIXO 150 LITROS*5,00*50,00<br/>
PO2*5*ESCOVAS DE AÇO*5,00*25,00<br/>
CTT*15*75,00<br/>
SE*1201<br/>

Exemplo de EDI para uma nota de Compra:

ST*850*5700<br/>
BG*1202*07042024<br/>
N1*EMPRESA SYSTEMPA*RUA VENÂNCIO AIRES 1233. BAIRRO CENTRO*SANTA MARIA - RS*5533334444*001010100-0001<br/>
N2*O ESQUINAO LANCHES*RUA DOS ANDRADAS. BAIRRO CENTRO*SANTA MARIA - RS*5599990888*031010332-0001<br/>
PO1*8*CHESS SALADA*15,00*120,00<br/>
PO2*12*CHESS ALCATRA*20,00*240,00<br/>
PO3*20*REFRI LATA*80,00*160,00<br/>
CTT*40*520,00<br/>
SE*1202<br/>