### Para fazer **mudanças temporárias** no Git, você tem três abordagens principais, dependendo da situação:

---

## **1. Usar uma Branch Temporária (Recomendado)**  

Essa é a abordagem mais segura para testes e mudanças rápidas.  

### **Passos:**  
1. **Crie uma branch temporária:**  
   ```bash
   git checkout -b temp
   ```

2. **Faça as mudanças e testes:**  
   ```bash
   echo "Teste" > teste.txt
   ```

3. **Descarte as alterações se não precisar mais:**  
   - Descartar todas as alterações não commitadas:
     ```bash
     git restore .
     ```
   - Ou remover os arquivos novos não rastreados:
     ```bash
     git clean -fd
     ```

4. **Volte para a branch principal e exclua a temporária:**  
   ```bash
   git checkout main
   git branch -d temp
   ```

> **Nota:** Nenhuma alteração será perdida se você não fizer commit. Se precisar recuperar algo, o Git preserva histórico por meio do `reflog`.

---

## **2. Usar o Stash para Guardar Alterações Temporariamente**  

Se você está no meio de um trabalho e quer testar algo **sem criar outra branch**, o `git stash` é útil.

### **Passos:**
1. **Guarde suas alterações:**  
   ```bash
   git stash
   ```

2. **Faça os testes no mesmo diretório:**  
   ```bash
   echo "Novo Teste" > teste2.txt
   ```

3. **Descarte as mudanças do teste (se precisar):**  
   ```bash
   git restore .
   git clean -fd
   ```

4. **Recupere as alterações guardadas:**  
   ```bash
   git stash pop
   ```

---

## **3. Trabalhar em Modo "Desanexado" (Detached HEAD)**  

Se você quer testar mudanças **sem afetar a branch atual**, pode usar o modo desanexado (detached HEAD).

### **Passos:**  
1. **Entre no modo desanexado:**  
   ```bash
   git checkout HEAD --detach
   ```

2. **Faça alterações e testes:**  
   ```bash
   echo "Teste Detached" > detached.txt
   ```

3. **Descartar alterações temporárias (se não precisar delas):**  
   ```bash
   git restore .
   git clean -fd
   ```

4. **Sair do modo desanexado:**  
   ```bash
   git checkout main
   ```

> **Nota:** Se você acabar gostando das alterações e quiser salvá-las, pode criar uma branch diretamente do estado desanexado:  
```bash
git checkout -b nova-branch
```

---

### **Resumo Rápido de Qual Abordagem Usar:**

| Situação                              | Abordagem                                  |
|---------------------------------------|--------------------------------------------|
| Mudanças temporárias e testes rápidos | Criar uma **branch temporária**            |
| Guardar progresso para testar outra coisa | Usar **`git stash`**                        |
| Testes isolados sem afetar a branch    | Trabalhar no modo **Detached HEAD**         |

Se precisar de mais ajuda com alguma dessas opções, é só avisar!

### **Resposta Rápida:**

O comando:
```bash
git clean -fd
```

**NÃO remove arquivos ou diretórios staged (adicionados ao índice com `git add`).**  

Ele só **remove arquivos e diretórios não rastreados** (untracked)—ou seja:  

- Arquivos que nunca foram adicionados ao Git.  
- Arquivos ignorados explicitamente pelo `.gitignore` (se usado com `-x`).  

---

### **Sobre a Flag `-d`:**

A flag `-d` é usada para **remover diretórios não rastreados**.  

- Sem o `-d`, o comando só remove **arquivos** não rastreados e deixa os diretórios intactos.  
- Com o `-d`, ele **remove diretórios inteiros** (e seus conteúdos) que não estão sob controle do Git.  

**Exemplo:**  
Se você tiver a seguinte estrutura:  
```
projeto/
├── rastreado.txt   # Rastreado (commitado ou staged)
├── tmp/            # Diretório não rastreado
│   ├── teste.txt   # Arquivo não rastreado
│   └── lixo.txt    # Arquivo não rastreado
└── novo-arquivo.txt  # Arquivo não rastreado
```

Executando:
```bash
git clean -fd
```

**Resultado:**  
- Remove o diretório `tmp/` e todos os seus arquivos.  
- Remove o arquivo `novo-arquivo.txt`.  
- **Mantém o arquivo `rastreado.txt` e quaisquer arquivos staged.**

---

