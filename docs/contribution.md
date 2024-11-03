## `CONTRIBUTING.md`

# Contributing to Robot Maze Project

Obrigado por contribuir ao projeto Robot Maze! Para mantermos o código organizado, consistente e fácil de colaborar, siga as diretrizes abaixo.

### 1. Código em Inglês

- **Padronização em Inglês**: Para garantir que o código seja acessível a uma comunidade ampla, todas as variáveis, funções, classes, comentários e commits devem estar em inglês.
- **Consistência**: Mesmo que o projeto seja inicialmente em português, é importante manter a consistência para que ele possa crescer e receber contribuições de outros desenvolvedores ao redor do mundo.

### 2. Fluxo de Trabalho com Branchs

Para manter o repositório principal (`main` branch) sempre estável e revisado, usamos um fluxo de trabalho baseado em branchs.

#### Por que usar branchs?

Usar branchs permite que cada nova funcionalidade, correção de bug ou ajuste seja desenvolvido isoladamente do código principal, o que facilita:
- **Revisão e Testes**: Branchs específicas facilitam a revisão de código antes da integração ao `main`.
- **Controle de Versão**: Permite acompanhar o desenvolvimento de funcionalidades separadas e reverter alterações específicas se necessário.
- **Colaboração**: Diversos colaboradores podem trabalhar simultaneamente em diferentes branchs sem afetar o trabalho um do outro.

#### Como Trabalhar com Branchs

1. **Crie uma Branch para Cada Tarefa**
   - Antes de começar uma nova funcionalidade, correção ou ajuste, crie uma branch separada. Use um nome descritivo para a branch, como `feature/maze-navigation`, `bugfix/collision-detection`, ou `docs/update-readme`.
   
   ```bash
   git checkout -b feature/maze-navigation
   ```

2. **Faça Commits Frequentes e Significativos**
   - Commits pequenos e frequentes ajudam no acompanhamento do progresso. Certifique-se de usar mensagens de commit claras e descritivas em inglês.
   
   ```bash
   git commit -m "Add basic maze navigation logic"
   ```

3. **Push para a Branch Remota**
   - Envie sua branch para o repositório remoto, criando um histórico de alterações disponível para revisão.
   
   ```bash
   git push origin feature/maze-navigation
   ```

4. **Crie uma Pull Request (PR)**
   - Depois de finalizar o desenvolvimento e testar, abra uma Pull Request para a branch `main`. Isso permite que outros colaboradores revisem as alterações antes da integração.
   - No PR, adicione uma descrição detalhada sobre o que foi alterado, e marque qualquer issue que a PR resolva, como `Closes #issue-number`.

5. **Mantenha a Branch Atualizada**
   - Se a branch `main` receber novas alterações durante o desenvolvimento, faça merge da `main` na sua branch local para manter seu código atualizado:
   
   ```bash
   git checkout nome-da-branch-que-voce-esta-trabalhando #esse comando é para garantir que você esta na branch correta
   git merge main
   ```

6. **Após Aprovação, Faça Merge para `main`**
   - Depois que a Pull Request for revisada e aprovada, faça o merge para `main`. Isso pode ser feito diretamente no GitHub.

7. **Apague Branchs Locais e Remotas**
   - Após o merge, apague a branch local e remota para manter o repositório organizado:
   
   ```bash
   git branch -d feature/maze-navigation
   git push origin --delete feature/maze-navigation
   ```

### 3. Diretrizes Gerais

- **Padrão de Código**: Siga as boas práticas de código C, com nomes de variáveis descritivos e comentários claros para blocos complexos.
- **Testes e Revisões**: Sempre revise e teste o código antes de abrir uma Pull Request, especialmente se for uma funcionalidade crítica.

Se tiver alguma dúvida, entre em contato ou consulte outros documentos na pasta `docs/`.

