#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


//* Estrutura das struct's para armazenamento dos dados */
struct itemCardapio{ //* cardapio
    int codItem;
	char NomeItem[20];
	int qtd;
	float valor;
};

struct dadosPedido{ //* v = pedido
	int numPedido; //* numero do pedido */
	int codCliente; //* codigo do cliente do pedido */
	float valorPedido; //* valor de cada pedido */
	float valorTotalPago; //* valor total pago pelo usuario com as taxas */
	int somaQtd; //* soma da quantidade de itens pedidos */
	float valorItem; //* valor de cada item */
};

struct dadosLanchonete{ //* v = lanch
	int codLanchonete;
    char nome[20], bairro[15], email[15], Telcontato[3][15], cnpj[15], login[10], senha[10];
	struct itemCardapio cardapio[20];

};

struct dadosCliente{ //* v = cliente
    int codCliente;
    char nome[10], sobrenome[10], cpf[11], Telcontato[3][12], login[10], senha[10];

};

//* Vari�veis Globais */
int NumeroLanchonete=1; //* variavel inicio de contagem cliente */
int NumeroCliente=1; //* variavel inicio de contagem cliente */
int NumeroCArdapio=1; //* variavel inicio de contagem cardapio */
int Numeropedido=1; //* variavel inicio de contagem pedido */
struct dadosCliente cliente[100]; //* Cadastro Dados Cliente App */
struct dadosLanchonete lanch[50]; //* Cadastro DadosLanchonete */
struct dadosPedido pedido[200]; //* cadastro e dados do pedido */

//* Estrutura de fun��es por modulos */
void relatorio_PF(int pfLogin){ //* Fun��o lista Relatorio de pedidos Pessoa Fisica Resumido */ 
	
	int i;
	system("cls");
	printf("\nL i s t a    d e    P e d i d o s    R e s u m i d o\n\n\n");
	for(i=0;i<200;i++){
		if(pedido[pfLogin].numPedido != -1){
			printf("Numero do Pedido: %d\nTotal Quantidade de Itens: %d\nValor Total de Pedidos: %.2f\n\n", pedido[i].numPedido, pedido[i].somaQtd, pedido[i].valorPedido);	
		}
	}
}	
	
void relatorio_PJ(int pjLogin){ //* Fun��o lista Relatorio de pedidos Pessoa Juridica Resumido */ 
	
	int i;
	system("cls");
	printf("\nL i s t a    d e    P e d i d o s    R e s u m i d o\n\n\n");
	for(i=0;i<200;i++){
		if(pedido[pjLogin].numPedido != -1){
			printf("Pedidos: %d\nTotal Quantidade de Itens: %d\nValor Total Pedidos: %.2f\n\n", pedido[i].numPedido, pedido[i].somaQtd, pedido[i].valorPedido);	
		}
	}
}	

void apresentar_lanches(int codLanch){ //* Fun��o busca e imprime o cardapio de uma lanchonete passada por parametro */

	int t;
	for(t=0; t<20; t++){
		if(lanch[codLanch].cardapio[t].codItem != -1){
		printf("\n%d - Item: %s\t\tValor unit�rio: %.2f\t\tQuantidade em estoque: %d\n", lanch[codLanch].cardapio[t].codItem, lanch[codLanch].cardapio[t].NomeItem, lanch[codLanch].cardapio[t].valor, lanch[codLanch].cardapio[t].qtd);
		}		
	}
}

int menu_PF(int pfLogin){ //* menu pessoa fisica que passa parametro para outras fun��es */

	int opc;

	do{
		system("pause");
		system("cls");
		printf("Ol�, %s", cliente[pfLogin].nome);
		printf("\n\n---M E N U    U S U � R I O---\n\n");
		printf("\n[1] para Acessar o Card�pio.\n");
		printf("[2] para Resumo dos meus Pedidos.\n");
		printf("[3] sair.\n");
		scanf("%d", &opc);

		switch(opc)
		{
			case 1:
				do{
					incluir_itemPedido(pfLogin);
					printf("Digite [6] para retornar ao Menu Usu�rio.\n");
					scanf("%d", &opc);
					if(opc!=6){
						printf("Op��o Invalida!! Digite uma op��o V�lida!!!\n");
					}
				}while(opc!=6);
				break;
			case 2:
				relatorio_PF(pfLogin);
				break;
			case 3:
				break;
			default: printf("Op��o Invalida!! Digite uma op��o V�lida!!!\n");
		}

	}while(opc>3 || opc<1);

}

