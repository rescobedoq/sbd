#ifndef REPOSITORIO_H
#define REPOSITORIO_H
#include <QVector>
#include <memory>
#include <algorithm>

template<typename T>
class Repositorio {
private:
    QVector<std::shared_ptr<T>> items;

public:
    // Cargar cache con elementos de un QVector
    void setItems(const QVector<std::shared_ptr<T>>& nuevosItems) {
        items = nuevosItems;
    }

    // Agrega un elemento en caché
    void agregar(const std::shared_ptr<T>& item) {
        items.append(item);
    }

    // Actualiza un elemento de la caché
    void actualizar(const std::shared_ptr<T>& item) {
        for (int i = 0; i < items.size(); ++i) {
            if (items[i]->getId() == item->getId()) {
                items[i] = item;
                return;
            }
        }
    }
    // Quita un elemento de la caché
    void remover(int id) {
        items.erase(
            std::remove_if(items.begin(), items.end(),
                           [id](const auto& item) {
                               return item->getId() == id;
                           }),
            items.end()
            );
    }
    // Acceso por indice
    std::shared_ptr<T> at(int index) const {
        if (index >= 0 && index < items.size()) {
            return items[index];
        }
        return nullptr;
    }

    // Buscar un elemento por ID
    std::shared_ptr<T> buscarPorId(int id) const {
        for (const auto& item : items) {
            if (item->getId() == id) {
                return item;
            }
        }
        return nullptr;
    }
    // Obtiene todos los elementos del repositorio
    QVector<std::shared_ptr<T>> obtenerTodos() const {
        return items;
    }

    QVector<std::shared_ptr<T>> filtrar(
        std::function<bool(const std::shared_ptr<T>&)> predicado) const
    {
        QVector<std::shared_ptr<T>> resultados;
        for (const auto& item : items) {
            if (predicado(item)) {
                resultados.append(item);
            }
        }
        return resultados;
    }

    int contar() const {
        return items.size();
    }

    void limpiar() {
        items.clear();
    }

    bool existe(int id) const {
        return buscarPorId(id) != nullptr;
    }
};
#endif // REPOSITORIO_H
