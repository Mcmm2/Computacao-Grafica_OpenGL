# Computacao-Grafica_OpenGL
Projeto pessoal de computação gráfica usando OpenGL e C++, feito no Ubuntu 16.04. 

Dependencias:
  1. GLFW 3.3, para funcionalidades de janela(https://www.glfw.org/download.html) 
  2. GLEW, para carregar as funções de sua GPU(http://glew.sourceforge.net/)  
  3. GLM, para as ferramentas matemáticas(https://glm.g-truc.net/0.9.9/index.html) 
  
Como rodar o programa:
  1. Inicialmente você deve possuir todas as 3 dependências mencionadas acima(Para o GLFW e o GLEW, recomendo que, ou baixem os binários, ou utilizem o cmake para build. No caso do GLM não é necessário fazer nada, pois é um header-only).
  2. Em seguida pegue a pasta GLM obtida no download da biblioteca e inclua em uma pasta chamada "extern" no diretório raiz do projeto.
  3. No meu caso, o projeto foi realizado em Ubuntu 16.04 sem o auxílio de IDE e com o compilador GCC. Para compilar o código esteja com o terminal na pasta "src" e utilize o texto escrito no arquivo compileLinking.txt.
 
Se tudo foi feito corretamente você deverá ver algo desse tipo:
  ![Screenshot from 2019-08-02 19-59-16](https://user-images.githubusercontent.com/42914210/62403119-8cc9c780-b561-11e9-8e16-ac18d1358383.png)
