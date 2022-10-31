#pragma once
#include "Node.h"

class Tree
{
private:

    Node* m_root; // Корень.

    unsigned int m_size;// Количество узлов.

public:

    Tree();

    ~Tree();

    Node* GetRoot() const;// Получить корень.

    void Insert(Node* node);// Вставка узла.

    Node* Max(Node* node) const;// Максимальное значение от указанного узла.

    Node* Min(Node* node) const;// Минимальное значение от указанного узла.

    Node* Next(const Node* node) const;// Следующий узел для указанного узла.

    Node* Previous(const Node* node) const;// Предыдущий узел для указанного узла.

    void Print(const Node* node) const;// Печать от указанного узла.

    void Remove(Node* node); // Удаление ветки для указанного узла.

    Node* Search(Node* node, const char* key) const;// Поиск от указанного узла.
};