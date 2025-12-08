# Sistema de Gestion de Biblioteca (SisBib)
El sistema de gestion de biblioteca consiste en el desarrollo de una aplicación de escritorio implementada en C++ utilizando el framework Qt.
El sistema tiene como objetivo la administración de materiales bibliográficos, permitiendo registrar, buscar y gestionar libros, revistas y tesis, así como controlar los préstamos y devoluciones realizados por los usuarios de la biblioteca.

## Autores
- Edgar Raul Almanza Mamani (ealmanzam@unsa.edu.pe)
- Gustavo Jonathan Turpo Torres (gturpot@unsa.edu.pe)
- Jael Emerson Huarca Pallani (jhuarcap@unsa.edu.pe)
- Oscar Raul Chilo Huillca (ochilo@unsa.edu.pe)
  
## Tecnologias usadas
- Lenguaje: C++
- Entorno de desarrollo: Qt Creator, para la interfaz y lógica del sistema.
- Almacenamiento de datos: Base de datos SQLite para registrar materiales, usuarios y préstamos.
- Control de versiones: GitHub, para trabajo colaborativo y seguimiento del código.

## Funcionalidades
- Registrar nuevos materiales bibliográficos (libros, revistas y tesis).
- Editar información existente (título, autor, año, tipo, etc.).
- Eliminar materiales del registro.
- Listar todos los materiales disponibles.
- Guardar y cargar los datos desde una base de datos SQLite.
- Registrar usuarios que solicitan préstamos.
- Consultar y gestionar información de cada usuario.
- Realizar préstamo de materiales disponibles a usuarios registrados.
- Registrar la devolución de materiales prestados.
- Controlar el estado de cada material (disponible / prestado).
- Buscar materiales por título.
- Filtrar materiales según disponibilidad.
- Buscar usuarios por nombre.
- Buscar prestamos por nombre de usuario.
- Filtrar prestamos según estado (pendientes, vencidos, devueltos).

## Cronograma semanal
|  Semana  | Entrega                                                                                                                    |
|----------|----------------------------------------------------------------------------------------------------------------------------|
| Semana 1 | Prototipo con clases base de materiales usando herencia y usuario. Carga y visualización de materiales desde archivo en UI |
| Semana 2 | Implementación de la base de datos. CRUD de materiales y usuarios. Creación de materiales usando patron Factory            |
| Semana 3 | Implementación del módulo de préstamos y devoluciones con validaciones de disponibilidad.                                  |
| Semana 4 | Módulo de búsqueda y filtrado para usuarios, materiales y préstamos usando funciones lambda. Aplicación del patrón Facade en controllers programación genérica para repositorio en memoria.|
| Semana 5 | Integración completa de todos los módulos y pruebas unitarias

## Videos de avances de funcionalidades
- Semana 1: https://youtu.be/lvsk7TnvAlI
- Semana 2: https://youtu.be/Gc0VZWt7-T4
- Semana 3 y 4: https://youtu.be/XDys7rfaBbU
- Resumen de la aplicacion y prueba de funcionalidades: https://youtu.be/wM4ivTvLmFc

## Requisitos previos
- Qt 6.x (recomendado: 6.7.2)
- Qt Creator
- Compilador MinGW 64-bit (si usas Windows)
- No requiere instalación adicional de dependencias externas

## Cómo abrir y ejecutar el proyecto
### Clonar o descargar el repositorio
Si deseas clonar el proyecto con Git:
```bash
git clone https://github.com/rescobedoq/sbd.git
```
O descarga el repositorio en formato .zip desde GitHub y extrae el contenido.
### Abrir el proyecto en Qt Creator
- Abrir Qt Creator.
- Seleccionar File → Open File or Project…
- Navegar a la carpeta del repositorio y abrir el archivo:
```bash
Biblioteca\CMakeLists.txt
```
### Configurar el kit de compilación
Qt Creator solicitará seleccionar un Kit.
Elige el kit apropiado, por ejemplo:
- Desktop Qt 6.7.2 MinGW 64-bit
Presiona Configure Project para continuar.
### Compilar el proyecto
En Qt Creator:
- Clic en el botón Build (Martillo) o presiona Ctrl + B
### Ejecutar el sistema
- Clic en Run (el botón verde ▶️) o presiona Ctrl + R
El sistema se abrirá en una ventana independiente, listo para su uso.
