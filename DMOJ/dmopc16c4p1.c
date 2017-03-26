#include <stdio.h>

int T;
long long l;

int main() {
	for(scanf("%d", &T);T;T--){
		scanf("%lld", &l);
		putchar_unlocked(l & (l - 1) ? 'F':'T');
		putchar_unlocked('\n');
	}
}
