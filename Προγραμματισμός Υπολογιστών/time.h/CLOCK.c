//clock.c:Ektuposi tou xronou apo tin arxi tou programmatos mas
#include <stdio.h>
#include <time.h>

main()
{
	int i;
	clock_t t;
	t=clock();
	printf("Kikloi: %d\n",t);
	printf("Kikloi ana deuterolepta: %ld\n",CLOCKS_PER_SEC);
	printf("Xronos apo tin enarksi: %f",(float)t/CLOCKS_PER_SEC);
}
