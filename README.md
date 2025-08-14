# 🏴‍☠️ UE5 VR 불멸의 이순신 (Immortal Yi Sun-sin)

![Unreal Engine 5](https://img.shields.io/badge/Unreal%20Engine-5.1-blue.svg?style=flat-square&logo=unreal-engine)
![VR](https://img.shields.io/badge/Platform-VR-red.svg?style=flat-square)
![Development Status](https://img.shields.io/badge/Status-Development-yellow.svg?style=flat-square)

조선 시대 명장 **이순신**의 이야기를 VR로 체험하는 몰입형 역사 교육 프로젝트입니다.

## 📋 프로젝트 개요

이 프로젝트는 Unreal Engine 5를 기반으로 제작된 VR 체험 콘텐츠로, 사용자가 이순신의 업적과 조선 수군의 역사를 직접 체험할 수 있도록 설계되었습니다.

### 🎯 주요 특징

- **🎮 VR 몰입 체험**: OpenXR 및 Oculus VR 지원
- **🏛️ 역사적 재현**: 조선 시대 배경과 전투 상황 구현
- **🧩 인터랙티브 요소**: 퍼즐, 갤러리, 무기 체험 등
- **🎬 시네마틱 경험**: 시퀀스를 통한 스토리텔링
- **🔊 몰입형 오디오**: ResonanceAudio를 활용한 공간 음향

## 🛠️ 기술 스택

### 엔진 & 플랫폼

- **Unreal Engine 5.1**
- **OpenXR** (크로스 플랫폼 VR 지원)
- **OculusVR** (Meta Quest 시리즈 최적화)

### 주요 플러그인

- `ResonanceAudio` - 3D 공간 음향
- `EnhancedInput` - 향상된 입력 시스템
- `Water` - 바다 및 물 시뮬레이션

### 지원 플랫폼

- Windows (PC VR)
- Android (Quest 시리즈)
- Linux, Mac
- Console (PS4/PS5, Xbox, Switch)
- HoloLens

## 📁 프로젝트 구조

```
Content/
├── 📂 Assets/           # 3D 모델 및 에셋
├── 📂 Audios/          # 음향 파일
├── 📂 Characters/      # 캐릭터 모델 및 애니메이션
├── 📂 FPWeapon/        # 1인칭 무기 시스템
├── 📂 FXVarietyPack/   # 시각 효과
├── 📂 GN_Blueprint/    # 게임 플레이 블루프린트
├── 📂 GN_UI/           # 사용자 인터페이스
├── 📂 Gallery/         # 갤러리 시스템
├── 📂 Levels/          # 게임 레벨
├── 📂 MJ_Blueprint/    # 메인 블루프린트 로직
├── 📂 MJ_PuzzleImages/ # 퍼즐 게임 이미지
├── 📂 Movies/          # 비디오 파일
├── 📂 Sequence/        # 시네마틱 시퀀스
├── 📂 Sounds/          # 효과음
├── 📂 VRTemplate/      # VR 템플릿
└── 📂 temp_BP/         # 임시 블루프린트
```

## 🎮 주요 기능

### VR 인터랙션

- 손 추적 및 컨트롤러 지원
- 물리 기반 상호작용
- 공간 이동 및 텔레포트

### 역사적 콘텐츠

- 거북선 체험
- 명량대첩 재현
- 조선 수군 전술 학습
- 역사적 인물 갤러리

### 교육적 요소

- 퍼즐 게임을 통한 학습
- 인터랙티브 갤러리
- 역사적 배경 설명

## 🚀 시작하기

### 시스템 요구사항

- **OS**: Windows 10/11 (64-bit)
- **VR**: Oculus Rift/Quest, SteamVR 지원 헤드셋
- **RAM**: 16GB 이상 권장
- **GPU**: GTX 1060 / RX 580 이상

### 설치 방법

1. 레포지토리 클론

```bash
git clone https://github.com/myoungjelee/UE5_VR_Immortal-YiSunSin.git
```

2. Unreal Engine 5.1 설치
3. `.uproject` 파일 더블클릭으로 프로젝트 열기
4. VR 헤드셋 연결 후 플레이

## 🎯 개발 진행상황

- [x] VR 기본 시스템 구축
- [x] 캐릭터 및 환경 모델링
- [x] 인터랙션 시스템 구현
- [x] 갤러리 시스템 완성
- [x] 퍼즐 게임 구현
- [ ] 전투 시퀀스 완성
- [ ] 최적화 및 성능 개선
- [ ] 멀티플랫폼 테스트

## 📸 스크린샷

_스크린샷은 향후 업데이트 예정입니다._

## 🤝 기여하기

이 프로젝트는 교육용 목적으로 제작되었습니다. 개선사항이나 버그를 발견하시면 이슈를 등록해 주세요.

## 📄 라이선스

이 프로젝트는 교육 및 연구 목적으로 제작되었습니다.

## 📞 연락처

**개발자**: myoungjelee  
**GitHub**: [@myoungjelee](https://github.com/myoungjelee)

---

_한국사를 VR로 체험하며 배우는 새로운 교육의 미래를 만들어갑니다_ 🇰🇷