int menu_lanch(int pjLogin){ //* menu Lanchonete pessoa juridica que passa parametro para outras fun��es */

	int opc;

	do{
		system("pause");
		system("cls");
		printf("Ol�, %s", lanch[pjLogin].nome);
		printf("\n\n---M E N U    P R E S T A D O R---\n");
		printf("\n[1] para Cadastrar seu Card�pio.\n");
		printf("[2] para Lista de Pedidos.\n");
		printf("[3] sair.\n");
		scanf("%d", &opc);

		switch(opc)
		{
			case 1:
				do{
					incluir_cardapio(pjLogin);
					printf("Digite [6] para retornar ao Menu Prestador.\n");
					scanf("%d", &opc);
					if(opc!=6){
						printf("Op��o Invalida!! Digite uma op��o V�lida!!!\n");
					}
				}while(opc!=6);
				break;
			case 2:
				relatorio_PJ(pjLogin);
				break;
			case 3:
				
				break;
			default: printf("Op��o Invalida!! Digite uma op��o V�lida!!!\n");
		}

	}while(opc>3 || opc<1);

}

int localizar_posicao_cardapio(int lanchonete, int cCardap){ //*Localiza uma posi��o VAZIA no vetor da struct cadastro/cardapio */
    int s=0;
    while (lanch[lanchonete].cardapio[s].codItem != cCardap && s<20){
        s++;
    }
    if (lanch[lanchonete].cardapio[s].codItem == cCardap){
        return s; //retorna a posição vazia do vetor lanchonete
    }

    return -9; //retorna -9 para indicar que o cardapio não foi localizado
}

int localiza_posicao_SENHA_PJ(char cSENHAPJ[]){//* localiza posi��o e compara Senha pessoa juridica */

	int s=0;
    while (strcmp(lanch[s].senha, cSENHAPJ)!= 0 && s<50){
        s++;
    }
    if (strcmp(lanch[s].senha, cSENHAPJ) == 0){
        return s; //retorna a posição da senha lanchonete
    }

    return -9; //retorna -9 para indicar que a senha PJ não foi localizado
}

int localiza_posicao_LOGIN_PJ(char cLOGINPJ[]){ //* localiza posi��o e compara login pessoa juridico */

	int s=0;
    while (strcmp(lanch[s].login, cLOGINPJ)!= 0 && s<50){
		s++;
    }
    if (strcmp(lanch[s].login, cLOGINPJ) == 0){
			return s; //compara e retorna Login pessoa juridica
    }

    return -9; //retorna -9 para indicar que o Login PJ não foi localizado
}

int localiza_posicao_SENHA_PF(char cSENHAPF[]){ //* localiza posi��o e compara Senha pessoa fisica */

	int s=0;
    while (strcmp(cliente[s].senha, cSENHAPF)!= 0 && s<100){
        s++;
    }
    if (strcmp(cliente[s].senha, cSENHAPF) == 0){
        return s; //compara e retorna Login pessoa fisica
    }

    return -9; //retorna -9 para indicar que a senha não foi localizado
}

int localiza_posicao_LOGIN_PF(char cLOGINPF[]){ //* localiza posi��o e compara login pessoa fisica */

	int s=0;
    while (strcmp(cliente[s].login, cLOGINPF)!= 0 && s<100){
		s++;
    }
    if (strcmp(cliente[s].login, cLOGINPF) == 0){
			return s; //compara e retorna a posição Login
    }

    return -9; //retorna -9 para indicar que o cliente não foi localizado
}

int localizar_pedido(int pPed){ //*lozaliza uma posi��o VAZIA no vetor da struct dadosPedido */
    int j=0;
    while (pedido[j].numPedido != pPed && j<200){
        j++;
    }
    if (pedido[j].numPedido == pPed){
        return j; //retorna a posição vazia do numero pedido
    }

    return -9; //retorna -9 para indicar que o numero pedido não foi localizado
}

int localizarCliente(int cCli){ //*lozaliza uma posi��o VAZIA no vetor da struct cadastro/cliente */
    int j=0;
    while (cliente[j].codCliente != cCli && j<100){
        j++;
    }
    if (cliente[j].codCliente == cCli){
        return j; //retorna a posição do cliente vazia
    }

    return -9; //retorna -9 para indicar que o cliente não foi localizado
}

int localiza_posicao_CPF(char cCPF[]){ //* localiza posi��o e compara CPF */

	int s=0;
    while (strcmp(cliente[s].cpf, cCPF)!= 0 && s<100){
        s++;
    }
    if (strcmp(cliente[s].cpf, cCPF) == 0){
        return s; //compara e retorna a posição do CPF
    }

    return -9; //retorna -9 para indicar que o CPF não foi localizado
}

int localiza_posicao_CNPJ(char cCNPJ[]){ //*localiza posi��o e compara CNPJ */

	int i=0;
    while (strcmp(lanch[i].cnpj, cCNPJ) != 0 && i<50){
        i++;
    }
    if (strcmp(lanch[i].cnpj,cCNPJ) == 0){
        return i; //compara e retorna a posição do CNPJ
    }

    return -9; //retorna -9 para indicar que o CNPJ não foi localizado
}

