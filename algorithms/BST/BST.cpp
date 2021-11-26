#include <iostream>

struct data {

    std::string name;
    int value{0};

    data() {}
    data(std::string name_, int value_) {
        name = name_;
        value = value_;
    }
    friend std::ostream &operator<<(std::ostream &os, const data &dt) {
        os << "Name: " << dt.name << " , "
           << "Value: " << dt.value;
        return os;
    }
};

int cmp(data obj1, data obj2) {
    if (obj1.value > obj2.value) {
        return 1;
    } else if (obj1.value < obj2.value) {
        return 0;
    }
    return -1;
}

template <class T>
class BST {
public:
    int insert(BST *root, T object) {
        if (root == nullptr) {
            return 0;
        }
        BST *temp = root;
        BST *obj = new BST(object);
        BST *parent = nullptr;
        while (temp != nullptr) {

            if (object == temp->data) {
                delete obj;
                return 0;
            }
            parent = temp;
            (object > temp->data) ? temp = temp->right : temp = temp->left;
        }
        temp = new BST(object);
        temp->parent = parent;
        (temp->data > temp->parent->data) ? temp->parent->right = temp : temp->parent->left = temp;
        return 1;
    }

    //use for diffrent than in built variables e.g data structures
    int insert(BST *root, T object, int (*cmp)(T obj1, T obj2)) {
        if (root == nullptr) {
            return 0;
        }
        BST *temp = root;
        BST *obj = new BST(object);
        BST *parent = nullptr;
        while (temp != nullptr) {

            if (cmp(object, temp->data) == -1) {
                delete obj;
                return 0;
            }
            parent = temp;
            (cmp(object, temp->data) == 1) ? temp = temp->right : temp = temp->left;
        }
        temp = new BST(object);
        temp->parent = parent;
        (cmp(temp->data, temp->parent->data) == 1) ? temp->parent->right = temp : temp->parent->left = temp;
        return 1;
    }

    BST *find(BST *root, T object) {
        if (root == nullptr) {
            return nullptr; //pusto
        }
        BST *temp = root;

        while (temp != nullptr) {

            if (object == temp->data) {
                return temp;
            }

            object > temp->data ? temp = temp->right : temp = temp->left;
        }
        return nullptr;
    }

    //use for diffrent than in built variables e.g data structures
    BST *find(BST *root, T object, int (*cmp)(T obj1, T obj2)) {
        if (root == nullptr) {
            return nullptr; //pusto
        }
        BST *temp = root;

        while (temp != nullptr) {
            if (cmp(object, temp->data) == 1) {
                temp = temp->right;
            } else if (cmp(object, temp->data) == 0) {
                temp = temp->left;
            } else {
                return temp;
            }
        }
        return nullptr;
    }

    int delete_(BST *root, T object) {
        BST *obj = find(root, object);

        if (obj != nullptr) {

            //jest solo
            if (obj->right == nullptr && obj->left == nullptr) {

                //tylko korzen
                if (obj->parent == nullptr) {
                    delete obj;
                    root = nullptr;
                    return 1;
                }

                if (obj->parent->right == obj) {
                    obj->parent->right = nullptr;
                    delete obj;
                    obj = nullptr;
                    return 1;
                } else {
                    obj->parent->left = nullptr;
                    delete obj;
                    obj = nullptr;
                    return 1;
                }
            }

            //ma obu potomków
            if (obj->right != nullptr && obj->left != nullptr) {
                BST *temp = obj->left;
                //szukam największego w lewej stronie drzewa
                while (temp->right != nullptr) {
                    temp = temp->right;
                }
                T data = temp->data;
                delete_(root, data);
                obj->data = data;
                return 1;

            }

            //ma jedenego potomka
            else {
                BST *child;
                child = (obj->left != nullptr) ? obj->left : obj->right;
                //obj to korzen
                if (obj->parent == nullptr) {
                    root = child;
                    delete obj;
                    obj = nullptr;
                    return 1;
                }

                if (obj->parent->left == obj) {
                    obj->parent->left = child;
                    child->parent = obj->parent;
                    delete obj;
                    obj = nullptr;
                    return 1;
                } else {
                    obj->parent->right = child;
                    child->parent = obj->parent;
                    delete obj;
                    obj = nullptr;
                    return 1;
                }
            }
        }

        else {
            return 0;
        }
    }

