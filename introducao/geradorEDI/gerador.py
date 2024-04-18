class Data():
    def __init__(self):
        self.codEstr = 850
        self.codTipo = int
        self.numNota = int
        self.data = str
    def getDados(self):
        pass
    def perguntaDados(self):
        p = 0
        while(p==0):
            a = input("A nota se refere a uma venda? (s = sim, n = nao)\n")
            if(a=="s" or a =="sim"):
                self.codTipo = 5400
                p = 1
            elif(a=="n" or a =="nao" or a =="não"):
                self.codTipo = 5700
                p = 1
            else:
                print("Nao seja tapado\n")
        p = 0
        while(p==0):
            a = input("Insira numero da nota fiscal\n")
            try:
                self.numNota = int(a)
                p = 1
            except:
                print("Nao seja tapado\n")
        p = 0
        while(p==0):
            a = input("Insira data do EDI no formato dia/mes/ano\n")
            try:
                parcial = a.split("/")
                if(len(parcial) != 3):
                    raise
                if(int(parcial[1])<1 or int(parcial[1])>12):
                    raise
                if(int(parcial[0])<1 or int(parcial[0])>31): #ainda precisa ajustar
                    raise
                self.data = parcial[0]+parcial[1]+parcial[2]
                p = 1
            except:
                print("Nao seja tapado, data nao esta no formato dia/mes/ano\n")



    def imprimeEDI(self):
        print("ST*{0}*{1}".format(self.codEstr, self.codTipo))
        print("BG*{0}*{1}".format(self.numNota, self.data))
        print("N1*nome*endereco*cidade*telefone*cpf/CNPJ")
        print("N2*nome*endereco*cidade*telefone*cpf/CNPJ")
        print("POX*quantidade*descrição*valorUnitario*total")
        print("CTT*numeroItens*valorTotalNota")
        print("SE*numeroNotaFiscal")
        

    def geraEDI(self):
        pass

def gerador():
    data = Data()
    data.perguntaDados()
    data.imprimeEDI()

if __name__ == "__main__":
    gerador()