int localizar_posicao_Lanchonete(int cLanch){ //*Localiza posi��es vazias do codigo lanchonete vetor da struct */
    int s=0;
    while (lanch[s].codLanchonete != cLanch && s<50){
        s++;
    }
    if (lanch[s].codLanchonete == cLanch){
        return s; //retorna a posição do codigo Lanchonete
    }

    return -9; //retorna -9 para indicar que o codigo Lanchonete não foi localizado
}

void altera_cliente(){ //*Faz altera��es nos dados cadastrais lendo dados a partir do CPF e CNPJ */

	char cpf[11], cnpj[14], resposta;
	int opc, posicao, i, pfCliente, pjCliente;

	do{
		system("pause");
		system("cls");
		printf("\n\nA L T E R A R   D A D O S   C A D A S T R A I S\n\n");

		printf("\nDigite [1] para Pessoa F�sica.\n");
		printf("Digite [2] para Pessoa Jur�dica.\n");
		printf("Digite [3] para voltar.\n");
		scanf("%d", &opc);


		switch(opc)
		{

			case 1:
				fflush(stdin);
				printf("\nDigite seu CPF: ");
				fflush(stdin);
				gets(cpf);
				fflush(stdin);

				//verifica se o CPF já esta cadastrado
				pfCliente = localiza_posicao_CPF(cpf);

				if (pfCliente == -9){
					printf("CPF n�o cadastrado. \n");
					}else{
						//Exibe os dados do Cliente
						system("pause");
						system("cls");
						printf("\n\nD A D O S    C A D A S T R A I S    P E S S O A    F I S � C A\n\n");
						printf("Codigo Cdo Usu�rio: %d\n", cliente[pfCliente].codCliente);
						printf("Nome: %s\n", cliente[pfCliente].nome);
						printf("Sobrenome: %s\n", cliente[pfCliente].sobrenome);
		            	printf("CPF: %s\n", cliente[pfCliente].cpf);
						printf("Telefone Principal(whatsapp): %s\n", cliente[pfCliente].Telcontato[0]);
						printf("Telefone 2 (whatsapp): %s\n", cliente[pfCliente].Telcontato[1]);
						printf("Telefone 3 (whatsapp): %s\n", cliente[pfCliente].Telcontato[2]);
						printf("Login: %s\n", cliente[pfCliente].login);
						printf("Senha: %s\n", cliente[pfCliente].senha);

						do{
							printf("\nDigite [1] se realmente deseja fazer altera��o.\nDigite [2] para cancelar.\n");
							scanf("%d", &opc);
							if(opc>2 || opc<1){
								printf("Opca��o Invalida!! Digite uma op��o v�lida!!");
							}
						}while(opc>2 || opc<1);
						//Realiza alteracoes nos dados
						if(opc==1){
							fflush(stdin);
							printf("C�digo do Usu�rio: %d\n", cliente[pfCliente].codCliente);
							fflush(stdin);
							printf("Digite seu novo Nome: ");
							fflush(stdin);
							gets(cliente[pfCliente].nome);
							fflush(stdin);
							printf("Digite seu novo Sobrenome: ");
							fflush(stdin);
							gets(cliente[pfCliente].sobrenome);
							fflush(stdin);
							printf("Digite seu novo Telefone Principal(whatsapp): ");
							fflush(stdin);
							gets(cliente[pfCliente].Telcontato[0]);
							fflush(stdin);
							printf("Digite seu novo Login: ");
							fflush(stdin);
							gets(cliente[pfCliente].login);
							fflush(stdin);
							printf("Digite sua nova Senha: ");
							gets(cliente[pfCliente].senha);
							fflush(stdin);

							printf("\n\nDADOS ALTERADOS COM SUCESSO.\n");
						}
					}
				break;
			case 2:
				printf("\nDigite seu CNPJ: ");
				fflush(stdin);
				gets(cnpj);
				fflush(stdin);

				//verifica se o CNPJ já esta cadastrado
				pjCliente = localiza_posicao_CNPJ(cnpj);

				if (pjCliente == -9){
					printf("CNPJ n�o cadastrado. \n");
					}else{
						//Exibe os dados do Cliente
						system("pause");
						system("cls");
						printf("\n\nD A D O S    C A D A S T R A I S    P E S S O A    J U R � D I C A \n\n");
						printf("Meu Codigo: %d\n", lanch[pjCliente].codLanchonete);
						printf("Nome: %s\n", lanch[pjCliente].nome);
						printf("Bairro: %s\n", lanch[pjCliente].bairro);
						printf("Telefone Principal(whatsapp): %s\n", lanch[pjCliente].Telcontato[0]);
						printf("Telefone Principal 2: %s\n", lanch[pjCliente].Telcontato[1]);
						printf("Telefone Principal 3: %s\n", lanch[pjCliente].Telcontato[2]);
						printf("Email: %s\n", lanch[pjCliente].email);
						printf("CNPJ: %s\n", lanch[pjCliente].cnpj);
						printf("Login: %s\n", lanch[pjCliente].login);
						printf("Senha: %s\n", lanch[pjCliente].senha);
						do{
							printf("\nDigite [1] se realmente deseja fazer altera��o.\nDigite [2] para cancelar.\n");
							scanf("%d", &opc);
							if(opc>2 || opc<1){
								printf("Opca��o Invalida!! Digite uma op��o v�lida!!");
							}
						}while(opc>2 || opc<1);

						//Realiza alteracoes nos dados
						if(opc==1){
							printf("C�digo do Usu�rio: %d\n", lanch[pjCliente].codLanchonete);
							printf("Digite seu novo Nome: ");fflush(stdin);
							gets(lanch[pjCliente].nome);fflush(stdin);
							printf("Digite seu novo Bairro: "); fflush(stdin);
							gets(lanch[pjCliente].bairro);fflush(stdin);
							printf("Digite seu novo Telefone Principal(whatsapp): "); fflush(stdin);
							gets(lanch[pjCliente].Telcontato[0]); fflush(stdin);
							printf("Digite seu novo Email: ");fflush(stdin);
							gets(lanch[pjCliente].email);fflush(stdin);
							printf("Digite seu novo CNPJ: ");fflush(stdin);
							gets(lanch[pjCliente].cnpj);fflush(stdin);
							printf("Digite seu novo Login: ");fflush(stdin);
							gets(lanch[pjCliente].login);fflush(stdin);
							printf("Digite sua nova Senha: ");fflush(stdin);
							gets(lanch[pjCliente].senha);fflush(stdin);

							printf("\n\nDADOS ALTERADOS COM SUCESSO.\n");
						}
					}
				break;
			case 3:
				break;
			default:
				printf("Op��o Inv�lida!! Digite uma op��o V�lida!!!\n");
				break;
				if(opc<2 && opc<1){
					printf("Op��o Inv�lida!! Digite uma op��o V�lida!!!\n");
				}
		}
	}while(opc!=3);
}

