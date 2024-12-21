#include <iostream>
using namespace std;

class Client {                      // класс клиента
private:
    int id;                         // уникальный идентификатор
    string requestType;             // тип запроса ("low" или "high")
    time_t timestamp;               // время обращения
public:
    // конструктор по умолчанию
    Client() : id(-1), requestType(""), timestamp(0) {}

    // конструктор с передаваемыми id и типом запроса
    Client(int id, string requestType) : id(id), requestType(requestType) {
        timestamp = time(NULL);     // записываем текущее время
    }

    int getId() {                   // геттер id
        return id;
    }
    string getRequestType() {       // геттер типа запроса
        return requestType;
    }
    time_t getTimestamp() {         // геттер времени обращения
        return timestamp;
    }
};

// класс оператор
class Operator {
private:
    int id;                         // уникальный идентификатор
    bool isBusy;                    // статус занятости
public:
    // конструктор по умолчанию
    Operator() : id(-1), isBusy(false) {}

    // конструктор с параметром id
    Operator(int id) : id(id), isBusy(false) {}

    // геттеры
    bool getIsBusy() {
        return isBusy;
    }
    int getId() {
        return id;
    }

    // метод обработки клиента
    void processRequest(Client client) {
        isBusy = true;
        isBusy = false;
    }
};

struct Client_str {
    Client client;      // сам клиент
    Client_str *next;   // ссылка на следующего клиента
    Client_str *prev;   // ссылка на предыдущего клиента
    Client_str(Client c) : client(c), next(nullptr), prev(nullptr) {}
};

// класс очереди типа - первым пришел-первым ушел
class Queue {
private:
    Client_str *first;   // первый клиент в очереди
    Client_str *last;   //  последний клиент в очереди
public:
    Queue() : first(nullptr), last(nullptr) {}

    void add(Client client) {           // добавление клиента в очередь
        Client_str *n_client = new Client_str(client);
        if (!last) {                    // если очередь пустая
            first = last = n_client;    // первый и последний в очереди - добавляемый
        } else {
            last->next = n_client;      // теперь у последнего следующим будет новый клиент
            n_client->prev = last;      // у добавляемоего предыдущий будет последний
            last = n_client;            // последним становится добавляемый
        }
    }

    // убрать клиента из начала очереди
    bool remove() {
        if (!first) return false;       // если очередь пуста возвращаем false
        first = first->next;            // первым становится предыдущий первого
        if (first) {                    // если есть первый (если после удаления в очереди остались клиенты)
            first->prev = nullptr;      // у нового первого не будет предыдущего
        } else {                        // иначе если очередь теперь пуста
            last = nullptr;             // удаляем последнего
        }
        return true;                    // если убрали клиента возвращаем true
    }

    // вывести очередь
    void print_queue() {
        cout << "Queue is: ";
        Client_str* current = first;            // текущий клиент для обхода очереди
        while (current) {                       // пока есть текущий клиент
            cout << current->client.getId();    // выводит клиента
            current = current->next;            // текущим становится следующий
            if (current) cout << ", ";          // если есть текущий, то ставим запятую для вывода
        }
        cout << "." << endl;
    }

};

// класс очереди, куда можно добавлять в начало (двусвязный список)
class Deque {
private:
    Client_str *first;      // первый клиент в очереди
    Client_str *last;       //  последний клиент в очереди
public:
    Deque() : first(nullptr), last(nullptr) {}

    void add_last(Client client) {      // добавление клиента в конец очереди
        Client_str *n_client = new Client_str(client);
        if (!last) {                    // если очередь пустая
            first = last = n_client;    // первый и последний в очереди - добавляемый
        } else {
            last->next = n_client;      // теперь у последнего следующим будет новый клиент
            n_client->prev = last;      // у добавляемоего предыдущий будет последний
            last = n_client;            // последним становится добавляемый
        }
    }

    void add_first(Client client) {     // добавление клиента в начало очереди
        Client_str *n_client = new Client_str(client);
        if (!first) {                   // если очередь пуста
            first = last = n_client;    // первый и последний в очереди - добавляемый
        } else {
            n_client->next = first;     // следующим за добавляемым становится первый
            first->prev = n_client;     // предыдущим для первого становится добавляемый
            first = n_client;           // первым становится добавляемый
        }
    }

    bool remove_first() {                   // удаление первого
        if (!first) return false;           // если очередь пуста, то возвращаем false
        first = first->next;                // первым становится следующий за первым
        if (first) {                        // если после сдвига очередь не пуста, то
            first->prev = nullptr;          // очищаем у первого предыдущий
        } else {                            // иначе если очередь пуста
            last = nullptr;                 // очищаем последнего
        }
        return true;                        // возвращаем true, что первый удален
    }

    bool remove_last() {                    // удаление последнего
        if (!last) return false;            // если очередь пуста возвращаем false
        last = last->prev;                  // последним становится предыдущий для последнего
        if (last) {                         // если очередь не пуста
            last->next = nullptr;           // очищаем следующего за последним
        } else {                            // если же очередь пуста
            first = nullptr;                // очищаем первого
        }
        return true;                        // возвращаем true, что последний удален из очереди
    }

    void print_deque() {                    // вывод очереди
        cout << "Queue is: ";
        Client_str* current = first;            // текущий клиент для обхода очереди
        while (current) {                       // пока есть текущий клиент
            cout << current->client.getId();    // выводит клиента
            current = current->next;            // текущим становится следующий
            if (current) cout << ", ";          // если есть текущий, то ставим запятую для вывода
        }
        cout << "." << endl;
    }
};

int main()
{

    return 0;
}
