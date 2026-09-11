#include "CppUnitTest.h"
#include "DoublyLinkedList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace chains;

namespace UniqueListSuite
{
    TEST_CLASS(CreationTests)
    {
    public:
        TEST_METHOD(DefaultConstructor_LeavesListEmpty)
        {
            const DoublyLinkedList<int> list;

            Assert::AreEqual(std::size_t(0), list.size());
            Assert::IsTrue(list.empty());
        }

        TEST_METHOD(InitializerList_KeepsGivenOrder)
        {
            const DoublyLinkedList<int> list = { 10, 20, 30, 40, 50 };

            Assert::AreEqual(std::size_t(5), list.size());
            Assert::AreEqual(10, list[0]);
            Assert::AreEqual(20, list[1]);
            Assert::AreEqual(30, list[2]);
            Assert::AreEqual(40, list[3]);
            Assert::AreEqual(50, list[4]);
        }

        TEST_METHOD(CopyConstructor_MakesIndependentCopy)
        {
            const DoublyLinkedList<int> original = { 1, 2, 3 };

            DoublyLinkedList<int> copy(original);
            Assert::AreEqual(original.size(), copy.size());
            Assert::AreEqual(original[0], copy[0]);
            Assert::AreEqual(original[1], copy[1]);
            Assert::AreEqual(original[2], copy[2]);

            copy[0] = 99;
            Assert::AreEqual(1, original[0]);
        }

        TEST_METHOD(MoveConstructor_TransfersDataAndEmptiesSource)
        {
            DoublyLinkedList<int> source = { 5, 10, 15 };

            const DoublyLinkedList<int> destination(std::move(source));

            Assert::AreEqual(std::size_t(3), destination.size());
            Assert::AreEqual(5, destination[0]);
            Assert::AreEqual(10, destination[1]);
            Assert::AreEqual(15, destination[2]);
            Assert::AreEqual(std::size_t(0), source.size());
            Assert::IsTrue(source.empty());
        }

        TEST_METHOD(CopyAssignment_ReplacesAllContent)
        {
            const DoublyLinkedList<int> original = { 7, 8, 9 };
            DoublyLinkedList<int> target;

            target = original;

            Assert::AreEqual(original.size(), target.size());
            Assert::AreEqual(original[0], target[0]);
            Assert::AreEqual(original[1], target[1]);
            Assert::AreEqual(original[2], target[2]);
        }

        TEST_METHOD(MoveAssignment_TransfersDataAndEmptiesSource)
        {
            DoublyLinkedList<int> source = { 7, 8, 9 };
            DoublyLinkedList<int> target;

            target = std::move(source);

            Assert::AreEqual(std::size_t(3), target.size());
            Assert::AreEqual(7, target[0]);
            Assert::AreEqual(8, target[1]);
            Assert::AreEqual(9, target[2]);
            Assert::IsTrue(source.empty());
        }
    };

    TEST_CLASS(MutationTests)
    {
    public:
        TEST_METHOD(PushBack_AppendsAtTheTail)
        {
            DoublyLinkedList<int> list = { 1, 2 };

            list.pushBack(3);

            Assert::AreEqual(std::size_t(3), list.size());
            Assert::AreEqual(1, list[0]);
            Assert::AreEqual(2, list[1]);
            Assert::AreEqual(3, list[2]);
        }

        TEST_METHOD(PushFront_InsertsAtTheHead)
        {
            DoublyLinkedList<int> list = { 2, 3 };

            list.pushFront(1);

            Assert::AreEqual(std::size_t(3), list.size());
            Assert::AreEqual(1, list[0]);
            Assert::AreEqual(2, list[1]);
            Assert::AreEqual(3, list[2]);
        }

        TEST_METHOD(InsertAt_MiddlePosition_ShiftsTailPart)
        {
            DoublyLinkedList<int> list = { 10, 30, 40 };

            list.insertAt(1, 20);

            Assert::AreEqual(std::size_t(4), list.size());
            Assert::AreEqual(10, list[0]);
            Assert::AreEqual(20, list[1]);
            Assert::AreEqual(30, list[2]);
            Assert::AreEqual(40, list[3]);
        }

        TEST_METHOD(InsertAt_LastPosition_WorksAsPushBack)
        {
            DoublyLinkedList<int> list = { 10, 20 };

            list.insertAt(2, 30);

            Assert::AreEqual(std::size_t(3), list.size());
            Assert::AreEqual(30, list[2]);
        }

        TEST_METHOD(PopBack_RemovesTheTail)
        {
            DoublyLinkedList<int> list = { 1, 2, 3 };

            list.popBack();

            Assert::AreEqual(std::size_t(2), list.size());
            Assert::AreEqual(1, list[0]);
            Assert::AreEqual(2, list[1]);
        }

        TEST_METHOD(PopFront_RemovesTheHead)
        {
            DoublyLinkedList<int> list = { 1, 2, 3 };

            list.popFront();

            Assert::AreEqual(std::size_t(2), list.size());
            Assert::AreEqual(2, list[0]);
            Assert::AreEqual(3, list[1]);
        }

        TEST_METHOD(DeleteAt_Middle_UnlinksElement)
        {
            DoublyLinkedList<int> list = { 10, 20, 30, 40 };

            list.deleteAt(2);

            Assert::AreEqual(std::size_t(3), list.size());
            Assert::AreEqual(10, list[0]);
            Assert::AreEqual(20, list[1]);
            Assert::AreEqual(40, list[2]);
        }

        TEST_METHOD(DeleteAt_FirstAndLast_HandledByFastPaths)
        {
            DoublyLinkedList<int> list = { 10, 20, 30 };

            list.deleteAt(0);
            Assert::AreEqual(20, list[0]);
            Assert::AreEqual(std::size_t(2), list.size());

            list.deleteAt(1);
            Assert::AreEqual(20, list[0]);
            Assert::AreEqual(std::size_t(1), list.size());
        }

        TEST_METHOD(RemoveFirstOf_ExistingValue_ReturnsTrue)
        {
            DoublyLinkedList<int> list = { 5, 10, 15, 10, 20 };

            const bool removed = list.removeFirstOf(10);

            Assert::IsTrue(removed);
            Assert::AreEqual(std::size_t(4), list.size());
            Assert::AreEqual(5, list[0]);
            Assert::AreEqual(15, list[1]);
            Assert::AreEqual(10, list[2]);
            Assert::AreEqual(20, list[3]);
        }

        TEST_METHOD(RemoveFirstOf_MissingValue_ReturnsFalse)
        {
            DoublyLinkedList<int> list = { 1, 2, 3 };

            const bool removed = list.removeFirstOf(999);

            Assert::IsFalse(removed);
            Assert::AreEqual(std::size_t(3), list.size());
        }
    };