int modulo_Login(){ //* Localiza cadastros de logs/senha e compara dados */

	int opc, pfLogin, pfSenha, pjLogin, pjSenha;
	char Lpf[10], Spf[10], Lpj[10], Spj[10];

	system("cls");
	printf("\n\n--------------ENTRE NA SUA CONTA--------------\n\n");

	do{
		printf("Digite [1] Pessoa F�sica.\n");
		printf("Digite [2] Pessoa Jur�dica.\n");
		scanf("%d", &opc);
		if(opc!=2 && opc!=1){
			printf("Op��o Invalida!! Digite uma op��o V�lida!!\n");
		}
	}while(opc!=2 && opc!=1);

	if(opc==1){ //*Condicional Pessoa Log Pessoa juridica */
		printf("Digite seu Login: ");
		scanf("%s", &Lpf);
		printf("Digite sua Senha: ");
		scanf("%s", &Spf);
		
		//verifica se o LOGIN já esta cadastrado
		pfLogin = localiza_posicao_LOGIN_PF(Lpf);
		pfSenha = localiza_posicao_SENHA_PF(Spf);
		if (pfLogin == -9 || pfSenha == -9 ){
			printf("LOGIN n�o cadastrado!! Tente novamente.\n");
			}else{
				//Exibe os dados do Cliente
				printf("\nOl�, %s %s\nC�digo do usu�rio: %d\n\n", cliente[pfLogin].nome, cliente[pfLogin].sobrenome, cliente[pfLogin].codCliente);
				menu_PF(pfLogin);
			}
	}
	if(opc==2){ //*Condicional Pessoa Log Pessoa juridica */
	printf("Digite seu Login: ");
	scanf("%s", Lpj);
	printf("Digite sua Senha: ");
	scanf("%s", Spj);
	//verifica se o LOGIN já esta cadastrado
	pjLogin = localiza_posicao_LOGIN_PJ(Lpj);
	pjSenha = localiza_posicao_SENHA_PJ(Spj);
	if (pjLogin == -9 || pjSenha == -9 ){
		printf("LOGIN n�o cadastrado!! Tente novamente.\n");
		}else{
			//Exibe os dados do Cliente
			printf("\nOl�, %s \nC�digo do usu�rio: %d\n\n", lanch[pjLogin].nome, lanch[pjLogin].codLanchonete);
			menu_lanch(pjLogin);
		}
	}
}

