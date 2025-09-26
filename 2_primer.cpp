#include <iostream>
#include <unordered_set>

// Структура узла односвязного списка
struct ListNode {
    int val;         // Значение узла
    ListNode* next;  // Указатель на следующий узел
    ListNode(int x) : val(x), next(nullptr) {}  // Конструктор для инициализации узла
};

class Solution {
public:
    // Функция поиска цикла (алгоритм Черепахи и Зайца)
    bool hasCycle(ListNode* head) {
        // Проверяем базовые случаи: пустой список или список из одного элемента
        if (head == nullptr || head->next == nullptr) {
            return false;
        }

        ListNode* slow = head; // Черепаха (двигается на 1 узел за шаг)
        ListNode* fast = head; // Заяц (двигается на 2 узла за шаг)

        // Пока не достигнем конца списка
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;          // Черепаха делает один шаг
            fast = fast->next->next;    // Заяц делает два шага

            // Если указатели встретились - обнаружен цикл
            if (slow == fast) {
                return true;
            }
        }

        return false; // Если дошли до конца - цикла нет
    }

    // Функция для безопасного вывода списка (ограничивает количество элементов)
    void printList(ListNode* head, int maxNodes = 10) {
        // Обрабатываем случай пустого списка
        if (head == nullptr) {
            std::cout << "NULL" << std::endl;
            return;
        }

        std::unordered_set<ListNode*> visited;  // Для отслеживания посещенных узлов
        int count = 0;                          // Счетчик узлов
        ListNode* current = head;               // Текущий узел

        // Выводим узлы, пока не достигнем конца или лимита
        while (current != nullptr && count < maxNodes) {
            std::cout << current->val;

            // Проверяем, был ли узел уже посещен (для обнаружения цикла)
            if (visited.count(current)) {
                std::cout << " -> [ЦИКЛ к узлу " << current->val << "]";
                break;
            }
            visited.insert(current);  // Помечаем узел как посещенный

            // Добавляем стрелку, если есть следующий узел
            if (current->next != nullptr) {
                std::cout << " -> ";
            }

            current = current->next;  // Переходим к следующему узлу
            count++;                  // Увеличиваем счетчик
        }

        // Обрабатываем случаи превышения лимита или конца списка
        if (count >= maxNodes) {
            std::cout << " ... (превышен лимит " << maxNodes << " узлов)";
        }
        else if (current == nullptr) {
            std::cout << " -> NULL";
        }

        std::cout << std::endl;
    }

    // Функция для определения длины цикла (если есть)
    int cycleLength(ListNode* head) {
        // Если цикла нет, возвращаем 0
        if (!hasCycle(head)) return 0;

        ListNode* slow = head;
        ListNode* fast = head;

        // Находим точку встречи указателей в цикле
        do {
            slow = slow->next;
            fast = fast->next->next;
        } while (slow != fast);

        // Измеряем длину цикла
        int length = 1;
        fast = fast->next;
        while (fast != slow) {
            fast = fast->next;
            length++;
        }

        return length;
    }
};

// Демонстрация работы программы
int main() {
    setlocale(LC_ALL, "");  // Настройка локали для корректного отображения кириллицы

    Solution solution;

    // Создаем список с циклом: 1 -> 2 -> 3 -> 4 -> 5 -> 2 (цикл)
    std::cout << "=== Список с циклом ===" << std::endl;
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = head->next;  // Создаем цикл на узел 2

    std::cout << "Структура списка: ";
    solution.printList(head);

    bool hasCycle = solution.hasCycle(head);
    std::cout << "Список содержит цикл: " << (hasCycle ? "Да" : "Нет") << std::endl;

    if (hasCycle) {
        std::cout << "Длина цикла: " << solution.cycleLength(head) << " узлов" << std::endl;
    }

    std::cout << std::endl;

    // Создаем список без цикла: 1 -> 2 -> 3 -> 4 -> 5
    std::cout << "=== Список без цикла ===" << std::endl;
    ListNode* head2 = new ListNode(1);
    head2->next = new ListNode(2);
    head2->next->next = new ListNode(3);
    head2->next->next->next = new ListNode(4);
    head2->next->next->next->next = new ListNode(5);

    std::cout << "Структура списка: ";
    solution.printList(head2);

    bool hasCycle2 = solution.hasCycle(head2);
    std::cout << "Второй список содержит цикл: " << (hasCycle2 ? "Да" : "Нет") << std::endl;

    std::cout << std::endl;

    // Тестируем пустой список
    std::cout << "=== Пустой список ===" << std::endl;
    ListNode* head3 = nullptr;
    std::cout << "Структура списка: ";
    solution.printList(head3);
    bool hasCycle3 = solution.hasCycle(head3);
    std::cout << "Третий список содержит цикл: " << (hasCycle3 ? "Да" : "Нет") << std::endl;

    // Очистка памяти (для списка без цикла)
    delete head2->next->next->next->next;
    delete head2->next->next->next;
    delete head2->next->next;
    delete head2->next;
    delete head2;

    // Для списка с циклом нужно аккуратно удалять, чтобы не попасть в бесконечный цикл
    // Разрываем цикл перед удалением
    head->next->next->next->next->next = nullptr;
    delete head->next->next->next->next;
    delete head->next->next->next;
    delete head->next->next;
    delete head->next;
    delete head;

    return 0;
}
