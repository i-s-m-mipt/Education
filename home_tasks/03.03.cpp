#include <iostream>

class List {
private:
    // Переносим структуру Node в private-секцию
    struct Node {
        int value = 0;
        Node *next = nullptr;
    };

    Node *head = nullptr;
    Node *tail = nullptr;

public:
    // Конструктор теперь не принимает Node*, так как они скрыты
    List() = default;
    List(int initial_value); // Новый конструктор для удобства
    bool IsEmpty() const;
    void show() const;
    void PushFront(int el);
    void PushBack(int el);
    void PopFront();
    void PopBack();
    int GetMedianValue() const;
    ~List();
};

// Новый конструктор для создания списка с одним элементом
List::List(int initial_value) {
    head = tail = new Node{initial_value};
}

bool List::IsEmpty() const { return head == nullptr; }

void List::show() const {
    if (IsEmpty()) {
        std::cout << "List is empty";
        return;
    }

    Node *current = head;
    std::cout << "List elements: \n";
    while (current != nullptr) {
        std::cout << current->value << "\n";
        current = current->next;
    }
}

void List::PushFront(int el) {
    Node *new_node = new Node{el, head};
    head = new_node;
    if (tail == nullptr) { // Если список был пуст
        tail = head;
    }
}

void List::PushBack(int el) {
    Node *new_node = new Node{el};
    if (IsEmpty()) {
        head = tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
}

void List::PopFront() {
    if (IsEmpty()) {
        std::cout << "List is empty";
        return;
    }

    Node *temp = head;
    head = head->next;
    delete temp;

    if (head == nullptr) { // Если список стал пустым
        tail = nullptr;
    }
}

void List::PopBack() {
    if (IsEmpty()) {
        std::cout << "List is empty";
        return;
    }

    if (head == tail) { // Если в списке только один элемент
        delete head;
        head = tail = nullptr;
        return;
    }

    // Ищем предпоследний элемент
    Node *current = head;
    while (current->next != tail) {
        current = current->next;
    }
    
    delete tail;
    tail = current;
    tail->next = nullptr;
}

int List::GetMedianValue() const {
    if (IsEmpty()) {
        std::cout << "List is empty";
        return -1;
    }

    Node *slow = head;
    Node *fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow->value;
}

List::~List() {
    Node *current = head;
    while (current != nullptr) {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

int main() {
    {
        // Новый способ инициализации списка
        List list(1); // Создаем список с одним элементом
        
        list.PushBack(2);
        list.PushBack(3);

        list.show();
        std::cout << "\n";
        std::cout << "Is empty: " << list.IsEmpty() << "\n";
        std::cout << "\n";

        list.PushBack(4);
        list.show();

        std::cout << "\n";

        // push_front testing
        list.PushFront(0);
        list.show();

        std::cout << "\n";

        // pop_front testing
        list.PopFront();
        list.show();

        std::cout << "\n";
        // pop_back testing
        list.PopBack();
        list.show();

        std::cout << "\n";

        // GetMedianValue testing
        std::cout << "Median: " << list.GetMedianValue() << "\n";
    }

    return 0;
}