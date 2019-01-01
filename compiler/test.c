void lyh()
{
	int a;
	a = 1;
}

void hlh(int aa)
{
	int a[3] = {1, 2, 3};
	int i;
	i=1;
	a[1]=0;
	i=a[2];
	a[2]=a[1];
}

void main(){
	hlh(1);
}