void incluir_itemPedido(pfLogin){ //* fun��o cadastra pedidos */

	int i, j, opc, qtd=0, lanchonete, lanche, item, resposta,y;
	float valor=0, somaValor=0, taxa=0, acrescimos=0;




	j = localizar_pedido(-1);
    if (j == -9){
        //nao localizou registro com codigo -1 ou seja não tem posicao livre
        printf("Nao tem vaga para cadastrar novos pedidos. Procure o responsavel pela TI\n");
	    }else{
			pedido[j].numPedido=Numeropedido;
			Numeropedido++;
			pedido[j].somaQtd=0;
			pedido[j].valorPedido=0;
			pedido[j].codCliente = pfLogin;
			pedido[j].valorItem = 0;
			do{
				system("pause");
				system("cls");
				printf("\n---S E L E C I O N E    A    L A N C H O N E T E---\n\n");
				printf("Lanchonetes por Nome e Bairro: \n");
				for(i=0; i<50; i++){
					if(lanch[i].codLanchonete != -1){
						printf("\nNome\t\tBairro\n");
						printf("%d - %s\t\t(%s)\n", lanch[i].codLanchonete, lanch[i].nome, lanch[i].bairro);
					}
				}
				
				printf("\nSelecione uma Lanchonete: ");
				scanf("%d", &opc);
				lanchonete = localizar_posicao_Lanchonete(opc);
				if(opc!=lanch[lanchonete].codLanchonete){
					printf("\nOp��o n�o corresponde a Lanchonete da lista!! Digite uma op��o da Lista ou tente mais tarde!!\n\n");
				}
			}while(opc!=lanch[lanchonete].codLanchonete);
			do{
				int t;
				system("pause");
				system("cls");
				printf("\nC a r d � p i o    d a    L a n c h o n e t e\n\n"); //* <<<<<<<<<<<<<<<<<<<<<<<<REGISTRO HISTORICO DE BUGGGGG
				printf("Bem vindo a Lanchonete: %s\n", lanch[lanchonete].nome);
				printf("N�mero do Pedido: %d\n\n", pedido[j].numPedido);
				apresentar_lanches(lanchonete);
				
				do{
					printf("\nSelecione um Item: ");
					scanf("%d", &item);
					lanche = localizar_posicao_cardapio(lanchonete, item);
					if(item!=lanch[lanchonete].cardapio[lanche].codItem){
						printf("Op��o n�o corresponde ao item da lista!! Digite uma op��o da Lista!!\n\n");
					}
				}while(item!=lanch[lanchonete].cardapio[lanche].codItem);
				
				printf("\nInforme a Quantidade: ");
				scanf("%d", &qtd);
				valor = lanch[lanchonete].cardapio[lanche].valor * qtd;
				pedido[j].valorPedido += valor;
				pedido[j].valorItem = lanche * qtd;
				pedido[j].somaQtd += qtd;
				lanch[lanchonete].cardapio[lanche].qtd = lanch[lanchonete].cardapio[lanche].qtd - qtd;

				printf("\nDigite [1] para incluir mais itens no seu pedido.\nDigite [2] para finalizar seu pedido.\n");
				scanf("%d", &resposta);
				if(resposta>2 && resposta<1){
					printf("Op��o Invalida!! Digite uma op��o V�lida!!!\n");
				}
			}while(resposta==1);

			if(resposta==2){
				system("cls");
				printf("\nR e s u m o    d o    P e d i d o\n\n\nN�mero do Pedido: %d\nQuantidade de item do Pedido: %d\nValor total do Pedido: %.2f\n", pedido[j].numPedido, pedido[j].somaQtd, pedido[j].valorPedido);
				printf("Total de itens: %d\n", pedido[j].somaQtd);
	            printf("\nF O R M A S    D E    P A G A M E N T O\n");
	            printf("ATENCAO!!! Pagamentos com CREDITO taxa adicional de 1.00 por item.\n\n");
				do{
					printf("[1] PIX [2] A VISTA [3] DEBITO [4] CREDITO: ");
					scanf("%d", &resposta);
					if(resposta>4 || resposta<1){
					    	printf("\nOpc�o inv�lida!!! Digite uma opc�o v�lida para continuar!!\n\n");
						}
				}while(resposta>4 || resposta<1);
				if(resposta == 1){
	                pedido[i].valorTotalPago = pedido[j].valorPedido;
					printf("\nTotal a pagar: %.2f\n", pedido[i].valorTotalPago);
	                }else
	                    if(resposta == 2){
	                        pedido[i].valorTotalPago = pedido[j].valorPedido;
							printf("Total a Pagar: %.2f\n\n", pedido[i].valorTotalPago);
	                        }else
	                            if(resposta== 3){
	                        	pedido[i].valorTotalPago = pedido[j].valorPedido;
								printf("Total a Pagar: %.2f\n\n", pedido[j].valorTotalPago);
		                        }else
									if(resposta == 4){
		                            taxa = 1.00;
		                            acrescimos = taxa * pedido[j].somaQtd;
		                            pedido[j].valorTotalPago = pedido[j].valorPedido + acrescimos;
		                            printf("Total da Taxa: %.2f\n", acrescimos);
		                            printf("Total a Pagar: %.2f\n\n", pedido[j].valorTotalPago);
		                            printf("Pedido %d Finalizado com sucesso.\n\n", pedido[j].numPedido);
								}
			}
		}
}

