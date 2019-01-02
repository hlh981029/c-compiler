void main()
{
	int a[3] = {1, 2, 3};
	int i;
	i=1;
	a[1]=0;
	a=a[2];
	a[2]=a;
}