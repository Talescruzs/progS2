class EDI():
    "Gerador de EDI, apenas implementada via terminal"
    def __init__(self):
        self.codEstr = 850
        self.codTipo = int
        self.numNota = int
        self.data = str
        self.nomeUse = str
        self.endereco = str
        self.cidade = str
        self.telefone = str
        self.cpfCNPJ = str
        self.nomeDest = str
        self.enderecoDest = str
        self.cidadeDest = str
        self.telefoneDest = str
        self.cpfCNPJDest = str
        self.produtos = list(dict())
        self.nItens = 0
        self.vTotal = 0

    def getDados(self):
        "função que seria implementada para pegar dados de algum outro lugar, que não o terminal"
        pass

    def __trataData(self): #ainda precisa ajustar
        parcial = self.data.split("/")
        validade = bool
        if(len(parcial) != 3):
            parcial[0] = int(self.data[0]+self.data[1])
            parcial.append(int(self.data[2]+self.data[3]))
            parcial.append(int(self.data[4]+self.data[5]+self.data[6]+self.data[7]))
            if(len(parcial) != 3):
                raise ValueError("data inserida fora do formato.")

        dia = int(parcial[0])
        mes = int(parcial[1])
        ano = int(parcial[2])
        validade1 = (mes==1 or mes==3 or mes==5 or mes==7 or mes==8 or mes==10 or mes==12) and (dia<=31)
        validade2 = (mes==4 or mes==6 or mes==9 or mes==11) and (dia<=30)
        validade3 = (mes==2 and dia<=28) or (mes==2 and dia==29 and ((ano%4==0 and ano%100!=0) or (ano%400==0)))
        if(mes<1 or mes>12):
            raise ValueError("data inesistente")
        elif not(validade1 or validade2 or validade3):
            raise ValueError("data inesistente")

        self.data = str(parcial[0])+str(parcial[1])+str(parcial[2])

    def __perguntaVenda(self):
        p = 0
        while(p==0):
            a = input("A nota se refere a uma venda? (s = sim, n = nao)\n")
            if(a=="s" or a =="sim" or a=="S" or a =="SIM"):
                self.codTipo = 5400
                p = 1
            elif(a=="n" or a =="nao" or a =="não" or a=="N" or a =="NAO" or a =="NÃO"):
                self.codTipo = 5700
                p = 1
            else:
                print("erro\n")
    
    def __perguntaNfiscal(self):
        p = 0
        while(p==0):
            a = input("Insira numero da nota fiscal\n")
            try:
                self.numNota = int(a)
                p = 1
            except:
                print("erro\n")
    
    def __perguntaData(self):
        p = 0
        while(p==0):
            self.data = input("Insira data do EDI\n")
            try:
                self.__trataData()
                p = 1
            except Exception as error:
                print("erro, "+repr(error)+"\n")

    def __getDadosEmissor(self):
        "Faria requisição ao sistema utilizado, aqui está inserindo dados genéricos"
        self.nomeUse = "juquinha"
        self.endereco = "Rua dos Bobos numero 0"
        self.cidade = "Pindamonhangaba"
        self.telefone = "123456789"
        self.cpfCNPJ = "123.123.123-12"

    def __getDadosDestino(self):
        "Faria requisição ao sistema utilizado, aqui está inserindo dados genéricos"
        self.nomeDest = "juquinha"
        self.enderecoDest = "Rua dos Bobos numero 0"
        self.cidadeDest = "Pindamonhangaba"
        self.telefoneDest = "123456789"
        self.cpfCNPJDest = "123.123.123-12"

    def __perguntaProduto(self):
        p = 0
        while(p==0):
            prod = dict()
            print("\n-Inserindo dados do produto {0}\n".format(len(self.produtos)+1))
            qtdProduto = input("Insira quantidade do produto\n")
            descProduto = input("Insira descricao do produto\n")
            vUniProduto = input("Insira o valor unitario do produto\n")
            try:
                prod["qtd"] = int(qtdProduto)
                prod["desc"] = descProduto
                prod["vUni"] = round(float(vUniProduto), 3) #casos raros de 3 casas de centavo
                prod["vTotal"] = prod["qtd"]*prod["vUni"]

                self.produtos.append(prod)
                p = 1

                a = input("Adicionar mais itens? (s = sim)\n")
                if(a=="s" or a =="sim" or a=="S" or a =="SIM"):
                    p = 0
            except:
                print("erro, dados inseridos de forma errada\n")
            
    def __getCTT(self):
        for p in self.produtos:
            self.nItens += p["qtd"]
            self.vTotal += p["vTotal"]

    def perguntaDados(self):
        "Valores inseridos via terminal"
        self.__perguntaVenda()
        self.__perguntaNfiscal()
        self.__perguntaData()
        self.__getDadosEmissor()
        self.__getDadosDestino()
        self.__perguntaProduto()
        self.__getCTT()

    def imprimeEDI(self):
        "Via terminal"
        print("ST*{0}*{1}".format(self.codEstr, self.codTipo))
        print("BG*{0}*{1}".format(self.numNota, self.data))
        print("N1*{0}*{1}*{2}*{3}*{4}".format(self.nomeUse, self.endereco, self.cidade, self.telefone, self.cpfCNPJ))
        print("N2*{0}*{1}*{2}*{3}*{4}".format(self.nomeDest, self.enderecoDest, self.cidadeDest, self.telefoneDest, self.cpfCNPJDest))
        for i in range(len(self.produtos)):
            print("PO{0}*{1}*{2}*{3}*{4}".format(i+1, self.produtos[i]["qtd"], self.produtos[i]["desc"], self.produtos[i]["vUni"], self.produtos[i]["vTotal"]))
        print("CTT*{0}*{1}".format(self.nItens, self.vTotal))
        print("SE*{0}".format(self.numNota))

    def geraEDI(self):
        "Funcao implementada para gerar um arquivo txt com o edi"
        file_path = "./EDI.txt"
        
        with open(file_path, 'w') as file:
            file.write("ST*{0}*{1}\n".format(self.codEstr, self.codTipo))
            file.write("BG*{0}*{1}\n".format(self.numNota, self.data))
            file.write("N1*{0}*{1}*{2}*{3}*{4}\n".format(self.nomeUse, self.endereco, self.cidade, self.telefone, self.cpfCNPJ))
            file.write("N2*{0}*{1}*{2}*{3}*{4}\n".format(self.nomeDest, self.enderecoDest, self.cidadeDest, self.telefoneDest, self.cpfCNPJDest))
            for i in range(len(self.produtos)):
                file.write("PO{0}*{1}*{2}*{3}*{4}\n".format(i+1, self.produtos[i]["qtd"], self.produtos[i]["desc"], self.produtos[i]["vUni"], self.produtos[i]["vTotal"]))
            file.write("CTT*{0}*{1}\n".format(self.nItens, self.vTotal))
            file.write("SE*{0}\n".format(self.numNota))

def gerador():
    edi = EDI()
    edi.perguntaDados()
    edi.imprimeEDI()
    edi.geraEDI()

if __name__ == "__main__":
    gerador()