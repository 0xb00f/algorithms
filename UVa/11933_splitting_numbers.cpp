#include <iostream>
#include <bitset>

#define SIZE 32

using namespace std;

int main(void)
{
	int num = 1;
	while(1)
	{
		cin >> num;
		if(!num) break;
		bitset<SIZE> bits(num), a(num), b(num);
		int i, count=1;
		for(i=bits._Find_first(); i < SIZE; i=bits._Find_next(i))
		{
			if(count % 2)
			{
				a.flip(i);
			}
			else
			{
				b.flip(i);
			}
			count++;
		}
		cout << b.to_ulong() << " " << a.to_ulong() << "\n";
	}
	return 0;
}
