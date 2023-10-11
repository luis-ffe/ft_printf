
#include <unistd.h>
#include <stdio.h>

int	ft_putnbr_fd(long long n, int fd)
{
	long long    num;
	int     x;
	
	x = 0;
	num = n;
	if (num < 0)
	{
			num *= -1;
			x += write (fd, "-", 1);
	}
	if (num < 10)
	{
		num += '0';
		return(x + write (fd, &num, 1));
	}
	if(num >= 10)
	{
		x += ft_putnbr_fd(num / 10, fd);
		x += ft_putnbr_fd(num % 10, fd);
	}
	return (x);
}

int main()
{
    int x = -9999999;
    int y = ft_putnbr_fd(x, 1);
    printf("\n%d\n", y);
}