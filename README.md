# Soccer Boots Recommender - Bayesian Classifier

나이브 베이즈 분류기(Naive Bayes Classifier)를 기반으로 축구 선수의 스탯과 성향을 입력받아 최적의 축구화를 추천하는 REST API 서버입니다.

---

## 프로젝트 구조

```
soccer_boots_bayes_project/
├── main.cpp                          # 서버 부트스트랩 진입점
│
├── data/
│   ├── SoccerPlayerBoots.h/.cpp      # 선수 데이터 도메인 모델
│
├── reader/
│   ├── SoccerPlayerBootsDataCsvReader.h/.cpp  # CSV 파일 로더
│   └── rapidcsv.h                    # CSV 파싱 라이브러리
│
├── model/
│   ├── SoccerBootsBayesianModel.h/.cpp    # 학습된 모델 데이터 컨테이너
│   ├── SoccerBootsBayesianTrainer.h/.cpp  # 베이즈 모델 학습기 (fit)
│   └── SoccerBootsRecommender.h/.cpp     # 추천 예측기 (predict)
│
├── api/
│   ├── ApiServer.h/.cpp               # Crow HTTP 서버 래퍼
│   └── RecommendationController.h/.cpp # /recommend/soccer-boots 라우트 핸들러
│
├── datasets/
│   ├── germany-bundesliga-players_boots.csv
│   ├── premier-league-players_boots.csv
│   └── spain-laliga-players_boots.csv
│
└── Crow/                             # Crow C++ HTTP 프레임워크
```

---

## 동작 원리

```
CSV 데이터 로드
    └─> SoccerBootsBayesianTrainer.fit()
            ├── 사전 확률 계산  (P(boots))
            ├── 수치 우도 계산  (가우시안 분포: 평균, 분산)
            └── 범주 우도 계산  (텍스트/리스트 빈도)
                    └─> SoccerBootsBayesianModel (학습 결과 보관)
                            └─> SoccerBootsRecommender.predict()
                                    └─> log P(boots | 입력) 최대값 → 추천 축구화
```

### 학습에 사용하는 피처

| 구분 | 예시 |
|------|------|
| **수치형** | 나이, 키, 골, 어시스트, 평점, 태클, 패스 성공률 등 (30개) |
| **텍스트형** | 국적, 포지션, 등번호 등 |
| **리스트형** | 포지션 목록, 강점, 약점, 플레이 스타일 |

---

## 빌드 환경

| 항목 | 버전 |
|------|------|
| C++ | C++20 |
| CMake | 3.29 이상 |
| HTTP 프레임워크 | [Crow](https://github.com/CrowCpp/Crow) |
| ASIO | Homebrew (`asio`) |
| 빌드 도구 | Ninja |

### 의존성 설치 (macOS)

```bash
brew install asio
```

---

## 빌드 방법

```bash
# 1. 프로젝트 루트에서 빌드 디렉토리 이동
cd cmake-build-debug

# 2. CMake 구성 (최초 1회 또는 CMakeLists.txt 변경 후)
cmake ..

# 3. 빌드
cmake --build . --target soccer_boots_bayes_project
```

---

## 실행 방법

> 데이터셋 경로가 `../datasets/`로 설정되어 있으므로 반드시 `cmake-build-debug/` 디렉토리에서 실행해야 합니다.

```bash
cd cmake-build-debug
./soccer_boots_bayes_project
```

서버 시작 시 출력 예시:
```
(2026-02-17) [INFO] Crow/1.0 server is running at http://0.0.0.0:8080
```

서버 종료: `Ctrl + C`

---

## API 명세

### `POST /recommend/soccer-boots`

선수 스탯을 입력받아 가장 적합한 축구화와 확률을 반환합니다.

#### 요청

```http
POST /recommend/soccer-boots
Content-Type: application/json
```

```json
{
  "textInputs": [
    {"key": "player_nationality", "value": "Brazil"}
  ],
  "numInputs": [
    {"key": "player_age",    "value": 25},
    {"key": "goals",         "value": 15},
    {"key": "assists",       "value": 8},
    {"key": "rating",        "value": 7.5}
  ],
  "listInputs": [
    {"key": "player_positions", "value": ["Forward"]},
    {"key": "strengths",        "value": ["Speed", "Dribbling"]},
    {"key": "weaknesses",       "value": ["Defensive contribution"]},
    {"key": "player_style",     "value": ["Likes to cut inside"]}
  ]
}
```

#### 응답

```json
{
  "boots": "X Speedportal.1",
  "prob": 0.87
}
```

| 필드 | 타입 | 설명 |
|------|------|------|
| `boots` | string | 추천 축구화 이름 |
| `prob` | number | 추천 확률 (0.0 ~ 1.0) |

#### 에러 응답

| 상태 코드 | 원인 |
|-----------|------|
| `400` | 요청 body가 유효한 JSON이 아닌 경우 |

#### CORS

모든 오리진(`*`)에 대해 CORS를 허용합니다. 프론트엔드에서 직접 호출 가능합니다.

```http
OPTIONS /recommend/soccer-boots  → 200 OK
```

---

## curl 테스트 예시

```bash
curl -X POST http://localhost:8080/recommend/soccer-boots \
  -H "Content-Type: application/json" \
  -d '{
    "textInputs": [
      {"key": "player_nationality", "value": "Brazil"}
    ],
    "numInputs": [
      {"key": "player_age", "value": 25},
      {"key": "goals",      "value": 20}
    ],
    "listInputs": [
      {"key": "player_positions", "value": ["Forward"]},
      {"key": "strengths",        "value": ["Speed", "Finishing"]}
    ]
  }'
```
