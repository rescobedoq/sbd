# Sistema de Biblioteca Digital (SBD)
El sistema de gestion de biblioteca consiste en el desarrollo de una aplicación de escritorio implementada en C++ utilizando el framework Qt.
El sistema tiene como objetivo la administración de materiales bibliográficos, permitiendo registrar, buscar y gestionar libros, revistas y tesis, así como controlar los préstamos y devoluciones realizados por los usuarios de la biblioteca.

## Tecnologias a usar
- Lenguaje: C++
- Entorno de desarrollo: Qt Creator, para la interfaz y lógica del sistema.
- Almacenamiento de datos: Archivos de texto (.txt / .csv) para registrar libros, usuarios y préstamos.
- Control de versiones: GitHub, para trabajo colaborativo y seguimiento del código.

## Funcionalidades
- Registrar nuevos materiales bibliográficos (libros, revistas y audiovisuales).
- Editar información existente (título, autor, año, tipo, etc.).
- Eliminar materiales del registro.
- Listar todos los materiales disponibles.
- Guardar y cargar los datos desde archivos JSON.
- Registrar usuarios que solicitan préstamos.
- Consultar información de cada usuario (nombre, código, historial de préstamos).
- Realizar préstamo de materiales disponibles a usuarios registrados.
- Registrar la devolución de materiales prestados.
- Controlar el estado de cada material (disponible / prestado).
- Buscar materiales por título, autor o tipo.
- Filtrar materiales según disponibilidad o categoría.

## Cronograma semanal

| Semana   | Entrega                                                                                                                    |
|----------|----------------------------------------------------------------------------------------------------------------------------|
| Semana 1 | Prototipo con clases base de materiales usando herencia y usuario. Carga y visualización de materiales desde archivo en UI |
| Semana 2 | CRUD de materiales y usuarios. Creación de materiales usando patron Factory                                                |
| Semana 3 | Módulo de préstamos y devoluciones con validaciones de disponibilidad                                                      |
| Semana 4 | Módulo de búsqueda y filtrado usando funciones lambda                                                                      |
| Semana 5 | Integración completa de todos los módulos y pruebas unitarias