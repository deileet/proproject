#include "CppUnitTest.h"
#include "../ListLib/LinkedListLib.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace collections;

namespace ListTests
{
    TEST_CLASS(LinkedListIntTests)
    {
    public:

        TEST_METHOD(DefaultConstructor_Success)
        {
            LinkedList<int> list;
            Assert::AreEqual(size_t(0), list.getCount());
            Assert::IsTrue(list.isEmpty());
        }

        TEST_METHOD(InitializerListConstructor_Success)
        {
            LinkedList<int> list = { 10, 20, 30, 40, 50 };
            size_t count = list.getCount();
            Assert::AreEqual(size_t(5), count);
            Assert::AreEqual(10, list[0]);
            Assert::AreEqual(20, list[1]);
            Assert::AreEqual(30, list[2]);
            Assert::AreEqual(40, list[3]);
            Assert::AreEqual(50, list[4]);
        }

        TEST_METHOD(CopyConstructor_Success)
        {
            LinkedList<int> original = { 1, 2, 3 };
            LinkedList<int> copy(original);
            Assert::AreEqual(original.getCount(), copy.getCount());
            Assert::AreEqual(original[0], copy[0]);
            Assert::AreEqual(original[1], copy[1]);
            Assert::AreEqual(original[2], copy[2]);
        }

        TEST_METHOD(MoveConstructor_Success)
        {
            LinkedList<int> source = { 5, 10, 15 };
            LinkedList<int> destination(std::move(source));
            Assert::AreEqual(size_t(3), destination.getCount());
            Assert::AreEqual(5, destination[0]);
            Assert::AreEqual(10, destination[1]);
            Assert::AreEqual(15, destination[2]);
            Assert::AreEqual(size_t(0), source.getCount());
            Assert::IsTrue(source.isEmpty());
        }

        TEST_METHOD(AssignmentOperator_Success)
        {
            LinkedList<int> original = { 7, 8, 9 };
            LinkedList<int> target;
            target = original;
            Assert::AreEqual(original.getCount(), target.getCount());
            Assert::AreEqual(original[0], target[0]);
            Assert::AreEqual(original[1], target[1]);
            Assert::AreEqual(original[2], target[2]);
        }

        TEST_METHOD(PushBack_Success)
        {
            LinkedList<int> list = { 1, 2 };
            list.push_back(3);
            Assert::AreEqual(size_t(3), list.getCount());
            Assert::AreEqual(1, list[0]);
            Assert::AreEqual(2, list[1]);
            Assert::AreEqual(3, list[2]);
        }

        TEST_METHOD(PushFront_Success)
        {
            LinkedList<int> list = { 2, 3 };
            list.push_front(1);
            Assert::AreEqual(size_t(3), list.getCount());
            Assert::AreEqual(1, list[0]);
            Assert::AreEqual(2, list[1]);
            Assert::AreEqual(3, list[2]);
        }

        TEST_METHOD(Insert_Success)
        {
            LinkedList<int> list = { 10, 30, 40 };
            list.insert(1, 20);
            Assert::AreEqual(size_t(4), list.getCount());
            Assert::AreEqual(10, list[0]);
            Assert::AreEqual(20, list[1]);
            Assert::AreEqual(30, list[2]);
            Assert::AreEqual(40, list[3]);
        }

        TEST_METHOD(PopBack_Success)
        {
            LinkedList<int> list = { 1, 2, 3 };
            list.pop_back();
            Assert::AreEqual(size_t(2), list.getCount());
            Assert::AreEqual(1, list[0]);
            Assert::AreEqual(2, list[1]);
        }

        TEST_METHOD(PopFront_Success)
        {
            LinkedList<int> list = { 1, 2, 3 };
            list.pop_front();
            Assert::AreEqual(size_t(2), list.getCount());
            Assert::AreEqual(2, list[0]);
            Assert::AreEqual(3, list[1]);
        }

        TEST_METHOD(Erase_Success)
        {
            LinkedList<int> list = { 10, 20, 30, 40 };
            list.erase(2);
            Assert::AreEqual(size_t(3), list.getCount());
            Assert::AreEqual(10, list[0]);
            Assert::AreEqual(20, list[1]);
            Assert::AreEqual(40, list[2]);
        }

        TEST_METHOD(Remove_Success)
        {
            LinkedList<int> list = { 5, 10, 15, 10, 20 };
            bool removed = list.remove(10);
            Assert::IsTrue(removed);
            Assert::AreEqual(size_t(4), list.getCount());
            Assert::AreEqual(5, list[0]);
            Assert::AreEqual(15, list[1]);
            Assert::AreEqual(10, list[2]);
            Assert::AreEqual(20, list[3]);
        }

        TEST_METHOD(IndexOf_Existing_Success)
        {
            LinkedList<int> list = { 100, 200, 300, 400 };
            int index = list.indexOf(300);
            Assert::AreEqual(2, index);
        }

        TEST_METHOD(IndexOf_NonExisting_ReturnsMinusOne)
        {
            LinkedList<int> list = { 100, 200, 300 };
            int index = list.indexOf(999);
            Assert::AreEqual(-1, index);
        }

        TEST_METHOD(SetAt_Success)
        {
            LinkedList<int> list = { 1, 2, 3, 4 };
            list.setAt(2, 99);
            Assert::AreEqual(99, list[2]);
        }

        TEST_METHOD(BracketOperator_Success)
        {
            LinkedList<int> list = { 5, 6, 7, 8 };
            list[1] = 60;
            Assert::AreEqual(60, list[1]);
        }

        TEST_METHOD(Clear_Success)
        {
            LinkedList<int> list = { 1, 2, 3, 4, 5 };
            list.clear();
            Assert::AreEqual(size_t(0), list.getCount());
            Assert::IsTrue(list.isEmpty());
        }

        TEST_METHOD(AsString_Success)
        {
            LinkedList<int> list = { 1, 2, 3, 4 };
            std::string result = list.asString();
            Assert::AreEqual(std::string("[1 <-> 2 <-> 3 <-> 4]"), result);
        }

        TEST_METHOD(OutOfRangeIndex_ThrowsException)
        {
            LinkedList<int> list = { 1, 2 };
            auto func = [&]() { list[5]; };
            Assert::ExpectException<std::out_of_range>(func);
        }

        TEST_METHOD(PopBack_EmptyList_ThrowsException)
        {
            LinkedList<int> list;
            auto func = [&]() { list.pop_back(); };
            Assert::ExpectException<std::out_of_range>(func);
        }

        TEST_METHOD(PopFront_EmptyList_ThrowsException)
        {
            LinkedList<int> list;
            auto func = [&]() { list.pop_front(); };
            Assert::ExpectException<std::out_of_range>(func);
        }
    };
}