void incluir_lanchonete(){ //*Cadastro de  Lanchonete */

	int i, opc;
	system("cls");
	i = localizar_posicao_Lanchonete(-1);

	if (i == -9){
	    //nao localizou registro com codigo -1 ou seja não tem posicao livre
	    printf("Nao tem vaga para cadastrar novas Lanchonete. Procure o responsavel pela TI\n");
	}else{

		lanch[i].codLanchonete=NumeroLanchonete;
		NumeroLanchonete++;
		//Contrato de presta��o de servi�o */
		printf("\nContrato de Presta��o de Servi�o.\n\n1-Prestadores de servi�o tem direito a 20 slots gr�tis para inclus�o de card�pio.\n2-Para ades�o de mais slots consulte o setor de TI no Fale Conosco.\n3-Ser� cobrada taxa de transa��o por venda e por retirada(saque).\n\n");
	
		system("pause");
		system("cls");
		printf("\n---C A D A S T R O    D E    L A N C H O N E T E---\n\n");
		printf("\nC�digo do Assinante: %d", lanch[i].codLanchonete); fflush(stdin);
		printf("\nDigite o nome da sua lanchonete: ");fflush(stdin);
		gets(lanch[i].nome);fflush(stdin);
		printf("Digite Bairro onde localiza-se sua lanchonete: "); fflush(stdin);
		gets(lanch[i].bairro); fflush(stdin);
		printf("Digite o E-mail: "); fflush(stdin);
		gets(lanch[i].email); fflush(stdin);
		printf("4.Digite seu Contato Principal(whatsapp) com DDD (--)-----/----: "); fflush(stdin);
		gets(lanch[i].Telcontato[0]); fflush(stdin);
		printf("Digite o CNPJ da lanchonete: "); fflush(stdin);
		gets(lanch[i].cnpj); fflush(stdin);
		do{
			printf("\n[1] Para adicionar mais contatos\n[2] para continuar\n");
		    scanf("%d", &opc);
		    if(opc>2 || opc==0){
		        printf("Op��o inv�lida!! Digite uma op��o v�lida");
		    }
		    if(opc == 1){
		    printf("Digite seu Contato 2 com DDD (--)-----/----: "); fflush(stdin);
			gets(lanch[i].Telcontato[1]); fflush(stdin);
		    printf("Digite seu Contato 3 com DDD (--)-----/----: "); fflush(stdin);
			gets(lanch[i].Telcontato[2]); fflush(stdin);
		    }
	    }while(opc>2 || opc==0);
	
	    printf("\n5.Digite um Usu�rio(m�ximo 10 caractetes): "); fflush(stdin);
		gets(lanch[i].login); fflush(stdin);
		printf("6.Digite uma Senha(m�ximo 10 caractetes): "); fflush(stdin);
		gets(lanch[i].senha); fflush(stdin);
	
	
		printf("\nCadastro conclu�do com sucesso!! Efetue seu Login e adicione seu card�pio.\n");
	
		}
}

void incluir_cliente(){ //* cadastro de Cliente */

	int opc, i;
	system("cls");
	printf("Ol�, Seja Bem Vindo(a).\n");
	do{
		system("pause");
		system("cls");
		printf("\n---SELECIONE UMA OP��O---\n\n");
		printf("\nDigite [1] para Pessoa F�sica.\n");
		printf("Digite [2] para Pessoa Jur�dica.\n");
		printf("Digite [3] para Voltar.\n");
		scanf("%d", &opc);

		switch(opc)

		{
			case 1:
				system("cls");
				printf("\n---C A D A S T R O    P E S S O A    F � S I C A---\n\n\n");
				i = localizarCliente(-1);

			    if (i == -9){
			        //nao localizou registro com codigo -1 ou seja não tem posicao livre
			        printf("Nao tem vaga para cadastrar novos setores. Procure o responsavel pela TI\n");
			    }else{

					cliente[i].codCliente=NumeroCliente;
					NumeroCliente++;
					
					fflush(stdin);
					printf("C�digo do assinante: %d", cliente[i].codCliente);
					fflush(stdin);
					printf("\n1.Digite seu Primeiro Nome: ");
					fflush(stdin);
					gets(cliente[i].nome);
					fflush(stdin);
					printf("2.Digite seu Sobrenome: ");
					fflush(stdin);
					gets(cliente[i].sobrenome);
					fflush(stdin);
					printf("4.Digite seu Telefone Principal(whatsapp) com DDD (--)-----/----: ");
					fflush(stdin);
					gets(cliente[i].Telcontato[0]);
					fflush(stdin);
					printf("3.Digite seu CPF: ");
					fflush(stdin);
					gets(cliente[i].cpf);
					fflush(stdin);

				    do{
				        printf("\n[1] Para adicionar mais contatos\n[2] para continuar\n");
				        scanf("%d", &opc);
				        if(opc>2 || opc==0){
				            printf("Op��o inv�lida!! Digite uma op��o v�lida");
				        }
				        if(opc == 1){
				        printf("Digite seu Contato 2 com DDD (--)-----/----: ");fflush(stdin);
						gets(cliente[i].Telcontato[1]);fflush(stdin);
						printf("Digite seu Contato 3 com DDD (--)-----/----: ");fflush(stdin);
						gets(cliente[i].Telcontato[2]); fflush(stdin);
				        }
				    }while(opc>2 || opc==0);

				    printf("\n5.Digite um Usu�rio(m�ximo 10 caractetes): "); fflush(stdin);
					gets(cliente[i].login); fflush(stdin);
				    printf("6.Digite uma Senha(m�ximo 10 caractetes): "); fflush(stdin);
					gets(cliente[i].senha); fflush(stdin);

				    printf("\nCadastro conclu�do com sucesso!! Efetue seu Login e comece suas compras.\n");
				}
				break;
			case 2:
				incluir_lanchonete();
				break;

			case 3:
				break;
			default: printf("Op��o Inv�lida!! Digite uma op��o V�lida!!!\n\n");
		}
	}while(opc>3 || opc==0);
}

