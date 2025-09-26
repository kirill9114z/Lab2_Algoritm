// Условие: Напишите функцию, которая принимает голову односвязного списка
// и возвращает голову развернутого списка (элементы в обратном порядке).

#include <iostream>

// Структура, представляющая узел односвязного списка
struct ListNode {
    int val;         // Значение узла
    ListNode* next;  // Указатель на следующий узел
    ListNode(int x) : val(x), next(nullptr) {}  // Конструктор для инициализации узла
};

class Solution {
public:
    // Основная функция разворота списка
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;   // Указатель на предыдущий узел (изначально пустой)
        ListNode* current = head;   // Указатель на текущий узел (начинаем с головы)

        // Проходим по всем узлам списка
        while (current != nullptr) {
            // Сохраняем ссылку на следующий узел, прежде чем меняем указатели
            ListNode* nextTemp = current->next;
            
            // Меняем направление указателя текущего узла на предыдущий
            current->next = prev;
            
            // Перемещаем указатель prev на текущий узел для следующей итерации
            prev = current;
            
            // Переходим к следующему узлу в исходном списке
            current = nextTemp;
        }
        
        // Возвращаем новую голову списка (prev теперь указывает на последний узел исходного списка)
        return prev;
    }
};

// Вспомогательная функция для вывода списка в консоль
void printList(ListNode* head) {
    while (head != nullptr) {
        std::cout << head->val << " -> ";
        head = head->next;
    }
    std::cout << "NULL" << std::endl;
}

// Функция для демонстрации работы алгоритма
int main() {
    setlocale(LC_ALL, ""); // Настройка локали для корректного отображения кириллицы

    // Создаем тестовый список: 1 -> 2 -> 3 -> 4 -> 5
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    std::cout << "Исходный список: ";
    printList(head);

    // Создаем экземпляр класса Solution и разворачиваем список
    Solution solution;
    ListNode* reversedHead = solution.reverseList(head);

    std::cout << "Развернутый список: ";
    printList(reversedHead);

    // Освобождение памяти (в реальном коде должно быть реализовано более аккуратно)
    while (reversedHead != nullptr) {
        ListNode* temp = reversedHead;
        reversedHead = reversedHead->next;
        delete temp;
    }

    return 0;
}
