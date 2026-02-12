Pointers

int MyInt = 5;
int* ptrMyInt = &MyInt; pointer to MyInt  * means it is pointer & means memory adress

int newInt = *ptrMyInt + 10; (15) * is dereferencing so it becomes MyInt instead of adress

references

int MyInt = 5;
int& RefMyInt = MyInt;

RefMyInt and MyInt are now linked

porpose potentials

instead of parsing full copies of the memorie parse the original memory adress

