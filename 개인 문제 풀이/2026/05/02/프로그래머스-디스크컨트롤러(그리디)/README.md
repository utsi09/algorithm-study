https://school.programmers.co.kr/learn/courses/30/lessons/42627?gad_source=1&gad_campaignid=23716289893&gbraid=0AAAAAC_c4nASgsGmGZemkdajd8H1Y7WOy&gclid=CjwKCAjwwdbPBhBgEiwAxBRA4aC_2SckMbmY0c86FxV1xmtu6AXg33ZVt9TOHRo0loH5o-GkET1KKBoC9E8QAvD_BwE

---

전 문제와 유사하게 우선순위 큐와 그리디를 사용하는데

다른점은 이전에는 pq에 한번 넣고나면 무게값은 필요없어서 int형 pq였다면 이번엔 소요시간과 요청시간 둘다 필요하기 때문에 pair 타입 pq를 사용했다

또 처음 짤때 for을 딱 n 만큼 반복했는데 그랬더니 공백시간은 아무것도 안하고 흘러가서 공백시간이 있는 tc는 오답처리 되었다

while로 완료된 작업이 n보다 작은 동안 반복하게하고

pq가 비었을땐 t를 다음 work 시간대로 이동시켜서 해결하였다
