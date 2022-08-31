# C++을 이용해서 만든 도서관리 콘솔 프로그램
## 개발기간
2021/09/20 ~ 2021/09/25 (5일)

## 개발계기
> C++에 대해 이론공부만 하다, 실제로 프로그램을 만들어봐야겠다 싶어서 제작하게 됨

## 개발 환경
Visual Studio2015환경에서 MySQL WorkBench 8.0를 연동하여 개발

## cpp파일과 헤더파일

![구조](https://user-images.githubusercontent.com/82512951/187675257-5175a289-4f63-4a95-a7d5-3db9b18dcfb3.JPG)

## MySQL

### MySQL 2개의 tables
![Mysql2개의테이블](https://user-images.githubusercontent.com/82512951/187692417-c4bf7ed6-9844-4f86-b08d-dd227ca1818e.JPG)
#### 책의정보가 등록된 book table과 user table

### user table
![user셀렉트](https://user-images.githubusercontent.com/82512951/187692201-536c9a64-b36a-4d5c-b9d6-d90b829aa173.JPG)
### book table
![book셀렉트](https://user-images.githubusercontent.com/82512951/187692860-ec6f1822-25cf-41cc-b238-6dc25e49a912.JPG)


## 구현

### 0. 초기화면
![초기화면](https://user-images.githubusercontent.com/82512951/187695358-77d0291f-b24f-4ce1-aeac-b8d4c77f4414.JPG)


### 1. 로그인

#### 1-1 유저 로그인
> 1을 입력하고 아이디를 입력한 후 , 비밀번호를 입력하라고 나온다.

#### 아이디 혹은 비밀번호를 틀리게 입력할 경우
![올바르지않은아이디와비밀번호입력](https://user-images.githubusercontent.com/82512951/187694273-1ad4b541-3b6f-4f94-b8a3-0d45f2b9c868.JPG)

#### 제대로 테이블에 등록된 아이디와 비밀번호를 입력하면 로그인 성공
![로그인성공](https://user-images.githubusercontent.com/82512951/187694414-daca25b4-b56c-4f5c-b1f2-466a7e90e74d.JPG)

#### 1-2 관리자 로그인
> 관리자로 로그인 했을 경우 book테이블에 책을 등록할 수 있다.

![관리자로등록](https://user-images.githubusercontent.com/82512951/187695100-6c437700-9e5d-47f6-a88b-51cbe153c502.JPG)
#### 등록 확인
![책등록mysql](https://user-images.githubusercontent.com/82512951/187695266-5397dd00-25d7-4f05-8d97-936c182ce5b6.JPG)


#### 2. 회원가입
> 등록된 회원이아니라면 회원가입을 할 수 있다.

![회원가입](https://user-images.githubusercontent.com/82512951/187694595-7b0e2018-58d3-4f03-b8e3-7a2eb2420e48.JPG)

#### 아이디와 비밀번호 생년월일을 입력해 회원가입을 완료하면 MySQL의 user테이블에 추가
![user가추가됨](https://user-images.githubusercontent.com/82512951/187694907-2741df04-f2f3-4aeb-abaf-93d79805031a.JPG)

#### 3. 대여하기 
> MySQL에 등록되어 있는 책을 대여할 수 있다.

#### 책 목록이 먼저 나오고, 
![책목록이나온다](https://user-images.githubusercontent.com/82512951/187695834-e6d15f55-792c-4578-b3fd-2f54038a2277.JPG)
#### 대여를 하면 대여가 완료된다. (개수가 0이하면은 대여가 불가능하게 설계)
![대여완료](https://user-images.githubusercontent.com/82512951/187695958-4a87c07a-8147-47d3-8c55-76b65e089273.JPG)

#### 메뉴에서 도서목록을 선택하여 보면 대여한 책의 개수가 줄어든 것을 알 수 있다.
![대여한거개수줄어든다](https://user-images.githubusercontent.com/82512951/187696094-11dd065b-86ce-4e36-8f08-38f719417d75.JPG)
#### MySQL에서도 개수가 줄어든 것을 알 수 있다.
![mysql도줄어든다](https://user-images.githubusercontent.com/82512951/187696105-29d88cfc-58b8-499a-97e2-8255450d049a.JPG)

#### 메뉴에서 2번을 눌러 대여목록을 보면 정상적으로 대여 된 것을 볼 수 있다.

![현재대여목록을볼수있다](https://user-images.githubusercontent.com/82512951/187697090-7c962f78-6bfd-4301-b8ee-9793e09d28d8.JPG)

#### 4. 반납하기
> 대여한 책을 반납할 수 있다.

#### 현재 대여중인 책 목록이 나오고 반납을 할건지 안할건지 선택한 후 , 반납한다.

![책반납구현](https://user-images.githubusercontent.com/82512951/187697403-b1585cbf-0980-45ef-bb8e-7497b187fd1b.JPG)

#### MySQL에서도 반납한 책의 개수가 증가한다.

![mysql도증가](https://user-images.githubusercontent.com/82512951/187697493-29ff2dfb-0215-47c2-ab8d-4140e5b9f107.JPG)

#### 콘솔창에서도 개수가 증가한다.

![책의개수가다시증가](https://user-images.githubusercontent.com/82512951/187697638-4663bdde-1861-4c3f-812b-24c766d448dd.JPG)

#### 5. 종료
> 로그아웃을 한 뒤, Stop을 선택하면 프로그램이 종료된다.


![종료](https://user-images.githubusercontent.com/82512951/187697884-aa0ee2be-fed8-4f03-9cdd-a5d7e08b6c0e.JPG)