    TEST_CLASS(QueryTests)
    {
    public:
        TEST_METHOD(IndexOf_ExistingValue_ReturnsItsPosition)
        {
            const DoublyLinkedList<int> list = { 100, 200, 300, 400 };

            const int index = list.findIndexOf(300);

            Assert::AreEqual(2, index);
        }

        TEST_METHOD(IndexOf_MissingValue_ReturnsMinusOne)
        {
            const DoublyLinkedList<int> list = { 100, 200, 300 };

            const int index = list.findIndexOf(999);

            Assert::AreEqual(-1, index);
        }

        TEST_METHOD(AssignAt_ChangesTheRequestedCell)
        {
            DoublyLinkedList<int> list = { 1, 2, 3, 4 };

            list.assignAt(2, 99);

            Assert::AreEqual(99, list[2]);
        }

        TEST_METHOD(BracketOperator_AllowsReadingAndWriting)
        {
            DoublyLinkedList<int> list = { 5, 6, 7, 8 };

            Assert::AreEqual(6, list[1]);

            list[1] = 60;

            Assert::AreEqual(60, list[1]);
            Assert::AreEqual(std::size_t(4), list.size());
        }

        TEST_METHOD(ClearAll_ReturnsListToInitialState)
        {
            DoublyLinkedList<int> list = { 1, 2, 3, 4, 5 };

            list.clearAll();

            Assert::AreEqual(std::size_t(0), list.size());
            Assert::IsTrue(list.empty());
        }

        TEST_METHOD(ToText_FormatsListWithArrowSeparators)
        {
            const DoublyLinkedList<int> list = { 1, 2, 3, 4 };

            const std::string result = list.toText();

            Assert::AreEqual(std::string("[1 <-> 2 <-> 3 <-> 4]"), result);
        }
    };

    TEST_CLASS(ExceptionTests)
    {
    public:
        TEST_METHOD(BracketOperator_TooLargeIndex_Throws)
        {
            const DoublyLinkedList<int> list = { 1, 2 };

            auto attempt = [&list]() { static_cast<void>(list[5]); };

            Assert::ExpectException<std::out_of_range>(attempt);
        }

        TEST_METHOD(PopBack_OnEmptyList_Throws)
        {
            DoublyLinkedList<int> list;

            auto attempt = [&list]() { list.popBack(); };

            Assert::ExpectException<std::out_of_range>(attempt);
        }

        TEST_METHOD(PopFront_OnEmptyList_Throws)
        {
            DoublyLinkedList<int> list;

            auto attempt = [&list]() { list.popFront(); };

            Assert::ExpectException<std::out_of_range>(attempt);
        }

        TEST_METHOD(InsertAt_IndexBeyondSize_Throws)
        {
            DoublyLinkedList<int> list = { 1, 2 };

            auto attempt = [&list]() { list.insertAt(7, 100); };

            Assert::ExpectException<std::out_of_range>(attempt);
        }

        TEST_METHOD(DeleteAt_IndexOutOfRange_Throws)
        {
            DoublyLinkedList<int> list = { 1, 2 };

            auto attempt = [&list]() { list.deleteAt(2); };

            Assert::ExpectException<std::out_of_range>(attempt);
        }
    };
}
