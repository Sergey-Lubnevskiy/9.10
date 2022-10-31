#include <iostream>
#include "Tree.h"

using namespace std;

Tree::Tree() : m_root(nullptr), m_size(0U)
{
}

Tree::~Tree()
{
    while (m_root != nullptr)
    {
        Remove(m_root);
    }
}

Node* Tree::GetRoot() const
{
    return m_root;
}

void Tree::Insert(Node* newNode)
{
    newNode->m_left = nullptr;// Потомков нет.
    newNode->m_right = nullptr;

    Node* node = m_root;
    Node* temp = nullptr;

    while (node != nullptr)// Поиск места.
    {
        temp = node;// Будущий родитель.

        if (strcmp(newNode->m_english, node->m_english) < 0)
        {
            node = node->m_left;

        }
        else
        {
            node = node->m_right;
        }
    }

    newNode->m_parent = temp; // Заполняем родителя.

    if (temp == nullptr)// Элемент первый (единственный).
    {
        m_root = newNode;
    }

    else if (strcmp(newNode->m_english, temp->m_english) < 0)// Опеределение большего ключа.
    {
        temp->m_left = newNode;
    }
    else
    {
        temp->m_right = newNode;
    }

    ++m_size;
}

Node* Tree::Max(Node* node) const
{

    if (node != nullptr)// Поиск самого "правого" узла.
    {
        while (node->m_right != nullptr)
        {
            node = node->m_right;
        }
    }

    return node;
}

Node* Tree::Min(Node* node) const
{

    if (node != nullptr)// Поиск самого "левого" узла.
    {
        while (node->m_left != nullptr)
        {
            node = node->m_left;
        }
    }

    return node;
}

Node* Tree::Next(const Node* node) const
{
    Node* next = nullptr;

    if (node != nullptr)
    {

        if (node->m_right != nullptr)// Если есть правый потомок.
        {
            next = Min(node->m_right);
        }
        else
        {

            next = node->m_parent; // Родитель узла.


            while (next != nullptr && node == next->m_right)// Если node не корень и node справа.
            {

                node = next;// Движемся вверх.
                next = next->m_parent;
            }
        }
    }

    return next;
}

Node* Tree::Previous(const Node* node) const
{
    Node* previous = nullptr;

    if (node != nullptr)
    {
        if (node->m_left != nullptr) // Если есть левый потомок.
        {
            previous = Max(node->m_left);
        }
        else
        {
            previous = node->m_parent;// Родитель узла.

            while (previous != nullptr && node == previous->m_left)// Если node не корень и node слева.
            {
                node = previous; // Движемся вверх.
                previous = previous->m_parent;
            }
        }
    }

    return previous;
}

void Tree::Print(const Node* node) const
{
    if (node != nullptr)
    {
        Print(node->m_left);

        cout << node->m_english << '\t' << node->m_russian << endl;

        Print(node->m_right);
    }
}

void Tree::Remove(Node* removeNode)
{
    if (removeNode != nullptr)
    {
        Node* node = nullptr;
        Node* temp = nullptr;

        if (removeNode->m_left == nullptr || removeNode->m_right == nullptr) // Не 2 дочерних элемента.
        {
            temp = removeNode;
        }
        else
        {
            temp = Next(removeNode);
        }

        if (temp->m_left != nullptr)
        {
            node = temp->m_left;
        }
        else
        {
            node = temp->m_right;
        }

        if (node != nullptr)
        {
            node->m_parent = temp->m_parent;
        }

        if (temp->m_parent == nullptr)// Удаляется корневой узел
        {
            m_root = node;
        }

        else if (temp == temp->m_parent->m_left)// Слева от родителя
        {
            temp->m_parent->m_left = node;
        }

        else// Справа от родителя
        {
            temp->m_parent->m_right = node;
        }

        if (temp != removeNode)
        {
            strcpy_s(removeNode->m_english, 15U, temp->m_english);// Копирование данных узла.
            strcpy_s(removeNode->m_russian, 15U, temp->m_russian);
        }

        delete temp;

        --m_size;
    }
}

Node* Tree::Search(Node* node, const char* key) const
{
    while (node != nullptr && strcmp(key, node->m_english) != 0)// Пока есть узлы и ключи не совпадают.
    {
        if (strcmp(key, node->m_english) < 0)
        {
            node = node->m_left;
        }
        else
        {
            node = node->m_right;
        }
    }

    return node;
}