#ifndef TESTCASE_H
#define TESTCASE_H

#define TESTCASE 1   // 1 = 테스트 코드 빌드, 0 = 일반 빌드

#if TESTCASE

void run_whitebox_tc1(void);  // PMIC VOUT 변경 확인
void run_whitebox_tc2(void);  // DTC 저장/삭제 동작 확인
void run_blackbox_tc1(void);  // CAN UDS ReadDTC 요청 시 응답 확인
void run_blackbox_tc2(void);  // CAN UDS ClearDTC 요청 시 응답 확인
void run_all_tests(void);

#endif // TESTCASE

#endif
