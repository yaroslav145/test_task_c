#include <iostream>

using namespace std;

template<typename T>
class Node
{
    public:
        Node* next;
        T data;

        Node(T data)
        {
            this->data = data;
            this->next = nullptr;
        }
};


template<typename T>
class MyList
{
    private:
        Node<T>* root = nullptr;
        Node<T>* lastNode = nullptr;
        int listSize = 0;

    public:
        ~MyList()
        {
            clear();
        }


        void push_back(T data)
        {
            Node<T>* temp = new Node<T>(data);

            if(root == nullptr)
            {
                root = temp;
            }
            else
            {
                lastNode->next = temp;
            }

            lastNode = temp;

            listSize++;
        }


        void pop_front()
        {
            if(root == nullptr)
                return;

            Node<T>* temp = root->next;

            delete root;

            root = temp;

            listSize--;
        }


        T& operator[](const int id)
        {
            Node<T>* p = root;

            for(int i = 0; p != nullptr; ++i)
            {
                if(i == id)
                    return p->data;

                p = p->next;
            }
        }


        int size()
        {
            return listSize;
        }


        void clear()
        {
            Node<T>* temp;

            while(root != nullptr)
            {
                temp = root;
                root = root -> next;
                delete temp;
                listSize = 0;
            }
        }
};

int main()
{
    MyList<int> list;

    for(int i = 0; i < 50; ++i)
    {
        list.push_back(i);
    }

    for(int i = 0; i < 50; ++i)
    {
        //list.pop_front();
    }

    for(int i = 0; i < 50; ++i)
    {
       cout << list[i] << endl;
    }

    return 0;
}
