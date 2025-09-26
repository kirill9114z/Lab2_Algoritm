import java.util.HashSet;
import java.util.Set;

class ListNode {
    int val;
    ListNode next;
    ListNode(int x) {
        val = x;
        next = null;
    }
}

class CycleDetection {

    // Функция поиска цикла 
    public boolean hasCycle(ListNode head) {
        if (head == null || head.next == null) {
            return false;
        }

        ListNode slow = head; 
        ListNode fast = head; 

        while (fast != null && fast.next != null) {
            slow = slow.next;         
            fast = fast.next.next;    

            if (slow == fast) {        // Если встретились - цикл
                return true;
            }
        }

        return false; // Если fast дошел до конца, то цикла нет
    }

    // Функция для безопасного вывода списка
    public void printList(ListNode head) {
        printList(head, 10);
    }

    public void printList(ListNode head, int maxNodes) {
        if (head == null) {
            System.out.println("NULL");
            return;
        }

        Set<ListNode> visited = new HashSet<>();
        int count = 0;
        ListNode current = head;

        while (current != null && count < maxNodes) {
            System.out.print(current.val);

            // Проверяем, был ли узел уже посещен
            if (visited.contains(current)) {
                System.out.print(" -> [ЦИКЛ к узлу " + current.val + "]");
                break;
            }
            visited.add(current);

            if (current.next != null) {
                System.out.print(" -> ");
            }

            current = current.next;
            count++;
        }

        if (count >= maxNodes) {
            System.out.print(" ... (превышен лимит " + maxNodes + " узлов)");
        } else if (current == null) {
            System.out.print(" -> NULL");
        }

        System.out.println();
    }

    public int cycleLength(ListNode head) {
        if (!hasCycle(head)) return 0;

        ListNode slow = head;
        ListNode fast = head;

        do {
            slow = slow.next;
            fast = fast.next.next;
        } while (slow != fast);

        int length = 1;
        fast = fast.next;
        while (fast != slow) {
            fast = fast.next;
            length++;
        }

        return length;
    }

    public static void main(String[] args) {
        CycleDetection solution = new CycleDetection();

        // Создаем список с циклом: 1 -> 2 -> 3 -> 4 -> 5 -> 2 (цикл)
        System.out.println("=== Список с циклом ===");
        ListNode head = new ListNode(1);
        head.next = new ListNode(2);
        head.next.next = new ListNode(3);
        head.next.next.next = new ListNode(4);
        head.next.next.next.next = new ListNode(5);
        head.next.next.next.next.next = head.next; // Создаем цикл на узел 2

        System.out.print("Структура списка: ");
        solution.printList(head);

        boolean hasCycle = solution.hasCycle(head);
        System.out.println("Список содержит цикл: " + (hasCycle ? "Да" : "Нет"));

        if (hasCycle) {
            System.out.println("Длина цикла: " + solution.cycleLength(head) + " узлов");
        }

        System.out.println();
      
        System.out.println("=== Список без цикла ===");
        ListNode head2 = new ListNode(1);
        head2.next = new ListNode(2);
        head2.next.next = new ListNode(3);
        head2.next.next.next = new ListNode(4);
        head2.next.next.next.next = new ListNode(5);

        System.out.print("Структура списка: ");
        solution.printList(head2);

        boolean hasCycle2 = solution.hasCycle(head2);
        System.out.println("Второй список содержит цикл: " + (hasCycle2 ? "Да" : "Нет"));

        System.out.println();

        System.out.println("=== Пустой список ===");
        ListNode head3 = null;
        System.out.print("Структура списка: ");
        solution.printList(head3);
        boolean hasCycle3 = solution.hasCycle(head3);
        System.out.println("Третий список содержит цикл: " + (hasCycle3 ? "Да" : "Нет"));

        System.out.println();

        System.out.println("=== Список с одним элементом ===");
        ListNode head4 = new ListNode(1);
        System.out.print("Структура списка: ");
        solution.printList(head4);
        boolean hasCycle4 = solution.hasCycle(head4);
        System.out.println("Четвертый список содержит цикл: " + (hasCycle4 ? "Да" : "Нет"));

        System.out.println();

        System.out.println("=== Список с циклом из одного элемента ===");
        ListNode head5 = new ListNode(1);
        head5.next = head5; // Цикл на самого себя
        System.out.print("Структура списка: ");
        solution.printList(head5, 3); // Ограничиваем вывод 3 узлами
        boolean hasCycle5 = solution.hasCycle(head5);
        System.out.println("Пятый список содержит цикл: " + (hasCycle5 ? "Да" : "Нет"));
        if (hasCycle5) {
            System.out.println("Длина цикла: " + solution.cycleLength(head5) + " узлов");
        }

        // В Java не нужно явно освобождать память - сборщик мусора сделает это автоматически
    }
}
