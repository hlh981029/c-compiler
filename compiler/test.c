void main()
{
    int hun, ten, ind, n, d, aaa;

    for (n = 100; n<1000; n++)
    {
        hun = n / 100;
        ten = (n - hun * 100) / 10;
        ind = n % 10;
        aaa = hun * hun * hun + ten * ten * ten + ind * ind * ind;
        if (n == aaa)
        {
            d = n;
        }
    }
}