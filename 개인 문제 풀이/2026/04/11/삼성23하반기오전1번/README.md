https://www.codetree.ai/ko/frequent-problems/samsung-sw/problems/royal-knight-duel/submissions?page=1&page_size=20

---
잘못한 점

재귀 내에서 하나라도 false 나면 이동을 취소해야되는데 일일히 재귀마다 이동을 적용한 부분 (중요 포인트)

  -> 밀려날 기사 번호만 벡터에 저장
    -> 한 기사의 여러부분을 밀수있으므로 벡터에 중복을 제거하기 위해 unique를 적용함  (중요 포인트)

