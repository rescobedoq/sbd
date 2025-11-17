#ifndef MATERIALFACTORY_H
#define MATERIALFACTORY_H

#include "Material.h"
#include "Libro.h"
#include "Revista.h"
#include "Tesis.h"

class MaterialFactory {
public:
    static Material* crearMaterial(int tipo);
    // tipo: 1 = Libro, 2 = Revista, 3 = Tesis
};

#endif
