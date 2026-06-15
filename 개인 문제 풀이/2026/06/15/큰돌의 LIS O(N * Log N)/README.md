```cpp
  auto lowerPos = lower_bound(lis, lis+len, num);
  if(*lowerPos==0) len++;
  *lowerPos = num;
```

lower_bound 함수를 이용해 크거나 같은 곳을 가르키는 포인터를 만든다

만약 크거나 같은게 없다면 새로운 큰 녀석이기 때문에 길이를 1 더하고

있든없든 그자리에 num을 넣는다 