void incluir_cardapio(int pjLogin){ //* fun��o cadastra cardapio da lanchonete

	int i, opc;
do{
	system("cls");
	printf("\n\n---C A D A S T R E    S E U    C A R D � P I O---\n\n");

	i = localizar_posicao_cardapio(pjLogin, -1);

	if(i == -9){
	    //nao localizou registro com codigo -1 ou seja não tem posicao livre
	    printf("Nao tem vaga para cadastrar novos setores. Procure o responsavel pela TI\n");
	}else{
		system("cls");
		
		lanch[pjLogin].cardapio[i].codItem=NumeroCArdapio;
		NumeroCArdapio++;
		printf("\n---PREENCHA O FORMUL�RIO DO ITEM---\n");
		printf("\nC�digo do lanche: %d\n", lanch[pjLogin].cardapio[i].codItem);
		fflush(stdin);
		printf("Nome do Item: ");
		gets(lanch[pjLogin].cardapio[i].NomeItem);
		fflush(stdin);
		printf("Valor do lanche: ");
		scanf("%f", &lanch[pjLogin].cardapio[i].valor);
		printf("Quantidade em estoque: ");
		scanf("%d", &lanch[pjLogin].cardapio[i].qtd);

		printf("\n\nCadastro conclu�do com sucesso.\n\n");

		do{
			printf("Digite [1] para adicionar mais itens.\nDigite [2] para finalizar.\n");
			scanf("%d", &opc);
			if(opc!=2 && opc!=1){
				printf("Op��o inv�lida!! Digite uma op��o v�lida\n\n");
			}
		}while(opc!=2 && opc!=1);
	
	}
}while(opc==1);

}

void inicializarCadastro(){ //* contagem para inicializa��o de cod cliente, cod lanchonete, cod cardapio */

    int s, j, i, p;

    for(s=0;s<100;s++){
        cliente[s].codCliente=-1;
	}
    for(j=0;j<50;j++){
    	lanch[j].codLanchonete=-1;
    	for(i=0;i<20;i++){
    		lanch[j].cardapio[i].codItem=-1;
    	}
	}
	for(p=0;p<200;p++){
		pedido[p].numPedido=-1;
	}
}

