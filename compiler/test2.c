// void lyh()
// {
// 	int a;
// 	a = 1;
// }

// void hlh(int aa)
// {
// 	int a[3] = {1, 2, 3};
// 	print(a[aa]);
// }

// void main(){
// 	// hlh(1);
// 	int a[3] = {1,2,3};
// 	print(a[1]);
// }

// int get_sign_simple(int a)
// {
// 	int result;
// 	if(a > 0)
// 	{
// 		result = 1;
// 	}
// 	else if(a == 0)
// 	{
// 		result = 0;
// 	}
// 	else
// 	{
// 		result = -1;
// 	}
// 	return result;
// }

// int get_sign(int a)
// {
// 	if(a > 0)
// 	{
// 		return 1;
// 	}
// 	else if(a == 0)
// 	{
// 		return 0;
// 	}
// 	else
// 	{
// 		return -1;
// 	}
// }

// struct simple_struct
// {
// 	int key;
// 	int value;
// }
// simple_object_0;

// struct simple_struct simple_object_1;

// struct complex_struct
// {
// 	int key;
// 	struct simple_struct value;
// }
// complex_object_0;

// struct complex_struct complex_object_1;


// void print_plus_1(int input);
// void print_twice(int input);

void print_plus_1(int puls_num)
{
	print(puls_num + 1);
}

// void print_twice(int twice_num)
// {
// 	print(twice_num * 2);
// }

void main()
{
	int a = 10, c;
	int arr[3] = {1, 2, 3};
	int b = 1;
	int i;
	c = 0;
	for(i = 0; i < 10; i++)
	{
		print(i);
		if(i < 5)
		{
			c = c + 1;
			print(a);
		}
	}
	// each adjacent 2 lines -> error
	// print_twice(a + 2);
	// print_twice(arr[2] * 3);
	// print_twice(a + 1);

	// print_twice(arr[2]);
	// print(get_sign(a));
	// a = -1;
	// print(get_sign_simple(a));

	// print_plus_1(arr[1]);
}

