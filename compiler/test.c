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

void print_plus_1(int input)
{
	print(input + 1);
}
void print_twice(int input)
{
	print(input * 2);
}

void main()
{
	int a = 1;
	int arr[3] = {1, 2, 3};
	print(arr[2] * 3);
	print_twice(arr[2] * 3);
	//error
	// print_plus_1(arr[arr[0]]);
	//error

	print_plus_1(a);
	// print(get_sign(a));
	// a = -1;
	// print(get_sign_simple(a));

	// print_plus_1(arr[1]);
	// print_twice(arr[2]);
}

