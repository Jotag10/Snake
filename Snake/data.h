ponto comida(lagarta **head, ponto comida_lagarta, setting config);


//função que lê o ficheiro de configurações
setting read_setting();
//função que incializa a lagarta
lagarta *inciar_lagarta(setting);
//função que cria novo nó apra a lagarat
lagarta *novo_no_lagarta(lagarta *,setting);
//funçãoq ue atualiza as posições da lagarta
lagarta *atualizar_lagarta(ponto , lagarta *, setting );
//função que atualiza valores de old
lagarta *atualizar_lagarta_old(lagarta *);

int colisao_margens(lagarta *, setting );

lagarta *free_lagarta(lagarta *head);
