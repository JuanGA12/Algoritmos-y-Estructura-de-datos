#include "tester.h"

void Tester::execute() {
    Collection collections[] = { forward_list, linked_list, circular_list };
    size_t numberOfCollections = sizeof(collections) / sizeof(collections[0]);

    for (int i = 0; i < numberOfCollections; i++) {
        for (int j = 0; j < NUMBER_OF_TESTS; ++j) {
            testList<int>(collections[i]);
            testList<char>(collections[i]);
        }
    }
}

template <typename T>
List<T>* Tester::getCollection(Collection collection) {
    switch (collection) {
        case forward_list: return new ForwardList<T>();
        case linked_list: return new LinkedList<T>();
        case circular_list: return new CircularLinkedList<T>();
        default: throw invalid_argument("Not a valid collection - build");
    }
}

template <typename T>
void Tester::testSpecifics(Collection collection, List<T>* list) {
    switch (collection) {
        case forward_list: testForward((ForwardList<T>*) list); break;
        case linked_list: testLinked((LinkedList<T>*) list); break;
        case circular_list: testCircularLinked((CircularLinkedList<T>*) list); break;
        default: throw invalid_argument("Not a valid collection - specifics");
    }
}

template <typename T>
void Tester::testList(Collection collection) {
    Mocker mocker;
    unsigned int size = mocker.generateRandomInt(10);
    T* elements = mocker.generateRandomArray<T>(size);
    List<T>* list = getCollection<T>(collection);
    List<T>* list1 = getCollection<T>(collection);

    ASSERT(list->size() == 0, "The " + list->name() + " size is not working");
    ASSERT(list->empty() == true, "The " + list->name() + " empty is not working");

    list->push_back(elements[0]);
    list->push_back(elements[1]);
    ASSERT(list->size() == 2, "The " + list->name() + " push_back or size is not working");
    ASSERT((*list)[1] == elements[1], "The " + list->name() + " operator [] is not working");

    list->push_back(elements[2]);
    list->push_back(elements[3]);
    list->pop_front();
    ASSERT(list->size() == 3, "The " + list->name() + " pop_front is not working");
    ASSERT(list->front() == elements[1], "The " + list->name() + " front is not working");
    ASSERT((*list)[2] == elements[3], "The " + list->name() + " operator [] is not working");

    list->push_back(elements[4]);
    list->push_back(elements[5]);
    list->pop_back();
    ASSERT(list->size() == 4, "The " + list->name() + " pop_back is not working");
    ASSERT(list->back() == elements[4], "The " + list->name() + " back is not working");
    
    list->reverse();

    ASSERT(list->back() == elements[1], "The " + list->name() + " reverse is not working");
    ASSERT(list->front() == elements[4], "The " + list->name() + " reverse is not working");
    ASSERT((*list)[1] == elements[3], "The " + list->name() + " reverse is not working");
    ASSERT((*list)[2] == elements[2], "The " + list->name() + " reverse is not working");

    list->push_back(elements[6]);
    list->push_back(elements[7]);
    list->sort();

    ASSERT(isSorted(list), "The " + list->name() + " sort is not working");

    list->clear();
    ASSERT(list->size() == 0, "The " + list->name() + " size or clear is not working");
    ASSERT(list->empty() == true, "The " + list->name() + " empty is not working");

    testSpecifics(collection, list);

    cout << "Completed: " << list->name() << endl;
}

template <typename T>
bool Tester::isSorted(List<T>* list) {
    for (int i = 1; i < list->size(); ++i) {
        if ((*list)[i - 1] > (*list)[i]) {
            return false;
        }
    }

    return true;
}


template <typename T>
void Tester::print(List<T>* list) {
    for (int i = 0; i < list->size(); ++i) {
        cout << (*list)[i] << " ";
    }

    cout << endl;
}


template <typename T>
void Tester::testForward(ForwardList<T>* list) {
    Mocker mocker;
    unsigned int size = mocker.generateRandomInt(5);
    T* elements = mocker.generateRandomArray<T>(size);

    ForwardList<T>* list1 = new ForwardList<T>;
    list1->push_back(elements[0]);
    list1->push_back(elements[1]);
    list1->push_back(elements[2]);
    list1->push_back(elements[3]);
    list1->push_back(elements[4]);

    list->merge(*list1);
    ASSERT(list->size() == 5, "The " + list->name() + " merge is not working");

    auto it = list->begin();
    ++it;
    ASSERT(*it == elements[1], "The " + list->name() + " iterator is not working");
    ++it;
    ++it;
    ASSERT(it != list->end(), "The " + list->name() + " iterator is not working");

}

template <typename T>
void Tester::testLinked(LinkedList<T>* list) {
    Mocker mocker;
    unsigned int size = mocker.generateRandomInt(5);
    T* elements = mocker.generateRandomArray<T>(size);

    LinkedList<T>* list1 = new LinkedList<T>;
    list1->push_back(elements[0]);
    list1->push_back(elements[1]);
    list1->push_back(elements[2]);
    list1->push_back(elements[3]);
    list1->push_back(elements[4]);

    list->merge(*list1);
    ASSERT(list->size() == 5, "The " + list->name() + " merge is not working");

    auto it = list->begin();
    ++it;
    ASSERT(*it == elements[1], "The " + list->name() + " iterator is not working");
    ++it;
    ++it;
    --it;
    ASSERT(*it == elements[2], "The " + list->name() + " iterator is not working");
    ASSERT(it != list->end(), "The " + list->name() + " iterator is not working");
}


template <typename T>
void Tester::testCircularLinked(CircularLinkedList<T>* list) {
    Mocker mocker;
    unsigned int size = mocker.generateRandomInt(5);
    T* elements = mocker.generateRandomArray<T>(size);

    CircularLinkedList<T>* list1 = new CircularLinkedList<T>;
    list1->push_back(elements[0]);
    list1->push_back(elements[1]);
    list1->push_back(elements[2]);
    list1->push_back(elements[3]);
    list1->push_back(elements[4]);

    list->merge(*list1);
    ASSERT(list->size() == 5, "The " + list->name() + " merge is not working");

    auto it = list->begin();
    ++it;
    ASSERT(*it == elements[1], "The " + list->name() + " iterator is not working");
    ++it;
    ++it;
    --it;
    ASSERT(*it == elements[2], "The " + list->name() + " iterator is not working");
    ASSERT(it != list->end(), "The " + list->name() + " iterator is not working");
    ++it;
    ++it;
    ++it;
    ++it;
    ASSERT(*it == elements[1], "The " + list->name() + " iterator is not working");
    --it;
    --it;
    ASSERT(*it == elements[4], "The " + list->name() + " iterator is not working");

}
