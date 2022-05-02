using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

namespace DataStructuresCS
{
    class LinkedList<T> : IEnumerable
    {
        Node head = null;
        int length = 0;

        /* ====== Private helpers ====== */
        private class Node
        {
            internal T value;
            internal Node next;
            public Node(T data) => this.value = data;
        }

        private Node GetLastNode()
        {
            for (Node retVal = head; retVal != null; retVal = retVal.next)
            {
                if (retVal.next == null)
                    return retVal;
            }

            throw new InvalidOperationException("Sequence contains no elements");
        }
        private Node GetAt(int index)
        {
            if (length < index) {
                IndexOutOfRangeException indexOutOfRangeException = new($"Length: {length}. Requested: {index}");
                throw indexOutOfRangeException;
            }


            Node retVal = head;
            for (int i = 1; i <= index; ++i) {
                retVal = retVal.next;
            }

            return retVal;
        }
        private void SetAt(int index, T value)
        {
            Node retVal = head;
            for (int i = 0; i < index; ++i)
            {
                retVal = retVal.next;
            }

            retVal.value = value;
        }



        /* ========= Overloads ========= */
        public IEnumerator GetEnumerator()
        {
            Node current = head;
            while (current != null)
            {
                yield return current.value;
                current = current.next;
            }
        }

        public T this[Index index]
        {
            get => GetAt(index.IsFromEnd ? this.length - index.Value : index.Value).value;
            set => SetAt(index.IsFromEnd ? this.length - index.Value : index.Value, value);
        }


        /* ====== Public functions ====== */
        public LinkedList() { }
        public LinkedList(IEnumerable<T> collection)
        {
            foreach (var item in collection)
            {
                Insert(item);
            }
        }

        public int Length{ get => length; }

        public void Insert(T data)
        {
            ++length;

            if (head == null)
                head = new Node(data);
            else
                GetLastNode().next = new Node(data);
        }
        public void InsertAt(Index index, T data)
        {
            int idx = index.IsFromEnd ? length - index.Value : index.Value;
            if (length <= idx)
            {
                IndexOutOfRangeException indexOutOfRangeException = new($"Max index: {length-1}. Requested index: {idx}");
                throw indexOutOfRangeException;
            }

            if (idx == 0)
            {
                Node temp = head;
                head = new Node(data)
                {
                    next = temp
                };
            }
            else
            {
                Node nodeAt = GetAt(idx-1);
                Node temp = nodeAt.next;
                nodeAt.next = new Node(data)
                {
                    next = temp
                };

            }
            ++length;

        }

        public void Clear()
        {
            head = null;
            length = 0;
        }

        public void Remove(T data)
        {
            for(Node current = head, previous = null; current != null; previous = current, current = current.next)
            {
                if (Equals(current.value, data))
                {
                    if (previous == null)
                        head = current.next;
                    else
                        previous.next = current.next;

                    --length;
                    return;
                }
            }
            ArgumentException argumentException = new($"Argument: {data} not found in the collection!");
            throw argumentException;
        }
        public void RemoveAt(Index index)
        {
            int idx = index.IsFromEnd ? length - index.Value : index.Value;
            if (length <= idx)
            {
                IndexOutOfRangeException indexOutOfRangeException = new($"Max index: {length - 1}. Requested index: {idx}");
                throw indexOutOfRangeException;
            }

            if (idx == 0)
            {
                head = head.next;
            }
            else
            {
                Node nodeAt = GetAt(idx - 1);
                nodeAt.next = nodeAt.next.next;

            }
            --length;
        }


        public bool Contains(T data)
        {
            for (Node current = head; current != null; current = current.next)
            {
                if (Equals(current.value, data))
                    return true;
            }
            return false;
        }
        public int IndexOf(T data)
        {
            int index = 0;
            for (Node current = head; current != null; current = current.next)
            {
                if (Equals(current.value, data))
                    return index;
                index++;
            }

            ArgumentException argumentException = new($"Argument: {data} not found in the collection!");
            throw argumentException;
        }

        public string AsString()
        {
            var sbuilder = new System.Text.StringBuilder();

            for (Node current = head; current != null; current = current.next)
                sbuilder.Append(current.value + " ");

            return sbuilder.ToString().Trim();
        }
        public T[] AsArray()
        {
            T[] retVal = new T[length];
            int index = 0;

            for (Node current = head; current != null; current = current.next)
                retVal[index++] = current.value;

            return retVal;
        }
    }
}