int main(){

	int i, opc;
	inicializarCadastro();
	system("cls");
	
	do{
		system("cls");
		setlocale(LC_ALL, "Portuguese");
		system("color E4");
		printf("\n------ M E N U    I N I C I A L ------\n\n\n");
		printf("1.Cadastre-se!\n");
		printf("2.Fa�a seu Login!\n");
		printf("3.Alterar dados cadastrais.\n");
		printf("4.Sair\n");
		printf("5.Carrega Beta Test.\n");

		printf("\n\nSelecione uma op��o: ");
		scanf("%d", &opc);

		switch(opc)
		{
			case 1:
				do{
					incluir_cliente();
					printf("Digite [6] para retornar ao Menu Inicial\n");
					scanf("%d", &opc);
					if(opc!=6){
						printf("Op��o Invalida!! Digite uma op��o V�lida!!!\n");
					}
				}while(opc!=6);
				break;
			case 2:
				do{
					modulo_Login();
					printf("Digite [6] para retornar ao Menu Inicial\n");
					scanf("%d", &opc);
					if(opc!=6){
						printf("Op��o Invalida!! Digite uma op��o V�lida!!!\n");
					}
				}while(opc!=6);
				break;
			case 3:
				do{
					altera_cliente();
					printf("Digite [6] para retornar ao Menu Inicial\n");
						scanf("%d", &opc);
						if(opc!=6){
							printf("Op��o Invalida!! Digite uma op��o V�lida!!!\n");
						}
				}while(opc!=6);
				break;
			case 4:
				printf("Programa Finalizado\n");
				break;
			case 5:
				cliente[0].codCliente = 1;
				(strcpy(cliente[0].nome, "Gabriel"));
				(strcpy(cliente[0].sobrenome, "Santos"));
				(strcpy(cliente[0].Telcontato[0], "71999999999"));
				(strcpy(cliente[0].cpf , "99999999999"));
				(strcpy(cliente[0].login, "M"));
				(strcpy(cliente[0].senha, "s"));
				
				lanch[0].codLanchonete = 1;
				(strcpy(lanch[0].nome, "Cristiane"));
				(strcpy(lanch[0].bairro, "Ribeira"));
				(strcpy(lanch[0].email, "cris@hotmail.com"));
				(strcpy(lanch[0].Telcontato[0], "71888888888"));
				(strcpy(lanch[0].cnpj, "111111111111111"));
				(strcpy(lanch[0].login , "L")); 
				(strcpy(lanch[0].senha , "s"));
				
				lanch[1].codLanchonete = 2;
				(strcpy(lanch[1].nome, "Deise"));
				(strcpy(lanch[1].bairro, "Nordeste"));
				(strcpy(lanch[1].email, "deise_barraqueira@gmail.com"));
				(strcpy(lanch[1].Telcontato[0], "71333333333"));
				(strcpy(lanch[1].cnpj, "9777777777"));
				(strcpy(lanch[1].login , "L")); 
				(strcpy(lanch[1].senha , "s"));
				
				lanch[2].codLanchonete = 3;
				(strcpy(lanch[2].nome, "Enoque"));
				(strcpy(lanch[2].bairro, "Santa Cruz"));
				(strcpy(lanch[2].email, "enoque_brocado@gmail.com"));
				(strcpy(lanch[2].Telcontato[0], "71333333333"));
				(strcpy(lanch[2].cnpj, "9777777777"));
				(strcpy(lanch[2].login , "L")); 
				(strcpy(lanch[2].senha , "s"));

				//*cardapio posi��o 0
				lanch[0].cardapio[0].codItem=1;
				(strcpy(lanch[0].cardapio[0].NomeItem , "coxinha sem catupiry"));
				lanch[0].cardapio[0].valor = 10.00;
				lanch[0].cardapio[0].qtd = 20;
				
				lanch[0].cardapio[1].codItem=2;
				(strcpy(lanch[0].cardapio[1].NomeItem , "Coxinha com catupiry"));
				lanch[0].cardapio[1].valor = 15.00;
				lanch[0].cardapio[1].qtd = 20;
				
				lanch[0].cardapio[2].codItem=3;
				(strcpy(lanch[0].cardapio[2].NomeItem,"Pastel"));
				lanch[0].cardapio[2].valor = 15.00;
				lanch[0].cardapio[2].qtd = 20;
				//*cardapio posi��o 1
				lanch[1].cardapio[0].codItem=1;
				(strcpy(lanch[1].cardapio[0].NomeItem , "coxinha sem catupiry"));
				lanch[1].cardapio[0].valor = 10.00;
				lanch[1].cardapio[0].qtd = 20;
				
				lanch[1].cardapio[1].codItem=2;
				(strcpy(lanch[1].cardapio[1].NomeItem , "Coxinha com catupiry"));
				lanch[1].cardapio[1].valor = 15.00;
				lanch[1].cardapio[1].qtd = 20;
				
				lanch[1].cardapio[2].codItem=3;
				(strcpy(lanch[1].cardapio[2].NomeItem,"Pastel"));
				lanch[1].cardapio[2].valor = 15.00;
				lanch[1].cardapio[2].qtd = 20; 
				//*cardapio posi��o 3
				lanch[2].cardapio[0].codItem=1;
				(strcpy(lanch[2].cardapio[0].NomeItem , "coxinha sem catupiry"));
				lanch[2].cardapio[0].valor = 10.00;
				lanch[2].cardapio[0].qtd = 20;
				
				lanch[2].cardapio[1].codItem=2;
				(strcpy(lanch[2].cardapio[1].NomeItem , "Coxinha com catupiry"));
				lanch[2].cardapio[1].valor = 15.00;
				lanch[2].cardapio[1].qtd = 20;
				
				lanch[2].cardapio[2].codItem=3;
				(strcpy(lanch[2].cardapio[2].NomeItem,"Pastel"));
				lanch[2].cardapio[2].valor = 15.00;
				lanch[2].cardapio[2].qtd = 20; 	
				break;
			default: printf("Op��o Invalida!! Digite uma op��o V�lida!!!\n");
		}
	}while(opc>4 || opc==0);

    return 0;
}
