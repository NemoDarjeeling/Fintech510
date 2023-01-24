def series18(n):
    """Implement your function below"""
    a = -n**2
    b = 1
    for i in range (3*n):
        print(a, end=' ')
        a += b
        b += 2
