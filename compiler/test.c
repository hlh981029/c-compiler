struct {
	int a1,a2;
	int a3;
}b;


void main() {
	int a;
	a = input();
	b.a1 = 1;
	b.a2 = b.a1;
	b.a3 = a;
	print(b.a1);
	print(b.a2);
	print(b.a3);
	
}