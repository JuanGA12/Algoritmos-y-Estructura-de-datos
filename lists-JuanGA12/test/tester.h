#ifndef TESTER_H
#define TESTER_H

#include <stdexcept>
#include <iostream>
#include <assert.h>

#include "../mock/mocker.cpp"
#include "../structures/lists/forward.h"
#include "../structures/lists/linked.h"
#include "../structures/lists/circular.h"

using namespace std;

#ifndef NDEBUG
#   define ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#   define ASSERT(condition, message) do { } while (false)
#endif

#define NUMBER_OF_TESTS 10

enum Collection { forward_list, linked_list, circular_list };

class Tester {
    private:
        template <typename T>
        static List<T>* getCollection(Collection);

        template <typename T>
        static void testList(Collection collection);

        template <typename T>
        static bool isSorted(List<T>*);

        template <typename T>
        static void print(List<T>*);

        template <typename T>
        static void testSpecifics(Collection, List<T>*);

        template <typename T>
        static void testForward(ForwardList<T>*);

        template <typename T>
        static void testLinked(LinkedList<T>*);

        template <typename T>
        static void testCircularLinked(CircularLinkedList<T>*);

    public:
        static void execute();
};

#endif