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

// void print_plus_1(int puls_num)
// {
// 	print(puls_num + 1);
// }

// void print_twice(int twice_num)
// {
// 	print(twice_num * 2);
// }

int return_array_item(int a[1], int b){
	return a[b];
}

void main()
{
	// int a = 10, c;
	int arr[3] = {1, 2, 3};
	// int b = 1;
	// int i;
	// c = 10;
	// for(i = 0; i < a; i++)
	// {
	// 	if(i < 5)
	// 	{
	// 		c--;
	// 		print(c);
	// 	}
	// }
	// while(c)
	// {
	// 	c--;
	// 	print(a);
	// }

	// print(arr[2] * 3);
	// b++;
	// print(b);
	// b = input();
	// print(b);

	// print_plus_1(a + 1);
	// print_plus_1(arr[2]);
	// print_plus_1(arr[2] + 1);

	// print_plus_1(arr[2] + 1);
	// print_plus_1(arr[2] + 1);
	// print_plus_1(arr[arr[0]]);

	// print_twice(a + 2);
	// print_twice(arr[2] * 3);
	// print_twice(a + 1);

	// print_twice(a + 2);
	// print_twice(arr[2] * 3);
	// print_twice(a + 1);

	// print_twice(arr[2]);
	// print(a);
	// print(get_sign(a));
	// a = -1;
	// print(get_sign_simple(a));

	// print_plus_1(arr[1]);
	print(return_array_item(arr, 1));
}