    //use for diffrent than in built variables e.g data structures
    int delete_data_structure(BST *root, T object) {
        BST *obj = find(root, object, cmp);

        if (obj != nullptr) {

            //jest solo
            if (obj->right == nullptr && obj->left == nullptr) {

                //tylko korzen
                if (obj->parent == nullptr) {
                    delete obj;
                    root = nullptr;
                    return 1;
                }

                if (obj->parent->right == obj) {
                    obj->parent->right = nullptr;
                    delete obj;
                    obj = nullptr;
                    return 1;
                } else {
                    obj->parent->left = nullptr;
                    delete obj;
                    obj = nullptr;
                    return 1;
                }
            }

            //ma obu potomków
            if (obj->right != nullptr && obj->left != nullptr) {
                BST *temp = obj->left;
                //szukam największego w lewej stronie drzewa
                while (temp->right != nullptr) {
                    temp = temp->right;
                }
                T data = temp->data;
                delete_data_structure(root, data);
                obj->data = data;
                return 1;

            }

            //ma jedenego potomka
            else {
                BST *child;
                child = (obj->left != nullptr) ? obj->left : obj->right;
                //obj to korzen
                if (obj->parent == nullptr) {
                    root = child;
                    delete obj;
                    obj = nullptr;
                    return 1;
                }

                if (obj->parent->left == obj) {
                    obj->parent->left = child;
                    child->parent = obj->parent;
                    delete obj;
                    obj = nullptr;
                    return 1;
                } else {
                    obj->parent->right = child;
                    child->parent = obj->parent;
                    delete obj;
                    obj = nullptr;
                    return 1;
                }
            }
        }

        else {
            return 0;
        }
    }

    void preorder(BST *root) {
        if (root == nullptr)
            return;
        std::cout << root->data << std::endl;
        preorder(root->left);
        preorder(root->right);
    }

    void inorder(BST *root) {
        if (root == nullptr)
            return;

        inorder(root->left);
        std::cout << root->data << std::endl;
        inorder(root->right);
    }

    int height(BST *root) {
        if (root == nullptr)
            return 0;

        int left = height(root->left);
        int right = height(root->right);
        if (left > right)
            return left + 1;
        else
            return right + 1;
    }

    void chop_tree(BST *root) {
        if (root == nullptr)
            return;

        chop_tree(root->left);
        chop_tree(root->right);

        delete root;
        root = nullptr;
    }

    int print(BST *root) {

        if (root == nullptr)
            return 0;
        std::cout << "}\n";
        std::cout << "Wysokosc: " << height(root) << "\n\n";
        printful(root);
        std::cout << "}\n";
        return 0;
    }

    BST(T obj) { data = obj; }
    BST(){};

private:
    void printful(BST *root) {

        if (root != nullptr) {

            std::cout << "Wezel: " << root->data;
            if (root->parent != nullptr) {
                std::cout << " [Rodzic: " << root->parent->data << " | ";
            } else {
                std::cout << " [Rodzic: Brak  | ";
            }
            if (root->left != nullptr) {
                std::cout << "Lewy potomek: " << root->left->data << " | ";
            } else {
                std::cout << "Lewy potomek: Brak "
                          << " | ";
            }
            if (root->right != nullptr) {
                std::cout << "Prawy potomek: " << root->right->data << " ] " << std::endl
                          << std::endl;
            } else {
                std::cout << "Prawy potomek: Brak ] " << std::endl
                          << std::endl;
            }

            printful(root->left);

            printful(root->right);
        }
    }
    T data{};
    BST *root{nullptr};
    BST *parent{nullptr};
    BST *left{nullptr};
    BST *right{nullptr};
};
