struct {
	int a1,a2;
	int a3;
}b;
void main() {
	b.a1 = 1;
	b.a2 = b.a1;
	b.a3 = 0;
	print(b.a1);
	print(b.a2);
	print(b.a3);
}