### **Outras Flags Úteis do `git clean`:**

- **`-f`** (**Force**): Necessário para forçar a limpeza (o Git não permite limpar por engano).  
- **`-d`**: Remove **diretórios não rastreados** além dos arquivos.  
- **`-x`**: Remove também arquivos ignorados pelo `.gitignore`.  
- **`-n`**: Faz um **teste** mostrando o que seria removido, sem realmente apagar nada.  
  ```bash
  git clean -fdn
  ```
- **`-i`**: Abre um modo interativo para escolher o que apagar.  
  ```bash
  git clean -fi
  ```

---

Se precisar testar antes de usar o comando ou tiver mais dúvidas, é só avisar!

Claro! Aqui está uma lista detalhada dos **Conventional Commits** mais comuns, junto com exemplos e explicações. Isso vai te deixar preparado para trabalhar em equipe com boas práticas de versionamento.  

---

## **Conventional Commits — Tipos Comuns**

### **1. feat** *(Feature)*  
> **Adição de uma nova funcionalidade ao código.**  
**Exemplo:**  
```bash
git commit -m "feat: adicionar suporte a múltiplos idiomas"
```

### **2. fix** *(Bugfix)*  
> **Correção de um bug ou erro existente.**  
**Exemplo:**  
```bash
git commit -m "fix: corrigir erro de validação no formulário"
```

### **3. docs** *(Documentation)*  
> **Alterações na documentação do projeto (README, manuais, etc.).**  
**Exemplo:**  
```bash
git commit -m "docs: atualizar instruções de instalação"
```

### **4. style** *(Styling)*  
> **Mudanças que não afetam o código em si, mas o estilo (espaços, ponto-e-vírgula, indentação).**  
**Exemplo:**  
```bash
git commit -m "style: ajustar indentação no arquivo main.js"
```

### **5. refactor** *(Refactoring)*  
> **Alterações no código que não corrigem bugs nem adicionam funcionalidades.**  
**Exemplo:**  
```bash
git commit -m "refactor: otimizar algoritmo de busca binária"
```

### **6. perf** *(Performance)*  
> **Mudanças com foco em melhorias de desempenho.**  
**Exemplo:**  
```bash
git commit -m "perf: reduzir tempo de carregamento da página inicial"
```

### **7. test** *(Testing)*  
> **Adição ou modificação de testes automatizados.**  
**Exemplo:**  
```bash
git commit -m "test: criar testes unitários para a classe Produto"
```

### **8. chore** *(Chores)*  
> **Mudanças que não afetam o código ou a lógica do sistema (builds, scripts, dependências).**  
**Exemplo:**  
```bash
git commit -m "chore: atualizar dependências do npm"
```

### **9. build** *(Builds)*  
> **Mudanças que afetam o sistema de build ou ferramentas de compilação.**  
**Exemplo:**  
```bash
git commit -m "build: adicionar webpack ao projeto"
```

### **10. ci** *(Continuous Integration)*  
> **Alterações nos arquivos ou configurações de CI/CD (GitHub Actions, Jenkins, Travis).**  
**Exemplo:**  
```bash
git commit -m "ci: corrigir pipeline de deploy no GitHub Actions"
```

### **11. revert** *(Reversão de Commit)**  
> **Reverter um commit anterior.**  
**Exemplo:**  
```bash
git commit -m "revert: desfazer commit 123abc"
```

### **12. merge** *(Merge de Branches)*  
> **Indica o merge de branches.**  
**Exemplo:**  
```bash
git commit -m "merge: combinar branch feature/login com main"
```

---

## **Exemplos de Mensagens Detalhadas**  
Você também pode adicionar descrições mais completas:  
```bash
git commit -m "feat: implementar autenticação por token

Adiciona middleware para validação de tokens JWT e suporte a geração
de tokens no login. Atualiza dependências relacionadas à segurança."
```

---

## **Por que usar Conventional Commits?**  

- **Organização:** Torna o histórico do Git mais legível.  
- **Automação:** Ferramentas podem gerar changelogs automaticamente.  
- **CI/CD Integrado:** Builds e testes podem ser executados com base no tipo de commit.  
- **Controle de Versão Semântico:** Permite automatizar versionamento (ex: `1.0.0` → `1.1.0` ou `2.0.0`).  

Se precisar de mais exemplos ou dúvidas sobre como aplicá-los na prática, é só chamar!
