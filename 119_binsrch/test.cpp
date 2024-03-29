int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low > high) {
    exit(EXIT_FAILURE);
  }
  if (low == high) {
    return low;
  }
  if (f->invoke(low) >= 0) {
    return low;
  }
  if (f->invoke(high - 1) <= 0) {
    return high - 1;
  }
  high = high - 1;
  int mid;
  int guess;
  while (low <= high) {
    mid = (low + high) / 2;
    printf("mid=%d\n", mid);
    guess = f->invoke(mid);
    printf("f(mid)=%d\n", guess);
    if (guess == 0) {
      return mid;
    }
    if (guess > 0) {
      high = mid - 1;
      printf("high=%d\n", high);
    }
    else {
      low = mid + 1;
      printf("low=%d\n", low);
    }
  }
  if (guess > 0) {
    return mid - 1;
  }
  return mid;
}