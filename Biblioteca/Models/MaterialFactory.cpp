#include "MaterialFactory.h"

Material* MaterialFactory::crearMaterial(int tipo) {
    switch (tipo) {
    case 1:
        return new Libro();
    case 2:
        return new Revista();
    case 3:
        return new Tesis();
    default:
        return nullptr;
    }
}
