## reader writer problem
###1. reader-writer  문제란 무엇인가

#####&nbsp; 고전적인 프로세스 동기화 문제 중 하나이다. reader와 writer는 자원을 공유하지만, reader가 자원을 읽기만 할 수 있지만 writer는 자원을 갱신할 수도 있기 때문에 여러 reader가 critical section(임계 구역)에 들어갈 수 있는 반면 writer는 한번에 한 writer만 임계구역에 도달해야 한다. 

&nbsp;&nbsp;&nbsp;다음은 reader-writer 문제에 대한 전제이다.
 - 하나 이상의 writer가 임계구역에 도달하면 공유자원의 일관성이 무너질 수 있기 때문에 임계구역에는 한번에 하나의 writer만 들어가야 한다.
 - writer가 공유자원에 대해 접근할 준비가 되지 않았다면, reader가 지체하지 않고 임계구역에 들어갈 수 있게 해야 한다.
 - reader는 중복으로 임계구역에 들어갈 수 있다. writer가 임계구역에 들어오지 않으면 reader는 최대한 많은 중복을 허용해야 한다.
 
 
###2. Reader 선호 알고리즘

#####&nbsp; 이 문제에 대해 널리 알려진 문제 해결법이다. 현재 임계구역에 들어가 있는 reader의 수를 변수로 count를 하여 count가 0이 되면 그 때 writer에게 기회를 준다. 그렇지만 이 경우에는 reader의 스레드가 일정 이상 많이 생성이 될 경우, writer의 기회가 주어지지 않게 될 수도 있다. 그렇기 때문에 reader 선호라 불린다. 

 
