#include <iostream>
using namespace std;

inline int pdt(int x,int y,int MOD) {
    int ret;
    __asm__ __volatile__ ("\tmull %%ebx\n\tdivl %%ecx\n":"=d"(ret):"a"(x),"b"(y),"c"(MOD));
    return ret;
}

int PDT(int x,int y,int mods) { //����Ż����׳������ܲ��þ������ã���֪��ʲô����»��ܱ���һ��û��
    int ret;
    __asm__ __volatile__ ("\tmull %%ebx\n\tdivl %%ecx\n":"=d"(ret):"a"(x),"b"(y),"c"(mods));
    return ret;
}

int main()
{
    cout << PDT(10 , 10 , 1);
}